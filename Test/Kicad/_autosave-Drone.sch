EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 5850 4325 2    50   Input ~ 0
SWDIO
Text GLabel 5850 4425 2    50   Input ~ 0
SWCLK
Text GLabel 5850 3625 2    50   Input ~ 0
MOTOR1_Signal
Text GLabel 5850 3725 2    50   Input ~ 0
MOTOR2_Signal
Text GLabel 4550 3025 0    50   Input ~ 0
MOTOR3_Signal
Text GLabel 4550 3125 0    50   Input ~ 0
MOTOR4_Signal
Text GLabel 5850 3925 2    50   Input ~ 0
TX1
Text GLabel 5850 4025 2    50   Input ~ 0
RX1
Text GLabel 5850 3225 2    50   Input ~ 0
TX2
Text GLabel 5850 3325 2    50   Input ~ 0
RX2
Text GLabel 4550 4025 0    50   Input ~ 0
TX3
Text GLabel 4550 4125 0    50   Input ~ 0
RX3
Text GLabel 4550 3725 0    50   Input ~ 0
SDA1
$Comp
L Sensor_Motion:MPU-6050 U4
U 1 1 5F83865B
P 1725 6625
F 0 "U4" H 1200 7325 50  0000 C CNN
F 1 "MPU-6050" H 1200 7425 50  0000 C CNN
F 2 "Sensor_Motion:InvenSense_QFN-24_4x4mm_P0.5mm" H 1725 5825 50  0001 C CNN
F 3 "https://store.invensense.com/datasheets/invensense/MPU-6050_DataSheet_V3%204.pdf" H 1725 6475 50  0001 C CNN
	1    1725 6625
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR035
U 1 1 5F85A548
P 1725 7325
F 0 "#PWR035" H 1725 7075 50  0001 C CNN
F 1 "GND" H 1730 7152 50  0000 C CNN
F 2 "" H 1725 7325 50  0001 C CNN
F 3 "" H 1725 7325 50  0001 C CNN
	1    1725 7325
	1    0    0    -1  
$EndComp
Wire Wire Line
	1025 6925 1025 7325
Wire Wire Line
	1025 7325 1725 7325
Connection ~ 1725 7325
Text GLabel 2425 6525 2    50   Input ~ 0
GYRO_AUX_SDA
Text GLabel 2425 6625 2    50   Input ~ 0
GYRO_AUX_SCL
Text GLabel 1025 6325 0    50   Input ~ 0
SDA1
Text GLabel 1025 6425 0    50   Input ~ 0
SCL1
Wire Wire Line
	1025 6825 1025 6925
Connection ~ 1025 6925
Wire Wire Line
	1025 6525 1025 6825
Connection ~ 1025 6825
$Comp
L Device:C C15
U 1 1 5F85CA93
P 2425 7175
F 0 "C15" H 2540 7221 50  0000 L CNN
F 1 ".1uF" H 2540 7130 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 2463 7025 50  0001 C CNN
F 3 "~" H 2425 7175 50  0001 C CNN
	1    2425 7175
	1    0    0    -1  
$EndComp
Wire Wire Line
	2425 6925 2425 7025
Wire Wire Line
	2425 7325 1725 7325
Wire Wire Line
	2425 6825 2875 6825
$Comp
L Device:C C16
U 1 1 5F85F7AC
P 2875 7175
F 0 "C16" H 2990 7221 50  0000 L CNN
F 1 "2.2nF" H 2990 7130 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 2913 7025 50  0001 C CNN
F 3 "~" H 2875 7175 50  0001 C CNN
	1    2875 7175
	1    0    0    -1  
$EndComp
Wire Wire Line
	2875 6825 2875 7025
Wire Wire Line
	2875 7325 2425 7325
Connection ~ 2425 7325
Text GLabel 2425 6325 2    50   Input ~ 0
GYRO_INT
$Comp
L power:+3.3V #PWR031
U 1 1 5F8610EA
P 1625 5450
F 0 "#PWR031" H 1625 5300 50  0001 C CNN
F 1 "+3.3V" H 1640 5623 50  0000 C CNN
F 2 "" H 1625 5450 50  0001 C CNN
F 3 "" H 1625 5450 50  0001 C CNN
	1    1625 5450
	1    0    0    -1  
$EndComp
$Comp
L Device:C C13
U 1 1 5F865292
P 2125 5625
F 0 "C13" V 2325 5375 50  0000 C CNN
F 1 "10nF" V 2250 5400 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 2163 5475 50  0001 C CNN
F 3 "~" H 2125 5625 50  0001 C CNN
	1    2125 5625
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C14
U 1 1 5F8667FF
P 2125 5875
F 0 "C14" V 2025 5725 50  0000 C CNN
F 1 ".1uF" V 1950 5750 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 2163 5725 50  0001 C CNN
F 3 "~" H 2125 5875 50  0001 C CNN
	1    2125 5875
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1625 5450 1625 5625
Wire Wire Line
	1625 5625 1825 5625
Connection ~ 1625 5625
Wire Wire Line
	1625 5625 1625 5925
Wire Wire Line
	1825 5625 1825 5875
Connection ~ 1825 5625
Wire Wire Line
	1825 5625 1975 5625
Wire Wire Line
	1975 5875 1825 5875
Connection ~ 1825 5875
Wire Wire Line
	1825 5875 1825 5925
Wire Wire Line
	2275 5625 2325 5625
Wire Wire Line
	2325 5625 2325 5775
