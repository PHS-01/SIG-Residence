#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "screens.h"
#include "residence.h"
#include "terminal_control.h"
#include "menu_borders.h"

void dashboard_residence() {
    int opcao;

    do {
        clear_screen();
        
        // Desenha o menu com bordas
        draw_menu_header("GESTAO DE RESIDENCIAS", MENU_WIDTH);
        draw_menu_option(1, "Cadastrar nova residencia", MENU_WIDTH);
        draw_menu_option(2, "Consultar residencia", MENU_WIDTH);
        draw_menu_option(3, "Atualizar residencia", MENU_WIDTH);
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
                draw_simple_header("CADASTRO DE RESIDENCIA", MENU_WIDTH);
                create_residence_ui();
                break;
            case 2:
                draw_simple_header("CONSULTAR RESIDENCIA", MENU_WIDTH);
                read_residence_ui();
                break;
            case 3:
                draw_simple_header("ATUALIZAR RESIDENCIA", MENU_WIDTH);
                update_residence_ui();
                break;
            case 4:
                draw_simple_header("EXCLUSAO LOGICA DE RESIDENCIA", MENU_WIDTH);
                delete_residence_ui();
                break;
            case 5:
                draw_simple_header("EXCLUSAO FISICA DE RESIDENCIA", MENU_WIDTH);
                physical_delete_residence_ui();
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