#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <TFT_eSPI.h>  // knihovna pro TFT displej

// Wi-Fi údaje
const char* ssid = "Petr_doma";
const char* password = "H3sloHesl0";

// URL pro vtipy
const String url = "https://v2.jokeapi.dev/joke/Programming";

TFT_eSPI tft = TFT_eSPI();  // instance displeje

unsigned long lastJokeMillis = 0;
const unsigned long interval = 20000;  // každých 20 sekund nový vtip

String getJoke() {
  HTTPClient http;
  WiFiClientSecure client;
  client.setInsecure(); // vypnout ověřování certifikátu

  http.begin(client, url);
  http.addHeader("User-Agent", "ESP8266");

  int httpCode = http.GET();
  if (httpCode <= 0) {
    Serial.print("HTTP error: ");
    Serial.println(http.errorToString(httpCode));
    http.end();
    return "<chyba při načítání>";
  }

  String result = http.getString();
  http.end();

  Serial.println("Odpověď ze serveru:");
  Serial.println(result);

  DynamicJsonDocument doc(4096);
  DeserializationError error = deserializeJson(doc, result);
  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return "<chyba JSON>";
  }

  String type = doc["type"].as<String>();
  String joke = doc["joke"] | "";
  String setup = doc["setup"] | "";
  String delivery = doc["delivery"] | "";

  return type == "single" ? joke : setup + "\n\n" + delivery;
}

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println("\nPřipojuji se k Wi-Fi...");

  WiFi.begin(ssid, password);
  unsigned long startAttemptTime = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
    delay(250);
    Serial.print(".");
  }
  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Wi-Fi připojeno!");
    Serial.print("IP adresa: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Nepodařilo se připojit k Wi-Fi!");
    while (true) delay(1000);
  }

  // Inicializace displeje
  tft.init();
  tft.setRotation(1);    // nastav orientaci (zkus 0-3 podle zapojení)
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);

  // Vykreslení prvního vtipu
  String joke = getJoke();
  Serial.println("Vtip:");
  Serial.println(joke);

  tft.setCursor(0, 0);
  tft.fillScreen(TFT_BLACK);
  tft.println(joke);

  lastJokeMillis = millis();
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastJokeMillis >= interval) {
    String joke = getJoke();
    Serial.println("Nový vtip:");
    Serial.println(joke);

    tft.fillScreen(TFT_BLACK);
    tft.setCursor(0, 0);
    tft.println(joke);

    lastJokeMillis = currentMillis;
  }

  delay(100);
}
