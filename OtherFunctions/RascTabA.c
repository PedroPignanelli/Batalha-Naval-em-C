#include <stdio.h>

void Cria(){
    int M[34][34]; //Matriz que conterá a tabela. (É maior pois devemos considerar os espaços das barras e traços)

    char barra = '|', traco='-', ponta = '+', vazio=' ', espaco; //Variáveis para criação da tabela (Estrutura)

    char v='A'; //Variável para auxiliar na posição da coordenadas (letras)

    int cont=1; //Variável para auxiliar na posição da coordenadas (números)
    
    //Loop for para iniciar a assimilação de valores às posições da matriz
    for (int i=0;i<34;i++){
        for (int j=0; j<34; j++){
            
            //Condição para posicionar as letras
            if (i==0){ 
                if (j%2==0 && j!= 0){
                    M[i][j]=v;
                    v++;
                }
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

            else if (i == 0 && j%2!=0 || i%2!=0 && j==0) 
                M[i][j]=vazio;

            else 
                M[i][j]=espaco;

        }
    }

    for (int i=0; i<34; i++){
        for (int j=0;j<34;j++){
            if(j==0 && i!=0 && i%2 == 0 ){
                printf("%02d", M[i][j]);  
            }
            else{
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
