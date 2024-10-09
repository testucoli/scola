/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: silviasuriani
 *
 * Created on 3 ottobre 2024, 12.23
 */

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

int main(int argc, char** argv) {

    int scelta;

    do {
        printf("inserisci:\n\t1:inserire un nuovo studente\n\t2:inserire un nuovo voto\n\t3:stampa studenti\n\t0:per uscire");
        scanf("%d", &scelta);
        switch (scelta) {
            case 1://inserimento studente
                insertstudente();
                break;
            case 2://inserimento voto
                insertvoto();
                break;
            case 3://stampa studenti
                stampastudenti();
                break;
            case 0://uscita
                break;
            default:
                printf("\ncomando sbagliato\n");

        }
    } while (scelta != 0);


    return (EXIT_SUCCESS);
}

void insertstudente() {
    studente s;
    printf("\ninserisci il nome: ");
    scanf("%s", s.nome);
    printf("\ninserisci il cognome: ");
    scanf("%s", s.cognome);
    printf("\ninserisci la matricola: ");
    scanf("%d", &s.matricola);
    FILE *fp = fopen("studenti.bin", "ab");
    int k = fwrite(&s, sizeof (studente), 1, fp);
    fclose(fp);
    printf("\nstudenti inseriti: %d", k);
}

void insertvoto() {
    studente s;
    voto v;
    char nome[20];
    char cognome[20];
    printf("\ninserisci il nome: ");
    scanf("%s", nome);
    printf("\ninserisci il cognome: ");
    scanf("%s", cognome);
    printf("\ninserisci disciplina: ");
    scanf("%s", v.disciplina);
    printf("\ninserisci la valutazione: ");
    scanf("%d", &v.val);


    FILE *fp = fopen("studenti.bin", "rb");
    int trovato = 0;
    while (fread(&s, sizeof (studente), 1, fp) > 0 && trovato == 0) {
        if (strcmp(s.nome, nome) == 0 && strcmp(s.cognome, cognome) == 0)
            trovato = 1;
    }
    fclose(fp);

    printf("\n la matricola: %d\n", s.matricola);
    if (trovato == 1) {
        v.matricola = s.matricola;
        printf("\n setto la matricola  2\n");
        FILE *fp1 = fopen("voti.bin", "ab");
        if (fp1 == NULL) {

            printf("Errore apertura file");
            exit(0);
        }

        fwrite(&v, sizeof (voto), 1, fp1);
        fclose(fp1);

    } else {
        printf("\nlo studente %s %s non esiste\n", nome, cognome);
    }

}

void stampastudenti() {
    studente s;
    FILE *fp = fopen("studenti.bin", "rb");

    while (fread(&s, sizeof (studente), 1, fp) > 0) {
        printf("\n\t nome: %s\t cognome: %s \tmatricola: %d\n", s.nome, s.cognome, s.matricola);
    }
    fclose(fp);
}