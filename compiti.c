#include <stdio.h>
#include <stdlib.h>




int main(){
    FILE *test;
    int scelta;
    int acidita;
    int valore;
    int valorefile;
    int trovato=0;
    test=fopen("test.txt", "a+");
    if(test == NULL){
        printf("il file non esiste\n");
        exit(1);
    }
    rewind(test);

    while(1){
    printf("inserisci la scelta: 1: inserisci la nuova rilevazione 2: leggi i valori maggiori da un valore prefissato 0: esci \n");
    scanf("%d",&scelta);
    if(scelta == 0){
        fclose(test);
        exit(0);
    }

    switch (scelta)
    {
    case 1:
        printf("inserisci la nuova rilevazione di acidita seguendo la scala da 0 a 14 \n");
        
        scanf("%d", &acidita);
        if(acidita>14 || acidita<0){
        printf("non hai rispettato la scala\n");
        return(0);
}else{
     fprintf(test,"%d\n",acidita);
}
        break;
    case 2:
        rewind(test);
        printf("leggi i valori maggiori da un valore prefissato\n");
        scanf("%d",&valore);
        while(fscanf(test,"%d",&valorefile)!= EOF){
            if(valorefile>valore){
                printf("i numeri maggiori sono: %d\n",valorefile);
                trovato=1;
            }
        }

        if (!trovato){
            printf("nessun numero maggiore del valore prefissato\n");
        }
        break;

    default:
        break;
    }

}


return 0;

}