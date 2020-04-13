EESchema Schematic File Version 4
LIBS:Klokpulser 2.1-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 3
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Diode:1N4007 D?
U 1 1 5C1F1A76
P 5500 3000
AR Path="/5C1F1A76" Ref="D?"  Part="1" 
AR Path="/5C1E93EA/5C1F1A76" Ref="D3"  Part="1" 
AR Path="/5C259D75/5C1F1A76" Ref="D7"  Part="1" 
F 0 "D3" V 5500 2800 50  0000 L CNN
F 1 "B0540W" V 5400 2650 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 5500 2825 50  0001 C CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30138.pdf" H 5500 3000 50  0001 C CNN
	1    5500 3000
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5C1F1A7D
P 4450 2800
AR Path="/5C1F1A7D" Ref="R?"  Part="1" 
AR Path="/5C1E93EA/5C1F1A7D" Ref="R11"  Part="1" 
AR Path="/5C259D75/5C1F1A7D" Ref="R21"  Part="1" 
F 0 "R11" H 4200 2850 50  0000 L CNN
F 1 "10k" H 4200 2750 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4380 2800 50  0001 C CNN
F 3 "~" H 4450 2800 50  0001 C CNN
	1    4450 2800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5C1F1A84
P 4450 3200
AR Path="/5C1F1A84" Ref="R?"  Part="1" 
AR Path="/5C1E93EA/5C1F1A84" Ref="R12"  Part="1" 
AR Path="/5C259D75/5C1F1A84" Ref="R22"  Part="1" 
F 0 "R12" H 4200 3250 50  0000 L CNN
F 1 "10k" H 4200 3150 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4380 3200 50  0001 C CNN
F 3 "~" H 4450 3200 50  0001 C CNN
	1    4450 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 2950 4450 3000
Wire Wire Line
	4600 3000 4450 3000
Connection ~ 4450 3000
Wire Wire Line
	4450 3000 4450 3050
Wire Wire Line
	4450 2650 4450 2550
Wire Wire Line
	4450 2550 4900 2550
Wire Wire Line
	5100 2550 5100 2850
Wire Wire Line
	4900 2800 4900 2550
Connection ~ 4900 2550
Wire Wire Line
	4900 2550 5100 2550
Wire Wire Line
	5100 2550 5500 2550
Wire Wire Line
	5500 2550 5500 2850
Connection ~ 5100 2550
Wire Wire Line
	5500 2550 5700 2550
Wire Wire Line
	5700 2550 5700 2800
Connection ~ 5500 2550
Wire Wire Line
	4900 3200 4900 3350
Wire Wire Line
	4900 3350 5100 3350
Wire Wire Line
	5100 3350 5100 3150
Wire Wire Line
	5500 3150 5500 3350
Wire Wire Line
	5500 3350 5700 3350
Wire Wire Line
	5700 3350 5700 3200
$Comp
L Device:R R?
U 1 1 5C1F1AA1
P 6200 2800
AR Path="/5C1F1AA1" Ref="R?"  Part="1" 
AR Path="/5C1E93EA/5C1F1AA1" Ref="R13"  Part="1" 
AR Path="/5C259D75/5C1F1AA1" Ref="R23"  Part="1" 
F 0 "R13" H 6250 2850 50  0000 L CNN
F 1 "10k" H 6250 2750 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 6130 2800 50  0001 C CNN
F 3 "~" H 6200 2800 50  0001 C CNN
	1    6200 2800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5C1F1AA8
P 6200 3200
AR Path="/5C1F1AA8" Ref="R?"  Part="1" 
AR Path="/5C1E93EA/5C1F1AA8" Ref="R14"  Part="1" 
AR Path="/5C259D75/5C1F1AA8" Ref="R24"  Part="1" 
F 0 "R14" H 6250 3250 50  0000 L CNN
F 1 "10k" H 6250 3150 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 6130 3200 50  0001 C CNN
F 3 "~" H 6200 3200 50  0001 C CNN
	1    6200 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 2550 6200 2550
Wire Wire Line
	6200 2550 6200 2650
Connection ~ 5700 2550
Wire Wire Line
	6000 3000 6200 3000
Wire Wire Line
	6200 3000 6200 2950
Wire Wire Line
	6200 3050 6200 3000
Connection ~ 6200 3000
$Comp
L power:GND #PWR?
U 1 1 5C1F1AC4
P 4450 3850
AR Path="/5C1F1AC4" Ref="#PWR?"  Part="1" 
AR Path="/5C1E93EA/5C1F1AC4" Ref="#PWR0101"  Part="1" 
AR Path="/5C259D75/5C1F1AC4" Ref="#PWR0115"  Part="1" 
F 0 "#PWR0101" H 4450 3600 50  0001 C CNN
F 1 "GND" H 4455 3677 50  0000 C CNN
F 2 "" H 4450 3850 50  0001 C CNN
F 3 "" H 4450 3850 50  0001 C CNN
	1    4450 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 3850 4450 3800
