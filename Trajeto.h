#ifndef TRAJETO_H_INCLUDED
#define TRAJETO_H_INCLUDED

#include "Cidade.h"

class Trajeto {
    private:
        Cidade* origem;
        Cidade* destino;
        char tipo;       // 'A' para Aquatico, 'T' para Terrestre
        int distancia;

    public:
        Trajeto(Cidade* origem, Cidade* destino, char tipo, int distancia);
        Cidade* getOrigem();
        Cidade* getDestino();
        char getTipo();
        int getDistancia();
};

#endif // TRAJETO_H_INCLUDED
