#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <chrono>
#include <thread>

using namespace std;
using namespace chrono;

//221 170 39-2
//aaa bbb cc-c

//P=170 * 392 = 66,640
//encontrar a soma dos 221 imediatamente anteriores a  P = 66,640

/* Convencao: EhPrimo = 1 se o numero dado 'e primo */
/*  EhPrimo = 0 se o numero dado nao 'e primo       */

long long int soma =0;			//Vetor para Soma
int primos[222];				//Vetor para salvar os 221 numeros primos
int idc = 0;					//Indice para controlar vetor de primos

//Função para encontrar primos de um intervalo dado um Inicio e um Fim
void TestaPrimo4(int n, int f) {	
	//Loop Inicio ate Fim
	while(n>f){
		int EhPrimo, 
		    d=3;
		if (n <= 1 || (n != 2 && n % 2 == 0 ) || (n % 6 != 1 && n % 6 != 5))
		    EhPrimo = 0;    
		else
		    EhPrimo = 1;
		while (EhPrimo  && d <= n / 2) {
		    if (n % d == 0)
		        EhPrimo = 0;
		    d = d + 2;
		    }
		
		//If para salvar e somar numeros primos encontrados
		if(EhPrimo != 0){
			//Caso seja encontrado, e o vetor ainda nao estiver cheio
			if(idc < 221){	
				soma = soma + n;
				primos[idc]= n;
				idc++;
			}
			//Else para zerar N e parar de procurar mais primos, caso o vetor esteja cheio
			else if(idc == 221){
				n=0;
			}
		}	
		//Decrementa N para proxima iteracao
		n--;
		
	}
	
}


int main(){


	int p = 66640;
	
	auto start = std::chrono::steady_clock::now();							//Start do Clock	
	
	//Com thread
	std::thread half1(TestaPrimo4,p,(p/2));									//Chama primeira metade em uma thread
	half1.join();
	std::thread half2(TestaPrimo4,((p/2)-1),0);								//Chama segunda metade em outra tthread
	half2.join();
	
	//Sem Thread
	//TestaPrimo4(p,0);														//Função testa primo completa 66640 - 0
	
	auto end = std::chrono::steady_clock::now();							//End do Clock
	milliseconds tempoexec = duration_cast<milliseconds>(end - start);		//Calcula o tempo de execucao em milissegundos (end - start)
	
	//For para printar os numeros primos armazenados no vetor
	for(int i = 0; i<221;i++){
		std::cout <<" Primo:"<<i+1<<"  valor:"<<primos[i]<<endl;
	}
	printf(" [-] ------------------------- [-]\n ",soma);
	printf(" -Valor da soma: %lld\n ",soma);								//Print soma total
	std::cout <<" -Tempo de execucao da soma: " << tempoexec.count() << " ms\n";		//Print tempo de execucao
	
	
	//Ponteiro para arquivo abero tem modo write
	FILE* sc = fopen("log.txt", "w");
	
	//Prints para salvar em txt a mesma coisa impressa no terminal
	for(int i = 0; i<221;i++){
		fprintf(sc,"Primo %d			Valor: %d \n",i+1,primos[i]);
	}
	fprintf(sc," [-] ------------------------- [-]\n ");
	fprintf(sc," -Valor da soma: %lld\n ",soma);
	int coutt = tempoexec.count();
	fprintf(sc," -Tempo de execucao da soma: %d  ms",coutt);
	fclose(sc);
	
	
	std::cout <<"\n ----------->SALVO EM log.txt na mesma pasta deste codigo fonte <-------------"<<endl;
	
	
	
	return 0;
}