Wire Wire Line
	4900 3900 4900 3800
Connection ~ 4900 3350
$Comp
L Device:R R?
U 1 1 5C1F1ACD
P 3950 3600
AR Path="/5C1F1ACD" Ref="R?"  Part="1" 
AR Path="/5C1E93EA/5C1F1ACD" Ref="R9"  Part="1" 
AR Path="/5C259D75/5C1F1ACD" Ref="R19"  Part="1" 
F 0 "R9" V 3850 3450 50  0000 L CNN
F 1 "10k" V 3750 3450 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3880 3600 50  0001 C CNN
F 3 "~" H 3950 3600 50  0001 C CNN
	1    3950 3600
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5C1F1AD4
P 4200 4100
AR Path="/5C1F1AD4" Ref="R?"  Part="1" 
AR Path="/5C1E93EA/5C1F1AD4" Ref="R10"  Part="1" 
AR Path="/5C259D75/5C1F1AD4" Ref="R20"  Part="1" 
F 0 "R10" V 4100 4000 50  0000 L CNN
F 1 "10k" V 4000 4000 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4130 4100 50  0001 C CNN
F 3 "~" H 4200 4100 50  0001 C CNN
	1    4200 4100
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5C1F1ADB
P 3900 4300
AR Path="/5C1F1ADB" Ref="R?"  Part="1" 
AR Path="/5C1E93EA/5C1F1ADB" Ref="R8"  Part="1" 
AR Path="/5C259D75/5C1F1ADB" Ref="R18"  Part="1" 
F 0 "R8" H 3650 4350 50  0000 L CNN
F 1 "10k" H 3650 4250 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3830 4300 50  0001 C CNN
F 3 "~" H 3900 4300 50  0001 C CNN
	1    3900 4300
	-1   0    0    1   
$EndComp
Wire Wire Line
	3900 4450 3900 4550
Wire Wire Line
	3900 4550 4900 4550
Wire Wire Line
	4900 4550 4900 4300
Wire Wire Line
	4600 4100 4350 4100
Wire Wire Line
	3800 3600 3700 3600
Wire Wire Line
	4050 4100 3900 4100
Wire Wire Line
	3900 4150 3900 4100
Connection ~ 3900 4100
Wire Wire Line
	3900 4100 3700 4100
Wire Wire Line
	4450 3400 4450 3350
Wire Wire Line
	4150 3600 4100 3600
Wire Wire Line
	4900 4550 5100 4550
Wire Wire Line
	5100 4550 5100 4250
Connection ~ 4900 4550
Wire Wire Line
	5100 3950 5100 3800
Wire Wire Line
	5100 3800 4900 3800
Connection ~ 4900 3800
Wire Wire Line
	5100 4550 5300 4550
Wire Wire Line
	5700 4550 5700 4300
Connection ~ 5100 4550
Wire Wire Line
	5500 4250 5500 4550
Connection ~ 5500 4550
Wire Wire Line
	5500 4550 5700 4550
Wire Wire Line
	5500 3950 5500 3800
Wire Wire Line
	5700 3800 5700 3900
Connection ~ 5700 3350
Connection ~ 5700 3800
Wire Wire Line
	4900 3500 5100 3500
Wire Wire Line
	5650 3800 5700 3800
Wire Wire Line
	5500 3800 5700 3800
$Comp
L power:GND #PWR?
U 1 1 5C1F1B23
P 6200 3850
AR Path="/5C1F1B23" Ref="#PWR?"  Part="1" 
AR Path="/5C1E93EA/5C1F1B23" Ref="#PWR0102"  Part="1" 
AR Path="/5C259D75/5C1F1B23" Ref="#PWR0116"  Part="1" 
F 0 "#PWR0102" H 6200 3600 50  0001 C CNN
F 1 "GND" H 6205 3677 50  0000 C CNN
F 2 "" H 6200 3850 50  0001 C CNN
F 3 "" H 6200 3850 50  0001 C CNN
	1    6200 3850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5C1F1B29
P 6700 3600
AR Path="/5C1F1B29" Ref="R?"  Part="1" 
AR Path="/5C1E93EA/5C1F1B29" Ref="R16"  Part="1" 
AR Path="/5C259D75/5C1F1B29" Ref="R26"  Part="1" 
F 0 "R16" V 6600 3500 50  0000 L CNN
F 1 "10k" V 6500 3500 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 6630 3600 50  0001 C CNN
F 3 "~" H 6700 3600 50  0001 C CNN
	1    6700 3600
	0    1    1    0   