Wire Wire Line
	2325 5875 2275 5875
Wire Wire Line
	2325 5775 2475 5775
Wire Wire Line
	2475 5775 2475 5825
Connection ~ 2325 5775
Wire Wire Line
	2325 5775 2325 5875
$Comp
L power:GND #PWR033
U 1 1 5F86ECC6
P 2475 5825
F 0 "#PWR033" H 2475 5575 50  0001 C CNN
F 1 "GND" H 2475 5650 50  0000 C CNN
F 2 "" H 2475 5825 50  0001 C CNN
F 3 "" H 2475 5825 50  0001 C CNN
	1    2475 5825
	1    0    0    -1  
$EndComp
Wire Notes Line
	475  5150 3400 5150
Wire Notes Line
	3400 5150 3400 7800
Text Notes 625  5025 0    89   ~ 0
Gyroscope
$Comp
L Regulator_Linear:MIC5504-3.3YM5 U1
U 1 1 5F87AC1E
P 1775 1300
F 0 "U1" H 1775 1667 50  0000 C CNN
F 1 "MIC5504-3.3YM5" H 1775 1576 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-5" H 1775 900 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/MIC550X.pdf" H 1525 1550 50  0001 C CNN
	1    1775 1300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR010
U 1 1 5F87B26E
P 1775 1600
F 0 "#PWR010" H 1775 1350 50  0001 C CNN
F 1 "GND" H 1780 1427 50  0000 C CNN
F 2 "" H 1775 1600 50  0001 C CNN
F 3 "" H 1775 1600 50  0001 C CNN
	1    1775 1600
	1    0    0    -1  
$EndComp
$Comp
L Device:C C10
U 1 1 5F87BA49
P 2300 1350
F 0 "C10" H 2430 1190 50  0000 C CNN
F 1 "1uF" H 2430 1250 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 2338 1200 50  0001 C CNN
F 3 "~" H 2300 1350 50  0001 C CNN
	1    2300 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2175 1200 2300 1200
Wire Wire Line
	2300 1500 2300 1600
Wire Wire Line
	2300 1600 1775 1600
Connection ~ 1775 1600
Connection ~ 2300 1200
$Comp
L power:+3.3V #PWR08
U 1 1 5F87E535
P 2760 1200
F 0 "#PWR08" H 2760 1050 50  0001 C CNN
F 1 "+3.3V" V 2775 1328 50  0000 L CNN
F 2 "" H 2760 1200 50  0001 C CNN
F 3 "" H 2760 1200 50  0001 C CNN
	1    2760 1200
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR07
U 1 1 5F87F2C2
P 900 1200
F 0 "#PWR07" H 900 1050 50  0001 C CNN
F 1 "+5V" V 915 1328 50  0000 L CNN
F 2 "" H 900 1200 50  0001 C CNN
F 3 "" H 900 1200 50  0001 C CNN
	1    900  1200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1100 1200 1175 1200
Wire Wire Line
	1375 1200 1375 1400
Connection ~ 1375 1200
$Comp
L Device:C C9
U 1 1 5F880171
P 1175 1350
F 0 "C9" H 1050 1150 50  0000 C CNN
F 1 "1uF" H 1050 1225 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1213 1200 50  0001 C CNN
F 3 "~" H 1175 1350 50  0001 C CNN
	1    1175 1350
	1    0    0    -1  
$EndComp
Connection ~ 1175 1200
Wire Wire Line
	1175 1200 1375 1200
Wire Wire Line
	1175 1500 1175 1600
Wire Wire Line
	1175 1600 1775 1600
Text Notes 725  775  0    89   ~ 0
Power Supply
$Comp
L Device:D_Schottky_Small D1
U 1 1 5F893814
P 1000 1200
F 0 "D1" H 1000 993 50  0000 C CNN
F 1 "?" H 1000 1084 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" V 1000 1200 50  0001 C CNN
F 3 "~" V 1000 1200 50  0001 C CNN
	1    1000 1200
	-1   0    0    1   
$EndComp
Wire Notes Line
	3125 475  3125 1950
Wire Notes Line
	3125 1950 475  1950
Wire Wire Line
	5050 1575 5050 1625
Wire Wire Line
	5050 1625 5150 1625
Wire Wire Line
	5150 1625 5150 1725
Connection ~ 5050 1625
Wire Wire Line
	5050 1625 5050 1725
Wire Wire Line
	5150 1625 5250 1625
Connection ~ 5150 1625
Wire Wire Line
	5250 1625 5350 1625
Wire Wire Line
	5350 1625 5350 1725
Connection ~ 5250 1625
Wire Wire Line
	5250 1625 5250 1725
Wire Wire Line
	5050 4725 5050 4775
Wire Wire Line
	5050 4775 5150 4775
Wire Wire Line
	5250 4775 5250 4725
Connection ~ 5150 4775
Wire Wire Line
	5150 4775 5250 4775
Wire Wire Line
	5150 4725 5150 4775
$Comp
L power:GND #PWR028
U 1 1 5F8EB7C2
P 5050 4775
F 0 "#PWR028" H 5050 4525 50  0001 C CNN
F 1 "GND" H 5055 4602 50  0000 C CNN
F 2 "" H 5050 4775 50  0001 C CNN
F 3 "" H 5050 4775 50  0001 C CNN
	1    5050 4775
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 4725 5350 4775
Wire Wire Line
	5350 4775 5250 4775
