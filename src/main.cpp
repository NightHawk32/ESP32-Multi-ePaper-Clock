#include <GxEPD2_BW.h>
#include "board.h"
#include "bitmaps.h"
#include "GxEPD2_display_selection_new_style.h"
#include <U8g2_for_Adafruit_GFX.h>
#include "myWifi.h"
#include <WiFi.h>
#include <time.h>

const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 0;

TaskHandle_t updateDisplayTaskHandle = NULL;
SemaphoreHandle_t semDisplay = NULL;

struct tm timeinfo;

U8G2_FOR_ADAFRUIT_GFX u8g2Fonts1;
U8G2_FOR_ADAFRUIT_GFX u8g2Fonts2;
U8G2_FOR_ADAFRUIT_GFX u8g2Fonts3;
U8G2_FOR_ADAFRUIT_GFX u8g2Fonts4;

const char HelloWorld[] = "Hello World!";
const char one[] = "Hello World!";

void printLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

void scanNetworks() {
  Serial.println("Scan start");

  // WiFi.scanNetworks will return the number of networks found.
  int n = WiFi.scanNetworks();
  Serial.println("Scan done");
  if (n == 0) {
      Serial.println("no networks found");
  } else {
      Serial.print(n);
      Serial.println(" networks found");
      Serial.println("Nr | SSID                             | RSSI | CH | Encryption");
      for (int i = 0; i < n; ++i) {
          // Print SSID and RSSI for each network found
          Serial.printf("%2d",i + 1);
          Serial.print(" | ");
          Serial.printf("%-32.32s", WiFi.SSID(i).c_str());
          Serial.print(" | ");
          Serial.printf("%4ld", WiFi.RSSI(i));
          Serial.print(" | ");
          Serial.printf("%2ld", WiFi.channel(i));
          Serial.print(" | ");
          switch (WiFi.encryptionType(i))
          {
          case WIFI_AUTH_OPEN:
              Serial.print("open");
              break;
          case WIFI_AUTH_WEP:
              Serial.print("WEP");
              break;
          case WIFI_AUTH_WPA_PSK:
              Serial.print("WPA");
              break;
          case WIFI_AUTH_WPA2_PSK:
              Serial.print("WPA2");
              break;
          case WIFI_AUTH_WPA_WPA2_PSK:
              Serial.print("WPA+WPA2");
              break;
          case WIFI_AUTH_WPA2_ENTERPRISE:
              Serial.print("WPA2-EAP");
              break;
          case WIFI_AUTH_WPA3_PSK:
              Serial.print("WPA3");
              break;
          case WIFI_AUTH_WPA2_WPA3_PSK:
              Serial.print("WPA2+WPA3");
              break;
          case WIFI_AUTH_WAPI_PSK:
              Serial.print("WAPI");
              break;
          default:
              Serial.print("unknown");
          }
          Serial.println();
          delay(10);
      }
  }
  Serial.println("");

  // Delete the scan result to free memory for code below.
  WiFi.scanDelete();
}

void setup_wifi() {
  delay(10);
  WiFi.begin(MY_WIFI_SSID, MY_WIFI_PASSWORD);
  int counter = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if (++counter > 100) ESP.restart();
    Serial.print(".");
  }
  Serial.print("WiFi connected: ");
  Serial.println(MY_WIFI_SSID);
}

