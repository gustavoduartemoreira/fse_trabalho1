#include <unistd.h>
#include <cliente.h>
#include <gpio.h>

void gpio_init(void)
{
    wiringPiSetup();
}

void toggle(int item, int state){
    pinMode(item, OUTPUT);
    digitalWrite(item, state);
}

void desliga_tudo(){
    // lampadas
    pinMode(L_01, OUTPUT);
    digitalWrite(L_01, 0);

    pinMode(L_02, OUTPUT);
    digitalWrite(L_02, 0);

    // ar condicionado
    pinMode(AC, OUTPUT);
    digitalWrite(AC, 0);

    //projetor
    pinMode(PR, OUTPUT);
    digitalWrite(PR, 0);
}

void sensor_presenca(){
    char* msg = "1";
    printf("Sensor de presenca ativado \n");
    sendServer(msg);
}

void sensor_fumaca(){
    char* msg = "2";
    printf("Sensor de fumaca ativado \n");
    sendServer(msg);
}

void sensor_porta(){
    char* msg = "3";
    printf("Sensor de porta ativado \n");
    sendServer(msg);
}

void sensor_janela(){
    char* msg = "4";
    printf("Sensor de janela ativado \n");
    sendServer(msg);
}

void* gpio_handler(){
    //sensor de presença
    pinMode(Spres, INPUT);
    wiringPiISR(Spres, INT_EDGE_RISING, sensor_presenca);
    // sensor de fumaça
    pinMode(Sfum, INPUT);
    wiringPiISR(Sfum, INT_EDGE_RISING, sensor_fumaca);
    // sensor de porta
    pinMode(Spor, INPUT);
    wiringPiISR(Spor, INT_EDGE_RISING, sensor_porta);
    // sensor de janela
    pinMode(Sjan, INPUT);
    wiringPiISR(Sjan, INT_EDGE_RISING, sensor_janela);

    for (;;)
    {
        sleep(1);
    }
}
