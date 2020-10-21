EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 5
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 4400 3800 1    39   Input ~ 0
VBUS
$Comp
L power:+3.3V #PWR016
U 1 1 5F6E4375
P 5600 3800
F 0 "#PWR016" H 5600 3650 50  0001 C CNN
F 1 "+3.3V" H 5615 3973 50  0000 C CNN
F 2 "" H 5600 3800 50  0001 C CNN
F 3 "" H 5600 3800 50  0001 C CNN
	1    5600 3800
	1    0    0    -1  
$EndComp
$Comp
L DX_MON:TC1015-3.3VCT713 U3
U 1 1 5F6E6506
P 5000 4000
F 0 "U3" H 5000 4341 39  0000 C CNN
F 1 "TC1015-3.3VCT713" H 5000 4266 39  0000 C CNN
F 2 "rhais_package-smd:SOT-23-5" H 5000 4000 39  0001 C CNN
F 3 "" H 5000 4000 39  0001 C CNN
	1    5000 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 3900 5600 3900
Wire Wire Line
	5600 3900 5600 3800
Wire Wire Line
	4400 3800 4400 3900
Wire Wire Line
	4400 3900 4500 3900
$Comp
L power:GND #PWR06
U 1 1 5F6E7098
P 5000 4400
F 0 "#PWR06" H 5000 4150 50  0001 C CNN
F 1 "GND" H 5005 4227 50  0000 C CNN
F 2 "" H 5000 4400 50  0001 C CNN
F 3 "" H 5000 4400 50  0001 C CNN
	1    5000 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 4400 5000 4300
$Comp
L Device:C_Small C6
U 1 1 5F6E72D6
P 5600 4200
F 0 "C6" H 5650 4300 50  0000 L CNN
F 1 "470pF" H 5650 4100 50  0000 L CNN
F 2 "rhais_rcl:C0603" H 5600 4200 50  0001 C CNN
F 3 "~" H 5600 4200 50  0001 C CNN
	1    5600 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 4000 5600 4000
Wire Wire Line
	5600 4000 5600 4100
$Comp
L power:GND #PWR017
U 1 1 5F6E7556
P 5600 4400
F 0 "#PWR017" H 5600 4150 50  0001 C CNN
F 1 "GND" H 5605 4227 50  0000 C CNN
F 2 "" H 5600 4400 50  0001 C CNN
F 3 "" H 5600 4400 50  0001 C CNN
	1    5600 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 4400 5600 4300
Wire Wire Line
	4500 4000 4400 4000
Wire Wire Line
	4400 4000 4400 3900
Connection ~ 4400 3900
$Comp
L Device:C_Small C3
U 1 1 5F6E7C90
P 3850 4000
F 0 "C3" H 3900 4100 50  0000 L CNN
F 1 "1uF" H 3900 3900 50  0000 L CNN
F 2 "rhais_rcl:C0603" H 3850 4000 50  0001 C CNN
F 3 "~" H 3850 4000 50  0001 C CNN
	1    3850 4000
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C2
U 1 1 5F6E812F
P 3650 4000
F 0 "C2" H 3600 3900 50  0000 R CNN
F 1 "0.1uF" H 3600 4100 50  0000 R CNN
F 2 "rhais_rcl:C0603" H 3650 4000 50  0001 C CNN
F 3 "~" H 3650 4000 50  0001 C CNN
	1    3650 4000
	1    0    0    1   
$EndComp
$Comp
L Device:C_Small C8
U 1 1 5F6E94E9
P 6150 4000
F 0 "C8" H 6200 4100 50  0000 L CNN
F 1 "1uF" H 6200 3900 50  0000 L CNN
F 2 "rhais_rcl:C0603" H 6150 4000 50  0001 C CNN
F 3 "~" H 6150 4000 50  0001 C CNN
	1    6150 4000
	-1   0    0    -1  
$EndComp
$Comp
L Device:C_Small C7
U 1 1 5F6E94EF
P 6350 4000
F 0 "C7" H 6300 3900 50  0000 R CNN
F 1 "0.1uF" H 6300 4100 50  0000 R CNN
F 2 "rhais_rcl:C0603" H 6350 4000 50  0001 C CNN
F 3 "~" H 6350 4000 50  0001 C CNN
	1    6350 4000
	-1   0    0    1   
$EndComp
Text HLabel 3750 3700 1    39   Input ~ 0
VBUS
Wire Wire Line
	3750 3700 3750 3800
Wire Wire Line
	3750 3800 3850 3800
Wire Wire Line
	3850 3800 3850 3900
Wire Wire Line
	3750 3800 3650 3800
Wire Wire Line
	3650 3800 3650 3900
