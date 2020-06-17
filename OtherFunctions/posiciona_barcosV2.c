#include <stdio.h>
#include <string.h>
#include <time.h>

int main(){

char tabuleiro[16][16];
char water;

water = '*';

    for (int j = 0; j<16; j++){
        for (int k = 0; k<16; k++){
            tabuleiro[j][k] = water;
        }
    }
    printf ("tab Pre Posi");
    for (int j = 0; j<16; j++){
        for (int k = 0; k<16; k++){
            printf ("%c", tabuleiro[j][k]);
            if (k == 15){
                printf ("\n");
            }
        }
    }
    printf ("\n");
    printf ("As aeronaves de patrulha avistaram a armada inimiga..."); //mudar essa frase e a dos outros
    //posiciona PortaAvioes - 10 casas, 5 x 2
    int validation = 0;
    int direction;
    time_t start, end;
    srand(time(NULL));

    while (validation == 0){
        direction = rand()%2; // 0 -> Horizontal / 1-> Vertical
        int x, y;
        if (direction == 0){
            do{
            x = rand() % 16;
            y = rand() % 16;

            } while ( x >= 11 || y >= 14 );
        
            tabuleiro[x][y] = 'P';
            tabuleiro[x+1][y] = 'P';
            tabuleiro[x+2][y] = 'P';
            tabuleiro[x+3][y] = 'P';
            tabuleiro[x+4][y] = 'P';
            tabuleiro[x][y+1] = 'P';
            tabuleiro[x+1][y+1] = 'P';
            tabuleiro[x+2][y+1] = 'P';
            tabuleiro[x+3][y+1] = 'P';
            tabuleiro[x+4][y+1] = 'P';
        }
        else{
            do{
            x = rand() % 16;
            y = rand() % 16;                
            } while ( x == 15 || y >= 11 );
            
            tabuleiro[x][y] = 'P';
            tabuleiro[x][y+1] = 'P';
            tabuleiro[x][y+2] = 'P';
            tabuleiro[x][y+3] = 'P';
            tabuleiro[x][y+4] = 'P';   
            tabuleiro[x+1][y] = 'P';
            tabuleiro[x+1][y+1] = 'P';
            tabuleiro[x+1][y+2] = 'P';
            tabuleiro[x+1][y+3] = 'P';
            tabuleiro[x+1][y+4] = 'P';
        }

    validation = 1;        
    }

    //faz o programa esperar 1 segundo ate posicionar os couracados -> nova semente para o srand (time)
    time(&start);
    do time(&end); while(difftime(end, start) <= 1);

    printf ("\nOs torpedeiros estao se posicionando para iniciar o ataque ...");
    //Posiciona couracados - 2 couracados - 5 casas cada, 5 x 1
    validation = 0;
    while (validation == 0){
        for (int i = 0; i < 2; i++){ //posicionar duas vezes (sao 2 couracados)
            srand(time(NULL));
            direction = rand()%2; // 0 -> Horizontal / 1-> Vertical
            int x, y;

            if (direction == 0){
                do{
                x = rand() % 16;
                y = rand() % 16;                
                } while (x > 10 || tabuleiro[x][y] != '*' || tabuleiro[x+1][y] != '*' || tabuleiro[x+2][y] != '*' || tabuleiro[x+3][y] != '*' || tabuleiro[x+4][y] != '*');

                tabuleiro[x][y] = 'C';
                tabuleiro[x+1][y] = 'C';
                tabuleiro[x+2][y] = 'C';
                tabuleiro[x+3][y] = 'C';
                tabuleiro[x+4][y] = 'C';
            }
            else{
                do{
                x = rand() % 16;
                y = rand() % 16;                
                } while (y > 10 || tabuleiro[x][y] != '*' || tabuleiro[x][y+1] != '*' || tabuleiro[x][y+2] != '*' || tabuleiro[x][y+3] != '*' || tabuleiro[x][y+4] != '*');

                tabuleiro[x][y] = 'C';
                tabuleiro[x][y+1] = 'C';
                tabuleiro[x][y+2] = 'C';
                tabuleiro[x][y+3] = 'C';
                tabuleiro[x][y+4] = 'C';
            }
        time(&start);
        do time(&end); while(difftime(end, start) <= 1);    
        } 
    validation = 1;       
    }

    printf ("\nOs porta avioes ja estao lancando suas aeronaves...");
    //Posiciona torpedeiros - 3 torpedeiros - 3 casas cada, 3 x 1
    validation = 0;
    while (validation == 0){
        for (int i = 0; i < 3; i++){ // sao 3 torpedeiros
            srand(time(NULL));
            direction = rand()%2; // 0 -> Horizontal / 1-> Vertical
            int x, y;

            if (direction == 0){
                do{
                x = rand() % 16;
                y = rand() % 16;                
                } while (x > 13 || tabuleiro[x][y] != '*' || tabuleiro[x+1][y] != '*' || tabuleiro[x+2][y] != '*');

                tabuleiro[x][y] = 'T';
                tabuleiro[x+1][y] = 'T';
                tabuleiro[x+2][y] = 'T';
            }
            else{
                do{
                x = rand() % 16;
                y = rand() % 16;                
                } while (y > 13 || tabuleiro[x][y] != '*' || tabuleiro[x][y+1] != '*' || tabuleiro[x][y+2] != '*');

                tabuleiro[x][y] = 'T';
                tabuleiro[x][y+1] = 'T';
                tabuleiro[x][y+2] = 'T';

            }
        time(&start);
        do time(&end); while(difftime(end, start) <= 0.5);    
        } 
    validation = 1;       
    }

    printf ("\nOs couracados ja estao com os canhoes apontados para o inimigo...\n A BATALHA VAI COMECAR!\n");
    //Posiciona Hidroavioes - 4 hidroavioes - 2 casas cada, 2 x 1
    validation = 0;
    while (validation == 0){
        for (int i = 0; i < 4; i++){ //sao 4 hidroavioes
            srand(time(NULL));
            direction = rand()%2; // 0 -> Horizontal / 1-> Vertical
            int x, y;

            if (direction == 0){
                do{
                x = rand() % 16;
                y = rand() % 16;                
                } while (x > 14 || tabuleiro[x][y] != '*' || tabuleiro[x+1][y] != '*');

                tabuleiro[x][y] = 'H';
                tabuleiro[x+1][y] = 'H';
            }
            else{
                do{
                x = rand() % 16;
                y = rand() % 16;                
                } while (y > 14 || tabuleiro[x][y] != '*' || tabuleiro[x][y+1] != '*');

                tabuleiro[x][y] = 'H';
                tabuleiro[x][y+1] = 'H';
            }
        time(&start);
        do time(&end); while(difftime(end, start) <= 0.5);    
        } 
    validation = 1;       
    }
    
    for (int j = 0; j<16; j++){
        for (int k = 0; k<16; k++){
            printf ("%c", tabuleiro[j][k]);
            if (k == 15){
                printf ("\n");
            }
        }
    }    

getch();
return 0;
}
