#define OS_ESP32

#include <WiFiMulti.h>
#include <OneSignal.h>

// Replace with your own OneSignal App ID
#define OS_APP_ID "YOUR_ONESIGNAL_APP_ID_HERE"

// Run your app and put your own player ID here for testing
#define OS_USER_ID "YOUR_ONESIGNAL_USER_ID"

// Your wifi network name 
#define WIFI_SSID "example_wifi_network"

// Your wifi network password
#define WIFI_PASSPHRASE "example_wifi_passphrase"

OneSignal onesignal(OS_APP_ID);

WiFiMulti wifiMulti;

void setup() {
  Serial.begin(115200);
  
  Serial.println("Connecting to wifi");
  
  wifiMulti.addAP(WIFI_SSID, WIFI_PASSPHRASE);

  while (wifiMulti.run() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(500);
    Serial.println("Waiting for connection");
  }

  Serial.println("Connected to " + String(WIFI_SSID));

  // Build & send a push notification
  OSNotification notif;
  notif.contents = "Hello, World!";
  notif.headings = "Test Title";
  notif.url = "https://www.google.com";

  Serial.println("Built notification, building audience");
  
  OSAudience audience(OS_USER_ID);
  
  String result = onesignal.sendNotificationToAudience(notif, audience);
  
  Serial.println("Sent with result:");
  Serial.println(result);
}

void loop() {
  // No-op
}
