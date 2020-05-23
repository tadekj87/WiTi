//WiTi.cpp WiTi : Ten plik zawiera funkcję „main”.W nim rozpoczyna się i kończy wykonywanie programu.
// Grupa: WT 13: Junak Tadeusz, Karol Kędzia

#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

struct Zadanie {
	int czasWykonania, kara, czas;
	Zadanie() { czasWykonania = 0; kara = 0; czas = 0; }
};


int main()
{
	int liczbaDanych;
	ifstream plik;
	int czasWykonania, kara, czas;
	Zadanie zadanie[1000];

	plik.open("dane.txt");
	plik >> liczbaDanych;

	for (int i = 0; i < liczbaDanych; i++)
	{
		plik >> czasWykonania;
		plik >> kara;
		plik >> czas;

		zadanie[i].czasWykonania = czasWykonania;
		zadanie[i].kara = kara;
		zadanie[i].czas = czas;
	}

	int przestrzen = 1 << liczbaDanych;

	int* OPT = new int[przestrzen];

	OPT[0] = 0;
	int bit;
	int Pz;

	for (int i = 1; i < (przestrzen); i++)
	{
		OPT[i] = INT_MAX;
		Pz = 0;
		bit = 1;

		for (int j = 0; j < liczbaDanych; j++)
		{
			if (i & bit)
				Pz += zadanie[j].czasWykonania; 

			bit *= 2;
		}

		bit = 1;

		for (int j = 0; j < liczbaDanych; j++)
		{
			if (i & bit)
			{
				int wiMax=0;

				if ((Pz - zadanie[j].czas)>0)
					wiMax = zadanie[j].kara * (Pz - zadanie[j].czas);

				int ibit = i - bit;

				int OPT_bez_z = OPT[ibit];

				if(OPT[i]>wiMax+OPT_bez_z)
					OPT[i] = wiMax + OPT_bez_z;
			}

			bit *= 2;
		}
	}
	cout << "Czas optymalny to: " << OPT[przestrzen-1] << endl;

	delete[] OPT;

	return 0;
}