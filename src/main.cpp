#include <iostream>
#include "../include/Wifi.hpp"
#include "hardware/i2c.h"
#include "lwipopts.h"
#include "hardware/gpio.h"
#include "pico/stdio.h"
#include "pico/time.h"
#include "../include/Distance_Sensor.hpp"

//#include "../include/motors.hpp"





const char WIFI_SSID[] = "XXX"; //WIFI NAME
const char WIFI_PASSWORD[] = "XXX"; //WIFI Password

 //std::vector<uint> stepper::pins = {12,13,14,15};

MOTOR_STATE motor::motor_state = STOP;
uint left_wheel = 14,right_wheel = 15;
motor motor(left_wheel,right_wheel);
server ser;

uint connection_LED = 16;
void connection_LED_init();
void connection_LED_on();
void connection_LED_off();


void callback(uint gpio,uint32_t event);
void interrupt_initialize(uint gpio,void (*callback)(uint,uint32_t));


uint echo = 17,trigger = 18;
distance_sensor sensor(echo,trigger,callback);




int main()
{
    stdio_init_all();

    //Assurs connection light is off until device connects to the internet
    connection_LED_init();
    connection_LED_off();
    //=======================================================================

    interrupt_initialize(sensor.echo,callback);

    sleep_ms(1000);
    ser.server_initialization(WIFI_SSID,WIFI_PASSWORD);
    connection_LED_on();
    
   
    while(true)
    {
    motor.motor_state_machine();
    sensor.trigger_sensor();
    printf("Distance %d\n",sensor.calculate_distance_cm());


if((sensor.calculate_distance_cm() < 30) && motor::motor_state == FORWARD)
{
    motor::motor_state = STOP;
}


//printf("%d\n",gpio_get(left_wheel));
//printf("%d\n",gpio_get(right_wheel));
sleep_ms(10);
       
       

     
    }
    return 0;

}





void connection_LED_init()
{
    gpio_init(connection_LED);
    gpio_set_dir(connection_LED, GPIO_OUT);
    gpio_put(connection_LED,0);

}


void connection_LED_on()
{
    gpio_put(connection_LED,1);
}
void connection_LED_off()
{
    gpio_put(connection_LED,0);
}

void callback(uint gpio,uint32_t event)
{
   // printf("Working IRQ\n");
    switch(event)
    {
        case GPIO_IRQ_EDGE_RISE:
        sensor.set_time_at_rise();
        break;

        case GPIO_IRQ_EDGE_FALL:
        sensor.set_time_at_fall();
        
        break;
    }
}

void interrupt_initialize(uint gpio,void (*callback)(uint,uint32_t))
{

gpio_set_irq_enabled_with_callback(gpio, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true, callback);
}