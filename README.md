# WeTello
DJI Tello control for Arduino Wemos

### Code tested & working !  
I'm using the Wemos D1 mini to act as a wireless bridge from serial to tello.  
The goal with this project is to control multiple Tello drones with very little hardware.

Using the Arduino serial monitor you can use these numeric commands.

1 takeoff  
2 land  
3 speed?  
4 battery?  
5 time?  
6 rotate clockwise 360deg  
7 UP 20cm  
8 RIGHT 20cm  
9 DOWN 20cm  
0 LEFT 20cm  


Tello SDK https://dl-cdn.ryzerobotics.com/downloads/tello/0228/Tello+SDK+Readme.pdf  
Also included in this project is a script from ryzerobotics "Tello Python3 Control Demo" Tello3.py  
This script works fine and controls the drone.

i have pointed the Wemos & the python script at a linux box and used  
 netcat -ulp 8889  
to see what it sends, and it sends the same as my arduino code :)

More info on the SDK can be found here https://www.ryzerobotics.com/tello/downloads

