#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
typedef struct Adatok
{
	int melyseg;
	int sorszam;
	struct Adatok* kovetkezo;
	
}Adatok;
Adatok* feltoltes(Adatok* adat, int melyseg, int sorszam);
void Torles(Adatok* adat);

int main(char* args, char** argv)
{
	/*------------------------------------------------------------------*/
	/*Ez a rész az adatok beolvasására szolgál. Miután egy láncolt listát készítettünk,
	Egy pointer helyfoglalással annyi elem számára készítünk egy tömböt, amennyi szükséges az
	adatok tárolására. Amikor a tárolásuk megtörént, töröljük a láncolt lista minden helyfoglalását*/
	setlocale(LC_ALL, "");
	FILE* beolvas;
	beolvas = fopen("melyseg.txt", "r");
	Adatok* lista, *elso, *temp, *adatok;
	char sor[100];
	fgets(sor, sizeof(sor), beolvas);
	lista = malloc(sizeof(Adatok));
	int szam, szamlalo =0;
	szam = atoi(sor);
	lista = feltoltes(lista, szam, szamlalo);
	szamlalo++;
	elso = lista;
	while (fgets(sor, sizeof(sor), beolvas))
	{
		szam = atoi(sor);
		lista = feltoltes(lista, szam, szamlalo);
		szamlalo++;
	}
	fclose(beolvas);
	
	adatok = (Adatok*)malloc(szamlalo * sizeof(Adatok));
	Adatok* elem;
	szam = 0;
	for (elem = elso; elem !=NULL; elem = elem->kovetkezo)
	{
		adatok[szam].melyseg = elem->melyseg;
		adatok[szam].sorszam = elem->sorszam;
		adatok[szam].kovetkezo = NULL;
		szam++;
	}
	elem = elso;
	Torles(elso);
	/*------------------------------------------------------------------*/



	/*-------------------1. feladat-------------------------------------*/
	printf("1. feladat\nA fájl adatainak száma : %d \n\n", szamlalo);
	/*-------------------1. feladat vége--------------------------------*/



	/*-------------------2. feladat-------------------------------------*/
	int bekert, i=0;
	printf("2. feladat\nAdjon meg egy távolságértéket: "); scanf("%d", &bekert);
	short meret = adatok[bekert].melyseg;
	printf("Ezen a helyen a felszín %d méter mélyen van.\n\n",meret);
	/*-------------------2. feladat vége--------------------------------*/



	/*-------------------3. feladat-------------------------------------*/
	short ures = 0;
	for (int i = 0; i < szamlalo; i++)
	{
		if (adatok[i].melyseg == 0)
		{
			ures++;
		}
	}
	float u, sz, szazalek;
	u = (float)ures;
	sz = (float)szamlalo;
	szazalek = (float)ures/szamlalo;
	printf("3. feladat\nAz érintetlen terület aránya %.2f %%", szazalek*100);
	/*-------------------3. feladat vége--------------------------------*/



	/*-------------------4. feladat-------------------------------------*/
	FILE* kiiras;
	kiiras = fopen("gödrök.txt", "w");
	int elozo = 1;
	int elsoSzam=0;
	int godrokszama = 0;
	for (i = 0; i < szamlalo; i++)
	{
		if (adatok[i].melyseg != 0)
		{
			godrokszama++;
			elsoSzam = i+1;
			fprintf(kiiras, "%d ", adatok[i].melyseg);
			break;
		}
	}
	for (i = elsoSzam; i < szamlalo; i++)
	{
		if (elozo == 0 && adatok[i].melyseg != 0)
		{
			fprintf(kiiras, "\n");
			elozo = 1;
			godrokszama++;
		}
		if (elozo == 1 && adatok[i].melyseg != 0)
		{
			fprintf(kiiras, "%d ", adatok[i].melyseg);
		}
		if (elozo == 1 && adatok[i].melyseg == 0)  elozo = 0;

	}
	fclose(kiiras);
	/*-------------------4. feladat vége--------------------------------*/



	/*-------------------5. feladat-------------------------------------*/
	printf("\n\n5. feladat\nA gödrök száma: %d", godrokszama);
	/*-------------------5. feladat vége--------------------------------*/



	if (meret > 0)
	{
		int elsoMelyseg = 0, utolsoMelyseg = 0;
		printf("\n\n6. feladat:\n");
		/*----------------6. |a|-----------------------------------------*/
		for (i = bekert; i >= 0; i--)
		{
			if (adatok[i].melyseg == 0)
			{
				elsoMelyseg = i + 1;
				break;
			}
		}
		for (i = bekert - 1; i < szamlalo; i++)
		{
			if (adatok[i].melyseg == 0)
			{
				utolsoMelyseg = i - 1;
				break;
			}
		}
		printf("a)\nA gödör kezdete: %d méter, a gödör vége: %d méter. ", elsoMelyseg + 1, utolsoMelyseg + 1);
		/*----------------6. |a| vége------------------------------------*/


		/*----------------6. |b|-----------------------------------------*/
		int max = -1, index, monNo = 1, monCsokken = 1, monCsMax = -1000, monCsMin = 1000;
		for (i = elsoMelyseg; i <= utolsoMelyseg - 1; i++)
		{
			if (adatok[i].melyseg > max)
			{
				max = adatok[i].melyseg;
				index = i;

			}
		}


		for (i = index; i >= elsoMelyseg; i--)
		{
			if (adatok[i].melyseg < monCsMin)
			{
				monCsMin = adatok[i].melyseg;
			}
			if (adatok[i].melyseg > monCsMax)
			{
				monCsokken = 0;
				break;
			}
		}
		for (i = index; i < utolsoMelyseg; i++)
		{
			if (adatok[i].melyseg > monCsMax)
			{
				monCsMax = adatok[i].melyseg;
			}
			if (adatok[i].melyseg < monCsMax)
			{
				monNo = 0;
				break;
			}

		}
		if (monCsokken == 1)printf("\nb)\nFolyamatosan mélyül\n");
		else if (monNo == 1)printf("\nb)\nFolyamatosan mélyül\n");
		else printf("\nb)\nNem mélyül folyamatosan\n");
		/*----------------6. |b| vége------------------------------------*/



		/*----------------6. |c|-----------------------------------------*/
		printf("c)\nA legnagyobb mélysége: %d méter\n", max);
		/*----------------6. |c| vége------------------------------------*/



		/*----------------6. |d|-----------------------------------------*/
		int osszSzelesseg = 0;
		for (int i = elsoMelyseg; i <= utolsoMelyseg; i++)
		{
			osszSzelesseg += adatok[i].melyseg;
		}
		int godor = 0;
		printf("d)\nTérfogata: %d m^3 méter\n", osszSzelesseg * 10);
		/*----------------6. |d| vége------------------------------------*/


		
		/*----------------6. |e|-----------------------------------------*/
		for (int i = elsoMelyseg; i <= utolsoMelyseg; i++)
		{
			godor++;
		}
		printf("e)\nA vízmennyiség: %d m^3 méter", ((osszSzelesseg) * 10) - (godor * 10));
		/*----------------6. |e| vége------------------------------------*/
	}


	/*----------------6., ha nulla az adat------------------------------------*/
	else
	{
		printf("\n\n6.feladat\nAz adott helyen nincs gödör");
	}
	getch();
	return 0;
}

//Láncolt lista feltöltése folyamatos beolvasással
Adatok* feltoltes(Adatok* adat, int melyseg, int sorszam)
{
	Adatok* temp = (Adatok*)malloc(sizeof(Adatok));
	temp->melyseg = melyseg;
	temp->sorszam = sorszam;
	temp->kovetkezo = NULL;
	adat->kovetkezo = temp;
	return temp;
}

//Láncolt lista pointer helyfoglalásainak törlése, felszabadításaa
void Torles(Adatok* adat)
{
	Adatok* a, *temp;
	a = adat;
	while (a != NULL)
	{
		temp = a;
		a = a->kovetkezo;
		free(temp);
		
	}
}