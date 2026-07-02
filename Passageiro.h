#ifndef PASSAGEIRO_H_INCLUDED
#define PASSAGEIRO_H_INCLUDED

#include <string>
#include "Cidade.h"

class Passageiro {
    private:
        std::string nome;
        Cidade* localAtual;

    public:
        Passageiro(std::string nome, Cidade* localAtual);
        std::string getNome();
        Cidade* getLocalAtual();
        void setLocalAtual(Cidade* local);
};

#endif // PASSAGEIRO_H_INCLUDED
