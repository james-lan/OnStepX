// -----------------------------------------------------------------------------------
// Time/Location source TEENSY 3.2 RTC support

#include "../../Common.h"

#if TIME_LOCATION_SOURCE == TEENSY

#include "Tls_Teensy.h"

#include <TimeLib.h> // https://github.com/PaulStoffregen/Time/archive/master.zip

bool TimeLocationSource::init() {
  ready = true;
  return ready;
}

void TimeLocationSource::set(JulianDate ut1) {
    
  GregorianDate greg = calendars.julianDayToGregorian(ut1);
  greg.year -= 2000;
  if (greg.year >= 100) greg.year -= 100;

  double f1 = fabs(ut1.hour) + TLS_CLOCK_SKEW;
  int h = floor(f1);
  double m = (f1 - h)*60.0;
  double s = (m - floor(m))*60.0;

  setTime(h, floor(m), floor(s), greg.day, greg.month, greg.year);   // set current system time

  unsigned long TeensyTime;
  TeensyTime = now();                         // get time in epoch
  Teensy3Clock.set(TeensyTime);               // set Teensy time
}

void TimeLocationSource::get(JulianDate &ut1) {
  unsigned long TeensyTime;

  TeensyTime = Teensy3Clock.get();            // get time from Teensy RTC
  setTime(TeensyTime);                        // set system time

  if (year() >= 0 && year() <= 3000 && month() >= 1 && month() <= 12 && day() >= 1 && day() <= 31 &&
      hour() <= 23 && minute() <= 59 && second() <= 59) {
    GregorianDate greg; greg.year = year(); greg.month = month(); greg.day = day();
    ut1 = calendars.gregorianToJulianDay(greg);
    ut1.hour = hour() + minute()/60.0 + second()/3600.0;
  }
}

TimeLocationSource tls;

#endif