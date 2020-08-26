#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <chrono>
#include <thread>

using namespace std;
using namespace chrono;

//22117039-2
//aaabbbcc-c

//P=170 * 392 = 66,640
//encontrar a soma dos 221 imediatamente anteriores a  P = 66,640

/* Convencao: EhPrimo = 1 se o numero dado 'e primo */
/*  EhPrimo = 0 se o numero dado nao 'e primo       */

long long int soma =0;
int primos[222];
int idc = 0;

void TestaPrimo4(int n, int f) {	

	while(n>f){
		
		int EhPrimo, 
		    d=3;
		if (n <= 1 || (n != 2 && n % 6 == 1 && n % 6 == 5))
		    EhPrimo = 0;    
		else
		    EhPrimo = 1;
		while (EhPrimo  && d <= n / 2) {
		    if (n % d == 0)
		        EhPrimo = 0;
		    d = d + 2;
		    }
		
		if(EhPrimo != 0){
		//	std::cout<<"\n testando numero"<<n<<endl;
			if(idc < 221){	
				soma = soma + n;
				primos[idc]= n;
				idc++;
			}
			//else if(idc == 221){
			//	n=0;
			//}
		}	
		n--;
		
	}
	
}


int main(){


	int p = 66640;
	auto start = std::chrono::steady_clock::now();		
	
	
	//Com thread
	std::thread half1(TestaPrimo4,p,(p/2));
	half1.join();
	std::thread half2(TestaPrimo4,((p/2)-1),0);
	half2.join();
	
	
	//Sem Thread
	//TestaPrimo4(p,0);
	
	auto end = std::chrono::steady_clock::now();
	milliseconds tempoexec = duration_cast<milliseconds>(end - start);
	for(int i = 0; i<221;i++){
		std::cout <<" Primo:"<<i+1<<"  valor:"<<primos[i]<<endl;
	}
	printf(" [-] ------------------------- [-]\n ",soma);
	printf(" -Valor da soma: %lld\n ",soma);
	std::cout <<" -Tempo de execucao da soma: " << tempoexec.count() << " ms\n";
	
	
	
	FILE* sc = fopen("log.txt", "w");
			for(int i = 0; i<221;i++){
		fprintf(sc,"Primo %d			Valor: %d \n",i+1,primos[i]);
	}
	fprintf(sc," [-] ------------------------- [-]\n ");
	fprintf(sc," -Valor da soma: %lld\n ",soma);
	int coutt = tempoexec.count();
	fprintf(sc," -Tempo de execucao da soma: %d  ms",coutt);
	fclose(sc);
	
	std::cout <<"\n ------------>SALVO EM log.txt na mesma pasta deste codigo fonte <-----------------"<<endl;
	
	
	
	return 0;
}




