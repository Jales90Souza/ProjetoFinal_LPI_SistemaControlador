#include <iostream>
#include <string>
#include <vector>
#include "ControladorDeTransito.h"

using namespace std;

// Função para exibir o menu principal
void exibirMenuPrincipal() {
    cout << "\n==========================================" << endl;
    cout << "       SISTEMA CONTROLADOR DE VIAGENS     " << endl;
    cout << "==========================================" << endl;
    cout << "1. Cadastrar Cidade" << endl;
    cout << "2. Cadastrar Trajeto" << endl;
    cout << "3. Cadastrar Transporte" << endl;
    cout << "4. Cadastrar Passageiro" << endl;
    cout << "5. Gestao de Viagens (Iniciar / Avancar Tempo)" << endl;
    cout << "6. Consultas e Relatorios" << endl;
    cout << "0. Salvar e Sair" << endl;
    cout << "------------------------------------------" << endl;
    cout << "Escolha uma opcao: ";
}

// Submenu para agrupar as opções de relatórios (Item 6)
void exibirMenuRelatorios() {
    cout << "\n--- CONSULTAS E RELATORIOS ---" << endl;
    cout << "1. Localizacao das Pessoas (Passageiros)" << endl;
    cout << "2. Localizacao dos Transportes" << endl;
    cout << "3. Relatar Viagens em Andamento" << endl;
    cout << "4. Relatar Cidades Mais Visitadas" << endl;
    cout << "0. Voltar ao Menu Principal" << endl;
    cout << "------------------------------" << endl;
    cout << "Escolha uma opcao: ";
}

int main() {
    ControladorDeTransito controlador;

    // Carrega automaticamente os dados salvos em arquivos de texto ao iniciar
    controlador.carregarDados();

    int opcaoPrincipal = -1;

    while (opcaoPrincipal != 0) {
        exibirMenuPrincipal();
        cin >> opcaoPrincipal;

        // 1. CADASTRO DE CIDADES
        if (opcaoPrincipal == 1) {
            string nome;
            cout << "\n[1] --- Cadastrar Cidade ---" << endl;
            cout << "Nome da Cidade: ";
            cin.ignore();
            getline(cin, nome);
            controlador.cadastrarCidade(nome);
        }

        // 2. CADASTRO DE TRAJETOS
        else if (opcaoPrincipal == 2) {
            string origem, destino;
            char tipo;
            int distancia;

            cout << "\n[2] --- Cadastrar Trajeto ---" << endl;
            cout << "Cidade de Origem: ";
            cin.ignore();
            getline(cin, origem);
            cout << "Cidade de Destino: ";
            getline(cin, destino);
            cout << "Tipo de Trajeto ('T' para Terrestre, 'A' para Aquatico): ";
            cin >> tipo;
            cout << "Distancia em Km: ";
            cin >> distancia;

            controlador.cadastrarTrajeto(origem, destino, tipo, distancia);
        }

        // 3. CADASTRO DE TRANSPORTES
        else if (opcaoPrincipal == 3) {
            string nome, localAtual;
            char tipo;
            int capacidade, velocidade, distDescanso, tempoDescanso;

            cout << "\n[3] --- Cadastrar Transporte ---" << endl;
            cout << "Nome do Transporte: ";
            cin.ignore();
            getline(cin, nome);
            cout << "Tipo ('T' para Terrestre, 'A' para Aquatico): ";
            cin >> tipo;
            cout << "Capacidade de Passageiros: ";
            cin >> capacidade;
            cout << "Velocidade (Km/h): ";
            cin >> velocidade;
            cout << "Distancia entre descansos (Km): ";
            cin >> distDescanso;
            cout << "Tempo de descanso (Horas): ";
            cin >> tempoDescanso;
            cout << "Cidade atual do transporte: ";
            cin.ignore();
            getline(cin, localAtual);

            controlador.cadastrarTransporte(nome, tipo, capacidade, velocidade, distDescanso, tempoDescanso, localAtual);
        }

        // 4. CADASTRO DE PASSAGEIROS
        else if (opcaoPrincipal == 4) {
            string nome, localAtual;

            cout << "\n[4] --- Cadastrar Passageiro ---" << endl;
            cout << "Nome do Passageiro: ";
            cin.ignore();
            getline(cin, nome);
            cout << "Cidade atual do passageiro: ";
            getline(cin, localAtual);

            controlador.cadastrarPassageiro(nome, localAtual);
        }

        // 5. GESTÃO DE VIAGENS
        else if (opcaoPrincipal == 5) {
            int subOpcao = 0;
            cout << "\n[5] --- Gestao de Viagens ---" << endl;
            cout << "1. Iniciar Nova Viagem (Simular e partir)" << endl;
            cout << "2. Avancar Horas no Sistema" << endl;
            cout << "Escolha uma opcao: ";
            cin >> subOpcao;

            if (subOpcao == 1) {
                string nomeTransporte, nomeOrigem, nomeDestino;
                int qtdPassageiros;
                vector<string> nomesPassageiros;

                cout << "\n--- Iniciar Viagem ---" << endl;
                cout << "Cidade de Origem: ";
                cin.ignore();
                getline(cin, nomeOrigem);
                cout << "Cidade de Destino: ";
                getline(cin, nomeDestino);
                cout << "Nome do Transporte a ser utilizado: ";
                getline(cin, nomeTransporte);

                cout << "Quantos passageiros vao viajar? ";
                cin >> qtdPassageiros;
                cin.ignore();

                for (int i = 0; i < qtdPassageiros; i++) {
                    string nomePassageiro;
                    cout << "Digite o nome do passageiro " << i + 1 << ": ";
                    getline(cin, nomePassageiro);
                    nomesPassageiros.push_back(nomePassageiro);
                }

                controlador.iniciarViagem(nomeTransporte, nomesPassageiros, nomeOrigem, nomeDestino);
            }
            else if (subOpcao == 2) {
                int horas;
                cout << "\nQuantas horas deseja avancar no tempo? ";
                cin >> horas;
                controlador.avancarHoras(horas);
            }
        }

        // 6. CONSULTAS E RELATÓRIOS
        else if (opcaoPrincipal == 6) {
            int opcaoRelatorio = -1;
            while (opcaoRelatorio != 0) {
                exibirMenuRelatorios();
                cin >> opcaoRelatorio;

                if (opcaoRelatorio == 1) {
                    // Relata onde estão as pessoas (cidade ou em trânsito)
                    controlador.relatarEstadoPessoas();
                }
                else if (opcaoRelatorio == 2) {
                    // Relata onde estão os transportes
                    controlador.relatarEstadoTransportes();
                }
                else if (opcaoRelatorio == 3) {
                    // Relata as viagens em andamento
                    controlador.relatarViagensEmAndamento();
                }
                else if (opcaoRelatorio == 4) {
                    // Relata as cidades mais visitadas
                    controlador.relatarCidadesMaisVisitadas();
                }
            }
        }
        // 0. SALVAR E SAIR
        else if (opcaoPrincipal == 0) {
            // Salva todas as listas modificadas antes de fechar o programa
            controlador.salvarDados();
            cout << "\nDados salvos com sucesso. Saindo do sistema... Ate mais!" << endl;
        }
        else {
            cout << "\n[ERRO] Opcao invalida! Tente novamente." << endl;
        }
    }

    return 0;
}
