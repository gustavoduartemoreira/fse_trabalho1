#include <servidor.h>
#include <sensores.h>
#include <stdio.h>
#include <stdlib.h>
#include <menu.h>


void comunicacaoTCP(int ClienteSocket){
    char buffer[16];
    memset(buffer, 0, sizeof(buffer));
    int recebido;
    if((recebido = recv(ClienteSocket, buffer, sizeof(buffer), 0)) < 0){
        printf("Erro ao receber %d\n", recebido);
        
    }

    buffer[15] = '\0';
    while (recebido > 0)
    {
        if(send(ClienteSocket, buffer, recebido, 0) != recebido){
            printf("Erro ao enviar dados para o cliente");
            
        }
        if((recebido = recv(ClienteSocket, buffer, sizeof(buffer), 0)) < 0){
            printf("Erro ao receber dados do cliente");
            
        }
    }
    int comando;
    sscanf(buffer, "%d", &comando);

    estadoSensores(comando);
}

void *criarServidor(){
    int ServidorSocket, ClienteSocket;
    struct sockaddr_in ServidorAddr;
    struct sockaddr_in ClienteAddr;

    if((ServidorSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("Erro ao criar socket");
        exit(1);
    }

    memset(&ServidorAddr, 0, sizeof(ServidorAddr));
    ServidorAddr.sin_family = AF_INET;
    ServidorAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    ServidorAddr.sin_port = htons(PORTA_SERVIDOR);

    //bind
    if(bind(ServidorSocket, (struct sockaddr *) &ServidorAddr, sizeof(ServidorAddr)) < 0){
        printf("Erro ao fazer bind");
        exit(1);
    }

    //listen
    if(listen(ServidorSocket, 10) < 0){
        printf("Erro ao fazer listen");
        exit(1);
    }

    while (1)
    {
        unsigned int tamanho = sizeof(ClienteAddr);
        ClienteSocket = accept(ServidorSocket, (struct sockaddr *) &ClienteAddr, &tamanho);
        if(ClienteSocket < 0){
            printf("Erro ao aceitar conexao: %d\n", ClienteSocket);
            exit(1);
        }
        comunicacaoTCP(ClienteSocket);
        close(ClienteSocket);
    }
    close(ServidorSocket);
    return NULL;  
}

void enviarComando(int item, int comando){
    struct sockaddr_in Cliente;
    int IdSocket = socket(AF_INET, SOCK_STREAM, 0);

    if(IdSocket == -1){
        char *msg = "Erro ao criar socket, iniciar o sistema distribuido";
        saida_m(msg);
    }

    Cliente.sin_family = AF_INET;
    Cliente.sin_port = htons(PORTA_SERVIDOR);
    Cliente.sin_addr.s_addr = inet_addr(CLIENTE_IP);

    if(connect(IdSocket, (struct sockaddr *) &Cliente, sizeof(Cliente)) < 0){
        char *msg = "Erro ao criar socket, iniciar o sistema distribuido";
        saida_m(msg);
    }

    char buff[6];
    snprintf(buff, 6, "%d %d %d", item, comando, 1);

    int size = strlen(buff);

    if(send(IdSocket, buff, size, 0) != size){
        char *msg = "Erro ao criar socket, iniciar o sistema distribuido";
        saida_m(msg);
    }

    char buffer[16];
    int size_recv = recv(IdSocket, buffer, 16, 0);
    if(size_recv < 0){
        char *msg = "Erro ao criar socket, iniciar o sistema distribuido";
        saida_m(msg);
    }
    buffer[15] = '\0';
    int resp;
    sscanf(buffer, "%d", &resp);

}

