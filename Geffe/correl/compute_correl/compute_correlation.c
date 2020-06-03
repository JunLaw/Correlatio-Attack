#include <stdio.h>
#include <stdlib.h>

void chtobin(char ** argv,int *tab){
	for(int i = 0; i< 8; i++){
		if(argv[1][i] == '0'){
			tab[i] = 0;
		}else if(argv[1][i] == '1'){
			tab[i] = 1;
		}
		else{
			printf("erreur");
		}
	}
}

//calcul la correlation entre la fonction de filtrage et la sortie du LFSR
void correl(int *tab,int x[8],int n){
	double correl1 = 0;
	double correl0 = 0;
	for(int i = 0; i< 8; i++){
		if(tab[i] == x[i]){
			if(tab[i] == 0){correl0++;}
			else{correl1++;}
		}
	}
	printf("F = 0 => P(X%d = 0) = %f\n",n,correl0/4.0);
	printf("F = 1 => P(X%d = 1) = %f\n",n,correl1/4.0);
	printf("Taux de correlation total = %f\n\n",((correl0+correl1)/8.0) *100.0);
	
}

//calcul la correlation entre la sortie des LFSR et la fonction de filtrage
void main(int argc, int **argv){
	if(argc == 2){
		int tab[8] = {0};
		chtobin(argv,tab);
		for(int i = 0;i < 8;i++){
			printf("%d",tab[i]);
		}
		printf("\n");
	int	x0[8] = {0,1,0,1,0,1,0,1}; // registre x0
	int x1[8] = {0,0,1,1,0,0,1,1}; // registre x1
	int x2[8] = {0,0,0,0,1,1,1,1}; // registre x2
	
	correl(tab,x0,1);
	correl(tab,x1,2);
	correl(tab,x2,3);
	
	
	
	
}else{
	printf("pas assez d'argument");
	
}
}
