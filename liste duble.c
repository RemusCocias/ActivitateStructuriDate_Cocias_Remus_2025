#include <stdio.h>
#include <stdlib.h>

typedef struct NodDublu{
    int val;
    struct NodDublu* prev;
    struct NodDublu* next;
}NodDublu;

typedef struct NodSimplu{
    int val;
    struct NodSimplu* next;
}NodSimplu;

NodDublu* creareNodDublu(int val){
    NodDublu* n=(NodDublu*)malloc(sizeof(NodDublu));
    n->val=val;
    n->prev=NULL;
    n->next=NULL;
    return n;
}

void inserareSortataDublu(NodDublu** cap,int val){
    NodDublu* n=creareNodDublu(val);
    if(*cap==NULL){
        *cap=n;
        return;
    }
    NodDublu* c=*cap;
    if(c->val>=val){
        n->next=c;
        c->prev=n;
        *cap=n;
        return;
    }
    while(c->next&&c->next->val<val)
        c=c->next;
    n->next=c->next;
    if(c->next)c->next->prev=n;
    n->prev=c;
    c->next=n;
}

void afisareCrescator(NodDublu* cap){
    while(cap){
        printf("%d ",cap->val);
        if(cap->next==NULL)break;
        cap=cap->next;
    }
    printf("\n");
}

void afisareDescrescator(NodDublu* cap){
    while(cap&&cap->next)cap=cap->next;
    while(cap){
        printf("%d ",cap->val);
        cap=cap->prev;
    }
    printf("\n");
}

void stergerePozitieDublu(NodDublu** cap,int poz){
    if(*cap==NULL)return;
    NodDublu* c=*cap;
    if(poz==0){
        *cap=c->next;
        if(c->next)c->next->prev=NULL;
        free(c);
        return;
    }
    int i=0;
    while(c&&i<poz){
        c=c->next;
        i++;
    }
    if(c==NULL)return;
    if(c->prev)c->prev->next=c->next;
    if(c->next)c->next->prev=c->prev;
    free(c);
}

NodSimplu* creareNodSimplu(int val){
    NodSimplu* n=(NodSimplu*)malloc(sizeof(NodSimplu));
    n->val=val;
    n->next=NULL;
    return n;
}

NodSimplu* copiazaPare(NodDublu* cap){
    NodSimplu* capS=NULL,*ultim=NULL;
    while(cap){
        if(cap->val%2==0){
            NodSimplu* nou=creareNodSimplu(cap->val);
            if(capS==NULL){
                capS=nou;
                ultim=nou;
            }else{
                ultim->next=nou;
                ultim=nou;
            }
        }
        cap=cap->next;
    }
    return capS;
}

void afisareListaSimpla(NodSimplu* cap){
    while(cap){
        printf("%d ",cap->val);
        cap=cap->next;
    }
    printf("\n");
}

void interschimbaPozitiiDublu(NodDublu* cap,int p1,int p2){
    if(p1==p2)return;
    NodDublu* a=NULL,*b=NULL;
    int i=0;
    while(cap){
        if(i==p1)a=cap;
        if(i==p2)b=cap;
        cap=cap->next;
        i++;
    }
    if(a&&b){
        int tmp=a->val;
        a->val=b->val;
        b->val=tmp;
    }
}

int main(){
    NodDublu* lista=NULL;
    inserareSortataDublu(&lista,4);
    inserareSortataDublu(&lista,1);
    inserareSortataDublu(&lista,9);
    inserareSortataDublu(&lista,2);

    afisareCrescator(lista);
    afisareDescrescator(lista);

    stergerePozitieDublu(&lista,2);
    afisareCrescator(lista);

    NodSimplu* listaS=copiazaPare(lista);
    afisareListaSimpla(listaS);

    interschimbaPozitiiDublu(lista,0,1);
    afisareCrescator(lista);

    return 0;
}
