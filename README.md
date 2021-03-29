# FreestyleIoT_Project

For this project, i ve chosen to upgrade my existing IoT house >> https://www.youtube.com/watch?v=xoJDLW5kjLk and make it really internet of things by monitoring sensor outputs locally and via the BLYNK app >> https://blynk.io/ and control actuators locally and via BLYNK.

Link to the kitlist >> https://docs.google.com/spreadsheets/d/1GlvLmVtN7IZRM3OurWxvNwD4gjMKiJFMoon5G-sc7mI/edit?usp=sharing

The full Schematic can be found in this repository.

If you have a 3D printer and want to print your own house, you can find the STL files in this repository.
The STL files are still the IoT house version 1, i will update these files in the near future to have a cleaner finish.

i recommend a 0.2 layer height for the bigger parts and 0.1 for the smaller detail, no rafts, skirts, supports needed.

All ESP32 code can be found in this repository as well.


Steps
_____________________________

1) Start by building the project following the schematics, You can also have a look at the Photos and screenshots (BLYNK app) 
in this repository and the demonstration video >> https://www.youtube.com/watch?v=XRs4ygz1CqU
2) Open you Arduino IDE >> https://www.arduino.cc/en/software and first install the necessary board managers (ESP32) if not yet installed, follow the instructions on this page if Windows >> https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/  and this page if MacOS or Linux  https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-mac-and-linux-instructions/
3) Install following libraries from following links. In github, click on the Green "Code" button and then "Download zip". No need to unzip the file
You can then install these like follows >> In Arduino IDE, go to Sketch > Include Library > Add . ZIP library and select the library you’ve just downloaded.
Wire.h >> https://github.com/espressif/arduino-esp32 (This is a package af several neede libraries)
Adafruit_Sensor.h >> https://github.com/adafruit/Adafruit_Sensor
Adafruit_BME280.h >> https://github.com/adafruit/Adafruit_BME280_Library
WiFi.h >> https://github.com/espressif/arduino-esp32 (This is a package af several neede libraries)


