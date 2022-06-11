#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#define Relay1 D1
 
// Setup Wifi
const char *ssid     = "Hidden";
const char *password = "113333555555";

// set time to light on
const int onhour=9;
const int onmin=40;

// set time to light off
const int offhour=9;
const int offmin=47;

const long utcOffsetInSeconds = 25200; // get utc offset Indonesia location
 
// Set date to day
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
 
// Define NTP Client to get time from id.pool.ntp.org
WiFiUDP ntpUDP; // define ntp
NTPClient timeClient(ntpUDP, "id.pool.ntp.org", utcOffsetInSeconds);
 
void setup(){
  Serial.begin(115200);
  pinMode(Relay1, OUTPUT); // set relay on
 
  WiFi.begin(ssid, password); // init wifi ssid and password
 
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." ); // while connecting will print this
  }
 
  timeClient.begin(); // wifi ready to use
}
 
void loop() {
  timeClient.update();

  // get time now
  Serial.print(daysOfTheWeek[timeClient.getDay()]);
  Serial.print(", ");
  Serial.print(timeClient.getHours()); // separate by hour
  Serial.print(":");
  Serial.print(timeClient.getMinutes()); // separate by minutes
  Serial.print(":");
  Serial.println(timeClient.getSeconds()); // separate by second

  if((timeClient.getHours() >= onhour && timeClient.getMinutes() > onmin) 
      && (timeClient.getHours() <= offhour && timeClient.getMinutes() < offmin))
  {
    digitalWrite(Relay1, HIGH);
    Serial.println("Light ON");
  }
  else {
    digitalWrite(Relay1, LOW);
    Serial.println("Light OFF");
  }
 
  delay(1000);
}
