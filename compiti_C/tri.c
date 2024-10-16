#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LUNGHEZZA 100 
#define MAX_PART 100

typedef struct{
    char nome[MAX_LUNGHEZZA];
    char cognome[MAX_LUNGHEZZA];
    int pettorina;
    int dd,mm,yy; // data di nascita
} atleta;

typedef struct {
    int pettorina;
    char tipo_prova; // 'N', 'C', 'B'
    int tempo; // tempo in secondi
} risultato;

void inserimento();
void inserisci_risultato();
void tempo_totale_atleta();
void ricerca_tempi_minori();
void stampa_tempi_totali();

int main(){
    int scelta;

    while(1){
        printf("\n1. Iscrivi un nuovo atleta\n");
        printf("2. Inserisci risultato di un atleta\n");
        printf("3. Calcola tempo totale di un atleta\n");
        printf("4. Ricerca atleti con tempo minore\n");
        printf("5. Stampa tempi totali di tutti gli atleti\n");
        printf("0. Esci\n");
        scanf("%d", &scelta);

        switch(scelta) {
            case 1:
                inserimento();
                break;
            case 2:
                inserisci_risultato();
                break;
            case 3:
                tempo_totale_atleta();
                break;
            case 4:
                ricerca_tempi_minori();
                break;
            case 5:
                stampa_tempi_totali();
                break;
            case 0:
                exit(0);
            default:
                printf("Scelta non valida\n");
        }
    }
}

void inserimento() {
    FILE *fp;
    atleta atleti;

    printf("Nome: ");
    scanf("%s", atleti.nome);
    printf("Cognome: ");
    scanf("%s", atleti.cognome);
    printf("Pettorina: ");
    scanf("%d", &atleti.pettorina);
    printf("Data di nascita (gg mm aaaa): ");
    scanf("%d %d %d", &atleti.dd, &atleti.mm, &atleti.yy);

    fp = fopen("atleti.bin", "ab");
    if (fp == NULL) {
        printf("Errore nell'aprire il file\n");
        return;
    }

    fwrite(&atleti, sizeof(atleta), 1, fp);
    fclose(fp);
    printf("Atleta iscritto correttamente!\n");
}

void inserisci_risultato() {
    FILE *fp;
    risultato res;
    atleta atleti;
    int pettorina;
    char tipo_prova;
    
    printf("Numero di pettorina: ");
    scanf("%d", &pettorina);
    
    printf("Tipo di prova (N: Nuoto, C: Corsa, B: Bicicletta): ");
    scanf(" %c", &tipo_prova);
    
    printf("Tempo (in secondi): ");
    scanf("%d", &res.tempo);
    
    res.pettorina = pettorina;
    res.tipo_prova = tipo_prova;
    
    fp = fopen("risultati.bin", "ab");
    if (fp == NULL) {
        printf("Errore nell'aprire il file\n");
        return;
    }
    
    fwrite(&res, sizeof(risultato), 1, fp);
    fclose(fp);
    printf("Risultato inserito correttamente!\n");
}

void tempo_totale_atleta() {
    FILE *fp;
    risultato res;
    atleta atleti;
    char nome[MAX_LUNGHEZZA], cognome[MAX_LUNGHEZZA];
    int pettorina, tempo_totale = 0;

    printf("Nome atleta: ");
    scanf("%s", nome);
    printf("Cognome atleta: ");
    scanf("%s", cognome);

    // Cerca l'atleta per nome e cognome
    fp = fopen("atleti.bin", "rb");
    if (fp == NULL) {
        printf("Errore nell'aprire il file\n");
        return;
    }

    while (fread(&atleti, sizeof(atleta), 1, fp)) {
        if (strcmp(atleti.nome, nome) == 0 && strcmp(atleti.cognome, cognome) == 0) {
            pettorina = atleti.pettorina;
            break;
        }
    }
    fclose(fp);

    // Ora cerca i tempi relativi al numero di pettorina
    fp = fopen("risultati.bin", "rb");
    if (fp == NULL) {
        printf("Errore nell'aprire il file dei risultati\n");
        return;
    }

    while (fread(&res, sizeof(risultato), 1, fp)) {
        if (res.pettorina == pettorina) {
            tempo_totale += res.tempo;
        }
    }
    fclose(fp);

    printf("Tempo totale di %s %s: %d secondi\n", nome, cognome, tempo_totale);
}

void ricerca_tempi_minori() {
    FILE *fp;
    risultato res;
    int tempo_rif;
    char tipo_prova;

    printf("Inserisci tipo di prova (N, C, B): ");
    scanf(" %c", &tipo_prova);
    printf("Inserisci tempo di riferimento (in secondi): ");
    scanf("%d", &tempo_rif);

    fp = fopen("risultati.bin", "rb");
    if (fp == NULL) {
        printf("Errore nell'aprire il file dei risultati\n");
        return;
    }

    while (fread(&res, sizeof(risultato), 1, fp)) {
        if (res.tipo_prova == tipo_prova && res.tempo < tempo_rif) {
            // Cerca l'atleta in base alla pettorina
            atleta atleti;
            FILE *fa = fopen("atleti.bin", "rb");
            if (fa == NULL) {
                printf("Errore nell'aprire il file degli atleti\n");
                return;
            }

            while (fread(&atleti, sizeof(atleta), 1, fa)) {
                if (atleti.pettorina == res.pettorina) {
                    printf("%s %s ha fatto un tempo di %d secondi\n", atleti.nome, atleti.cognome, res.tempo);
                    break;
                }
            }
            fclose(fa);
        }
    }
    fclose(fp);
}

void stampa_tempi_totali() {
    FILE *fp, *fr;
    atleta atleti;
    risultato res;

    fp = fopen("atleti.bin", "rb");
    if (fp == NULL) {
        printf("Errore nell'aprire il file degli atleti\n");
        return;
    }

    while (fread(&atleti, sizeof(atleta), 1, fp)) {
        int tempo_totale = 0;

        fr = fopen("risultati.bin", "rb");
        if (fr == NULL) {
            printf("Errore nell'aprire il file dei risultati\n");
            return;
        }

        while (fread(&res, sizeof(risultato), 1, fr)) {
            if (res.pettorina == atleti.pettorina) {
                tempo_totale += res.tempo;
            }
        }
        fclose(fr);

        printf("Tempo totale di %s %s: %d secondi\n", atleti.nome, atleti.cognome, tempo_totale);
    }

    fclose(fp);
}
