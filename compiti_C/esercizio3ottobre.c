#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PERSONE 1000

typedef struct {
    char nome[50];
    char cognome[50];
    int telefono;
    int matricola;
    char sesso;
} persona;

void visualizza_persona(persona p) {
    printf("Nome: %s\n", p.nome);
    printf("Cognome: %s\n", p.cognome);
    printf("Telefono: %d\n", p.telefono);
    printf("Matricola: %d\n", p.matricola);
    printf("Sesso: %c\n", p.sesso);
}

int main() {
    int scelta;
    persona p[MAX_PERSONE];
    FILE *fp;
    FILE *f;
    int n=0;

    while(1) {
        printf("1: visualizza dipendenti maschi, 2: visualizza dipendenti femmine, 3: aggiungi persone, 0: esci\n");
        scanf("%d", &scelta);

        if (scelta == 0) {
            exit(0);
        }

        switch(scelta) {
            case 1:
                fp = fopen("maschi.bin", "rb");
                if (fp == NULL) {
                    printf("File maschi non trovato\n");
                    break;
                }
                while (fread(&p, sizeof(persona), 1, fp)) {
                    visualizza_persona(p[n]);
                }
                fclose(fp);
                break;

            case 2:
                f = fopen("femmine.bin", "rb");
                if (f == NULL) {
                    printf("File femmine non trovato\n");
                    break;
                }
                while (fread(&p, sizeof(persona), 1, f)) {
                    visualizza_persona(p[n]);
                }
                fclose(f);
                break;

            case 3:
            if(n>=MAX_PERSONE){
             printf("raggiunto il limite massimo di persone\n");
             break;
            }
                printf("Inserisci nome: ");
                scanf("%s", p[n].nome);

                printf("Inserisci cognome: ");
                scanf("%s", p[n].cognome);

                printf("Inserisci matricola: ");
                scanf("%d", &p[n].matricola);

                printf("Inserisci telefono: ");
                scanf("%d", &p[n].telefono);

                printf("Inserisci sesso (m/f): ");
                scanf(" %c", &p[n].sesso);  

                if(p[n].sesso!='m' && p[n].sesso!='f'){
                    printf("sesso non valido\n");

                }else{
                    n++;
                }
                f = fopen("femmine.bin", "ab");
                fp = fopen("maschi.bin", "ab");
                if (fp == NULL || f==  NULL) {
                    printf("File non trovati\n");
                    return 0;
                }
                for(int i=0; i<n;i++){
                    if(p[i].sesso=='m'){
                        fwrite(&p[i],sizeof(persona),1,fp);
                        printf("aggiunto al file dei maschi\n");
                    }else if(p[i].sesso=='f'){
                        fwrite(&p[i],sizeof(persona),1,f);
                        printf("aggiunto al file delle femmine\n");
                    }
                }
                fclose(fp);
                fclose(f);
                 break;
                /*if (p.sesso == 'm') {
                    fp = fopen("maschi.bin", "ab");
                    if (fp == NULL) {
                        printf("Errore nell'apertura del file maschi.bin\n");
                        break;
                    }
                    fwrite(&p, sizeof(persona), 1, fp);
                    fclose(fp);
                } else if (p.sesso == 'f') {
                    f = fopen("femmine.bin", "ab");
                    if (f == NULL) {
                        printf("Errore nell'apertura del file femmine.bin\n");
                        break;
                    }
                    fwrite(&p, sizeof(persona), 1, f);
                    fclose(f);
                } else {
                    printf("Sesso non valido\n");
                }*/
               

            default:
                printf("Opzione non valida\n");
                break;
        }
    }

    return 0;
}
