//Criado por Luis G F Vianna e Pedro L M Pignanelli
//Trabalho Final - SSC 0304 - Introdução a Programacao para Engenharias
//EESC - USP
//Sao Carlos - 2020

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


struct BaseTable{   //Struct que funciona como se fosse uma matriz, base pro tabuleiro e etc
    char posicao[16][16];   //Associa as posicoes
    float pontos;   //Usaremos so na matriz 'tiros', marca a pontuacao daquele jogador. Fizemos isso para facilitar a passagem de valores entre funções
    int N;   //No struct tipo 'tabuleiro' marca quantas casas existem 'desocupadas'. Na struct tipo 'tiros', quantos acertos o jogador já teve 
};
    
// Prototipos das funcoes
void layout_menu();
void exibir_desenvolvedores();
void print_tabuleiro(struct BaseTable *tabuleiro, int jogador, int tipo);
void exibir_ajuda();
void iniciar_jogo();
void marcar_tiro(struct BaseTable *tiros, struct BaseTable *tabuleiro, int jogador, int lin_temp, char col_temp);
void marcar_pontos(struct BaseTable *tiros, struct BaseTable *tabuleiro, int jogador, int hit);
void funcao_zera_pontos();
void gravar_jogo(struct BaseTable *tabuleiro, struct BaseTable *tiros, int pl);
void carregar_jogo();


struct BaseTable tabuleiro[2];   //Definir duas matrizes diferentes, uma para cada jogador
struct BaseTable tiros[2];       //A matriz tabuleiro é onde põe os navios e os tiros onde registramos os disparos

