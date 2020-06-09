//Criado por Luis G F Vianna e Pedro L M Pignanelli
//Trabalho Final - SSC 0304 - Introducao a Programacao para Engenharias
//EESC - USP
//Sao Carlos - 2020

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct BaseTable{   // struct que funciona como se fosse uma matriz, base pro tabuleiro e etc
    char posicao[16][16]; //associa as posicoes
    float pontos; //usaremos so na matriz 'tiros', marca a pontuacao daquele jogador. Fizemos isso para facilitar a passagem de valores entre funcoes
    int N; //no struct tipo 'tabuleiro' marca quantas casas existem 'desocupadas'. na struct tipo 'tiros', quantos acertos o jogador ja teve 
};
    
// Prototipos das funcoes
void layout_menu();
void exibir_ajuda();
void iniciar_jogo();
void marcar_pontos(struct BaseTable *tiros, struct BaseTable *tabuleiro, int jogador, int hit);
void marcar_tiro(struct BaseTable *tiros, struct BaseTable *tabuleiro, int jogador, int lin_temp, char col_temp);
void gravar_jogo();
void carregar_jogo();
void funcao_zera_pontos();
void print_tabuleiro(struct BaseTable *tabuleiro, int jogador, int tipo);
void exibir_desenvolvedores();

    struct BaseTable tabuleiro[2];  // definir duas matrizes diferentes, uma para cada jogador
    struct BaseTable tiros[2];      // a matriz tabuleiro eh onde poe os navios e a tiros onde registramos os disparos

