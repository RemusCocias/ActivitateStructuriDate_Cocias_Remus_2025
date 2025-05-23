#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nume[50];
    int varsta;
    int urgenta; // cu cat mai mare, cu atat mai grav
}Pacient;

typedef struct{
    Pacient* v;
    int dim;
    int cap;
}Heap;

Heap* creareHeap(int cap){
    Heap* h=(Heap*)malloc(sizeof(Heap));
    h->v=(Pacient*)malloc(sizeof(Pacient)*cap);
    h->dim=0;
    h->cap=cap;
    return h;
}

void swap(Pacient* a,Pacient* b){
    Pacient t=*a;
    *a=*b;
    *b=t;
}

void urca(Heap* h,int i){
    while(i>0&&(h->v[(i-1)/2].urgenta<h->v[i].urgenta)){
        swap(&h->v[i],&h->v[(i-1)/2]);
        i=(i-1)/2;
    }
}

void adaugaPacient(Heap* h,Pacient p){
    if(h->dim==h->cap)return;
    h->v[h->dim]=p;
    urca(h,h->dim);
    h->dim++;
}

void coboara(Heap* h,int i){
    int max=i;
    int st=2*i+1;
    int dr=2*i+2;
    if(st<h->dim&&h->v[st].urgenta>h->v[max].urgenta)max=st;
    if(dr<h->dim&&h->v[dr].urgenta>h->v[max].urgenta)max=dr;
    if(max!=i){
        swap(&h->v[i],&h->v[max]);
        coboara(h,max);
    }
}

Pacient extrageUrgent(Heap* h){
    if(h->dim==0){
        Pacient gol;
        strcpy(gol.nume,"");
        gol.varsta=0;
        gol.urgenta=0;
        return gol;
    }
    Pacient p=h->v[0];
    h->v[0]=h->v[h->dim-1];
    h->dim--;
    coboara(h,0);
    return p;
}

void afisareHeap(Heap* h){
    for(int i=0;i<h->dim;i++)
        printf("%s %d ani, urgenta: %d\n",h->v[i].nume,h->v[i].varsta,h->v[i].urgenta);
}

int main(){
    Heap* h=creareHeap(100);

    Pacient p1={"Ion",34,3};
    Pacient p2={"Maria",65,8};
    Pacient p3={"Vasile",21,5};
    Pacient p4={"Andreea",28,10}; // cu ambulanta
    Pacient p5={"George",47,2};

    adaugaPacient(h,p1);
    adaugaPacient(h,p2);
    adaugaPacient(h,p3);
    adaugaPacient(h,p4);
    adaugaPacient(h,p5);

    printf("Toti pacientii in heap:\n");
    afisareHeap(h);

    printf("\nSe preia pacientul cu urgenta cea mai mare:\n");
    Pacient urg=extrageUrgent(h);
    printf("%s %d ani, urgenta: %d\n",urg.nume,urg.varsta,urg.urgenta);

    printf("\nHeap actualizat:\n");
    afisareHeap(h);

    free(h->v);
    free(h);

    return 0;
}
