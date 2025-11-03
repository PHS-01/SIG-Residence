#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "finance.h"
#include "terminal_control.h"
#include "menu_borders.h"

void dashboard_finance() {
    int opcao;

    do {
        clear_screen();
        
        // Desenha o menu com bordas
        draw_menu_header("GESTAO DE FINANCAS", MENU_WIDTH);
        draw_menu_option(1, "Cadastrar nova transacao", MENU_WIDTH);
        draw_menu_option(2, "Consultar transacao", MENU_WIDTH);
        draw_menu_option(3, "Atualizar transacao", MENU_WIDTH);
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
                draw_simple_header("CADASTRO DE TRANSACAO", MENU_WIDTH);
                create_finance_ui();
                break;
            case 2:
                draw_simple_header("CONSULTAR TRANSACAO", MENU_WIDTH);
                read_finance_ui();
                break;
            case 3:
                draw_simple_header("ATUALIZAR TRANSACAO", MENU_WIDTH);
                update_finance_ui();
                break;
            case 4:
                draw_simple_header("EXCLUSAO LOGICA DE TRANSACAO", MENU_WIDTH);
                delete_finance_ui();
                break;
            case 5:
                draw_simple_header("EXCLUSAO FISICA DE TRANSACAO", MENU_WIDTH);
                physical_delete_finance_ui();
                break;
            case 0:
                print_success("Retornando ao menu principal...");
                break;
        }

        if (opcao != 0 && opcao >= 1 && opcao <= 5) {
            printf("\n");
            print_info("[ Pressione ENTER para continuar ]");
            wait_for_enter();
        }

    } while (opcao != 0);
}