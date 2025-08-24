#include <stdio.h>
#include <ncurses.h>
#include <string.h>

#include "screens.h"

void credits(int y, int x)
{
    const char *text[] = {
        "   ******  *******   ******** *******   ** **********   *******    ********",
        "  **////**/**////** /**///// /**////** /**/////**///   **/////**  **////// ",
        " **    // /**   /** /**      /**    /**/**    /**     **     //**/**       ",
        "/**       /*******  /******* /**    /**/**    /**    /**      /**/*********",
        "/**       /**///**  /**////  /**    /**/**    /**    /**      /**////////**",
        "//**    **/**  //** /**      /**    ** /**    /**    //**     **        /**",
        " //****** /**   //**/********/*******  /**    /**     //*******   ******** ",
        "  //////  //     // //////// ///////   //     //       ///////   ////////  ",
        "",
        "",
        "A U T O R E S",
        "",
        "Pedro Henrique da Silva",
        "Gleydson Henrique Dantas da Silva",
        "",
        "O R I E N T A D O R",
        "",
        "Flavius da Luz e Gorgônio",
        "",
        "I N S T I T U I C A O",
        "",
        "UNIVERSIDADE FEDERAL DO RIO GRANDE DO NORTE",
        "",
        "F E R R A M E N T A S",
        "",
        "Github and Git",
        "Linguagem: C",
        "",
        "P R O J E T O",
        "",
        "https://github.com/PHS-01/SIG-Residence.git",
        "",
        "",
        "",
        "",
        "[0] Voltar"
    };

    int length_text = sizeof(text) / sizeof(text[0]);

    char resp;

    do 
    {
        resp = draw_alert(text, length_text, strlen(text[0]) + 4, 0);
    } 
    while (resp != '0');

}