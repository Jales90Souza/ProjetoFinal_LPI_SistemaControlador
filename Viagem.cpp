#include "Viagem.h"
#include <iostream>

Viagem::Viagem(Transporte* transporte, std::vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino) {
    this->transporte = transporte;
    this->passageiros = passageiros;
    this->origem = origem;
    this->destino = destino;
    this->proxima = nullptr; // Inicialmente sem conexão
    this->horasEmTransito = 0;
    this->emAndamento = false;
}

void Viagem::iniciarViagem() {
    this->emAndamento = true;
}

void Viagem::avancarHoras(int horas) {
    if (!emAndamento) return;
    this->horasEmTransito += horas;
}

void Viagem::relatarEstado() {
    std::cout << "Viagem em andamento para: " << destino->getNome()
              << " | Horas em transito: " << horasEmTransito << "\n";
}

bool Viagem::isEmAndamento() { return emAndamento; }
