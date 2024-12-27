#include "../include/Distance_Sensor.hpp"
#include "hardware/gpio.h"
#include "pico/time.h"
#include "pico/types.h"




distance_sensor::distance_sensor(uint &echo,uint &trigger,void (*callback)(uint,uint32_t))
{
gpio_init(echo);
gpio_init(trigger);

gpio_set_dir(trigger, GPIO_OUT);
gpio_set_dir(echo, GPIO_IN);

gpio_put(trigger, 0);
gpio_pull_down(echo);

this->trigger = trigger;
this->echo = echo;


}



void distance_sensor::set_time_at_rise()
{
time_at_rise = to_us_since_boot(get_absolute_time());

}

void distance_sensor::set_time_at_fall()
{

time_at_fall = to_us_since_boot(get_absolute_time());

}

void distance_sensor::trigger_sensor()
{
    gpio_put(trigger,1);
    sleep_us(10);
    gpio_put(trigger, 0);
}

uint distance_sensor::calculate_distance_cm()
{
return (time_at_fall-time_at_rise)/58;
}