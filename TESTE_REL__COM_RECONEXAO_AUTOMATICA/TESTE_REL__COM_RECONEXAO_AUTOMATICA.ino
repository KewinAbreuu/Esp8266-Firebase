#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "TP-Link_49AE"
#define WIFI_PASSWORD "84478658"

// Insert Firebase project API Key
#define API_KEY "AIzaSyB8WpaHjzv2WLdM812retS2F5Dk0hSYgCM"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "appportaria-b0a1b-default-rtdb.firebaseio.com/" 

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

//some importent variables
String sValue, sValue2;
bool signupOK = false;

void setup() {
  Serial.begin(115200);
  pinMode(2,OUTPUT);
  pinMode(5,OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  }
  else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  //Verifica se o wifi ta conectado e tenta se reconectar
   while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Tentando se Reconectar ao Wifi");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  } Serial.print("Reconexão Realizada com sucesso");
 
  if (Firebase.ready() && signupOK ) {
    if (Firebase.RTDB.getString(&fbdo, "/L1")) {
      if (fbdo.dataType() == "string") {
        sValue = fbdo.stringData();
        int a = sValue.toInt();
        Serial.println(a);
        if (a == 1){
          digitalWrite(2,HIGH);
        }else{
          digitalWrite(2,LOW);
        }
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }
    
    if (Firebase.RTDB.getString(&fbdo, "/L1")) {
      if (fbdo.dataType() == "string") {
        sValue2 = fbdo.stringData();
        int b = sValue2.toInt();
        Serial.println(b);
        if (b == 1){
          digitalWrite(5,HIGH);
        }else{
          digitalWrite(5,LOW);
        }
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }
  
  }
}
