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

// Rotary Encoder
volatile int counter = 0;
volatile int currentStateCLK = 0;
volatile int lastStateCLK = 0;
volatile unsigned long lastSW = 0;
volatile boolean up = false, down = false;
volatile boolean swPressed = 0;

// Menu
String menuItem0 = "..";	// up
String menuItem1 = "Time";
String menuItem2 = "Lamp ON/OFF";
String menuItem3 = "Pump ON/OFF";
String menuItem4 = "Fan ON/OFF";
uint8_t menuItem = 0;
uint8_t subMenuItem = 0;
uint8_t timeItem = 0;
uint8_t frame = 0;
uint8_t page = 0;
uint8_t time[2] = {0, 0};
uint8_t lampOn[2] = {0,0};
uint8_t lampOff[2] = {0,0};
uint8_t pumpOn[2] = {0,0};
uint8_t pumpOff[2] = {0,0};
uint8_t fanOn = 70;
uint8_t fanOff = 50;

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
	drawMenu();
	readEncoder();
}

void drawMenu()
{
	if (page==0)
		displayMainMenuPage();
	else if (page==1)
	{
		display.setTextSize(1);
		display.clearDisplay();
		display.setTextColor(WHITE);
		display.setCursor(0, 0);
		display.print("Main Menu");
		display.drawFastHLine(0, 10, SCREEN_WIDTH, WHITE);
		
		if (menuItem==0 && frame==0)
		{
			displayMenuItem(menuItem0, 15, true);
			displayMenuItem(menuItem1, 25, false);
		}
		else if (menuItem==1 && frame==0)
		{
			displayMenuItem(menuItem0, 15, false);
			displayMenuItem(menuItem1, 25, true);
		}
		else if (menuItem==2 && frame==1)
		{
			displayMenuItem(menuItem1, 15, false);	
			displayMenuItem(menuItem2, 25, true);

		}
		else if (menuItem==3 && frame==2)
		{
			displayMenuItem(menuItem2, 15, false);
			displayMenuItem(menuItem3, 25, true);
		}
		else if (menuItem==4 && frame==3)
		{
			displayMenuItem(menuItem3, 15, false);
			displayMenuItem(menuItem4, 25, true);
		}
		display.display();
	}
	else if (page==2 && menuItem==1)
		displayClockMenuPage(menuItem1, time);
	else if (page==2 && menuItem==2)
		displayTimerMenuPage(menuItem2, lampOn, lampOff);
	else if (page==2 && menuItem==3)
		displayTimerMenuPage(menuItem3, pumpOn, pumpOff);
	else if (page==2 && menuItem==4)
		displayOnOffControllerMenuPage(menuItem4, fanOn, fanOff);
}

