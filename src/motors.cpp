#include "../include/motors.hpp"
#include "hardware/gpio.h"
#include "pico/time.h"




motor::motor(uint left_wheel,uint right_wheel)
{
    gpio_init(left_wheel);
    gpio_init(right_wheel);


    gpio_set_dir(left_wheel, GPIO_OUT);
    gpio_set_dir(right_wheel, GPIO_OUT);


    //DC motors activate on Low signal=============
    gpio_put(left_wheel, 1);
    gpio_put(right_wheel, 1);
    //===========================================

    this->left_wheel = left_wheel;
    this->right_wheel = right_wheel;

    motor_state = STOP;

}


void motor::motor_state_machine()
{
switch(motor_state)
{

case FORWARD:
motor_forward();
break;
case LEFT:
motor_turn_left();
sleep_ms(250);
motor_state = STOP;

break;
case RIGHT:
motor_turn_right();
sleep_ms(250);
motor_state = STOP;

break;
case STOP:
motor_stop();

break;
}

}



void motor::motor_turn_left()
{
    gpio_put(right_wheel, 0);
    gpio_put(left_wheel, 1);

}
void motor::motor_turn_right()
{
    gpio_put(right_wheel, 1);
    gpio_put(left_wheel, 0);
}
void motor::motor_forward()
{
    gpio_put(right_wheel, 0);
    gpio_put(left_wheel, 0);
}
void motor::motor_stop()
{
    gpio_put(right_wheel, 1);
    gpio_put(left_wheel, 1);

}
