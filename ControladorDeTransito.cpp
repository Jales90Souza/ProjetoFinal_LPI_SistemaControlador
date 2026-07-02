#include "ControladorDeTransito.h"
#include <iostream>
#include <fstream>

Cidade* ControladorDeTransito::buscarCidade(std::string nome) {
    for (size_t i = 0; i < cidades.size(); i++) {
        if (cidades[i]->getNome() == nome) return cidades[i];
    }
    return nullptr;
}

Transporte* ControladorDeTransito::buscarTransporte(std::string nome) {
    for (size_t i = 0; i < transportes.size(); i++) {
        if (transportes[i]->getNome() == nome) return transportes[i];
    }
    return nullptr;
}

void ControladorDeTransito::cadastrarCidade(std::string nome) {
    cidades.push_back(new Cidade(nome));
    std::cout << "Cidade " << nome << " cadastrada!\n";
}

void ControladorDeTransito::cadastrarTrajeto(std::string nomeOrigem, std::string nomeDestino, char tipo, int distancia) {
    Cidade* orig = buscarCidade(nomeOrigem);
    Cidade* dest = buscarCidade(nomeDestino);
    if (orig && dest) {
        trajetos.push_back(new Trajeto(orig, dest, tipo, distancia));
        std::cout << "Trajeto cadastrado com sucesso!\n";
    } else {
        std::cout << "Erro: Cidade de origem ou destino nao encontrada.\n";
    }
}

void ControladorDeTransito::cadastrarTransporte(std::string nome, char tipo, int capacidade, int velocidade,
                                                 int distancia_entre_descansos, int tempo_de_descanso, std::string localAtual) {
    Cidade* local = buscarCidade(localAtual);
    if (local) {
        transportes.push_back(new Transporte(nome, tipo, capacidade, velocidade, distancia_entre_descansos, tempo_de_descanso, local));
        std::cout << "Transporte " << nome << " cadastrado!\n";
    }
}

void ControladorDeTransito::cadastrarPassageiro(std::string nome, std::string localAtual) {
    Cidade* local = buscarCidade(localAtual);
    if (local) {
        passageiros.push_back(new Passageiro(nome, local));
        std::cout << "Passageiro " << nome << " cadastrado!\n";
    }
}

void ControladorDeTransito::iniciarViagem(std::string nomeTransporte, std::vector<std::string> nomesPassageiros,
                                          std::string nomeOrigem, std::string nomeDestino) {
    std::cout << "\n[Sistema] Analisando viabilidade da viagem...\n";

    // 1. Buscar a Cidade de Origem e de Destino
    Cidade* orig = buscarCidade(nomeOrigem);
    Cidade* dest = buscarCidade(nomeDestino);

    if (orig == nullptr || dest == nullptr) {
        std::cout << "[Erro] Cidade de origem ou destino nao encontrada no sistema.\n";
        return;
    }

    // 2. Buscar o Transporte solicitado
    Transporte* transp = buscarTransporte(nomeTransporte);
    if (transp == nullptr) {
        std::cout << "[Erro] Transporte '" << nomeTransporte << "' nao encontrado.\n";
        return;
    }

    // 3. Validação: Verificar se o transporte está fisicamente na cidade de origem
    if (transp->getLocalAtual() != orig) {
        std::cout << "[Erro] O transporte '" << nomeTransporte << "' nao esta em " << nomeOrigem
                  << " (Atualmente em: " << transp->getLocalAtual()->getNome() << ").\n";
        return;
    }

    // 4. Validação: Verificar se existe um trajeto direto compatível (Aquático/Terrestre)
    Trajeto* trajetoValido = nullptr;
    for (size_t i = 0; i < trajetos.size(); i++) {
        if (trajetos[i]->getOrigem() == orig &&
            trajetos[i]->getDestino() == dest &&
            trajetos[i]->getTipo() == transp->getTipo()) {
            trajetoValido = trajetos[i];
            break;
        }
    }

    if (trajetoValido == nullptr) {
        std::cout << "[Erro] Nao existe trajeto direto disponivel entre " << nomeOrigem
                  << " e " << nomeDestino << " para o tipo de transporte '" << transp->getTipo() << "'.\n";
        return;
    }

    // 5. Coletar os ponteiros dos passageiros reais a partir dos nomes recebidos
    std::vector<Passageiro*> passageirosDaViagem;
    for (size_t i = 0; i < nomesPassageiros.size(); i++) {
        for (size_t j = 0; j < passageiros.size(); j++) {
            if (passageiros[j]->getNome() == nomesPassageiros[i]) {
                if (passageiros[j]->getLocalAtual() == orig) {
                    passageirosDaViagem.push_back(passageiros[j]);
                } else {
                    std::cout << "[Aviso] O passageiro " << nomesPassageiros[i]
                              << " nao esta em " << nomeOrigem << " e foi desconsiderado.\n";
                }
                break;
            }
        }
    }

    if (passageirosDaViagem.empty() && !nomesPassageiros.empty()) {
        std::cout << "[Erro] Nenhum dos passageiros selecionados esta na cidade de origem para embarcar.\n";
        return;
    }

    // 6. Criar e registrar a nova Viagem de forma dinâmica
    Viagem* novaViagem = new Viagem(transp, passageirosDaViagem, orig, dest);

    viagens.push_back(novaViagem);

    std::cout << "[Sucesso] Viagem iniciada! O transporte " << nomeTransporte
              << " partiu de " << nomeOrigem << " rumo a " << nomeDestino
              << " levando " << passageirosDaViagem.size() << " passageiro(s).\n";
}

