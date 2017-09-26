# VJ11-Strukture-podataka
Vjezba 11

Napisati program koji za svaku pročitanu riječ iz teksta, generira slučajni broj u rasponu od 10 - 1010.
U binarno stablo se sprema kombinacija (broj, riječ), uzevši da glavna vrijednost po kojoj se unosi u stablo
jest vrijednost broja. Ukoliko u stablu postoji zapis sa generiranim brojem, potrebno je ponoviti generiranje
slučajnog broja, te ponoviti unos. Ukoliko se unese nova kombinacija (broj, riječ), tako slučajno generirani
broj sprema se u vezanu listu, a kombinacija u binarno stablo, kako je već navedeno.
Potrebno je generirati 20 slučajnih brojeva u rasponu od 1 do maksimalnog broja elemenata koji su zapisani u
listi, te je potrebno na ekran ispisati riječi koje se nalaze zapiasne u binarnom stablu čiji je broj
jednak broju koji se nalazi zapisan u elementu vezane liste pod rednim brojem koji je slučajno generiran.

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
