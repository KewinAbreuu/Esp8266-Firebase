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
// String sValue, sValue2, sValue3, sValue4, sValue5, sValue6, sValue7, sValue8, sValue9, sValue10, sValue11, sValue12, sValue13, sValue14, sValue15, sValue16;
const int pinos[] = {D0, D1, D2, D3, D4, D5, D6, D8};
const String caminhos[] = {"D1/L1", "D2/L1", "D3/L1", "D4/L1", "D5/L1", "D6/L1", "D7/L1", "D8/L1"};
String sValues[8];

bool signupOK = false;

//WHATSDOG
const unsigned long WDT_TIMEOUT = 30000; // Tempo limite do watchdog em milissegundos (30 segundos)
unsigned long previousMillis = 0;

void whatsDog() {
  unsigned long currentMillis = millis();
  
  // Verifica se o tempo atual menos o tempo anterior é maior que o tempo limite do watchdog
  if (currentMillis - previousMillis > WDT_TIMEOUT) {
    Serial.println("A placa travou. Reiniciando ESP8266...");
    ESP.restart(); // Reinicia o ESP8266
  }

  // Atualiza o tempo anterior
  previousMillis = currentMillis;
}
//WHATSDOG

void setup() {

  //WHATCHSDOG
  Serial.begin(115200);
  Serial.println("----------------------------------------");
  Serial.println("Esp Inicializado");
  pinMode(bot, INPUT);
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
  Serial.println("começo do loop");

  if (Firebase.ready() && signupOK) {
    controlarPinos();
  }
  whatsDog();
}


void controlarPinos() {
  for (int i = 0; i < 8; ++i) {
    if (Firebase.RTDB.getString(&fbdo, caminhos[i])) {
      if (fbdo.dataType() == "string") {
        sValues[i] = fbdo.stringData();
        int valor = sValues[i].toInt();
        digitalWrite(pinos[i], valor == 1 ? HIGH : LOW);
        Serial.print("PORTA D");
        Serial.print(i);
        Serial.println(valor == 1 ? " on" : " off");
      }
    } else {
      Serial.println(fbdo.errorReason());
    }
  }
}