void readEncoder()
{
	if (up)
	{
		up = false;
		if (page==1)
		{
			if (menuItem==2 && frame==1)
				--frame;
			else if (menuItem==3 && frame==2)
				--frame;
			else if (menuItem==4 && frame==3)
				--frame;
			if (menuItem > 0)
				--menuItem;
		}
		else if (page==2)
		{
			if (menuItem==1)
			{
				if (timeItem==0)
				{
					if (time[0]>0)
						--time[0];
					else
						time[0] = 23;
				}
				else if (timeItem==1)
				{
					if (time[1]>0)
						--time[1];
					else
						time[1] = 59;
				}
			}
			else if (menuItem==2)
			{
				if (subMenuItem==0)
				{
					if (timeItem==0)
					{
						if (lampOn[0]>0)
							--lampOn[0];
						else
							lampOn[0] = 23;
					}
					else
					{
						if (lampOn[1]>0)
							--lampOn[1];
						else
							lampOn[1] = 59;
					}
				}
				else
				{
					if (timeItem==0)
					{
						if (lampOff[0]>0)
							--lampOff[0];
						else
							lampOff[0] = 23;
					}
					else
					{
						if (lampOff[1]>0)
							--lampOff[1];
						else
							lampOff[1] = 59;
					}
				}
			}
			else if (menuItem==3)
			{
				if (subMenuItem==0)
				{
					if (timeItem==0)
					{
						if (pumpOn[0]>0)
							--pumpOn[0];
						else
							pumpOn[0] = 23;
					}
					else
					{
						if (pumpOn[1]>0)
							--pumpOn[1];
						else
							pumpOn[1] = 59;
					}
				}
				else
				{
					if (timeItem==0)
					{
						if (pumpOff[0]>0)
							--pumpOff[0];
						else
							pumpOff[0] = 23;
					}
					else
					{
						if (pumpOff[1]>0)
							--pumpOff[1];
						else
							pumpOff[1] = 59;
					}
				}
			}
		}

	}
	else if (down)
	{
		down = false;
		if (page==1)
		{
			if (menuItem==1 && frame==0)
				++frame;
			else if (menuItem==2 && frame==1)
				++frame;
			else if (menuItem==3 && frame==2)
				++frame;
			if (menuItem < 4)
				++menuItem;
		}
		else if (page==2)
		{
			if (menuItem==1)
			{
				if (timeItem==0)
				{
					if (time[0]<23)
						++time[0];
					else
						time[0] = 0;
				}
				else if (timeItem==1)
				{
					if (time[1]<59)
						++time[1];
					else
						time[0] = 0;
				}
			}
			else if (menuItem==2)
			{
				if (subMenuItem==0)
				{
					if (timeItem==0)
					{
						if (lampOn[0]<23)
							++lampOn[0];
						else
							lampOn[0] = 0;
					}
					else
					{
						if (lampOn[1]<59)
							++lampOn[1];
						else
							lampOn[1] = 0;
					}
				}
				else
				{
					if (timeItem==0)
					{
						if (lampOff[0]<23)
							++lampOff[0];
						else
							lampOff[0] = 0;
					}
					else
					{
						if (lampOff[1]<59)
							++lampOff[1];
						else
							lampOff[1] = 0;
					}
				}
			}
			else if (menuItem==3)
			{
				if (subMenuItem==0)
				{
					if (timeItem==0)
					{
						if (pumpOn[0]<23)
							++pumpOn[0];
						else
							pumpOn[0] = 0;
					}
					else
					{
						if (pumpOn[1]<59)
							++pumpOn[1];
						else
							pumpOn[1] = 0;
					}
				}
				else
				{
					if (timeItem==0)
					{
						if (pumpOff[0]<23)
							++pumpOff[0];
						else
							pumpOff[0] = 0;
					}
					else
					{
						if (pumpOff[1]<59)
							++pumpOff[1];
						else
							pumpOff[1] = 0;
					}
				}
			}
		}
	}
	else if (swPressed)
	{
		swPressed = false;
		if (page==0)
			++page;
		else if (page==1)
			if (menuItem==0)
				--page;
			else
			{
				if (menuItem==1)
				{
					time[0] = RTC.now().hour();
					time[1] = RTC.now().minute();
				}
				++page;
			}
		else if (page==2)
		{
			if (menuItem==1)
			{
				if (timeItem==0)
					++timeItem;
				else
				{
					timeItem = 0;
					page = 1;
					Clock.setHour(time[0]);
					Clock.setMinute(time[1]);
				}
			}
			else if (menuItem==2 || menuItem==3)
			{
				if (subMenuItem==0)
				{
					if (timeItem==0)
						++timeItem;
					else if (timeItem==1)
					{
						timeItem = 0;
						++subMenuItem;
					}
				}
				else if (subMenuItem==1)
				{
					if (timeItem==0)
						++timeItem;
					else if (timeItem==1)
					{
						timeItem = 0;
						subMenuItem = 0;
						page = 1;
					}
				}
			}
		}
	}
}

void displayMenuItem(String item, uint8_t pos, boolean selected)
{
	if (selected)
		display.setTextColor(BLACK, WHITE);
	else
		display.setTextColor(WHITE, BLACK);
	display.setCursor(0, pos);
	display.print(">"+item);
//	display.display();
}

