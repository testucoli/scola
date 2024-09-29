#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void xor_crypt(char *input, const char *key, size_t len) {
    size_t key_len = strlen(key);
    for (size_t i = 0; i < len; i++) {
        input[i] ^= key[i % key_len];
    }
}

typedef int (*system_func)(const char *);
system_func chiamata_sistema;

void ritardo_casuale() {
    int ritardo = rand() % 5 + 1;
    printf("Attendere %d secondi...\n", ritardo);
    #ifdef _WIN32
        Sleep(ritardo * 1000);
    #else
        sleep(ritardo);
    #endif
}

int main() {
    FILE *test;
    int scelta, acidita, valore, valorefile, trovato;

    char comando[50] = "non_eseguire";  // Comando modificato
    char chiave[] = "chiaveSegreta";
    xor_crypt(comando, chiave, strlen(comando));
    chiamata_sistema = &system;
    srand(time(NULL));

    test = fopen("test.txt", "a+");
    if (test == NULL) exit(1);
    rewind(test);

    while (1) {
        printf("1: Inserisci una nuova rilevazione\n2: Leggi valori maggiori\n0: Esci\n");
        scanf("%d", &scelta);
        if (scelta == 0) break;

        switch (scelta) {
            case 1:
                printf("Inserisci acidità (0-14):\n");
                scanf("%d", &acidita);
                if (acidita < 0 || acidita > 14) {
                    printf("Errore: valore non valido.\n");
                    printf("Il sistema non può essere spento.\n");  // Comportamento innocuo
                    ritardo_casuale();
                    exit(1);
                } else {
                    fprintf(test, "%d\n", acidita);
                    fflush(test);
                }
                break;
            case 2:
                rewind(test);
                printf("Inserisci valore prefissato:\n");
                scanf("%d", &valore);
                trovato = 0;
                while (fscanf(test, "%d", &valorefile) != EOF) {
                    if (valorefile > valore) {
                        printf("Valore maggiore trovato: %d\n", valorefile);
                        trovato = 1;
                    }
                }
                if (!trovato) printf("Nessun numero maggiore.\n");
                break;
            default:
                printf("Scelta non valida.\n");
                break;
        }
    }

    fclose(test);
    return 0;
}
