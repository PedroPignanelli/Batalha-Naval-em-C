#include <stdio.h>

void Cria(){
    char M[34][34]; //Matriz que conterá a tabela. (É maior pois devemos considerar os espaços das barras e traços)

    char barra = '|', traco='-', ponta = '+', coordenadas=' ', espaco=' '; //Variáveis para criação da tabela (Estrutura)

    char letra[16] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P'}; //Vetor para auxiliar na posição da coordenadas (letras)
    int cont=1, position =0; //Variáveis que também irão auxiliar na criação das coordenadas
 
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

            else
                M[i][j]= coordenadas; //Local das coordenadas

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
int main(void){
    Cria();
    return 0;
}
