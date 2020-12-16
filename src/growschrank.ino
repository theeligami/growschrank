#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <avr/sleep.h>
#include <DS3231.h>
#include <Wire.h>
#include <SPI.h>
#include <util/delay.h>

// Relais
#define RELAIS_1 2
#define RELAIS_2 3
#define RELAIS_3 4
#define RELAIS_4 5
#define RELAIS_5 6
#define RELAIS_6 7
#define RELAIS_7 8
#define RELAIS_8 9

// Rotary Encoder
#define SW  10
#define CLK  11
#define DT  12

// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

// DS3231
DS3231 Clock;
RTClib RTC;
char time_text[6];

// Rotary Encoder
volatile int counter = 0;
volatile int currentStateCLK = 0;
volatile int lastStateCLK = 0;
volatile int swPressed = 0;
volatile unsigned long lastSW = 0;

// Menu
String menu_item_0 = "..";	// up
String menu_item_1 = "Lampe ON/OFF Zeit";
String menu_item_2 = "Luftpumpe ON/OFF Zeit";
String menu_item_3 = "Uhrzeit";
uint8_t menu_item = 0;
uint8_t last_menu_item = 0;
uint8_t frame = 0;
uint8_t page = 0;
uint8_t lamp_on[2] = {0,0};
uint8_t lamp_off[2] = {0,0};
uint8_t pump_on[2] = {0,0};
uint8_t pump_off[2] = {0,0};
uint8_t time[2] = {0,0};

void setup()
{
  	// Start serial interface
	Serial.begin(9600);
  
  	// Start I2C Interface
  	Wire.begin();

  	// Set display
  	if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) // Address 0x3C for 128x32
  	{
    	Serial.println(("SSD1306 allocation failed"));
    	while(1);
  	}
  	display.clearDisplay();
  	display.setTextSize(1);
  	display.setTextColor(WHITE);
  	display.setCursor(0, 0);
  	display.println("Booting...");
  	display.display();
  	display.setTextSize(3);
  	
  	// Set clock to 24h
  	Clock.setClockMode(false);
	
	// Pin modes
	pinMode(CLK, INPUT_PULLUP);
  	pinMode(DT, INPUT_PULLUP);
  	pinMode(SW, INPUT_PULLUP);
  	pinMode(RELAIS_1, OUTPUT);
  	pinMode(RELAIS_2, OUTPUT);
  	pinMode(RELAIS_3, OUTPUT);
  	pinMode(RELAIS_4, OUTPUT);
  	pinMode(RELAIS_5, OUTPUT);
  	pinMode(RELAIS_6, OUTPUT);
  	pinMode(RELAIS_7, OUTPUT);
  	pinMode(RELAIS_8, OUTPUT);
  

  	// Read the initial state of CLK for rotary encoder
  	lastStateCLK = digitalRead(CLK);

	PCICR |= (1 << PCIE0);
	PCMSK0 |= ((1 << PCINT2) | (1 << PCINT3) | (1 << PCINT4));

	display.setTextSize(1);
}

void loop()
{
	sprintf(time_text, "%02d:%02d", RTC.now().hour(), RTC.now().minute());
	display.clearDisplay();
  	display.setCursor(0, 0);
	display.println(time_text);
	display.println(swPressed);
  	display.println(counter);
	display.display();
  	delay(100);
}

ISR(PCINT0_vect)
{
  	cli();
	if (!digitalRead(SW))
			swPressed = 1;
	else
	{
		// Read the current state of CLK
  		currentStateCLK = digitalRead(CLK);
  		// If last and current state of CLK are different, then pulse occurred
  		// React to only 1 state change to avoid double count
  		if (currentStateCLK != lastStateCLK  && currentStateCLK == 1)
  		{

    		// If the DT state is different than the CLK state then
    		// the encoder is rotating CCW so decrement
    		if (digitalRead(DT) != currentStateCLK)
      			counter --;
    		else
				// Encoder is rotating CW so increment
      			counter ++;
  		}
		// Remember last CLK state
		lastStateCLK = currentStateCLK;
	}
	_delay_us(100);
	sei();
}
