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
Open up Vitis 2023.2 and choose `Open Workspace`.
![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/41b6197c-7f92-4b0e-9d10-09e3f0f22790)

Choose where to create the workspace, create a new folder, and select that folder as the workspace.
![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/0f875eb0-73c2-48b2-a31e-982e611b9ab9)

After the workspace has loaded, click the `Create HLS Component` button.
![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/63b93914-d99f-462c-b4ce-b0e988f28b5f)

Set a name for the hls component and click `Next`
![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/d6c2f056-5f84-4f46-9e62-65375dde6ac0)

Leave as is and click `Next`
![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/77e4584b-e3db-4a26-9d66-fe528a5a69b5)

For now, skip adding design and testbench files. We will do this at a later
stage. Click `Next`.
![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/7a1059a6-f684-4cf3-a2f1-9efacd0ae852)

Find the correct part and click `Next`
![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/e2f555bf-4c96-46b5-b718-a74516c41ca6)

Leave as is and click `Next`
![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/94db124d-1eff-4650-92a3-88a87ed19b5e)

Click `Finish`.
![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/13accd00-4dd6-4167-add4-caab39039b9a)


### 1.2 Create Source Files
On the left side in the Explorer window, right-click `Sources` and click `Add Source
File`. 
![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/89330e01-683f-4fcf-b57d-52249bc8e95c)

Add the files `fir.c` and `fir.h`.
![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/22040adf-fdd3-4ccc-907f-e87acebebc23)

Right-click on `Test Bench`, click `Add Test Bench File`.
![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/72d2b99b-d56d-428e-8df3-c18312965541)

Add the file `tb.c`.
![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/95d23d3a-26e4-49d4-825f-d918468cbe32)


The file tree should now look like this:
![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/f4c514e4-89eb-4707-a2c2-481fab28efee)

### 1.3 Get Source Code from Github
The source code can be found here:
* [tb.c](src/hls/tb.c)
* [fir.c](src/hls/fir.c)
* [fir.h](src/hls/fir.h)

The files should now look like this:

`fir.h`

![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/5e716d2e-da83-488c-b124-8bf63b93c1eb)

`fir.c`

![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/48953be3-61f2-4bb5-9edb-275bfe898053)

`tb.c`

![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/44191923-92fa-4693-952d-70a1fbc1f74e)

Click gear-icon on the right side of `C SYNTHESIS`. 
![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/8a97578e-bdc7-402b-a446-4815b781716f)

Search for top.
![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/130cef9e-c8a4-4943-8f92-b5f73a71b4c3)

Click `Browse` to select the top level function for synthesis. In our case this is `fir.c` and click `OK`.
![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/eac6f38d-d292-4972-a638-7f45267b1760)

### 1.4 Simulation and Synthesis
In the Flow navigator window:
![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/273e78ba-3053-49b2-a2e7-e4a83d4ba9b3)

Run the C simulation and ensure that the output looks something like this:
```
 Output:  Abbbbbbbbbbbbbbbbbb
 INFO: [SIM 211-1] CSim done with 0 errors.
 INFO: [SIM 211-3] *************** CSIM finish ***************
 INFO: [HLS 200-111] Finished Command csim_design CPU user time: 0 seconds. CPU system time: 0 seconds. Elapsed time: 23.032 seconds; current allocated memory: 0.934 MB.
 INFO: [HLS 200-1510] Running: close_project 
 INFO: [HLS 200-112] Total CPU user time: 1 seconds. Total CPU system time: 0 seconds. Total elapsed time: 28.659 seconds; peak allocated memory: 169.469 MB.
 INFO: [Common 17-206] Exiting vitis_hls at Fri Nov 10 14:14:04 2023...
 INFO: [vitis-run 60-791] Total elapsed time: 0h 0m 48s
 C-simulation finished successfully
```

Run the C Synthesis
![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/fe1055c6-d84a-4f88-91da-e508b646a08b)

Ensure that the report looks something like this:
![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/853a4733-3bf6-4a5d-8799-5508cd622f6d)


The code is not optimised and has timing violations. Since this is only an example, this is fine.

#### [Optional] Improve the latency

Swap out the content of `fir.c` with [fir_improved.c](src/hls/fir_improved.c) and run C Synthesis again.
![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/0aed7147-ee45-40f0-8979-a89713e7a09c)



### 1.5 Export RTL as IP

Keep as `Verilog` 
![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/14935579-0a29-40d6-851a-34e8cba95204)

Set trace level to `all` in order to later see the waveform.
![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/c47f1cec-4b5c-4666-a32d-6926206cace0)

In the Flow navigator window, click `Run` under the  `C/RTL COSIMULATION`.
![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/e57ac0ce-f9fc-453b-b66d-1e588d823134)


#### [Optional] View the waveform

Run Cosimulation and press the `Waveform` button in the top menu and wait for the Vivado program to open.
![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/1efb7b7f-cabc-4b22-8d5e-91412becda06)

![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/87db3f53-0eea-4a51-8afb-8c75b74777e3)

Locate the `Block-level handshake`
![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/a9f57bcd-cf70-4ce7-8c18-d1e2dc5f60ac)

And drag it to the top
![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/0c5a8843-aa35-4bb7-8565-ec855c2f9c09)

Locate the `input_r__output_r__return(axi_slave)`
![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/414e0fa8-3935-447c-b568-22a5f0d45e1d)

And drag it to the top
![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/3e3f2b7f-ed79-403f-b6d7-5ee05cbbb1ec)

Remove the rest, and inspect the waveform
![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/9bf3dd87-1791-4dfa-a958-6856363c3d96)
![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/162e5a5a-61b0-49a3-b4db-6d53c944b800)



## 2. Hardware Setup in Vivado

### 2.1 Create New Project
As we assume some familiarity with the Vivado Design Suite, we will not go over how to create a new project.
Create a new Vivado project and do not create any files.

Remember to select the correct board file. You can find it by searching for `Zybo`. (You might have to click the 'Refresh' button).
Ensure that the `Board Rev` is `B.4`.

![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/82e9f247-3f18-49d1-b703-1acfa834cc00)


### 2.2 Create Block Design

In the `Flow Navigator` window, under `IP INTEGRATOR` click `Create Block Design`.

![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/68607a17-9a05-4e05-91a1-2041f21b8ed6)

Click `OK`

![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/440003db-0a06-4876-aa57-98b9373fa0ab)

In the `Diagram` window, press the `+` button or right-click and press `Add IP`.

Search for `Zynq` in the pop-up window and double-click `ZYNQ7 Processing System`.

![Image](img/vivado-03.png)

In Vitis 2023.2, click `RUN` under `PACKAGE`

![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/7156413c-a005-40a2-9a30-afa65a836a29)


Locate the ZIP file that we just exported, and unzip the file.

![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/61909568-4206-4d44-a4ff-feaf16e9d704)

![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/8f8f7514-82b2-4f13-a62e-90b1fa8c886f)

![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/11b09d5e-034c-4f86-86dc-d02e097baf7f)


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

Select the `Fir_Platform` from earlier

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


Click the gear-icon to the right of `Run` under `Component`

![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/5e2a797b-450b-4488-9905-c765667e1a2b)

If `Board Initialization` is set to TCL, you might get an error.

![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/4cdad469-cbb3-4ef2-b509-6d29d48e1898)

Set `Board Initialization` to FSBL

![image](https://github.com/MartinJrgsn/CS4110-HLS-Tutorial/assets/72263169/7102ddc8-a264-4b8c-826b-04d93142249e)


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
