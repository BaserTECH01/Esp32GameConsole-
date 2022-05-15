#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

void setup()
{
    tft.init();
    tft.fillScreen(TFT_BLACK);
    tft.setRotation(2);
    tft.fillRect(50, 50, 25, 25, TFT_GREEN);
}

void loop()
{

}