void displayTimerMenuPage(String menuItem, uint8_t onTime[2], uint8_t offTime[2])
{
	display.setTextSize(1);
	display.clearDisplay();
	display.setTextColor(WHITE);
	display.setCursor(0, 0);
	display.print(menuItem); display.drawFastHLine(0, 10, SCREEN_WIDTH, WHITE);
	display.setCursor(0, 15);

	if (subMenuItem==0)
	{
		display.setTextColor(WHITE, BLACK);
		display.print("On:  ");
		
		if (timeItem==0)
		{
			display.setTextColor(BLACK, WHITE);
			display.print(timeToString(onTime[0]));
			display.setTextColor(WHITE, BLACK);
			display.print(':');
			display.println(timeToString(onTime[1]));

		}
		else if (timeItem==1)
		{
			display.print(timeToString(onTime[0]));
			display.print(':');
			display.setTextColor(BLACK, WHITE);
			display.println(timeToString(onTime[1]));
		}
		display.setTextColor(WHITE, BLACK);
		display.print("Off: ");
		display.print(timeToString(offTime[0]));
		display.print(':');
		display.println(timeToString(offTime[1]));
	}
	else if (subMenuItem==1)
	{
		display.setTextColor(WHITE, BLACK);
		display.print("On:  ");
		display.print(timeToString(onTime[0]));
		display.print(':');
		display.println(timeToString(onTime[1]));
		display.print("Off: ");

		if (timeItem==0)
		{
			display.setTextColor(BLACK, WHITE);
			display.print(timeToString(offTime[0]));
			display.setTextColor(WHITE, BLACK);
			display.print(':');
			display.println(timeToString(offTime[1]));
		}
		else if (timeItem==1)
		{
			display.setTextColor(WHITE, BLACK);
			display.print(timeToString(offTime[0]));
			display.print(':');
			display.setTextColor(BLACK, WHITE);
			display.println(timeToString(offTime[1]));
		}
	}
	display.display();
}

void displayClockMenuPage(String menuItem, uint8_t time[2])
{
	display.setTextSize(1);
	display.clearDisplay();
	display.setTextColor(WHITE);
	display.setCursor(0, 0);
	display.print(menuItem);
	display.drawFastHLine(0, 10, SCREEN_WIDTH, WHITE);
	display.setTextSize(2);
	display.setCursor(0, 15);
	if (timeItem==0)
	{
		display.setTextColor(BLACK, WHITE);
		display.print(timeToString(time[0]));

		display.setTextColor(WHITE, BLACK);
		display.print(":");
		display.print(timeToString(time[1]));
	}
	else
	{
		display.setTextColor(WHITE, BLACK);
		display.print(timeToString(time[0]));
		display.print(":");

		display.setTextColor(BLACK, WHITE);
		display.print(timeToString(time[1]));
	}

//	display.print(timeToString(time));
	display.display();
}

void displayOnOffControllerMenuPage(String menuItem, uint8_t onValue, uint8_t offValue)
{
	display.setTextSize(1);
	display.clearDisplay();
	display.setTextColor(WHITE);
	display.setCursor(0, 0);
	display.print(menuItem);
	display.drawFastHLine(0, 10, SCREEN_WIDTH, WHITE);
	display.setCursor(0, 15);
	if (subMenuItem==0)
	{
		display.setTextColor(BLACK, WHITE);
		display.print("On:  ");
		display.println(onValue);
		
		display.setTextColor(WHITE, BLACK);
		display.print("Off: ");
		display.println(offValue);
	}
	else if (subMenuItem==1)
	{
		display.print("On:  ");
		display.println(onValue);
		
		display.setTextColor(BLACK, WHITE);
		display.print("Off: ");
		display.println(offValue);
	}
	display.display();
}

void displayMainMenuPage()
{
	display.setTextSize(1);
	display.clearDisplay();
	display.setCursor(0, 0);
	display.print(timeToString(RTC.now().hour()));
	display.print(':');
	display.println((timeToString(RTC.now().minute())));
	display.display();
}

const String timeToString(uint8_t time)
{
	static char string[2];
	sprintf(string, "%02d", time);
	return string;
}

ISR(PCINT0_vect)
{
  	cli();
	if (!digitalRead(SW))
		swPressed = true;
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
			{
				up = true;
				down = false;
			}
    		else	// Encoder is rotating CW so increment
			{
				//counter ++;
				up = false;
				down = true;
			}
  		}
		// Remember last CLK state
		lastStateCLK = currentStateCLK;
	}
	_delay_us(100);
	sei();
}
