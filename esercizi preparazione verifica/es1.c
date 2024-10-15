/*Scrittura e lettura da file di testo
Scrivi un programma che chiede all'utente di inserire una lista di nomi e cognomi (fino a quando l'utente inserisce "stop").
I nomi e i cognomi devono essere salvati in un file di testo chiamato nomi.txt.
Successivamente, il programma deve rileggere il file e stampare i nomi sullo schermo.*/


#include <stdio.h>
#include <string.h>
typedef struct{
  char nome[20];
  char cognome[20];
}persona;


int main(){
  persona persone;
  FILE *fp;
  char stop[]="stop";
  int count=0;
  char buff[255];

fp=fopen("file.txt","a");
if(fp==NULL){
    printf("errore \n");
    return 1;
}
while(1){
    printf("inserisci il nome del dipendente: ");
    scanf("%s",persone.nome);

    if(strcmp(persone.nome,stop)==0){
        break;
    }

    printf("inserisci il cognome del dipendente: ");
    scanf("%s",persone.cognome);
    fprintf(fp,"%s %s\n",persone.nome,persone.cognome);
}
fclose(fp);


fp=fopen("file.txt","r");
if(fp==NULL){
    printf("errore \n");
    return 1;
}

while(fgets(buff,sizeof(buff),fp)!=NULL){
    printf("%s",buff);

}
fclose(fp);
return 0;
}