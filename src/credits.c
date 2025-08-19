#include <stdio.h>
#include <ncurses.h>
#include <string.h>

void credits(int y, int x)
{
    char *titulo[] = {
        "####################################################",
        "-----             C R E D I T O S              -----",
        ">>>    Projeto de Sistema de gestão de despesa   <<<",
        "####################################################",
        ""
    };

    char *autores[] = {
        "####################################################",
        "-----              A U T O R E S                ----",
        ">>>       Gleydson Henrique Dantas da Silva      <<<",
        ">>>            Pedro Henrique da Silva           <<<",
        "####################################################",
        ""
    };

    char *orientador[] = {
        "-----           O R I E N T A D O R            -----",
        ">>>           Flavius da Luz e Gorgônio          <<<",
        "####################################################",
        ""
    };

    char *instituicao[] = {
        "-----           I N S T I T U I Ç Ã O          -----",
        ">>> UNIVERSIDADE FEDERAL DO RIO GRANDE DO NORTE  <<<",
        "####################################################",
        ""
    };

    char *ferramentas[] = {
        "---             F E R R A M E N T A S            ---",
        ">>>                   Github                     <<<",
        ">>>                    Git                       <<<",
        ">>>                 Linguagem: C                 <<<",
        ">>>               Compilador: GCC                <<<",
        "####################################################",
        ""
    };

    char *projeto[] = {
        "-----             P R O J E T O                -----",
        ">>> Repositório:                                 <<<",
        ">>> https://github.com/PHS-01/SIG-Residence.git  <<<",
        "####################################################",
        ""
    };

    // Juntar todas as seções num vetor
    char **secoes[] = {titulo, autores, orientador, instituicao, ferramentas, projeto};
    int tamanhos[] = {
        sizeof(titulo)/sizeof(titulo[0]),
        sizeof(autores)/sizeof(autores[0]),
        sizeof(orientador)/sizeof(orientador[0]),
        sizeof(instituicao)/sizeof(instituicao[0]),
        sizeof(ferramentas)/sizeof(ferramentas[0]),
        sizeof(projeto)/sizeof(projeto[0])
    };

    int h = 2;

    // Printar seção por seção, centralizando
    for (int s = 0; s < 6; s++) {
        for (int i = 0; i < tamanhos[s]; i++) {
            mvprintw(h, (x/2) - (strlen(secoes[s][i]) / 2), "%s", secoes[s][i]);
            h++;
        }
        h += 1;
    }

    // Pequeno rodapé
    mvprintw(y-3, 16, "[0] Voltar ao Menu");
}