int main(){
    layout_menu();   //Imprimindo o menu de inicio

    int comand_menu, flagmain = 0;   //Fica em loop inifinito até que 'flagmain' seja alterada        

    while (flagmain == 0){
        scanf ("%d", &comand_menu);
            fflush (stdin);

        switch (comand_menu){
            case 1:
                flagmain = 1;   //Quebra o laço de repeticao do menu de entrada e inicia o jogo
            break;

            case 2: 
                flagmain = 1;
                carregar_jogo();   //Carrega algum jogo salvo
            break;

            case 3:
                exibir_desenvolvedores();   //Funcao que printa os desenvolvedores
            break;

            case 4:
                exibir_ajuda();   //Função que exibira os comandos in-game
            break;

            case 5:                
                return 0;   //Finaliza o jogo
            break;

            default:
                printf("Comando invalido. Por favor, digite um numero entre 1 e 5:\n");
            break;
        }

    }

    //Definindo as bases do jogo
    char comando[16];   //Char responsavel por salvar os comandos
    int status = 0;     //E uma variavel para rodarmos o loop while, durante a partida
    int pl = 0;         //Usada em todo o programa para definir se Player 1 ou player 2

    iniciar_jogo (tabuleiro, tiros, pl);

    while (status == 0){       //Loop para funcionamento do jogo, que só será rompido caso solicitado pelo jogador
        int tipo = 1;          //E o tipo do tabuleiro, no caso, aqui sempre sera impresso o tabuleiro 'tipo 1' => tiros
        int jogador = pl%2;    //Variavel que sera repassada para as outras funcoes definindo qual player esta jogando.

        print_tabuleiro(tiros, jogador, tipo);
        printf("\n\t\tEste e o mapa de onde voce ja atirou!\n\nInsira um comando, jogador #%d:\n", (jogador+1));
        scanf(" %s[^\n]", comando);
        
        //Converte o comando de cada jogador para caixa alta (facilitara a programação ao longo do código)
        for(int i = 0; i < 10; i++)
            comando[i]=toupper(comando[i]); 

        if (strcmp (comando, "SAIR") == 0){
            int confirm;   //Variavel que servirá para confirmar a ação

            printf ("\n\nDeseja realmente sair?\n\n[1]SIM\n[2]NAO (voltar ao jogo)\n");
            scanf ("%d", &confirm);

            if (confirm == 1){
                funcao_zera_pontos();
                status = 1;   //Define 'status' como 1, assim saindo do loop e encerrando o programa
                return 0;     //Encerra o programa de fato
            }

            else
                confirm = NULL;   //limpa o valor de confirm
            
        }

        else if (strcmp (comando, "POW") == 0){
            //Variáveis para deifinir as coordenadas dos tiros
            int lin_temp;
            char col_temp;
            
            scanf (" %c%d", &col_temp, &lin_temp);   //Registra a coordenada do tiro
                fflush (stdin);
            col_temp = toupper (col_temp); //Converte a letra para maiusculo para assimilar corretamente a coordenada
            
            while (lin_temp > 16 || lin_temp < 1|| col_temp > 'P' ){
                printf ("\nCoordenada invalida. Por favor, digite uma coordenada valida:\n");
                scanf (" %c%d", &col_temp, &lin_temp);
                    fflush (stdin);
                    col_temp = toupper (col_temp);
            }
            printf("\n");
            marcar_tiro (tiros, tabuleiro, jogador, lin_temp, col_temp);
            pl = pl+1;   //Soma 1 ao valor de pl sempre que alguem atira, "alternando" quem está atirando
        }

        else if (strcmp (comando, "RESET") == 0){   //Chama as funções que recomeça o jogo e zera os pontos
            funcao_zera_pontos();                   
            iniciar_jogo (tabuleiro,pl);
        }

        else if (strcmp(comando, "AJUDA") == 0){    //Chama a função que printa os comandos do jogo
            exibir_ajuda(); 
        }

        else if (strcmp (comando, "GRAVAR") == 0){   //Chama a função que salva o progresso atual do jogo
            gravar_jogo(tabuleiro, tiros, pl);
        }

        else if (strcmp (comando, "CARREGAR") == 0){   //Chama a função que carrega um jogo salvo previamente
            carregar_jogo();
        }

        else if (strcmp (comando, "ACASO") == 0){   //Chama apenas a função que inicia o jogo, assim começando um novo sem zeras as pontuações
            printf ("\nReiniciando o jogo...\n");
            pl = 0;
            iniciar_jogo(tabuleiro, tiros, pl);
        }

        else{   //Caso seja digitado um comando inválido, entramos nessa condição
            printf ("\nComando desconhecido, insira um comando valido.\nSe precisar de ajuda com os comandos, digite 'ajuda':\n");
        }

        //Para melhorar a interface introduzimos o comando "getch()", pausando após um comando, a fim de melhorar a visualização
        printf ("\n\n\tPressione qualquer tecla para continuar a batalha\n\n");
        getch ();
            fflush (stdin);
    }

printf ("\nSucesso!"); // E so um print pra sabermos se deu tudo certo - n faz nada no codigo

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

void iniciar_jogo(struct BaseTable *tabuleiro, struct BaseTable *tiros, int pl){   //Define os parametros iniciais das matrizes e contagens do jogo
    for (int i = 0; i < 2; i++){        //Definimos as matrizes "tabuleiro"(onde as posições dos barcos são salvas) como sendo inteira de '*'
        for (int j = 0; j < 16; j++){   //Onde tivermos um barco, ela sera posteriormente definida com outro caractere
            for (int k = 0; k <16; k++){
                tabuleiro[i].posicao[j][k] = '*';   //Definimos as matrizes tiros como sendo inteiras de 'espaços'
                tiros[i].posicao[j][k] = ' ';       //A cada tiro ela assume o valor da mesma coordenada da matriz tabuleiro do jogador adversario
            }    
        }   
    }

    tabuleiro[0].N = 256;   //Define o numero de casas inicial do tabuleiro DO JOGADOR (256)
    tabuleiro[1].N = 256;

    tiros [0].N = 0;        //Define a quantidade de acertos no inicial DO JOGADOR (zero)
    tiros [1].N = 0;

    exibir_ajuda();
}

void marcar_pontos(struct BaseTable *tiros, struct BaseTable *tabuleiro, int jogador, int hit){//Função responsável por definir as pontuacoes de cada jogador ao longo da partida
    int var = (jogador+1)%2;   //Var é o outro jogador, o que "recebe o tiro" 
    float value = 0;           //Variável para registrar quantos pontos o jogador ganha ou perde

    tabuleiro[var].N = tabuleiro[var].N - 1;   //A cada tiro dado, o numero de casas 'N' no tabuleiro DO ADVERSARIO diminui 1

    switch(hit){
        case 1:
            tiros[jogador].N = tiros[jogador].N + 1;         //Aumenta 1 na contagem de acertos do jogador

        //codigo que ainda precisamos desenvolver

            tiros[jogador].pontos = tiros[jogador].pontos + value;   //Soma 'value' a pontuação do jogador
        break;

        case 0:
            value = tabuleiro[var].N - 84;
            value = value + tiros[jogador].N;
            value = value/tabuleiro[var].N;
            value = value + 5;

            //deduz 'value' da pontuacao.
            tiros[jogador].pontos = tiros[jogador].pontos - value;
        break;
    
        default:
        break;
    }

}

void marcar_tiro(struct BaseTable *tiros, struct BaseTable *tabuleiro, int jogador, int lin_temp, char col_temp){//Função que compara as matrizes e define se o jogador conseguiu um acerto ou não
    int hit;   //Parâmetro para definir se acertou ou nao, repassado a funcao 'marcar pontos'
    char line[16]= {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P'};

    for (int i=0; i<16; i++){   //Compara o caractere lido com um vetor(line) e então define um número para a posição
        //comparamos a matriz tiros do jogador A com a matriz tabuleiro do jogador B para saber se acertou ou nao um barco
        if (col_temp == line[i]){
            tiros[jogador].posicao[lin_temp-1][i] = '*';
            if (tiros[jogador].posicao[lin_temp-1][i] != tabuleiro[(jogador+1)%2].posicao[lin_temp-1][i]){ 
                tiros[jogador].posicao[lin_temp-1][i] = tabuleiro[(jogador+1)%2].posicao[lin_temp-1][i];
                hit = 1;
                marcar_pontos(tiros, tabuleiro, jogador, hit);
                int tipo = 1;
                print_tabuleiro(tabuleiro, jogador, tipo);
                printf ("\n\t\tNa mosca! Voce acertou um navio inimigo!\n");
            }
            else{
                hit = 0;
                marcar_pontos(tiros, tabuleiro, jogador, hit);
                int tipo = 1;
                print_tabuleiro(tabuleiro, jogador, tipo);
                printf ("\n\t\tRecalibre sua mira! Voce acertou a agua :(\n");
                
            }
                        
        }else{}
    }
}

void gravar_jogo(struct BaseTable *tabuleiro, struct BaseTable *tiros, int pl){
    //Ideia: Cria 5 variáveis (Ex: tab1, tab2, pont1, pont2, vez). 
    //Primeira e segunda variável(uma string): Podemos ler a matriz do tabuleiro do jogador 1 (estrutura + tiros realizados) e salvá-la como tab1. Fazer mesma coisa com a tab2, porém com a matriz do jogador 2
    //Terceira e quarta variável(int): Podemos ler os pontos de cada jogador e gravar em suas respectivar variáveis (pont1 e pont2).
    //Quinta variavel(int): 1 ou 2, representando a vez de qual jogador que parou o jogo
    //Depois, salvamos as 4 variáveis dentro de um arquivo texto que não permite alteração 

    //terminar isso aqui

    char fileName[26] = "tabuleiro.txt"; 

    FILE *game_save;
    
    game_save = fopen(fileName,"w");
    if (game_save == NULL){
        printf ("error");
    }

    fwrite(tabuleiro, 2*sizeof(struct BaseTable), 1, game_save);
    fwrite(tiros, 2*sizeof(struct BaseTable), 1, game_save);
    
    fclose (game_save);
}

void carregar_jogo(){
    //Ideia: Essa função vai ser mais "fácil" de criar, pois já vamos ter tudo salvo, só vamos precisar saber como (parte foda neh kkkkkk).
    //Mas a solução consiste em abrir o arquivo texto salvo, e ai já vamos ter as variáveis prontas. Sendo assim, só precisamos colocar a pontuação para rodar nas funções que estão no código (ex: tiros[jogador].pontos = pont1, logo no final da função, depois tudo vai rodar normalmente) e substituir as matrizes iniciais por tab1 e tab2. Em relação a vez ainda não pensei como da pra fazer exatamente, mas acho que deve ser o menor dos problemas
    //Extra: Poderíamos colocar aquele mecanismo de "certeza", igual do comando reset, antes do jogador selecionar o arquivo que quer abrir. Caso ele queira mesmo, podemos printar um "Carregando jogo..." com espaço de duas linhas pra cima e 2 pra baixo. Pra terminar, depois de imprimir o tabuleiro do jogador que parou, poderíamos printar a mensagem "A vez é do jogador X\n Insira um comando jogador X...", Mas não sei se é tão necessário, já que já vai ter "Insira um comando jogador X"...
}

void funcao_zera_pontos(){   //Zera as pontuacoes dos jogadores
    for (int i = 0; i < 2; i++){
        tiros[i].pontos = 0;
        tiros[i].N = 0;
        tabuleiro[i].N = 256;
        tabuleiro[i].pontos = 0;
    }   
}

void exibir_desenvolvedores(){//Printa os seguintes dados na tela

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

void print_tabuleiro( struct BaseTable *tabuleiro, int jogador, int tipo){   //Cabeçalho do tabuleiro, com o player e sua pontuação
    printf ("\t   _______________________________________________\n");
    printf ("\t  |                                               |\n");
    printf ("\t         P L A Y E R  %d         Pontos: %.1f\n", (jogador+1) , tiros[jogador].pontos);
    printf ("\t  |_______________________________________________|\n");
    
    
    //Sessão para printar a tabela:
    char M[34][34];   //Matriz que conterá a tabela. (É maior pois devemos considerar os espaços das barras e traços)
    char barra = '|', traco='-', ponta = '+', espaco=' ';   //Variáveis para criação da tabela (Estrutura)
    char letra[16] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P'}; //Vetor para auxiliar na posição da coordenadas (letras)
    int num = 1, position = 0; //Variáveis que também irão auxiliar na criação das coordenadas
    int lin = 0;
    int col = 0;

    //Loop for para iniciar a assimilação de valores às posições da matriz
    for (int i=0;i<34;i++){
        for (int j=0; j<34; j++){
            if (i==0){   //Condição para posicionar as letras
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
                M[i][j]= num;
                num++;
            }

            else if (i%2==0 && j%2!=0)
                M[i][j]= barra;

            else if (i%2!=0 && j%2== 0 && j!=0)
                M[i][j]=traco;  

            else if (i%2!=0 && j==0) 
                M[i][j]=espaco;

            else{   //Para usar a mesma função para imprimir todas as matrizes, usamos a variável 'tipo' nesse 'switch'
                switch (tipo){
                case 1:   
                        M[i][j]= tiros[jogador].posicao[col][lin];   //Local das coordenadas
                        lin = lin+1;
                        if (lin==16){
                            lin = 0;
                            col++;
                            }
                        else{}
                    break;

                case 2:
                        M[i][j]= tabuleiro[jogador].posicao[col][lin]; //Local das coordenadas
                        lin = lin+1;
                        if (lin==16){
                            lin = 0;
                            col++;
                            }
                        else{}
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

void layout_menu(){ //Função responsável por printar a tela do menu inicial
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