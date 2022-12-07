#ifndef __FILA_DE_FUNCAO__
#define __FILA_DE_FUNCAO__

#include "definicoes.h"
#include "FIFO.h"
#include "temporizador.h"

struct Evento {
    int prioridade;
    Microssegundos release_time;
    Microssegundos tempo;
    void (* funcao)(void *);
    void * args;
};
/*
class FilaDeFuncao : public FIFO<Evento, 16> {
    public:
        void executar(){
            Evento proximo;
            FIFO_Errors_t status = FIFO_ERROR_EMPTY;
            __asm__("cli");
            while (this->size() > 0){
                status = this->dequeue(&proximo);
                __asm__("sei");
                if (status == FIFO_SUCCESS) proximo.funcao(proximo.args);
            }
            __asm__("sei");
        }
};
*/

class FilaDeFuncao: public ListaEncadeada<Evento*, true, false, int> {
    public:
        void executar(){
            Evento *proximo;
            __asm__("cli");
            while (this->tamanho() > 0){
                proximo = this->remove_inicio();
                __asm__("sei");
                proximo->funcao(proximo->args);
                __asm__("cli");
            }
            __asm__("sei");
        
        }
};

#endif