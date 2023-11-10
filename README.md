# Using HLS with Zybo Zynq-7000 development board

## Table of Contents

* [Introduction](#introduction)
* [Prerequisites](#prerequisites)
1. [High Level Synthesis in Vitis HLS](#1-high-level-synthesis-in-vitis-hls)
	1. [Create New Project](#11-create-new-project)
	1. [Create Source Files](#12-create-source-files)
	1. [Get Source Code from Github](#13-get-source-code-from-github)
	1. [Simulation and Synthesis](#14-simulation-and-synthesis)
	1. [Export RTL as IP](#15-export-rtl-as-ip)
1. [Hardware Setup in Vivado](#2-hardware-setup-in-vivado)
	1. [Create New Project](#21-create-new-project)
	1. [Create Block Design](#22-create-block-design)
	1. [Create HDL Wrapper and Generate Bitstream](#23-create-hdl-wrapper-and-generate-bitstream)
	1. [Export Hardware Platform](#24-export-hardware-platform)
1. [Application Setup in Vitis](#3-application-setup-in-vitis)
	1. [Create Platform Project](#31-create-platform-project)
	1. [Create Application Project](#32-create-application-project)
	1. [Get Source Code from Github](#33-get-source-code-from-github)
	1. [Build and Run Project](#34-build-and-run-project)
1. [Further Reading](#further-reading)

## Introduction
This is a complete guide for utilising a Vitis HLS design with the Zybo Zynq-7000 development board. We will use a simple FIR (Finite Impulse Response) moving average filter as an example.

The guide has been made for the USN course CS4110 by Kent Odde and Stian Onarheim upon request of Professor Jose Ferreira.

## Prerequisites
* Vitis 2021.X
* Viviado 2021.X
* Vitis HLS 2021.X
* Zybo Zynq-7000 development board



## 1. High Level Synthesis in Vitis HLS

### 1.1 Create New Project
Open up Vitis HLS and choose `Create Project`.

![Image](img/vitis-hls-01.png)

Give the project a suitable name and location.

![Image](img/vitis-hls-02.png)

For now, skip adding design and testbench files. We will do this at a later
stage. Click `Next`.

![Image](img/vitis-hls-03.png)

Click the "Three horizontal dots" button under `Part Selection`.

![Image](img/vitis-hls-04.png)

In the `Device Selection Dialog`, press `Boards` and search for `Zybo`.
To install board files, look at Jose and Manuels guide [here](https://usn.instructure.com/courses/24824/pages/w2-day-1-zybo-hw-development-tutorial?module_item_id=269761).

If the board does not show up, try clicking `Boards` again after searching and the board should appear. 

If on Linux, also follow the instructions in the last post [here](https://forum.digilentinc.com/topic/16795-vivado-hls-board-files-for-the-zyboz7-20/).

![Image](img/vitis-hls-05.png)

Give the solution a suitable name and press `Finish`.

![Image](img/vitis-hls-06.png)

### 1.2 Create Source Files
On the left side in the Explorer window, right-click `Sources` and click `New
file`. Add the files `fir.c` and `fir.h`.

Right-click on `Test Bench`, click `New file` and add the file `tb.c`.

![Image](img/vitis-hls-07.png)

The file tree should now look like this:

![Image](img/vitis-hls-08.png)

### 1.3 Get Source Code from Github
The source code can be found here:
* [tb.c](src/hls/tb.c)
* [fir.c](src/hls/fir.c)
* [fir.h](src/hls/fir.h)

The files should now look like this:

`fir.h`

![Image](img/vitis-hls-09.png)

`fir.c`

![Image](img/vitis-hls-10.png)

`tb.c`

![Image](img/vitis-hls-11.png)

Go to `Project` --> `Project Settings` --> `Syntesis`. Select `fir.c` and click `Browse` to select the top level function for synthesis. In our case this is `fir`.

![Image](img/vitis-set-top-function.png)

### 1.4 Simulation and Synthesis
In the Flow navigator window as seen below:

![Image](img/vitis-hls-12.png)

Run the C simulation and ensure that the output looks something like this:
```
utput:  Abbbbbbbbbbbbbbbbbb
INFO: [SIM 211-1] CSim done with 0 errors.
INFO: [SIM 211-3] *************** CSIM finish ***************
INFO: [HLS 200-111] Finished Command csim_design CPU user time: 23.45 seconds. CPU system time: 1.31 seconds. Elapsed time: 24.48 seconds; current allocated memory: 251.756 MB.
Finished C simulation.
```

Run the C Synthesis and ensure that the output looks something like this:

![Image](img/vitis-hls-13.png)

The code is not optimised and has timing violations. Since this is only an example, this is fine.

#### [Optional] Improve the latency

Swap out the content of `fir.c` with [fir_improved.c](src/hls/fir_improved.c) and run C Synthesis again.

![Image](img/vitis-hls-17.png)



### 1.5 Export RTL as IP

In the Flow navigator window, press the `Export RTL` button and save the ZIP file in a suitable location. When prompted by the `Run Cosimulation` window, keep it set to `Verilog`, and set dump trace to `all` in order to later see the waveform. (See image below).

![Image](img/vitis-hls-14.png)

![Image](img/vitis-hls-cosimulation.png)


#### [Optional] View the waveform

Run Cosimulation and press the `Waveform` button in the top menu and wait for the Vivado program to open.

![Image](img/vitis-hls-15.png)

It should look something like this:

![Image](img/vitis-hls-16.png)

## 2. Hardware Setup in Vivado

### 2.1 Create New Project
As we assume some familiarity with the Vivado Design Suite, we will not go over how to create a new project.
Create a new Vivado project and do not create any files.

Remember to select the correct board file. You can find it by searching for `Zybo`. (You might have to click the 'Refresh' button).
Ensure that the `Board Rev` is `B.4`.

![Image](img/vivado-01.png)

### 2.2 Create Block Design

In the `Flow Navigator` window, under `IP INTEGRATOR` click `Create Block Design`.

![Image](img/vivado-02.png)

In the `Diagram` window, press the `+` button or right-click and press `Add IP`.

Search for `Zynq` in the pop-up window and double-click `ZYNQ7 Processing System`.

![Image](img/vivado-03.png)

Locate the ZIP file that we exported in step [1.5](#15-export-rtl-as-ipxo), and unzip the file.

![Image](img/vivado-04.png)

Go back to the `Flow Navigator` window in Vivado and click `IP Catalog` under `PROJECT MANAGER`.

Right-click anywhere in the `IP Catalog` tab and click `Add Repository` and select the folder that we unzipped.

![Image](img/vivado-05.png)

Expand the `User Repository` folder and double-click `Fir`.

![Image](img/vivado-06.png)

Click the `Add IP to Block Design` button.

![Image](img/vivado-07.png)

Return to the `Diagram` window. It should now look something like this:

![Image](img/vivado-08.png)

Click `Run Block Automation`.
The presets should look like the image below. Click the `OK` button.

![Image](img/vivado-09.png)

Click `Run Connection Automation`.
The presets should look like the image below. Click the `OK` button.

![Image](img/vivado-10.png)

Click the `Regenerate Layout` button located in the `Diagram` window's toolbar.

![Image](img/vivado-11.png)

If everything is done correctly, the diagram should now look like this:

![Image](img/vivado-12.png)

Click the `Validate Design` button located in the `Diagram` window's toolbar.

![Image](img/vivado-13.png)

Ignore the four critical warning messages.
Click the `OK` button.

![Image](img/vivado-14.png)

### 2.3 Create HDL Wrapper and Generate Bitstream

Right-click the design file under `Sources` and click `Create HDL Wrapper`.

![Image](img/vivado-15.png)

Select the `Let Vivado manage wrapper and auto-update` option and click the `OK` button.

![Image](img/vivado-16.png)

In the `Flow Navigator` window, click the `Generate Bitstream` button located under `PROGRAM AND DEBUG`.

![Image](img/vivado-17.png)

Click the `OK` button.

![Image](img/vivado-18.png)

This will take some time. Eventually you will be met with a window like this:

![Image](img/vivado-19.png)

### 2.4 Export Hardware Platform

Click `File` --> `Export` --> `Export Hardware`.

![Image](img/vivado-20.png)

Choose the `Include bitstream` option and click the `Next` button.

![Image](img/vivado-21.png)

Choose a suitable XSA file name and location. In the final window, click the `Finish` button.

![Image](img/vivado-22.png)

## 3. Application Setup in Vitis

### 3.1 Create Platform component

Continue in your vitis workspace, and click + button:

![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/115153285/bfb1d0e8-bff1-47a7-b013-a9a09673ec57)

![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/115153285/d61bad9c-bb0f-4919-9fdf-064b72fe74fb)


Choose a suitable platform project name and click `Next`.

![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/115153285/ea58675b-70e8-4b57-8367-13f5d71600cc)

Select Hardware Design, and specify the XSA file that we created in step [2.4](#24-export-hardware-platform).

![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/115153285/27376a35-07d9-4099-88a3-2d6165f5614b)


Ensure that the `Software Specification` section matches the image below, and click `Finish`.

![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/115153285/9693ae3f-1d94-4c28-8fdd-47aa77e6d407)

Click finish.

![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/115153285/17c3d5a6-f477-44d5-91dd-8bf2af08fb3a)

Wait for Vitis to complete loading:

![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/115153285/08c0d5a5-0515-4de3-976c-b8f23f5e3d59)

Click build:

![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/115153285/d8c0114b-87ea-40be-aec9-e73db30fa090)


### 3.2 Create Application Project

Click file>New Component>From Examples

![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/115153285/2a19d31d-6207-4a14-8929-fa09dc35886b)

Select Hello World

![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/115153285/551ac999-a5bd-4349-adf1-5c4a52c4270c)

Click the button "Create Application component from template" without changing any of the options.

![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/115153285/a46f36c9-f12e-41a7-b04e-9ebae7062ddc)

Specify a name and click next.

![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/115153285/f0f9644e-5f2d-4840-9171-ed080b3ee248)

Select the Fir_platform from earlier

![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/115153285/f5d41ca4-3d3a-4e7c-9e1d-60f3d1248503)

Should look like this:

![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/115153285/b2316fee-2a98-4db0-bf02-9586b6f42172)

![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/115153285/9c041f0e-770a-49cc-b154-94d89d2ccd0f)


### 3.3 Get Source Code from Github
The source code can be found here:
* [main.c](src/main.c)

Swap the file content of `helloworld.c` with `src/main.c` from the Git repository.

### 3.4 Build and Run Project

Build the component

![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/115153285/8e3534e9-8974-47fd-bd9d-f2d4d73c9bcf)


Remember to set the boot mode jumper (21 in the Figure) to JTAG mode (to the far right).



![Image](img/vitis-15.png)


Run the component while the Zybo board is connected.

![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/115153285/e5b9d479-f683-4fe9-8ee7-7306ebc1d55f)


Use a serial communication tool (screen, PuTTY) to interact with your application running on the Zybo.

We will use putty:

![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/115153285/b12dd09e-03a7-469a-b0e0-7e2680651591)

![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/115153285/e9f9d375-0611-46d1-8f32-91d2b6fc0853)

![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/115153285/36ab285d-57cd-488d-8ea7-5b2c354d52c8)

At all times it should print out the moving average of the three last entered characters.

For instance, entering the sequence `a b c` repeatedly, should result in only `b`'s as output, as this will
be the current moving average.

![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/115153285/355d18e0-ce80-42ab-8e4d-0ea8118a6683)


# Further Reading

See section 4 in the [Vitis High-Level Synthesis User Guide](https://www.xilinx.com/support/documentation/sw_manuals/xilinx2020_2/ug1399-vitis-hls.pdf) for more information about the AXI4-Lite slave C drivers.
