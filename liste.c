#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nod{
    int valoare;
    struct Nod* urm;
}Nod;

Nod* creareNod(int val){
    Nod* nou=(Nod*)malloc(sizeof(Nod));
    nou->valoare=val;
    nou->urm=NULL;
    return nou;
}

void inserareSortata(Nod** cap,int val){
    Nod* nou=creareNod(val);
    if(*cap==NULL||(*cap)->valoare>=val){
        nou->urm=*cap;
        *cap=nou;
    }else{
        Nod* crt=*cap;
        while(crt->urm!=NULL&&crt->urm->valoare<val)
            crt=crt->urm;
        nou->urm=crt->urm;
        crt->urm=nou;
    }
}

void afisare(Nod* cap){
    while(cap){
        printf("%d ",cap->valoare);
        cap=cap->urm;
    }
    printf("\n");
}

void stergePozitie(Nod** cap,int poz){
    if(*cap==NULL)return;
    if(poz==0){
        Nod* temp=*cap;
        *cap=(*cap)->urm;
        free(temp);
        return;
    }
    Nod* crt=*cap;
    for(int i=0;i<poz-1&&crt!=NULL;i++)
        crt=crt->urm;
    if(crt==NULL||crt->urm==NULL)return;
    Nod* temp=crt->urm;
    crt->urm=crt->urm->urm;
    free(temp);
}

int* salvareInVector(Nod* cap,int* dim){
    Nod* crt=cap;
    int nr=0;
    Nod* temp=cap;
    while(temp){
        if(temp->valoare%2==0)nr++; // conditia aleasa: elementele pare
        temp=temp->urm;
    }
    int* vec=(int*)malloc(sizeof(int)*nr);
    int k=0;
    while(crt){
        if(crt->valoare%2==0){
            vec[k]=crt->valoare;
            k++;
        }
        crt=crt->urm;
    }
    *dim=nr;
    return vec;
}

void interschimba(Nod* cap,int poz1,int poz2){
    if(poz1==poz2)return;
    Nod *a=NULL,*b=NULL,*crt=cap;
    int i=0;
    while(crt){
        if(i==poz1)a=crt;
        if(i==poz2)b=crt;
        crt=crt->urm;
        i++;
    }
    if(a&&b){
        int temp=a->valoare;
        a->valoare=b->valoare;
        b->valoare=temp;
    }
}

int main(){
    Nod* lista=NULL;
    inserareSortata(&lista,5);
    inserareSortata(&lista,2);
    inserareSortata(&lista,9);
    inserareSortata(&lista,4);
    afisare(lista);

    stergePozitie(&lista,1);
    afisare(lista);

    int dim=0;
    int* v=salvareInVector(lista,&dim);
    for(int i=0;i<dim;i++)printf("%d ",v[i]);
    printf("\n");
    free(v);

    interschimba(lista,0,1);
    afisare(lista);

    return 0;
}
