#include "Proj1.h"

using namespace std;

int main()
{
	//long tick = GetTickCount();
	Graf<Wierzcholek> g1, g2;
	Graf<Wierzcholek>::szacowanaLiczba += 2;

	// demonstracja operacji tworzenia grafu
	//Wierzcholek w1(1, 2);
	//Wierzcholek w2(2, 3);
	//Wierzcholek::szacowanaLiczba += 2;

	/*g1.DodajWierzcholek(w1);
	g1.DodajWierzcholek(w2);

	g1.DodajKrawedz(1, 2);
	g1.UsunKrawedz(1, 2);

	g1.ZapiszStrukture();*/

	// demonstracja implementacji generatora, sciezki krytycznej i skracania
	GeneratorGrafu<Wierzcholek> generator;
	generator.GenerujGraf(g2, 25);
	AcyklicznyPodgraf<Wierzcholek> acykl;
	acykl.Zawolaj(g2);

	SciezkaKrytyczna<Wierzcholek> sciezka(g2);
	sciezka.SkracajSciezke();

	// zliczanie wyjatkow

	licz_wyjatki();

	//cout << endl << "Czas wykonania: " << (GetTickCount() - tick) << " ms";
	cin.get();
	return EXIT_SUCCESS;
}

void licz_wyjatki()
{
	cout << "Zestawienie bledow:" << endl;
	cout << "- kopiowanie wierzcholkow:\t" << BladKopiiWierzcholka<Wierzcholek>::licznik << endl;
	cout << "- odczyt wierzcholkow:\t\t" << BladOdczytuGrafu::licznik << endl;
	cout << "- zapis struktury grafu:\t" << BladZapisuGrafu::licznik << endl;
	cout << endl;
	cout << "Zestawienie instancji Graf<Wierzcholek>:" << endl;
	cout << "- liczba szacowana:\t" << Graf<Wierzcholek>::szacowanaLiczba << endl;
	cout << "- liczba faktyczna:\t" << Graf<Wierzcholek>::faktycznaLiczba << endl;
	cout << endl;
	cout << "Zestawienie instancji Wierzcholek:" << endl;
	cout << "- liczba szacowana:\t" << Wierzcholek::szacowanaLiczba << endl;
	cout << "- liczba faktyczna:\t" << Wierzcholek::faktycznaLiczba << endl;
}
