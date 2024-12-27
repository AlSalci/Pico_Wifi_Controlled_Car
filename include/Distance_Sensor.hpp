#include "pico/stdio.h"



class distance_sensor 
{


private:



public:
/*
@Initializes the GPIOs that will be connected to the ultrasonic sensor. Addiitonally sets up system interrupts
@Params- 
@Echo- Echo pin GPIO
@Trigger- Trigger pin gpio
@Callback - Callback function for system interrupt.NOT IMPLEMENTED, IRQ handling set up in main for now
@Return- None 
*/
distance_sensor(uint &echo,uint &trigger,void (*callback)(uint,uint32_t));
uint echo,trigger;

uint time_at_rise,time_at_fall;

/*
@Sets the time that was seen at the rising edge of the distance sensor echo pin
@Params- None
@Return- None 
*/
void set_time_at_rise();
/*
@Sets the time that was seen at the falling edge of the distance sensor echo pin
@Params- None
@Return- None 
*/
void set_time_at_fall();
/*
@Tiggers the ultrasonic sensor by toggling the trigger pin High then Low 
@Params- None
@Return- None 
*/
void trigger_sensor();

/*
@Calculates the distance of the object in front of the sensor 
@Params- None
@Return- The distance calculated from the ultrasonic sensor 
*/
uint calculate_distance_cm();


};