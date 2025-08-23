#include <stdio.h>

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

    printf("Pressione ENTER para sair...");
    getchar(); getchar();
}

// Função - Verificar Usuário
void check_user(char nome[], char cpf[], char data_nascimento[], char matricula[], char email[], char telefone[], char endereco[]) {
    printf("╔══════════════════════════════════════════╗\n");
    printf("║            VERIFICAR_USUÁRIO             ║\n"); // Adicionar o CPF para verificar os dados de cada usuário
    printf("╚══════════════════════════════════════════╝\n");
    printf("[o] - Nome: %s\n", nome); 
    printf("[o] - CPF: %s\n", cpf);
    printf("[o] - Data de Nascimento: %s\n", data_nascimento);
    printf("[o] - Matrícula: %s\n",matricula); 
    printf("[o] - E-mail: %s\n", email);
    printf("[o] - Telefone: %s\n", telefone);
    printf("[o] - Endereço: %s\n", endereco);
    
    printf("Pressione ENTER para sair...");
    getchar(); getchar();
}

// Função - Alterar Usuário
void change_user(char nome[], char cpf[], char data_nascimento[], char matricula[], char email[], char telefone[], char endereco[]) {
    printf("╔══════════════════════════════════════════╗\n");
    printf("║              ALTERAR_USUÁRIO             ║\n"); 
    printf("╚══════════════════════════════════════════╝\n");
    printf("[o] - Digite seus novos dados: \n"); // Futuramente adicionar o CPF e exibir os dados para alteração 
    
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

    printf("[✔] - Dados alterados com sucesso!\n");

    printf("Pressione ENTER para sair...");
    getchar(); getchar();
}

// Função - Excluir Usuário
void delete_user(char nome[], char cpf[], char data_nascimento[], char matricula[], char email[], char telefone[], char endereco[]) {
    char op_delete;

    printf("╔══════════════════════════════════════════╗\n");
    printf("║              EXCLUIR_USUÁRIO             ║\n"); 
    printf("╚══════════════════════════════════════════╝\n");
    printf("[o] - Insira seu CPF: \n"); // CPF usado para verificação dos dados anexados a ele.

    printf("[o] - Nome: %s\n", nome);
    printf("[o] - CPF: %s\n", cpf);
    printf("[o] - Data de Nascimento: %s\n", data_nascimento);
    printf("[o] - Matrícula: %s\n",matricula); 
    printf("[o] - E-mail: %s\n", email);
    printf("[o] - Telefone: %s\n", telefone);
    printf("[o] - Endereço: %s\n", endereco);
    
    printf("[!] - Excluir dados? (S/N)"); // Confirmação para excluir os dados
    scanf("%c", op_delete);

    if (op_delete == 'S' || op_delete == 's') {
    printf("[✔] - Usuário excluído com sucesso!\n");
    }

    else if (op_delete == 'N' || op_delete == 'n') {
    printf("[i] - Exclusão cancelada.\n");
    }

    else {
    printf("[x] - Resposta inválida!\n");
    }

    printf("Pressione ENTER para sair...");
    getchar(); getchar();
}