void ControladorDeTransito::avancarHoras(int horas) {
    for (size_t i = 0; i < viagens.size(); i++) {
        viagens[i]->avancarHoras(horas);
    }
}

void ControladorDeTransito::carregarDados() {
    std::cout << "[Sistema] Carregando dados dos arquivos de texto...\n";

    std::string linha;
    size_t posicao = 0;

    // 1. CARREGAR CIDADES
    std::ifstream arqCidades("cidades.txt");
    if (arqCidades.is_open()) {
        while (std::getline(arqCidades, linha)) {
            if (!linha.empty()) {
                cidades.push_back(new Cidade(linha));
            }
        }
        arqCidades.close();
    }

    // 2. CARREGAR PASSAGEIROS
    std::ifstream arqPassageiros("passageiros.txt");
    if (arqPassageiros.is_open()) {
        while (std::getline(arqPassageiros, linha)) {
            if (linha.empty()) continue;

            posicao = linha.find(';');
            std::string nome = linha.substr(0, posicao);
            linha = linha.substr(posicao + 1);

            std::string nomeCidade = linha;

            Cidade* cidadeAtual = buscarCidade(nomeCidade);
            if (cidadeAtual != nullptr) {
                passageiros.push_back(new Passageiro(nome, cidadeAtual));
            }
        }
        arqPassageiros.close();
    }

    // 3. CARREGAR TRANSPORTES
    std::ifstream arqTransportes("transportes.txt");
    if (arqTransportes.is_open()) {
        while (std::getline(arqTransportes, linha)) {
            if (linha.empty()) continue;

            posicao = linha.find(';');
            std::string nome = linha.substr(0, posicao);
            linha = linha.substr(posicao + 1);

            posicao = linha.find(';');
            std::string sTipo = linha.substr(0, posicao);
            linha = linha.substr(posicao + 1);

            posicao = linha.find(';');
            std::string sCapacidade = linha.substr(0, posicao);
            linha = linha.substr(posicao + 1);

            posicao = linha.find(';');
            std::string sVelocidade = linha.substr(0, posicao);
            linha = linha.substr(posicao + 1);

            posicao = linha.find(';');
            std::string sDistDescanso = linha.substr(0, posicao);
            linha = linha.substr(posicao + 1);

            posicao = linha.find(';');
            std::string sTempoDescanso = linha.substr(0, posicao);
            linha = linha.substr(posicao + 1);

            std::string nomeCidade = linha;

            char tipo = sTipo[0];
            int capacidade = std::stoi(sCapacidade);
            int velocidade = std::stoi(sVelocidade);
            int distDescanso = std::stoi(sDistDescanso);
            int tempoDescanso = std::stoi(sTempoDescanso);

            Cidade* cidadeAtual = buscarCidade(nomeCidade);
            if (cidadeAtual != nullptr) {
                transportes.push_back(new Transporte(nome, tipo, capacidade, velocidade, distDescanso, tempoDescanso, cidadeAtual));
            }
        }
        arqTransportes.close();
    }

    // 4. CARREGAR TRAJETOS
    std::ifstream arqTrajetos("trajetos.txt");
    if (arqTrajetos.is_open()) {
        while (std::getline(arqTrajetos, linha)) {
            if (linha.empty()) continue;

            posicao = linha.find(';');
            std::string nomeOrigem = linha.substr(0, posicao);
            linha = linha.substr(posicao + 1);

            posicao = linha.find(';');
            std::string nomeDestino = linha.substr(0, posicao);
            linha = linha.substr(posicao + 1);

            posicao = linha.find(';');
            std::string sTipo = linha.substr(0, posicao);
            linha = linha.substr(posicao + 1);

            std::string sDistancia = linha;

            Cidade* orig = buscarCidade(nomeOrigem);
            Cidade* dest = buscarCidade(nomeDestino);
            char tipo = sTipo[0];
            int distancia = std::stoi(sDistancia);

            if (orig != nullptr && dest != nullptr) {
                trajetos.push_back(new Trajeto(orig, dest, tipo, distancia));
            }
        }
        arqTrajetos.close();
    }

    std::cout << "[Sistema] Dados carregados com sucesso!\n";
    std::cout << "Cidades: " << cidades.size() << " | Passageiros: " << passageiros.size()
              << " | Transportes: " << transportes.size() << " | Trajetos: " << trajetos.size() << "\n";
}

