#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int matricola;
    char nome[20];
    char cognome[20];
} studente;

typedef struct {
    int matricola;
    char disciplina[20];
    int val;
} voto;

void insertstudente();
void insertvoto();
void stampastudenti();
void calcolamedia();

int main(int argc, char** argv) {

    int scelta;

    do {
        printf("\nInserisci:\n\t1: Inserire un nuovo studente\n\t2: Inserire un nuovo voto\n\t3: Stampa studenti\n\t4: Calcola media voti e visualizza voti\n\t0: Per uscire\n");
        scanf("%d", &scelta);
        switch (scelta) {
            case 1:
                insertstudente();
                break;
            case 2:
                insertvoto();
                break;
            case 3:
                stampastudenti();
                break;
            case 4:
                calcolamedia();
                break;
            case 0:
                break;
            default:
                printf("\nComando sbagliato\n");
        }
    } while (scelta != 0);

    return 0;
}

void insertstudente() {
    studente s;
    printf("\nInserisci il nome: ");
    scanf("%s", s.nome);  
    printf("Inserisci il cognome: ");
    scanf("%s", s.cognome);  
    printf("Inserisci la matricola: ");
    scanf("%d", &s.matricola);

    FILE *fp = fopen("studenti.bin", "ab");
    if (fp == NULL) {
        printf("\nErrore nell'apertura del file studenti.bin\n");
        return;
    }

    int k = fwrite(&s, sizeof(studente), 1, fp);
    fclose(fp);
    
    printf("\nStudente inserito: %d\n", k);
}

void insertvoto() {
    studente s;
    voto v;
    char nome[20];
    char cognome[20];
    
    printf("\nInserisci il nome: ");
    scanf("%s", nome);  
    printf("Inserisci il cognome: ");
    scanf("%s", cognome); 
    printf("Inserisci la disciplina: ");
    scanf("%s", v.disciplina); 
    printf("Inserisci la valutazione: ");
    scanf("%d", &v.val);

    FILE *fp = fopen("studenti.bin", "rb");
    if (fp == NULL) {
        printf("\nErrore nell'apertura del file studenti.bin\n");
        return;
    }

    int trovato = 0;
    while (fread(&s, sizeof(studente), 1, fp) > 0 && trovato == 0) {
        if (strcmp(s.nome, nome) == 0 && strcmp(s.cognome, cognome) == 0) {
            trovato = 1;
        }
    }
    fclose(fp);

    if (trovato == 1) {
        v.matricola = s.matricola;

        FILE *fp1 = fopen("voti.bin", "ab");
        if (fp1 == NULL) {
            printf("\nErrore nell'apertura del file voti.bin\n");
            return;
        }

        fwrite(&v, sizeof(voto), 1, fp1);
        fclose(fp1);

        printf("\nVoto inserito per lo studente con matricola %d\n", s.matricola);
    } else {
        printf("\nLo studente %s %s non esiste\n", nome, cognome);
    }
}

void stampastudenti() {
    studente s;
    FILE *fp = fopen("studenti.bin", "rb");
    if (fp == NULL) {
        printf("\nErrore nell'apertura del file studenti.bin\n");
        return;
    }

    printf("\nLista degli studenti:\n");
    while (fread(&s, sizeof(studente), 1, fp) > 0) {
        printf("\tNome: %s\tCognome: %s\tMatricola: %d\n", s.nome, s.cognome, s.matricola);
    }
    fclose(fp);
}


void calcolamedia() {
    studente s;
    voto v;
    
    FILE *fp = fopen("studenti.bin", "rb");
    if (fp == NULL) {
        printf("\nErrore nell'apertura del file studenti.bin\n");
        return;
    }

    FILE *fp_voti = fopen("voti.bin", "rb");
    if (fp_voti == NULL) {
        printf("\nErrore nell'apertura del file voti.bin\n");
        fclose(fp);  
        return;
    }

    printf("\nMedia e voti per ogni studente:\n");
    
   
    while (fread(&s, sizeof(studente), 1, fp) > 0) {
        int somma_voti = 0;
        int numero_voti = 0;

        
        rewind(fp_voti);
        
        printf("\nStudente: %s %s (Matricola: %d)\n", s.nome, s.cognome, s.matricola);
        printf("Voti:\n");

       
        while (fread(&v, sizeof(voto), 1, fp_voti) > 0) {
            if (v.matricola == s.matricola) {
                printf("\tDisciplina: %s\tValutazione: %d\n", v.disciplina, v.val);
                somma_voti += v.val;
                numero_voti++;
            }
        }

        if (numero_voti > 0) {
            float media = (float) somma_voti / numero_voti;
            printf("Media voti: %.2f\n", media);
        } else {
            printf("Nessun voto disponibile\n");
        }
    }

    fclose(fp);
    fclose(fp_voti);
}