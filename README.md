# SOS-Call-Based-System
This project implements an SOS call system using Arduino. It is designed to send an emergency distress signal (SOS) to predefined contacts when activated. This can be a crucial safety feature in situations where immediate help is required.

Architecture of the circuit
![Screenshot_20230827_132913](https://github.com/amandeepsirohi/SOS-Call-Based-System/assets/125798090/89dba9b2-d4df-4e0b-bafd-0a8ebef643b3)


## Usage
clone the repo
```console
git clone https://github.com/amandeepsirohi/SOS-Call-Based-System.git 
```



## Components Required
> -  Arduino board (e.g., Arduino Uno)<br/> 
> -  GSM module (e.g., SIM900)<br/> 
> - GPS module (optional, for location tracking)<br/> 
> - Push button or trigger sensor<br/> 
> - Power source (battery or power supply)<br/> 
> - SIM card with active plan<br/> 
> - Required connectors and cables<br/> 

## Wiring
> - Connect the GSM module to the Arduino using appropriate pins (TX, RX, VCC, GND).<br/> 
> - Connect the GPS module in a similar fashion if used.<br/> 
> - Wire the push button to an Arduino pin for activation.<br/> 

## Installation and Setup
> - Connect all the components according to the wiring diagram.<br/> 
> - Insert a valid SIM card into the GSM module.<br/> 
> - Load the provided Arduino sketch onto the board using the Arduino IDE.<br/> 
> - Ensure that the GSM and GPS modules are powered up and properly connected.<br/> 
> - Upload the code to the Arduino.<br/> 

## Usage
> - Power up the Arduino with the required power source.<br/> 
> - Press the push button to trigger the SOS call.<br/> 
> - The GSM module will establish a connection and send an SOS message to predefined contacts.<br/> 
> - Optionally, if a GPS module is connected, the location coordinates can be included in the SOS message.<br/> 
