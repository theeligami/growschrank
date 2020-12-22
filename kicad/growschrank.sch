EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "lun. 30 mars 2015"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 8950 1450 1    60   ~ 0
Vin
Text Label 9350 1450 1    60   ~ 0
IOREF
Text Label 8900 2500 0    60   ~ 0
A0
Text Label 8900 2600 0    60   ~ 0
A1
Text Label 8900 2700 0    60   ~ 0
A2
Text Label 8900 2800 0    60   ~ 0
A3
Text Label 8900 2900 0    60   ~ 0
A4(SDA)
Text Label 8900 3000 0    60   ~ 0
A5(SCL)
Text Label 10550 3000 0    60   ~ 0
0(Rx)
Text Label 10550 2800 0    60   ~ 0
2
Text Label 10550 2900 0    60   ~ 0
1(Tx)
Text Label 10550 2700 0    60   ~ 0
3(**)
Text Label 10550 2600 0    60   ~ 0
4
Text Label 10550 2500 0    60   ~ 0
5(**)
Text Label 10550 2400 0    60   ~ 0
6(**)
Text Label 10550 2300 0    60   ~ 0
7
Text Label 10550 2100 0    60   ~ 0
8
Text Label 10550 2000 0    60   ~ 0
9(**)
Text Label 10550 1900 0    60   ~ 0
10(**/SS)
Text Label 10550 1800 0    60   ~ 0
11(**/MOSI)
Text Label 10550 1700 0    60   ~ 0
12(MISO)
Text Label 10550 1600 0    60   ~ 0
13(SCK)
Text Label 10550 1400 0    60   ~ 0
AREF
NoConn ~ 9400 1600
Text Label 10550 1300 0    60   ~ 0
A4(SDA)
Text Label 10550 1200 0    60   ~ 0
A5(SCL)
Text Notes 10850 1000 0    60   ~ 0
Holes
Text Notes 8550 750  0    60   ~ 0
Shield for Arduino that uses\nthe same pin disposition\nlike "Uno" board Rev 3.
$Comp
L Connector_Generic:Conn_01x08 P1
U 1 1 56D70129
P 9600 1900
F 0 "P1" H 9600 2350 50  0000 C CNN
F 1 "Power" V 9700 1900 50  0000 C CNN
F 2 "Socket_Arduino_Uno:Socket_Strip_Arduino_1x08" V 9750 1900 20  0000 C CNN
F 3 "" H 9600 1900 50  0000 C CNN
	1    9600 1900
	1    0    0    -1  
$EndComp
Text Label 8650 1800 0    60   ~ 0
Reset
$Comp
L power:+3.3V #PWR01
U 1 1 56D70538
P 9150 1450
F 0 "#PWR01" H 9150 1300 50  0001 C CNN
F 1 "+3.3V" V 9150 1700 50  0000 C CNN
F 2 "" H 9150 1450 50  0000 C CNN
F 3 "" H 9150 1450 50  0000 C CNN
	1    9150 1450
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR02
U 1 1 56D707BB
P 9050 1350
F 0 "#PWR02" H 9050 1200 50  0001 C CNN
F 1 "+5V" V 9050 1550 50  0000 C CNN
F 2 "" H 9050 1350 50  0000 C CNN
F 3 "" H 9050 1350 50  0000 C CNN
	1    9050 1350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 56D70CC2
P 9300 3150
F 0 "#PWR03" H 9300 2900 50  0001 C CNN
F 1 "GND" H 9300 3000 50  0000 C CNN
F 2 "" H 9300 3150 50  0000 C CNN
F 3 "" H 9300 3150 50  0000 C CNN
	1    9300 3150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 56D70CFF