$EndComp
Wire Wire Line
	6200 3400 6200 3350
Wire Wire Line
	6500 3600 6550 3600
Wire Wire Line
	6200 3800 6200 3850
Wire Wire Line
	6850 3600 6950 3600
$Comp
L Device:R R?
U 1 1 5C1F1B34
P 6450 4100
AR Path="/5C1F1B34" Ref="R?"  Part="1" 
AR Path="/5C1E93EA/5C1F1B34" Ref="R15"  Part="1" 
AR Path="/5C259D75/5C1F1B34" Ref="R25"  Part="1" 
F 0 "R15" V 6250 4000 50  0000 L CNN
F 1 "10k" V 6350 4000 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 6380 4100 50  0001 C CNN
F 3 "~" H 6450 4100 50  0001 C CNN
	1    6450 4100
	0    1    1    0   
$EndComp
Wire Wire Line
	6300 4100 6000 4100
$Comp
L Device:R R?
U 1 1 5C1F1B3C
P 6750 4300
AR Path="/5C1F1B3C" Ref="R?"  Part="1" 
AR Path="/5C1E93EA/5C1F1B3C" Ref="R17"  Part="1" 
AR Path="/5C259D75/5C1F1B3C" Ref="R27"  Part="1" 
F 0 "R17" H 6500 4350 50  0000 L CNN
F 1 "10k" H 6500 4250 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 6680 4300 50  0001 C CNN
F 3 "~" H 6750 4300 50  0001 C CNN
	1    6750 4300
	-1   0    0    1   
$EndComp
Wire Wire Line
	5700 4550 6750 4550
Wire Wire Line
	6750 4550 6750 4450
Connection ~ 5700 4550
Wire Wire Line
	6600 4100 6750 4100
Wire Wire Line
	6750 4150 6750 4100
Connection ~ 6750 4100
Wire Wire Line
	6750 4100 6950 4100
Wire Wire Line
	6200 2550 6400 2550
Wire Wire Line
	6400 2550 6400 2400
Connection ~ 6200 2550
$Comp
L power:+24V #PWR?
U 1 1 5C1F1B4D
P 6400 2400
AR Path="/5C1F1B4D" Ref="#PWR?"  Part="1" 
AR Path="/5C1E93EA/5C1F1B4D" Ref="#PWR0103"  Part="1" 
AR Path="/5C259D75/5C1F1B4D" Ref="#PWR0117"  Part="1" 
F 0 "#PWR0103" H 6400 2250 50  0001 C CNN
F 1 "+24V" H 6415 2573 50  0000 C CNN
F 2 "" H 6400 2400 50  0001 C CNN
F 3 "" H 6400 2400 50  0001 C CNN
	1    6400 2400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C1F1B59
P 5300 4600
AR Path="/5C1F1B59" Ref="#PWR?"  Part="1" 
AR Path="/5C1E93EA/5C1F1B59" Ref="#PWR0104"  Part="1" 
AR Path="/5C259D75/5C1F1B59" Ref="#PWR0118"  Part="1" 
F 0 "#PWR0104" H 5300 4350 50  0001 C CNN
F 1 "GND" H 5305 4427 50  0000 C CNN
F 2 "" H 5300 4600 50  0001 C CNN
F 3 "" H 5300 4600 50  0001 C CNN
	1    5300 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 4600 5300 4550
Connection ~ 5300 4550
Wire Wire Line
	5300 4550 5500 4550
Text HLabel 6950 3600 2    50   Input ~ 0
INPUT_A
Text HLabel 6950 4100 2    50   Input ~ 0
INPUT_B
Text HLabel 3700 4100 0    50   Input ~ 0
INPUT_A
Text HLabel 3700 3600 0    50   Input ~ 0
INPUT_B
Connection ~ 4900 3500
Wire Wire Line
	4900 3500 4900 3350
Wire Wire Line
	4900 3500 4900 3800
Wire Wire Line
	5700 3600 5700 3800
Wire Wire Line
	5700 3350 5700 3600
Connection ~ 5700 3600
Wire Wire Line
	5700 3600 5500 3600
Text HLabel 5100 3500 2    50   Input ~ 0
OUT_B
Text HLabel 5500 3600 0    50   Input ~ 0
OUT_A
$Comp
L Diode:1N4007 D?
U 1 1 5C420521
P 5100 3000
AR Path="/5C420521" Ref="D?"  Part="1" 
AR Path="/5C1E93EA/5C420521" Ref="D1"  Part="1" 
AR Path="/5C259D75/5C420521" Ref="D5"  Part="1" 
F 0 "D1" V 5350 3000 50  0000 L CNN
F 1 "B0540W" V 5250 3000 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 5100 2825 50  0001 C CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30138.pdf" H 5100 3000 50  0001 C CNN
	1    5100 3000
	0    1    1    0   
