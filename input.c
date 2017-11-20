#include <stdio.h>
#include <stdlib.h>

struct station
{
    char name[20];
    int l;                      //peremennaya dlay podstscheta dlini puti
    int count;
    struct transfer *utransfer;
};

struct transfer
{
    char st[20];
    struct station *unewstation;
    int duration;
};

struct station * input(FILE *file)
  {
      int i;
      struct station *u;
      u=(struct station *)malloc (sizeof(struct station)); //sozdanie struct u
      fscanf(file,"%s%d%d",u->name,&(u->l),&(u->count));
      (u->utransfer)=(struct transfer *)malloc((u->count)*sizeof(struct transfer));

      for(i=0;i<(u->count);i++)
     {
      ((u->utransfer)+i)->unewstation = u;                                           //trebuet dorabotki!!!!
         fscanf(file,"%s%d",((u->utransfer)+i)->st,&(((u->utransfer)+i)->duration));
      }
      return u;
  }

int main()
{
    char filename[10];
    struct station *p;
    FILE *file;
    int i;


    printf("read base from: ");
                scanf("%s",filename);

                 file=fopen(filename,"r");
if (file==NULL){printf("File '%s' cannot be open\n", filename);  return 7;}

 p=input(file);

 printf("%-25s   %d    %d\n",p->name, p->l, p->count);

          for(i=0;i<(p->count);i++)
          {printf("\t%s   %d \n",((p->utransfer)+i)->st,((p->utransfer)+i)->duration);
          printf("%s\n",((p->utransfer)+i)->unewstation->name);}


    return 0;
}
