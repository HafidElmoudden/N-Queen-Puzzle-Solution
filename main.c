#include <stdio.h>
#include <stdlib.h>
#define N 8
int ** allocation_2D(int nl, int nc){
    int **res,i;
    res=(int**)malloc(nl*sizeof(int*));
    if(res == NULL){
        printf("Erreur d'allocation!");
        exit(31);
    }
    for(i=0;i<nl;i++){
        res[i]=(int*)malloc(nc*sizeof(int));
        if(res[i] == NULL){
            printf("Erreur d'allocation!");
            exit(31);
        }
    }
    return res;
}
int ** createBoard(int nl,int nc){
    int ** res = allocation_2D(nl,nc);
    int i,j;
    for(i=0;i<nl;i++){
        for(j=0;j<nc;j++){
            res[i][j]=0;
        }
    }
    return res;
}
// Afficher le board
int boardShow(int **tab){
    int i,j;
    for(i=0;i<N;i++){
        printf("|");
        for (j=0;j<N;j++){
            printf(" %d |",tab[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}
// Poitioner les dames
int ** damPut(int ** tab,int ipos, int jpos){
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            if (i == ipos && j == jpos)
                tab[i][j]=1;
        }
    }

}
// Depositioner les dames
int ** damDelete(int ** tab,int ipos, int jpos){
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            if (i == ipos && j == jpos)
                tab[i][j]=0;
        }
    }

}
int safeTest(int ** tab,int ipos,int jpos){
    int i,j;
    // Horizontal safe test
    for(i=0;i<N;i++){
        if(tab[ipos][i] == 1){
            if(i == jpos)
            continue;
            return 1;
        }
    }
    // Vertical safe test
    for(i=0;i<N;i++){
        if(tab[i][jpos] == 1){
            if(i == ipos)
            continue;
            return 1;
        }
    }
    // left start diagonale safe test

        // Up
    i=ipos-1;
    j=jpos-1;
    while((i>= 0 && i < N) && (j>=0 && j<N)){
        if(tab[i][j] == 1)
            return 1;
        i--;
        j--;
    }
        // Down
    i=ipos+1;
    j=jpos+1;
    while((i>= 0 && i < N) && (j>=0 && j<N)){
        if(tab[i][j] == 1)
            return 1;
        i++;
        j++;
    }

    // Right start diagnoale safe test
        // Up
    i=ipos+1;
    j=jpos+1;
    while((i>= 0 && i < N) && (j>=0 && j<N)){
        if(tab[i][j] == 1)
            return 1;
        i++;
        j++;
    }
        // Down
     i=ipos+1;
     j=jpos-1;
    while((i>= 0 && i < N) && (j>=0 && j<N)){
        if(tab[i][j] == 1)
            return 1;
        i++;
        j--;
    }
    return 0;
}
int solver(int ** tab,int nl,int nc){
    int i=0,j=0,k;
    int * T=(int *)malloc(N*sizeof(int));
    while((i>= 0 && i < N) && (j>=0 && j<N)){
        damPut(tab,i,j);
        if(safeTest(tab,i,j)==0){
            T[j]=i;
            j++;
            i=0;
        }
        else if(safeTest(tab,i,j)==1){
            damDelete(tab,i,j);
            if(i==N-1){
                j--;
                i=T[j];
                damDelete(tab,i,j);  // T[j]+1
            }
            if(i==N-1){
                j--;
                i=T[j];
                damDelete(tab,i,j);
            }
            i++;

        }
        boardShow(tab);
    }
}
int main(){
    int ** board=createBoard(N,N);
        solver(board,N,N);
    return 0;
}