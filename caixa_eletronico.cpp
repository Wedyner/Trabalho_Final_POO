#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

// Classe Conta que representa uma conta bancaria
class Conta {
private:
    int numeroConta;
    int senha;
    double saldo;
    vector<string> historicoTransacoes;

public:
    Conta(int numero, int senha, double saldoInicial)
        : numeroConta(numero), senha(senha), saldo(saldoInicial) {
        historicoTransacoes.push_back("Conta criada com saldo inicial de R$ " + formatarValor(saldoInicial));
    }

    bool autenticar(int numeroInserido, int senhaInserida) const {
        return numeroConta == numeroInserido && senha == senhaInserida;
    }

    double consultarSaldo() const {
        return saldo;
    }

    bool sacar(double valor) {
        if (valor > saldo) {
            cout << "Saldo insuficiente." << endl;
            return false;
        }
        saldo -= valor;
        historicoTransacoes.push_back("Saque de R$ " + formatarValor(valor));
        return true;
    }

    void depositar(double valor) {
        saldo += valor;
        historicoTransacoes.push_back("Deposito de R$ " + formatarValor(valor));
    }

    void exibirHistoricoTransacoes() const {
        cout << "\nHistorico de transacoes:\n";
        for (const string &transacao : historicoTransacoes) {
            cout << transacao << endl;
        }
    }

    bool alterarSenha(int senhaAntiga, int novaSenha) {
        if (senha == senhaAntiga) {
            senha = novaSenha;
            historicoTransacoes.push_back("Senha alterada com sucesso.");
            return true;
        }
        cout << "Senha incorreta. A alteracao nao foi realizada." << endl;
        return false;
    }

    string formatarValor(double valor) const {
        ostringstream stream;
        stream << fixed << setprecision(2) << valor;
        return stream.str();
    }
};

// Classe para gerenciar o menu de operacoes
class Menu {
public:
    void exibir() const {
        cout << "\nMenu:\n";
        cout << "1 - Consultar Saldo\n";
        cout << "2 - Sacar\n";
        cout << "3 - Depositar\n";
        cout << "4 - Exibir Historico de Transacoes\n";
        cout << "5 - Alterar Senha\n";
        cout << "6 - Sair\n";
        cout << "Escolha uma opcao: ";
    }
};

// Classe CaixaEletronico que gerencia as operacoes bancarias
class CaixaEletronico {
private:
    Conta conta;

public:
    CaixaEletronico(Conta contaInicial) : conta(contaInicial) {}

    void iniciar() {
        Menu menu;
        int numeroConta, senhaInserida;

        cout << "Bem-vindo ao caixa eletronico!\n";
        
        // Solicita número da conta e senha
        cout << "Por favor, insira o numero da sua conta: ";
        cin >> numeroConta;
        cout << "Por favor, insira sua senha: ";
        cin >> senhaInserida;

        // Verifica autenticacao com número da conta e senha
        if (conta.autenticar(numeroConta, senhaInserida)) {
            cout << "Acesso concedido.\n";
            int opcao;
            do {
                menu.exibir();
                cin >> opcao;
                processarOpcao(opcao);
            } while (opcao != 6);
        } else {
            cout << "Conta ou senha incorretos. Acesso negado.\n";
        }
    }

private:
    void processarOpcao(int opcao) {
        switch (opcao) {
            case 1:
                consultarSaldo();
                break;
            case 2:
                realizarSaque();
                break;
            case 3:
                realizarDeposito();
                break;
            case 4:
                exibirHistorico();
                break;
            case 5:
                alterarSenha();
                break;
            case 6:
                cout << "Obrigado por usar o caixa eletronico. Ate logo!\n";
                break;
            default:
                cout << "Opcao invalida. Tente novamente.\n";
        }
    }

    void consultarSaldo() const {
        cout << "Seu saldo atual e: R$ " << conta.formatarValor(conta.consultarSaldo()) << endl;
    }

    void realizarSaque() {
        double valorSaque;
        cout << "Insira o valor do saque: ";
        cin >> valorSaque;
        if (conta.sacar(valorSaque)) {
            cout << "Saque realizado com sucesso. Saldo restante: R$ " << conta.formatarValor(conta.consultarSaldo()) << endl;
        }
    }

    void realizarDeposito() {
        double valorDeposito;
        cout << "Insira o valor do deposito: ";
        cin >> valorDeposito;
        conta.depositar(valorDeposito);
        cout << "Deposito realizado com sucesso. Saldo atual: R$ " << conta.formatarValor(conta.consultarSaldo()) << endl;
    }

    void exibirHistorico() const {
        conta.exibirHistoricoTransacoes();
    }

    void alterarSenha() {
        int senhaAntiga, novaSenha;
        cout << "Insira sua senha atual: ";
        cin >> senhaAntiga;
        cout << "Insira sua nova senha: ";
        cin >> novaSenha;
        if (conta.alterarSenha(senhaAntiga, novaSenha)) {
            cout << "Senha alterada com sucesso.\n";
        }
    }
};

// Funcao principal
int main() {
    Conta conta1(12345, 54321, 10000.00); // Conta de teste com saldo inicial de 10000
    CaixaEletronico caixa(conta1);
    caixa.iniciar();

    return 0;
}
