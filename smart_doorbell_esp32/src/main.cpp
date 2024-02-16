#define BLYNK_TEMPLATE_ID "TMPL2k8HJe88I"
#define BLYNK_TEMPLATE_NAME "smart doorbell esp32"
#define BLYNK_AUTH_TOKEN "lgtsuQQpTn1HzzwmvnaamfTjSeffdG_D"

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <time.h>
// put function declarations here:

// WiFi credentials
const char* ssid = "FABIA_3G_LINK_FIBRA";
const char* password = "gloria110xrecife365";

// Blynk authentication token

char auth[] = BLYNK_AUTH_TOKEN;
#define BUTTON_PIN 23
#define LED_PIN 2
// Pin connected to the button
const int touchPin = 2; // Change this to the pin connected to your button

// Variable to store the previous state of the button
int prevButtonState = LOW;
int campaign_on = 0;

void runCampaign() {
  Blynk.run();
  // Read the state of the button
  int buttonState = digitalRead(BUTTON_PIN);
  digitalWrite(LED_PIN, LOW);
  // Check if the button state has changed
    if (buttonState == HIGH) {
      // Send notification to Blynk app
      Blynk.logEvent("campainha", "Alguém está tocando a campainha!");
      Serial.println("Button pressed!");
      Serial.println(buttonState);
      digitalWrite(LED_PIN, HIGH);
      delay(1000);
    }
}

void scanWifi() {
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      Blynk.logEvent("wifi_info", "SSID: " + WiFi.SSID(i) + " RSSI: " + WiFi.RSSI(i));
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
      delay(10);
    }
  }
  Serial.println("");
}


void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, password);
  
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
}

unsigned long time_now = 0;
int period = 30000;
void loop() {
  Blynk.run();

  if(millis() >= time_now + period){
        time_now += period;
        scanWifi();
    }

  runCampaign();

  }
