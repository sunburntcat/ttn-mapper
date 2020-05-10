/*
 * Serial_Display.cpp - Helper class for Serial output
 *
 */

#include "OLED_Display.h"  // Just in case old oled functions are needed
#include "Serial_Display.h"
#include "gps.h"

// Converts an "os time" to a String: "hh:mm:ss"
String Serial_Display::hms(ostime_t t) {
  s4_t h, m, s;
  String txt;

  s = osticks2ms(t) / 1000;
  m = s / 60;
  s -= m * 60;
  h = m / 60;
  m -= h * 60;

  txt = String(h);
  txt += String(m < 10 ? ":0" : ":");
  txt += String(m);
  txt += String(s < 10 ? ":0" : ":");
  txt += String (s);

  return txt;
}

// Converts GPS time to a String: "hh:mm:ss"
String Serial_Display::gps_time( void ) {
  String txt;

  txt = String(GPS.hour < 10 ? "0" : "");
  txt += String(GPS.hour);
  txt += String(GPS.minute < 10 ? ":0" : ":");
  txt += String(GPS.minute);
  txt += String(GPS.seconds < 10 ? ":0" : ":");
  txt += String (GPS.seconds);

  return txt;
}

// Returns the uptime in seconds
s4_t Serial_Display::_uptime( void )
{
  return osticks2ms(os_getTime()) / 1000;
}

// Increments sent counter
void Serial_Display::addSent ( void )
{
  _sent++;
}

// Increments error counter
void Serial_Display::addError ( void )
{
  _error++;
}

// Increments Send complete counter
void Serial_Display::addComplete ( void )
{
  _complete++;
}

// Updates top / Bottom status lines
void Serial_Display::update ( void )
{
  s4_t uptime;
  s4_t h, m, s;

  // Check for new GPS data
  if (GPS.newNMEAreceived()) {
    GPS.parse(GPS.lastNMEA());
  }

  Serial.println("Sent:");
  Serial.print(_sent);
  Serial.println(" Complete:");
  Serial.print(_complete);
  Serial.println(" Errors:");
  Serial.print(_error);

  Serial.println(gps_time());
  Serial.println(" Fix Quality:");
  Serial.print(GPS.fixquality);
  Serial.println(" Satellites:");
  Serial.print(GPS.satellites);

}
