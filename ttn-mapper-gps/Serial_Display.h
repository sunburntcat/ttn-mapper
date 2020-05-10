/*
 * serial_display.h - Helper class for Serial display
 *
 * (refactored from OLED_Display.h)
 *
 */

#ifndef _serial_display_h
#define _serial_display_h

// Class definition
class Serial_Display
{
  protected:
    s4_t _uptime( void );
    uint32_t _sent;
    uint32_t _error;
    uint32_t _complete;

  public:
    // Constructor
    Serial_Display ( int reset = -1 )
    {
      _sent = 0;
      _error = 0;
      _complete = 0;
    }

    void update ( void );
    String hms(ostime_t t);
    String gps_time( void );
    void addSent ( void );
    void addError ( void );
    void addComplete ( void );
};


#endif /* _serial_display_h */
