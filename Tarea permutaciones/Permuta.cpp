
//#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <strstream>
#include <stdlib.h> 
#include <time.h>
using namespace std;

static int cont = 0;
static int *apMemoria;
static int *apAquiVoy;
static int *apMemReinas;
static int *apAquiVoyReinas;
static int cuentaR = 0;

void swap(int *a, int *b){
	int aux = *b;
	*b = *a;
	*a = aux;
}

void imprime(int arr[], int n){
	for(int i = 0; i <= n; i++){
		cout << arr[i];
	}
}

void guarda (int arr[], int n){
	// cout << "Numero a guardar: ";
	// imprime(arr, n);
	// cout << endl;
	
	for(int i = 0; i <= n ; i++){
		*apAquiVoy = arr[i];				
		apAquiVoy ++;
		
	 }
}
bool solucionValida(int aPosible[], int aGuardadas[] int n, int m){  //m es tamaño de arreglo de reinas guardadas
	bool resp = false;
	if(m==0){
		guardaReina(arr,n-1);
		resp = true;
	}else{
		
	}
	return resp;
}

void guardaReina(int arr[], int n){
	for(int i = 0; i<=n; i++){
		*apAquiVoyReinas = arr[i];				
		apAquiVoyReinas ++;
	}
}

void reinasBuenas(int arr[], int n){
	//cout << "Empieza " << " n: " << n<<endl;
	bool sigo = true;
	int i = 0, j;
	while(sigo && i < n-1){
		j=(i+1);
		while(sigo && j<n){
			if(abs(j-i) == abs(arr[j]-arr[i])){
				sigo = false;
			}
			j++;				
		}
		i++;
	}
	if(sigo){
		//cout << "GUARDO!"<< endl;
		imprime(arr,n-1);
		//cout << endl;
		cuentaR++;
		//guardaReina(arr,n-1);
	}
}

void permuta(int *arr, int i, int n){
	if(i==n){
		guarda(arr, n);
		reinasBuenas(arr,n+1);
		cont ++;
	}
	else{
		for(int j = i; j <= n; j++){
			swap(*(arr + i), *(arr + j));
			permuta(arr, i + 1, n);
			swap(*(arr + i), *(arr + j));
		}
	}
}

void saca (int arr[], int n, int fac){
	for(int i = 0; i < fac; i ++){
		for(int j = 0; j < n; j++){
			cout << *apMemoria;
			apMemoria++;
		}
		cout << endl;
	}
}

int factorial(int n){
	int resp = 1;
	for(int i = 2; i <= n; i++){
		resp *= i;
	}
	return resp;
}



#define N 4
int main(int argc, char *argv[])
{	
	
	int n;
	int permutame[N];
	char propio,reina;

	if(argc > 1){
		n = atoi(argv[1]);
		
	}else{
		n = 3;
	}

	cout << "Numero de elementos a permutar: " << n << endl;

	int fact = factorial(n);

	cout << n << " factorial es: " << fact << endl;
	apAquiVoy = (int *) malloc(sizeof(int) * (fact*n));
	apMemoria=apAquiVoy;
	apAquiVoyReinas = (int *) malloc(sizeof(int) * (10*n));
	apMemReinas=apAquiVoyReinas;

	cout << "Hacer propio arreglo con " << n << " numeros? (s/n)" << endl;
	cin >> propio;

	if(propio == 'n'){
		for(int i = 0; i < n; i++){
			permutame[i] = i;
		}
	}else{
		for(int i = 0; i < n; i++){
			cout << "Dato " << i << ": ";
			cin >> permutame[i];
			cout << endl;
		}
		cout << "Arreglo a permutar: "; 
		imprime(permutame, n-1);
		cout << endl;
	}
	permuta(permutame,0,n-1);
	cout << "Numero de permutaciones: " << cont << endl;
	saca(permutame, n, fact);
	cout << endl;
	
	cout << "Reinas guardadas: " << cuentaR << endl;
	

	cout << endl;
	
	cout << "Fin :)";
	
	// int permutame[5]={0,1,2,3,4};
	// int fact = factorial(5);
	// cout << "5 factorial es: " << fact << endl;
	// apAquiVoy = (int *) malloc(sizeof(int) * (120*5));
	// apMemoria=apAquiVoy;
	// permuta(permutame,0,4);
	

	return 0;
}

