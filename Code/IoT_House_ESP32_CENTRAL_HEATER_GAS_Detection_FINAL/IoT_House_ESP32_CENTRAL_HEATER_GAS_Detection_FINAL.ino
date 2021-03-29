/*
   Evaluatie Week 5: een op afstand bedienbare IoT centrale verwarmingsregelaar:
   Gebruik een digitale temperatuursensor BME280.
   Geef de waarde weer op je telefoon.
   Creeer een thermometer wijzerplaat instelling op je telefoon.
   Als de temperatuur op de locatie op afstand onder deze vooraf ingestelde waarde komt,
   moet een LED aangaan (het verwarmingssysteem) en dit moet op je telefoon worden weergegeven.
*/

#define BLYNK_PRINT Serial

#include <Wire.h> // Library for I2C Communication
#include <Adafruit_Sensor.h> // Unified Adafruit Sensor abstraction layer Library
#include <Adafruit_BME280.h> // Library for BME280 Sensor
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h> // Library for BLYNK
#include <Adafruit_SSD1306.h> // Library for OLED
#include <Fonts/FreeSerif9pt7b.h> // Library for Fonts / OLED

// OLED 128x64 Screen
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Initialize the OLED screen
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// BITMAP Koen_LEGO start-up screen
static const uint8_t image_data_KoenLego2[1024] = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xf0, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xbf, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0x3f, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0x3f, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0x3e, 0x7e, 0x7b, 0x3f, 0xff, 0xff,
  0xff, 0xfe, 0x03, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf2, 0x78, 0x18, 0x38, 0x1f, 0xff, 0xff,
  0xff, 0xff, 0xf3, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x71, 0x99, 0x98, 0x9f, 0xff, 0xff,
  0xff, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x73, 0x99, 0x99, 0x9f, 0xff, 0xff,
  0xff, 0xff, 0xd7, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf2, 0x73, 0x90, 0x19, 0x9f, 0xff, 0xff,
  0xff, 0xff, 0x97, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0x33, 0x91, 0xf9, 0x9f, 0xff, 0xff,
  0xff, 0xff, 0x87, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0x13, 0x99, 0xf9, 0x9f, 0xff, 0xff,
  0xff, 0xff, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0x98, 0x18, 0x19, 0x9f, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0x88, 0x3c, 0x19, 0x9f, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xef, 0xff, 0xf0, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xf8, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xf7, 0xc1, 0xff, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xf8, 0x00, 0x1f, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xfc, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xfe, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0x00, 0x07, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xe7, 0xff,
  0xf0, 0x00, 0x8e, 0x00, 0xff, 0xff, 0xff, 0xfc, 0xf9, 0xff, 0xf9, 0xff, 0xff, 0xff, 0xe7, 0xff,
  0x80, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xc3, 0xfc, 0xf9, 0xff, 0xf9, 0xff, 0xff, 0xff, 0xe7, 0xff,
  0x03, 0x00, 0x00, 0x00, 0x7f, 0xfe, 0x03, 0xfe, 0x73, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xe7, 0xff,
  0x00, 0x00, 0x00, 0x00, 0x3f, 0xf0, 0x03, 0xfe, 0x73, 0x0e, 0x18, 0x3c, 0x3c, 0x3c, 0x66, 0x7f,
  0x00, 0x00, 0x00, 0x00, 0x0f, 0xe0, 0x01, 0xfe, 0x72, 0x06, 0x18, 0x18, 0x18, 0x18, 0x24, 0x7f,
  0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x01, 0xfe, 0x26, 0x66, 0x39, 0x99, 0x9b, 0x91, 0xe4, 0xff,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x01, 0xff, 0x26, 0x06, 0x7b, 0x98, 0x10, 0x13, 0xe1, 0xff,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0x26, 0x06, 0x7b, 0x90, 0x10, 0x13, 0xe1, 0xff,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0xff, 0x06, 0x7e, 0x79, 0x99, 0xf3, 0xf3, 0xe4, 0xff,
  0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 0xff, 0x8e, 0x7e, 0x79, 0x99, 0xf9, 0xf1, 0x24, 0x7f,
  0x00, 0x00, 0x00, 0x18, 0x03, 0xc0, 0x00, 0xff, 0x8f, 0x06, 0x70, 0x18, 0x18, 0x18, 0x26, 0x7f,
  0x00, 0x00, 0x00, 0x20, 0x01, 0xc6, 0x00, 0x7f, 0x9f, 0x8e, 0x7a, 0x7e, 0x3c, 0x3c, 0x67, 0x7f,
  0x20, 0x00, 0x00, 0x28, 0x01, 0xc6, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x60, 0x00, 0x00, 0x00, 0x00, 0x60, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xe3, 0x00, 0x40, 0x00, 0x00, 0xe0, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xf3, 0x00, 0x00, 0x00, 0x0b, 0x10, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xf0, 0x00, 0x00, 0x00, 0x0c, 0x10, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xf8, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xfc, 0x10, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xe0, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xfb, 0xc0, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xf8, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xe0, 0x80, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xc1, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x82, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x04, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

