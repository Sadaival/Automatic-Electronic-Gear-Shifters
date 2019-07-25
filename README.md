# Automatic-Electronic-Gear-Shifters

1.INTRODUCTION

The problem generally faced in automobiles with multiple power sources is addition of power in proper ratio for maximum output. Efficycle being a two-power source vehicle (battery and man power) required efficient transmission for both of them giving combined maximum output. 

The system will be fitted on efficycle and will independently control the gear ratios of motor and man power sprockets. The gear ratio will depend on the speed of the vehicle and vary to give maximum output.

2. CONCEPT AND TECHNICAL FEATURES

SPEED MEASURE

The speed is measured by a hall sensor fitted on the back of the wheel. 5 Magnets are placed at equal distances around the wheel, as soon as a magnet passes the hall sensor it is sensed by the hall sensor and a signal is sent to the microcontroller which then records the time difference between two consecutive signals to measure RPM and therefore speed.


JOYSTICK MODULE

A joystick is fitted on to the steering handle of the efficycle. The joystick allows the driver to have control of both the gears when in manual mode. The joystick can be moved in two perpendicular directions which correspondingly change the man power and motor power gears. Pressing the joystick inwards allows the transmission to shift to automatic mode wherein the gears are shifted according to the speed of the vehicle.


DISPLAY MODULE

The efficycle is fitted with a TFT LCD 8” Display screen. The screen is for driver’s assistance and displays both the gears of efficycle (man power and motor power). It also displays the speed of the efficycle. It also displays the mode of transmission (manual or automatic).



SERVO CONTROL

A servo is fitted on each derailleur of the gear. Whenever the servo gets a signal to change gear from the microcontroller, it shifts to a specific angle commanded by the microcontroller. Thereby moving the derailleur left or right. The derailleur therefore pulls the chain with it and shifts the gear.


MICROCONTROLLER

All the calculations and signals transmission are done by a microcontroller. The microcontroller used is an Arduino MEGA. The microcontroller calculates speed by taking the time difference between two signals received from the hall sensor. The microcontroller takes input from the joystick and tells its position thereby determining when the driver moved the joystick and in which direction to upshift or downshift one of the two gears. It also tells when the driver shifted from manual to automatic mode and thereby shifting modes of operation. It controls the servo and sends signals to change the angle of gear according to current position of servo. Constants such as the angle to rotate the servo and the speeds at which gear is changed are stored in the memory of microcontroller When in manual mode it changes the gears according to the signal received from joystick and when in automatic mode it changes the gear according to speed. It sends signal to the display module to display data for the driver.


3.CALCULATION AND ANALYSIS

CALCULATION OF SPEED
Diameter of wheel = 0.71 m
No. of magnets on wheel = 5
Time taken between crossing of magnets = t

Rpm = (12)/(t)/1000.00)

Speed = (3.14*0.71*rpm) *1000/(60*60)

For max power: rpm=rpm(max) / 2

4.  MASS PRODUCTION FEASIBILITY

The product when considered for mass production will cost an amount of INR 1500. Which is affordable for an average customer buying this product. The components required can be easily installed on every efficycle rolled out of the factory and will require minimal labour to install.

5. SCOPE AND APPLICATIONS

The application of this product is not only limited to efficycle, but can be used in all types of bicycles or vehicles which require efficient transmission like e-rikshaws.

