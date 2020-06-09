//Adaptações: Passar o parâmetro para a função (a matriz do tabuleiro), aumentar em 1 valor o loop que tem a variável z (representa o tabuleiro de cada jogador, deixei como 1 porque tava sem o struct da matriz), mudar as matrizes para o nome original, fazer a equivalência da matriz (não sei como ta na original, mas podemos deixar como " " em vez de "0" cada posição nao ocupada), dar um jeito de fazer aparecer "P1" ou "C2" em vez de só "P" e "C" e arrumar o bug (O problema ta na hora de checar se a posição já foi ou não ocupada... Acho que não to usando o break direito, porque ele continua o laço pra sempre e fode tudo), se quiser ver que o problema é la mesmo tira o c=0 depois do else de cada condicao do switch que o negócio vai rodar (tudo fudido mas vai kkkkkkk)

#include <stdio.h>
#include <stdlib.h>

void posiciona_barcos();

int main(){
    int M1[16][16], M2[16][16];
    posiciona_barcos(M1, M2);
    return 0;
}

void posiciona_barcos(char M1[16][16], int M2[16][16]){
    int v[20], direcao[10], i, tipo, cond1, cond2, cond3, cond4, vez;   //Definindo as variáveis que servirão para sabermos informações "chaves" de cada barco, ou seja, onde a primeira peça estará localizada, juntamente com a direção que seguirão as seguintes
    char letra[4] = {'P', 'C', 'T', 'H'};

    for (i=0; i<16; i++){
        for (int j=0; j<16; j++){
            M1[i][j]='0';
        }
    }

    srand(time(NULL));
    //Loop para fazer a mesma coisa para o tabuleiro dos 2 jogadores
    for (int z=0; z<1; z++){
        //Sendo cada bloco composto por uma coordenada x e outra y, temos que cada barco possui 2, ou seja, como temos 10 barcos, precisaremos de 20 valores
        for (i=0; i<20; i++)
            v[i]= 1+ rand()%16;
        
        //A direção consistirá em 4 opções: Para cima(0), para baixo (1), para a direita (2) e para a esquerda(3)
        for (i=0; i<10; i++)
            direcao[i]=rand()%4;

        //Loop para fazer definir o bloco referência de cada barco e sua respectiva direção de construção
        for (i=0;i<20;i++){
            //Condições que servirão para definir "limites" para o posicionamento dos blocos referência, variando de acordo com o tipo de barco
            if (i==0){
                cond1=6;
                cond2=11;
                cond3=10;
                cond4=7;
            }

            else if(i==2){
                cond1=7;
                cond2=10;
                cond3=9;
                cond4=8;
            }

            else if(i==6){
                cond1=9;
                cond2=8;
            }

            else{
                cond1=10;
                cond2=7;

            }

            //Sequência de condições para garantir que não haja, no futuro, nenhuma construção impossível de ser realizada em relação ao porta-aviões e ao couraçado
            if (i<6){
                if (v[i]>cond1 && v[i+1]>cond1){
                    if(v[i]<cond2 && v[i+1]<cond2){
                        int j=i;
                        do{
                            v[j]=rand()%16;
                            if(j==i+1)
                                j=i-1;
                            i++;
                        }while(v[i]>cond1 && v[i]<cond2 && v[i+1]>cond1 && v[i+1]<cond2);
                    }

                    else if (v[i]<cond2 && v[i+1]>cond3)
                        direcao[vez]=0;

                    else if(v[i]>cond3 && v[i+1]<cond2)
                        direcao[vez]=3;
                    
                    else{
                        do{
                            direcao[vez] = rand()%4;
                        }while (direcao[vez] == 1 || direcao[vez] == 2);
                    }
                }
                else if(v[i]<cond4 && v[i+1]>cond1){
                    if (v[i+1]<cond2)
                        direcao[vez]=2;
                    
                    else {
                        do{
                            direcao[vez] = rand()%4;
                        }while (direcao[vez]==1 || direcao[vez]==3);
                    }
                }

                else if(v[i]>cond1 && v[i+1]<cond4){
                    if (v[i]<cond2)
                        direcao[vez]=1;
                
                    else{
                        do{
                            direcao[vez] = rand()%4;
                        }while (direcao[vez]==0 || direcao[vez]==2);
                    }
                }

                else{
                    do{
                        direcao[vez] = rand()%4;
                    }while (direcao[vez]==0 || direcao[vez]==3);
                }
            }
            //Condições para os torpedeiros e hidroaviões
            else{
                if(v[i]<cond2){
                    if (v[i+1]<cond2){
                        do{
                            direcao[vez] = rand()%4;
                        } while(direcao[vez] == 0 || direcao[vez] == 3);
                    }

                    else if (v[i+1]>cond1)
                        do{
                            direcao[vez] = rand()%4;
                        } while(direcao[vez] == 1 || direcao[vez] == 3);
                    
                    else{
                        do{
                            direcao[vez] = rand()%4;
                        }while(direcao[vez] == 3);
                    }
                }
                else if(v[i]>cond1){
                    if(v[i+1]<cond2){
                        do{
                            direcao[vez] = rand()%4;
                        } while(direcao[vez] == 0 || direcao[vez] == 2);    
                    }
                    
                    if (v[i+1]>cond1){
                        do{
                            direcao[vez] = rand()%4;
                        } while(direcao[vez] == 1 || direcao[vez] == 2);
                    }

                    else{
                        do{
                            direcao[vez] = rand()%4;
                        }while(direcao[vez] == 2);
                    }
                }
                else{
                    if(v[i+1]<cond2){
                        do{
                            direcao[vez] = rand()%4;
                        } while(direcao[vez] == 0); 
                    }

                    if (v[i+1]>cond1){
                        do{
                            direcao[vez] = rand()%4;
                        } while(direcao[vez] == 1);
                    }

                    else
                        direcao[vez] = rand()%4;
                    
                }
                
            }
            int cont;
            int c;

            //Switch para "montar" cada peça, a partir do bloco de origem e a direção definida, após verificar se já foi colocado ou não um bloco na coordenada projetada
            switch (direcao[vez]){
                case 0:
                    for (cont=0; cont<cond2; cont++){   //Loop para posicionar os blocos
                        if(M1[v[i]][v[i+1]-c]== '0'){   //Se o espaço estiver disponível, o bloco será colocado
                            M1[v[i]][v[i+1]-c] = letra[tipo];
                            c++;
                        }
                        else{                           //Caso não esteja, "reiniciamos" todas as posições, voltando ao valor original, regulamos o valor de "i" e da variável "vez" para que refaça o processo sem haver conflitos e quebramos o ciclo
                            c=0;
                            for (cont=0; cont<cond2; cont++)
                                M1[v[i]][v[i+1]-c] = '0';
                            i=i-2;
                            vez--;
                            break;
                        }
                    }
                    break;
                
                case 1:
                    c=0;
                    for (cont=0; cont<cond2; cont++){
                        if(M1[v[i]][v[i+1]+c]== '0'){
                            M1[v[i]][v[i+1]+c] = letra[tipo];
                            c++;
                        }
                        else{
                            c=0;
                            for (cont=0; cont<cond2; cont++)
                                M1[v[i]][v[i+1]+c] = '0';
                            i=i-2;
                            vez--;
                            break;
                        }
                    }
                    break;
                
                case 2:
                    c=0;
                    for (cont=0; cont<cond2; cont++){
                        if(M1[v[i]+c][v[i+1]]== '0'){
                            M1[v[i]+c][v[i+1]] = letra[tipo];
                            c++;
                        }
                        else{
                            c=0;
                            for (cont=0; cont<cond2; cont++)
                                M1[v[i]+c][v[i+1]] = '0';
                            i=i-2;
                            vez--;
                            break;
                        }
                    }
                    break;

                default:
                    c=0;
                    for (cont=0; cont<cond2; cont++){
                        if(M1[v[i]-c][v[i+1]]== '0'){
                            M1[v[i]-c][v[i+1]] = letra[tipo];
                            c++;
                        }
                        else{
                            c=0;
                            for (cont=0; cont<cond2; cont++)
                                M1[v[i]-c][v[i+1]] = '0';
                            i=i-2;
                            vez--;
                            break;
                        }
                    } 
                    break;
            }
                
            //Como cada barco possui 2 coordenadas, utilizamos o i++ para não dar problema e aumentamos em 1 o valor da vez para indicar que passamos para o próximo barco
            i++;
            vez++;
        }   
    }
    //Tirar isso aqui depois, foi só pra ver como tava ficando
    for (i=0; i<16; i++){
        for (int j=0; j<16; j++){
            if (j==15)
                printf("%c\n", M1[i][j]);
            else
                printf("%c  ", M1[i][j]);
        }
    }
}
    