$EndComp
$Comp
L Diode:1N4007 D?
U 1 1 5C4205FC
P 5100 4100
AR Path="/5C4205FC" Ref="D?"  Part="1" 
AR Path="/5C1E93EA/5C4205FC" Ref="D2"  Part="1" 
AR Path="/5C259D75/5C4205FC" Ref="D6"  Part="1" 
F 0 "D2" V 5350 4150 50  0000 L CNN
F 1 "B0540W" V 5250 4150 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 5100 3925 50  0001 C CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30138.pdf" H 5100 4100 50  0001 C CNN
	1    5100 4100
	0    1    1    0   
$EndComp
$Comp
L Diode:1N4007 D?
U 1 1 5C42071F
P 5500 4100
AR Path="/5C42071F" Ref="D?"  Part="1" 
AR Path="/5C1E93EA/5C42071F" Ref="D4"  Part="1" 
AR Path="/5C259D75/5C42071F" Ref="D8"  Part="1" 
F 0 "D4" V 5500 3900 50  0000 L CNN
F 1 "B0540W" V 5400 3750 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 5500 3925 50  0001 C CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30138.pdf" H 5500 4100 50  0001 C CNN
	1    5500 4100
	0    1    1    0   
$EndComp
$Comp
L Transistor_BJT:BC547 Q5
U 1 1 5D73204A
P 4800 4100
AR Path="/5C1E93EA/5D73204A" Ref="Q5"  Part="1" 
AR Path="/5C259D75/5D73204A" Ref="Q11"  Part="1" 
F 0 "Q5" H 4550 3900 50  0000 L CNN
F 1 "BC547" H 4550 3800 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 5000 4025 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC547.pdf" H 4800 4100 50  0001 L CNN
	1    4800 4100
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:BC547 Q7
U 1 1 5D7322CB
P 5800 4100
AR Path="/5C1E93EA/5D7322CB" Ref="Q7"  Part="1" 
AR Path="/5C259D75/5D7322CB" Ref="Q13"  Part="1" 
F 0 "Q7" H 5700 3900 50  0000 L CNN
F 1 "BC547" H 5550 3800 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 6000 4025 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC547.pdf" H 5800 4100 50  0001 L CNN
	1    5800 4100
	-1   0    0    -1  
$EndComp
$Comp
L Transistor_BJT:BC547 Q8
U 1 1 5D7325FC
P 6300 3600
AR Path="/5C1E93EA/5D7325FC" Ref="Q8"  Part="1" 
AR Path="/5C259D75/5D7325FC" Ref="Q14"  Part="1" 
F 0 "Q8" H 6490 3646 50  0000 L CNN
F 1 "BC547" H 6490 3555 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 6500 3525 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC547.pdf" H 6300 3600 50  0001 L CNN
	1    6300 3600
	-1   0    0    -1  
$EndComp
$Comp
L Transistor_BJT:BC547 Q3
U 1 1 5D732875
P 4350 3600
AR Path="/5C1E93EA/5D732875" Ref="Q3"  Part="1" 
AR Path="/5C259D75/5D732875" Ref="Q9"  Part="1" 
F 0 "Q3" H 4541 3646 50  0000 L CNN
F 1 "BC547" H 4541 3555 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 4550 3525 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC547.pdf" H 4350 3600 50  0001 L CNN
	1    4350 3600
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:BC557 Q4
U 1 1 5D732E5E
P 4800 3000
AR Path="/5C1E93EA/5D732E5E" Ref="Q4"  Part="1" 
AR Path="/5C259D75/5D732E5E" Ref="Q10"  Part="1" 
F 0 "Q4" H 4600 2650 50  0000 L CNN
F 1 "BC557" H 4600 2750 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 5000 2925 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC557.pdf" H 4800 3000 50  0001 L CNN
	1    4800 3000
	1    0    0    1   
$EndComp
$Comp
L Transistor_BJT:BC557 Q6
U 1 1 5D732F66
P 5800 3000
AR Path="/5C1E93EA/5D732F66" Ref="Q6"  Part="1" 
AR Path="/5C259D75/5D732F66" Ref="Q12"  Part="1" 
F 0 "Q6" H 5650 2650 50  0000 L CNN
F 1 "BC557" H 5500 2750 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 6000 2925 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC557.pdf" H 5800 3000 50  0001 L CNN
	1    5800 3000
	-1   0    0    1   
$EndComp
$EndSCHEMATC