void updateDisplayTask(void *pvParameters){
  while(1){
        static int d1_up_cnt = 0;
        static int d2_up_cnt = 0;
        static int d3_up_cnt = 0;
        static int d4_up_cnt = 0;

        static int min_low_prev = 99;
        static int min_high_prev = 99;
        static int hr_low_prev = 99;
        static int hr_high_prev = 99;
    if(xSemaphoreTake(semDisplay,portMAX_DELAY)){

        int min_low = timeinfo.tm_min %10;
        int min_high = timeinfo.tm_min /10;
        int hr_low = timeinfo.tm_hour %10;
        int hr_high = timeinfo.tm_hour /10;

        if(min_low != min_low_prev){
            if(d4_up_cnt >= 10){
                display4.setFullWindow();
                d4_up_cnt = 0;
            }else{
                display4.setPartialWindow(0, 0, display4.width(), display4.height());
            }                
            display4.firstPage();
            do
            {
                display4.fillScreen(GxEPD_WHITE);
                display4.drawInvertedBitmap(0, 0, epd_bitmap_allArray[min_low], 128, 296, GxEPD_BLACK);
            }
            while (display4.nextPage());
            d4_up_cnt++;
        }

        if(min_high != min_high_prev){
            if(d3_up_cnt >= 10){
                display3.setFullWindow();
                d3_up_cnt = 0;
            }else{
                display3.setPartialWindow(0, 0, display3.width(), display3.height());
            }                
            display3.firstPage();
            do
            {
                display3.fillScreen(GxEPD_WHITE);
                display3.drawInvertedBitmap(0, 0, epd_bitmap_allArray[min_high], 128, 296, GxEPD_BLACK);
            }
            while (display3.nextPage());
            d3_up_cnt++;
        }

        if(hr_low != hr_low_prev){
            if(d2_up_cnt >= 10){
                display2.setFullWindow();
                d2_up_cnt = 0;
            }else{
                display2.setPartialWindow(0, 0, display2.width(), display2.height());
            }                
            display2.firstPage();
            do
            {
                display2.fillScreen(GxEPD_WHITE);
                display2.drawInvertedBitmap(0, 0, epd_bitmap_allArray[hr_low], 128, 296, GxEPD_BLACK);
            }
            while (display2.nextPage());
            d2_up_cnt++;
        }

        if(hr_high != hr_high_prev){
            if(d1_up_cnt >= 10){
                display1.setFullWindow();
                d1_up_cnt = 0;
            }else{
                display1.setPartialWindow(0, 0, display1.width(), display1.height());
            }                
            display1.firstPage();
            do
            {
                display1.fillScreen(GxEPD_WHITE);
                display1.drawInvertedBitmap(0, 0, epd_bitmap_allArray[hr_high], 128, 296, GxEPD_BLACK);
            }
            while (display1.nextPage());
            d1_up_cnt++;
        }

        display1.hibernate();
        display2.hibernate();
        display3.hibernate();
        display4.hibernate();

        min_low_prev = min_low;
        min_high_prev = min_high;
        hr_low_prev = hr_low;
        hr_high_prev = hr_high;        
    }
  }  
}

void setup()
{
    delay(500);
    Serial.begin(115200); /* prepare for possible serial debug */

    Serial.println("Starting ....");
    delay(1000);
	
    display1.init(0, true, 2, false); // USE THIS for Waveshare boards with "clever" reset circuit, 2ms reset pulse
    display2.init(0, true, 2, false);
    display3.init(0, true, 2, false);
    display4.init(0, true, 2, false);

    display1.setRotation(2);
    display2.setRotation(2);
    display3.setRotation(0);
    display4.setRotation(0);

    display1.hibernate();
    display2.hibernate();
    display3.hibernate();
    display4.hibernate();
	Serial.println("Setup done ....");
    configTzTime("CET-1CEST,M3.5.0,M10.5.0/3", NTP_SERVER);
    scanNetworks();
    setup_wifi();

    semDisplay = xSemaphoreCreateBinary();
    xTaskCreate(
        updateDisplayTask,     // Function name of the task
        "Update Display",  // Name of the task (e.g. for debugging)
        2048,       // Stack size (bytes)
        NULL,       // Parameter to pass
        1,          // Task priority
        &updateDisplayTaskHandle  // Assign task handle
    );
}

long nextUpdate = 0;


void loop()
{
    if(WiFi.status() != WL_CONNECTED){
        setup_wifi();
    }

    if(millis() > nextUpdate){    
        if(!getLocalTime(&timeinfo)){
            Serial.println("Failed to obtain time");
        }
        Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
        nextUpdate = millis() + (60-timeinfo.tm_sec)*1000;
        xSemaphoreGive(semDisplay);
  }
    
}