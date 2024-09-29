/*Svolgere l'esercizio "Esempio: file di Record" sul file Gestione File in Moodle (ultime 2 slide): dopo aver caricato tutte le persone, implementare le seguenti 2 procedure/funzioni:
- cercaPiuAnziano: è una procedura che, dati come parametri l'array di persone e il numero di persone, stampa a video i dati della persona più anziana
- calcolaMaggiorenni: è una funzione che, dati come parametri l'array di persone e il numero di persone, restituisce il numero di persone maggiorenni.

Nel main richiamare le suddette procedure/funzioni per testarle.

POICHE' L'ORARIO E' STATO AGGIORNATO NELLA NOTTE FRA VENERDì E SABATO, CHI NON RIESCE A SVOLGERE QUESTI COMPITI O UNA PARTE DI ESSI, LI SVOLGERA' PER MARTEDì 1 OTTOBRE
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nome[50];
    char cognome[50];
    int eta;
}persona;


void cercaPiuAnziano();
int calcolaMaggiorenni();

int main(){
    int scelta;
    persona persone;
    FILE *fp;
    int maggiorenni;


    while(1){
        printf("1:inserisci i dati delle persone, 2:ricerca della persona piu anziana, 3:lista di quante persone maggiorenni ci sono\n");
        scanf("%d",&scelta);
    if(scelta == 0){
        exit(0);
    }

    switch(scelta){
      case 1:
        fp=fopen("dati.bin","ab");
        if(fp == NULL){
            printf("file non trovato\n");
            return 1;
        }
        printf("Inserisci nome: ");
                fgets(persone.nome, sizeof(persone.nome), stdin);
                persone.nome[strcspn(persone.nome, "\n")] = 0; 

        printf("Inserisci cognome: ");
                fgets(persone.cognome, sizeof(persone.cognome), stdin);
                persone.cognome[strcspn(persone.cognome, "\n")] = 0; 

                printf("Inserisci età: ");
                scanf("%d", &persone.eta);
                getchar(); 

                fwrite(&persone, sizeof(persona), 1, fp);
                fclose(fp);
        break;
      case 2:
        cercaPiuAnziano();
        break;
      case 3:
        maggiorenni = calcolaMaggiorenni();
                printf("Il numero di persone maggiorenni è: %d\n", maggiorenni);

        break;
      default:
        printf("opzione non valida\n");
        break;
    }
}
return 0;

}
void cercaPiuAnziano() {
    FILE *fp = fopen("dati.bin", "rb");
    if (fp == NULL) {
        printf("Errore nell'apertura del file\n");
        return;
    }

    persona persone, piuAnziano;
    int trovato = 0;

    while (fread(&persone, sizeof(persona), 1, fp)) {
        if (!trovato || persone.eta > piuAnziano.eta) {
            piuAnziano = persone;
            trovato = 1;
        }
    }

    if (trovato) {
        printf("La persona più anziana è: %s %s con %d anni.\n", piuAnziano.nome, piuAnziano.cognome, piuAnziano.eta);
    } else {
        printf("Nessuna persona presente nel file.\n");
    }

    fclose(fp);
}
 


int calcolaMaggiorenni() {
    FILE *fp = fopen("dati.bin", "rb");
    if (fp == NULL) {
        printf("Errore nell'apertura del file\n");
        return 0;
    }

    persona persone;
    int conteggio = 0;

    while (fread(&persone, sizeof(persona), 1, fp)) {
        if (persone.eta >= 18) {
            conteggio++;
        }
    }

    fclose(fp);
    return conteggio;
}


