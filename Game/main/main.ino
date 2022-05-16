#include <WebServer.h>
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <Update.h>
WebServer server(80);
#include "updateIndex.h";
// Statik IP adres
IPAddress local_IP(192, 168, 1, 56);
// Gateway IP adres
IPAddress gateway(192, 168, 1, 1);
//Subnet
IPAddress subnet(255, 255, 0, 0);

constexpr char WIFI_SSID[] = "FiberHGW_ZTXF6D_2.4GHz";
constexpr char WIFI_PASS[] = "tgzUCAdkAt";


#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

int8_t screenYSize = 240;
int8_t screenXSize = 240;

int8_t screenDYSize = 20;
int8_t screenDXSize = 20;

int8_t SquareYSize = screenYSize / screenDYSize;
int8_t SquareXSize = screenXSize / screenDXSize;


uint32_t last;
int y=0;
boolean direction=1;


void setup()
{
    Serial.begin(9600);
    tft.init();
    tft.setRotation(2);
    tft.fillScreen(TFT_BLACK);

        Serial.println("hello1");
//Burada üst kısımda belirlediğimiz statik ip ve gateway adreslerini ayarlıyoruz.
     if (!WiFi.config(local_IP,gateway,subnet)) {
    Serial.println("Statik ip ve gateway adres ayarlama başarısız oldu.");
    }

//Wifi bağlantısını başlatıyoruz.    
    WiFi.begin(WIFI_SSID, WIFI_PASS);
Serial.println("hello2");
    Serial.printf("Bağlanılıyor :  %s .", WIFI_SSID);
    while (WiFi.status() != WL_CONNECTED) { Serial.print("."); delay(200); }
    Serial.println(" Wifi'a Bağlandı");

    IPAddress ip = WiFi.localIP();

    Serial.printf("SSID: %s\n", WIFI_SSID);
    Serial.printf("Channel: %u\n", WiFi.channel());
    Serial.printf("IP: %u.%u.%u.%u\n", ip & 0xff, (ip >> 8) & 0xff, (ip >> 16) & 0xff, ip >> 24);

server.on("/serverIndex", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", serverIndex);
  });
  /*handling uploading firmware file */
  server.on("/update", HTTP_POST, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart();
  }, []() {
    HTTPUpload& upload = server.upload();
    if (upload.status == UPLOAD_FILE_START) {
      Serial.printf("Update: %s\n", upload.filename.c_str());
      if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { //start with max available size
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      /* flashing firmware to ESP*/
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_END) {
      if (Update.end(true)) { //true to set the size to the current progress
        Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
      } else {
        Update.printError(Serial);
      }
    }
  });

  
  server.begin();
}


float oldSeconds = 0;
float allSeconds = 0;

float konum = 0;
float speed = 80.0f;

void loop()
{
    server.handleClient();
    
    
    float allSeconds = (float)millis()/1000;
    float deltaSeconds = allSeconds - oldSeconds;

    Serial.println(deltaSeconds);
   if (millis() - last > 3000) {
    direction=!direction;
    last = millis();
   }
    
   if(direction==1){
      konum = konum + (speed * deltaSeconds);
     tft.fillRect(120, (int)konum, 25, 25, TFT_GREEN);
     tft.fillRect(120, (int)konum-25,25, 25,TFT_BLACK);      
      y=konum;
    }
  
   if(direction==0){
      konum = konum - (speed * deltaSeconds);
     tft.fillRect(120, (int)konum, 25, 25, TFT_GREEN);
     tft.fillRect(120, (int)konum+25,25, 25,TFT_BLACK);      
      y=konum;
    }

       oldSeconds = allSeconds;
}