Connection ~ 5250 4775
Connection ~ 5050 4775
$Comp
L power:+3.3VA #PWR012
U 1 1 5F90AF1D
P 5450 1725
F 0 "#PWR012" H 5450 1575 50  0001 C CNN
F 1 "+3.3VA" V 5465 1853 50  0000 L CNN
F 2 "" H 5450 1725 50  0001 C CNN
F 3 "" H 5450 1725 50  0001 C CNN
	1    5450 1725
	0    1    1    0   
$EndComp
Text GLabel 4550 2325 0    50   Input ~ 0
HSE_IN
Text GLabel 4550 2425 0    50   Input ~ 0
HSE_OUT
$Comp
L Device:Crystal_GND24_Small HSE1
U 1 1 5F91A8B4
P 1650 2700
F 0 "HSE1" H 1500 2975 50  0000 L CNN
F 1 "16 MHz" H 1450 2900 50  0000 L CNN
F 2 "Crystal:Crystal_SMD_3225-4Pin_3.2x2.5mm_HandSoldering" H 1650 2700 50  0001 C CNN
F 3 "~" H 1650 2700 50  0001 C CNN
	1    1650 2700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR020
U 1 1 5F91C717
P 1650 3000
F 0 "#PWR020" H 1650 2750 50  0001 C CNN
F 1 "GND" H 1655 2827 50  0000 C CNN
F 2 "" H 1650 3000 50  0001 C CNN
F 3 "" H 1650 3000 50  0001 C CNN
	1    1650 3000
	1    0    0    -1  
$EndComp
Text GLabel 1275 2700 0    50   Input ~ 0
HSE_IN
Text GLabel 1925 2700 2    50   Input ~ 0
HSE_OUT
$Comp
L Device:C C11
U 1 1 5F91D0F4
P 1350 2850
F 0 "C11" H 1475 2625 50  0000 C CNN
F 1 "12pF" H 1475 2700 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1388 2700 50  0001 C CNN
F 3 "~" H 1350 2850 50  0001 C CNN
	1    1350 2850
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C12
U 1 1 5F91DDB6
P 1825 2850
F 0 "C12" H 1950 2625 50  0000 C CNN
F 1 "12pF" H 1950 2700 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1863 2700 50  0001 C CNN
F 3 "~" H 1825 2850 50  0001 C CNN
	1    1825 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 2700 1275 2700
Connection ~ 1650 3000
Wire Wire Line
	1650 2800 1650 3000
Wire Wire Line
	1650 2600 1650 2575
Wire Wire Line
	1650 2575 1500 2575
Wire Wire Line
	1500 2575 1500 3000
Wire Wire Line
	1500 3000 1650 3000
Wire Wire Line
	1350 3000 1500 3000
Connection ~ 1500 3000
Wire Wire Line
	1650 3000 1825 3000
Wire Wire Line
	1350 2700 1550 2700
Connection ~ 1350 2700
Wire Wire Line
	1750 2700 1825 2700
Wire Wire Line
	1825 2700 1925 2700
Connection ~ 1825 2700
Text GLabel 4550 1925 0    50   Input ~ 0
NRST
$Comp
L Device:R_Small R1
U 1 1 5F94C99B
P 6525 2300
F 0 "R1" H 6584 2346 50  0000 L CNN
F 1 "10k" H 6584 2255 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" H 6525 2300 50  0001 C CNN
F 3 "~" H 6525 2300 50  0001 C CNN
	1    6525 2300
	1    0    0    -1  
$EndComp
Text GLabel 4550 3225 0    50   Input ~ 0
BOOT1
Text GLabel 4550 2125 0    50   Input ~ 0
BOOT0
Text GLabel 6525 2200 1    50   Input ~ 0
BOOT0
$Comp
L Device:R_Small R2
U 1 1 5F957497
P 6800 2300
F 0 "R2" H 6859 2346 50  0000 L CNN
F 1 "10k" H 6859 2255 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" H 6800 2300 50  0001 C CNN
F 3 "~" H 6800 2300 50  0001 C CNN
	1    6800 2300
	1    0    0    -1  
$EndComp
Text GLabel 6800 2200 1    50   Input ~ 0
BOOT1
$Comp
L power:GND #PWR016
U 1 1 5F95C8DB
P 6525 2400
F 0 "#PWR016" H 6525 2150 50  0001 C CNN
F 1 "GND" H 6530 2227 50  0000 C CNN
F 2 "" H 6525 2400 50  0001 C CNN
F 3 "" H 6525 2400 50  0001 C CNN
	1    6525 2400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR017
U 1 1 5F95D5BF
P 6800 2400
F 0 "#PWR017" H 6800 2150 50  0001 C CNN
F 1 "GND" H 6805 2227 50  0000 C CNN
F 2 "" H 6800 2400 50  0001 C CNN
F 3 "" H 6800 2400 50  0001 C CNN
	1    6800 2400
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J1
U 1 1 5F9634B7
P 7375 2100
F 0 "J1" H 7483 2381 50  0000 C CNN
F 1 "SWD" H 7483 2290 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 7375 2100 50  0001 C CNN
F 3 "~" H 7375 2100 50  0001 C CNN
	1    7375 2100
	1    0    0    -1  
$EndComp
Text GLabel 7575 2000 2    50   Input ~ 0
SWCLK
Text GLabel 7575 2100 2    50   Input ~ 0
SWDIO
$Comp
L power:GND #PWR013
U 1 1 5F9653BF
P 7975 2200
F 0 "#PWR013" H 7975 1950 50  0001 C CNN
F 1 "GND" H 7980 2027 50  0000 C CNN
F 2 "" H 7975 2200 50  0001 C CNN
F 3 "" H 7975 2200 50  0001 C CNN
	1    7975 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7575 2200 7975 2200
