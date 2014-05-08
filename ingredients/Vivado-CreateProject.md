# Create a Project in Vivado

- Prerequests: 
  - Vivado has been installed
  - license has been configured properly
- Demo version: Vivado 2014.1

## GUI Work Flow
### Launch Vivado on Windows

![Vivado in Windows Start Menu](../images/Vivado-CreateProject-LaunchVivadoWindows.png)

### Launch Vivado on Linux
```bash
source /opt/Xilinx/Vivado/2014.1/settings64.sh
# /opt/Xilinx is the installation directory of Vivado
vivado &
# & means launch the tool and enable more commands in this shell
```

### Vivado Startup Window
![Vivado Startup Window](../images/Vivado-CreateProject-StartupWindow.png)

### Create New Project
Input Project Name and Location

![Vivado New Project Name](../images/Vivado-CreateProject-NewProject-ProjectName.png)


Select RTL Project for projects with HDL as top module

![Vivado New Project Type](../images/Vivado-CreateProject-NewProject-ProjectType.png)

Select Project Part with the help of filters

![Vivado New Project Part](../images/Vivado-CreateProject-NewProject-DefaultPart-Part.png)

If Xilinx demo boards are used, go to `Boards` and select the board.

![Vivado New Project Board](../images/Vivado-CreateProject-NewProject-DefaultPart-Board.png)

Review the project summary

![Vivado New Project Summary](../images/Vivado-CreateProject-NewProject-Summary.png)

Click Finish then get the created project.
![Vivado New Project Final](../images/Vivado-CreateProject-NewProject-Project.png)

## Tcl Work Flow
### Create Project
Tcl Command
`create_project <project name> <project location> -part <part number,package-speedgrade>`
Example
`create_project project_1 C:/CASE/CASE/demo/project_1 -part xc7z020clg484-1`

### Set Board Model
Example
`set_property board_part xilinx.com:zc702:part0:1.0 [current_project]`