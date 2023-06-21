/**************************************************************

Barebones Blynk Setup v1
Adafruit Huzzah ESP8266
Upload Speed : 921600

Badar Jahangir Kayani
9/7/17

**************************************************************/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

const char* ssid     = "CaseGuest";
const char* password = "";

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "327a5cb8f40b40fcba8dac14852bc022";

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, password);
}

void loop()
{
  Blynk.run();
}

