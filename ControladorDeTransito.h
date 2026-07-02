#ifndef CONTROLADORDETRANSITO_H_INCLUDED
#define CONTROLADORDETRANSITO_H_INCLUDED

#ifndef CONTROLADORDETRANSITO_H
#define CONTROLADORDETRANSITO_H

#include <vector>
#include <string>
#include "Cidade.h"
#include "Trajeto.h"
#include "Transporte.h"
#include "Passageiro.h"
#include "Viagem.h"

class ControladorDeTransito {
private:
    std::vector<Cidade*> cidades;
    std::vector<Trajeto*> trajetos;
    std::vector<Transporte*> transportes;
    std::vector<Passageiro*> passageiros;
    std::vector<Viagem*> viagens;

    Cidade* buscarCidade(std::string nome);
    Transporte* buscarTransporte(std::string nome);


public:
    void cadastrarCidade(std::string nome);
    void cadastrarTrajeto(std::string nomeOrigem, std::string nomeDestino, char tipo, int distancia);
    void cadastrarTransporte(std::string nome, char tipo, int capacidade, int velocidade,
                             int distancia_entre_descansos, int tempo_de_descanso, std::string localAtual);
    void cadastrarPassageiro(std::string nome, std::string localAtual);

    void iniciarViagem(std::string nomeTransporte, std::vector<std::string> nomesPassageiros,
                       std::string nomeOrigem, std::string nomeDestino);
    void avancarHoras(int horas);


    void carregarDados();
    void salvarDados();
    void relatarEstadoPessoas();
    void relatarEstadoTransportes();
    void relatarViagensEmAndamento();
    void relatarCidadesMaisVisitadas();
    // =======================================================
};

#endif



#endif // CONTROLADORDETRANSITO_H_INCLUDED
