/*creare due file uno con i dati dello studente(nome cognome matricola)
laltro con i suoi voti(voto materia matricola) 
dopo con il controllo della matricola cercare i voti collegati 
a quella matricola e stamparli
*/



#include <stdio.h>
#include <stdlib.h>


typedef struct{
    char nome[50];
    char cognome[50];
    int matricola;
}studente;


typedef struct{
    int matricola;
    char materia[50];
    float voto;
}voto;

int main()
{
    int scelta;
    FILE *s;
    FILE *v;
    studente studenti;
    voto voti;
    
    
    while(1){
        printf("1:per inserire lo studente\n");
        printf("2:per inserire il voto\n");
        printf("3:per visualizzare i voti di uno studente\n");
        printf("0:per uscire\n");
        scanf("%d",&scelta);
        if(scelta==0){
            exit(0);
        }
        switch(scelta){
            case 1:
            printf("inserisci il nome dello studente\n");
            scanf("%s",studenti.nome);
            printf("inserisci il cognome dello studente\n");
            scanf("%s",studenti.cognome);
            printf("inserisci la matricola dello studente\n");
            scanf("%d",&studenti.matricola);
            s=fopen("studenti.txt","w+");
            fwrite(&studenti,sizeof(studente),1,s);
            fclose(s);
            break;
        }
    
}
    return 0;
}
