#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "screens.h"
#include "people.h"
#include "terminal_control.h"
#include "menu_borders.h"

void dashboard_people() {
    int opcao;

    do {
        clear_screen();
        
        // Desenha o menu com bordas
        draw_menu_header("GESTAO DE PESSOAS", MENU_WIDTH);
        draw_menu_option(1, "Cadastrar nova pessoa", MENU_WIDTH);
        draw_menu_option(2, "Consultar pessoa", MENU_WIDTH);
        draw_menu_option(3, "Atualizar pessoa", MENU_WIDTH);
        draw_menu_option(4, "Exclusao logica (inativar)", MENU_WIDTH);
        draw_menu_option(5, "Exclusao fisica (permanente)", MENU_WIDTH);
        draw_menu_option(0, "Voltar ao Menu anterior", MENU_WIDTH);
        draw_menu_footer(MENU_WIDTH);
        
        printf("\n");
        
        if (!read_int_input("Digite sua opção: ", &opcao)) {
            print_error("Opção inválida! Digite um número.");
            wait_for_enter();
            continue;
        }

        clear_screen();

        switch (opcao) {
            case 1:
                draw_simple_header("CADASTRO DE PESSOA", MENU_WIDTH);
                create_people_ui();
                break;
            case 2:
                draw_simple_header("CONSULTAR PESSOA", MENU_WIDTH);
                read_people_ui();
                break;
            case 3:
                draw_simple_header("ATUALIZAR PESSOA", MENU_WIDTH);
                update_people_ui();
                break;
            case 4:
                draw_simple_header("EXCLUSAO LOGICA DE PESSOA", MENU_WIDTH);
                delete_people_ui();
                break;
            case 5:
                draw_simple_header("EXCLUSAO FISICA DE PESSOA", MENU_WIDTH);
                physical_delete_people_ui();
                break;
            case 0:
                break;
        }

        if (opcao != 0 && opcao >= 1 && opcao <= 5) {
            printf("\n");
            print_info("[ Pressione ENTER para continuar ]");
            wait_for_enter();
        }

    } while (opcao != 0);
}