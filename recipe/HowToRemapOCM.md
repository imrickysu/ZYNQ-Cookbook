# How to Remap OCM #

### Register ###
SLCR.OCM_CFG: 0xF8000910

### Details ###
The 256 KB RAM array can be mapped to either a low address range ( 0x0000_0000  to 0x0003_FFFF ) or a high address range ( 0xFFFC_0000  to  0xFFFF_FFFF ) in a granularity of four independent 64 KB sections via the 4-bit slcr.OCM_CFG[RAM_HI].

(Excerpted from Chapter 29. OCM)

### References ###
Refer to UG585 Chapter 29.2.4 -> OCM Relocation and Chapter 29.4 Programming Model for the process of modifying this register.

### Example ###
* When OCM_CFG = 0x10, OCM address is mapped to 0x00000000 - 0x0003FFFF
* When OCM_CFG = 0x18, OCM address is mapped to 0x00000000 - 0x0002FFFF and 0xFFFF00000 - 0xFFFFFFFF
* When OCM_CFG = 0x1F, OCM address is mapped to 0xFFFC0000 - 0xFFFFFFFF

Note: SLCR needs to be unlocked before writing data to it.

### Program Defaults ###
BootROM sets OCM_CFG to 0x18, which means OCM is mapped to first 196KB and last 64KB (0x00000000 - 0x0002FFFF and 0xFFFF00000 - 0xFFFFFFFF).

U-boot set OCM_CFG to 0x1F, which means OCM is mapped to last 256KB (0xFFFC0000 - 0xFFFFFFFF) [AR47047](http://www.xilinx.com/support/answers/47047.htm)
