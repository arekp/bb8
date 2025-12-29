/*
 * BB8_WiFi_Controller.ino
 * Kod dla płytki ESP32 ("Mózg")
 * ------------------------------------
 * Odpowiedzialność: Tworzenie Access Pointa Wi-Fi, uruchomienie serwera WWW z API.
 * Tłumaczy polecenia HTTP na proste, jednoliterowe komendy wysyłane przez port szeregowy (Serial2)
 * do Arduino, które steruje silnikami.
 * 
 * Używane biblioteki: WiFi, ESPAsyncWebServer, AsyncTCP
 */

#include <WiFi.h>
#include <ESPAsyncWebServer.h>

// Definicja portu szeregowego do komunikacji z Arduino
// Używamy Serial2, aby nie kolidował z monitorem szeregowym (Serial)
// GPIO 17 (TX2) -> podłącz do RX w Arduino
// GPIO 16 (RX2) -> podłącz do TX w Arduino
HardwareSerial& ArduinoSerial = Serial2;

// Konfiguracja sieci Wi-Fi (Access Point)
const char* ssid = "BB8-Control";
const char* password = "12345678";

// Tworzenie obiektu serwera na porcie 80
AsyncWebServer server(80);

void setup() {
  // Uruchomienie monitora szeregowego do debugowania
  Serial.begin(115200);

  // Uruchomienie portu szeregowego do komunikacji z Arduino
  ArduinoSerial.begin(9600, SERIAL_8N1, 16, 17); // RX, TX

  // Uruchomienie Access Pointa
  Serial.println("\nStarting Access Point...");
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // --- Definicja endpointów API ---
  // Każde żądanie wysyła odpowiedni znak do Arduino przez Serial2

  server.on("/move/forward", HTTP_GET, [](AsyncWebServerRequest *request){
    ArduinoSerial.write('F');
    request->send(200, "text/plain", "Command: Forward");
  });
  server.on("/move/backward", HTTP_GET, [](AsyncWebServerRequest *request){
    ArduinoSerial.write('B');
    request->send(200, "text/plain", "Command: Backward");
  });
  server.on("/move/left", HTTP_GET, [](AsyncWebServerRequest *request){
    ArduinoSerial.write('L');
    request->send(200, "text/plain", "Command: Left");
  });
  server.on("/move/right", HTTP_GET, [](AsyncWebServerRequest *request){
    ArduinoSerial.write('R');
    request->send(200, "text/plain", "Command: Right");
  });
  server.on("/move/stop", HTTP_GET, [](AsyncWebServerRequest *request){
    ArduinoSerial.write('S');
    request->send(200, "text/plain", "Command: Stop");
  });
  server.on("/move/fw-right", HTTP_GET, [](AsyncWebServerRequest *request){
    ArduinoSerial.write('I');
    request->send(200, "text/plain", "Command: Fwd-Right");
  });
  server.on("/move/fw-left", HTTP_GET, [](AsyncWebServerRequest *request){
    ArduinoSerial.write('G');
    request->send(200, "text/plain", "Command: Fwd-Left");
  });
  server.on("/move/bw-left", HTTP_GET, [](AsyncWebServerRequest *request){
    ArduinoSerial.write('J');
    request->send(200, "text/plain", "Command: Bwd-Left");
  });
  server.on("/move/bw-right", HTTP_GET, [](AsyncWebServerRequest *request){
    ArduinoSerial.write('H');
    request->send(200, "text/plain", "Command: Bwd-Right");
  });

  // Uruchomienie serwera
  server.begin();
  Serial.println("HTTP server started. Ready for commands.");
}

void loop() {
  // Pętla jest pusta, ponieważ serwer asynchroniczny i obsługa portu szeregowego działają w tle.
}