// Push buttons
#define up_Button 2 // Controls the temp in the upward direction
#define down_Button 4 // Controls the temp in the downward direction
int upVal; // Status of Up-Button
int downVal; // Status of Down-Button
String msg = "Down-button state is ";
String msg2 = "  Up-Button state is: ";
int dt = 100; // Delay time, only when pressing a button

// Configure start-up temp
float setTemp = 20.00;

// Define LEDs
#define blue_LED 27
#define green_LED 26
#define red_LED 25

// Define Fan
#define fan 17

// Define MQ-2 Gas Detector
#define GasDetector 36
// MQ-2 GasSensor threshold value for alarm, value between 0 and 4095 (12bits)
// value will easely pass this threshold if gas is detected.
int sensorTresh = 2000;
// To avoid that BLYNK will send a notification every 5 seconds (default)
unsigned long old_millis = 0;
int no_Alarm = 60000; // 60 seconds

// Define Active Buzzer
#define buzzer 32

// Own Blynk Server and port
char server[] = "192.168.10.122"; // RPi4B
#define port 8080 // Default port

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "********";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "********"; // Use the Orange modem Wi-Fi
char pass[] = "********";

// Create an object "bme" for I2C communication
Adafruit_BME280 bme;

// Functions to read and store temperature, pressure, altitude and humidity
// This code is telling the ESP32 that every time Blynk app sends a _READ request on a Virtual Pin,
// the ESP32 will read the sensor on that Virtual Pin and then write the sensor reading back to Blynk app.

BLYNK_READ(V1) // on Virtual Pin 1
{
  // Read temperature minus correction
  float temperature = (bme.readTemperature()) - 4.0;
  Blynk.virtualWrite(V1, temperature); // Send to Blynk
}

// This function will be called every time Temp. Slider Widget
// in Blynk app writes values to the Virtual Pin V2
BLYNK_WRITE(V2)
{
  // assigning incoming value from pin V2 to a float variable
  setTemp = param.asFloat();;
  // process received value
}

// Virtueele LEDs in BLYNK
WidgetLED vRedLED(V3); //virtual pin 3
WidgetLED vGreenLED(V4); //virtual pin 4
WidgetLED vBlueLED(V5); //virtual pin 5

BLYNK_READ(V6) // on Virtual Pin 6
{
  // Read the MQ-2 Sensor value
  int gasValBLYNK = analogRead(GasDetector);
  Blynk.virtualWrite(V6, gasValBLYNK); // Send to Blynk
}

void setup() {

  // Start the Serial Monitor @ 115200 Baud rate
  Serial.begin(115200);
  delay(10);

  // Set the push-buttons as INPUT (Pull-UP in hardware)
  pinMode(up_Button, INPUT);
  pinMode(down_Button, INPUT);

  // Set LEDs as OUTPUT
  pinMode(blue_LED, OUTPUT);
  pinMode(green_LED, OUTPUT);
  pinMode(red_LED, OUTPUT);
  
  // Set Fan as OUTPUT
  pinMode(fan, OUTPUT);

  // Set MQ-2 Gas Detector as INPUT
  pinMode(GasDetector, INPUT);

  // Set buzzer as OUTPUT
  pinMode(buzzer, OUTPUT);

  // Because the OLED and the BME280 have different addresses, 
  // we can use the same I2C SDA and SCL lines without any problem.
  // The OLED display address is 0x3C and the BME280 address is 0x76.
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  delay(2000); // Pause for 2 seconds

  // Clear the buffer.
  display.clearDisplay();

  // Draw Start-up screen bitmap on the screen
  // const tImage KoenLego2 = { image_data_KoenLego2, 128, 64, 8 }; >> info from bitmap (LCD Image Converter)
  display.drawBitmap(0, 0, image_data_KoenLego2, 128, 64, 1);
  display.display();

  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  // Initialize the BLYNK Client
  Blynk.begin(auth, ssid, pass, server, port);

  // We initialize the BME280 sensor with the default 0x76 address.
  bool status = bme.begin(0x76);
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
}

