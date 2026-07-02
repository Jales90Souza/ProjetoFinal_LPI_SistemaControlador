#include "Transporte.h"

Transporte::Transporte(std::string nome, char tipo, int capacidade, int velocidade,
                       int distancia_entre_descansos, int tempo_de_descanso, Cidade* localAtual) {
    this->nome = nome;
    this->tipo = tipo;
    this->capacidade = capacidade;
    this->velocidade = velocidade;
    this->distancia_entre_descansos = distancia_entre_descansos;
    this->tempo_de_descanso = tempo_de_descanso;
    this->tempo_de_descanso_atual = 0; // Inicializa sem cansaço
    this->localAtual = localAtual;
}

std::string Transporte::getNome() { return nome; }
char Transporte::getTipo() { return tipo; }
int Transporte::getCapacidade() { return capacidade; }
int Transporte::getVelocidade() { return velocidade; }
int Transporte::getDistanciaEntreDescansos() { return distancia_entre_descansos; }
int Transporte::getTempoDescanso() { return tempo_de_descanso; }
int Transporte::getTempoDescansoAtual() { return tempo_de_descanso_atual; }
Cidade* Transporte::getLocalAtual() { return localAtual; }
void Transporte::setLocalAtual(Cidade* local) { localAtual = local; }
