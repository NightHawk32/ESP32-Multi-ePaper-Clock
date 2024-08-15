#include <lvgl.h>
#include <GxEPD2_BW.h>
#include "board.h"
#include "GxEPD2_display_selection_new_style.h"
#include <U8g2_for_Adafruit_GFX.h>

U8G2_FOR_ADAFRUIT_GFX u8g2Fonts;

const char HelloWorld[] = "Hello World!";
const char one[] = "Hello World!";

void setup()
{
    delay(500);
    Serial.begin(115200); /* prepare for possible serial debug */

    Serial.println("Starting ....");
    delay(1000);
	
    display1.init(115200, true, 2, false); // USE THIS for Waveshare boards with "clever" reset circuit, 2ms reset pulse
    display2.init(115200, true, 2, false);
    display3.init(115200, true, 2, false);
    display4.init(115200, true, 2, false);

    display1.setRotation(0);
    u8g2Fonts.begin(display1);
    if (display1.pages() > 1)
    {
        delay(100);
        Serial.print("pages = "); Serial.print(display1.pages()); Serial.print(" page height = "); Serial.println(display1.pageHeight());
        delay(1000);
    }
    volatile uint16_t bg = GxEPD_WHITE;
    volatile uint16_t fg = GxEPD_BLACK;
    u8g2Fonts.setFontMode(1);                 // use u8g2 transparent mode (this is default)
    u8g2Fonts.setFontDirection(0);            // left to right (this is default)
    u8g2Fonts.setForegroundColor(fg);         // apply Adafruit GFX color
    u8g2Fonts.setBackgroundColor(bg);         // apply Adafruit GFX color
    u8g2Fonts.setFont(u8g2_font_logisoso92_tn);  // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall
    
    display1.firstPage();
    do
    {
        display1.fillScreen(bg);
        u8g2Fonts.setCursor(20, 200); // start writing at this position
        u8g2Fonts.print("1");
    }
    while (display1.nextPage());
    //Serial.println("helloWorld done");

    display1.hibernate();
	Serial.println("Setup done ....");
}

void loop()
{
    delay(500);
    //Serial.println("Loop ....");
}