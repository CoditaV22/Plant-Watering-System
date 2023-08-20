**Automated Plant Watering System**

**Key Components:**
- ATmega164 MCU
- 1602 LCD
- Water Level Sensor
- Soil Moisture Sensor
- Relay Module
- Mini Water-Pump

**Description**

Using the ATmega164 MCU I decided to implement a self watering system that detects the soil moisture of a plant, depending of which, activates the relay module which, connected to a mini-water pump, waters the plant. I also decided to make use of a water-level sensor in order give us alerts to fill up the water container.

The MCU reads the ADC values of the sensors and sends the signal to the relay module. After, it goes into power-saving mode for 1 minute, when it is woken up by a counter which increments at each 1ms with the use of Timer2 Overflow ISR.


**DEMONSTRATION:**https://www.youtube.com/shorts/HQkldGFYNVA



_Note:_ In the demo video , the time interval from sleep mode to waking up is lowered so I can record. Also , in the demo-code the relay activates no matter the moisture threshold. That is because when I ran the tests before recording, the soil filled with water thus increasing its moisture. 


  
