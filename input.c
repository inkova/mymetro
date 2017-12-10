#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char filename[20]="basa.txt";

struct station
{
    char name[20];
    int l;                      //variable to find path length
    int count;
    struct transfer *utransfer;
};

struct transfer
{
    struct station *unewstation;
    int duration;
};

typedef struct Node
{
    struct Node **next;
    struct station * ukas;
} Node;

void add(char *word, Node **root, int n, struct station * u)
{
    printf("Adding word %s\n", word);
    char *i = word; Node **p = &root[(*i)%n];
    while (*p)
    {
	printf("%c already exists here\n", *i);
	++i;
	if (!*i)
	{
	    (*p)->ukas = u;
	    return;
	}
	p = &(*p)->next[(*i)%n];
    }
    while (1)
    {
	printf("Creating %c\n", *i);
	*p = malloc(sizeof(Node));
	(*p)->next = calloc(sizeof(Node*), n);
	++i;
	if (!*i)	//if *i is the end of the word
	{
	    (*p)->ukas = u;
	    return;
	}
	(*p)->ukas = NULL;	//because it is not the end of the word
	p = &(*p)->next[(*i)%n];
    }
}

struct station *search(char *word, Node **root, int n)
{
    char *i = word; Node *p = root[(*i)%n];
    while (p)
    {
	++i;
	if (!*i)
	{
	    if (!p->ukas) return NULL; //otherwise having word 'name' could already find word 'nam'
	    return p->ukas;
	}
	p = p->next[(*i)%n];
    }
    return NULL;
}

struct station * input(FILE *basa, Node **root, int n) // basa - list for graph construction;
  {

      int i;
      char nameproverki[20];
      struct station *u, *ukas, *q;
      while (!feof(basa))
      {
        fscanf(basa,"%s", nameproverki);
        printf("osnov  %s \n", nameproverki);
        ukas=search(nameproverki, root, n);
        printf("%s %p\n", nameproverki, ukas);
        if(ukas==NULL)
        {
          u=(struct station *)malloc (sizeof(struct station));
          add(nameproverki, root, n, u);
        }
        else
          u=ukas;

       strcpy(u->name, nameproverki);
       fscanf(basa,"%d",&(u->count));
       (u->l)=100000;

       (u->utransfer)=(struct transfer *)malloc((u->count)*sizeof(struct transfer));

        for(i=0;i<(u->count);i++)
        {
           fscanf(basa,"%s", nameproverki);
           printf("zikl   %s \n", nameproverki);
           ukas=search(nameproverki, root, n);
           if(ukas==NULL)
           {
             q=(struct station *)malloc (sizeof(struct station));
             add(nameproverki, root, n, q);
           }
           else
               q=ukas;

           ((u->utransfer)+i)->unewstation = q;
           fscanf(basa,"%d", &(((u->utransfer)+i)->duration));

        }

      }
      return u;

  }

struct station *forroute(char *word, Node **root, int n)
{
    struct station *purpose;
    purpose=search(word, root, n);
    (purpose)->l=0;
    if(purpose!=NULL) (purpose)->l=0;
    return purpose;
}


void routesearch(struct station *run, struct station *source, int lmax)
{   int i=0, tp;

    for(; i<(run->count); ++i)
    {
      tp=((run->utransfer)+i)->unewstation->l - (run->l);
      if( tp > ((run->utransfer)+i)->duration)
      {
        ((run->utransfer)+i)->unewstation->l= run->l + ((run->utransfer)+i)->duration ;
        if(((run->utransfer)+i)->unewstation==source)
        {
           lmax=((run->utransfer)+i)->unewstation->l;
           return;
        }
        if (((run->utransfer)+i)->unewstation->l < lmax) routesearch(((run->utransfer)+i)->unewstation, source,lmax);
       }
    }
    return;
}


int main()
{
    char filename[10], purpose[30], source[30];
    struct station *p, *upurpose, *usource;
    FILE *file;
    int i, n=255;
    Node **root; root = calloc(sizeof(Node*), n);

    //printf("read base from: ");
    // scanf("%s",filename);

                 file=fopen("basa.txt","r");
if (file==NULL){printf("File '%s' cannot be open\n", filename);  return 7;}

 p=input(file, root, n);

printf("to: ");
scanf("%s", purpose);
printf("from: ");
scanf("%s", source);

int lmax=100000;
upurpose=forroute(purpose, root, n);
usource=search(source, root, n);
routesearch(upurpose,usource,lmax);
printf("%d", (usource)->l);
fclose(file);
return 0;
}