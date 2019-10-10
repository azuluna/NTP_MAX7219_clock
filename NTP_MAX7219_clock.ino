#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

const char *ssid     = "Wifi Belakang";
const char *password = "bismillahaja";

//MAX7219
const uint16_t WAIT_TIME = 1000;

//NTP
const long utcOffsetInSeconds = 25200;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

//MAX7219
#define MAX_DEVICES 4
#define CLK_PIN   14 // D5
#define DATA_PIN  13 // D7 
#define CS_PIN    15 // D8

//convert
int jam;
int menit;

// Hardware SPI connection
MD_Parola P = MD_Parola(CS_PIN, MAX_DEVICES);

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();
  P.begin();
}

void loop() {
  timeClient.update();
  jam = timeClient.getHours();
  menit = timeClient.getMinutes();
  if (jam > 12) {
    jam = jam - 12;
  }
  //  Serial.print(daysOfTheWeek[timeClient.getDay()]);
  //  Serial.print(", ");
  //  //  Serial.print(timeClient.getHours());
  //  Serial.print(jam);
  //  Serial.print(":");
  //  Serial.print(timeClient.getMinutes());
  //  Serial.print(":");
  //  Serial.println(timeClient.getSeconds());

  //Serial.println(timeClient.getFormattedTime());
  //  P.print(String(" ") + jam + String(":") + timeClient.getMinutes());
  if (jam < 10) {
    if (menit < 10) {
      P.print(String(" 0") + jam + String(":0") + menit);
    }
    else {
      P.print(String(" 0") + jam + String(":") + menit);
    }
  }
  else {
    if (menit < 10) {
      P.print(String(" ") + jam + String(":0") + menit);
    }
    else {
      P.print(String(" ") + jam + String(":") + menit);
    }
  }
  delay(1000);
}
