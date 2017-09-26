/*
Zadatak 3. - Grupa 3.
-----------------------------------------------------------------------------------------------------------
Napisati program koji za svaku proèitanu rijeè iz teksta, generira sluèajni broj u rasponu od 10 - 1010.
U binarno stablo se sprema kombinacija (broj, rijeè), uzevši da glavna vrijednost po kojoj se unosi u stablo
jest vrijednost broja. Ukoliko u stablu postoji zapis sa generiranim brojem, potrebno je ponoviti generiranje
sluèajnog broja, te ponoviti unos. Ukoliko se unese nova kombinacija (broj, rijeè), tako sluèajno generirani
broj sprema se u vezanu listu, a kombinacija u binarno stablo, kako je veæ navedeno.
Potrebno je generirati 20 sluèajnih brojeva u rasponu od 1 do maksimalnog broja elemenata koji su zapisani u
listi, te je potrebno na ekran ispisati rijeèi koje se nalaze zapiasne u binarnom stablu èiji je broj
jednak broju koji se nalazi zapisan u elementu vezane liste pod rednim brojem koji je sluèajno generiran.

Napomena:
typedef struct _listNode
{
char number;
struct _listNode *Next;
}_LISTNODE;
typedef struct _treeNode
{
int number;
char[50] word;
struct _treeNode *Left;
struct _treeNode *Right;
}_TREENODE;
__________________________________________________________________________________________________________
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

typedef struct lista *pos;
typedef struct lista
{
	int number;//zasto je ovo originalno char boga pitaj, ja sam prebacija u int
	pos next;
}lista;

typedef struct stablo *node;
typedef struct stablo
{
	int number;
	char word[50];
	node left;
	node right;
}stablo;

int brojRijeciUFileu();//samo broji koliko ima rijeci u fileu
int RNG(int, int[]);//radi rng brojeve izmedju 10 i 1010
int RNGLista(int, int, int[]);//radi rng brojeve izmedju 0 i broja rijeci
node unosIzFilea(int[], node, pos);//cita iz filea i unosi u listu i stablo
node unosUStablo(node, node);//generic unos u stablo
void unosUListu(int, pos);//generic unos u listu na pocetak
void printListu(pos);//printa cilu listu, samo za testiranje
void printStablo(node);//printa cilo stablo samo za testiranje
int randomBrojeviIzListe(pos, int);//hvata ranom brojeve iz liste sa odabranih mjesta
void printOdabraniBrojeviStablo(int, node);//printa ono sta zadatak pita

int main()
{
	srand(time(NULL));

	lista head;
	head.next = NULL;

	node root = NULL;

	int brojRijeci, *rNiz, niz[20], nizRandomBrojeva[20];//rniz je niz brojeva u kojeg se unose svi random brojevi, onda se iz njega vade za listu i stablo, sluzi za provjeru da se nebi dvaput iskoristija isti random broj
														//niz[20] prima random brojeve od 0 do broja clanova liste
														//nizRandomBrojeva[20] prima 20 random brojeva iz liste koji odgovrajau rijecima u stablu koja se trebaju ispisati
	brojRijeci = brojRijeciUFileu();
	rNiz = (int)malloc(brojRijeci * sizeof(int));//treba ga dinamicki alocirat posto neznamo koliki je brj rijeci u fileu
	root = unosIzFilea(rNiz, root, &head);//unosimo iz filea u stablo i listu
	printListu(&head);//printamo listu samo za testira
	printf("\n\n\n\n");
	printStablo(root);//ista stvar ka i sa printanjem liste
	for (int i = 0; i < 20; i++)
	{
		niz[i] = RNGLista(brojRijeci, i, niz);//odabiremo 1 od 20 brojeva u listi 
		nizRandomBrojeva[i] = randomBrojeviIzListe(&head, niz[i]);//citamo random broj u listi koji je na odabranoj poziciji
	}
	printf("\n\n\n\n");
	for (int i = 0; i < 20; i++)
	{
		printOdabraniBrojeviStablo(nizRandomBrojeva[i], root);//ispisujemo sadrzaje stabla koji imaju random brojeve iste kao i one koje smo odabrali iz liste
	}
	printf("\n\n\n\n");
	return 0;
}

int brojRijeciUFileu()
{
	FILE* dat;
	dat = fopen("Text.txt", "r");
	int brojac = 0;
	char rijec[50];
	while (!feof(dat))
	{
		fscanf(dat, "%s", rijec);//svaki put kad rijec procita brojac se poveca
		brojac++;
	}
	fclose(dat);
	return brojac;
}

int RNG(int brojac, int niz[])//obicni rng od 10 do 1010 koji pazi da se ne ponavlja
{
	int R, check = 0;
	do
	{
		check = 0;
		R = rand() % 1000 + 10;
		for (int i = 0; i < brojac; i++)
		{
			if (niz[i] == R)
			{
				check = 1;
				break;
			}
		}
	} while (check == 1);
	return R;
}

int RNGLista(int broj, int brojac, int niz[])//obicni rng od 0 do broja rijeci koji pazi da se ne ponavlja
{
	int R, check = 0;
	do
	{
		check = 0;
		R = rand() % broj;
		for (int i = 0; i < brojac; i++)
		{
			if (niz[i] == R)
			{
				check = 1;
				break;
			}
		}
	} while (check == 1);
	return R;
}

node unosIzFilea(int niz[], node S, pos P)
{
	FILE *dat;
	dat = fopen("Text.txt", "r");
	int i = 0;//ovo ce nam sluzit ka brojac, doce do max broj rijeci
	while (!feof(dat))
	{
		node temp = (node)malloc(sizeof(stablo));
		fscanf(dat, " %s", temp->word);
		niz[i] = RNG(i, niz);//generiramo random broj od 10 do 1010
		temp->number = niz[i];
		S = unosUStablo(temp, S);//unosimo u stablo
		unosUListu(temp->number, P);//unosimo u listu
		i++;
	}
	fclose(dat);
	return S;//vracamo S zato da se u mainu promini
}

node unosUStablo(node temp, node S)
{
	if (NULL == S)
	{
		S = (node)malloc(sizeof(stablo));
		S->left = NULL;
		S->right = NULL;
		strcpy(S->word, temp->word);
		S->number = temp->number;
	}
	else if (temp->number > S->number)
	{
		S->right = unosUStablo(temp, S->right);
	}
	else if (temp->number < S->number)
	{
		S->left = unosUStablo(temp, S->left);
	}
	return S;
}

void unosUListu(int x, pos P)//samo unosimo na pocetak
{
	pos temp = (pos)malloc(sizeof(lista));
	temp->number = x;
	temp->next = P->next;
	P->next = temp;
}

void printListu(pos P)
{
	P = P->next;
	while (NULL != P)
	{
		printf("\n\t%d", P->number);
		P = P->next;
	}
}

void printStablo(node S)
{
	if (NULL != S)
	{
		printStablo(S->left);
		printf("\n\t%s %d", S->word, S->number);
		printStablo(S->right);
	}
}

int randomBrojeviIzListe(pos P, int x)//primamo listu i broj lokacije na kojem se nalazi random broj koji nam treba
{
	int i = 0;
	while (NULL != P->next && i < x)//dok nismo dosli do kraja ili lokacije
	{
		i++;
		P = P->next;
	}
	return P->number;
}

void printOdabraniBrojeviStablo(int x, node S)//s obzirom da ispisujemo i da se root u mainu ne mijenja ovo moze biti void, ne treba biti node posto ne mijenjamo vrijednosti, iako i tako bi isto radilo (funkcija slicna unosu)
{
	if (S->number == x)//ako je isti ispisemo ga
	{
		printf("\n\t%s %d", S->word, S->number);
	}
	else if (x > S->number)//ako je veci idemo desno
	{
		printOdabraniBrojeviStablo(x, S->right);
	}
	else if (x < S->number)//ako je manji idemo livo
	{
		printOdabraniBrojeviStablo(x, S->left);
	}
}