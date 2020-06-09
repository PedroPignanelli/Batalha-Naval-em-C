//Protótipo Base MENU

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct BaseTable{   // struct que funciona como se fosse uma matriz, base pro tabuleiro e etc
    char posicao[16][16];
};
    
// Prototipos das funcoes
void layout_menu();
void exibir_ajuda();
void iniciar_jogo();
void marcar_pontos(struct BaseTable *tiros, struct BaseTable *tabuleiro, int jogador);
void marcar_tiro(struct BaseTable *tiros, struct BaseTable *tabuleiro, int jogador, int lin_temp, char col_temp);
void gravar_jogo();
void carregar_jogo();
void funcao_zera_pontos();
void print_tabuleiro(struct BaseTable *tabuleiro, int jogador, int tipo);
void exibir_desenvolvedores();

 struct BaseTable tabuleiro[2];  // definir duas matrizes diferentes, uma para cada jogador
 struct BaseTable tiros[2];      // a matriz tabuleiro eh onde poe os navios e a tiros onde registramos os disparos
int main(){
    

    //definicoes bases do jogo
    char comando[16];               // Char responsavel por salvar os comandos
    int status = 0;                 // Eh uma 'flag' para sabermos quando encerrar o jogo (ver o 'while' abaixo)
   
    int pl = 0;                     // Player 1 ou player 2

        //imprimimos o menu de inicio
    layout_menu();                 
    int comand_menu, flagmen = 0;                 

    while (flagmen == 0){
        
        scanf ("%d", &comand_menu);
        fflush (stdin);
        switch (comand_menu)
        {
            case 1:
                flagmen = 1; //quebra o laco de repeticao prelimiar e inicia o jogo
            break;

            case 2: 
                flagmen = 1;
                carregar_jogo();    //carrega o jogo
            break;

            case 3:
                exibir_desenvolvedores(); //exibe os desenvolvedores
                comand_menu = 0;
            break;

            case 4:
                exibir_ajuda();  //exibe ajuda sobre comandos in game
            break;

            case 5:
                flagmen = 1;
                status = 1;
            break;

            default:
            break;
        }

    }
   
    iniciar_jogo (tabuleiro, pl);

    while (status == 0){        // funciona como se fosse um menu durante a execucao do jogo, cada comando digitado leva o jogador a uma outra funcao
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
            scanf (" %c%d", &col_temp, &lin_temp);      //registra a coordenada do tiro
            col_temp = toupper (col_temp);
             while (lin_temp > 16 || col_temp > 'P'|| lin_temp < 1 ){
                    printf ("\nINSIRA UMA COORDENADA VALIDA!!!\n");
                    scanf (" %c%d", &col_temp, &lin_temp);
                    col_temp = toupper (col_temp);
                }
            fflush (stdin);
            marcar_tiro (tiros, tabuleiro, jogador, lin_temp, col_temp);
            marcar_pontos (tiros, tabuleiro, jogador);
            pl = pl+1;
            //soma 1 ao valor de pl sempre que alguem atira, assim conseguimos manter uma contagem de quem esta atirando no momento
        }
        else if (strcmp (comando, "RESET") == 0){   //chama as funcoes zera pontos e iniciar jogo
            funcao_zera_pontos();                   //assim, reinicia-se o jogo com pontuacoes zeradas
            iniciar_jogo (tabuleiro,pl);
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
            iniciar_jogo(tabuleiro,pl);
        }
        else{   //caso o comando inserido nao seja valido:
            printf ("\n O COMANDO '%s' E DESCONHECIDO, INSIRA UM COMANDO VALIDO\n\nSe precisar de ajuda com os comandos, utilize o comando 'ajuda'\n", comando);
        }
        fflush (stdin);
    }

printf ("\nsucess");

return 0;  
}

void exibir_ajuda(){    // exibir todos os comandos, um menu de ajuda

printf ("\n\tLISTA DE COMANDOS (funcionam somente durante o jogo):");
printf ("\n\t'ajuda' \tExibe esta lista de comandos!");
printf ("\n\t'POW'     \tInsira o comando POW seguido das coordenadas onde voce deseja atirar!");
printf ("\n\t'reset' \tReinicia o jogo inteiro, zerando as pontuacoes!");
printf ("\n\t'acaso' \tReinicia o jogo inteiro, mas mantem as pontuacoes!");
printf ("\n\t'gravar' \tSalva o jogo, para voce continua-lo depois!");
printf ("\n\t'carregar' \tCarrega um jogo salvo!");
printf ("\n\t'sair'    \tFecha o aplicativo :( \n");
printf("\n\n LEMBRE-SE: SEMPRE INSIRA AS COORDENADAS DOS SEUS TIROS NA FORMA 'LETRA NUMERO'\n");
}

