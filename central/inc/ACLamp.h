#include <stdio.h>
#include <stdlib.h>
#include <servidor.h>

typedef struct {
    int lampada1;
    int lampada2;
    int pr;
    int ac;
} Estado;

void estado_inicial();
void enviaComando(Estado estado);
