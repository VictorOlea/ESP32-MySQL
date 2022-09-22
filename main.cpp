#include <Arduino.h>
#include <WiFi.h>
#include <DHT.h>  

const char* ssid     = "*****"; // SSID
const char* password = "*****";  // Password
const char* host = "*****";   // Server IP
const int   port = 80;                // Server Port
const int   watchdog = 5000;          // Watchdog frequency
unsigned long previousMillis = millis(); 

#define DHTTYPE DHT11   // DHT 11

#define dht_dpin 15
DHT dht(dht_dpin, DHTTYPE); 

void setup(void)
{ 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  dht.begin();
  Serial.begin(9600);
  Serial.println("Humedad y Temperatura\n\n");
  delay(700);

}
void loop() {
    float h = dht.readHumidity();
    float t = dht.readTemperature();      
    Serial.print("Humedad = ");
    Serial.print(h);
    Serial.print("%  ");
    Serial.print("Temperatura = ");
    Serial.print(t); 
    Serial.print("°C  ");

    unsigned long currentMillis = millis();
    
  if ( currentMillis - previousMillis > watchdog ) {
    previousMillis = currentMillis;
    WiFiClient client;
  
    if (!client.connect(host, port)) {
      Serial.println("Fallo al conectar");
      return;
    }

    String url = "/TestESP32/connect.php?temp=";
    url += t;
    url += "&hum=";
    url += h;
    
    // Enviamos petición al servidor
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
      }
    }
  
    // Leemos la respuesta del servidor
    while(client.available()){
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
  }
  delay(800);
}