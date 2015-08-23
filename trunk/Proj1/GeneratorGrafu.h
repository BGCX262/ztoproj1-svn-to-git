#pragma once

template <class V>
class GeneratorGrafu
{
public:
	GeneratorGrafu();
	~GeneratorGrafu();
	void GenerujGraf(Graf<V> &, int);

private:
	int _n;
	int _m;

	void _IloscKrawedzi();
	void _DodajWierzcholki(Graf<V> &);
	void _DodajKrawedzie(Graf<V> &);

};

template <class V>
GeneratorGrafu<V>::GeneratorGrafu()
{
	srand((unsigned int) time(NULL));
}

template <class V>
GeneratorGrafu<V>::~GeneratorGrafu()
{

}

/*
	metoda glowna generujaca graf
	wywoluje odpowiednie prywatne metody
*/
template <class V>
void GeneratorGrafu<V>::GenerujGraf(Graf<V> & G, int n)
{
	_n = n;
	_DodajWierzcholki(G);
	_DodajKrawedzie(G);
}

//metoda dodaje n wierzcholkow
template <class V>
void GeneratorGrafu<V>::_DodajWierzcholki(Graf<V> & G)
{
	for (int i = 0; i < _n; i++)
	{
		V v;
		V::szacowanaLiczba++;
		G.DodajWierzcholek(v);
	}
}


//metoda dodaje losowe krawedzie
template <class V>
void GeneratorGrafu<V>::_DodajKrawedzie(Graf<V> & G)
{
	_IloscKrawedzi();
	int lewy, prawy;
	for (int i = 0; i < _m; i++)
	{	
		do
		{
			lewy = rand() % _n + 1;
			prawy = rand() % _n + 1;
		} while (lewy == prawy || G.SprawdzKrawedz(lewy, prawy)
			|| !G.SprawdzWierzcholek(lewy) || !G.SprawdzWierzcholek(prawy));
		G.DodajKrawedz(lewy, prawy);
	}
}

//metoda losuje ilosc krawedzi
template <class V>
void GeneratorGrafu<V>::_IloscKrawedzi()
{
	float gestosc;
	gestosc = (float)rand() / (float)RAND_MAX;
	_m = (int)((_n * (_n - 1) * gestosc) / 2);
}