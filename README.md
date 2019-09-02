# HiFive1-Blink

This is a demonstration on how to implement a simple C++ program on the FE310-G000 RISC-V based microcontroller on the HiFive1 evaluation kit from SiFive.

The objective is to learn the risc-v and its peripherals from scratch. The drivers are implemented on bare metal.

In this demo the following features of the FE310-G000 chip are used:

- The PLL is used to generate a core clock with 256 MHz fequency
- A pwm peripheral is used to generate a 1 ms tick 
- A GPIO pin is used to set the LED status
- PLIC and the core Interrupt circuitry is excersiced to generate a pwm timer interrupt.

The assembler start-up files and the linker script are copied from the freedom-metal SDK from SiFive. The other drivers are developped in this project, and works directly on top of the chip silicon. The objective is to build a thin- and easily understandable driver layer that can be used to build C++ applications on.

# Set-Up

This repsitory does only contain the application- and driver source code. To run it on the HiFive board it is necessary to compile it into a binary that can be downloaded to the HiFive1 target.

The FE310-G000 is based on a 32-bit RISC-V core, and to compile it, the GCC compiler for the target must be installed.

To set up the project in FreedomStudio, follow the steps below:
- In a workspace of your choise, select File/New/Project to show the "New Project" wizard
- In the dialog select "C/C++" project and "MakeFile project with existing code". Click Next to enter the "Import Existing Code" dialogue
- Brows to the location where you have cloned the project, i.e. [path]/HiFive1-Blink. Then the project name will be automatically set to "HiFive1-Blink". Make sure that the language boxes C and C++ are checked and select the "SiFive RISC-V GNU GCC Newlib" Tool-chain as Toolchain for indexer settings and press Finish.

Once everything is set up you will need to modify the Makefile to reflect where the GCC toolchain is located on your system.
The variable GCC_PATH needs to be changed to [your path to GCC riscv32]/bin

When all is set up it should be possible to build the binary by navigating into the HiFive1-Blink folder and type make in a terminal.

