#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char namespisok[11]="spisok.txt";

struct station
{
    char name[20];
    int l;                      //peremennaya dlay podstscheta dlini puti
    int count;
    struct transfer *utransfer;
};

struct transfer
{
    struct station *unewstation;
    int duration;
};

void ** check(char *name)
{
    //printf("   %s \n", name);
    FILE *spisok;
    char namei[20];          // probegaet po imenam v faile
    void **ukas;
    spisok=fopen(namespisok,"r");
    if (spisok==NULL){printf("File '%s' cannot be open (chek) %s\n", namespisok, name);  return 0;}
    //printf("   %s \n", name);
    while (!feof(spisok))
    {
        fscanf(spisok,"%s%p",namei,ukas);
        if (!strcmp(name, namei)) return ukas;
    }
    fclose(spisok);
    return 0;
}

struct station * input(FILE *basa) // basa - spisok dlay grafa; spisok - name + ukas na structuru
  {
      FILE *spisok;
      int i;
      char nameproverki[20];
      struct station *u, *ukas, *q;

      fscanf(basa,"%s", nameproverki);

      ukas=check(nameproverki);
      if(ukas==0)
      {
        u=(struct station *)malloc (sizeof(struct station));
        spisok=fopen(namespisok,"a");
        if (spisok==NULL){printf("File '%s' cannot be open (input 1)\n", namespisok);  return 0;}
        fprintf(spisok,"%s %p\n", nameproverki, u);
        fclose(spisok);
      }
      else
        u=ukas;

     strcpy(u->name, nameproverki);
     fscanf(basa,"%d%d",&(u->l),&(u->count));


     (u->utransfer)=(struct transfer *)malloc((u->count)*sizeof(struct transfer));

      for(i=0;i<(u->count);i++)
     {

         fscanf(basa,"%s", nameproverki);
         printf("   %s \n", nameproverki);

         ukas=check(nameproverki);
         printf("   %s \n", nameproverki);
         if(ukas==0)
         {
           q=(struct station *)malloc (sizeof(struct station));
           spisok=fopen(namespisok,"a");
           if (spisok==NULL){printf("File '%s' cannot be open (input 2)\n", namespisok);  return 0;}
           fprintf(spisok,"%s %p\n", nameproverki, q);

           fclose(spisok);
         }
         else
           //{
               q=ukas;
         //  printf("%d    %s %p\n",i, nameproverki, q);}

         ((u->utransfer)+i)->unewstation = q;
         fscanf(basa,"%d", &(((u->utransfer)+i)->duration));

      }
      return u;

  }

int main()
{
    char filename[10];
    struct station *p;
    FILE *file, *spisok;
    int i;


    printf("read base from: ");
                scanf("%s",filename);

                 file=fopen(filename,"r");
if (file==NULL){printf("File '%s' cannot be open\n", filename);  return 7;}

         spisok=fopen(namespisok,"w");
           if (spisok==NULL){printf("File '%s' cannot be open (input 2)\n", namespisok);  return 0;}

           fclose(spisok);
//while(!feof(file))
 p=input(file);

 printf("%-25s   %d    %d\n",p->name, p->l, p->count);

//          for(i=0;i<(p->count);i++)
//          {printf("\t%s   %d \n",((p->utransfer)+i)->duration);
//          }

fclose(file);
    return 0;

}
