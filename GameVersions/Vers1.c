//Protótipo Base MENU

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct BaseTable{   // struct que funciona como se fosse uma matriz, base pro tabuleiro e etc
    char coluna[16];
    int linha[16];
};
    
// Prototipos das funcoes
void exibir_ajuda();
void iniciar_jogo();
void marcar_pontos(int jogador);
void marcar_tiro(struct BaseTable *tiros, struct BaseTable *tabuleiro, int jogador, int lin_temp, char col_temp);
void gravar_jogo();
void carregar_jogo();
void funcao_zera_pontos();


int main(){
    //definicoes bases do jogo
    char comando[16];               // char responsavel por salvar os comandos
    int status = 0;                 // eh uma 'flag' para sabermos quando encerrar o jogo (ver o 'while' abaixo)
    struct BaseTable tabuleiro[2];  // definir duas matrizes diferentes, uma para cada jogador
    struct BaseTable tiros[2];      // a matriz tabuleiro eh onde poe os navios e a tiros onde registramos os disparos
    int pl = 0;                     // player 1 ou player 2
    iniciar_jogo(tabuleiro);        //chama a funcao iniciar_jogo

    
    while (status == 0){        // funciona como se fosse o menu do jogo, cada comando digitado leva o jogador a uma outra funcao
        printf ("\nInsira um comando, jogador #%d\n", ((pl%2)+1));
        scanf (" %s[^\n]", comando);
        for(int i = 0; i < 10; i++)
            comando[i]=toupper(comando[i]); //converte o comando de cada jogador para caixa alta, facilitando a vida de todo mundo

        int jogador = pl%2; //uma outra variavel, que sera repassada para as outras funcoes definindo qual player esta jogando
        
        if (strcmp (comando, "SAIR") == 0){
            funcao_zera_pontos();
            status = 1; //define 'status' como 1, assim saindo do ciclo e encerrando o programa
        }
        else if (strcmp (comando, "POW") == 0){
            int lin_temp;
            char col_temp;
            scanf (" %c%d", &col_temp, &lin_temp); //registra a coordenada do tiro
            marcar_tiro (tiros, tabuleiro, jogador, lin_temp, col_temp);
            fflush (stdin);
            pl = pl+1;
            //soma 1 ao valor de pl sempre que alguem atira, assim conseguimos manter uma contagem de quem esta atirando no momento
        }
        else if (strcmp (comando, "RESET") == 0){   //chama as funcoes zera pontos e iniciar jogo
            funcao_zera_pontos();                   //assim, reinicia-se o jogo com pontuacoes zeradas
            iniciar_jogo ();
        }
        else if (strcmp(comando, "AJUDA") == 0){    //simplesmente chama a funcao ajuda, que printa os comandos na tela
            exibir_ajuda();
        }
        else if (strcmp (comando, "GRAVAR") == 0){  //chama a funcao gravar
            gravar_jogo();
        }
        else if (strcmp (comando, "CARREGAR") == 0){//chama a funcao carregar
            carregar_jogo();
        }
        else if (strcmp (comando, "ACASO") == 0){  //reinicia o jogo  mas salva as pontuacoes, pois nao chama a 'funcao_zera_pontos'
            printf ("\n\nREINICIANDO O JOGO E MANTENDO AS PONTUACOES ATUAS\nREPOSICIONEM SUAS ARMADAS!\n");
            pl = 0;
            fflush (stdin);
            iniciar_jogo();
        }
        else{   //caso o comando inserido nao seja valido:
            printf ("\n O COMANDO '%s' E DESCONHECIDO, INSIRA UM COMANDO VALIDO\n\nSe precisar de ajuda com os comandos, utilize o comando 'ajuda'\n", comando);
        }
    }

printf ("\nsucess");

return 0;  
}

void exibir_ajuda(){        // exibir todos os comandos, um menu de ajuda

printf ("\n\tLISTA DE COMANDOS:");
printf ("\n\t'ajuda' \tExibe esta lista de comandos!");
printf ("\n\t'POW'     \tInsira o comando POW seguido das coordenadas onde voce deseja atirar!");
printf ("\n\t'reset' \tReinicia o jogo inteiro, zerando as pontuacoes!");
printf ("\n\t'acaso' \tReinicia o jogo inteiro, mas mantem as pontuacoes!");
printf ("\n\t'gravar' \tSalva o jogo, para voce continua-lo depois!");
printf ("\n\t'carregar' \tCarrega um jogo salvo!");
printf ("\n\t'sair'    \tFecha o aplicativo :( \n");
}

void iniciar_jogo(){
    
    // printar as matrizes - tabuleiros
    // posicionar os navios
    // gerar as duas contagens de pontos
    // chamar a funcao exibir_ajuda para ja mostrar os comandos incluidos
    exibir_ajuda();
}

void marcar_pontos(int jogador){
    // funcao responsavel por marcar os pontos de cada tiro
}

void marcar_tiro(struct BaseTable *tiros, struct BaseTable *tabuleiro, int jogador, int lin_temp, char col_temp){
    printf ("TIRO EM %c%d", col_temp, lin_temp);
    // compara a coordenada informada com as coordenadas onde os navios estao
    // chamar a funcao marcar_pontos
    marcar_pontos(jogador);

}

void gravar_jogo(){
    // salva o jogo em um arquivo (como fazer isso???)
}

void carregar_jogo(){
    // carrega algum arquivo do jogo previamente salvo
}

void funcao_zera_pontos(){

}