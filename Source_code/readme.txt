Project Description
-------------------
The project involves creating a linux device driver and corresponding user program on the Raspberry Pi 3B+:
The user program outputs the number of times (0-9) that the infrared sensor was triggered to a 7 segment cathode led display.
The kernel driver acts as an interface between user space and gpio pins. Memory location of gpio pins is abstracted from the user program.
Restart the counter to 1 in the user program once there is an overflow 

This project uses the C programming language.


Prerequisites
-------------
The following prerequisites are needed to complete this project:
Knowledge of creating kernel modules
Knowledge of registering linux devices
Knowledge of location of memory mapped GPIO pins for 7 segment display
Knowledge of user space device driver Linux interfaces
