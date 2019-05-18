# Arduino Marine Manager
Embedded application, running on an Arduino and using a LCD display, to help with maintenance on a marine fish tank

# Basic Usage
Once built and deployed this software will allow:
* The (hard coded) configuration of various chores that need to be performed, along with how often they should be done
* The (hard coded) configuration of various water parameters that need to be monitors, along with how often they should be done, and the ranges that these values can fall into
* The software will maintain and display a "todo" list, arranging chores and parameters in time order based on priority, letting the user know what things they should be doing next
* Users can regsiter when they perform a chore, and this will be logged
* Users can regsiter when they take a measurement, and enter the value, and this will be logged
* Graphs can be displayed that display the frequency of performing chores
* Graphs can be displayed that display the values over time of the different measurements
* Users can display a summary of all known water parameters
* All live data is perdiodically save to an SD Card, with file backups made "just in case"
* User input is performed using the LCD's touchscreen interface

# Hardware
This project is developed for an Arduino Mega 256

Plugged into this is a Kuman 3.5 Inch Touch Screen LCD for Arduino UNO R3 MEGA 2560 with SD Card Socket SC3A-1
As this LCD is for an Arduino UNO, I connected the Uno SPI pins to the Mega ones by soldering on jumper wires.

# Platform
This project was developed within the Windows 10 environment

# Software Development
As the Arduino IDE is limited, this project is developed using Visual Studio Code
On top of that PlatformIO was added as an extension
The Arduino IDE still needs to be installed to gain access to the default libraries
Other libraries are stored within this repo