$Comp
L Device:LED_Small D2
U 1 1 5F97A507
P 3725 4425
F 0 "D2" V 3750 4675 50  0000 R CNN
F 1 "Green" V 3675 4750 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 3725 4425 50  0001 C CNN
F 3 "~" V 3725 4425 50  0001 C CNN
	1    3725 4425
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED_Small D3
U 1 1 5F97BA91
P 4050 4425
F 0 "D3" V 4096 4523 50  0000 L CNN
F 1 "Red" V 4005 4523 50  0000 L CNN
F 2 "LED_SMD:LED_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 4050 4425 50  0001 C CNN
F 3 "~" V 4050 4425 50  0001 C CNN
	1    4050 4425
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3725 4325 3725 4225
Wire Wire Line
	3725 4225 4550 4225
Wire Wire Line
	4050 4325 4550 4325
$Comp
L Device:R_Small R7
U 1 1 5F99C630
P 3725 4625
F 0 "R7" H 3475 4650 50  0000 L CNN
F 1 "220" H 3450 4575 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" H 3725 4625 50  0001 C CNN
F 3 "~" H 3725 4625 50  0001 C CNN
	1    3725 4625
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R8
U 1 1 5F9A0E49
P 4050 4625
F 0 "R8" H 3875 4675 50  0000 L CNN
F 1 "220" H 3850 4600 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" H 4050 4625 50  0001 C CNN
F 3 "~" H 4050 4625 50  0001 C CNN
	1    4050 4625
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR026
U 1 1 5F9A1FB9
P 3725 4725
F 0 "#PWR026" H 3725 4475 50  0001 C CNN
F 1 "GND" H 3730 4552 50  0000 C CNN
F 2 "" H 3725 4725 50  0001 C CNN
F 3 "" H 3725 4725 50  0001 C CNN
	1    3725 4725
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR027
U 1 1 5F9A32B4
P 4050 4725
F 0 "#PWR027" H 4050 4475 50  0001 C CNN
F 1 "GND" H 4055 4552 50  0000 C CNN
F 2 "" H 4050 4725 50  0001 C CNN
F 3 "" H 4050 4725 50  0001 C CNN
	1    4050 4725
	1    0    0    -1  
$EndComp
NoConn ~ 4550 4525
NoConn ~ 4550 3925
NoConn ~ 4550 2825
NoConn ~ 4550 2725
NoConn ~ 4550 2625
NoConn ~ 5850 3025
NoConn ~ 5850 3125
NoConn ~ 5850 3825
NoConn ~ 5850 4125
NoConn ~ 5850 4225
Wire Notes Line
	850  2250 2525 2250
Wire Notes Line
	2525 2250 2525 3350
Wire Notes Line
	2525 3350 850  3350
Wire Notes Line
	850  3350 850  2250
Text Notes 950  2400 0    89   ~ 0
Crystal
Connection ~ 4225 700 
$Comp
L power:+3.3VA #PWR03
U 1 1 5F90A98A
P 4225 700
F 0 "#PWR03" H 4225 550 50  0001 C CNN
F 1 "+3.3VA" V 4240 828 50  0000 L CNN
F 2 "" H 4225 700 50  0001 C CNN
F 3 "" H 4225 700 50  0001 C CNN
	1    4225 700 
	0    1    1    0   
$EndComp
Connection ~ 3875 1075
Wire Wire Line
	3875 1025 3875 1075
Wire Wire Line
	4225 1075 4225 1025
Wire Wire Line
	3875 1075 4225 1075
Connection ~ 3875 700 
Wire Wire Line
	3875 725  3875 700 
Wire Wire Line
	4225 700  4225 725 
Wire Wire Line
	3875 700  4225 700 
$Comp
L Device:C C7
U 1 1 5F8FF52C
P 4225 875
F 0 "C7" H 4050 900 50  0000 C CNN
F 1 "1uF" H 4050 975 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 4263 725 50  0001 C CNN
F 3 "~" H 4225 875 50  0001 C CNN
	1    4225 875 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5F8FF196
P 3875 1075
F 0 "#PWR06" H 3875 825 50  0001 C CNN
F 1 "GND" H 3880 902 50  0000 C CNN
F 2 "" H 3875 1075 50  0001 C CNN
F 3 "" H 3875 1075 50  0001 C CNN
	1    3875 1075
	1    0    0    -1  
$EndComp
$Comp
L Device:C C6
U 1 1 5F8FEA07
P 3875 875
F 0 "C6" H 3700 900 50  0000 C CNN
F 1 "10nF" H 3700 975 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 3913 725 50  0001 C CNN
F 3 "~" H 3875 875 50  0001 C CNN
	1    3875 875 
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR02
U 1 1 5F8FDD1D
P 3875 700
F 0 "#PWR02" H 3875 550 50  0001 C CNN
F 1 "+3.3V" H 3890 873 50  0000 C CNN
F 2 "" H 3875 700 50  0001 C CNN
F 3 "" H 3875 700 50  0001 C CNN
	1    3875 700 
	1    0    0    -1  
