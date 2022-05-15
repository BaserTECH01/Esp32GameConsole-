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

int direction = 1;
double oldSeconds = 0;
double allSeconds = 0;

void loop()
{
    double allSeconds = (double)millis()/1000;
    double deltaSeconds = allSeconds - oldSeconds;

    Serial.println(deltaSeconds);
}
