#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CLIENTES 100
#define MAX_FORNECEDORES 100
#define MAX_FESTAS 100
#define MAX_CONTRATOS 100

typedef struct {
    int codigo;
    char nome[50];
    char endereco[100];
    char telefone[20];
    char data_nascimento[11];
} Cliente;

typedef struct {
    int codigo;
    char nome_buffet[50];
    char telefone[20];
} Fornecedor;

typedef struct {
    int codigo_festa;
    int quantidade_convidados;
    char data[11];
    char dia_semana[20];
    char horario[20];
    char tema[50];
    int codigo_cliente;
    int codigo_fornecedor;
} Festa;

typedef struct {
    int numero_contrato;
    float valor_total;
    float desconto;
    float valor_final;
    char forma_pagamento[20];
    char status[20];
    int codigo_festa;
} Contrato;

Cliente clientes[MAX_CLIENTES];
int num_clientes = 0;

Fornecedor fornecedores[MAX_FORNECEDORES];
int num_fornecedores = 0;

Festa festas[MAX_FESTAS];
int num_festas = 0;

Contrato contratos[MAX_CONTRATOS];
int num_contratos = 0;

void cadastrar_cliente() {
    int codigo;
    printf("Digite o codigo do cliente: ");
    scanf("%d", &codigo);

    // Verificar se o cliente já está cadastrado
    for (int i = 0; i < num_clientes; i++) {
        if (clientes[i].codigo == codigo) {
            printf("Cliente ja cadastrado com o mesmo codigo.\n");
            return;
        }
    }

    // Preencher os dados do cliente
    clientes[num_clientes].codigo = codigo;
    printf("Digite o nome do cliente: ");
    scanf(" %[^\n]", clientes[num_clientes].nome);
    printf("Digite o endereco do cliente: ");
    scanf(" %[^\n]", clientes[num_clientes].endereco);
    printf("Digite o telefone do cliente: ");
    scanf(" %[^\n]", clientes[num_clientes].telefone);
    printf("Digite a data de nascimento do cliente (dd/mm/aaaa): ");
    scanf(" %[^\n]", clientes[num_clientes].data_nascimento);

    num_clientes++;
    printf("Cliente cadastrado com sucesso.\n");
}

void cadastrar_fornecedor() {
    int codigo;
    printf("Digite o codigo do fornecedor: ");
    scanf("%d", &codigo);

    // Verificar se o fornecedor já está cadastrado
    for (int i = 0; i < num_fornecedores; i++) {
        if (fornecedores[i].codigo == codigo) {
            printf("Fornecedor ja cadastrado com o mesmo codigo.\n");
            return;
        }
    }

    // Preencher os dados do fornecedor
    fornecedores[num_fornecedores].codigo = codigo;
    printf("Digite o nome do buffet do fornecedor: ");
    scanf(" %[^\n]", fornecedores[num_fornecedores].nome_buffet);
    printf("Digite o telefone do fornecedor: ");
    scanf(" %[^\n]", fornecedores[num_fornecedores].telefone);

    num_fornecedores++;
    printf("Fornecedor cadastrado com sucesso.\n");
}

int verificar_disponibilidade_festa(char* data, char* horario) {
    for (int i = 0; i < num_festas; i++) {
        if (strcmp(festas[i].data, data) == 0 && strcmp(festas[i].horario, horario) == 0) {
            return 0; // Festa já cadastrada para a mesma data e horário
        }
    }
    return 1; // Disponível para cadastrar a festa
}

