#include <GxEPD2_BW.h>
#include "board.h"
#include "bitmaps.h"
#include "GxEPD2_display_selection_new_style.h"
#include <U8g2_for_Adafruit_GFX.h>

U8G2_FOR_ADAFRUIT_GFX u8g2Fonts1;
U8G2_FOR_ADAFRUIT_GFX u8g2Fonts2;
U8G2_FOR_ADAFRUIT_GFX u8g2Fonts3;
U8G2_FOR_ADAFRUIT_GFX u8g2Fonts4;

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

    display1.setRotation(2);
    display2.setRotation(2);
    display3.setRotation(0);
    display4.setRotation(0);

    u8g2Fonts1.begin(display1);
    if (display1.pages() > 1)
    {
        delay(100);
        Serial.print("pages = "); Serial.print(display1.pages()); Serial.print(" page height = "); Serial.println(display1.pageHeight());
        delay(1000);
    }
    u8g2Fonts2.begin(display2);
    if (display2.pages() > 1)
    {
        delay(100);
        Serial.print("pages = "); Serial.print(display2.pages()); Serial.print(" page height = "); Serial.println(display2.pageHeight());
        delay(1000);
    }
    u8g2Fonts3.begin(display3);
    if (display3.pages() > 1)
    {
        delay(100);
        Serial.print("pages = "); Serial.print(display3.pages()); Serial.print(" page height = "); Serial.println(display3.pageHeight());
        delay(1000);
    }
    u8g2Fonts4.begin(display4);
    if (display4.pages() > 1)
    {
        delay(100);
        Serial.print("pages = "); Serial.print(display4.pages()); Serial.print(" page height = "); Serial.println(display4.pageHeight());
        delay(1000);
    }
    volatile uint16_t bg = GxEPD_WHITE;
    volatile uint16_t fg = GxEPD_BLACK;
    u8g2Fonts1.setFontMode(1);                 // use u8g2 transparent mode (this is default)
    u8g2Fonts1.setFontDirection(0);            // left to right (this is default)
    u8g2Fonts1.setForegroundColor(fg);         // apply Adafruit GFX color
    u8g2Fonts1.setBackgroundColor(bg);         // apply Adafruit GFX color
    u8g2Fonts1.setFont(u8g2_font_logisoso92_tn);  // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall
    u8g2Fonts2.setFontMode(1);                 // use u8g2 transparent mode (this is default)
    u8g2Fonts2.setFontDirection(0);            // left to right (this is default)
    u8g2Fonts2.setForegroundColor(fg);         // apply Adafruit GFX color
    u8g2Fonts2.setBackgroundColor(bg);         // apply Adafruit GFX color
    u8g2Fonts2.setFont(u8g2_font_logisoso92_tn);  // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall
    u8g2Fonts3.setFontMode(1);                 // use u8g2 transparent mode (this is default)
    u8g2Fonts3.setFontDirection(0);            // left to right (this is default)
    u8g2Fonts3.setForegroundColor(fg);         // apply Adafruit GFX color
    u8g2Fonts3.setBackgroundColor(bg);         // apply Adafruit GFX color
    u8g2Fonts3.setFont(u8g2_font_logisoso92_tn);  // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall
    u8g2Fonts4.setFontMode(1);                 // use u8g2 transparent mode (this is default)
    u8g2Fonts4.setFontDirection(0);            // left to right (this is default)
    u8g2Fonts4.setForegroundColor(fg);         // apply Adafruit GFX color
    u8g2Fonts4.setBackgroundColor(bg);         // apply Adafruit GFX color
    u8g2Fonts4.setFont(u8g2_font_logisoso92_tn);  // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall
    
    /*display1.firstPage();
    do
    {
        display1.fillScreen(bg);
        u8g2Fonts1.setCursor(20, 200); // start writing at this position
        u8g2Fonts1.print("1");
    }
    while (display1.nextPage());
    
    display2.firstPage();
    do
    {
        display2.fillScreen(bg);
        u8g2Fonts2.setCursor(20, 200); // start writing at this position
        u8g2Fonts2.print("2");
    }
    while (display2.nextPage());

    display3.firstPage();
    do
    {
        display3.fillScreen(bg);
        u8g2Fonts3.setCursor(20, 200); // start writing at this position
        u8g2Fonts3.print("3");
    }
    while (display3.nextPage());

    display4.firstPage();
    do
    {
        display4.fillScreen(bg);
        u8g2Fonts4.setCursor(20, 200); // start writing at this position
        u8g2Fonts4.print("4");
    }
    while (display4.nextPage());*/
    //Serial.println("helloWorld done");

    display1.hibernate();
    display2.hibernate();
    display3.hibernate();
    display4.hibernate();
	Serial.println("Setup done ....");

    display4.firstPage();
    do
    {
        display4.fillScreen(GxEPD_WHITE);
        display4.drawInvertedBitmap(0, 0, epd_bitmap_allArray[0], 128, 296, GxEPD_BLACK);
    }
    while (display4.nextPage());

    display4.setPartialWindow(0, 0, display4.width(), display4.height());
    //display.setFullWindow();

    for(int i = 1; i<10; i++){
        display4.firstPage();
        do
        {
            display4.fillScreen(GxEPD_WHITE);
            display4.drawInvertedBitmap(0, 0, epd_bitmap_allArray[i], 128, 296, GxEPD_BLACK);
        }
        while (display4.nextPage());
        delay(1000);
    }

    display1.firstPage();
    do
    {
        display1.fillScreen(GxEPD_WHITE);
        display1.drawInvertedBitmap(0, 0, epd_bitmap_allArray[1], 128, 296, GxEPD_BLACK);
    }
    while (display1.nextPage());

    display2.firstPage();
    do
    {
        display2.fillScreen(GxEPD_WHITE);
        display2.drawInvertedBitmap(0, 0, epd_bitmap_allArray[2], 128, 296, GxEPD_BLACK);
    }
    while (display2.nextPage());

    display3.firstPage();
    do
    {
        display3.fillScreen(GxEPD_WHITE);
        display3.drawInvertedBitmap(0, 0, epd_bitmap_allArray[3], 128, 296, GxEPD_BLACK);
    }
    while (display3.nextPage());

    display1.hibernate();
    display2.hibernate();
    display3.hibernate();
    display4.hibernate();
    delay(2000);
}

void loop()
{
    delay(500);
    //Serial.println("Loop ....");
    
}