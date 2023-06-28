#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <U8g2.h>

U8G2_SH1106_128X64_NONAME_F_HW_I2C display(U8G2_R0, U8X8_PIN_NONE);

const char* ssid = "WIFI_NAME";                                  // Replace the next variables with your SSID/Password combination
const char* password = "WIFI_PASSWORD";

const char* mqtt_server = "mqtt.eclipseprojects.io";

WiFiClient espClient;
PubSubClient client(espClient);

String teamName = "";                                       // Replace this with your team name
char[] topic = "ecg_project";

void reconnect() {
  while (!client.connected()) {                             // Loop until we're reconnected
    Serial.println("Attempting MQTT connection...");
    
                                                            // Attempt to connect
    if (client.connect(MQTT_CLIENT_NAME)) {
      Serial.println("Connected");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      delay(5000);                                          // Wait 5 seconds before retrying
    }
  }
}

void callback() {

}

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    pinMode(36, INPUT);
    Serial.print("Waiting for WiFi...");
    
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    
    Serial.println("");
    Serial.println("WiFi Connected");
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);  
}

int readings[64];
int currentReadingIndex = 0;

char finalMessage[20];

void loop() {
    if (!client.connected()) {
        reconnect();
    }

    int sensorReading = analogRead(36);
    readings[currentReadingIndex] = sensorReading;
    currentReadingIndex = (currentReadingIndex + 1) % 64;

    Serial.println(sensorReading);
    
    display.clearBuffer();
    display.setFont(u8g2_font_ncenB08_tr);
    display.setCursor(0, 10);
    display.print("ECG: ");
    display.print(sensorReading);

    int graphIndex = 0;

    for (int i = 0; i < 64; i+=2) {
        int yVal = map(readings[graphIndex], 0, 4095, 0, 64);         //Adjust the ranges according to the readings you get
        int yValNext = map(readings[graphIndex + 1], 0, 4095, 0, 64);
        display.drawLine(i, yVal, i+2, yValNext);
        graphIndex = (graphIndex + 1) % 64;
    }

    display.sendBuffer();

    String message = teamName + ":" + String(sensorReading);
    message.toCharArray(finalMessage, sizeof(finalMessage));
    client.publish(topic, finalMessage);

    delay(10);
    client.loop();
}
