#include <Wire.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Adafruit_AHTX0.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ---------- WiFi + ThingSpeak ----------
const char* WIFI_NAME = "chitti 5G";
const char* WIFI_PASSWORD = "Mittu@2728";
const char* SERVER = "api.thingspeak.com";
String API_KEY = "WRXR8EO4RXYM7PNC";
unsigned long CHANNEL_ID = 3142125;

// ---------- Sensors & Display ----------
Adafruit_AHTX0 aht;
#define MQ_PIN 34
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ---------- Variables ----------
float temperature = 0, humidity = 0;
int gasValue = 0;
int aqi = 0;
String airStatus = "Good";
unsigned long lastUpload = 0;

// ---------- Setup ----------
void setup() {
  Serial.begin(9600);
  Wire.begin(21, 22);
  delay(1000);

  // --- Initialize AHT20 ---
  if (!aht.begin()) {
    Serial.println("❌ Could not find AHT20! Check wiring.");
    while (1);
  }
  Serial.println("✅ AHT20 initialized");

  pinMode(MQ_PIN, INPUT);

  // --- Initialize OLED ---
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("❌ SSD1306 allocation failed");
    while (1);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Air Quality Monitor");
  display.display();

  // --- Connect WiFi ---
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

// ---------- AQI Status ----------
String getAirStatus(int aqi) {
  if (aqi <= 50) return "Good";
  else if (aqi <= 100) return "Moderate";
  else if (aqi <= 150) return "Poor";
  else if (aqi <= 200) return "Unhealthy";
  else if (aqi <= 300) return "Very Unhealthy";
  else return "Hazardous";
}

// ---------- Loop ----------
void loop() {
  sensors_event_t humidityEvent, tempEvent;
  aht.getEvent(&humidityEvent, &tempEvent);

  temperature = tempEvent.temperature;
  humidity = humidityEvent.relative_humidity;
  gasValue = analogRead(MQ_PIN);

  // ---- AQI Calculation ----
  aqi = map(gasValue, 200, 2000, 0, 500);
  if (aqi < 0) aqi = 0;
  if (aqi > 500) aqi = 500;

  airStatus = getAirStatus(aqi);

  // ---- Serial Output ----
  Serial.println("---------");
  Serial.print("Temp: "); Serial.print(temperature); Serial.println(" °C");
  Serial.print("Humidity: "); Serial.print(humidity); Serial.println(" %");
  Serial.print("Gas Value: "); Serial.println(gasValue);
  Serial.print("AQI: "); Serial.print(aqi); Serial.print(" ("); Serial.print(airStatus); Serial.println(")");
  Serial.println("------------------------------");

  // ---- OLED Output ----
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Air Quality Monitor");
  display.setCursor(0, 15);
  display.print("Temp: "); display.print(temperature); display.println(" C");
  display.print("Hum:  "); display.print(humidity); display.println(" %");
  display.print("Gas:  "); display.println(gasValue);
  display.print("AQI:  "); display.println(aqi);
  display.print("Stat: "); display.println(airStatus);
  display.display();

  // ---- Upload to ThingSpeak (every 10s) ----
  if (millis() - lastUpload > 10000) {
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      String url = "http://" + String(SERVER) + "/update?api_key=" + API_KEY +
                   "&field1=" + String(temperature) +
                   "&field2=" + String(humidity) +
                   "&field3=" + String(gasValue) +
                   "&field4=" + String(aqi) +
                   "&field5=" + airStatus;
      http.begin(url);
      int code = http.GET();
      if (code > 0) Serial.println("✅ Data uploaded to ThingSpeak");
      else Serial.println("❌ Upload failed");
      http.end();
      lastUpload = millis();
    }
  }

  delay(2000); // refresh local display
}
