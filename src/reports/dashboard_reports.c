#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "screens.h"
#include "reports.h"
#include "terminal_control.h"
#include "menu_borders.h"

void dashboard_reports() {
    int opcao;

    do {
        clear_screen();
        
        // Desenha o menu com bordas
        draw_menu_header("RELATORIOS E ESTATISTICAS", MENU_WIDTH);
        draw_menu_option(1, "Relatorio Completo de Pessoas", MENU_WIDTH);
        draw_menu_option(2, "Relatorio de Pessoas Ativas", MENU_WIDTH);
        draw_menu_option(3, "Relatorio Completo de Financas", MENU_WIDTH);
        draw_menu_option(4, "Relatorio de Financas Ativas", MENU_WIDTH);
        draw_menu_option(5, "Relatorio Completo de Residencias", MENU_WIDTH);
        draw_menu_option(6, "Relatorio de Residencias Ativas", MENU_WIDTH);
        draw_menu_option(7, "Relatorio Consolidado Geral", MENU_WIDTH);
        draw_menu_option(8, "Relatorio por Mes de Nascimento", MENU_WIDTH);
        draw_menu_option(9, "Relatorio por Ano de Nascimento", MENU_WIDTH);
        draw_menu_option(10, "Relatorio de Residencia por Estado", MENU_WIDTH);
        draw_menu_option(11, "Relatorio de Financas por Categoria", MENU_WIDTH);
        draw_menu_option(12, "Estatisticas do Sistema", MENU_WIDTH);
        draw_menu_option(0, "Voltar ao Menu anterior", MENU_WIDTH);
        draw_menu_footer(MENU_WIDTH);
        
        printf("\n");
        
        if (!read_int_input("Digite sua opção: ", &opcao)) {
            print_error("Opção inválida! Digite um número.\n");
            wait_for_enter();
            continue;
        }

        clear_screen();

        switch (opcao) {
            case 1:
                generate_people_report(false);
                break;
            case 2:
                generate_people_report(true);
                break;
            case 3:
                generate_finance_report(false);
                break;
            case 4:
                generate_finance_report(true);
                break;
            case 5:
                generate_residence_report(false);
                break;
            case 6:
                generate_residence_report(true);
                break;
            case 7:
                generate_consolidated_report();
                break;
            case 8:
                generate_birth_report(true);
                break;
            case 9:
                generate_birth_report(false);
                break;
            case 10:
                generate_residence_by_state();
                break;
            case 11:
                generate_finance_by_category();
                break;
            case 12:
                show_system_statistics();
                break;
            case 0:
                print_success("Retornando ao menu principal...");
                break;
        }

        if (opcao != 0 && opcao >= 1 && opcao <= 12) {
            printf("\n");
            print_info("[ Pressione ENTER para continuar ]");
            wait_for_enter();
        }

    } while (opcao != 0);
}