void ControladorDeTransito::salvarDados() {
    std::cout << "[Sistema] Salvando dados nos arquivos de texto...\n";

    // 1. SALVAR CIDADES
    std::ofstream arqCidades("cidades.txt");
    if (arqCidades.is_open()) {
        for (size_t i = 0; i < cidades.size(); i++) {
            arqCidades << cidades[i]->getNome() << "\n";
        }
        arqCidades.close();
    } else {
        std::cout << "[Erro] Nao foi possivel abrir cidades.txt para salvar.\n";
    }

    // 2. SALVAR PASSAGEIROS
    std::ofstream arqPassageiros("passageiros.txt");
    if (arqPassageiros.is_open()) {
        for (size_t i = 0; i < passageiros.size(); i++) {
            arqPassageiros << passageiros[i]->getNome() << ";"
                           << passageiros[i]->getLocalAtual()->getNome() << "\n";
        }
        arqPassageiros.close();
    } else {
        std::cout << "[Erro] Nao foi possivel abrir passageiros.txt para salvar.\n";
    }

    // 3. SALVAR TRANSPORTES
    std::ofstream arqTransportes("transportes.txt");
    if (arqTransportes.is_open()) {
        for (size_t i = 0; i < transportes.size(); i++) {
            arqTransportes << transportes[i]->getNome() << ";"
                           << transportes[i]->getTipo() << ";"
                           << transportes[i]->getCapacidade() << ";"
                           << transportes[i]->getVelocidade() << ";"
                           << transportes[i]->getDistanciaEntreDescansos() << ";"
                           << transportes[i]->getTempoDescanso() << ";"
                           << transportes[i]->getLocalAtual()->getNome() << "\n";
        }
        arqTransportes.close();
    } else {
        std::cout << "[Erro] Nao foi possivel abrir transportes.txt para salvar.\n";
    }

    // 4. SALVAR TRAJETOS
    std::ofstream arqTrajetos("trajetos.txt");
    if (arqTrajetos.is_open()) {
        for (size_t i = 0; i < trajetos.size(); i++) {
            arqTrajetos << trajetos[i]->getOrigem()->getNome() << ";"
                        << trajetos[i]->getDestino()->getNome() << ";"
                        << trajetos[i]->getTipo() << ";"
                        << trajetos[i]->getDistancia() << "\n";
        }
        arqTrajetos.close();
    } else {
        std::cout << "[Erro] Nao foi possivel abrir trajetos.txt para salvar.\n";
    }

    std::cout << "[Sistema] Todos os dados foram salvos com sucesso!\n";
}

// Implementação dos Relatórios
void ControladorDeTransito::relatarEstadoPessoas() {
    std::cout << "\n--- Relatorio: Localizacao das Pessoas ---\n";
    if (passageiros.empty()) {
        std::cout << "Nenhum passageiro cadastrado.\n";
        return;
    }
    for (size_t i = 0; i < passageiros.size(); i++) {
        std::cout << "- " << passageiros[i]->getNome()
                  << " esta atualmente em: " << passageiros[i]->getLocalAtual()->getNome() << "\n";
    }
}

void ControladorDeTransito::relatarEstadoTransportes() {
    std::cout << "\n--- Relatorio: Localizacao os Transportes ---\n";
    if (transportes.empty()) {
        std::cout << "Nenhum transporte cadastrado.\n";
        return;
    }
    for (size_t i = 0; i < transportes.size(); i++) {
        std::cout << "- " << transportes[i]->getNome()
                  << " esta atualmente em: " << transportes[i]->getLocalAtual()->getNome() << "\n";
    }
}

void ControladorDeTransito::relatarViagensEmAndamento() {
    std::cout << "\n--- Relatorio: Viagens em Andamento ---\n";
    bool nenhumaViagem = true;
    for (size_t i = 0; i < viagens.size(); i++) {
        if (viagens[i]->isEmAndamento()) {
            viagens[i]->relatarEstado();
            nenhumaViagem = false;
        }
    }
    if (nenhumaViagem) {
        std::cout << "Nenhuma viagem em andamento no momento.\n";
    }
}

void ControladorDeTransito::relatarCidadesMaisVisitadas() {
    std::cout << "\n--- Relatorio: Cidades Mais Visitadas ---\n";

    if (cidades.empty()) {
        std::cout << "Nenhuma cidade cadastrada no sistema.\n";
        return;
    }

    if (viagens.empty()) {
        std::cout << "Nenhuma viagem foi registrada ate o momento. Todas as cidades possuem 0 visitas.\n";
        for (size_t i = 0; i < cidades.size(); i++) {
            std::cout << "- " << cidades[i]->getNome() << ": 0 visita(s)\n";
        }
        return;
    }

    std::cout << "Ranking de visitas por cidade (baseado no local atual dos transportes):\n";

    for (size_t i = 0; i < cidades.size(); i++) {
        int contadorVisitas = 0;
        std::string nomeCidadeAtual = cidades[i]->getNome();

        for (size_t j = 0; j < transportes.size(); j++) {
            if (transportes[j]->getLocalAtual() != nullptr) {
                if (transportes[j]->getLocalAtual()->getNome() == nomeCidadeAtual) {
                    contadorVisitas++;
                }
            }
        }

        std::cout << "- " << nomeCidadeAtual << ": " << contadorVisitas << " visita(s)\n";
    }
}
