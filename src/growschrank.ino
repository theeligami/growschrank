#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <avr/sleep.h>
#include <DS3231.h>
#include <Wire.h>
#include <SPI.h>
#include <util/delay.h>
#include <EEPROM.h>

// Relais
#define LAMP 2
#define PUMP 3
#define RELAIS_3 4
#define RELAIS_4 5
#define RELAIS_5 6
#define RELAIS_6 7
#define RELAIS_7 8
#define FAN 9

// Rotary Encoder
#define SW  10
#define CLK  11
#define DT  12

// EEPROM
#define	LAMP_ON_ADR		0
#define LAMP_OFF_ADR	16
#define PUMP_ON_ADR		32
#define PUMP_OFF_ADR	48
#define FAN_ON_ADR		64
#define FAN_OFF_ADR		72

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
String menuItem1 = "Clock";
String menuItem2 = "Lamp ON/OFF";
String menuItem3 = "Pump ON/OFF";
String menuItem4 = "Fan ON/OFF";
uint8_t menuItem = 0;
uint8_t subMenuItem = 0;
uint8_t timeItem = 0;
uint8_t frame = 0;
uint8_t page = 0;
uint8_t time[2] = {0,0};
uint8_t lampOn[2], lampOff[2];
uint8_t pumpOn[2], pumpOff[2];
uint8_t fanOn, fanOff;
boolean flag = false;

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
	
	// Get EEPROM values
	EEPROM.get(LAMP_ON_ADR, lampOn);
	EEPROM.get(LAMP_OFF_ADR, lampOff);
	EEPROM.get(PUMP_ON_ADR, pumpOn);
	EEPROM.get(PUMP_OFF_ADR, pumpOff);
	EEPROM.get(FAN_ON_ADR, fanOn);
	EEPROM.get(FAN_OFF_ADR, fanOff);

	// Pin modes
	pinMode(CLK, INPUT_PULLUP);
  	pinMode(DT, INPUT_PULLUP);
  	pinMode(SW, INPUT_PULLUP);
  	pinMode(LAMP, OUTPUT);
  	pinMode(PUMP, OUTPUT);
  	pinMode(RELAIS_3, OUTPUT);
  	pinMode(RELAIS_4, OUTPUT);
  	pinMode(RELAIS_5, OUTPUT);
  	pinMode(RELAIS_6, OUTPUT);
  	pinMode(RELAIS_7, OUTPUT);
  	pinMode(FAN, OUTPUT);
  

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
	checkTimer(lampOn, lampOff, LAMP);
	checkTimer(pumpOn, pumpOff, PUMP);
	_delay_ms(1);
}

// Draws the menu to the screen
void drawMenu()
{
	if (page==0)	// Main menu
		displayMainMenuPage();
	else if (page==1)	// Settings selection menu
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
	else if (page==2 && menuItem==1)	// Clock
		displayClockMenuPage(menuItem1, time);
	else if (page==2 && menuItem==2)	// Lamp time
	{
		if (!flag)
		{
			flag = true;
			EEPROM.get(LAMP_ON_ADR, lampOn);
			EEPROM.get(LAMP_OFF_ADR, lampOff);
		}
		displayTimerMenuPage(menuItem2, lampOn, lampOff);
	}
	else if (page==2 && menuItem==3)	// Pump time
	{
		if (!flag)
		{
			flag = true;
			EEPROM.get(PUMP_ON_ADR, pumpOn);
			EEPROM.get(PUMP_OFF_ADR, pumpOff);
		}
		displayTimerMenuPage(menuItem3, pumpOn, pumpOff);
	}
	else if (page==2 && menuItem==4)	// Fan controller
	{
		if (!flag)
		{
			flag = true;
			EEPROM.get(FAN_ON_ADR, fanOn);
			EEPROM.get(FAN_OFF_ADR, fanOff);
		}
		displayOnOffControllerMenuPage(menuItem4, fanOn, fanOff);
	}
}

// Handles encoder input
void readEncoder()
{
	if (up)		// Encoder turned UP
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
			else if (menuItem==4)
			{
				if (subMenuItem==0)
				{
					if (fanOn>71)
						--fanOn;
				}
				else
					if (fanOff>0)
						--fanOff;
			}
		}

	}
	else if (down)	// Encoder turned DOWN
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
			else if (menuItem==4)
			{
				if (subMenuItem==0)
				{
					if (fanOn<100)
						++fanOn;
				}
				else
					if (fanOff<70)
						++fanOff;
			}
		}
	}
	else if (swPressed)	// Encoder switch pressed
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
						if (menuItem==2)
						{
							EEPROM.put(LAMP_ON_ADR, lampOn);
							EEPROM.put(LAMP_OFF_ADR, lampOff);
						}
						else
						{
							EEPROM.put(PUMP_ON_ADR, pumpOn);
							EEPROM.put(PUMP_OFF_ADR, pumpOff);
						}
						timeItem = 0;
						subMenuItem = 0;
						page = 1;
						flag = false;
					}
				}
			}
			else if (menuItem==4)
			{
				if (subMenuItem==0)
					++subMenuItem;
				else 
				{
					EEPROM.put(FAN_ON_ADR, fanOn);
					EEPROM.put(FAN_OFF_ADR, fanOff);
					subMenuItem = 0;
					page = 1;
					flag = false;
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

	if (subMenuItem==0)	// On time
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
	else if (subMenuItem==1)	// Off time
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
	if (timeItem==0)	// Hour
	{
		display.setTextColor(BLACK, WHITE);
		display.print(timeToString(time[0]));

		display.setTextColor(WHITE, BLACK);
		display.print(":");
		display.print(timeToString(time[1]));
	}
	else	// Minute
	{
		display.setTextColor(WHITE, BLACK);
		display.print(timeToString(time[0]));
		display.print(":");

		display.setTextColor(BLACK, WHITE);
		display.print(timeToString(time[1]));
	}
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
	if (subMenuItem==0) // On condition
	{
		display.setTextColor(BLACK, WHITE);
		display.print("On:  ");
		display.println(onValue);
		
		display.setTextColor(WHITE, BLACK);
		display.print("Off: ");
		display.println(offValue);
	}
	else if (subMenuItem==1) // Off condition
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
	display.setTextSize(2);
	display.clearDisplay();
	display.setCursor(35, 0);
	display.print(timeToString(RTC.now().hour()));
	display.print(':');
	display.println((timeToString(RTC.now().minute())));

	display.display();
}

void checkTimer(uint8_t on[2], uint8_t off[2], uint8_t pin)
{
	if (on[0]==RTC.now().hour() && on[1]==RTC.now().minute())
		digitalWrite(pin, HIGH);
	else if (off[0]==RTC.now().hour() && off[1]==RTC.now().minute())
		digitalWrite(pin, LOW);
}

void checkOnOffController(uint8_t on, uint8_t off, uint8_t value, uint8_t pin)
{	
	if (value>=on)
		digitalWrite(pin, HIGH);
	else if (value<=off)
		digitalWrite(pin, LOW);
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
