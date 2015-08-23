#pragma once

using namespace std;

template <class V>
class BladKopiiWierzcholka : public exception
{
public:
	BladKopiiWierzcholka<V>(int wierzcholek) : exception(), wierzcholek(wierzcholek)
	{
		++licznik;
	}

	virtual const char* what () const
	{
		return string("Blad przy kopiowaniu wierzcholka " + wierzcholek).c_str();
	}

	static int licznik;

private:
	int wierzcholek;
};

class BladOdczytuGrafu : public exception
{
public:
	BladOdczytuGrafu(int wierzcholek) : exception(), wierzcholek(wierzcholek)
	{
		++licznik;
	}

	virtual const char* what () const
	{
		return string("Blad przy odczycie informacji o wierzcholku " + wierzcholek).c_str();
	}

	static int licznik;

private:
	int wierzcholek;
};

class BladZapisuGrafu : public exception
{
public:
	BladZapisuGrafu() : exception()
	{
		++licznik;
	}

	virtual const char* what () const
	{
		return "Blad przy zapisie grafu";
	}

	static int licznik;
};

class BrakWierzcholka : public exception
{
public:
	BrakWierzcholka(int wierzcholek) : exception(), wierzcholek(wierzcholek)
	{
		++licznik;
	}

	virtual const char* what () const
	{
		return (string("Brak wierzcholka " + wierzcholek) + " w grafie").c_str();
	}

	static int licznik;

private:
	int wierzcholek;
};
