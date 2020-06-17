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

struct Remainings{   //Struct que servirá para sabermos quantas peças faltam para afundar um barco (para contar na pontuação)
    int counth;
    int countt;
    int countc;
    int countp;
};

    
//Protótipos das funcoes

void iniciar_jogo();
void posiciona_barcos(struct BaseTable *tabuleiro);
void marcar_tiro(struct BaseTable *tiros, struct BaseTable *tabuleiro, struct Remainings *contador, int jogador, int lin_temp, char col_temp);
void marcar_pontos(struct BaseTable *tiros, struct BaseTable *tabuleiro, int jogador, int hit, int qa, int ba);
void gravar_jogo(struct BaseTable *tabuleiro, struct BaseTable *tiros);
void carregar_jogo(struct BaseTable *tabuleiro, struct BaseTable *tiros);
void funcao_zera_pontos(struct BaseTable *tabuleiro, struct BaseTable *tiros);
void print_tabuleiro(struct BaseTable *tabuleiro, int jogador, int tipo);
void exibir_desenvolvedores();
void layout_menu();
void exibir_ajuda();

struct BaseTable tabuleiro[2];   //Definir duas matrizes diferentes, uma para cada jogador
struct BaseTable tiros[2];       //A matriz tabuleiro é onde põe os navios e os tiros onde registramos os disparos

//Definindo o contador p em forma de vetor, assim sendo possível de saber de quem é a vez
struct Remainings contador[2];



