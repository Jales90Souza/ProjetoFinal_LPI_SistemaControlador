#ifndef VIAGEM_H_INCLUDED
#define VIAGEM_H_INCLUDED

#include <vector>
#include "Transporte.h"
#include "Passageiro.h"
#include "Cidade.h"

class Viagem {
    private:
        Transporte* transporte;
        std::vector<Passageiro*> passageiros;
        Cidade* origem;
        Cidade* destino;
        Viagem* proxima;
        int horasEmTransito;
        bool emAndamento;

    public:
        Viagem(Transporte* transporte, std::vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino);
        void iniciarViagem();
        void avancarHoras(int horas);
        void relatarEstado();
        bool isEmAndamento();
};

#endif // VIAGEM_H_INCLUDED
