#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define min(a, b) (((a) < (b)) ? (a) : (b))


typedef struct {
int szamlalo;
int nevezo;
} tort;

void kiirtomb (tort ** inputtomb,int sorok,int oszlopok);
void teszt();
void kiirtort( tort input){printf("%2i/%2i\n",input.szamlalo,input.nevezo);} 

void tort_egyszerusites ( tort * tortinput){
	int i;
	int minimum = min(((int)(abs(tortinput->szamlalo))),((int)abs(tortinput->nevezo)));
	if (minimum == 0) {tortinput->nevezo == 1 ; return;}

	if(tortinput->nevezo % tortinput->szamlalo == 0 || tortinput->szamlalo % tortinput->nevezo == 0 ) 
	{tortinput->nevezo /= minimum;tortinput->szamlalo /= minimum;} else{
	for ( i = 2 ;
		i <= min(((int)(abs(tortinput->szamlalo))),((int)abs(tortinput->nevezo)));
		i++){
			if(( tortinput->nevezo%i == 0) && (tortinput->szamlalo %i ==0))
				{
					tortinput->nevezo /= i;tortinput->szamlalo /= i;
					i = 1;
				}
	}}
		if (tortinput->nevezo<0){
		tortinput->szamlalo *=-1;
		tortinput->nevezo *=-1;
	}
}

tort tort_szorzas(tort tort1, tort tort2){
	tort temp;
	temp.szamlalo = tort1.szamlalo * tort2.szamlalo;
	temp.nevezo = tort1.nevezo * tort2.nevezo;
	tort_egyszerusites(&temp);
	return temp;
}

tort tort_osztas(tort osztando, tort oszto){
	tort temp;
	temp.szamlalo = osztando.szamlalo*oszto.nevezo;
	temp.nevezo = osztando.nevezo*oszto.szamlalo;
	tort_egyszerusites(&temp);
	return temp;
}

tort tort_osszeadas(tort tort1, tort tort2){
	tort temp;
	temp.szamlalo = tort1.szamlalo*tort2.nevezo + tort2.szamlalo*tort1.nevezo;
	temp.nevezo = tort1.nevezo*tort2.nevezo;
	tort_egyszerusites(&temp);
	return temp;
}

tort tort_kivonas (tort kissebbitendo, tort kivonando){
	tort temp;
	temp.szamlalo = kissebbitendo.szamlalo*kivonando.nevezo - kivonando.szamlalo*kissebbitendo.nevezo;
	temp.nevezo = kissebbitendo.nevezo*kivonando.nevezo;
	tort_egyszerusites(&temp);
	return temp;
}

void elem_kinullaz(tort * kissebbitendo, tort * kivonando,int hanyadik, int hossz){
	tort temp = tort_osztas(kissebbitendo[hanyadik],kivonando[hanyadik]);
	int i;
	for(i = hanyadik ; i <hossz ; i++){
		kissebbitendo[i] = tort_kivonas(kissebbitendo[i], tort_szorzas(temp,kivonando[i]));
	}
}

void gauss_eliminacio (tort **input_gauss,int n){ // n a sorok száma
	int i,j;
	kiirtomb(input_gauss,n,n+1);
	for (i  = 0; i <n ; i++) // Felsõ háromszög mátrix 
	{
		for(j = i+1; j<n;j++){
			elem_kinullaz(input_gauss[j], input_gauss[i],i,n+1);
			kiirtomb(input_gauss,n,n+1);
		}
	}
	printf("Felsõ háromszög kész!\n");
	for (i  = n-1; i >=0 ; i--)// Átlós mátrix
	{
		for(j = i-1; j>=0;j--){
			elem_kinullaz(input_gauss[j], input_gauss[i],i,n+1);
			kiirtomb(input_gauss,n,n+1);
		}
	}
	printf("eredmeny elott\n");kiirtomb(input_gauss,n,n+1);
	printf("\n");
	for ( i = 0; i<n ; i++){ // Eredmények.
	input_gauss[i][n] = tort_osztas(input_gauss[i][n],input_gauss[i][i]);
	input_gauss[i][i] = tort_osztas(input_gauss[i][i],input_gauss[i][i]);
	}
	kiirtomb(input_gauss,n,n+1);
	printf("Kesz!");
}

void kiirtomb (tort ** inputtomb,int sorok,int oszlopok){
	int i,j;
	for ( i = 0; i < sorok;i++)
	{
		for (j = 0; j<oszlopok; j++){
				printf("%3i/%3i  ", inputtomb[i][j].szamlalo,inputtomb[i][j].nevezo);}
	printf("\n");}printf("\n\n");
}

void main (){

	int sorok = 5;
	int oszlopok = 6;
	int i,j;
	tort temp;
	tort **tomb;
	srand ( time(NULL) );
	tomb =malloc(sorok * sizeof(tort *));
	
	if(tomb == NULL)
		{
		printf("Szopo :(");
		}
	for(i = 0; i < sorok; i++)
		{
		tomb[i] = malloc(oszlopok * sizeof(tort));
		if(tomb[i] == NULL)
			{
			printf("Szopo :(");
			}
		}// Memória allokálás
	for(i = 0; i <sorok;i++){for (j = 0;j <oszlopok;j++){
		temp.szamlalo =rand()%10;temp.nevezo = 1;
		tomb[i][j] = temp;
		}
	} //Random feltöltés
	gauss_eliminacio(tomb,sorok);
	//teszt();
	getchar();
}

void teszt(){
tort tort1,tort2,eredmeny;
tort1.szamlalo= 1000;
tort1.nevezo = -500;
kiirtort(tort1);
printf("\n");
tort_egyszerusites(&tort1);
kiirtort(tort1);

}