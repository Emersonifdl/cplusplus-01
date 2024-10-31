#include <iostream>
#include <string>

using namespace std;

class Cliente
{
private:
    string nome;
    string cpf;

public:
    // Construtor com nome e cpf como parâmetros e usando lista de inicialização
    Cliente(string nome, string cpf) : nome(nome), cpf(cpf) {}

    // Métodos para obter o nome
    string getNome() const { return nome; }
    // Métodos para obter o cpf
    string getCpf() const { return cpf; }
};

class ContaBancaria
{
private:
    int numero;
    double saldo;
    Cliente titular;

    // Método para verificar se o valor usado nas operações é válido
    bool valorEhValido(double valor) const
    {
        return valor > 0;
    }

    // Método para verificar se há saldo disponível
    bool possuiSaldoSuficiente(double valor) const
    {
        return getSaldo() >= valor;
    }

    // Método para obter metade da transferência
    double metadeDaTransferencia(double valor) const
    {
        return valor / 2;
    }

public:
    // Construtor com número, titular e saldo como parâmetros e usando lista de inicialização
    ContaBancaria(int numero, const Cliente &titular, double saldo = 0.0)
        : numero(numero), saldo(saldo), titular(titular) {}

    // Método para obter o número da conta
    int getNumero() const { return numero; }

    // Método para obter o saldo
    double getSaldo() const { return saldo; }

    // Método para atualizar o saldo
    void setSaldo(double saldoNovo)
    {
        if (!valorEhValido(saldoNovo))
        {
            cout << "Valor de saldo inválido" << endl;
            return;
        }

        // Atualiza o saldo
        saldo = saldoNovo;
    }

    // Método para depositar o valor na conta
    void depositar(double valor)
    {
        if (!valorEhValido(valor))
        {
            cout << "Valor de depósito inválido" << endl;
            return;
        }

        // Realiza o depósito
        setSaldo(getSaldo() + valor);
    }

    // Método para sacar o valor da conta
    void sacar(double valor)
    {

        if (!valorEhValido(valor) || !possuiSaldoSuficiente(valor))
        {
            cout << "Valor de saque inválido ou saldo insuficiente" << endl;
            return;
        }

        // Realiza o saque
        setSaldo(getSaldo() - valor);
    }

    // Método para transferir para 01 conta de destino
    void transferir(double valor, ContaBancaria &destino)
    {
        // Verifica se o valor é válido
        if (!valorEhValido(valor))
        {
            cout << "Valor de transferência inválido" << endl;
            return;
        }

        // Verifica se há saldo suficiente da conta de origem
        if (!possuiSaldoSuficiente(valor))
        {
            cout << "Saldo insuficiente para transferência" << endl;
            return;
        }

        // Realiza a transferência
        setSaldo(getSaldo() - valor);
        destino.depositar(valor);
        cout << "Transferido: R$" << valor << " da conta " << getNumero() << " para a conta " << destino.getNumero() << endl;
    }

    // Método para transferir para 02 contas de destino
    void transferir(double valor_total, ContaBancaria &destino1, ContaBancaria &destino2)
    {
        // Verifica se o valor é válido
        if (!valorEhValido(valor_total))
        {
            cout << "Valor de transferência inválido." << endl;
            return;
        }

        // Verifica se há saldo suficiente da conta de origem
        if (!possuiSaldoSuficiente(valor_total))
        {
            cout << "Saldo insuficiente para transferência" << endl;
            return;
        }

        double metadeTransferencia = metadeDaTransferencia(valor_total);

        setSaldo(getSaldo() - valor_total);

        destino1.depositar(metadeTransferencia);
        destino2.depositar(metadeTransferencia);

        cout << "Transferido: R$" << metadeTransferencia << " para as contas (" << destino1.numero << " e " << destino2.numero << ") da conta " << getNumero() << endl;
    }

    // Método para exibir saldo
    void exibirSaldo() const
    {
        cout << "Saldo atual da conta " << getNumero()
             << ": R$ " << getSaldo()
             << endl;
    }

    // Método para exibir informações do titular e da conta
    void exibirInformacoes() const
    {
        cout << "Titular: " << titular.getNome()
             << ", CPF: " << titular.getCpf() << endl
             << "Conta: " << getNumero()
             << ", Saldo: R$ " << getSaldo()
             << endl;
    }
};

int main()
{
    // Criação dos clientes
    Cliente cliente1("Ana", "111.111.111-11");
    Cliente cliente2("Bruno", "222.222.222-22");
    Cliente cliente3("Carla", "333.333.333-33");

    // Criação das contas bancárias com saldos iniciais
    ContaBancaria conta1(1001, cliente1, 1000.0);
    ContaBancaria conta2(1002, cliente2);
    ContaBancaria conta3(1003, cliente3);

    // Exibe o saldo inicial da conta de Ana
    conta1.exibirSaldo();

    // Ana transfere R$200 para Bruno
    conta1.transferir(200.0, conta2);

    // Ana transfere R$300 divididos entre Bruno e Carla
    conta1.transferir(300.0, conta2, conta3);

    // Exibição dos saldos finais
    cout << endl;
    conta1.exibirInformacoes();
    conta2.exibirInformacoes();
    conta3.exibirInformacoes();

    return 0;
}
