# Create a ZYNQ only BD Design without DDR
Design Target:

- Processor: ZYNQ
- No further IP connected
- Disable DDR Controller
- Enable QSPI Flash so that ZYNQ can boot PL from QSPI

## GUI Work Flow

### Create Block Design
![](../images/Vivado-CreateBD.png)

### Set BD Name
![](../images/Vivado-CreateBD-Name.png)

### Add IP in BD
![](../images/Vivado-CreateBD-AddIp.png)

### Add ZYNQ
![](../images/Vivado-CreateBD-AddZynq.png)

### ZYNQ Default Block
![](../images/Vivado-CreateBD-ZynqDefault.png)

### Double Click ZYNQ Block to Configure ZYNQ
![](../images/Vivado-CreateBD-ZynqConfigDefault.png)

### Remove FCLK Output
![](../images/Vivado-CreateBD-ZynqRemoveFclk.png)

### Remove AXI Master GP0
![](../images/Vivado-CreateBD-ZynqRemoveGP0M.png)

### Disable DDR Controller
![](../images/Vivado-CreateBD-ZynqRemoveDDR.png)

### Enable QSPI Controller
![](../images/Vivado-CreateBD-ZynqEnableQSPI.png)

### Make Ports External
![](../images/Vivado-CreateBD-MakePortsExternal.png)

### Final ZYNQ Block Configuration
![](../images/Vivado-CreateBD-FinalBD.png)