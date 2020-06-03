#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

void main(){
	srand(time(NULL));
	 FILE* fichier = NULL;
    fichier = fopen("rand.txt", "r+");
	int j = 0;

	for(int i = 0 ; i < 256; i++){
		if(fichier != NULL){
			j = rand()%2;
		 fprintf(fichier,"%d" ,j);
		 printf("%d",j);
	 }
	}
	fclose(fichier);
	
}
