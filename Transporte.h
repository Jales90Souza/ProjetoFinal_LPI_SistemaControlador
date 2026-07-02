#ifndef TRANSPORTE_H_INCLUDED
#define TRANSPORTE_H_INCLUDED

#include <string>
#include "Cidade.h"

class Transporte {
    private:
        std::string nome;
        char tipo;        // 'A' ou 'T'
        int capacidade;
        int velocidade;
        int distancia_entre_descansos;
        int tempo_de_descanso;
        int tempo_de_descanso_atual;
        Cidade* localAtual;

    public:
        Transporte(std::string nome, char tipo, int capacidade, int velocidade,
                   int distancia_entre_descansos, int tempo_de_descanso, Cidade* localAtual);

        std::string getNome();
        char getTipo();
        int getCapacidade();
        int getVelocidade();
        int getDistanciaEntreDescansos();
        int getTempoDescanso();
        int getTempoDescansoAtual();
        Cidade* getLocalAtual();
        void setLocalAtual(Cidade* local);
};

#endif // TRANSPORTE_H_INCLUDED
