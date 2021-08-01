#include "mbed.h"
#include "Motor.h"

DigitalOut led1(LED1);
CAN can0(p9, p10);
 
Motor m1(p23, p6, p5); //pinos pwm, frente, trás movimento horizontal
Motor m2(p24, p8, p7); //pinos pwm, frente, trás movimento vertical

void mov_frente(){
    //movimento de subida da pata
    m1.speed(1);
    m2.speed(1);
    wait(5);
    //movimento de descida da pata
    m1.speed(1);
    m2.speed(-1);
    wait(5);
    //período em que a pata está em contato com o chão
    m1.speed(-1);
    m2.speed(0);
    wait(10);
}

void mov_tras(){
    //movimento de subida da pata
    m1.speed(-1);
    m2.speed(1);
    wait(5);
    //movimento de descida da pata
    m1.speed(-1);
    m2.speed(-1);
    wait(5);
    //período em que a pata está em contato com o chão
    m1.speed(1);
    m2.speed(0);
    wait(10);
}


int main() {
    printf("main()\n");
    CANMessage msg;
    while (1) {
        printf("loop()\n");
        if (can0.read(msg)) { //Checa se a mensagem foi recebida
            printf("Message received: %d\n", msg.data[0] & msg.data[1]);
            led1 = !led1;
            if (msg.data[0] == 0x66 & msg.data[1] == 0x72){ //Lógica de receber a mensagem CAN ("fr" - frente) para movimentar para frente e aplicar o respectivo comando
                mov_frente();
            }
            else if (msg.data[0] == 0x74 & msg.data[1] == 0x72){ //Lógica de receber a mensagem CAN ("tr" - trás) para movimentar para trás e aplicar o respectivo comando
                mov_tras();
            }
        }
        wait(0.2);
    }
}
