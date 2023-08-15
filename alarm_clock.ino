#include <RTClib.h>
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// set alarm times
uint8_t start_time_hr = 6;
uint8_t start_time_min = 30;
DateTime start_time;

uint8_t alarm_time_hr = 7;
uint8_t alarm_time_min = 0;
DateTime alarm_time;

uint8_t end_time_hr = 8;
uint8_t end_time_min = 30;
DateTime end_time;

RTC_DS3231 rtc;
void printTime(DateTime now);

char daysOfTheWeek[7][12] = {
  "Sunday",
  "Monday",
  "Tuesday",
  "Wednesday",
  "Thursday",
  "Friday",
  "Saturday"
};

String status;

void setup () {
  Serial.begin(9600);

  // setup RTC
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1);
  }

  // automatically sets the RTC to the date & time on PC this sketch was compiled
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  // initialize LED
  pinMode(LED_BUILTIN, OUTPUT);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // clear LCD
  lcd.clear();
  

}

void loop () {
  DateTime now = rtc.now();

  // printTime(now);
  // printTime(start_time);
  // Serial.println(now > start_time);
  // Serial.println(now < alarm_time);
  // Serial.println(now > alarm_time);
  // Serial.println(now < end_time);

  lcd.setCursor(0, 0);
  lcd.print("Now:   ");
  if (now.hour() < 10){
    lcd.print(" ");
  }
  lcd.print(now.hour());
  lcd.print(":");
  if (now.minute() < 10){
    lcd.print("0");
  }
  lcd.print(now.minute());

  lcd.setCursor(0, 1);
  lcd.print("Alarm: ");
  if (alarm_time_hr < 10){
    lcd.print(" ");
  }
  lcd.print(alarm_time_hr);
  lcd.print(":");
  if (alarm_time_min < 10){
    lcd.print("0");
  }
  lcd.print(alarm_time_min);

  status = checkAlarm(now);

  if (status == "warning"){
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(1000);                      // wait for a second
  }
  else if (status == "on")
  {
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(500);                      // wait for a second
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
    delay(500);                      // wait for a second
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000); // delay 1 seconds
  }

}



void printTime(DateTime time) {
  Serial.print("Current time: ");
  Serial.print(time.year(), DEC);
  Serial.print('/');
  Serial.print(time.month(), DEC);
  Serial.print('/');
  Serial.print(time.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[time.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(time.hour(), DEC);
  Serial.print(':');
  Serial.print(time.minute(), DEC);
  Serial.print(':');
  Serial.println(time.second(), DEC);
}

String checkAlarm(DateTime now) {

  DateTime start_time = DateTime(now.year(), now.month(), now.day(), start_time_hr, start_time_min, 0);
  DateTime alarm_time = DateTime(now.year(), now.month(), now.day(), alarm_time_hr, alarm_time_min, 0);
  DateTime end_time = DateTime(now.year(), now.month(), now.day(), end_time_hr, end_time_min, 0);


  if ( // case where light should be on but not alarm yet
    now > start_time &&
    now < alarm_time
    ) {
      Serial.println("warning");
      return "warning";
  } 
  else if (
    now >= alarm_time &&
    now < end_time

  ) {
      Serial.println("on");
      return "on";
  }
  else {
      Serial.println("off");
      return "off";
  }

}