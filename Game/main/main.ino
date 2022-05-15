#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

int8_t screenYSize = 240;
int8_t screenXSize = 240;

int8_t screenDYSize = 20;
int8_t screenDXSize = 20;

int8_t SquareYSize = screenYSize / screenDYSize;
int8_t SquareXSize = screenXSize / screenDXSize;

void setup()
{
  Serial.begin(9600);
    tft.init();
    tft.setRotation(2);
    tft.fillScreen(TFT_BLACK);
}

void loop()
{
    unsigned long runMicros = millis();
    double allSeconds = (double)millis()/1000;

    Serial.println(allSeconds);
}