$EndComp
Connection ~ 4975 1025
$Comp
L power:GND #PWR05
U 1 1 5F8DBFDF
P 4975 1025
F 0 "#PWR05" H 4975 775 50  0001 C CNN
F 1 "GND" H 4980 852 50  0000 C CNN
F 2 "" H 4975 1025 50  0001 C CNN
F 3 "" H 4975 1025 50  0001 C CNN
	1    4975 1025
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 1025 5625 1025
Wire Wire Line
	6275 1025 5950 1025
Wire Wire Line
	6275 1000 6275 1025
Connection ~ 5950 1025
Connection ~ 5950 675 
Wire Wire Line
	6275 675  6275 700 
Wire Wire Line
	5950 675  6275 675 
$Comp
L Device:C C5
U 1 1 5F8C6C7D
P 6275 850
F 0 "C5" H 6100 875 50  0000 C CNN
F 1 "4.7uF" H 6100 950 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 6313 700 50  0001 C CNN
F 3 "~" H 6275 850 50  0001 C CNN
	1    6275 850 
	1    0    0    -1  
$EndComp
Connection ~ 5625 1025
Wire Wire Line
	5950 1025 5950 1000
Wire Wire Line
	5625 1025 5950 1025
Connection ~ 5300 1025
Wire Wire Line
	5625 1025 5625 1000
Wire Wire Line
	4975 1025 5300 1025
Wire Wire Line
	5300 1025 5300 1000
Wire Wire Line
	4975 1000 4975 1025
Connection ~ 5625 675 
Wire Wire Line
	5950 675  5950 700 
Wire Wire Line
	5625 675  5950 675 
Connection ~ 5300 675 
Wire Wire Line
	5625 675  5625 700 
Wire Wire Line
	5300 675  5625 675 
Connection ~ 4975 675 
Wire Wire Line
	5300 675  5300 700 
Wire Wire Line
	4975 675  5300 675 
$Comp
L Device:C C4
U 1 1 5F8BCBE4
P 5950 850
F 0 "C4" H 5775 875 50  0000 C CNN
F 1 "100nF" H 5775 950 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 5988 700 50  0001 C CNN
F 3 "~" H 5950 850 50  0001 C CNN
	1    5950 850 
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 5F8BCBDE
P 5625 850
F 0 "C3" H 5450 875 50  0000 C CNN
F 1 "100nF" H 5450 950 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 5663 700 50  0001 C CNN
F 3 "~" H 5625 850 50  0001 C CNN
	1    5625 850 
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5F8B63E8
P 5300 850
F 0 "C2" H 5125 875 50  0000 C CNN
F 1 "100nF" H 5125 950 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 5338 700 50  0001 C CNN
F 3 "~" H 5300 850 50  0001 C CNN
	1    5300 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	4975 700  4975 675 
$Comp
L Device:C C1
U 1 1 5F8B2DC8
P 4975 850
F 0 "C1" H 4800 875 50  0000 C CNN
F 1 "100nF" H 4800 950 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 5013 700 50  0001 C CNN
F 3 "~" H 4975 850 50  0001 C CNN
	1    4975 850 
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR01
U 1 1 5F8B1FC1
P 4975 675
F 0 "#PWR01" H 4975 525 50  0001 C CNN
F 1 "+3.3V" H 4990 848 50  0000 C CNN
F 2 "" H 4975 675 50  0001 C CNN
F 3 "" H 4975 675 50  0001 C CNN
	1    4975 675 
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR09
U 1 1 5F8AEF00
P 5050 1575
F 0 "#PWR09" H 5050 1425 50  0001 C CNN
F 1 "+3.3V" H 5065 1748 50  0000 C CNN
F 2 "" H 5050 1575 50  0001 C CNN
F 3 "" H 5050 1575 50  0001 C CNN
	1    5050 1575
	1    0    0    -1  
$EndComp
Text GLabel 9400 2625 2    50   Input ~ 0
TX2
Text GLabel 9400 2725 2    50   Input ~ 0
RX2
Text GLabel 8675 2600 2    50   Input ~ 0
TX1
Text GLabel 8675 2700 2    50   Input ~ 0
RX1
Text GLabel 10050 2600 2    50   Input ~ 0
TX3
Text GLabel 10050 2700 2    50   Input ~ 0
RX3
$Comp
L Mechanical:MountingHole_Pad H1
U 1 1 5FA26841
P 7675 3650
F 0 "H1" H 7775 3699 50  0000 L CNN
F 1 "4V5" H 7775 3608 50  0000 L CNN
F 2 "Connector_PinHeader_2.00mm:PinHeader_1x01_P2.00mm_Vertical" H 7675 3650 50  0001 C CNN
F 3 "~" H 7675 3650 50  0001 C CNN
	1    7675 3650
	1    0    0    -1  
$EndComp
Text GLabel 1250 1200 1    50   Input ~ 0
4V5
Text GLabel 7675 3750 3    50   Input ~ 0
4V5
$Comp
L power:+3.3V #PWR018
U 1 1 5FA3C324
P 10050 2800
F 0 "#PWR018" H 10050 2650 50  0001 C CNN
F 1 "+3.3V" V 10065 2928 50  0000 L CNN
F 2 "" H 10050 2800 50  0001 C CNN
F 3 "" H 10050 2800 50  0001 C CNN
	1    10050 2800
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR024
U 1 1 5FA3C6F0
P 8000 3750
F 0 "#PWR024" H 8000 3600 50  0001 C CNN
F 1 "+3.3V" H 8015 3923 50  0000 C CNN
F 2 "" H 8000 3750 50  0001 C CNN
F 3 "" H 8000 3750 50  0001 C CNN
	1    8000 3750
	-1   0    0    1   
