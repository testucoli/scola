#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    persona p;
    FILE *fp;
    FILE *f;

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
                    visualizza_persona(p);
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
                    visualizza_persona(p);
                }
                fclose(f);
                break;

            case 3:
                printf("Inserisci nome: ");
                scanf("%s", p.nome);

                printf("Inserisci cognome: ");
                scanf("%s", p.cognome);

                printf("Inserisci matricola: ");
                scanf("%d", &p.matricola);

                printf("Inserisci telefono: ");
                scanf("%d", &p.telefono);

                printf("Inserisci sesso (m/f): ");
                scanf(" %c", &p.sesso);  

                if (p.sesso == 'm') {
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
                }
                break;

            default:
                printf("Opzione non valida\n");
                break;
        }
    }

    return 0;
}
