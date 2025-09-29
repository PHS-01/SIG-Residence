#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Funções que desenham as telas
#include "screens.h"
// Funções para controle do terminal e manipulação do texto
#include "terminal_control.h"

// Lista de pessoas
char people[4][50] = {
    "Name 1",
    "Name 2",
    "Name 3",
    "Name 4"
};

int get_max_string_length(const char* strings[], int count) {
    int max_length = 0;

    for (int i = 0; i < count; i++) {
        int current_length = strlen(strings[i]);
        if (current_length > max_length) {
            max_length = current_length;
        }
    }

    return max_length;
}

// Função para desenhar o card de cada pessoa dentro de uma caixa
void draw_user_card(int y, int x, const char* name) {
    int card_width = 35;  // Largura do card
    int card_height = 5;  // Altura do card (3 linhas para o conteúdo e 1 linha para o topo/borda)

    // Desenha a caixa ao redor do card
    draw_box(y, x, card_height, card_width);

    // Ícone de usuário (desenhado em 3 linhas)
    const char* user_icon[] = {
        "  ┌─┐  ",  
        "  └─┘  ", 
        " ┌───┐ "
    };

    // Desenha o ícone de usuário (desenhando em 3 linhas)
    for (int i = 0; i < 3; i++) {
        ansi_print(y + i + 1, x + 1, user_icon[i]);
    }

    // Desenha o nome do usuário logo após o ícone
    ansi_print(y + 2, x + 10, name);  // O nome começa após o ícone (com 8 espaços de distância)
}


// Função para desenhar a lista de pessoas dentro de caixas
void draw_people_list(int rows, int cols) {
    int start_y = rows / 6;  // Começar após a borda superior
    int start_x = cols + 2;  // Começar logo após a borda esquerda, mais à direita

    // Desenha cada card de pessoa dentro de uma caixa
    for (int i = 0; i < 4; i++) {
        // Cada card será desenhado com espaçamento entre eles (2 linhas de distância)
        draw_user_card(start_y + i * 5, start_x, people[i]);
    }
}

// Função para desenhar o painel de opções
void draw_options_panel(int rows, int cols) {
    const char *options[] = {
        "[1] Criar Pessoa",
        "[2] Ler Pessoa",
        "[3] Atualizar Pessoa",
        "[4] Excluir Pessoa",
        "[0] Voltar"
    };

    int length_options = sizeof(options) / sizeof(options[0]);
    int start_y = (rows - length_options) / 2;  // Centraliza verticalmente na tela
    int max_length = get_max_string_length(options, length_options);
    int x_pos = (cols - max_length) / 2;

    // Desenha as opções dentro da caixa esquerda, alinhadas à esquerda
    for (int i = 0; i < length_options; i++) {
        // Alinhamento à esquerda dentro da largura da caixa
        ansi_print(start_y + i * 2, x_pos, options[i]); // espaçamento vertical entre as opções
    }
}

// Função principal do dashboard
void dashboard_people(void) {
    int rows = 0, cols = 0;
    update_terminal_size(&rows, &cols);  // Pega o tamanho atual da tela

    int left_width = cols / 4;    // Largura da caixa da esquerda (opções)
    int right_width = cols - left_width  + 1;  // Largura da caixa da direita (pessoas)

    char resp;

    do {
        clear_screen();
        system("clear");

        draw_box(1, 1, 3, cols);                        // Caixa superior
        draw_box(4, 1, rows - 3, left_width - 1);       // Caixa esquerda
        draw_box(4, left_width, rows - 3, right_width); // Caixa direita

        // Desenha o painel de opções (à esquerda)
        draw_options_panel(rows, left_width);

        // Desenha a lista de pessoas (à direita)
        draw_people_list(rows, left_width);

        resp = get_keypress();  // Lê a resposta do usuário

        // Ações baseadas na tecla pressionada
        switch (resp) {
            case '1':
                // create_people();  // Função para criar pessoa
                break;
            case '2':
                // read_people();  // Função para ler pessoa
                break;
            case '3':
                // update_people();  // Função para atualizar pessoa
                break;
            case '4':
                // delete_people();  // Função para excluir pessoa
                break;
            case '0':
                break;
            default:
                break;
        }

    } while (resp != '0');
}