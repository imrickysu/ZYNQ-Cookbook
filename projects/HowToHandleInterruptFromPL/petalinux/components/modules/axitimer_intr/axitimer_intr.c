#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <asm/io.h>

MODULE_LICENSE("GPL");

#define DEVICE_NAME "xilaxitimer"

//#define IRQ_NUM		91
#define IRQ_NUM	61	


#define XIL_AXI_TIMER_BASEADDR 0x41C00000
#define XIL_AXI_TIMER_HIGHADDR 0x41C0FFFF

#define XIL_AXI_TIMER_TCSR_OFFSET		0x0
#define XIL_AXI_TIMER_TLR_OFFSET		0x4
#define XIL_AXI_TIMER_TCR_OFFSET		0x8
#define XIL_AXI_TIMER_CSR_INT_OCCURED_MASK	0x00000100

#define XIL_AXI_TIMER_CSR_CASC_MASK		0x00000800
#define XIL_AXI_TIMER_CSR_ENABLE_ALL_MASK	0x00000400
#define XIL_AXI_TIMER_CSR_ENABLE_PWM_MASK	0x00000200
#define XIL_AXI_TIMER_CSR_INT_OCCURED_MASK	0x00000100
#define XIL_AXI_TIMER_CSR_ENABLE_TMR_MASK	0x00000080
#define XIL_AXI_TIMER_CSR_ENABLE_INT_MASK	0x00000040
#define XIL_AXI_TIMER_CSR_LOAD_MASK		0x00000020
#define XIL_AXI_TIMER_CSR_AUTO_RELOAD_MASK	0x00000010
#define XIL_AXI_TIMER_CSR_EXT_CAPTURE_MASK	0x00000008
#define XIL_AXI_TIMER_CSR_EXT_GENERATE_MASK	0x00000004
#define XIL_AXI_TIMER_CSR_DOWN_COUNT_MASK	0x00000002
#define XIL_AXI_TIMER_CSR_CAPTURE_MODE_MASK	0x00000001

#define TIMER_CNT	0xF8000000

static struct platform_device *pdev;
void *dev_virtaddr;
static int int_cnt;

static irqreturn_t xilaxitimer_isr(int irq,void*dev_id)		
{      
  unsigned int data;
  
  /* 
   * Check Timer Counter Value
   */
  data = ioread32(dev_virtaddr + XIL_AXI_TIMER_TCR_OFFSET);
  printk("xilaxitimer_isr: Interrupt Occurred ! Timer Count = 0x%08X\n",data);
  
  /* 
   * Clear Interrupt
   */
  data = ioread32(dev_virtaddr + XIL_AXI_TIMER_TCSR_OFFSET);
  iowrite32(data | XIL_AXI_TIMER_CSR_INT_OCCURED_MASK,
	    dev_virtaddr + XIL_AXI_TIMER_TCSR_OFFSET);
  
  /* 
   * Disable Timer after 100 Interrupts
   */
  int_cnt++;
  
  if (int_cnt>=100)
    {
      printk("xilaxitimer_isr: 100 interrupts have been occurred. Disabling timer");
      data = ioread32(dev_virtaddr + XIL_AXI_TIMER_TCSR_OFFSET);
      iowrite32(data & ~(XIL_AXI_TIMER_CSR_ENABLE_TMR_MASK),
		dev_virtaddr + XIL_AXI_TIMER_TCSR_OFFSET);
    }
  
  return IRQ_HANDLED;
}

static int __init xilaxitimer_init(void)  
{
  unsigned int data;
  
  int_cnt = 0;
  
  printk(KERN_INFO "xilaxitimer_init: Initialize Module \"%s\"\n", DEVICE_NAME);
  
  /* 
   * Register ISR
   */
  if (request_irq(IRQ_NUM, xilaxitimer_isr, 0, DEVICE_NAME, NULL)) {
    printk(KERN_ERR "xilaxitimer_init: Cannot register IRQ %d\n", IRQ_NUM);
    return -EIO;
  }
  else {
    printk(KERN_INFO "xilaxitimer_init: Registered IRQ %d\n", IRQ_NUM);
  }
  
  /* 
   * Map Physical address to Virtual address
   */
  dev_virtaddr = ioremap_nocache(XIL_AXI_TIMER_BASEADDR,
				 XIL_AXI_TIMER_HIGHADDR - XIL_AXI_TIMER_BASEADDR + 1);
  
  /* 
   * Set Timer Counter
   */
  iowrite32(TIMER_CNT,
	    dev_virtaddr + XIL_AXI_TIMER_TLR_OFFSET);
  data = ioread32(dev_virtaddr + XIL_AXI_TIMER_TLR_OFFSET);
  printk("xilaxitimer_init: Set timer count 0x%08X\n",data);
  
  /* 
   * Set Timer mode and enable interrupt
   */
  iowrite32(XIL_AXI_TIMER_CSR_LOAD_MASK,
	    dev_virtaddr + XIL_AXI_TIMER_TCSR_OFFSET);
  iowrite32(XIL_AXI_TIMER_CSR_ENABLE_INT_MASK | XIL_AXI_TIMER_CSR_AUTO_RELOAD_MASK,
	    dev_virtaddr + XIL_AXI_TIMER_TCSR_OFFSET);

  /* 
   * Register Device Module
   */
  pdev = platform_device_register_simple(DEVICE_NAME, 0, NULL, 0);              
  if (pdev == NULL) {                                                     
    printk(KERN_WARNING "xilaxitimer_init: Adding platform device \"%s\" failed\n", DEVICE_NAME);
    kfree(pdev);                                                             
    return -ENODEV;                                                          
  }
  
  /* 
   * Start Timer
   */
  data = ioread32(dev_virtaddr + XIL_AXI_TIMER_TCSR_OFFSET);
  iowrite32(data | XIL_AXI_TIMER_CSR_ENABLE_TMR_MASK,
	    dev_virtaddr + XIL_AXI_TIMER_TCSR_OFFSET);

  return 0;
} 

static void __exit xilaxitimer_edit(void)  		
{
  /* 
   * Exit Device Module
   */
  iounmap(dev_virtaddr);
  free_irq(IRQ_NUM, NULL);
  platform_device_unregister(pdev);                                             
  printk(KERN_INFO "xilaxitimer_edit: Exit Device Module \"%s\".\n", DEVICE_NAME);
}

module_init(xilaxitimer_init);
module_exit(xilaxitimer_edit);

MODULE_AUTHOR ("Xilinx");
MODULE_DESCRIPTION("Test Driver for Zynq PL AXI Timer.");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("custom:xilaxitimer");