void loop() {

  upVal = digitalRead(up_Button);
  downVal = digitalRead(down_Button);
  // Serial.print(msg + downVal);
  // Serial.println(msg2 + upVal);

  if (upVal == 1 && downVal == 0) { // When pressing the Up-Button
    setTemp += 0.50;
    delay(dt); // Delay time, only when pressing the button
    if (setTemp > 30.00) {
      setTemp = 30;
    }
  }
  if (upVal == 0 && downVal == 1) { // When pressing the Down-Button
    setTemp -= 0.50;
    delay(dt); // Delay time, only when pressing the button
    if (setTemp < 0.00) {
      setTemp = 0.00;
    }
  }

  // Control hardware LED and BLYNK Virtual LED
  // Central Heating will turn on if setTemp is lower than actual temp.
  // Cooler will turn on if setTemp is higher than actual temp.
  // Measured temp may differ 0,5°C from "setTemp"
  // Read temperature minus temperature correction & +/- 0.5°C
  float temp_high = bme.readTemperature() - 4.0 + 0.5;
  float temp_low = bme.readTemperature() - 4.0 - 0.5;

  
  // Heater On
  if (setTemp > temp_high) {
    digitalWrite(red_LED, HIGH), digitalWrite(green_LED, LOW), digitalWrite(blue_LED, LOW);
    vRedLED.on(), vGreenLED.off(), vBlueLED.off();
    digitalWrite(fan, LOW);
  }
  // Goldilocks Zone
  if ((setTemp > temp_low && setTemp < temp_high) || (setTemp == temp_low) || (setTemp == temp_high)) {
    digitalWrite(red_LED, LOW), digitalWrite(green_LED, HIGH), digitalWrite(blue_LED, LOW);
    vRedLED.off(), vGreenLED.on(), vBlueLED.off();
    digitalWrite(fan, LOW);
  }
  // Cooler On
  if (setTemp < temp_low) {
    digitalWrite(red_LED, LOW), digitalWrite(green_LED, LOW), digitalWrite(blue_LED, HIGH);
    vRedLED.off(), vGreenLED.off(), vBlueLED.on();
    digitalWrite(fan, HIGH);
  }

  // Read the MQ-2 Sensor value
  int gasVal = analogRead(GasDetector);
  // Serial.print("MQ-2 Sensor value: ");
  // Serial.println(gasVal);
  // Check if the MQ-2 sensor threshold value was reached.

  unsigned long new_millis = millis();
  
  if (gasVal >= sensorTresh){
    Serial.println(" >> threshold exeeded");
    digitalWrite(buzzer, HIGH);
    // Only send a BLYNK notification if more then 60 seconds have passed
    // since last notification
    if ((new_millis - old_millis) > no_Alarm) {
      Blynk.notify("GAS DETECTED !!!!!!!");
      old_millis = new_millis;
    }
  }
  else{
    // Serial.println(" >> below treshold"); 
    digitalWrite(buzzer, LOW);
  }
  

  // Clear the OLED buffer
  display.clearDisplay();
  // Set the text color to white, 
  // failing to set this wil give you a black screen
  display.setTextColor(WHITE);
  display.invertDisplay(false);
  // display current temperature in °C
  display.setFont();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Current Temperature:");
  display.setTextSize(2);
  display.setCursor(0, 10);
  // Read temperature minus correction
  display.print(String((bme.readTemperature()) - 4.0));
  display.print(" ");
  display.setTextSize(1);
  display.cp437(true);
  display.write(167);
  display.setTextSize(2);
  display.print("C");
  // display set temperature in °C
  display.setTextSize(1);
  display.setCursor(0, 40);
  display.print("Set Temperature:");
  display.setTextSize(2);
  display.setCursor(0, 50);
  display.print(setTemp);
  display.print(" ");
  display.setTextSize(1);
  display.cp437(true);
  display.write(167);
  display.setTextSize(2);
  display.print("C");

  // "display.display()" is NOT necessary after every single drawing command,
  // you can batch up a bunch of drawing operations and then update the screen
  // all at once by calling "display.display()".
  display.display();

  // Run the Function to read and print temperature, pressure, altitude and humidity
  Blynk.run();
}
