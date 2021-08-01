#include "Motor.h"
#include "mbed.h"

Motor::Motor(PinName pwm, PinName fwd, PinName rev):
        _pwm(pwm), _fwd(fwd), _rev(rev) {

    //Seta condição inicial do PWM
    _pwm.period(0.001);
    _pwm = 0;

    //Seta condição inicial para outputs
    _fwd = 0;
    _rev = 0;
}

void Motor::speed(float speed) {
    _fwd = (speed > 0.0);
    _rev = (speed < 0.0);
    _pwm = abs(speed);
}



