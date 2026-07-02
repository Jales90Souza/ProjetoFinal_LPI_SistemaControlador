#include "Cidade.h"

Cidade::Cidade(std::string nome) {
    this->nome = nome;
}

std::string Cidade::getNome() {
    return nome;
}