$EndComp
Text GLabel 4550 4425 0    50   Input ~ 0
GYRO_INT
Text GLabel 8900 3325 2    50   Input ~ 0
GYRO_AUX_SDA
Text GLabel 8900 3425 2    50   Input ~ 0
GYRO_AUX_SCL
Text GLabel 6950 4550 2    50   Input ~ 0
MOTOR1_Signal
Text GLabel 6925 4975 2    50   Input ~ 0
MOTOR2_Signal
Text GLabel 6925 5425 2    50   Input ~ 0
MOTOR3_Signal
Text GLabel 6925 5850 2    50   Input ~ 0
MOTOR4_Signal
Text GLabel 3000 3650 0    50   Input ~ 0
SCL1
Text GLabel 3000 3750 0    50   Input ~ 0
SDA1
$Comp
L Device:R_Small R3
U 1 1 5FA7D2E3
P 3100 3550
F 0 "R3" H 3159 3596 50  0000 L CNN
F 1 "2.2k" H 3159 3505 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" H 3100 3550 50  0001 C CNN
F 3 "~" H 3100 3550 50  0001 C CNN
	1    3100 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R4
U 1 1 5FA7DE55
P 3400 3650
F 0 "R4" H 3459 3696 50  0000 L CNN
F 1 "2.2k" H 3459 3605 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" H 3400 3650 50  0001 C CNN
F 3 "~" H 3400 3650 50  0001 C CNN
	1    3400 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 3750 3400 3750
Wire Wire Line
	3000 3650 3100 3650
Wire Wire Line
	3100 3450 3400 3450
Wire Wire Line
	3400 3450 3400 3550
Text GLabel 9900 3750 3    50   Input ~ 0
GYRO_AUX_SDA
Text GLabel 10200 3750 3    50   Input ~ 0
GYRO_AUX_SCL
$Comp
L Device:R_Small R5
U 1 1 5FA96C2F
P 9900 3650
F 0 "R5" H 9959 3696 50  0000 L CNN
F 1 "2.2k" H 9959 3605 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" H 9900 3650 50  0001 C CNN
F 3 "~" H 9900 3650 50  0001 C CNN
	1    9900 3650
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R6
U 1 1 5FA9A352
P 10200 3650
F 0 "R6" H 10259 3696 50  0000 L CNN
F 1 "2.2k" H 10259 3605 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" H 10200 3650 50  0001 C CNN
F 3 "~" H 10200 3650 50  0001 C CNN
	1    10200 3650
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR022
U 1 1 5FA9AC22
P 9900 3550
F 0 "#PWR022" H 9900 3400 50  0001 C CNN
F 1 "+3.3V" H 9915 3723 50  0000 C CNN
F 2 "" H 9900 3550 50  0001 C CNN
F 3 "" H 9900 3550 50  0001 C CNN
	1    9900 3550
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR023
U 1 1 5FA9B4F4
P 10200 3550
F 0 "#PWR023" H 10200 3400 50  0001 C CNN
F 1 "+3.3V" H 10215 3723 50  0000 C CNN
F 2 "" H 10200 3550 50  0001 C CNN
F 3 "" H 10200 3550 50  0001 C CNN
	1    10200 3550
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Male J2
U 1 1 5FAA78D5
P 8475 2700
F 0 "J2" H 8575 3000 50  0000 C CNN
F 1 "UART1" H 8575 2925 50  0000 C CNN
F 2 "Connector_PinHeader_2.00mm:PinHeader_1x03_P2.00mm_Vertical" H 8475 2700 50  0001 C CNN
F 3 "~" H 8475 2700 50  0001 C CNN
	1    8475 2700
	1    0    0    -1  
$EndComp
Text GLabel 8675 2800 2    50   Input ~ 0
4V5
$Comp
L Connector:Conn_01x03_Male J4
U 1 1 5FABB3F1
P 9200 2725
F 0 "J4" H 9300 3025 50  0000 C CNN
F 1 "UART2" H 9300 2950 50  0000 C CNN
F 2 "Connector_PinHeader_2.00mm:PinHeader_1x03_P2.00mm_Vertical" H 9200 2725 50  0001 C CNN
F 3 "~" H 9200 2725 50  0001 C CNN
	1    9200 2725
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Male J3
U 1 1 5FAC49E0
P 9850 2700
F 0 "J3" H 9950 3000 50  0000 C CNN
F 1 "UART3" H 9950 2925 50  0000 C CNN
F 2 "Connector_PinHeader_2.00mm:PinHeader_1x03_P2.00mm_Vertical" H 9850 2700 50  0001 C CNN
F 3 "~" H 9850 2700 50  0001 C CNN
	1    9850 2700
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H2
U 1 1 5FA2FDB1
P 8000 3650
F 0 "H2" H 8100 3699 50  0000 L CNN
F 1 "3V3" H 8100 3608 50  0000 L CNN
F 2 "Connector_PinHeader_2.00mm:PinHeader_1x01_P2.00mm_Vertical" H 8000 3650 50  0001 C CNN
F 3 "~" H 8000 3650 50  0001 C CNN
	1    8000 3650
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male J5
U 1 1 5FADE1CE
P 8700 3325
F 0 "J5" H 8808 3506 50  0000 C CNN
F 1 "GYRO_AUX_I2C" H 8800 3425 50  0000 C CNN
F 2 "Connector_PinHeader_2.00mm:PinHeader_1x02_P2.00mm_Vertical" H 8700 3325 50  0001 C CNN
F 3 "~" H 8700 3325 50  0001 C CNN
	1    8700 3325
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male J6
U 1 1 5FAEC910
P 6750 4550
F 0 "J6" H 6650 4550 50  0000 C CNN
F 1 "S1" H 6650 4475 50  0000 C CNN
F 2 "Connector_PinHeader_2.00mm:PinHeader_1x02_P2.00mm_Vertical" H 6750 4550 50  0001 C CNN
F 3 "~" H 6750 4550 50  0001 C CNN
	1    6750 4550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR025
