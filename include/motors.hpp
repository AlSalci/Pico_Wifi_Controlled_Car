#include "pico/stdio.h"
#include <vector>



enum MOTOR_STATE
{
FORWARD,
LEFT,
RIGHT,
STOP
};

class motor 
{

private:



public:
/*
@Sets up the GPIOs that will control the DC motors
@Params- None
@Return- None 
*/
motor(uint left_wheel,uint right_wheel);
uint left_wheel,right_wheel;

static MOTOR_STATE motor_state;

/*
@State machine in order to control the two DC motors 
@Params- None
@Return- None 
*/
void motor_state_machine();

void motor_turn_left();
void motor_turn_right();
void motor_forward();
void motor_stop();


};