int main(){
    layout_menu();   //Imprimindo o menu de inicio

    int comand_menu, flagmain = 0;   //Fica em loop inifinito até que 'flagmain' seja alterada        

    while (flagmain == 0){
        scanf ("%d", &comand_menu);
            fflush (stdin);

        switch (comand_menu){
            case 1:
                iniciar_jogo(tabuleiro, tiros);
                flagmain = 1;   //Quebra o laço de repeticao do menu de entrada e inicia o jogo
            break;

            case 2: 
                carregar_jogo(tabuleiro, tiros);   //Carrega algum jogo salvo
                flagmain = 1;
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

    while (status == 0){       //Loop para funcionamento do jogo, que só será rompido caso solicitado pelo jogador
        int tipo = 1;          //E o tipo do tabuleiro, no caso, aqui sempre sera impresso o tabuleiro 'tipo 1' => tiros
        int jogador = pl%2;    //Variavel que sera repassada para as outras funcoes definindo qual player esta jogando.
        int hit;

        print_tabuleiro(tiros, jogador, tipo);
        printf("\n\t\tEste e o mapa de onde voce ja atirou!\nInsira um comando, jogador #%d:\n", (jogador+1));
        scanf(" %s[^\n]", comando);
        
        //Converte o comando de cada jogador para caixa alta (facilitara a programação ao longo do código)
        for(int i = 0; i < 10; i++)
            comando[i]=toupper(comando[i]); 

        if (strcmp (comando, "SAIR") == 0){
            int confirm = 0;   //Variavel que servirá para confirmar a ação

            printf ("\n\nDeseja realmente sair?\n\n[1]SIM\t\t[2]NAO (voltar ao jogo)\n");
            scanf ("%d", &confirm);

            if (confirm == 1){
                funcao_zera_pontos(tabuleiro, tiros);

                return 0;
            }

            else
                confirm = 0;   //redefine o valor de confirm
            
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
            marcar_tiro (tiros, tabuleiro, contador, jogador, lin_temp, col_temp);

            pl = pl+1;   //Soma 1 ao valor de pl sempre que alguem atira, "alternando" quem está atirando
        }

        else if (strcmp (comando, "RESET") == 0){   //Chama as funções que recomeça o jogo e zera os pontos
            funcao_zera_pontos(tabuleiro, tiros);                   
            iniciar_jogo (tabuleiro, tiros);
        }

        else if (strcmp(comando, "AJUDA") == 0){    //Chama a função que printa os comandos do jogo
            exibir_ajuda(); 
        }

        else if (strcmp (comando, "GRAVAR") == 0){   //Chama a função que salva o progresso atual do jogo
            gravar_jogo(tabuleiro, tiros);
        }

        else if (strcmp (comando, "ACASO") == 0){   //Chama apenas a função que inicia o jogo, assim começando um novo sem zeras as pontuações
            printf ("\nReiniciando o jogo...\n");
            pl = 0;
            iniciar_jogo(tabuleiro, tiros);
        }

        else{   //Caso seja digitado um comando inválido, entramos nessa condição
            printf ("\nComando desconhecido, insira um comando valido.\nSe precisar de ajuda com os comandos, digite 'ajuda':\n");
        }

        //Para melhorar a interface introduzimos o comando "getch()", pausando após um comando, a fim de melhorar a visualização
        printf ("\n\n\tPressione qualquer tecla para continuar a batalha\n\n");
        getch ();
            fflush (stdin);

    }

printf ("\nSucesso!"); 

return 0;  
}

void exibir_ajuda(){    // exibir todos os comandos, um menu de ajuda

    printf ("\n\tLISTA DE COMANDOS (funcionam somente durante a partida):");
    printf ("\n\t'ajuda' \tExibe esta lista de comandos!");
    printf ("\n\t'POW'     \tInsira o comando POW seguido das coordenadas onde voce deseja atirar!");
    printf ("\n\t'reset' \tReinicia o jogo inteiro, zerando as pontuacoes!");
    printf ("\n\t'acaso' \tReinicia o jogo inteiro, mas mantem as pontuacoes!");
    printf ("\n\t'gravar' \tSalva o jogo, para voce continua-lo depois!");
    printf ("\n\t'sair'    \tFecha o aplicativo :( \n");
    printf("\n\n\t Lembre-se: Sempre insira as coordenadas dos seus tiros da forma 'letra numero'\n");
}

void iniciar_jogo(struct BaseTable *tabuleiro, struct BaseTable *tiros){   //Define os parametros iniciais das matrizes e contagens do jogo
    for (int i = 0; i < 2; i++){        //Definimos as matrizes "tabuleiro"(onde as posições dos barcos são salvas) como sendo inteira de '*'
        for (int j = 0; j < 16; j++){   //Onde tivermos um barco, ela sera posteriormente definida com outro caractere
            for (int k = 0; k <16; k++){
                tabuleiro[i].posicao[j][k] = '*';   //Definimos as matrizes tiros como sendo inteiras de 'espaços'
                tiros[i].posicao[j][k] = ' ';       //A cada tiro ela assume o valor da mesma coordenada da matriz tabuleiro do jogador adversario
            }    
        }   
    }

    posiciona_barcos (tabuleiro);

    tabuleiro[0].N = 256;   //Define o numero de casas inicial do tabuleiro do jogador (256)
    tabuleiro[1].N = 256;

    tiros[0].N = 0;        //Define a quantidade de acertos no inicial do jogador (zero)
    tiros[1].N = 0;
}

void posiciona_barcos(struct BaseTable *tabuleiro){
    int validation = 0;
    int direction;
    time_t start, end;
    srand(time(NULL));

    for (int player = 0; player < 2; player++){
        if (player==0) printf ("\nOs Hidro-Avioes de patrulha avistaram a armada inimiga...");
        //posiciona PortaAvioes - 10 casas, 5 x 2
        direction = rand()%2;   // 0 -> Horizontal / 1-> Vertical
        int x, y;
        
        if (direction == 0){
            do{
            x = rand() % 16;   //Coordenadas da peça "base" do barco
            y = rand() % 16;
            } while ( x >= 11 || y >= 14 );   //Limites para não dar erro na construção
        
            tabuleiro[player].posicao[x][y] = 'P';
            tabuleiro[player].posicao[x+1][y] = 'P';
            tabuleiro[player].posicao[x+2][y] = 'P';
            tabuleiro[player].posicao[x+3][y] = 'P';
            tabuleiro[player].posicao[x+4][y] = 'P';
            tabuleiro[player].posicao[x][y+1] = 'P';
            tabuleiro[player].posicao[x+1][y+1] = 'P';
            tabuleiro[player].posicao[x+2][y+1] = 'P';
            tabuleiro[player].posicao[x+3][y+1] = 'P';
            tabuleiro[player].posicao[x+4][y+1] = 'P';
        }

        else{
            do{
            x = rand() % 16;
            y = rand() % 16;                
            } while ( x == 15 || y >= 11 );
            
            tabuleiro[player].posicao[x][y] = 'P';
            tabuleiro[player].posicao[x][y+1] = 'P';
            tabuleiro[player].posicao[x][y+2] = 'P';
            tabuleiro[player].posicao[x][y+3] = 'P';
            tabuleiro[player].posicao[x][y+4] = 'P';   
            tabuleiro[player].posicao[x+1][y] = 'P';
            tabuleiro[player].posicao[x+1][y+1] = 'P';
            tabuleiro[player].posicao[x+1][y+2] = 'P';
            tabuleiro[player].posicao[x+1][y+3] = 'P';
            tabuleiro[player].posicao[x+1][y+4] = 'P';
        }
        
        //faz o programa esperar 1 segundo ate posicionar os couracados -> nova semente para o srand (time)
        time(&start);
        do time(&end); while(difftime(end, start) <= 1);

        if (player==1) printf ("\nOs Porta Avioes ja estao lancaram suas aeronaves...");

        //Posiciona couracados - 2 couracados - 5 casas cada, 5 x 1
        for (int i = 0; i < 2; i++){ //posicionar duas vezes (sao 2 couracados)
            srand(time(NULL));
            direction = rand()%2; // 0 -> Horizontal / 1-> Vertical
            int x, y;

            if (direction == 0){
                do{
                x = rand() % 16;
                y = rand() % 16;                
                } while (x > 10 || tabuleiro[player].posicao[x][y] != '*' || tabuleiro[player].posicao[x+1][y] != '*' || tabuleiro[player].posicao[x+2][y] != '*' || tabuleiro[player].posicao[x+3][y] != '*' || tabuleiro[player].posicao[x+4][y] != '*');

                tabuleiro[player].posicao[x][y] = 'C';
                tabuleiro[player].posicao[x+1][y] = 'C';
                tabuleiro[player].posicao[x+2][y] = 'C';
                tabuleiro[player].posicao[x+3][y] = 'C';
                tabuleiro[player].posicao[x+4][y] = 'C';
                }

            else{
                do{
                x = rand() % 16;
                y = rand() % 16;                
                } while (y > 10 || tabuleiro[player].posicao[x][y] != '*' || tabuleiro[player].posicao[x][y+1] != '*' || tabuleiro[player].posicao[x][y+2] != '*' || tabuleiro[player].posicao[x][y+3] != '*' || tabuleiro[player].posicao[x][y+4] != '*');

                tabuleiro[player].posicao[x][y] = 'C';
                tabuleiro[player].posicao[x][y+1] = 'C';
                tabuleiro[player].posicao[x][y+2] = 'C';
                tabuleiro[player].posicao[x][y+3] = 'C';
                tabuleiro[player].posicao[x][y+4] = 'C';
            }

            time(&start);
            do time(&end); while(difftime(end, start) <= 1);    
        } 


        if (player==0) printf ("\nOs Torpedeiros estao se posicionando para o ataque ...");

        //Posiciona torpedeiros - 3 torpedeiros - 3 casas cada, 3 x 1
        for (int i = 0; i < 3; i++){ // sao 3 torpedeiros
            srand(time(NULL));
            direction = rand()%2; // 0 -> Horizontal / 1-> Vertical
            int x, y;

            if (direction == 0){
                do{
                x = rand() % 16;
                y = rand() % 16;                
                } while (x > 13 || tabuleiro[player].posicao[x][y] != '*' || tabuleiro[player].posicao[x+1][y] != '*' || tabuleiro[player].posicao[x+2][y] != '*');

                tabuleiro[player].posicao[x][y] = 'T';
                tabuleiro[player].posicao[x+1][y] = 'T';
                tabuleiro[player].posicao[x+2][y] = 'T';
            }
            else{
                do{
                x = rand() % 16;
                y = rand() % 16;                
                } while (y > 13 || tabuleiro[player].posicao[x][y] != '*' || tabuleiro[player].posicao[x][y+1] != '*' || tabuleiro[player].posicao[x][y+2] != '*');

                tabuleiro[player].posicao[x][y] = 'T';
                tabuleiro[player].posicao[x][y+1] = 'T';
                tabuleiro[player].posicao[x][y+2] = 'T';

            }

            time(&start);
            do time(&end); while(difftime(end, start) <= 0.5);    
        } 

        if (player==1) printf ("\nOs Couracados ja tem o inimigo na mira...\nAtencao, a batalha vai comecar!\n");

        //Posiciona Hidroavioes - 4 hidroavioes - 2 casas cada, 2 x 1
        for (int i = 0; i < 4; i++){ //sao 4 hidroavioes
            srand(time(NULL));
            direction = rand()%2; // 0 -> Horizontal / 1-> Vertical
            int x, y;

            if (direction == 0){
                do{
                x = rand() % 16;
                y = rand() % 16;                
                } while (x > 14 || tabuleiro[player].posicao[x][y] != '*' || tabuleiro[player].posicao[x+1][y] != '*');

                tabuleiro[player].posicao[x][y] = 'H';
                tabuleiro[player].posicao[x+1][y] = 'H';
            }
            else{
                do{
                x = rand() % 16;
                y = rand() % 16;                
                } while (y > 14 || tabuleiro[player].posicao[x][y] != '*' || tabuleiro[player].posicao[x][y+1] != '*');

                tabuleiro[player].posicao[x][y] = 'H';
                tabuleiro[player].posicao[x][y+1] = 'H';
            }
        time(&start);
        do time(&end); while(difftime(end, start) <= 0.5);    
        } 
    } 
}
    
void marcar_tiro(struct BaseTable *tiros, struct BaseTable *tabuleiro, struct Remainings *contador, int jogador, int lin_temp, char col_temp){  //Função que compara as matrizes e define se o jogador conseguiu um acerto ou não
    int hit;
    char line[16]= {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P'};

    for (int i=0; i<16; i++){   //Compara o caractere lido com um vetor(line) e então define um número para a posição
        //comparamos a matriz tiros do jogador A com a matriz tabuleiro do jogador B para saber se acertou ou nao um barco
        if (col_temp == line[i]){
            tiros[jogador].posicao[lin_temp-1][i] = '*';
            if (tiros[jogador].posicao[lin_temp-1][i] != tabuleiro[(jogador+1)%2].posicao[lin_temp-1][i]){
                tiros[jogador].posicao[lin_temp-1][i] = tabuleiro[(jogador+1)%2].posicao[lin_temp-1][i];

                char embarc;  //Variável que auxiliará na determinação de qual barco foi atingido
                int qa, ba;   //Variáveis da fórmula do acréscimo de pontos

                embarc = tabuleiro[(jogador+1)%2].posicao[lin_temp-1][i];  //A variável embarcação assume o valor (letra do barco) de onde o jogador deu o tiro
                
                //Condições para saber qual tipo de barco que é, para determinarmos o qa e ba 
                if (embarc == 'H'){
                    qa = 2 - contador[jogador].counth;
                    contador[jogador].counth++;
                    ba= 2;
                    if (contador[jogador].counth==2) //Indica que o barco inteiro foi afundado, reiniciando a contagem para os próximos
                        contador[jogador].counth=0;
                }

                else if (embarc == 'T'){
                    qa = 3 - contador[jogador].countt;
                    contador[jogador].countt++;
                    if (contador[jogador].countt==3)
                        contador[jogador].countt=0;
                    ba= 3;
                }

                else if (embarc == 'C'){
                    qa = 5 - contador[jogador].countc;
                    contador[jogador].countc++;
                    if (contador[jogador].countc==5)
                        contador[jogador].countc=0;
                    ba=5;
                }

                else{
                    qa = 10 - contador[jogador].countp;
                    contador[jogador].countp++;
                    ba=10;
                }

                hit = 1;
                marcar_pontos(tiros, tabuleiro, jogador, hit, qa,ba);
                int tipo = 1;
                print_tabuleiro(tabuleiro, jogador, tipo);
                printf ("\n\t\tNa mosca! Voce acertou um navio inimigo!\n");
            }
            else{
                int qa, ba;
                hit = 0;
                marcar_pontos(tiros, tabuleiro, jogador, hit, qa, ba);
                int tipo = 1;
                print_tabuleiro(tabuleiro, jogador, tipo);
                printf ("\n\t\tRecalibre sua mira! Voce acertou a agua :(\n");
                
            }
                        
        }else{}
    }
}

void marcar_pontos(struct BaseTable *tiros, struct BaseTable *tabuleiro, int jogador, int hit, int qa, int ba){//Função responsável por definir as pontuacoes de cada jogador ao longo da partida
    int var = (jogador+1)%2;   //Var é o outro jogador, o que "recebe o tiro" 
    float value = 0;           //Variável para registrar quantos pontos o jogador ganha ou perde

    tabuleiro[var].N = tabuleiro[var].N - 1;   //A cada tiro dado, o numero de casas 'N' no tabuleiro DO ADVERSARIO diminui 1

    switch(hit){
        case 1:
            tiros[jogador].N = tiros[jogador].N + 1;         //Aumenta 1 na contagem de acertos do jogador
            value = (float)(ba*qa*1000)/256;

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


void gravar_jogo(struct BaseTable *tabuleiro, struct BaseTable *tiros){
    char tabuleiro_P1[256], tabuleiro_P2[256];
    char tiros_P1[256], tiros_P2[256];
        
    //Esse laço associa as posições das matrizes aos respectivos vetores
    int k = 0;
    for (int i = 0; i<16; i++){
        for (int j = 0; j<16;j++){
        tabuleiro_P1[k] = tabuleiro[0].posicao[j][i];
        tabuleiro_P2[k] = tabuleiro[1].posicao[j][i];

        if(tiros[0].posicao[j][i] == ' '){
            tiros_P1[k] = 'x';
        }else{tiros_P1[k] = tiros[0].posicao[j][i];}
        
        if(tiros[1].posicao[j][i] == ' '){
            tiros_P2[k] = 'x';
        }else{tiros_P2[k] = tiros[1].posicao[j][i];}
        
        k++;
        }
    }
    
    //Aqui estamos definindo o nome do arquivo com base no dia do ano, hora, minuto e segundo
    struct tm *time_s; //Struct padrão da biblioteca time.h
    time_t segundos;
    time (&segundos);
    time_s = localtime (&segundos);
    char fileName[40];
    sprintf(fileName, "tabuleiro_%d-%d-%d-%d.txt", time_s->tm_yday, time_s->tm_hour, time_s->tm_min, time_s->tm_sec); 
   
   //Criamos o arquivo de texto onde iremos gravar o progresso do jogo e o abrimos para escrita
    FILE *game_save;
    game_save = fopen(fileName,"w");
    if (game_save == NULL){
        printf ("\n\t Ocorreu um erro desconhecido ao salvar o arquivo\n");
    }

    //Escrevemos os vetores criados anteriormente no arquivo
    //Usamos o marcador ";" para separar cada elemento. Sera util para carregar o arquivo.
    fwrite(tabuleiro_P1, 256*sizeof(char), 1, game_save);
    fprintf (game_save, ";");
    fwrite(tabuleiro_P2, 256*sizeof(char), 1, game_save);
    fprintf (game_save, ";");
    fwrite(tiros_P1, 256*sizeof(char), 1, game_save);
    fprintf (game_save, ";");
    fwrite(tiros_P2, 256*sizeof(char), 1, game_save);
    fprintf (game_save, ";\n");
    fprintf (game_save, "%f;%f;", tiros[0].pontos, tiros[1].pontos);    // Salvamos os outros dados do jogo (pontuação, tiros dados,
    fprintf (game_save, "%d;%d;", tiros[0].N, tiros[1].N);              // casas livres no tabuleiro)
    fprintf (game_save, "%d;%d;", tabuleiro[0].N, tabuleiro[1].N);

    fclose (game_save);//fecha o arquivo e gera um feedback na tela.
    printf ("\n\tJogo salvo com sucesso!\n");
}

void carregar_jogo(struct BaseTable *tabuleiro, struct BaseTable *tiros){
    
    char load_name[96];

    printf ("\n\tInsira o nome do arquivo de jogo salvo:\n");
    scanf ("%s[^\n]", &load_name);

    FILE  *game_load;
    game_load = fopen (load_name, "r");

    if (game_load == NULL){
        printf ("\nErro na abertura do arquivo. Fechando janela");
        fclose (game_load);
        exit (1);
    }
    else{
        printf ("Carregando o jogo...\n");
        char RtabuleiroP1[256], RtabuleiroP2[256], RtirosP1[256], RtirosP2[256];
        
        fread(&RtabuleiroP1, sizeof(char), 257, game_load);
        fread(&RtabuleiroP2, sizeof(char), 257, game_load);
        fread(&RtirosP1, sizeof(char), 257, game_load);
        fread(&RtirosP2, sizeof(char), 257, game_load);
        fscanf (game_load, "%f;%f;%d;%d;%d;%d;", &tiros[0].pontos, &tiros[1].pontos, &tiros[0].N, &tiros[1].N, &tabuleiro[0].N, &tabuleiro[1].N);

        for (int i = 0, k = 0; i < 16; i++){
            for (int j = 0; j < 16; j++, k++){
            tabuleiro[0].posicao[j][i] = RtabuleiroP1[k];
            tabuleiro[1].posicao[j][i] = RtabuleiroP2[k];
            if (RtirosP1[k] == 'x'){
                tiros[0].posicao[j][i] = ' ';
            }else{tiros[0].posicao[j][i] = RtirosP1[k];}
            if (RtirosP2[k] == 'x'){
                tiros[1].posicao[j][i] = ' ';
            }else{tiros[1].posicao[j][i] = RtirosP2[k];}
            }
        }
    }

    fclose (game_load);        
}

void funcao_zera_pontos(struct BaseTable *tabuleiro, struct BaseTable *tiros){   //Zera as pontuacoes dos jogadores
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
    printf("\n\t\t\t\t\t|     SSC0304 - Introducao a Programacao para Engenharias   |");
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
    printf ("\n\t                                                                     _|__");
    printf ("\n\t                                                                    /    \\ ");
    printf ("\n\t                                                          ____|    /  []  |");
    printf ("\n\t                                                         |____|   |        \\");
    printf ("\n\t                                                             ||   | []   [] |");
    printf ("\n\t                                                _____       _||___|---------||_____        _____");
    printf ("\n\t                            _____     _________/     \\      |     []  []  []      \\\\      /     \\_________     _____");
    printf ("\n\t     ____|          _______/     \\    |_______________|    //    ____________      ||    |_______________|    /     \\________");
    printf ("\n\t    |____|          |_____________|           |      |    //     |    |     |      ||      |      |          |______________|");
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