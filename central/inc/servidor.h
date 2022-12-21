#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define PORTA_SERVIDOR 13508
#define CLIENTE_IP "164.41.98.26"
#define CLIENTE_PORTA 13509


void *criarServidor();
int enviarComandoDistribuido(int item, int state);
