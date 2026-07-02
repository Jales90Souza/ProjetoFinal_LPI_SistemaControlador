#include "Passageiro.h"

Passageiro::Passageiro(std::string nome, Cidade* localAtual) {
    this->nome = nome;
    this->localAtual = localAtual;
}

std::string Passageiro::getNome() { return nome; }
Cidade* Passageiro::getLocalAtual() { return localAtual; }
void Passageiro::setLocalAtual(Cidade* local) { localAtual = local; }
