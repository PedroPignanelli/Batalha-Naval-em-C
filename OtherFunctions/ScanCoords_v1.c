#include <stdio.h>
//le uma letra scanneada e associa ela a uma posicao de vetor
int main(){
    char col_temp;
    scanf ("%c", &col_temp);
    char line[16]= {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P'};
    for (int i=0; i<16; i++){
        if (col_temp == line[i]){
            printf ("Sucesso %d", i);
        }else{}
    }
    return 0;

}