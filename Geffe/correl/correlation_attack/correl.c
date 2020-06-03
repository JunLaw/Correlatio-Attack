#include <stdio.h>
#include <stdlib.h>

/*Decalage de bits et rajoute le nouvelle retroaction a la fin du LFSR*/
void pop_and_push(int *tab,int n,int new_value){
	int temp1=0;
	int temp2=new_value;
	int temp3 = tab[0];
	
	for(int i = n-1; i >= 0  ; i = i-2){
		temp1 = tab[i];
		tab[i] = temp2;
		temp2 = tab[i-1];
		tab[i-1] = temp1;
		
	}
	
	
}

/*fait tourner le lfsr avec les coefficient de retroaction assignés*/
void geffe(int* L1,int num_lfsr){
	int new_L1 = 0;	
			
			//calculer le nouveau s(i+m)//
			switch(num_lfsr){
				case 0:
					 new_L1 = L1[1] ^ L1[4] ^ L1[7] ^ L1[0]; 
					break;
				case 1:
					 new_L1 = L1[1] ^ L1[7] ^ L1[11] ^ L1[0]; 
					break;
				case 2 :
					 new_L1 = L1[2] ^ L1[3] ^ L1[5] ^ L1[0]; 
					break;
					default: break;
				}
			/////////////////////////
		
			//decaler et rajouter la nouvelle valeur dans le tableau//
		 pop_and_push(L1,16,new_L1);
		 /////////////////////////////////////		
	
}

/*Additionneur à un bit sur une suite de n bits*/
void additionneur(int *tab,int n){
	int i = 0;
	while(i < n){
		if( (tab[i] = ((tab[i]+1) % 2)) == 0){
			i++;
		}
		else{
			i = n;
		}	
	}	
}

//copie le tab1 dans le tab2
void copy(int *tab1,int *tab2,int n){
	for(int i = 0; i< n ; i++){
		tab2[i] = tab1[i];
	}
	
}

//calcul la correlation entre une fonction de filtrage et le lfsr
double compute_correl(int *tab1,int *tab2,int n){
	double correl = 0;
	for(int i = 0; i< n; i++){
		if(tab1[i] == tab2[i]){
			correl++;
		}
	}
	
	return (correl/8.0) * 100;
}

//recherche la bonne initialisation entre la suite chiffrante et le lfsr selon le taux de correlation de chaque lfsr
void search_init(int *f,int *x0,int stop,int n){
	int tmp[16] = {0};
	int best_rate_lfsr[16] = {0};
	double correl_max = 0;
	double correl = 0;
	int i =0;
	do{
		correl = 0;
		copy(x0,tmp,16);
		i++;
		
	for(int i = 0; i< 256; i++)
	{
		//printf("%d vs %d \n",f[i],tmp[i%8]);
		if(f[i] == tmp[i%16])
		{
			correl++;
		}	
		geffe(tmp,n);
	}
	
	switch(n)
	{
		case 0 :
		if( (correl/256.0) < 0.50){
			//printf("\n0)NOMBRE DE COINCIDENCE = %f nombre d'initialisation essayé = %d\n",correl,i);
			if(correl > correl_max){
				copy(x0,best_rate_lfsr,16);
				correl_max = correl;
			}
		additionneur(x0,16);
		}
		else{
			printf("0)taux de correlation = %f \n",correl/256.0);
		stop = 0;
		}
		break;
		case 1 :
		if( (correl/256.0) < 0.25 || (correl/256.0) > 0.30){
			//printf("\n1)NOMBRE DE COINCIDENCE = %f nombre d'initialisation essayé = %d\n",correl,i);
			if(correl > correl_max){
				copy(x0,best_rate_lfsr,16);
				correl_max = correl;
			}
		additionneur(x0,16);
		}
		else{
			printf("1)taux de correlation = %f \n",correl/256.0);
		stop = 0;
		}
		break;
		case 2:
		//printf("\n2)NOMBRE DE COINCIDENCE = %f nombre d'initialisation essayé = %d\n",correl,i);
		if(correl > correl_max){
				copy(x0,best_rate_lfsr,16);
				correl_max = correl;

			}
		if( (correl/256.0) < 0.75 ){
			
		additionneur(x0,16);
		}
		else{
			printf("2)taux de correlation = %f \n",correl/256.0);
		stop = 0;
		}
		break;
		default :
		stop = 0;
		break;
		
		
	}
	if(i >= 65535){
			stop = 0;
			copy(best_rate_lfsr,x0,16);
			printf("correl_max = %f\n",correl_max);
		}

	
}while(stop);
	
}

//compare deux tableau si vrai les deux tableaux sont identique
int compare(int *tab1,int *tab2){
	int z=0;
	for(int i = 0; i< 16; i ++){
		if(tab1[i] == tab2[i]){
			z++;
		}
			 
	}
	if(z == 16){
		return 1;
	}else{
		return 0;
	}
}

//Assigne les input du programme a un tableau de bit
void cast_input(int *S,char **argv,int n){
	for(int i = 0; i < n; i++){
		if(argv[1][i] == '1'){
			S[i] = 1;
		}else if(argv[1][i] == '0'){
			S[i] = 0;
		}else{
			printf("erreur ce ne sont pas des bits");
			exit;
		}
		
	}
}

//fonction non utilisé// 
void cast_filter_to_attack(int *f,int *x0,int *x1,int *x2){
	int sum = 0;
	int tourne = 0;
	int tab[16] = {0};
	for(int x = 0 ; x < 65535; x++)
	{
		tourne ++;
		for(int i = 0; i < 16;i++) //initialise la suite chiffrante à tester
		{
			sum = x0[i] + (2*x1[i]) + (4*x2[i]); 
			tab[i] = f[sum];
		}
		if(compare(tab,f) == 1)
		{
			x = 255;
			printf("COMBINAISON TROUVÉ\n");
			copy(tab,x1,16);
			
		}else
		{
			additionneur(x1,16);
		}
	}
	printf("%d fois\n",tourne);
}


int main(int argc,char ** argv){
	//en entrée on a S une suite chiffrante de 128 bits
	//printf("%s",argv[1]);
	int S[256] = {0};
	cast_input(S,argv,256);
	int stop = 1;
	int f[8] = {1,0,0,0,1,1,1,0}; // fonction de filtrage
	int	x0[16] = {0}; // registre x0
	int x1[16] = {0}; // registre x1
	int x2[16] = {0}; // registre x2
	int tmp[16] = {0};
	// On calcul le taux de correlation de x0
	
	search_init(S,x0,stop,0);
	search_init(S,x2,stop,2);
	search_init(S,x1,stop,1);
	
	
	for(int i = 0; i < 3;i++)
	{
	printf("LFSR %d : ",i);
	for(int j = 0; j<16; j++)
	{
		switch(i)
		{
			case 0:
			printf("[%d]",x0[j]);
			break;
			case 1:
			printf("[%d]",x1[j]);
			break;
			case 2:
			printf("[%d]",x2[j]);
			break;
		}
	}
	printf("\n");
}
	printf("\n");
	
		
}
