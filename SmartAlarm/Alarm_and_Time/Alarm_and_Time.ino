/**************************************************************

Alarm and Time with Alarm Sensing
Adafruit Huzzah ESP8266
Upload Speed : 921600

Badar Jahangir Kayani
9/9/17

**************************************************************/

//Comment this out to save space
#define BLYNK_PRINT Serial    
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <TimeLib.h>
#include <WidgetRTC.h>

const char* ssid     = "CaseGuest";
const char* password = "";
char auth[] = "327a5cb8f40b40fcba8dac14852bc022";

WidgetLED led1(V1);
BlynkTimer timer;
WidgetRTC rtc;

int alarm1[10];
int rtctime[3];
boolean alarm = false;

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, password);
  //Sync time from Blynk Server every 60 minutes
  setSyncInterval(3600);
  timer.setInterval(60000L, clockupdate);
  led1.off();
}

void loop()
{
  Blynk.run();
  timer.run();
}

//Get alarm 1 details and store it to an array
BLYNK_WRITE(V0){
  TimeInputParam t(param);
  alarm1[0] = t.getStartHour();
  alarm1[1] = t.getStartMinute();
  for (int i = 2; i <= 8; i++) {
    if (t.isWeekdaySelected(i-1)) {
      alarm1[i]=1;   
    }
    else{
      alarm1[i]=0;
    }
  }
}

//Turn alarm on or off
BLYNK_WRITE(V2){
  alarm1[9] = param.asInt();
  if(alarm1[9]==1){
    led1.on();
  }
  else{
    led1.off();
  }
}

// Synchronize time on connection
BLYNK_CONNECTED() {
  rtc.begin();
}


void clockupdate()
{
  rtctime[0]=hour();
  rtctime[1]=minute();
  rtctime[2]=weekday(); 
  //Change date numbering on rtctime to match alarm1 array for easy comparison 
  if(rtctime[2]==1){
    rtctime[2]=7;
  }
  else{
    rtctime[2]=rtctime[2]-1;
  }
  rtctime[2]=rtctime[2]+1;

  //Check to see if alarm condition is met
  if(alarm1[9]==1 && alarm1[0]==rtctime[0] && alarm1[1]==rtctime[1] && alarm1[rtctime[2]]==1){
    Blynk.notify("Alarm Condition");
    alarm = true;
  }
}


