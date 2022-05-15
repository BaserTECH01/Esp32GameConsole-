#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

void setup()
{
    tft.init();
    tft.fillSreen(TFT_BLACK);

    tft.fillRect(25, 25, 25, 25, TFT_GREEN);
}

void loop()
{

}