# FreestyleIoT_Project

For this project, i ve chosen to upgrade my existing IoT house >> https://www.youtube.com/watch?v=xoJDLW5kjLk and make it really internet of things by monitoring sensor outputs locally and via the BLYNK app >> https://blynk.io/ and control actuators locally and via BLYNK.

Link to the kitlist >> https://docs.google.com/spreadsheets/d/1GlvLmVtN7IZRM3OurWxvNwD4gjMKiJFMoon5G-sc7mI/edit?usp=sharing
Link to the demo video of this project >> https://www.youtube.com/watch?v=XRs4ygz1CqU
Link to my PrusaPrinters page for 3D Printing files and instructions. https://www.prusaprinters.org/prints/61861-iot-hous-version-1

The full Schematic can be found in this repository.

Read the extra notes in the ESP32 codes for additional information about what the line of code does.

If you have a 3D printer and want to print your own house, you can find the STL files in this repository.
The STL files are still the IoT house version 1, i will update these files in the near future to have a cleaner finish.

i recommend a 0.2 layer height for the bigger parts and 0.1 for the smaller detail, no rafts, skirts, supports needed.

All ESP32 code i wrote for this project can be found in this repository as well.


Steps
_____________________________

1) Start by building the project following the schematics, You can also have a look at the Photos and screenshots (BLYNK app) 
in this repository and the demonstration video >> https://www.youtube.com/watch?v=XRs4ygz1CqU
2) Follow the instructions to set up BLYNK here >> https://blynk.io/en/getting-started , however i recommend setting up your own BLYNK server on a Raspberry Pi 4B, when using the CLOUD based server, there are limitations on how many widgets you will be able to use. Follow these instructions >> https://github.com/blynkkk/blynk-server
3) Open you Arduino IDE >> https://www.arduino.cc/en/software and first install the necessary board managers (ESP32) if not yet installed, follow the instructions on this page if Windows >> https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/  and this page if MacOS or Linux  https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-mac-and-linux-instructions/
4) Install following libraries from following links. In github, click on the Green "Code" button and then "Download zip". No need to unzip the file
You can then install these like follows >> In Arduino IDE, go to Sketch > Include Library > Add . ZIP library and select the library you’ve just downloaded.
I recommend to fully restart Arduino IDE after installing all libraries !!!

Wire.h >> https://github.com/espressif/arduino-esp32 (This is a package af several neede libraries)
Adafruit_Sensor.h >> https://github.com/adafruit/Adafruit_Sensor
Adafruit_BME280.h >> https://github.com/adafruit/Adafruit_BME280_Library
WiFi.h >> https://github.com/espressif/arduino-esp32 (This is a package af several neede libraries)
WiFiClient.h >> https://github.com/espressif/arduino-esp32 (This is a package af several neede libraries)
BlynkSimpleEsp32.h >> https://github.com/blynkkk/blynk-library
Adafruit_SSD1306.h >> https://github.com/adafruit/Adafruit_SSD1306
Fonts/FreeSerif9pt7b.h >> https://learn.adafruit.com/adafruit-gfx-graphics-library/using-fonts
Adafruit_GFX.h >> https://github.com/adafruit/Adafruit-GFX-Library
Servo.h >> https://github.com/RoboticsBrno/ServoESP32
MFRC522.h >> https://github.com/miguelbalboa/rfid/archive/master.zip
SPI.h >> https://github.com/PaulStoffregen/SPI

5) Create your project in the BLYNK app. Because we use 2 x ESP32 for 1 project, we will need 2 Tokens to be generated by the app. Again, see the instructions on these sites for set this up >> https://blynk.io/en/getting-started and >> https://github.com/blynkkk/blynk-server when using your own local server.
6) Set up the BLYNK project on your Android or iPhone as follows, See BLYNK Screenshots folder in this repository.
7) In Arduino IDE, go to File >> Examples >> MFRC522 >> DumpInfo. This will open a sketch that will read your RFID Card(s) UID(s), write these down, you will need this info later. Upload this sketch to the ESP32 that has the MFRC522 RFID Card Reader/Writer connected to it.
8) Change following lines in "IoT_House_ESP32_BLYNK_ACCESS_CONTROL.ino" to get connected to your Wi-Fi access point, the correct BLYNK server and Token and program the right RFID UIDs for access to the House >>

// Own Blynk Server and port
char server[] = "BLYNK Server IP address"; // RPi4B    <<<<<
#define port 8080 // Default port

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "Put your BLYNK Token here";    <<<<<

/*
   Wi-Fi
*/
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Your SSID"; // Use your modems Wi-Fi    <<<<<
char pass[] = "Your Wi-Fi password";    <<<<<

if ((content.substring(1) == "C9 D1 82 A2") || (content.substring(1) == "47 E6 19 B2")) // Zet hier de UID(s) van de kaarten die je toegang wil verschaffen     <<<<<
    // In case of blue badge UID: C9 D1 82 A2 or blue badge UID: 47 E6 19 B2
  {
    Serial.println("\t >>> Your RFID tag is known");

    if (content.substring(1) == "C9 D1 82 A2") {    <<<<<
      // Blij gezicht + blije toon + bericht op Serial Monitor !!!
      Serial.print("You may enter, welcome Koen !!!");
      Serial.println();
      Blynk.notify("Koen has just entered the IoT House");
      welcome_OLED_Koen();
    }
    if (content.substring(1) == "47 E6 19 B2") {    <<<<<
      // Blij gezicht + blije toon + bericht op Serial Monitor !!!
      Serial.print("You may enter, welcome Vero !!!");
      Serial.println();
      Blynk.notify("Vero has just entered the IoT House");
      welcome_OLED_Vero();
    }

9) Change following lines in "IoT_House_ESP32_CENTRAL_HEATER_GAS_Detection_FINAL.ino" to get connected to your Wi-Fi access point, the correct BLYNK server and Token. >>

// Own Blynk Server and port
char server[] = "BLYNK Server IP address"; // RPi4B    <<<<<
#define port 8080 // Default port

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "Put your BLYNK Token here";    <<<<<

/*
   Wi-Fi
*/
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Your SSID"; // Use your modems Wi-Fi    <<<<<
char pass[] = "Your Wi-Fi password";    <<<<<

10) Now its time to upload the codes to the ESP32s. Upload "IoT_House_ESP32_BLYNK_ACCESS_CONTROL.ino" to the first ESP32 and "IoT_House_ESP32_CENTRAL_HEATER_GAS_Detection_FINAL.ino" to the second one. See this video for uploading code to the ESP32 using Arduino IDE, make sure that the needed drivers are installed for your COM port >> https://www.youtube.com/watch?v=G6l259vEt7k and https://www.youtube.com/watch?v=0XX6fwdxO9Q

11) If your wirring is correct, both codes got uploaded to the ESP32s without errors and your BLYNK got set-up correctly, it should operate like shown in the demo video.

Enjoy