void cadastrar_festa() {
    int codigo_cliente, codigo_fornecedor;
    printf("Digite o codigo do cliente: ");
    scanf("%d", &codigo_cliente);

    // Verificar se o cliente está cadastrado
    int cliente_encontrado = 0;
    for (int i = 0; i < num_clientes; i++) {
        if (clientes[i].codigo == codigo_cliente) {
            cliente_encontrado = 1;
            break;
        }
    }

    if (!cliente_encontrado) {
        printf("Cliente nao encontrado.\n");
        return;
    }

    // Preencher os dados da festa
    festas[num_festas].codigo_cliente = codigo_cliente;
    printf("Digite a quantidade de convidados da festa: ");
    scanf("%d", &festas[num_festas].quantidade_convidados);
    printf("Digite a data da festa (dd/mm/aaaa): ");
    scanf(" %[^\n]", festas[num_festas].data);
    printf("Digite o dia da semana da festa: ");
    scanf(" %[^\n]", festas[num_festas].dia_semana);

    // Verificar se a festa já está cadastrada para a mesma data
    if (!verificar_disponibilidade_festa(festas[num_festas].data, "")) {
        printf("Ja existe uma festa cadastrada para a mesma data e horario.\n");
        return;
    }

    // Definir o horário da festa
    if (strcmp(festas[num_festas].dia_semana, "sabado") == 0) {
        strcpy(festas[num_festas].horario, "12h-16h ou 18h-22h");
    } else {
        printf("Digite o horario de inicio da festa: ");
        scanf(" %[^\n]", festas[num_festas].horario);
    }

    printf("Digite o tema da festa: ");
    scanf(" %[^\n]", festas[num_festas].tema);

    printf("Digite o codigo do fornecedor: ");
    scanf("%d", &codigo_fornecedor);

    // Verificar se o fornecedor está cadastrado
    int fornecedor_encontrado = 0;
    for (int i = 0; i < num_fornecedores; i++) {
        if (fornecedores[i].codigo == codigo_fornecedor) {
            fornecedor_encontrado = 1;
            break;
        }
    }

    if (!fornecedor_encontrado) {
        printf("Fornecedor nao encontrado.\n");
        return;
    }

    festas[num_festas].codigo_fornecedor = codigo_fornecedor;
    festas[num_festas].codigo_festa = num_festas + 1; // Gerar um código sequencial para a festa

    num_festas++;
    printf("Festa cadastrada com sucesso.\n");
}

float calcular_valor_total(int quantidade_convidados, char* dia_semana) {
    float valor = 0.0;

    if (quantidade_convidados == 30) {
        if (strcmp(dia_semana, "segunda a quinta") == 0) {
            valor = 1899.0;
        } else {
            valor = 2099.0;
        }
    } else if (quantidade_convidados == 50) {
        if (strcmp(dia_semana, "segunda a quinta") == 0) {
            valor = 2199.0;
        } else {
            valor = 2299.0;
        }
    } else if (quantidade_convidados == 80) {
        if (strcmp(dia_semana, "segunda a quinta") == 0) {
            valor = 3199.0;
        } else {
            valor = 3499.0;
        }
    } else if (quantidade_convidados == 100) {
        if (strcmp(dia_semana, "segunda a quinta") == 0) {
            valor = 3799.0;
        } else {
            valor = 3999.0;
        }
    }

    return valor;
}

float calcular_desconto(char* forma_pagamento) {
    float desconto = 0.0;

    if (strcmp(forma_pagamento, "a vista") == 0) {
        desconto = 0.1;
    } else if (strcmp(forma_pagamento, "duas vezes") == 0) {
        desconto = 0.05;
    } else if (strcmp(forma_pagamento, "tres vezes") == 0) {
        desconto = 0.02;
    }

    return desconto;
}

void cadastrar_contrato() {
    int codigo_festa;
    printf("Digite o codigo da festa: ");
    scanf("%d", &codigo_festa);

    // Verificar se a festa está cadastrada
    int festa_encontrada = 0;
    int indice_festa;
    for (int i = 0; i < num_festas; i++) {
        if (festas[i].codigo_festa == codigo_festa) {
            festa_encontrada = 1;
            indice_festa = i;
            break;
        }
    }

    if (!festa_encontrada) {
        printf("Festa nao encontrada.\n");
        return;
    }

    float valor_total = calcular_valor_total(festas[indice_festa].quantidade_convidados, festas[indice_festa].dia_semana);

    // Preencher os dados do contrato
    contratos[num_contratos].numero_contrato = num_contratos + 1; // Gerar um número sequencial para o contrato
    contratos[num_contratos].valor_total = valor_total;
    contratos[num_contratos].desconto = calcular_desconto("a vista");
    contratos[num_contratos].valor_final = valor_total - (valor_total * contratos[num_contratos].desconto);
    strcpy(contratos[num_contratos].forma_pagamento, "a vista");
    strcpy(contratos[num_contratos].status, "a pagar");
    contratos[num_contratos].codigo_festa = codigo_festa;

    num_contratos++;
    printf("Contrato cadastrado com sucesso.\n");
}

