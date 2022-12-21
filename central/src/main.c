#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include <menu.h>
#include <ACLamp.h>
#include <sensores.h>

int main(int argc, char const *argv[])
{
    saida_inicio();
    estado_inicial();

    pthread_t thread_menu;
    pthread_t server;
    pthread_create(&thread_menu, NULL, menu, NULL);
    pthread_create(&server, NULL, criarServidor, NULL);
    pthread_join(server, NULL);
    pthread_join(thread_menu, NULL);


    return 0;
}

