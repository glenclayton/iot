#include <SPI.h>
#include <ESP8266WiFi.h>
#include <osapi.h>
#include <user_interface.h>
#include <ThingerWifi.h>
#define RELAY1 12
#define RELAY2 4
ThingerWifi thing("glen_c", "NodeMCU1", "###ThingerHaldle###");
os_timer_t myTimer;
os_timer_t myRelay1Timer;
os_timer_t myRelay2Timer;

void timerCallback(void *pArg)
{
  digitalWrite(13, LOW);
}


void relay1TimerCallback(void *pArg)
{
  digitalWrite(RELAY1, HIGH);
}
void relay2TimerCallback(void *pArg)
{
  digitalWrite(RELAY2, HIGH);
}

void setup() {
  pinMode(13, OUTPUT);
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY2, HIGH);
  digitalWrite(13, LOW);

  thing.add_wifi("#SSID", "#WEPKEY");
  thing["led"] << [](pson& in){
  digitalWrite(13, in ? HIGH : LOW);
  if (in) {
    os_timer_setfn(&myTimer,timerCallback,NULL);
    os_timer_arm(&myTimer, 5000, false);
  }
};
  thing["relay1"] << [](pson& in){
  digitalWrite(RELAY1, in ? LOW : HIGH);
  if (in) {
    os_timer_setfn(&myRelay1Timer,relay1TimerCallback,NULL);
    os_timer_arm(&myRelay1Timer, 1500, false);
  }
  };

  thing["relay2"] << [](pson& in){
  digitalWrite(RELAY2, in ? LOW : HIGH);
  if (in) {
    os_timer_setfn(&myRelay2Timer,relay2TimerCallback,NULL);
    os_timer_arm(&myRelay2Timer, 1500, false);
  }
};
}
