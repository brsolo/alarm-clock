# alarm-clock

Code for a custom alarm clock using arduino

As configured, at 6:30am LED will turn on. If you wake up after 6:30am naturally, you will see the LED on and know to wake-up. At 7:00am, the LED blinks. At 8:30am the LED turns off.

Using a DS3231 for keeping track of time, an LCD1602 for display, a green LED, and a 5 kΩ resistor.

Wiring the LCD1602 to Arduino Uno:
  
  LCD RS pin to digital pin 12
  LCD Enable pin to digital pin 11
  LCD D4 pin to digital pin 5
  LCD D5 pin to digital pin 4
  LCD D6 pin to digital pin 3
  LCD D7 pin to digital pin 2
  LCD R/W pin to GND
  LCD VSS pin to GND
  LCD VCC pin to 5V
  LCD LED+ to 5V through a 220 ohm resistor
  LCD LED- to GND

Wiring DS32131 to Arduino Uno:

  SCL to A5
  SDA to A4
  VCC to 5V
  GND to GND

Wiring for LED that is in series with 5 kΩ resistor:

  + to digital pin 13
  - to GND
