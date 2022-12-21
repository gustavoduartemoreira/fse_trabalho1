#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>


#define IP_SERVIDOR "164.41.98.26"
#define PORTA_SERVIDOR 5000
#define CLIENTE_PORTA 5001

void *sendServer();
void *createClient();