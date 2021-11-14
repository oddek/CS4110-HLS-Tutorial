# Using HLS with Zybo Zynq-7000 development board

## Table of Contents

* [About the Project](#about-the-project)
* [Example Programs](#example-programs)
* [Source Code](#source-code)
* [Computer](#computer)
	* [CPU](#cpu)
* [Assembler](#assembler)
* [Usage](#usage)
* [In Action](#in-action)
* [License](#license)
* [Contact](#contact)

## Introduction
This is a complete guide to utilising a Vitis HLS design with the Zybo Zynq-7000 development board. We will use a simple `FIR` (Finite Impulse Response) as an example.

## Prerequisits
* Vitis 2021.X
* Viviado 2021.X
* Vitis HLS 2021.X
* Zybo Zynq-7000 development board

## 1. Vitis HLS

### 1.1 Create new project
Open up Vitis HLS and choose `Create Project`.

![Hello](img/vitis-hls-01.png)

Give the project a suitable name and location, and click `Next`.

![Hello](img/vitis-hls-02.png)

For now, skip adding design and testbench files. We will do this at a later
stage. Click `Next`.

![Hello](img/vitis-hls-03.png)

Clik the "Three dots button" under `Part Selection`.

![Hello](img/vitis-hls-04.png)

In the Device Selection Dialog pess `Boards` and search for `Zybo`.

![Hello](img/vitis-hls-05.png)

Give the solution a suitable name and press `Finish`.

![Hello](img/vitis-hls-06.png)

### 1.2 Create source files
On the left side in the Explorer window, right-click `Sources` and clik `New
file`. Add the files `fir.c` and `fir.h`.

Right-click on `Test Bench`, click `New file` and add the file `tb.c`.

![Hello](img/vitis-hls-07.png)

The file tree should now look like this:

![Hello](img/vitis-hls-08.png)

### 1.3 Copy paste file content from Git.
The source code can be found here:
* [tb.c](src/hls/tb.c)
* [fir.c](src/hls/fir.c)
* [fir.h](src/hls/fir.h)

The files should now look like this:

`fir.h`

![Hello](img/vitis-hls-09.png)

`fir.c`

![Hello](img/vitis-hls-10.png)

`tb.c`

![Hello](img/vitis-hls-11.png)

### 1.4 Simulation and synthesis
In the Flow navigator window as seen below:

![Hello](img/vitis-hls-12.png)

Run the C simulation and ensure that the output looks something like this:
```
utput:  Abbbbbbbbbbbbbbbbbb
INFO: [SIM 211-1] CSim done with 0 errors.
INFO: [SIM 211-3] *************** CSIM finish ***************
INFO: [HLS 200-111] Finished Command csim_design CPU user time: 23.45 seconds. CPU system time: 1.31 seconds. Elapsed time: 24.48 seconds; current allocated memory: 251.756 MB.
Finished C simulation.
```

Run the C Synthesis and ensure that the output looks something like this:

![Hello](img/vitis-hls-13.png)

The code is not optimised and has timing violations. Since this is only an example, this is fine.

### 1.5 Export RTL as IP/XO

In the Flow navigator window, press the `Export RTL` button and save the ZIP file in a suitable location.

![Hello](img/vitis-hls-14.png)

#### [Optional] View the waveform

Run Cosimulation and press the `Waveform` button in the top menu and wait for the Vivado program to open.

![Hello](img/vitis-hls-15.png)

It should look something like this:

![Hello](img/vitis-hls-16.png)

## 2. Vivado

### 2.1 Create new project
As we assume some familiarity with the Vivado Design Suite, we will not go over how to create a new project.
Create a new Vivado project and do not create any files.

Remember to select the correct board file. You can find it by searching for `Zybo`. (You might have to click the 'Refresh' button).
Ensure that the `Board Rev` is `B.3`.

![Hello](img/vivado-01.png)

### 2.2 Create Block Design

In the `Flow Navigator` window, under `IP INTEGRATOR` click `Create Block Design`.

![Hello](img/vivado-02.png)

In the `Diagram` window, press the `+` button or right-click and press `Add IP`.

Search for `Zynq` in the pop-up window and double-click `ZYNQ7 Processing System`.

![Hello](img/vivado-03.png)

Locate the ZIP file that we exported in step [1.5 FINPUSS](#15-export-rtl-as-ipxo), and unzip the file.

![Hello](img/vivado-04.png)

Go back to the `Flow Navigator` window in Vivado and click `IP Catalog` under `PROJECT MANAGER`.

Right-click anywhere in the `IP Catalog` tab and click `Add Repository` and select the folder that we unzipped.

![Hello](img/vivado-05.png)

Expand the `User Repository` folder and double-click `Fir`.

![Hello](img/vivado-06.png)

Click the `Add IP to Block Design` button.

![Hello](img/vivado-07.png)

Return to the `Diagram` window. It should now look something like this:

![Hello](img/vivado-08.png)

Click `Run Block Automation`.
The presets should look like the image below. Click the `OK` button.

![Hello](img/vivado-09.png)

Click `Run Connection Automation`.
The presets should look like the image below. Click the `OK` button.

![Hello](img/vivado-10.png)

Click the `Regenerate Layout` button located in the `Diagram` window's toolbar.

![Hello](img/vivado-11.png)

If everything is done correctly, the diagram should now look like this:

![Hello](img/vivado-12.png)

Click the `Validate Design` button located in the `Diagram` window's toolbar.

![Hello](img/vivado-13.png)

Ignore the four critical warning messages.
Clik the `OK` button.

![Hello](img/vivado-14.png)

### 2.3 Create HDL Wrapper and generate bitstream

Right-click the design file unser `Sources` and click `Create HDL Wrapper`.

![Hello](img/vivado-15.png)

Select the `Let Vivado manage wrapper and auto-update` option and click the `OK` button.

![Hello](img/vivado-16.png)

In the `Flow Navigator` window, click the `Generate Bitstream` button located under `PROGRAM AND DEBUG`.

![Hello](img/vivado-17.png)

Click the `OK` button.

![Hello](img/vivado-18.png)

This will take some time. Eventually you will be met with a window like this:

![Hello](img/vivado-19.png)

### 2.4 Export Hardware Platform

Click `File` --> `Export` --> `Export Hardware`.

![Hello](img/vivado-20.png)

Choose the `Include bitstream` option and click the `Next` button.

![Hello](img/vivado-21.png)

Choose a suitable XSA file name and location, and click the `Next` button. In the final window, click the `Finish` button.

![Hello](img/vivado-22.png)

## 3. Vitis

### 3.1 Create Platform Project

Start Vitis IDE and choose a suitable location for your workspace.

![Hello](img/vitis-01.png)

When met by the welcome screen, choose `Create Platform Project`.

![Hello](img/vitis-02.png)

Choose a suitable platform project name and click `Next`.

![Hello](img/vitis-03.png)

Under `Hardware Spesification` click `Browse` and select the XSA file that we created in step LINK.

Ensure that the `Software Specification` section matches the image below, and click `Finish`.

![Hello](img/vitis-04.png)

After the project has been generated, you will be met with this window.

![Hello](img/vitis-05.png)

In the `Explorer` window on the left, right-click the platform project, and click `Build Project`.

![Hello](img/vitis-06.png)

### 3.2 Create Application Project

Create the Application Project. Click `File` --> `New` --> `Application Project`.

![Hello](img/vitis-07.png)

Select the platform that we have created and click `Next`.

![Hello](img/vitis-08.png)

Give the Application Project a suitable name and click `Next`.

![Hello](img/vitis-09.png)

Click `Next`.

![Hello](img/vitis-10.png)

Select the `Hello World` template and click `Finish`.

![Hello](img/vitis-11.png)

You will now be met by the generated Application Project. It should look something like this:

![Hello](img/vitis-12.png)

### 3.3 Copy paste file content from Git.
The source code can be found here:
* [main.c](src/main.c)

Swap the file content of `helloworld.c` with `src/main.c` from the Git repository.

### 3.4 Build and Run Project

In the Explorer window, right-click your application and choose `Build Project`.

![Hello](img/vitis-13.png)



![Hello](img/vitis-14.png)