P 10300 3150
F 0 "#PWR04" H 10300 2900 50  0001 C CNN
F 1 "GND" H 10300 3000 50  0000 C CNN
F 2 "" H 10300 3150 50  0000 C CNN
F 3 "" H 10300 3150 50  0000 C CNN
	1    10300 3150
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x06 P2
U 1 1 56D70DD8
P 9600 2700
F 0 "P2" H 9600 2300 50  0000 C CNN
F 1 "Analog" V 9700 2700 50  0000 C CNN
F 2 "Socket_Arduino_Uno:Socket_Strip_Arduino_1x06" V 9750 2750 20  0000 C CNN
F 3 "" H 9600 2700 50  0000 C CNN
	1    9600 2700
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 P5
U 1 1 56D71177
P 10800 650
F 0 "P5" V 10900 650 50  0000 C CNN
F 1 "CONN_01X01" V 10900 650 50  0001 C CNN
F 2 "Socket_Arduino_Uno:Arduino_1pin" H 10721 724 20  0000 C CNN
F 3 "" H 10800 650 50  0000 C CNN
	1    10800 650 
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 P6
U 1 1 56D71274
P 10900 650
F 0 "P6" V 11000 650 50  0000 C CNN
F 1 "CONN_01X01" V 11000 650 50  0001 C CNN
F 2 "Socket_Arduino_Uno:Arduino_1pin" H 10900 650 20  0001 C CNN
F 3 "" H 10900 650 50  0000 C CNN
	1    10900 650 
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 P7
U 1 1 56D712A8
P 11000 650
F 0 "P7" V 11100 650 50  0000 C CNN
F 1 "CONN_01X01" V 11100 650 50  0001 C CNN
F 2 "Socket_Arduino_Uno:Arduino_1pin" V 11000 650 20  0001 C CNN
F 3 "" H 11000 650 50  0000 C CNN
	1    11000 650 
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 P8
U 1 1 56D712DB
P 11100 650
F 0 "P8" V 11200 650 50  0000 C CNN
F 1 "CONN_01X01" V 11200 650 50  0001 C CNN
F 2 "Socket_Arduino_Uno:Arduino_1pin" H 11024 572 20  0000 C CNN
F 3 "" H 11100 650 50  0000 C CNN
	1    11100 650 
	0    -1   -1   0   
$EndComp
NoConn ~ 10800 850 
NoConn ~ 10900 850 
NoConn ~ 11000 850 
NoConn ~ 11100 850 
$Comp
L Connector_Generic:Conn_01x08 P4
U 1 1 56D7164F
P 10000 2600
F 0 "P4" H 10000 2100 50  0000 C CNN
F 1 "Digital" V 10100 2600 50  0000 C CNN
F 2 "Socket_Arduino_Uno:Socket_Strip_Arduino_1x08" V 10150 2550 20  0000 C CNN
F 3 "" H 10000 2600 50  0000 C CNN
	1    10000 2600
	-1   0    0    -1  
$EndComp
Wire Notes Line
	8525 825  9925 825 
Wire Notes Line
	9925 825  9925 475 
Wire Wire Line
	9350 1450 9350 1700
Wire Wire Line
	9350 1700 9400 1700
Wire Wire Line
	9400 1900 9150 1900
Wire Wire Line
	9400 2000 9050 2000
Wire Wire Line
	9400 2300 8950 2300
Wire Wire Line
	9400 2100 9300 2100
Wire Wire Line
	9400 2200 9300 2200
Connection ~ 9300 2200
Wire Wire Line
	8950 2300 8950 1450
Wire Wire Line
	9050 2000 9050 1475
Wire Wire Line
	9150 1900 9150 1475
Wire Wire Line
	9400 2500 8900 2500
Wire Wire Line
	9400 2600 8900 2600
Wire Wire Line
	9400 2700 8900 2700
Wire Wire Line
	9400 2800 8900 2800
Wire Wire Line
	9400 2900 8900 2900
Wire Wire Line
	9400 3000 8900 3000
$Comp
L Connector_Generic:Conn_01x10 P3
U 1 1 56D721E0
P 10000 1600
F 0 "P3" H 10000 2150 50  0000 C CNN
F 1 "Digital" V 10100 1600 50  0000 C CNN
F 2 "Socket_Arduino_Uno:Socket_Strip_Arduino_1x10" V 10150 1600 20  0000 C CNN
F 3 "" H 10000 1600 50  0000 C CNN
	1    10000 1600
	-1   0    0    -1  
$EndComp
Wire Wire Line
	10200 2100 10550 2100
Wire Wire Line
	10200 2000 10550 2000
