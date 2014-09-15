# How to Add Unzip Function to U-boot #

1. Open the U-boot config source code

  For ZYNQ, it's u-boot-xlnx/include/configs/zynq_zc70x.h

2. Append `#define CONFIG_CMD_UNZIP` to the file before `#endif`

  The full list of u-boot commands can be found at u-boot-xlnx/include/config_cmd_all.h

3. Clean and recompile u-boot
  ```
  make distclean
  make zynq_zc70x
  ```