U 1 1 5FAF18B5
P 6950 4650
F 0 "#PWR025" H 6950 4400 50  0001 C CNN
F 1 "GND" H 6955 4477 50  0000 C CNN
F 2 "" H 6950 4650 50  0001 C CNN
F 3 "" H 6950 4650 50  0001 C CNN
	1    6950 4650
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male J7
U 1 1 5FAF3C9A
P 6725 4975
F 0 "J7" H 6600 4975 50  0000 C CNN
F 1 "S2" H 6600 4875 50  0000 C CNN
F 2 "Connector_PinHeader_2.00mm:PinHeader_1x02_P2.00mm_Vertical" H 6725 4975 50  0001 C CNN
F 3 "~" H 6725 4975 50  0001 C CNN
	1    6725 4975
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR029
U 1 1 5FAF3CA0
P 6925 5075
F 0 "#PWR029" H 6925 4825 50  0001 C CNN
F 1 "GND" H 6930 4902 50  0000 C CNN
F 2 "" H 6925 5075 50  0001 C CNN
F 3 "" H 6925 5075 50  0001 C CNN
	1    6925 5075
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male J8
U 1 1 5FAF7278
P 6725 5425
F 0 "J8" H 6625 5450 50  0000 C CNN
F 1 "S3" H 6625 5350 50  0000 C CNN
F 2 "Connector_PinHeader_2.00mm:PinHeader_1x02_P2.00mm_Vertical" H 6725 5425 50  0001 C CNN
F 3 "~" H 6725 5425 50  0001 C CNN
	1    6725 5425
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR032
U 1 1 5FAF727E
P 6925 5525
F 0 "#PWR032" H 6925 5275 50  0001 C CNN
F 1 "GND" H 6930 5352 50  0000 C CNN
F 2 "" H 6925 5525 50  0001 C CNN
F 3 "" H 6925 5525 50  0001 C CNN
	1    6925 5525
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR034
U 1 1 5FAFB818
P 6925 5950
F 0 "#PWR034" H 6925 5700 50  0001 C CNN
F 1 "GND" H 6930 5777 50  0000 C CNN
F 2 "" H 6925 5950 50  0001 C CNN
F 3 "" H 6925 5950 50  0001 C CNN
	1    6925 5950
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male J9
U 1 1 5FAFB812
P 6725 5850
F 0 "J9" H 6650 5850 50  0000 C CNN
F 1 "S4" H 6650 5750 50  0000 C CNN
F 2 "Connector_PinHeader_2.00mm:PinHeader_1x02_P2.00mm_Vertical" H 6725 5850 50  0001 C CNN
F 3 "~" H 6725 5850 50  0001 C CNN
	1    6725 5850
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H3
U 1 1 5FB28D21
P 8725 4725
F 0 "H3" V 8679 4875 50  0000 L CNN
F 1 "MountingHole" V 8770 4875 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 8725 4725 50  0001 C CNN
F 3 "~" H 8725 4725 50  0001 C CNN
	1    8725 4725
	0    1    1    0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H4
U 1 1 5FB2B72E
P 8725 4900
F 0 "H4" V 8679 5050 50  0000 L CNN
F 1 "MountingHole" V 8770 5050 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 8725 4900 50  0001 C CNN
F 3 "~" H 8725 4900 50  0001 C CNN
	1    8725 4900
	0    1    1    0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H5
U 1 1 5FB2E1AA
P 8725 5075
F 0 "H5" V 8679 5225 50  0000 L CNN
F 1 "MountingHole" V 8770 5225 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 8725 5075 50  0001 C CNN
F 3 "~" H 8725 5075 50  0001 C CNN
	1    8725 5075
	0    1    1    0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H6
U 1 1 5FB2E1B0
P 8725 5250
F 0 "H6" V 8679 5400 50  0000 L CNN
F 1 "MountingHole" V 8770 5400 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 8725 5250 50  0001 C CNN
F 3 "~" H 8725 5250 50  0001 C CNN
	1    8725 5250
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR030
U 1 1 5FB305FA
P 8550 5250
F 0 "#PWR030" H 8550 5000 50  0001 C CNN
F 1 "GND" H 8555 5077 50  0000 C CNN
F 2 "" H 8550 5250 50  0001 C CNN
F 3 "" H 8550 5250 50  0001 C CNN
	1    8550 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 5250 8625 5250
Wire Wire Line
	8550 5250 8550 5075
Wire Wire Line
	8550 5075 8625 5075
Connection ~ 8550 5250
Wire Wire Line
	8550 5075 8550 4900
Wire Wire Line
	8550 4900 8625 4900
Connection ~ 8550 5075
Wire Wire Line
	8550 4900 8550 4725
Wire Wire Line
	8550 4725 8625 4725