Wire Wire Line
	10200 1900 10550 1900
Wire Wire Line
	10200 1800 10550 1800
Wire Wire Line
	10200 1700 10550 1700
Wire Wire Line
	10200 1600 10550 1600
Wire Wire Line
	10200 1400 10550 1400
Wire Wire Line
	10200 1300 10550 1300
Wire Wire Line
	10200 1200 10550 1200
Wire Wire Line
	10200 3000 10550 3000
Wire Wire Line
	10200 2900 10550 2900
Wire Wire Line
	10200 2800 10550 2800
Wire Wire Line
	10200 2700 10550 2700
Wire Wire Line
	10200 2600 10550 2600
Wire Wire Line
	10200 2500 10550 2500
Wire Wire Line
	10200 2400 10550 2400
Wire Wire Line
	10200 2300 10550 2300
Wire Wire Line
	10200 1500 10300 1500
Wire Wire Line
	10300 1500 10300 3100
Wire Wire Line
	9300 2100 9300 2200
Wire Wire Line
	9300 2200 9300 3150
Wire Notes Line
	8500 500  8500 3450
Wire Notes Line
	8500 3450 11200 3450
Wire Wire Line
	9400 1800 8650 1800
Text Notes 9700 1600 0    60   ~ 0
1
Wire Notes Line
	11200 1000 10700 1000
Wire Notes Line
	10700 1000 10700 500 
$Comp
L Connector_Generic:Conn_01x04 J1
U 1 1 5F9AF856
P 750 950
F 0 "J1" H 830 942 50  0000 L CNN
F 1 "OLED" H 830 851 50  0000 L CNN
F 2 "Connector_JST:JST_PH_B4B-PH-K_1x04_P2.00mm_Vertical" H 750 950 50  0001 C CNN
F 3 "~" H 750 950 50  0001 C CNN
	1    750  950 
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x10 J5
U 1 1 5F9B09E4
P 2200 3350
F 0 "J5" H 2280 3342 50  0000 L CNN
F 1 "Relais" H 2280 3251 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x10_P2.54mm_Vertical" H 2200 3350 50  0001 C CNN
F 3 "~" H 2200 3350 50  0001 C CNN
	1    2200 3350
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR013
U 1 1 5F9B8181
P 2400 3750
F 0 "#PWR013" H 2400 3500 50  0001 C CNN
F 1 "GND" H 2405 3577 50  0000 C CNN
F 2 "" H 2400 3750 50  0001 C CNN
F 3 "" H 2400 3750 50  0001 C CNN
	1    2400 3750
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J2
U 1 1 5F9B8C72
P 750 2050
F 0 "J2" H 668 1625 50  0000 C CNN
F 1 "BME280" H 668 1716 50  0000 C CNN
F 2 "Connector_JST:JST_PH_B4B-PH-K_1x04_P2.00mm_Vertical" H 750 2050 50  0001 C CNN
F 3 "~" H 750 2050 50  0001 C CNN
	1    750  2050
	-1   0    0    1   
$EndComp
Wire Wire Line
	950  1850 1375 1850
$Comp
L power:GND #PWR09
U 1 1 5F9BB115
P 1375 1950
F 0 "#PWR09" H 1375 1700 50  0001 C CNN
F 1 "GND" H 1380 1777 50  0000 C CNN
F 2 "" H 1375 1950 50  0001 C CNN
F 3 "" H 1375 1950 50  0001 C CNN
	1    1375 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	1375 1950 950  1950
Text Label 950  2150 0    60   ~ 0
A4(SDA)
Text Label 950  2050 0    60   ~ 0
A5(SCL)
$Comp
L power:GND #PWR07
U 1 1 5F9C1792
P 1375 1050
F 0 "#PWR07" H 1375 800 50  0001 C CNN
F 1 "GND" H 1380 877 50  0000 C CNN
F 2 "" H 1375 1050 50  0001 C CNN
F 3 "" H 1375 1050 50  0001 C CNN
	1    1375 1050
	1    0    0    -1  
