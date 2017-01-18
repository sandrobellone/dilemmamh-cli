    // dilemmamh.c - versione 0.03

    // Copyright 2015 2017 Sandro Bellone

    // This program is free software: you can redistribute it and/or modify
    // it under the terms of the GNU General Public License as published by
    // the Free Software Foundation, either version 3 of the License, or
    // (at your option) any later version.

    // This program is distributed in the hope that it will be useful,
    // but WITHOUT ANY WARRANTY; without even the implied warranty of
    // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    // GNU General Public License for more details.

    // You should have received a copy of the GNU General Public License
    // along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

void dmh(int nite, char t);
int scelta (int);
int terza_scelta(int,int);
int escludi_vera(int,int);
void guida();

int main(int argc, char *argv[]){
	int n=1000;	// numero di iterazioni
	char t='r';  // tipo di scelta
	srand((unsigned)time(NULL));      // sceglie il seme
	//guida();
	static char *optstring = "n:t:h";
	int indice;
	while ((indice=getopt(argc,argv,optstring))!=-1)
        switch(indice){
        case 'n' :
          //printf("l'opzione -n è stata riconosciuta ed ha il seguente parametro aggiuntivo: %s.\n",optarg);
          n=atoi(optarg);
          //printf("in intero: %d\n",n);
          break;
        case 't' :
          //printf("l'opzione -t è stata riconosciuta ed ha il seguente parametro aggiuntivo: %s.\n",optarg);
          t=optarg[0];
          break;
        case 'h' :
          guida();
          break;
        default :
          printf("opzione sconosciuta!\n");
    }
    printf("Numero iterazioni: %d\n",n);
    printf("Tipo di scelta: %c ",t);
    switch(t) {
        case 'r': printf("(scelta randomica)\n");break;
        case 's': printf("(scelta sempre accettata)\n");break;
        case 'm': printf("(scelta mai accettata)\n");break;
        case 'a': printf("(scelta accettata alternativamente)\n");break;
        default: printf("(tipo di scelta non prevista)\n"); return -1;}
    dmh(n,t);
	return 0;
}

void guida() {
	printf("Software di simulazione del dilemma di Monty Hall\n"
						"Sandro Bellone\nGennaio 2017\n\n"
						"Copyright 2015 2017 Sandro Bellone\n"
						"GNU General Public License vers. 3\n\n"
						"Utilizzo: dilemmamh-cli [-n <numero iterazioni>] [-t <tipo scelta>]\n"
						"Guida:    dilemmamh-cli -h\n"
						"Con <numero iterazioni>=1000 valore di default\n"
						"<tipo scelta>: r: scelta randomica (default)   s: accettata sempre\n"
						"               m: accettata mai                a: accettata in modo alternato\n");
}

void dmh(int nite, char t){
    int x, y, z, c, i;
    int numero_successi=0, numero_scambi=0, numero_successi_con_scambio=0,
        numero_successi_senza_scambio=0;
    for (i=0; i<nite; i++) {
        x=scelta(3);		// ok
        y=scelta(3);		// tentativo
        z=escludi_vera(x,y);
        if(t=='r') {
            if(scelta(2)) c=y;
            else c=terza_scelta(y,z);
        } else if(t=='s') c=y;
        else if (t=='m') c=terza_scelta(y,z);
        else if (t=='a') {
            if (i%2) c=y;
            else c=terza_scelta(y,z);
        }
        if (x==c) {
            numero_successi++;
            if(y!=c) {
                numero_successi_con_scambio++;
            } else numero_successi_senza_scambio++;
        }
        if (y!=c) numero_scambi++;
    }
    printf("Iterazioni: %d; scambi: %d; successi: %d,\n"
           "di cui con scambio: %d, senza scambio: %d\n",
           i, numero_scambi, numero_successi, numero_successi_con_scambio, numero_successi_senza_scambio);
}

int scelta(int i) {				// ritorna un numero intero casuale da 0 a i
	return (int)(rand()%i);
}

int terza_scelta(int x, int y) { // dati due numeri differenti da 1 a 3, ritorna il terzo
	if((x+y)==1) return 2;
	if((x+y)==2) return 1;
	return 0;
}

int escludi_vera(int x, int y) {			// sceglie un numero sbagliato
	int k;
	if (x==y) {
		k=scelta(2);
		if (x==0) return k+1;	// x==0; y==0;
		if (x==1) return k*2;	// x==1; y==1;
		else return k;			// x==2; y==2;
	}
	return terza_scelta(x,y);
}
