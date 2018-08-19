# WeTello
DJI Tello control for Arduino Wemos

## This code does not work yet!
it should, but it doesn't. I'm still looking in to why.

I'm using the Wemos D1 mini to act as a wireless bridge from serial to tello.
Ultimatly to control multiple Tello drones with very little hardware.

Using the Arduino serial monitor you can use these numeric commands.
1 takeoff.
2 land..
3 speed?
4 battery?
5 time?
6 clockwise 10 times
7 reconnect wifi
8 print wifi status

Tello SDK https://dl-cdn.ryzerobotics.com/downloads/tello/0228/Tello+SDK+Readme.pdf
Also included in this project is a script from ryzerobotics "Tello Python3 Control Demo" Tello3.py
This script works fine and controls the drone.

i have pointed this python script at a linux box and used 
 netcat -ulp 8889
to see what it sends, and it sends the same as my arduino code does but the Tello remains on earth :(

More info on the SDK can be found here https://www.ryzerobotics.com/tello/downloads
