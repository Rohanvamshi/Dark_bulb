# Dark_bulb

The project involves creating a linux device driver and corresponding user program on the Raspberry Pi 3B+:
* The user program outputs the number of times (0-9) that the infrared sensor was triggered to a 7 segment cathode led display.
* The kernel driver acts as an interface between ioctl used by userspace and gpio pins. Memory location of gpio pins is abstracted from the user program.
* Restart the counter to 1 in the user program once there is an overflow 

This project uses the C programming language.
