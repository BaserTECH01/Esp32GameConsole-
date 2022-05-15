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
    tft.init();
    tft.setRotation(2);
    tft.fillScreen(TFT_BLACK);
    tft.fillRect(25, 25, 25, 25, TFT_GREEN);
}

void loop()
{
    for (int8_t y = 0; y < screenDYSize; y++)
    {
        for(int8_t x = 0; x < screenDXSize; x++)
        {
            tft.fillRect(SquareYSize * y + 1, SquareXSize * x + 1, SquareYSize - 1, SquareXSize - 1, TFT_GREEN);
        }
    }

    delay(250);
}