void iniciar_jogo(struct BaseTable *tabuleiro, int pl){


    for (int i = 0; i < 2; i++){                    // Definimos as matrizes "tabuleiro"(onde as posições dos barcos são salvas) como sendo inteira de '*'
        for (int j = 0; j < 16; j++){               // Onde tivermos um barco, ela sera posteriormente definida com outro caracter
            for (int k = 0; k <16; k++){
                tabuleiro[i].posicao[j][k] = '*';   // Definimos as matrizes tiros como sendo inteiras de 'espaços'
                tiros[i].posicao[j][k] = ' ';       // A cada tiro ela assume o valor da mesma coordenada da matriz tabuleiro do jogador adversario
            }    
        }   
    }

    // gerar as duas contagens de pontos

    // chamar a funcao exibir_ajuda para ja mostrar os comandos incluidos
    exibir_ajuda();
}

void marcar_pontos(struct BaseTable *tiros, struct BaseTable *tabuleiro, int jogador){
    // funcao responsavel por marcar os pontos de cada tiro
}

void marcar_tiro(struct BaseTable *tiros, struct BaseTable *tabuleiro, int jogador, int lin_temp, char col_temp){
    printf ("\nTIRO EM %c%d\n", col_temp, lin_temp);

    char line[16]= {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P'};
    for (int i=0; i<16; i++){                  //COMPARA O CARACTER LIDO COM UM VETOR (line) E ENTAO DEFINE UM NUMERO P/ A POSICAO
        if (col_temp == line[i]){
            tiros[jogador].posicao[lin_temp-1][i] = '*';    //comparamos a matriz tiros do jogador A com a matriz tabuleiro do jogador B
            if (tiros[jogador].posicao[lin_temp-1][i] != tabuleiro[(jogador+1)%2].posicao[lin_temp-1][i]){
                tiros[jogador].posicao[lin_temp-1][i] = tabuleiro[(jogador+1)%2].posicao[lin_temp-1][i];
                printf ("\n\tVoce acertou um Navio inimigo!\n\tVeja no mapa:");
            }else{}
                        
        }else{}
    }
    for (int i = 0; i < 16; i++){
        for (int j = 0; j < 16; j++){
            
        }
        
    }
    int tipo = 1;
    print_tabuleiro(tabuleiro, jogador, tipo);
    // compara a coordenada informada com as coordenadas onde os navios estao
    // chamar a funcao marcar_pontos
    marcar_pontos(tiros, tabuleiro, jogador);

}

void gravar_jogo(){
    // salva o jogo em um arquivo (como fazer isso???)
}

void carregar_jogo(){
    // carrega algum arquivo do jogo previamente salvo
}

void funcao_zera_pontos(){

}

void exibir_desenvolvedores(){
    printf("\n\t\t ___________________________________________________________");
    printf("\n\t\t|                                                           |");
    printf("\n\t\t|     Jogo desenvolvido como Trabalho Final da disciplina   |");
    printf("\n\t\t|     SSC304 - Intrducao a Programacao para Engenharias     |");
    printf("\n\t\t|     EESC - USP  2020                                      |");
    printf("\n\t\t|                                                           |");
    printf("\n\t\t|     Desenvolvedores:                                      |");
    printf("\n\t\t|                                                           |");
    printf("\n\t\t|         Luis Gustavo Felicio Vianna                       |");
    printf("\n\t\t|         Pedro Luiz Miranda Pignanelli                     |");
    printf("\n\t\t|                                                           |");
    printf("\n\t\t|                                                           |");
    printf("\n\t\t|     Agradecimentos especiais, pelo imenso apoio:          |");
    printf("\n\t\t|                                                           |");
    printf("\n\t\t|         Prof. Jo Ueyama                                   |");
    printf("\n\t\t|         Monitora Ana Luisa Teixeira Costa                 |");
    printf("\n\t\t|         Monitor Erikson Julio de Aguiar                   |");
    printf("\n\t\t|         E a todos os colegas de classe pela ajuda         |");
    printf("\n\t\t|___________________________________________________________|\n\n");
}

void print_tabuleiro( struct BaseTable *tabuleiro, int jogador, int tipo){
    char M[34][34]; //Matriz que conterá a tabela. (É maior pois devemos considerar os espaços das barras e traços)

    char barra = '|', traco='-', ponta = '+', coordenadas=' ', espaco=' '; //Variáveis para criação da tabela (Estrutura)

    char letra[16] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P'}; //Vetor para auxiliar na posição da coordenadas (letras)
    int cont = 1, position = 0; //Variáveis que também irão auxiliar na criação das coordenadas
    int lin = 0;
    int col = 0;
    //Loop for para iniciar a assimilação de valores às posições da matriz
    for (int i=0;i<34;i++){
        for (int j=0; j<34; j++){
            
            //Condição para posicionar as letras
            if (i==0){ 
                if (j%2==0 && j!= 0){
                    M[i][j]=letra[position];
                    position++;
                }
                else
                    M[i][j]=espaco;
            }

            else if (i%2!=0 && j%2!=0)
                M[i][j]= ponta;

            //Condição para posicionar os números
            else if(i%2==0 && j==0){
                M[i][j]= cont;
                cont++;
            }

            else if (i%2==0 && j%2!=0)
                M[i][j]= barra;

            else if (i%2!=0 && j%2== 0 && j!=0)
                M[i][j]=traco;  

            else if (i%2!=0 && j==0) 
                M[i][j]=espaco;

            else{
                switch (tipo){//para usar a mesma funcao para imprimir a matriz separamos - se vamos imprimir a matriz tabuleiro ou tiros
                case 1:   
                        M[i][j]= tiros[jogador].posicao[col][lin]; //Local das coordenadas
                        lin = lin+1;
                        if (lin==16){
                            lin = 0;
                            col++;
                            }else{}
                    break;
                case 2:
                        M[i][j]= tabuleiro[jogador].posicao[col][lin]; //Local das coordenadas
                        lin = lin+1;
                        if (lin==16){
                            lin = 0;
                            col++;
                            }else{}
                    break;

                default:
                    break;
                }
            }
        }
    }

    //Loop for para imprimir o tabuleiro
    for (int i=0; i<34; i++){
        for (int j=0;j<34;j++){

            //Caso o local represente um número da coordenada
            if(j==0 && i!=0 && i%2 == 0 )
                printf("%02d", M[i][j]);  
            
            else{
                //Quando chegar na última coluna, os valores tem que ser imprimidos na linha de baixo
                if (j==33)
                    printf(" %c\n", M[i][j]);
                
                else
                    printf(" %c", M[i][j]);
            }

        }
    }

}

void layout_menu(){
    
        printf ("\n");
    for (int i=0; i<135; i++){printf ("=");}
    
    printf ("\n                                 ||\\       ||          //\\\\    \\\\                //   \\\\        //");
    printf ("\n                                 ||\\\\      ||         //  \\\\    \\\\              //     \\\\      //");
    printf ("\n                                 || \\\\     ||        //    \\\\    \\\\            //       \\\\    //");
    printf ("\n                                 ||  \\\\    ||       //      \\\\    \\\\          //         \\\\  //");
    printf ("\n                                 ||   \\\\   ||      //        \\\\    \\\\        //           \\\\//");
    printf ("\n                                 ||    \\\\  ||     //==========\\\\    \\\\      //             //");
    printf ("\n                                 ||     \\\\ ||    //            \\\\    \\\\    //             //");
    printf ("\n                                 ||      \\\\||   //              \\\\    \\\\  //             //");
    printf ("\n                                 ||       \\||  //                \\\\    \\\\//             //\n");
    for (int i=0; i<135; i++){printf ("=");}


    printf ("\n                                                                  ____|");
    printf ("\n                                                                 |____|");
    printf ("\n                                                                      |");
    printf ("\n                                                                     _|_ ");
    printf ("\n                                                                    /    \\ ");
    printf ("\n                                                          ____|    /      |");
    printf ("\n                                                         |____|   |    []  \\");
    printf ("\n                                                             ||   |  []  [] |");
    printf ("\n                                                _____       _||___|---------||___          _____");
    printf ("\n                            _____      ________/     \\      |     []  []  []      \\\\      /     \\________      _____");
    printf ("\n                    _______/     \\    |_______________|   //     ____________      ||    |_______________|    /     \\________");
    printf ("\n                    |____________|            |      |    //     |    |     |      ||      |      |          |______________|");
    printf ("\n        ||_______________|______|_____________|______|____||_____|____|_____|______||______|______|____________|______|_____________");
    printf ("\n        \\-------------------------------------------------------------------------------------------------------------------------/");
    printf ("\n          \\------[]------[]-----[]------[]------[]------[]------[]------[]------[]------[]------[]------[]------[]------[]------/");
    printf ("\n            \\--------[]------[]------[]------[]------[]------[]------[]------[]------[]------[]------[]------[]------[]-------/");
    printf ("\n              \\-------------------------------------------------------------------------------------------------------------/");
    printf ("\n                \\---------------------------------------------------------------------------------------------------------/");
    printf ("\n                  \\_____________________________________________________________________________________________________/\n");

    for (int i=0; i<135; i++){printf ("=");}

    printf ("\n\n\t\t\t\t\t\t _______________________________");
    printf ("\n\t\t\t\t\t\t|                               |");
    printf ("\n\t\t\t\t\t\t|  [1] Iniciar Novo Jogo        |");
    printf ("\n\t\t\t\t\t\t|  [2] Carregar Jogo            |");
    printf ("\n\t\t\t\t\t\t|  [3] Desenvolvedores          |");
    printf ("\n\t\t\t\t\t\t|  [4] Ajuda (comandos in game) |");
    printf ("\n\t\t\t\t\t\t|  [5] Sair                     |");
    printf ("\n\t\t\t\t\t\t|_______________________________|\n");
    printf ("\n\t\t (Obs.: Estes comenados sao especificos para o MENU)\n");
}