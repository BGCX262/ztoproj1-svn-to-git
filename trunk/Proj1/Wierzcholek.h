#pragma once

/*
	klasa wierzcho�ka
 */
class Wierzcholek
{
public:
	// konstruktor kopiuj�cy oraz operator przypisania rzucaj� wyj�tkami z prawdopodobie�stwem p
	static double p;

	static int faktycznaLiczba;
	static int szacowanaLiczba;

	// konstruktor domy�lny - gwarancja silna oraz niezg�aszania wyj�tk�w,
	Wierzcholek() throw();

	Wierzcholek(double, int) throw();
	
	// destruktor - gwarancja silna oraz niezg�aszania wyj�tk�w,
	~Wierzcholek() throw() {};

	// konstruktor kopiuj�cy - gwarancja silna, rzuca wyj�tkami z prawdopodobie�stwem p
	Wierzcholek(const Wierzcholek &);

	// operator przypisania - gwarancja silna, rzuca wyj�tkami z prawdopodobie�stwem p
	Wierzcholek & operator=(const Wierzcholek &);

	bool operator<(const Wierzcholek &) const;

	// unikatowy numer zadania (i)
	int i;

	// pole przechowuj�ce liczb� godzin (liczba zmiennoprzecinkowa)
	double h;

	// pole przechowuj�ce informacj� o liczbie os�b (liczba ca�kowita)
	int n;

private:
	// do przechowywania ostatnio nadanego identyfikatora
	static int ostatnieI;

	void _copy(const Wierzcholek &);
};

int Wierzcholek::ostatnieI = 0;

Wierzcholek::Wierzcholek() throw()
{
	i = (++ostatnieI); // nadajemy numer kolejny
	h = (double)(rand()%50) + 1;
	n = rand()%50 + 1;
	Wierzcholek::faktycznaLiczba++;
}

Wierzcholek::Wierzcholek(double h, int n) throw() : h(h), n(n)
{
	i = (++ostatnieI); // nadajemy numer kolejny
	Wierzcholek::faktycznaLiczba++;
}

Wierzcholek::Wierzcholek(const Wierzcholek & inny)
{
	_copy(inny);
	Wierzcholek::faktycznaLiczba++;
}

Wierzcholek & Wierzcholek::operator=(const Wierzcholek & inny)
{
	// kazemy operatorowi przypisania zachowywac sie jak konstruktor kopiujacy
	_copy(inny);
	return *this;
}

void Wierzcholek::_copy(const Wierzcholek & inny)
{
	// gwarancja silna - rzucamy wyjatek zanim cos zmienimy
	if(!PROBUJ(p))
		throw BladKopiiWierzcholka<Wierzcholek>(inny.i);

	// przepisujemy wartosci
	i = inny.i;
	h = inny.h;
	n = inny.n;
}

bool Wierzcholek::operator<(const Wierzcholek & inny) const
{
	return i < inny.i;
}

int BladKopiiWierzcholka<Wierzcholek>::licznik = 0;

int Wierzcholek::faktycznaLiczba = 0;
int Wierzcholek::szacowanaLiczba = 0;
