#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraCarte {
	int cod;
	int nrPagini;
	float* preturiPagini;
	char* titlu;
};
typedef struct StructuraCarte Carte;

Carte citireCarteDeLaTastatura() {
	Carte c;
	printf("Introduceti codul cartii: ");
	scanf("%d", &c.cod);

	printf("Introduceti numarul de pagini: ");
	scanf("%d", &c.nrPagini);

	c.preturiPagini = (float*)malloc(sizeof(float) * c.nrPagini);
	for (int i = 0; i < c.nrPagini; i++) {
		printf("Pretul paginii %d: ", i + 1);
		scanf("%f", &c.preturiPagini[i]);
	}

	char buffer[100];
	printf("Introduceti titlul cartii: ");
	getchar(); // consum newline
	fgets(buffer, 100, stdin);
	buffer[strcspn(buffer, "\n")] = '\0';
	c.titlu = (char*)malloc(strlen(buffer) + 1);
	strcpy(c.titlu, buffer);

	return c;
}

float calculeazaPretTotal(Carte c) {
	float suma = 0;
	for (int i = 0; i < c.nrPagini; i++) {
		suma += c.preturiPagini[i];
	}
	return suma;
}

void modificareTitluCarte(Carte* c, const char* titluNou) {
	if (c->titlu) {
		free(c->titlu);
	}
	c->titlu = (char*)malloc(strlen(titluNou) + 1);
	strcpy(c->titlu, titluNou);
}

void afisareCarte(Carte c) {
	printf("\n----- Afisare Carte -----\n");
	printf("Cod: %d\n", c.cod);
	printf("Numar pagini: %d\n", c.nrPagini);
	printf("Titlu: %s\n", c.titlu);
	printf("Preturi pe pagini:\n");
	for (int i = 0; i < c.nrPagini; i++) {
		printf("   Pagina %d: %.2f\n", i + 1, c.preturiPagini[i]);
	}
	printf("Pret total: %.2f\n", calculeazaPretTotal(c));
}

void afisareVectorCarti(Carte* carti, int nr) {
	for (int i = 0; i < nr; i++) {
		afisareCarte(carti[i]);
	}
}

void dezalocareCarte(Carte* c) {
	if (c->preturiPagini) {
		free(c->preturiPagini);
	}
	if (c->titlu) {
		free(c->titlu);
	}
	c->preturiPagini = NULL;
	c->titlu = NULL;
	c->nrPagini = 0;
	c->cod = 0;
}

Carte* filtrareCartiDupaNrPagini(Carte* vector, int nr, int prag, int* nrRezultate) {
	Carte* rezultat = (Carte*)malloc(sizeof(Carte) * nr);
	*nrRezultate = 0;
	for (int i = 0; i < nr; i++) {
		if (vector[i].nrPagini > prag) {
			rezultat[*nrRezultate] = vector[i];
			(*nrRezultate)++;
		}
	}
	return rezultat;
}

Carte* filtrareCartiDupaPretTotal(Carte* vector, int nr, float prag, int* nrRezultate) {
	Carte* rezultat = (Carte*)malloc(sizeof(Carte) * nr);
	*nrRezultate = 0;
	for (int i = 0; i < nr; i++) {
		if (calculeazaPretTotal(vector[i]) > prag) {
			rezultat[*nrRezultate] = vector[i];
			(*nrRezultate)++;
		}
	}
	return rezultat;
}

Carte* concateneazaVectori(Carte* v1, int n1, Carte* v2, int n2, int* nTotal) {
	*nTotal = n1 + n2;
	Carte* rezultat = (Carte*)malloc(sizeof(Carte) * (*nTotal));
	for (int i = 0; i < n1; i++) {
		rezultat[i] = v1[i];
	}
	for (int i = 0; i < n2; i++) {
		rezultat[n1 + i] = v2[i];
	}
	return rezultat;
}

void dezalocareVector(Carte* vector, int n) {
	for (int i = 0; i < n; i++) {
		dezalocareCarte(&vector[i]);
	}
	free(vector);
}

int main() {
	int nrCarti = 5;
	Carte* vectorCarti = (Carte*)malloc(sizeof(Carte) * nrCarti);
	for (int i = 0; i < nrCarti; i++) {
		printf("\n--- Citire carte %d ---\n", i + 1);
		vectorCarti[i] = citireCarteDeLaTastatura();
	}

	printf("\n--- Toate cartile ---\n");
	afisareVectorCarti(vectorCarti, nrCarti);

	// Filtrare: nr pagini > 200
	int nrFiltrate1 = 0;
	Carte* filtrate1 = filtrareCartiDupaNrPagini(vectorCarti, nrCarti, 200, &nrFiltrate1);
	printf("\n--- Carti cu mai mult de 200 pagini ---\n");
	afisareVectorCarti(filtrate1, nrFiltrate1);

	// Filtrare: pret total > 100
	int nrFiltrate2 = 0;
	Carte* filtrate2 = filtrareCartiDupaPretTotal(vectorCarti, nrCarti, 100.0f, &nrFiltrate2);
	printf("\n--- Carti cu pret total > 100 ---\n");
	afisareVectorCarti(filtrate2, nrFiltrate2);

	// Concatenare
	int nrConcatenat = 0;
	Carte* vectorConcatenat = concateneazaVectori(filtrate1, nrFiltrate1, filtrate2, nrFiltrate2, &nrConcatenat);
	printf("\n--- Vector concatenat ---\n");
	afisareVectorCarti(vectorConcatenat, nrConcatenat);

	// Dezalocari
	free(filtrate1);
	free(filtrate2);
	free(vectorConcatenat);
	dezalocareVector(vectorCarti, nrCarti);

	return 0;
}
