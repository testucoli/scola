/*Copia di un file di testo
Scrivi un programma che legga il contenuto di un file di testo origine.txt e lo copi in un altro file chiamato destinazione.txt.
 Alla fine del programma, stampa il numero di righe copiate.*/

#include <stdio.h>
#include <string.h>


int main(){

    FILE *fp;
    FILE *f;

    char copia[255];
    char incolla[255];
    fp=fopen("origine.txt","r");

    while(fgets(copia,sizeof(copia),fp)!=NULL){
        printf("%s",copia);
    }
    fclose(fp);
    f=fopen("destinazione.txt","w");
    strcpy(copia,incolla);

    fprintf(f,"%s\n",incolla);
    fclose(f);
    return 0;

}