/*Gli organizzatori di una gara di triathlon inseriscono tutti gli atleti iscritti alla competizione in un file binario memorizzando il numero di pettorale che è un numero progressivo, il nome, il cognome e la data di nascita.


I risultati delle tre diverse competizioni vengono anch'esse memorizzate in un file binario nel seguente modo:

numero_pettorale -  tempo (in secondi) -  tipo di prova (N per il nuoto, C per la corsa, B per la bicicletta).



Creare ed implementare in linguaggio C un algoritmo  per la gestione delle seguenti operazioni necessarie agli organizzatori della competizione:

- iscrizione di un nuovo atleta nel file delle iscrizioni;

- inserimento, nel file dei risultati, del tempo di un atleta, dato il nome, il cognome e il tipo di prova (N, C, B);

- ricerca del tempo totale di una atleta, dato il nome e il cognome (tempo totale= somma delle 3 prove);

- dato un tempo e un tipo di prova (N, C, B), stampare il nome e il cognome di tutti gli atleti con un tempo minore/migliore di quello inserito

- stampare i tempi totali di tutti gli atleti*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LUNGHEZZA 100 
#define MAX_PART 100

typedef struct{
    char nome[MAX_LUNGHEZZA];
    char cognome[MAX_LUNGHEZZA];
    int pettorina;
    int dd,mm,yy;
}atleta;

typedef struct{
    int pettorina;
    float tempo;
    char tipoprova;
}risultato;


void inserimento();
void risultati();


int main(){
int scelta;

while(1){
    printf("bla bla\n");
    scanf("%d",&scelta);
    if (scelta==0){
        exit(0);
    }

    switch(scelta){

        case 1:
        inserimento();
        break;


        case 2:
        risultati();
        break;

        case 3:

        break;
    }
}


}


void inserimento(){
    FILE *fp;
    atleta atleti;
    printf("nome: \n");
    scanf("%s",atleti.nome);
    printf("cognome: \n");
    scanf("%s",atleti.cognome);
    printf("pettorina: \n");
    scanf("%d",&atleti.pettorina);
    printf("data di nascita (dd mm yy) ");
    scanf("%d %d %d",&atleti.dd,&atleti.mm,&atleti.yy);
    fp=fopen("atleti.bin","ab");
    if(fp==NULL){
        printf("errore \n");
        return;
    }

    fwrite(&atleti,sizeof(atleta),1,fp);

    fclose(fp);
}

void risultati(){
    atleta atleti;
    risultato risultati;
    FILE *fp;
    FILE *f;
    char nome[MAX_LUNGHEZZA];
    char cognome[MAX_LUNGHEZZA];
    int trovato=0;

    printf("inserisci il nome da cercare\n");
    scanf("%s",nome);
    printf("inserisci cognome\n");
    scanf("%s",cognome);
    printf("inserisci la pettorina \n");
    scanf("%d",&risultati.pettorina);
    printf("inserisci il tempo in secondi \n");
    scanf("%f", &risultati.tempo);
    printf("inserisci il tipo di prova \n");
    scanf("%c", &risultati.tipoprova);
    fp=fopen("atleti.bin","rb");
    while(fread(&atleti,sizeof(atleta),1,fp)){
    if(strcmp(atleti.nome,nome) == 0 && strcmp(atleti.cognome,cognome) == 0){
        trovato=1;
    }

    }
    fclose(fp);
    if(trovato==1){
        f=fopen("risultati.bin","ab");
        if(f==NULL){
            printf("impossibile aprire il file \n");
            return;
        }
        risultati.pettorina == atleti.pettorina;
        fwrite(&risultati,sizeof(risultato),1,f);
        fclose(f);

         }

}





