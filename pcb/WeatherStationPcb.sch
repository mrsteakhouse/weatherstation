EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "WeatherStation"
Date "2020-05-16"
Rev "1"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L EspFlash:ESP-01 U3
U 1 1 5EC008CF
P 5050 1350
F 0 "U3" V 5146 1062 50  0000 R CNN
F 1 "ESP-01" V 5055 1062 50  0000 R CNN
F 2 "EspFlash:ESP-01" H 5050 1350 50  0001 C CNN
F 3 "~" H 5050 1350 50  0001 C CNN
	1    5050 1350
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J3
U 1 1 5EC0B13F
P 5400 2800
F 0 "J3" V 5272 2980 50  0000 L CNN
F 1 "Conn_01x04" V 5363 2980 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 5400 2800 50  0001 C CNN
F 3 "~" H 5400 2800 50  0001 C CNN
	1    5400 2800
	0    1    1    0   
$EndComp
$Comp
L Connector_Generic:Conn_01x06 J2
U 1 1 5EC0B8AD
P 4150 2800
F 0 "J2" V 4022 3080 50  0000 L CNN
F 1 "Conn_01x06" V 4113 3080 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x06_P2.54mm_Vertical" H 4150 2800 50  0001 C CNN
F 3 "~" H 4150 2800 50  0001 C CNN
	1    4150 2800
	0    1    1    0   
$EndComp
$Comp
L Device:C C2
U 1 1 5EC0C150
P 3250 2550
F 0 "C2" H 3365 2596 50  0000 L CNN
F 1 "10uF" H 3365 2505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3288 2400 50  0001 C CNN
F 3 "~" H 3250 2550 50  0001 C CNN
	1    3250 2550
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5EC0C5F8
P 2100 2550
F 0 "C1" H 2215 2596 50  0000 L CNN
F 1 "100nF" H 2215 2505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2138 2400 50  0001 C CNN
F 3 "~" H 2100 2550 50  0001 C CNN
	1    2100 2550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5EC0CCFE
P 2700 2900
F 0 "#PWR0101" H 2700 2650 50  0001 C CNN
F 1 "GND" H 2705 2727 50  0000 C CNN
F 2 "" H 2700 2900 50  0001 C CNN
F 3 "" H 2700 2900 50  0001 C CNN
	1    2700 2900
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J1
U 1 1 5EC0D311
P 1350 2300
F 0 "J1" H 1268 1975 50  0000 C CNN
F 1 "Screw_Terminal_01x02" H 1268 2066 50  0000 C CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 1350 2300 50  0001 C CNN
F 3 "~" H 1350 2300 50  0001 C CNN
	1    1350 2300
	-1   0    0    1   
$EndComp
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5EC0D8F5
P 1850 1900
F 0 "#FLG0101" H 1850 1975 50  0001 C CNN
F 1 "PWR_FLAG" H 1850 2073 50  0000 C CNN
F 2 "" H 1850 1900 50  0001 C CNN
F 3 "~" H 1850 1900 50  0001 C CNN
	1    1850 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 2200 1850 2200
Wire Wire Line
	1850 1900 1850 2200
Connection ~ 1850 2200
Wire Wire Line
	1850 2200 2100 2200
Wire Wire Line
	2100 2200 2100 2400
Connection ~ 2100 2200
Wire Wire Line
	2100 2200 2400 2200
Wire Wire Line
	2100 2700 2700 2700
Wire Wire Line
	3250 2400 3250 2200
Wire Wire Line
	3250 2200 3000 2200
Wire Wire Line
	2700 2500 2700 2700
Connection ~ 2700 2700
Wire Wire Line
	2700 2700 3250 2700
Wire Wire Line
	2700 2700 2700 2900
$Comp
L power:GND #PWR0102
U 1 1 5EC108FE
P 1550 2500
F 0 "#PWR0102" H 1550 2250 50  0001 C CNN
F 1 "GND" H 1555 2327 50  0000 C CNN
F 2 "" H 1550 2500 50  0001 C CNN
F 3 "" H 1550 2500 50  0001 C CNN
	1    1550 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 2300 1550 2400
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5EC11355
P 1750 2400
F 0 "#FLG0102" H 1750 2475 50  0001 C CNN
F 1 "PWR_FLAG" H 1750 2573 50  0000 C CNN
F 2 "" H 1750 2400 50  0001 C CNN
F 3 "~" H 1750 2400 50  0001 C CNN
	1    1750 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 2400 1550 2400
Connection ~ 1550 2400
Wire Wire Line
	1550 2400 1550 2500
Wire Wire Line
	3250 2200 3550 2200
Wire Wire Line
	4350 2200 4350 2600
Connection ~ 3250 2200
Wire Wire Line
	4350 2200 5500 2200
Wire Wire Line
	5500 2200 5500 2600
Connection ~ 4350 2200
$Comp
L power:GND #PWR0103
U 1 1 5EC1BDEF
P 6350 2600
F 0 "#PWR0103" H 6350 2350 50  0001 C CNN
F 1 "GND" H 6355 2427 50  0000 C CNN
F 2 "" H 6350 2600 50  0001 C CNN
F 3 "" H 6350 2600 50  0001 C CNN
	1    6350 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 2600 4250 2400
Wire Wire Line
	4250 2400 5400 2400
Wire Wire Line
	6350 2400 6350 2600
Wire Wire Line
	5400 2600 5400 2400
Connection ~ 5400 2400
Wire Wire Line
	5400 2400 5800 2400
Wire Wire Line
	5300 2600 5300 1800
Wire Wire Line
	5300 1800 5150 1800
Wire Wire Line
	5150 1800 5150 1550
Wire Wire Line
	4150 2600 4150 1800
Wire Wire Line
	4150 1800 5150 1800
Connection ~ 5150 1800
Wire Wire Line
	5050 1550 5050 1900
Wire Wire Line
	5050 1900 5200 1900
Wire Wire Line
	5200 1900 5200 2600
Wire Wire Line
	5050 1900 4050 1900
Wire Wire Line
	4050 1900 4050 2600
Connection ~ 5050 1900
Text Label 5300 1800 0    50   ~ 0
SCL
Text Label 5200 1900 0    50   ~ 0
SDA
Wire Wire Line
	3850 2200 3850 2600
Connection ~ 3850 2200
Wire Wire Line
	3850 2200 4350 2200
Wire Wire Line
	3550 2200 3550 850 
Wire Wire Line
	3550 850  4950 850 
Wire Wire Line
	5150 850  5150 1050
Connection ~ 3550 2200
Wire Wire Line
	3550 2200 3850 2200
Wire Wire Line
	4950 850  4950 1050
Connection ~ 4950 850 
Wire Wire Line
	4950 850  5150 850 
Wire Wire Line
	5800 2400 5800 1550
Wire Wire Line
	5800 1550 5250 1550
Connection ~ 5800 2400
Wire Wire Line
	5800 2400 6350 2400
NoConn ~ 4950 1550
NoConn ~ 5050 1050
NoConn ~ 5250 1050
NoConn ~ 3950 2600
Text Label 5800 1550 0    50   ~ 0
GND
Text Label 5500 2200 0    50   ~ 0
VCC
$Comp
L Regulator_Linear:MCP1755S-3302xCB U1
U 1 1 5EC560F4
P 2700 2200
F 0 "U1" H 2700 2442 50  0000 C CNN
F 1 "MCP1755S-3302xCB" H 2700 2351 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223" H 2700 2425 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/20002276C.pdf" H 2700 2200 50  0001 C CNN
	1    2700 2200
	1    0    0    -1  
$EndComp
$EndSCHEMATC
