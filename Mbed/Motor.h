#ifndef MBED_MOTOR_H
#define MBED_MOTOR_H

#include "mbed.h"

/** Interface to control a standard DC motor 
 *
 * with an H-bridge using a PwmOut and 2 DigitalOuts
 */

class Motor {
public:

    /** Create a motor control interface    
     *
     * @param pwm A PwmOut pin, driving the H-bridge enable line to control the speed
     * @param fwd A DigitalOut, set high when the motor should go forward
     * @param rev A DigitalOut, set high when the motor should go backwards
     */
    Motor(PinName pwm, PinName fwd, PinName rev);
    
    /** Set the speed of the motor
     * 
     * @param speed The speed of the motor as a normalised value between -1.0 and 1.0
     */
    void speed(float speed);

protected:
    PwmOut _pwm;
    DigitalOut _fwd;
    DigitalOut _rev;

};

#endif