void atualizar_status_contrato() {
    int numero_contrato;
    printf("Digite o numero do contrato: ");
    scanf("%d", &numero_contrato);

    // Verificar se o contrato existe
    int contrato_encontrado = 0;
    for (int i = 0; i < num_contratos; i++) {
        if (contratos[i].numero_contrato == numero_contrato) {
            contrato_encontrado = 1;
            strcpy(contratos[i].status, "pago");
            break;
        }
    }

    if (!contrato_encontrado) {
        printf("Contrato nao encontrado.\n");
        return;
    }

    printf("Status do contrato atualizado para pago.\n");
}

void exibir_clientes() {
    printf("Clientes cadastrados:\n");
    for (int i = 0; i < num_clientes; i++) {
        printf("Codigo: %d\n", clientes[i].codigo);
        printf("Nome: %s\n", clientes[i].nome);
        printf("Endereco: %s\n", clientes[i].endereco);
        printf("Telefone: %s\n", clientes[i].telefone);
        printf("Data de nascimento: %s\n", clientes[i].data_nascimento);
        printf("----------\n");
    }
}

void exibir_fornecedores() {
    printf("Fornecedores cadastrados:\n");
    for (int i = 0; i < num_fornecedores; i++) {
        printf("Codigo: %d\n", fornecedores[i].codigo);
        printf("Nome do buffet: %s\n", fornecedores[i].nome_buffet);
        printf("Telefone: %s\n", fornecedores[i].telefone);
        printf("----------\n");
    }
}

void exibir_festas() {
    printf("Festas cadastradas:\n");
    for (int i = 0; i < num_festas; i++) {
        printf("Codigo da festa: %d\n", festas[i].codigo_festa);
        printf("Codigo do cliente: %d\n", festas[i].codigo_cliente);
        printf("Quantidade de convidados: %d\n", festas[i].quantidade_convidados);
        printf("Data: %s\n", festas[i].data);
        printf("Dia da semana: %s\n", festas[i].dia_semana);
        printf("Horario: %s\n", festas[i].horario);
        printf("Tema: %s\n", festas[i].tema);
        printf("Codigo do fornecedor: %d\n", festas[i].codigo_fornecedor);
        printf("----------\n");
    }
}

void exibir_contratos() {
    printf("Contratos cadastrados:\n");
    for (int i = 0; i < num_contratos; i++) {
        printf("Numero do contrato: %d\n", contratos[i].numero_contrato);
        printf("Valor total: %.2f\n", contratos[i].valor_total);
        printf("Desconto: %.2f\n", contratos[i].desconto);
        printf("Valor final: %.2f\n", contratos[i].valor_final);
        printf("Forma de pagamento: %s\n", contratos[i].forma_pagamento);
        printf("Status: %s\n", contratos[i].status);
        printf("Codigo da festa: %d\n", contratos[i].codigo_festa);
        printf("----------\n");
    }
}

int main() {
    int opcao;

    do {
        printf("Selecione uma opcao:\n");
        printf("1. Cadastrar cliente\n");
        printf("2. Cadastrar fornecedor\n");
        printf("3. Cadastrar festa\n");
        printf("4. Cadastrar contrato\n");
        printf("5. Atualizar status do contrato\n");
        printf("6. Exibir clientes\n");
        printf("7. Exibir fornecedores\n");
        printf("8. Exibir festas\n");
        printf("9. Exibir contratos\n");
        printf("0. Sair\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar_cliente();
                break;
            case 2:
                cadastrar_fornecedor();
                break;
            case 3:
                cadastrar_festa();
                break;
            case 4:
                cadastrar_contrato();
                break;
            case 5:
                atualizar_status_contrato();
                break;
            case 6:
                exibir_clientes();
                break;
            case 7:
                exibir_fornecedores();
                break;
            case 8:
                exibir_festas();
                break;
            case 9:
                exibir_contratos();
                break; 
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }

    } while (opcao != 0);

    return 0;
}
