#include <menu.h>
#include <signal.h>
#include <stdlib.h>
#include <ncurses.h>
#include <ACLamp.h>
#include <sensores.h>


void saida_m(char *msg){
    refresh();
    endwin();

    int tamanho = strlen(msg);
    if(tamanho > 0){
        printf("%s", msg);
    }
    exit(0);
}

void saida_m_signal(){
    refresh();
    endwin();
    exit(0);
}


void saida_inicio(){
    signal(SIGINT, saida_m_signal);
}


Estado estado;
WINDOW *menu_win;
Sensores entrada;


void imprime_luzes_ac(WINDOW * menu_win){
    char esc_Lampada_AC[4][50] = {"Lampada 1", "Lampada 2", "Projetor Multimidia", "Ar Condicionado"};
    for(int i = 0; i < 4; i++){
        mvwprintw(menu_win, i + 1, 50, esc_Lampada_AC[i]);
    }

}

void imprime_sensores(WINDOW * menu_win){
    char esc_Sensores[4][50] = {"Sensor de Presenca", "Sensor de Fumaca", "Sensor de Porta", "Sensor de Janela"};
    for(int i = 0; i < 4; i++){
        mvwprintw(menu_win, i + 1, 50, esc_Sensores[i]);
    }
}

void imprime_estado(WINDOW * menu_win){
    wattron(menu_win, COLOR_PAIR(estado.lampada1 == 1 ? 3 : 2));
        mvwprintw(menu_win, 1, 60, estado.lampada1 == 1 ? "Ligada" : "Desligada");
        wattroff(menu_win, COLOR_PAIR(estado.lampada1 == 1 ? 3 : 2));

    wattron(menu_win, COLOR_PAIR(estado.lampada2 == 1 ? 3 : 2));
        mvwprintw(menu_win, 2, 60, estado.lampada2 == 1 ? "Ligada" : "Desligada");
        wattroff(menu_win, COLOR_PAIR(estado.lampada2 == 1 ? 3 : 2));
    
    wattron(menu_win, COLOR_PAIR(estado.pr == 1 ? 3 : 2));
        mvwprintw(menu_win, 3, 60, estado.pr == 1 ? "Ligada" : "Desligada");
        wattroff(menu_win, COLOR_PAIR(estado.pr == 1 ? 3 : 2));

    wattron(menu_win, COLOR_PAIR(estado.ac == 1 ? 3 : 2));
        mvwprintw(menu_win, 4, 60, estado.ac == 1 ? "Ligada" : "Desligada");
        wattroff(menu_win, COLOR_PAIR(estado.ac == 1 ? 3 : 2));
    
    wrefresh(menu_win);

}

void imprime_sensores_estado(WINDOW * menu_win){

    mvwprintw(menu_win, 1, 60, entrada.sensor_presenca == 1 ? "Ligado" : "Desligado");
    wattron(menu_win, COLOR_PAIR(entrada.sensor_presenca == 1 ? 3 : 2));
        mvwprintw(menu_win, 1, 60, entrada.sensor_presenca == 1 ? "Ligado" : "Desligado");
        wattroff(menu_win, COLOR_PAIR(entrada.sensor_presenca == 1 ? 3 : 2));

    mvprintw(2, 60, entrada.sensor_fumaca == 1 ? "Ligado" : "Desligado");
    wattron(menu_win, COLOR_PAIR(entrada.sensor_fumaca == 1 ? 3 : 2));
        mvwprintw(menu_win, 2, 60, entrada.sensor_fumaca == 1 ? "Ligado" : "Desligado");
        wattroff(menu_win, COLOR_PAIR(entrada.sensor_fumaca == 1 ? 3 : 2));
    
    mvprintw(3, 60, entrada.sensor_porta == 1 ? "Ligado" : "Desligado");
    wattron(menu_win, COLOR_PAIR(entrada.sensor_porta == 1 ? 3 : 2));
        mvwprintw(menu_win, 3, 60, entrada.sensor_porta == 1 ? "Ligado" : "Desligado");
        wattroff(menu_win, COLOR_PAIR(entrada.sensor_porta == 1 ? 3 : 2));
    
    mvprintw(4, 60, entrada.sensor_janela == 1 ? "Ligado" : "Desligado");
    wattron(menu_win, COLOR_PAIR(entrada.sensor_janela == 1 ? 3 : 2));
        mvwprintw(menu_win, 4, 60, entrada.sensor_janela == 1 ? "Ligado" : "Desligado");
        wattroff(menu_win, COLOR_PAIR(entrada.sensor_janela == 1 ? 3 : 2));


}

void menu_escolha(){

    int highlight = 1;
    int choice = 0;
    int c;

    initscr();
    start_color();

    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_BLACK, COLOR_GREEN);


    menu_win = newwin(80, 80, 0, 0);
    keypad(menu_win, TRUE);
    refresh();

    char esc_Lampada_AC[5][50] = {"Lampada 1", "Lampada 2", "Projetor","Ar Condicionado", "Sair"};
    
    while (1)
    {
        for(int i; i < 5; i++){
            if(highlight == i){
                wattron(menu_win, COLOR_PAIR(1));
                mvwprintw(menu_win, i + 1, 1, esc_Lampada_AC[i]);
                wattroff(menu_win, COLOR_PAIR(1));}
        }

        c = wgetch(menu_win);

        switch (c)
        {
            case KEY_UP:
                if(highlight == 1)
                    highlight = 5;
                else
                    --highlight;
                break;
            case KEY_DOWN:
                if(highlight == 5)
                    highlight = 4;
                else
                    ++highlight;
                break;
            case 11:
                choice = highlight;
                if(choice == 0){
                    if(estado.lampada1 == 1){
                        estado.lampada1 = 0;
                        imprime_estado(menu_win);
                    }
                    else{
                        estado.lampada1 = 1;
                        imprime_estado(menu_win);
                    }
                    enviaComando(estado);
                }
                if(choice == 1){
                    if(estado.lampada2 == 1){
                        estado.lampada2 = 0;
                        imprime_estado(menu_win);
                    }
                    else{
                        estado.lampada2 = 1;
                        imprime_estado(menu_win);
                    }
                    enviaComando(estado);
                }
                if(choice == 2){
                    if(estado.pr == 1){
                        estado.pr = 0;
                        imprime_estado(menu_win);
                    }
                    else{
                        estado.pr = 1;
                        imprime_estado(menu_win);
                    }
                    enviaComando(estado);
                }
                if(choice == 3){
                    if(estado.ac == 1){
                        estado.ac = 0;
                        imprime_estado(menu_win);
                    }
                    else{
                        estado.ac = 1;
                        imprime_estado(menu_win);
                    }
                    enviaComando(estado);
                }
                if(choice == 4){
                    endwin();
                    exit(0);
                }
    }
    
}
}

void atualiza_estado(Estado estadott){
    estado = estadott;
}

