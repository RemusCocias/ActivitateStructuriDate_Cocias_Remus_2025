#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraCarte {
	int cod;
	int nrPagini;
	float* preturiPagini; // vector cu preturi per pagina
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
	buffer[strcspn(buffer, "\n")] = '\0'; // eliminam \n
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

int main() {
	Carte carte = citireCarteDeLaTastatura();
	afisareCarte(carte);

	printf("\nModificam titlul cartii...\n");
	modificareTitluCarte(&carte, "Titlu Nou Actualizat");
	afisareCarte(carte);

	dezalocareCarte(&carte);
	return 0;
}
