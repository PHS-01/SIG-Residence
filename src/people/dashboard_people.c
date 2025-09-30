#include <stdio.h>
#include <string.h>
#include "screens.h"

// Array global de pessoas
char people[4][50];

// --- Funções auxiliares para desenhar a tela ---
// (essas você já deve ter em ansi_utils.c / ui_elements.c)
void clear_screen(void);
void draw_box(int x, int y, int w, int h);
void set_cursor(int x, int y);

// Redesenha o painel de pessoas
static void draw_people_list(void) {
    printf("\nPessoas cadastradas:\n");
    for (int i = 0; i < 4; i++) {
        if (strcmp(people[i], "Vazio") == 0 || people[i][0] == '\0') {
            printf(" [%d] (vazio)\n", i + 1);
        } else {
            printf(" [%d] %s\n", i + 1, people[i]);
        }
    }
}

// Redesenha o menu
static void draw_options_panel(void) {
    printf("\nOpções:\n");
    printf(" [1] Criar Pessoa\n");
    printf(" [2] Listar Pessoas\n");
    printf(" [3] Atualizar Pessoa\n");
    printf(" [4] Deletar Pessoa\n");
    printf(" [0] Voltar\n");
}

// --- Menu principal ---
void dashboard_people(void) {
    int option = -1;

    load_people("people.txt", people);

    while (1) {
        clear_screen();          // limpa a tela
        draw_people_list();      // mostra lista
        draw_options_panel();    // mostra menu
        printf("\nEscolha uma opção: ");
        if (scanf("%d", &option) != 1) {
            while (getchar() != '\n'); // limpa stdin
            continue;
        }
        while (getchar() != '\n'); // limpa buffer

        switch (option) {
            case 1:
                create_people(people);
                save_people("people.txt", people);
                break;
            case 2:
                read_people(people);
                break;
            case 3:
                update_people(people);
                save_people("people.txt", people);
                break;
            case 4:
                delete_people(people);
                save_people("people.txt", people);
                break;
            case 0:
                return; // volta ao menu anterior
            default:
                printf("Opção inválida.\n");
        }

        printf("\nPressione ENTER para continuar...");
        getchar();
    }
}