$EndComp
Text Label 950  750  0    60   ~ 0
A4(SDA)
Text Label 950  850  0    60   ~ 0
A5(SCL)
$Comp
L power:+5V #PWR06
U 1 1 5F9C1D9A
P 1375 950
F 0 "#PWR06" H 1375 800 50  0001 C CNN
F 1 "+5V" H 1390 1123 50  0000 C CNN
F 2 "" H 1375 950 50  0001 C CNN
F 3 "" H 1375 950 50  0001 C CNN
	1    1375 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1375 950  950  950 
Wire Wire Line
	1375 1050 950  1050
$Comp
L Connector_Generic:Conn_01x06 J4
U 1 1 5F9C58C1
P 2200 1950
F 0 "J4" H 2118 1425 50  0000 C CNN
F 1 "DS3231" H 2118 1516 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 2200 1950 50  0001 C CNN
F 3 "~" H 2200 1950 50  0001 C CNN
	1    2200 1950
	-1   0    0    1   
$EndComp
Text Label 2400 1950 0    60   ~ 0
A4(SDA)
Text Label 2400 1850 0    60   ~ 0
A5(SCL)
NoConn ~ 2400 1750
NoConn ~ 2400 1650
$Comp
L power:GND #PWR016
U 1 1 5F9C9EAA
P 2825 2150
F 0 "#PWR016" H 2825 1900 50  0001 C CNN
F 1 "GND" H 2830 1977 50  0000 C CNN
F 2 "" H 2825 2150 50  0001 C CNN
F 3 "" H 2825 2150 50  0001 C CNN
	1    2825 2150
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR015
U 1 1 5F9CA39D
P 2825 2050
F 0 "#PWR015" H 2825 1900 50  0001 C CNN
F 1 "+5V" H 2840 2223 50  0000 C CNN
F 2 "" H 2825 2050 50  0001 C CNN
F 3 "" H 2825 2050 50  0001 C CNN
	1    2825 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2825 2050 2400 2050
Wire Wire Line
	2825 2150 2400 2150
$Comp
L power:GND #PWR014
U 1 1 5F9D02DB
P 2250 1050
F 0 "#PWR014" H 2250 800 50  0001 C CNN
F 1 "GND" H 2255 877 50  0000 C CNN
F 2 "" H 2250 1050 50  0001 C CNN
F 3 "" H 2250 1050 50  0001 C CNN
	1    2250 1050
	1    0    0    -1  
$EndComp
Text Label 2400 3050 0    60   ~ 0
8
Text Label 2400 2950 0    60   ~ 0
9(**)
Text Label 2250 750  0    60   ~ 0
10(**/SS)
Wire Wire Line
	1450 3050 1400 3050
Wire Wire Line
	1450 2850 1450 3050
Wire Wire Line
	1400 2850 1450 2850
$Comp
L power:GND #PWR05
U 1 1 5F9E0CE3
P 900 3150
F 0 "#PWR05" H 900 2900 50  0001 C CNN
F 1 "GND" H 905 2977 50  0000 C CNN
F 2 "" H 900 3150 50  0001 C CNN
F 3 "" H 900 3150 50  0001 C CNN
	1    900  3150
	1    0    0    -1  
$EndComp
Text Label 900  2850 2    60   ~ 0
1(Tx)
Text Label 1400 3150 0    60   ~ 0
0(Rx)
NoConn ~ 1400 2950
NoConn ~ 900  3050
NoConn ~ 900  2950
$Comp
L power:+5V #PWR012
U 1 1 5F9B7BE1
P 2400 2850
F 0 "#PWR012" H 2400 2700 50  0001 C CNN
F 1 "+5V" H 2415 3023 50  0000 C CNN
F 2 "" H 2400 2850 50  0001 C CNN
F 3 "" H 2400 2850 50  0001 C CNN
	1    2400 2850
	1    0    0    -1  
$EndComp
Text Label 2400 3150 0    60   ~ 0
7
Text Label 2400 3250 0    60   ~ 0
6(**)
Text Label 2400 3350 0    60   ~ 0
5(**)
Text Label 2400 3450 0    60   ~ 0
4
Text Label 2400 3550 0    60   ~ 0
3(**)
Text Label 2400 3650 0    60   ~ 0
2
Text Label 2250 850  0    60   ~ 0
11(**/MOSI)
Text Label 2250 950  0    60   ~ 0
12(MISO)
Wire Notes Line
	475  1275 3250 1275
