#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <cliente.h>
#include <gpio.h>

void quit(){
    desliga_tudo();
    exit(0);
}

int main(int argc, char *argv[]) {
    signal(SIGINT, quit);
    gpio_init();

    desliga_tudo();

    pthread_t cliente_thread, gpio_thread;
    pthread_create(&cliente_thread, NULL, createClient, NULL);
    pthread_create(&gpio_thread, NULL, gpio_handler, NULL);
    pthread_join(cliente_thread, NULL);
    pthread_join(gpio_thread, NULL);
    quit();
    
    return 0;
}