Connection ~ 3750 3800
$Comp
L power:GND #PWR05
U 1 1 5F6EA105
P 3750 4300
F 0 "#PWR05" H 3750 4050 50  0001 C CNN
F 1 "GND" H 3755 4127 50  0000 C CNN
F 2 "" H 3750 4300 50  0001 C CNN
F 3 "" H 3750 4300 50  0001 C CNN
	1    3750 4300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR019
U 1 1 5F6EAC39
P 6250 4300
F 0 "#PWR019" H 6250 4050 50  0001 C CNN
F 1 "GND" H 6255 4127 50  0000 C CNN
F 2 "" H 6250 4300 50  0001 C CNN
F 3 "" H 6250 4300 50  0001 C CNN
	1    6250 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 4100 6150 4200
Wire Wire Line
	6150 4200 6250 4200
Wire Wire Line
	6250 4200 6250 4300
Wire Wire Line
	6250 4200 6350 4200
Wire Wire Line
	6350 4200 6350 4100
Connection ~ 6250 4200
Wire Wire Line
	3650 4100 3650 4200
Wire Wire Line
	3650 4200 3750 4200
Wire Wire Line
	3750 4200 3750 4300
Wire Wire Line
	3750 4200 3850 4200
Wire Wire Line
	3850 4200 3850 4100
Connection ~ 3750 4200
$Comp
L power:+3.3V #PWR018
U 1 1 5F6EC417
P 6250 3700
F 0 "#PWR018" H 6250 3550 50  0001 C CNN
F 1 "+3.3V" H 6265 3873 50  0000 C CNN
F 2 "" H 6250 3700 50  0001 C CNN
F 3 "" H 6250 3700 50  0001 C CNN
	1    6250 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 3700 6250 3800
Wire Wire Line
	6250 3800 6150 3800
Wire Wire Line
	6150 3800 6150 3900
Wire Wire Line
	6250 3800 6350 3800
Wire Wire Line
	6350 3800 6350 3900
Connection ~ 6250 3800
$Comp
L Device:R_Small R14
U 1 1 5F94E976
P 7000 4200
F 0 "R14" H 7059 4246 50  0000 L CNN
F 1 "440R" H 7059 4155 50  0000 L CNN
F 2 "rhais_rcl:R0603" H 7000 4200 50  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2860681.pdf" H 7000 4200 50  0001 C CNN
F 4 "Multicomp" H 7000 4200 50  0001 C CNN "MFR"
F 5 "MCWR06X4700FTL" H 7000 4200 50  0001 C CNN "MPN"
F 6 "2447374" H 7000 4200 50  0001 C CNN "OC_FARNELL"
F 7 "https://uk.farnell.com/multicomp/mcwr06x4700ftl/res-470r-1-0-1w-0603-thick-film/dp/2447374" H 7000 4200 50  0001 C CNN "URL_FARNELL"
	1    7000 4200
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D3
U 1 1 5F94F2E8
P 7000 3750
F 0 "D3" V 7039 3632 50  0000 R CNN
F 1 "LED" V 6948 3632 50  0000 R CNN
F 2 "rhais_led:LED0603" H 7000 3750 50  0001 C CNN
F 3 "https://www.kingbright.com/attachments/file/psearch/000/00/20160808bak/KP-1608SGC(Ver.21B).pdf" H 7000 3750 50  0001 C CNN
F 4 "Kingbright" H 7000 3750 50  0001 C CNN "MFR"
F 5 "8529833" H 7000 3750 50  0001 C CNN "OC_FARNELL"
F 6 "https://uk.farnell.com/kingbright/kp-1608sgc/led-0-8mm-x-1-2mm-green-12mcd/dp/8529833" H 7000 3750 50  0001 C CNN "URL_FARNELL"
F 7 "KP-1608SGC" H 7000 3750 50  0001 C CNN "MPN"
	1    7000 3750
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR040
U 1 1 5F9506D7
P 7000 3500
F 0 "#PWR040" H 7000 3350 50  0001 C CNN
F 1 "+3.3V" H 7015 3673 50  0000 C CNN
F 2 "" H 7000 3500 50  0001 C CNN
F 3 "" H 7000 3500 50  0001 C CNN
	1    7000 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 3500 7000 3600
Wire Wire Line
	7000 3900 7000 4100
$Comp
L power:GND #PWR041
U 1 1 5F9516F3
P 7000 4400
F 0 "#PWR041" H 7000 4150 50  0001 C CNN
F 1 "GND" H 7005 4227 50  0000 C CNN
F 2 "" H 7000 4400 50  0001 C CNN
F 3 "" H 7000 4400 50  0001 C CNN
	1    7000 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 4300 7000 4400
$EndSCHEMATC
