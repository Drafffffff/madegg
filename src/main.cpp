#include <DNSServer.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"
#include "FS.h"
#include "LITTLEFS.h"
#include "DFRobotDFPlayerMini.h"
#include <FastLED.h>
#define DATA_PIN 14
#define FPSerial Serial1
#define NUM_LEDS 12

DFRobotDFPlayerMini myDFPlayer;
CRGB leds[NUM_LEDS];
void printDetail(uint8_t type, int value);
DNSServer dnsServer;
AsyncWebServer server(80);
boolean ledStatus = 0;
boolean isToggleLed = 0;
int light;
int musicNum = 1;
void setup()
{
  pinMode(2, OUTPUT);
  pinMode(33, INPUT);
  digitalWrite(2, LOW);
  FPSerial.begin(9600, SERIAL_8N1, /*rx =*/16, /*tx =*/17);
  Serial.begin(115200);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  if (!myDFPlayer.begin(FPSerial, /*isACK = */ true, /*doReset = */ true))
  { // Use serial to communicate with mp3.
    Serial.println(F("Unable to begin"));
    while (true)
    {
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.volume(30); // Set volume value. From 0 to 30 f
  // your other setup stuff...
  WiFi.softAP("esp-captive");
  Serial.begin(115200);
  Serial.println("begin");
  dnsServer.start(53, "*", WiFi.softAPIP());
  LITTLEFS.begin();
  // server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER); // only when requested from AP
  // more handlers...
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(LITTLEFS, "/www/index.html", "text/html"); });
  // server.serveStatic("/", LITTLEFS, "/www/").setDefaultFile("index.html");
  server.on("/req", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              Serial.println("req");
              digitalWrite(2, ledStatus);
              // myDFPlayer.play(1); 
              ledStatus = !ledStatus;
              isToggleLed = 1;
              request->send(200, "text/plain", "OK"); });
  FastLED.setBrightness(50);
  server.begin();
}

void loop()
{
  dnsServer.processNextRequest();

  if (analogRead(32) > 100)
  {
    for (int j = 0; j < 200; j++)
    {
      for (int i = 0; i < NUM_LEDS; i++)
      {
        leds[i] = CRGB(j, ceil(j * 0.8), ceil(j * 0.2));
      }
      FastLED.show();
      delay(5);
    }
    delay(200);
    for (int j = 200; j > 0; j--)
    {
      for (int i = 0; i < NUM_LEDS; i++)
      {
        leds[i] = CRGB(j, ceil(j * 0.8), ceil(j * 0.2));
      }
      FastLED.show();
      delay(5);
    }
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB::Black;
    }
    FastLED.show();
  }

  if (isToggleLed)
  {

    for (int x = 0; x < 3; x++)
    {

      for (int j = 0; j < 200; j++)
      {
        for (int i = 0; i < NUM_LEDS; i++)
        {
          leds[i] = CRGB(j, ceil(j * 0.8), ceil(j * 0.2));
        }
        FastLED.show();
        delay(5);
      }
      delay(500);

      for (int j = 200; j > 0; j--)
      {
        for (int i = 0; i < NUM_LEDS; i++)
        {
          leds[i] = CRGB(j, ceil(j * 0.8), ceil(j * 0.2));
        }
        FastLED.show();
        delay(5);
      }
    }

    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB::Black;
    }
    FastLED.show();
    isToggleLed = 0;
    myDFPlayer.play(musicNum);
    musicNum++;
    if (musicNum > 3)
    {
      musicNum = 1;
    }
    for (int x = 0; x < 5; x++)
    {

      for (int j = 0; j < 200; j++)
      {
        for (int i = 0; i < NUM_LEDS; i++)
        {
          leds[i] = CRGB(j, ceil(j * 0.8), ceil(j * 0.2));
        }
        FastLED.show();
        delay(5);
      }
      delay(500);

      for (int j = 200; j > 0; j--)
      {
        for (int i = 0; i < NUM_LEDS; i++)
        {
          leds[i] = CRGB(j, ceil(j * 0.8), ceil(j * 0.2));
        }
        FastLED.show();
        delay(5);
      }
    } 
    isToggleLed = 0;
  }
}