int main(){

    //imprimimos o menu de inicio
    layout_menu();

    int comand_menu, flagmain = 0;  //fica em loop inifinito ate que 'flagmain' seja alterada        

    while (flagmain == 0){
        
        scanf ("%d", &comand_menu);
        fflush (stdin);
        switch (comand_menu)
        {
            case 1:
                flagmain = 1;  //quebra o laco de repeticao do menu de entrada e inicia o jogo
            break;

            case 2: 
                flagmain = 1;
                carregar_jogo();  //carrega o jogo
            break;

            case 3:
                exibir_desenvolvedores();  //exibe os desenvolvedores
                comand_menu = 0;
            break;

            case 4:
                exibir_ajuda();   //exibe ajuda sobre comandos in game
            break;

            case 5:                
                return 0; // retorna zero, encerrando o jogo
            break;

            default:
            break;
        }

    }

        //definicoes bases do jogo
    char comando[16];           // Char responsavel por salvar os comandos
    int status = 0;             // Eh uma variavel para rodarmos o 'while', durante a partida
    int pl = 0;                 // Usada em todo o programa para definir se Player 1 ou player 2

    iniciar_jogo (tabuleiro, tiros, pl);


    while (status == 0){        // funciona como se fosse um menu durante a execucao do jogo, cada comando digitado leva o jogador a uma outra funcao
        
        int tipo = 1;    //eh o tipo do tabuleiro, no caso, aqui sempre sera impresso o tabuleiro 'tipo 1' => tiros
        int jogador = pl%2;    //uma outra variavel, que sera repassada para as outras funcoes definindo qual player esta jogando. Tem valor sempre definida entre '0 e 1'
        printf ("\n\tInsira um comando, jogador #%d\n\tEste e o mapa de onde voce ja atirou!\n", (jogador+1));
        print_tabuleiro (tiros, jogador, tipo);
        
        scanf (" %s[^\n]", comando);
        
        //converte o comando de cada jogador para caixa alta, facilitando a vida de todo mundo
        for(int i = 0; i < 10; i++) comando[i]=toupper(comando[i]); 


        if (strcmp (comando, "SAIR") == 0){
            
            int confirm; //serve para confir a saida do jogo

            printf ("\n\nDeseja realmente sair?\n\n[1]SIM\n[2]NAO (voltar ao jogo)\n");
            scanf ("%d", &confirm);
            if (confirm == 1){
            funcao_zera_pontos();
            status = 1;     //define 'status' como 1, assim saindo do ciclo e encerrando o programa
            return 0;       //Encerra o programa de fato
            }
            else{
                confirm = NULL; //limpa o valor de confirm
            }
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
        else if (strcmp (comando, "GRAVAR") == 0){   //chama a funcao gravar
            
            gravar_jogo();
        }
        else if (strcmp (comando, "CARREGAR") == 0){ //chama a funcao carregar
            
            carregar_jogo();
        }
        else if (strcmp (comando, "ACASO") == 0){  //reinicia o jogo  mas salva as pontuacoes, pois nao chama a 'funcao_zera_pontos'
            
            printf ("\n\nREINICIANDO O JOGO E MANTENDO AS PONTUACOES ATUAS\nREPOSICIONEM SUAS ARMADAS!\n");
            pl = 0;
            iniciar_jogo(tabuleiro, tiros, pl);
        }
        else{   //caso o comando inserido nao seja valido:
            
            printf ("\n O COMANDO '%s' E DESCONHECIDO, INSIRA UM COMANDO VALIDO\n\nSe precisar de ajuda com os comandos, utilize o comando 'ajuda'\n", comando);
        }

        //fizemos isso para melhorar a interface, assim, pausamos entre cada comando enviado
        //sem esse 'getch()' os tabuleiros de tiros dados seriam impressos em sequencia a cada comando tornando
        //a visualizacao mais complicada
        printf ("\n\n\tPressione qualquer tecla para continuar a batalha\n");
        getch ();
        
        fflush (stdin); //sempre limpamos o buffer do teclado depois de cada comando
    }

printf ("\nsucess");

return 0;  
}

void exibir_ajuda(){    // exibir todos os comandos, um menu de ajuda

    printf ("\n\tLISTA DE COMANDOS (funcionam somente durante a partida):");
    printf ("\n\t'ajuda' \tExibe esta lista de comandos!");
    printf ("\n\t'POW'     \tInsira o comando POW seguido das coordenadas onde voce deseja atirar!");
    printf ("\n\t'reset' \tReinicia o jogo inteiro, zerando as pontuacoes!");
    printf ("\n\t'acaso' \tReinicia o jogo inteiro, mas mantem as pontuacoes!");
    printf ("\n\t'gravar' \tSalva o jogo, para voce continua-lo depois!");
    printf ("\n\t'carregar' \tCarrega um jogo salvo!");
    printf ("\n\t'sair'    \tFecha o aplicativo :( \n");
    printf("\n\n\t LEMBRE-SE: SEMPRE INSIRA AS COORDENADAS DOS SEUS TIROS NA FORMA 'LETRA NUMERO'\n");
        
}

void iniciar_jogo(struct BaseTable *tabuleiro, struct BaseTable *tiros, int pl){

    //Define os parametros iniciais das matrizes e contagens do jogo

    for (int i = 0; i < 2; i++){                    // Definimos as matrizes "tabuleiro"(onde as posições dos barcos são salvas) como sendo inteira de '*'
        for (int j = 0; j < 16; j++){               // Onde tivermos um barco, ela sera posteriormente definida com outro caracter
            for (int k = 0; k <16; k++){
                tabuleiro[i].posicao[j][k] = '*';   // Definimos as matrizes tiros como sendo inteiras de 'espaços'
                tiros[i].posicao[j][k] = ' ';       // A cada tiro ela assume o valor da mesma coordenada da matriz tabuleiro do jogador adversario
            }    
        }   
    }

    tabuleiro[0].N = 256;   //define o numero de casas inicial do tabuleiro DO JOGADOR (256)
    tabuleiro[1].N = 256;

    tiros [0].N = 0;    //define a quantidade de acertos no inicial DO JOGADOR (zero)
    tiros [1].N = 0;

    // chamar a funcao exibir_ajuda automaticamente no inicio da partida
    exibir_ajuda();
}

void marcar_pontos(struct BaseTable *tiros, struct BaseTable *tabuleiro, int jogador, int hit){
    
    // funcao responsavel por definir as pontuacoes de cada jogador ao longo da partida

    int var = (jogador+1)%2; //var eh o outro jogador, o que "recebe o tiro" 
    float value = 0; //eh a variavel para decidir quantos pontos o jogador ganha ou perde

    //a cada tiro dado, o numero de casas 'N' no tabuleiro DO ADVERSARIO diminui 1
    tabuleiro[var].N = tabuleiro[var].N - 1;

    if (hit == 1){
        

        //aumenta 1 na contagem de acertos DO JOGADOR
        tiros[jogador].N = tiros[jogador].N + 1;

        //soma 'value' a pontuacao DO JOGADOR
        tiros[jogador].pontos = tiros[jogador].pontos + value;
    }
    
    else{
        //faz todas as contas para ver qual a deducao de pontos pelo erro
        value = tabuleiro[var].N - 84;
        value = value + tiros[jogador].N;
        value = value/tabuleiro[var].N;
        value = value + 5;

        //deduz 'value' da pontuacao.
        tiros[jogador].pontos = tiros[jogador].pontos - value;
    }

}

void marcar_tiro(struct BaseTable *tiros, struct BaseTable *tabuleiro, int jogador, int lin_temp, char col_temp){
    
    // RESUMO DA FUNCAO: compara matrizes e define se o jogador conseguiu um acerto ou nao.
    // Tambem ira passar os parametros para a funcao 'marcar pontos'

    int hit;  //parametro para definir se acertou ou nao, repassado a funcao 'marcar pontos'

    printf ("\n\n\tDISPARANDO EM %c%d...\n", col_temp, lin_temp);
    
    char line[16]= {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P'};
    for (int i=0; i<16; i++){   //COMPARA O CARACTER LIDO COM UM VETOR (line) E ENTAO DEFINE UM NUMERO P/ A POSICAO
        
        //comparamos a matriz tiros do jogador A com a matriz tabuleiro do jogador B para saber se acertou ou nao um barco
        if (col_temp == line[i]){

            tiros[jogador].posicao[lin_temp-1][i] = '*';

            if (tiros[jogador].posicao[lin_temp-1][i] != tabuleiro[(jogador+1)%2].posicao[lin_temp-1][i]){ 
                
                tiros[jogador].posicao[lin_temp-1][i] = tabuleiro[(jogador+1)%2].posicao[lin_temp-1][i];
                hit = 1;
                printf ("\n\tNA MOSCA!\n\tVoce acertou um Navio inimigo!\n\tVeja no mapa:\n");
            
            }else{
                printf ("\n\tQUASE! Voce acertou a agua, recalibre sua mira!\n");
                hit = 0;
            }
                        
        }else{}
    }

    // chamar a funcao marcar_pontos
    marcar_pontos(tiros, tabuleiro, jogador, hit);

        //printa o tabuleiro com a pontuacao acertos
    int tipo = 1;
    print_tabuleiro(tabuleiro, jogador, tipo);

}

void gravar_jogo(){
    // salva o jogo em um arquivo (como fazer isso???)
}

void carregar_jogo(){
    // carrega algum arquivo do jogo previamente salvo
}

void funcao_zera_pontos(){

    //zera as pontuacoes dos jogadores
    for (int i = 0; i < 2; i++){
        tiros[i].pontos = 0;
        tiros[i].N = 0;
        tabuleiro[i].N = 256;
        tabuleiro[i].pontos = 0;
    }
    
}

void exibir_desenvolvedores(){

    //printa isso na tela, com os desenvolvedores e agradecimentos
    printf("\n\t\t\t\t\t ___________________________________________________________");
    printf("\n\t\t\t\t\t|                                                           |");
    printf("\n\t\t\t\t\t|     Jogo desenvolvido como Trabalho Final da disciplina   |");
    printf("\n\t\t\t\t\t|     SSC304 - Introducao a Programacao para Engenharias    |");
    printf("\n\t\t\t\t\t|     EESC - USP  2020                                      |");
    printf("\n\t\t\t\t\t|                                                           |");
    printf("\n\t\t\t\t\t|     Desenvolvedores:                                      |");
    printf("\n\t\t\t\t\t|                                                           |");
    printf("\n\t\t\t\t\t|         Luis Gustavo Felicio Vianna                       |");
    printf("\n\t\t\t\t\t|         Pedro Luiz Miranda Pignanelli                     |");
    printf("\n\t\t\t\t\t|                                                           |");
    printf("\n\t\t\t\t\t|                                                           |");
    printf("\n\t\t\t\t\t|     Agradecimentos especiais, pelo imenso apoio:          |");
    printf("\n\t\t\t\t\t|                                                           |");
    printf("\n\t\t\t\t\t|         Professor Doutor Jo Ueyama                        |");
    printf("\n\t\t\t\t\t|         Monitora Ana Luisa Teixeira Costa                 |");
    printf("\n\t\t\t\t\t|         Monitor Erikson Julio de Aguiar                   |");
    printf("\n\t\t\t\t\t|         E a todos os colegas de classe pelas ajudas       |");
    printf("\n\t\t\t\t\t|                                                           |");
    printf("\n\t\t\t\t\t|                                      Sao Carlos - 2020    |");
    printf("\n\t\t\t\t\t|___________________________________________________________|\n\n");
}

void print_tabuleiro( struct BaseTable *tabuleiro, int jogador, int tipo){
    
    //printa o cabeçalho do tabuleiro - informacoes de player e pontuacao
    printf ("\t   _______________________________________________\n");
    printf ("\t  |                                               |\n");
    printf ("\t        P L A Y E R %d         Pontos: %.1f\n", (jogador+1) , tiros[jogador].pontos);
    printf ("\t  |_______________________________________________|\n");
    
    
    //essa sessao toda eh para printar a tabela
    char M[34][34]; //Matriz que conterá a tabela. (É maior pois devemos considerar os espaços das barras e traços)

    char barra = '|', traco='-', ponta = '+', espaco=' '; //Variáveis para criação da tabela (Estrutura)

    //Vetor para auxiliar na posição da coordenadas (letras)
    char letra[16] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P'}; 
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

                //para usar a mesma funcao para imprimir todas as matrizes, usamos a variavel 'tipo' nesse 'switch'
                switch (tipo){
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
    
    //printa toda a tela do menu inicial
    printf ("\n\t");
    for (int i=0; i<145; i++){printf ("=");}
    printf ("\n\t\t                                 ||\\       ||          //\\\\    \\\\                //   \\\\        //");
    printf ("\n\t\t                                 ||\\\\      ||         //  \\\\    \\\\              //     \\\\      //");
    printf ("\n\t\t                                 || \\\\     ||        //    \\\\    \\\\            //       \\\\    //");
    printf ("\n\t\t                                 ||  \\\\    ||       //      \\\\    \\\\          //         \\\\  //");
    printf ("\n\t\t                                 ||   \\\\   ||      //        \\\\    \\\\        //           \\\\//");
    printf ("\n\t\t                                 ||    \\\\  ||     //==========\\\\    \\\\      //             //");
    printf ("\n\t\t                                 ||     \\\\ ||    //            \\\\    \\\\    //             //");
    printf ("\n\t\t                                 ||      \\\\||   //              \\\\    \\\\  //             //");
    printf ("\n\t\t                                 ||       \\||  //                \\\\    \\\\//             //\n\t");
    for (int i=0; i<145; i++){printf ("=");}
    printf ("\n\t                                                                  ____|");
    printf ("\n\t                                                                 |____|");
    printf ("\n\t                                                                      |");
    printf ("\n\t                                                                     _|_ ");
    printf ("\n\t                                                                    /    \\ ");
    printf ("\n\t                                                          ____|    /      |");
    printf ("\n\t                                                         |____|   |    []  \\");
    printf ("\n\t                                                             ||   |  []  [] |");
    printf ("\n\t                                                _____       _||___|---------||___          _____");
    printf ("\n\t                            _____      ________/     \\      |     []  []  []      \\\\      /     \\________      _____");
    printf ("\n\t                    _______/     \\    |_______________|    //    ____________      ||    |_______________|    /     \\________");
    printf ("\n\t                    |____________|            |      |    //     |    |     |      ||      |      |          |______________|");
    printf ("\n\t        ||_______________|______|_____________|______|____||_____|____|_____|______||______|______|____________|______|_____________");
    printf ("\n\t        \\-------------------------------------------------------------------------------------------------------------------------/");
    printf ("\n\t          \\------[]------[]-----[]------[]------[]------[]------[]------[]------[]------[]------[]------[]------[]------[]------/");
    printf ("\n\t            \\--------[]------[]------[]------[]------[]------[]------[]------[]------[]------[]------[]------[]------[]-------/");
    printf ("\n\t              \\-------------------------------------------------------------------------------------------------------------/");
    printf ("\n\t                \\---------------------------------------------------------------------------------------------------------/");
    printf ("\n\t                  \\_____________________________________________________________________________________________________/\n\t");
    for (int i=0; i<145; i++){printf ("=");}
    printf ("\n\n\t\t\t\t\t\t\t\t  MENU PRINCIPAL");
    printf ("\n\t\t\t\t\t\t\t _______________________________");
    printf ("\n\t\t\t\t\t\t\t|                               |");
    printf ("\n\t\t\t\t\t\t\t|  [1] Iniciar Novo Jogo        |");
    printf ("\n\t\t\t\t\t\t\t|  [2] Carregar Jogo            |");
    printf ("\n\t\t\t\t\t\t\t|  [3] Desenvolvedores          |");
    printf ("\n\t\t\t\t\t\t\t|  [4] Ajuda (comandos in game) |");
    printf ("\n\t\t\t\t\t\t\t|  [5] Sair                     |");
    printf ("\n\t\t\t\t\t\t\t|_______________________________|\n");
    printf ("\n\t\t\t\t\t\t (Obs.: Estes comenados sao especificos para o MENU)\n");
}