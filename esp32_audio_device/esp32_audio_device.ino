// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
// #define BLYNK_TEMPLATE_ID "TMPLlh8o1jPo"
// #define BLYNK_DEVICE_NAME "Getting started"
// #define BLYNK_AUTH_TOKEN "57xQ3I8tMFX5tsqzAuleqJsI0xU2wfaA"
#define BLYNK_TEMPLATE_ID "TMPL2Gin2L4ml"
#define BLYNK_TEMPLATE_NAME "esp32 testing"
#define BLYNK_AUTH_TOKEN "bH0iyH4yTWFeGf962HuuvvKlvtIx4w6Y"
// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

//#include "HardwareSerial.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

const byte RXD2 = 26;  // Connects to module's RX
const byte TXD2 = 27;  // Connects to module's TX
const byte relay_pin = 25; //
uint16_t song_number = 0;
int song_counter = 0;
bool relayActivated = false;
uint8_t gas_sensor_one = 32;
uint8_t gas_sensor_two = 33;
// Your WiFi credentials.
// Set password to "" for open networks.
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Son";
char pass[] = "Hotspot112";

BlynkTimer timer;
//HardwareSerial dfSD(1);  // Use UART channel 1
SoftwareSerial softwareSerial(RXD2, TXD2);
DFRobotDFPlayerMini player;


const uint16_t triggerOffNumbers[] = {5};
const uint8_t countOffNumbers = sizeof(triggerOffNumbers) / sizeof(triggerOffNumbers[0]);

const uint16_t triggerOnNumbers[] = {1};
const uint8_t countOnNumbers = sizeof(triggerOnNumbers) / sizeof(triggerOnNumbers[0]);
int playerActive = 0;
BLYNK_WRITE(V0) {
  int pinValue = param.asInt();
  song_number = pinValue;
}
struct Command{
  int songNo;
  int songNoDuration;
  int songPartner;
  int songPartnerDuration;
  bool relayActive;
};

Command commands[] = {
  {5, 2010, 25, 2010, false},
  {1, 2010, 31, 3020, true},
};
void setup() {
  Serial.begin(115200);
  pinMode(relay_pin, OUTPUT);
  digitalWrite(relay_pin, LOW);
  Serial.println(song_number);
  //dfSD.begin(9600, SERIAL_8N1, RXD2, TXD2);  // 16,17
  softwareSerial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  delay(1000);
  if (player.begin(softwareSerial)) {
    Serial.println("OK");
    // Set volume to maximum (0 to 30).
    player.volume(30);  //30 is very loud
  } else {
    Serial.println("Connecting to DFPlayer Mini failed!");
    while (true);
  }
  
  // Debug console
  //Serial.begin(115200);


}

void loop() {
  Serial.println(song_number);
  Blynk.run();
  timer.run();
  mp3(); 
 
  // int potvalue = analogRead(36);
  // Blynk.virtualWrite(V1, potvalue);
}