#include <cliente.h>
#include <gpio.h>

void *sendServer(char *msg){
    int socketClient;
    struct sockaddr_in server;
    //char message[16];
    unsigned int msg_len;

    int bytes_received;
    int bytes_total;

    // Create socket
    if((socketClient = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("Erro ao criar socket");
        exit(1);
    }

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(IP_SERVIDOR);
    server.sin_port = htons(PORTA_SERVIDOR);


    // Connect to server
    if(connect(socketClient, (struct sockaddr *)&server, sizeof(server)) < 0){
        printf("Erro ao conectar com o servidor");
        exit(1);
    }

    msg_len = strlen(msg);
    printf("%d\n", msg_len);

    // Send message to server
    if(send(socketClient, msg, msg_len, 0) != msg_len){
        printf("Erro ao enviar mensagem");
        exit(1);
    }
    close(socketClient);
}

// comunication with server

void comunicationServerTCP(int socketServidor){
    char message[16];

    memset(message, 0, sizeof(message));

    int bytes_received;
    if((bytes_received = recv(socketServidor, message, sizeof(message), 0)) < 0){
        printf("Erro ao receber mensagem");
        exit(1);
    }

    message[15] = '\0';

    int comando;
    sscanf(message, "%d", &comando);

    if(comando == 1){
        int item;
        int state;
        sscanf(message, "%d %d %d", &comando, &item, &state);
        printf("Comando: %d, ID: %d, Estado: %d", comando, item, state);
        toggle(item, state);
        char m[2];
        sprintf(m, 2, "%d", 1);
        int tam = strlen(m);
        printf("resultado\n");
        if(send(socketServidor, m, tam, 0) != tam){
            printf("Erro ao enviar mensagem");
            exit(1);
        }
    }
}

//criar cliente

void *createClient(){
    int socketServer, socketClient;
    struct sockaddr_in addr_server;
    struct sockaddr_in addr_client;

    if((socketServer = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("Erro ao criar socket");
        exit(1);
    }

    memset(&addr_client, '0', sizeof(addr_client));

    addr_client.sin_family = AF_INET;
    addr_client.sin_addr.s_addr = htonl(INADDR_ANY);
    addr_client.sin_port = htons(CLIENTE_PORTA);

    if(bind(socketClient, (struct sockaddr *)&addr_client, sizeof(addr_client)) < 0){
        printf("Erro ao fazer bind");
        exit(1);
    }
    if(listen(socketClient, 10) < 0){
        printf("Erro ao escutar");
        exit(1);
    }

    while(1){
        unsigned int addr_len = sizeof(addr_server);
        socketServer = accept(socketClient, (struct sockaddr *)&addr_server, &addr_len);

        if(socketServer < 0){
            printf("Erro ao aceitar");
            exit(1);
        }
        comunicationServerTCP(socketServer);
        close(socketServer);
    }

    close(socketClient);
}