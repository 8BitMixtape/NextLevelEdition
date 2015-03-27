NextLevelEdition
================

SMD 32U4 Massproduction Ready PCB that fits in Mixtape

How to install
================
Download Hardware Cores from Sparkfun:
https://learn.sparkfun.com/tutorials/pro-micro--fio-v3-hookup-guide/installing-mac--linux

For Linux udev rules needs to be changed:
http://forum.arduino.cc/index.php?topic=217910.0

/etc/udev/rules.d/70-persistent-net.rules

 # 8Bit Mixtape NextLevel Shit
 
ATTRS{idVendor}=="1b4f", ATTRS{idProduct}=="f100", ENV{ID_MM_DEVICE_IGNORE}="1"

ATTRS{idVendor}=="1b4f", ATTRS{idProduct}=="f101", ENV{ID_MM_DEVICE_IGNORE}="1"


Troubleshooting
================

If the serial port doesn't appear, see above.

Strange blinking: Did you attach the LiPo battery?

Bricked the board? if you choose the wrong board and upload this might happen. solder on the ISP plug and burn the bootloader. the files is in the core.

for linux:
avrdude -P /dev/ttyACM0 -b 19200 -c avrisp -p m32u4 -v -e -U flash:w:Caterina-fio.hex:i


Pins:
================

2 x Analog Input
----------------
A0 ( you can also only write 0) -> D18

A1 ( you can also only write 1) -> D19

2 x Digital Input / Buttons
---------------------------
D2 (2)

D3 (3)

Sound Output
------------
D9 (9) also connected to LED2

LEDs
----
D13 (13)

the middle i don't know. maybe charge state?

RX (0)

TX (1)

Timers
============

To change the prescaler of the timer connected to Pin9 (sound output)

TCCR1B = TCCR0B & 0b11111001; //no timer pre-scaler, fast PWM

