#include <sensores.h>
#include <ACLamp.h>
#include <menu.h>


Sensores _sensores;

void inicializa_sensores(){
    _sensores.sensor_presenca = 0;
    _sensores.sensor_fumaca = 0;
    _sensores.sensor_janela = 0;
    _sensores.sensor_porta = 0;
    atualiza_sensor(_sensores);
}

void estadoSensores(int comando){
    if(comando == 1){
        if(_sensores.sensor_presenca == 0){
            _sensores.sensor_presenca = 1;
        }
        else{
        _sensores.sensor_presenca = 1;
        }
    }
    if(comando == 2){
        if(_sensores.sensor_fumaca == 0){
            _sensores.sensor_fumaca = 1;
        }
        else{
        _sensores.sensor_fumaca = 1;
        }
    }
    if(comando == 3){
        if(_sensores.sensor_porta == 0){
            _sensores.sensor_porta = 1;
        }
        else{
        _sensores.sensor_porta = 1;
        }
    }
    if(comando == 4){
        if(_sensores.sensor_janela == 0){
            _sensores.sensor_janela = 1;
        }
        else{
        _sensores.sensor_janela = 1;
        }
    }
    atualiza_sensor(_sensores);
}