Connection ~ 8550 4900
$Comp
L power:GND #PWR019
U 1 1 5FB3EE82
P 9400 2825
F 0 "#PWR019" H 9400 2575 50  0001 C CNN
F 1 "GND" H 9405 2652 50  0000 C CNN
F 2 "" H 9400 2825 50  0001 C CNN
F 3 "" H 9400 2825 50  0001 C CNN
	1    9400 2825
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_MEC_5G SW1
U 1 1 5FB5436E
P 3475 2300
F 0 "SW1" H 3475 2585 50  0000 C CNN
F 1 "SW_MEC_5G" H 3475 2494 50  0000 C CNN
F 2 "Button_Switch_SMD_Personal:EVPBA" H 3475 2500 50  0001 C CNN
F 3 "http://www.apem.com/int/index.php?controller=attachment&id_attachment=488" H 3475 2500 50  0001 C CNN
	1    3475 2300
	1    0    0    -1  
$EndComp
Text GLabel 3275 2300 0    50   Input ~ 0
NRST
$Comp
L power:GND #PWR014
U 1 1 5FB721A8
P 3675 2300
F 0 "#PWR014" H 3675 2050 50  0001 C CNN
F 1 "GND" H 3680 2127 50  0000 C CNN
F 2 "" H 3675 2300 50  0001 C CNN
F 3 "" H 3675 2300 50  0001 C CNN
	1    3675 2300
	1    0    0    -1  
$EndComp
$Comp
L Memory_EEPROM:93CxxB U2
U 1 1 5FB7E39F
P 8450 1325
F 0 "U2" H 8225 1750 50  0000 C CNN
F 1 "93CxxB" H 8225 1675 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 8450 1325 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/20001749K.pdf" H 8450 1325 50  0001 C CNN
	1    8450 1325
	1    0    0    -1  
$EndComp
$Comp
L MCU_ST_STM32F1:STM32F103C8Tx U3
U 1 1 5F823D63
P 5250 3225
F 0 "U3" H 5350 3950 50  0000 C CNN
F 1 "STM32F103C8Tx" H 5350 4050 50  0000 C CNN
F 2 "Package_QFP:LQFP-48_7x7mm_P0.5mm" H 4650 1825 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/CD00161566.pdf" H 5250 3225 50  0001 C CNN
	1    5250 3225
	1    0    0    -1  
$EndComp
Text GLabel 8850 1425 2    50   Input ~ 0
MISO1
Text GLabel 8850 1325 2    50   Input ~ 0
MOSI1
Text GLabel 8050 1225 0    50   Input ~ 0
CS1
Text GLabel 8850 1225 2    50   Input ~ 0
SCK1
$Comp
L power:GND #PWR011
U 1 1 5FBAC969
P 8450 1625
F 0 "#PWR011" H 8450 1375 50  0001 C CNN
F 1 "GND" H 8455 1452 50  0000 C CNN
F 2 "" H 8450 1625 50  0001 C CNN
F 3 "" H 8450 1625 50  0001 C CNN
	1    8450 1625
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR04
U 1 1 5FBACF5B
P 8450 875
F 0 "#PWR04" H 8450 725 50  0001 C CNN
F 1 "+3.3V" H 8465 1048 50  0000 C CNN
F 2 "" H 8450 875 50  0001 C CNN
F 3 "" H 8450 875 50  0001 C CNN
	1    8450 875 
	1    0    0    -1  
$EndComp
$Comp
L Device:C C8
U 1 1 5FBAF166
P 8600 950
F 0 "C8" V 8425 1150 50  0000 C CNN
F 1 "100nF" V 8500 1150 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 8638 800 50  0001 C CNN
F 3 "~" H 8600 950 50  0001 C CNN
	1    8600 950 
	0    1    1    0   
$EndComp
Wire Wire Line
	8450 875  8450 950 
Connection ~ 8450 950 
Wire Wire Line
	8450 950  8450 1025
Wire Wire Line
	9250 950  9250 1625
Wire Wire Line
	9250 1625 8450 1625
Wire Wire Line
	8750 950  9250 950 
Connection ~ 8450 1625
Text GLabel 4550 3625 0    50   Input ~ 0
SCL1
Text GLabel 5850 4525 2    50   Input ~ 0
CS1
Text GLabel 4550 3325 0    50   Input ~ 0
SCK1
Text GLabel 4550 3425 0    50   Input ~ 0
MISO1
Text GLabel 4550 3525 0    50   Input ~ 0
MOSI1
NoConn ~ 5850 3425
NoConn ~ 5850 3525
Wire Wire Line
	2300 1200 2760 1200
$Comp
L power:+3.3V #PWR021
U 1 1 5FA85727
P 3100 3425
F 0 "#PWR021" H 3100 3275 50  0001 C CNN
F 1 "+3.3V" H 3115 3598 50  0000 C CNN
F 2 "" H 3100 3425 50  0001 C CNN
F 3 "" H 3100 3425 50  0001 C CNN
	1    3100 3425
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 3450 3100 3425
Connection ~ 3100 3450
NoConn ~ 4550 3825
$Comp
L power:+5V #PWR0101
U 1 1 5FC39363
P 7575 2300
F 0 "#PWR0101" H 7575 2150 50  0001 C CNN
F 1 "+5V" V 7590 2428 50  0000 L CNN
F 2 "" H 7575 2300 50  0001 C CNN
F 3 "" H 7575 2300 50  0001 C CNN
	1    7575 2300
	0    1    1    0   
$EndComp
$EndSCHEMATC
