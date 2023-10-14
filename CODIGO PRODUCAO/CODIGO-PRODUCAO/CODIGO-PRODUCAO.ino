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


//WHATCHSDOG
#include <ESP.h>
//WHATCHSDOG


//WHATCHSDOG
#define bot D7
//WHATCHSDOG


#define D0 16
#define D1 5
#define D2 4
#define D3 0
#define D4 2
#define D5 14
#define D6 12
#define D8 15


//ALTERAR -------------------------------------------------------------------------------------------------------------------------------------------------
// Insert your network credentials
#define WIFI_SSID "TP-Link_49AE"
#define WIFI_PASSWORD "84478658"

// Insert Firebase project API Key
#define API_KEY "AIzaSyB8WpaHjzv2WLdM812retS2F5Dk0hSYgCM"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://appportaria-b0a1b-default-rtdb.firebaseio.com/" 
//ALTERAR ------------------------------------------------------------------------------------------------------------------------------------------------

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

//some importent variables
String sValue, sValue2, sValue3, sValue4, sValue5, sValue6, sValue7, sValue8, sValue9, sValue10, sValue11, sValue12, sValue13, sValue14, sValue15, sValue16;
bool signupOK = false;

//WHATSDOG
void WDT_(unsigned long Duration){

  ESP.wdtDisable();
  unsigned long prevTime=millis();
  while (millis()-prevTime<Duration) {
  ESP.wdtEnable(1000);
  } 
}
//WHATSDOG

void setup() {

  //WHATCHSDOG
  Serial.begin(115200);
  Serial.println("----------------------------------------");
  Serial.println("Esp Inicializado");
  pinMode(bot, INPUT);
  WDT_(500);
  //WHATCHSDOG
  
  Serial.begin(115200);
  pinMode(D0,OUTPUT);
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);
  pinMode(D5,OUTPUT);
  pinMode(D6,OUTPUT);
  pinMode(D8,OUTPUT);
 
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
  Serial.print("começo do loop");
  
  //D1
  if (Firebase.ready() && signupOK ) {
    if (Firebase.RTDB.getString(&fbdo, "D1/L1")) {
      if (fbdo.dataType() == "string") {
        sValue = fbdo.stringData();
        int a = sValue.toInt();
        Serial.println(a);
        if (a == 1){
          digitalWrite(D0,HIGH);
          Serial.println("PORTA D0 on");
        }else{
          digitalWrite(D0,LOW);
          Serial.println("PORTA D0 off");
        }
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }
    
    //D2
    if (Firebase.RTDB.getString(&fbdo, "D2/L1")) {
      if (fbdo.dataType() == "string") {
        sValue2 = fbdo.stringData();
        int b = sValue2.toInt();
        Serial.println(b);
        if (b == 1){
          digitalWrite(D1,HIGH);
          Serial.println("PORTA D1 on");
        }else{
          digitalWrite(D1,LOW);
          Serial.println("PORTA D1 off");
        }
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }

    //D3
    if (Firebase.RTDB.getString(&fbdo, "D3/L1")) {
      if (fbdo.dataType() == "string") {
        sValue3 = fbdo.stringData();
        int c = sValue3.toInt();
        Serial.println(c);
        if (c == 1){
          digitalWrite(D2,HIGH);
          Serial.println("PORTA D2 on");
        }else{
          digitalWrite(D2,LOW);
          Serial.println("PORTA D2 off");
        }
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }
    
    //D4
    if (Firebase.RTDB.getString(&fbdo, "D4/L1")) {
      if (fbdo.dataType() == "string") {
        sValue4 = fbdo.stringData();
        int d = sValue4.toInt();
        Serial.println(d);
        if (d == 1){
          digitalWrite(D3,HIGH);
          Serial.println("PORTA D3 on");
        }else{
          digitalWrite(D3,LOW);
          Serial.println("PORTA D3 off");
        }
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }

     //D5
    if (Firebase.RTDB.getString(&fbdo, "D5/L1")) {
      if (fbdo.dataType() == "string") {
        sValue5 = fbdo.stringData();
        int e = sValue5.toInt();
        Serial.println(e);
        if (e == 1){
          digitalWrite(D4,HIGH);
          Serial.println("PORTA D4 on");
        }else{
          digitalWrite(D4,LOW);
          Serial.println("PORTA D4 off");
        }
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }

    //D6
    if (Firebase.RTDB.getString(&fbdo, "D6/L1")) {
      if (fbdo.dataType() == "string") {
        sValue6 = fbdo.stringData();
        int f = sValue6.toInt();
        Serial.println(f);
        if (f == 1){
          digitalWrite(D5,HIGH);
          Serial.println("PORTA D5 on");
        }else{
          digitalWrite(D5,LOW);
          Serial.println("PORTA D5 off");
        }
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }

   //D7
      if (Firebase.RTDB.getString(&fbdo, "D7/L1")) {
        if (fbdo.dataType() == "string") {
          sValue7 = fbdo.stringData();
          int g = sValue7.toInt();
          Serial.println(g);
          if (g == 1){
            digitalWrite(D6,HIGH);
            Serial.println("PORTA D6 on");
          }else{
            digitalWrite(D6,LOW);
            Serial.println("PORTA D6 off");
          }
        }
      }
      else {
        Serial.println(fbdo.errorReason());
      }

      //D8
      if (Firebase.RTDB.getString(&fbdo, "D8/L1")) {
        if (fbdo.dataType() == "string") {
          sValue8 = fbdo.stringData();
          int h = sValue8.toInt();
          Serial.println(h);
          if (h == 1){
            digitalWrite(D8,HIGH);
            Serial.println("PORTA D8 on");
          }else{
            digitalWrite(D8,LOW);
            Serial.println("PORTA D8 off");
          }
        }
      }
      else {
        Serial.println(fbdo.errorReason());
      }


   
  }
    
}
