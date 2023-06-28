int PULSE_FILTER_THRESHOLD = 1600;   // Adjust this number according to your pulse sensor readings

void setup() {
    Serial.begin(115200);
    pinMode(36, INPUT);             // Connect the pulse sensor to pin 36 (VP on the ESP32)
}

void loop() {
    int reading = analogRead(36);
    if (reading > PULSE_FILTER_THRESHOLD) {
        Serial.println(reading);
    } else {
        Serial.println(PULSE_FILTER_THRESHOLD-500);
    }
    delay(10);
}