Wire Notes Line
	3250 475  3250 1275
Text Notes 475  1275 0    50   ~ 0
Interface
Wire Notes Line
	475  1200 825  1200
Wire Notes Line
	825  1200 825  1275
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5FA40B73
P 10300 3100
F 0 "#FLG0101" H 10300 3175 50  0001 C CNN
F 1 "PWR_FLAG" V 10300 3228 50  0000 L CNN
F 2 "" H 10300 3100 50  0001 C CNN
F 3 "~" H 10300 3100 50  0001 C CNN
	1    10300 3100
	0    1    1    0   
$EndComp
Connection ~ 10300 3100
Wire Wire Line
	10300 3100 10300 3150
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5FA426B9
P 8950 1025
F 0 "#FLG0102" H 8950 1100 50  0001 C CNN
F 1 "PWR_FLAG" H 8950 1198 50  0000 C CNN
F 2 "" H 8950 1025 50  0001 C CNN
F 3 "~" H 8950 1025 50  0001 C CNN
	1    8950 1025
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0103
U 1 1 5FA43BA4
P 9350 1025
F 0 "#FLG0103" H 9350 1100 50  0001 C CNN
F 1 "PWR_FLAG" H 9350 1198 50  0000 C CNN
F 2 "" H 9350 1025 50  0001 C CNN
F 3 "~" H 9350 1025 50  0001 C CNN
	1    9350 1025
	1    0    0    -1  
$EndComp
Wire Wire Line
	9350 1025 9225 1025
Wire Wire Line
	9225 1025 9225 1475
Wire Wire Line
	9225 1475 9150 1475
Connection ~ 9150 1475
Wire Wire Line
	9150 1475 9150 1450
Wire Wire Line
	9050 1475 9000 1475
Wire Wire Line
	9000 1475 9000 1025
Wire Wire Line
	9000 1025 8950 1025
Connection ~ 9050 1475
Wire Wire Line
	9050 1475 9050 1350
NoConn ~ 10200 1400
NoConn ~ 10200 1600
NoConn ~ 9400 2800
NoConn ~ 9400 2700
NoConn ~ 9400 2600
NoConn ~ 9400 2500
NoConn ~ 9400 2300
NoConn ~ 9400 1700
NoConn ~ 9400 1800
$Comp
L Connector_Generic:Conn_01x04 J6
U 1 1 5FA6978B
P 2050 950
F 0 "J6" H 1968 525 50  0000 C CNN
F 1 "Rotary_Encoder" H 1968 616 50  0000 C CNN
F 2 "Connector_JST:JST_PH_B4B-PH-K_1x04_P2.00mm_Vertical" H 2050 950 50  0001 C CNN
F 3 "~" H 2050 950 50  0001 C CNN
	1    2050 950 
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_02x04_Odd_Even J3
U 1 1 5FA7595F
P 1100 2950
F 0 "J3" H 1150 3267 50  0000 C CNN
F 1 "ESP8266" H 1150 3176 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x04_P2.54mm_Vertical" H 1100 2950 50  0001 C CNN
F 3 "~" H 1100 2950 50  0001 C CNN
	1    1100 2950
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0101
U 1 1 5FA87A25
P 1450 2850
F 0 "#PWR0101" H 1450 2700 50  0001 C CNN
F 1 "+3.3V" H 1465 3023 50  0000 C CNN
F 2 "" H 1450 2850 50  0001 C CNN
F 3 "" H 1450 2850 50  0001 C CNN
	1    1450 2850
	1    0    0    -1  
$EndComp
Connection ~ 1450 2850
$Comp
L power:+5V #PWR?
U 1 1 5FE26E9C
P 1375 1850
F 0 "#PWR?" H 1375 1700 50  0001 C CNN
F 1 "+5V" H 1390 2023 50  0000 C CNN
F 2 "" H 1375 1850 50  0001 C CNN
F 3 "" H 1375 1850 50  0001 C CNN
	1    1375 1850
	1    0    0    -1  
$EndComp
$EndSCHEMATC
