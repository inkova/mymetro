#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct station
{
    char name[100];
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
    char *i = word; Node **p = &root[(*i)%n];
    while (*p)
    {
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
void get_word(FILE *file, char *word)
{   int c; char *i=word;

    c = getc(file);
    c = getc(file);
    while (c != '$')
    {
        *i = c;
         ++i;
         c = getc(file);

    }
    *i='\0';
    c = getc(file);

    return;
}

void my_scanf(char *word)
{   char c, *i=word;
    scanf("%c", &c);
    while (c != 10)
    {
        *i = c;
         ++i;
         scanf("%c", &c);

    }
    *i='\0';
return;
}

void time(int *hour, int *minute, int *l)
{
    (*minute)+=(*l);
    while((*minute)>=60)
    {
        (*minute)-=60;
        (*hour)+=1;
    }
    if(*hour>23) *hour-=24;
    return;
}

struct station * input(FILE *basa, Node **root, int n) // basa - list for graph construction;
  {

      int i;
      char nameproverki[100];
      struct station *u=NULL, *ukas=NULL, *q=NULL;
      while (!feof(basa))
      {
        get_word(basa,nameproverki);
        ukas=search(nameproverki, root, n);
        if(ukas==NULL)
        {
          u=(struct station*) malloc (sizeof(struct station));
          add(nameproverki, root, n, u);
        }
        else
          u=ukas;

       strcpy(u->name, nameproverki);
       fscanf(basa,"%d",&(u->count));
       (u->l)=100000;

       (u->utransfer)=(struct transfer *) malloc((u->count)*sizeof(struct transfer));

        for(i=0;i<(u->count);i++)
        {
           get_word(basa,nameproverki);
           ukas=search(nameproverki, root, n);
           if(ukas==NULL)
           {
             q=(struct station*)malloc (sizeof(struct station));
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


void route_print(struct station *run, struct station *source, int *hour, int *minute)
{
    int i=0, tp;
    if(run==source) { printf("\n->end of the road\n"); return; }
    for(i=0;i<(run->count); ++i)
    {
        tp= (run->l)-((run->utransfer)+i)->unewstation->l ;
        if (tp==((run->utransfer)+i)->duration)
        {
           time(hour, minute, &(((run->utransfer)+i)->duration));
           printf( "\n\t%-40s   %d:%02d", ((run->utransfer)+i)->unewstation->name, *hour, *minute);
           route_print(((run->utransfer)+i)->unewstation, source, hour, minute);
           return;
        }
   }
   printf("Error");
   return;
}

void forroute_print(struct station *run, struct station *source, int *hour, int *minute)
{
    printf("\nstart of the road->\n\t%-40s   %d:%02d",run->name, *hour, *minute);
    route_print(run, source, hour, minute);
    return;
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
    struct station *upurpose, *usource;
    FILE *file;
    int n=255;
    Node **root; root = calloc(sizeof(Node*), n);

file=fopen("basaT.txt","r");
if (file==NULL){printf("\n\t\t! ERROR !\nDatabases not found. You should contact technical support.\n");  return 7;}

input(file, root, n);
fclose(file);

char purpose[100], source[100];
int i;

printf("from: ");
my_scanf(source);

printf("to: ");
my_scanf(purpose);

int hour, minute;

printf("you want to be at the station %s at (hh mm) ", purpose);
scanf("%d%d", &hour, &minute);

int lmax=100000;
upurpose=forroute(purpose, root, n);
usource=search(source, root, n);

routesearch(upurpose,usource,lmax);

int hour_purpose=hour, minute_purpose=minute;
time(&hour_purpose, &minute_purpose, &(usource->l));
printf("\n\nYou should be at the station %s at %d:%02d\n", purpose, hour_purpose, minute_purpose);
printf("Your journey time will be %d minutes\n", (usource)->l);

forroute_print(usource, upurpose, &hour, &minute);

return 0;
}
