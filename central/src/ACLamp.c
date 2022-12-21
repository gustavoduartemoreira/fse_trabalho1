#include <ACLamp.h>

#define L_01 18
#define L_02 23
#define AC 24
#define PR 25


Estado _estado;

void estado_inicial(){
    _estado.lampada1 = 0;
    _estado.lampada2 = 0;
    _estado.pr = 0;
    _estado.ac = 0;
    atualiza_estado(_estado);
}

void enviaComando(Estado estado){
    int sit = 1;
    if(estado.lampada1 != _estado.lampada1){
        sit = enviarComandoDistribuido(L_01, estado.lampada1);
    }
    if(estado.lampada2 != _estado.lampada2){
        sit = enviarComandoDistribuido(L_02, estado.lampada2);
    }
    if(estado.pr != _estado.pr){
        sit = enviarComandoDistribuido(PR, estado.pr);
    }
    if(estado.ac != _estado.ac){
        sit = enviarComandoDistribuido(AC, estado.ac);
    }

    if(sit == 0){
        _estado = estado;
        atualiza_estado(_estado);
    }
}