# How to Handle Interrupt from PL #

## Resource ##
- [AR 62363](http://www.xilinx.com/support/answers/62363.html)

## Example Instructions ##
- This example is based on Vivado 2014.4 and PetaLinux 2014.4. 
- Linux kernel is using 3.17.

### Vivado Hardware Project ###

1. Create a new Vivado project based on your board
1. Create a block design
1. Add ZYNQ PS7 IP
1. Set PS7
  - Enable AXI GP0
  - Enable FCLK0 and set it to 100MHz
1. Add AXI Timer
1. Connect AXI Timer and ZYNQ PS7

The repo has an script to reproduce this project based on MicroZed board.
To run the script, open Vivado and run the following scripts in tcl console:
```tcl
cd <git_repo_root>/projects/HowToHandleInterruptFromPL
source <your_board_initialization_script>
source project.tcl  
# project.tcl creates the project, regenerate the block design, run implementation and export the design
```

### Create PetaLinux Project ###
1. Create a new PetaLinux project

  ``` 
  petalinux-create -t project -n petalinux
  cd petalinux
  ```

1. Import the hardware settings

  ```
  petalinux-config --get-hw-description=<Vivado_Export_to_SDK_Directory>
  ```

1. Try to build with the default settings

  ```
  petalinux-build
  petalinux-package --boot --fsbl ./images/linux/zynq_fsbl.elf --fpga <BITSTREAM> --u-boot
  ```

1. Check whether it works

  - The command above generates BOOT.bin in current working directory and `image/linux` directory.
  - Copy `BOOT.BIN` and `image.ub` to SD card
  - Boot your demo board from SD card
  - It should boot PetaLinux. Otherwise, check the above steps
  - Login with username = root, password = root
  - run `cat /proc/interrupts`. The Interrupt 61 should appear because petalinux by default assign the axi_timer driver to axi_timer IP.

### Customize PetaLinux ###
1. Unregister the driver for AXI Timer.
  1. Open <PetaLinux Project>/subsystems/linux/configs/device-tree/pl.dtsi
  1. Go to the line start with `compatible` under `axi_timer_0` block and remove this line

1. Check the interrupt number
  1. In `axi_timer_0` block, the interrupt number is in line `interrupts = <0 29 4>`. `29` here is the interrupt source.

1. Create driver module

  ```
  petalinux-create -t module -n axitimer_intr --enable
  ```

1. Add driver module source code
  1. Copy `axitimer_intr.c` to `<PetaLinux Project>/components/modules/axi_timer_intr/axitimer_intr.c` and replace the original file.

1. Open and check the file
  1. In line 14, `#define IRQ_NUM` is changed from 91 to 61. The 61 is calculated from the above `29` + 32.

1. Build the project
  ```
  petalinux-build
  ```

1. Check the design
  1. Copy `image/linux/image.ub` to SD card
  1. Boot demo board from SD card
  1. After login, `cat /proc/interrupts` should not show interrupt source 61 again.
  1. Find the axi_timer kernel module `find . -name "axitimer_intr.ko"`
  1. Insert module to kernel `insmod axitimer_intr.ko`. The console should show the print like this:

```
root@petalinux:/lib/modules/3.17.0-xilinx/extra# insmod axitimer_intr.ko
xilaxitimer_init: Initialize Module "xilaxitimer"
xilaxitimer_init: Registered IRQ 61
xilaxitimer_init: Set timer count 0xF8000000
root@petalinux:/lib/modules/3.17.0-xilinx/extra# xilaxitimer_isr: Interrupt Occurred ! Timer Count = 0xF80003A4
xilaxitimer_isr: Interrupt Occurred ! Timer Count = 0xF8000277
xilaxitimer_isr: Interrupt Occurred ! Timer Count = 0xF8000256
xilaxitimer_isr: Interrupt Occurred ! Timer Count = 0xF80003C2
xilaxitimer_isr: Interrupt Occurred ! Timer Count = 0xF80001B4
xilaxitimer_isr: Interrupt Occurred ! Timer Count = 0xF8000279
xilaxitimer_isr: Interrupt Occurred ! Timer Count = 0xF800028D
xilaxitimer_isr: Interrupt Occurred ! Timer Count = 0xF8000271
xilaxitimer_isr: Interrupt Occurred ! Timer Count = 0xF8000292
xilaxitimer_isr: Interrupt Occurred ! Timer Count = 0xF8000255
xilaxitimer_isr: Interrupt Occurred ! Timer Count = 0xF8000275
xilaxitimer_isr: Interrupt Occurred ! Timer Count = 0xF80001B5
xilaxitimer_isr: Interrupt Occurred ! Timer Count = 0xF8000263
xilaxitimer_isr: Interrupt Occurred ! Timer Count = 0xF8000264
```
