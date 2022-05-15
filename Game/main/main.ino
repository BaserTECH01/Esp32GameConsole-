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
float oldSeconds = 0;
float allSeconds = 0;

float konum = 0;
float speed = 12.0f;

void loop()
{
    tft.fillScreen(TFT_BLACK);
    
    float allSeconds = (float)millis()/1000;
    float deltaSeconds = allSeconds - oldSeconds;

    Serial.println(deltaSeconds);

    konum = konum + (speed * deltaSeconds);

    tft.fillRect(120, (int)konum, 25, 25, TFT_GREEN);

    oldSeconds = allSeconds;
}
