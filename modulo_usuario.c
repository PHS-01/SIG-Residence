#include <stdio.h>
#include <stdlib.h> // para usar system()

// Função principal - Módulo Usuário
int user(void) {
    int op_user;

    printf("╔══════════════════════════════════════════╗\n");
    printf("║              MODULO_USUARIO              ║\n");
    printf("║ ---------------------------------------- ║\n");
    printf("║         [1] - Cadastrar_Usuário          ║\n");
    printf("║         [2] - Verificar_Usuário          ║\n");
    printf("║         [3] - Alterar_Usuário            ║\n");
    printf("║         [4] - Excluir_Usuário            ║\n");
    printf("║         [0] - Sair                       ║\n");
    printf("╚══════════════════════════════════════════╝\n");
    printf("[?] Escolha uma opção: ");
    scanf("%d", &op_user);

    return op_user;
}

// Função - Cadastrar Usuário
void login_user(char nome[], char cpf[], char data_nascimento[], char matricula[], char email[], char telefone[], char endereco[]) {
    printf("╔══════════════════════════════════════════╗\n");
    printf("║            CADASTRAR_USUÁRIO             ║\n"); 
    printf("╚══════════════════════════════════════════╝\n");

    printf("[+] - Nome: ");
    scanf(" %[^\n]", nome);

    printf("[+] - CPF: ");
    scanf(" %[^\n]", cpf);

    printf("[+] - Data de Nascimento: ");
    scanf(" %[^\n]", data_nascimento);

    printf("[+] - Matrícula: ");
    scanf(" %[^\n]", matricula);

    printf("[+] - E-mail: ");
    scanf(" %[^\n]", email);

    printf("[+] - Telefone: ");
    scanf(" %[^\n]", telefone);

    printf("[+] - Endereço: ");
    scanf(" %[^\n]", endereco);

    printf("[✔] - Usuário cadastrado com sucesso!\n");

    printf("Pressione ENTER para continuar...");
    getchar(); getchar(); // pausa
}

// Função - Verificar Usuário
void check_user(char nome[], char cpf[], char data_nascimento[], char matricula[], char email[], char telefone[], char endereco[]) {
    printf("╔══════════════════════════════════════════╗\n");
    printf("║            VERIFICAR_USUÁRIO             ║\n"); 
    printf("╚══════════════════════════════════════════╝\n");
    printf("[o] - Nome: %s\n", nome);
    printf("[o] - CPF: %s\n", cpf);
    printf("[o] - Data de Nascimento: %s\n", data_nascimento);
    printf("[o] - Matrícula: %s\n",matricula); 
    printf("[o] - E-mail: %s\n", email);
    printf("[o] - Telefone: %s\n", telefone);
    printf("[o] - Endereço: %s\n", endereco);
    
    printf("Pressione ENTER para sair...");
    getchar();
    getchar();
}


