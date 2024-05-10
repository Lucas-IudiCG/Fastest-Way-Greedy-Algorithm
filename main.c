#include <stdio.h>
#include <stdlib.h>

int** criamapa(int x){
  int **mapa = (int **)malloc(x * sizeof(int*));
  for(int i = 0; i < x; i++) {
    mapa[i] = (int *)malloc(x * sizeof(int));
    for(int j = 0; j < x; j++){
      mapa[i][j]=100;
    }
  }
  return mapa;
}
void printmapa(int **mapa, int x){
    printf("\n   |");
    for(int i = 0; i < x; i++){
         printf("  %d  |",i+1);
    }
    for(int i = 0; i < x; i++){
        printf("\n %d |",i+1);
        for(int j = 0; j < x; j++){
            printf(" %03d |",mapa[i][j]);
        }
    }
  printf("\n");
}

int **leitura(int* esqfogo, int* totalesquinas){
  FILE  *textfile;
  char  *text;
  int inicio, fim, tempo;
  textfile = fopen("bombeiro.txt", "r");
  fscanf(textfile, "%d", esqfogo);
  fscanf(textfile, "%d", totalesquinas);
  int **mapa = criamapa(*totalesquinas);
  while(fscanf(textfile, "%d\t%d\t%d", &inicio, &fim, &tempo)){
    if (inicio == 0) break;
    mapa[inicio-1][fim-1] = tempo;
  }
  fclose(textfile);
  return mapa;
}

int caminhos(int **mapa,int destino,int totalesquinas){
  int caminho=0;
  int index;
  int soma=0;
  while(destino!=caminho){
      int menor=100;
      for(int i=0;i<totalesquinas;i++){
          if(mapa[caminho][i]<menor){
              menor=mapa[caminho][i];
              index=i;
          }
      }
      printf("%d ",caminho+1);
      soma=soma+mapa[caminho][index];
      caminho=index;
          
  }
  printf("%d",destino+1);
  return soma;
}


int main() {
  int esqfogo, totalesquinas;
  int **mapa = leitura(&esqfogo, &totalesquinas);
  printmapa(mapa, totalesquinas);
  printf("\n\n");
  printf("rota até a esquina #%d: ",esqfogo);
  printf("\ntempo calculado para rota = %d min.\n\n",caminhos(mapa,esqfogo-1,totalesquinas));
  for(int i = 0; i < totalesquinas; i++){
    free(mapa[i]);
  }
  free(mapa);
  return 0;
}