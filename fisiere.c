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
	getchar();
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

void afisareVectorCarti(Carte* vector, int dim) {
	for (int i = 0; i < dim; i++) {
		afisareCarte(vector[i]);
	}
}

void dezalocareVector(Carte* vector, int dim) {
	for (int i = 0; i < dim; i++) {
		dezalocareCarte(&vector[i]);
	}
	free(vector);
}

Carte* filtrareCartiDupaPretTotal(Carte* vector, int dim, int* dimNoua, float prag) {
	Carte* rezultat = (Carte*)malloc(sizeof(Carte) * dim);
	*dimNoua = 0;
	for (int i = 0; i < dim; i++) {
		if (calculeazaPretTotal(vector[i]) > prag) {
			rezultat[*dimNoua] = vector[i];
			(*dimNoua)++;
		}
	}
	return rezultat;
}

Carte* filtrareCartiDupaNrPagini(Carte* vector, int dim, int* dimNoua, int prag) {
	Carte* rezultat = (Carte*)malloc(sizeof(Carte) * dim);
	*dimNoua = 0;
	for (int i = 0; i < dim; i++) {
		if (vector[i].nrPagini < prag) {
			rezultat[*dimNoua] = vector[i];
			(*dimNoua)++;
		}
	}
	return rezultat;
}

Carte* concateneazaVectori(Carte* v1, int d1, Carte* v2, int d2) {
	Carte* rezultat = (Carte*)malloc(sizeof(Carte) * (d1 + d2));
	for (int i = 0; i < d1; i++) rezultat[i] = v1[i];
	for (int i = 0; i < d2; i++) rezultat[d1 + i] = v2[i];
	return rezultat;
}

void scrieCarteInFisierText(Carte c, FILE* f) {
	fprintf(f, "Cod: %d\n", c.cod);
	fprintf(f, "Titlu: %s\n", c.titlu);
	fprintf(f, "Numar pagini: %d\n", c.nrPagini);
	fprintf(f, "Preturi pe pagini: ");
	for (int i = 0; i < c.nrPagini; i++) {
		fprintf(f, "%.2f ", c.preturiPagini[i]);
	}
	fprintf(f, "\nPret total: %.2f\n", calculeazaPretTotal(c));
	fprintf(f, "--------------------------\n");
}

void scrieVectorInFisierText(Carte* vector, int n, const char* numeFisier) {
	FILE* f = fopen(numeFisier, "w");
	if (f) {
		for (int i = 0; i < n; i++) {
			scrieCarteInFisierText(vector[i], f);
		}
		fclose(f);
	}
}

void scrieCartiInFisierBinar(Carte* vector, int n, const char* numeFisier) {
	FILE* f = fopen(numeFisier, "wb");
	if (f) {
		for (int i = 0; i < n; i++) {
			fwrite(&vector[i].cod, sizeof(int), 1, f);
			fwrite(&vector[i].nrPagini, sizeof(int), 1, f);
			fwrite(vector[i].preturiPagini, sizeof(float), vector[i].nrPagini, f);
			int lungime = strlen(vector[i].titlu) + 1;
			fwrite(&lungime, sizeof(int), 1, f);
			fwrite(vector[i].titlu, sizeof(char), lungime, f);
		}
		fclose(f);
	}
}

Carte* citireCartiDinFisierBinar(const char* numeFisier, int* nrCarti) {
	FILE* f = fopen(numeFisier, "rb");
	Carte* vector = (Carte*)malloc(sizeof(Carte) * 100);
	*nrCarti = 0;
	while (!feof(f)) {
		Carte c;
		if (fread(&c.cod, sizeof(int), 1, f) != 1) break;
		if (fread(&c.nrPagini, sizeof(int), 1, f) != 1) break;
		c.preturiPagini = (float*)malloc(sizeof(float) * c.nrPagini);
		fread(c.preturiPagini, sizeof(float), c.nrPagini, f);
		int lungime = 0;
		fread(&lungime, sizeof(int), 1, f);
		c.titlu = (char*)malloc(sizeof(char) * lungime);
		fread(c.titlu, sizeof(char), lungime, f);
		vector[*nrCarti] = c;
		(*nrCarti)++;
	}
	fclose(f);
	return vector;
}

int main() {
	int nrCarti = 10;
	Carte* vectorCarti = (Carte*)malloc(sizeof(Carte) * nrCarti);
	for (int i = 0; i < nrCarti; i++) {
		printf("\n--- Citire carte %d ---\n", i + 1);
		vectorCarti[i] = citireCarteDeLaTastatura();
	}

	scrieCartiInFisierBinar(vectorCarti, nrCarti, "carti.dat");
	scrieVectorInFisierText(vectorCarti, nrCarti, "carti.txt");

	int nrCitite = 0;
	Carte* cartiDinFisier = citireCartiDinFisierBinar("carti.dat", &nrCitite);
	printf("\n--- Carti citite din fisier binar ---\n");
	afisareVectorCarti(cartiDinFisier, nrCitite);

	dezalocareVector(vectorCarti, nrCarti);
	dezalocareVector(cartiDinFisier, nrCitite);
	return 0;
}
