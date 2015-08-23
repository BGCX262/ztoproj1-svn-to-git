#pragma once

template <class V>
class AcyklicznyPodgraf
{
public:
	AcyklicznyPodgraf();
	~AcyklicznyPodgraf();
	void Zawolaj(Graf<V> &);
private:
	int _zrodlo;
	int _ujscie;
	typedef list<int>::iterator listIt;

	void _Dfs(Graf<V> &);
	void _DfsVisit(Graf<V> &, int, list<int> &, list<int> &);
	void _ZnajdzUjscie(Graf<V> &);
	void _ZnajdzZrodlo(Graf<V> &);
	bool _ZnajdzNaLiscie(list<int> &, int);

};

template <class V>
AcyklicznyPodgraf<V>::AcyklicznyPodgraf()
{
}

template <class V>
AcyklicznyPodgraf<V>::~AcyklicznyPodgraf()
{
}

template <class V>
void AcyklicznyPodgraf<V>::Zawolaj(Graf<V> & G)
{
	_Dfs(G);
	_ZnajdzUjscie(G);
	_ZnajdzZrodlo(G);
}

//metoda wywoluje _DfsVisit dla wszystkich zrodel w grafie
template <class V>
void AcyklicznyPodgraf<V>::_Dfs(Graf<V> & G)
{
	list<int> odwiedzone;
	list<int> sciezka;
	list<int> wierzcholki = G.PobierzWierzcholki();
	list<int>::iterator it;
	for (it = wierzcholki.begin(); it != wierzcholki.end(); it++)
	{
		if (!_ZnajdzNaLiscie(odwiedzone, *it))
			_DfsVisit(G, *it, odwiedzone, sciezka);
		
	}
}

/*
	rekurencyjna metoda odwiedza wierzcholek v
	jezeli na dotychczasowej sciezce byl juz wierzcholek v, to usun krawedz, ktora tu przyprowadzila
	odwiedz wszystkich sasiadow v, oznacz jako odwiedzony
*/
template <class V>
void AcyklicznyPodgraf<V>::_DfsVisit(Graf<V> & G, int v, list<int> & odwiedzone, list<int> & sciezka)
{
	if (_ZnajdzNaLiscie(sciezka, v))
	{
		G.UsunKrawedz(sciezka.back(), v);
		return;
	}
	
	sciezka.push_back(v);
	list<int> sasiedzi = G.PobierzSasiadow(v);
	for (listIt it = sasiedzi.begin(); it != sasiedzi.end(); it++)
	{
		if( !_ZnajdzNaLiscie(odwiedzone, *it))
			_DfsVisit(G, *it, odwiedzone, sciezka);
	}
	sciezka.pop_back();
	odwiedzone.push_back(v);
}



//metoda znajduje pierwsze ujscie w grafie a pozostale likwiduje
template <class V>
void AcyklicznyPodgraf<V>::_ZnajdzUjscie(Graf<V> & G)
{
	_ujscie = 0;
	list<int> sasiedzi;

	list<int> wierzcholki = G.PobierzWierzcholki();
	list<int>::iterator it;
	for (it = wierzcholki.begin(); it != wierzcholki.end(); it++)
	{
		sasiedzi = G.PobierzSasiadow(*it);
		if(sasiedzi.empty())
		{
			if(!_ujscie)
				_ujscie = *it;
			else
				G.DodajKrawedz(*it, _ujscie);
		}
	}
	G.UstawUjscie(_ujscie);
}

//metoda znajduje pierwsze zrodlo w grafie a pozostale likwiduje
template <class V>
void AcyklicznyPodgraf<V>::_ZnajdzZrodlo(Graf<V> & G)
{
	_zrodlo = 0;
	list<int> sasiedzi;
	
	list<int> wierzcholki = G.PobierzWierzcholki();
	list<int>::iterator it1;
	for (it1 = wierzcholki.begin(); it1 != wierzcholki.end(); it1++)
	{
		list<int>::iterator it2;
		for (it2 = wierzcholki.begin(); it2 != wierzcholki.end(); it2++)
		{
			sasiedzi = G.PobierzSasiadow(*it2);
			if (_ZnajdzNaLiscie(sasiedzi, *it1))
				break;
		}

		if (it2 == wierzcholki.end()) //znaleziono zrodlo
		{
			if(!_zrodlo)
				_zrodlo = *it1;
			else
				G.DodajKrawedz(_zrodlo, *it1);
		}
	}
	G.UstawZrodlo(_zrodlo);
}

//metoda srawdza czy wartosc i znajduje sie na liscie lista
template <class V>
bool AcyklicznyPodgraf<V>::_ZnajdzNaLiscie(list<int> & lista, int i)
{
	for (listIt it = lista.begin(); it != lista.end(); it++)
		if ( *it == i )
			return true;
	return false;
}
