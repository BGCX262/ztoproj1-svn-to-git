#pragma once

template <class V>
class SciezkaKrytyczna
{
public:
	SciezkaKrytyczna(Graf<V> &);
	~SciezkaKrytyczna();
	void ZnajdzSciezke();
	bool SkrocSciezke();
	void SkracajSciezke();
	double DlugoscSciezkiKrytycznej();

private:
	void _Max(map<int, list<int>> &, int, int);
	double _DlugoscSciezki(list<int>);

	Graf<V> & _graf;
	list<int> _sciezka;

};

template <class V>
SciezkaKrytyczna<V>::SciezkaKrytyczna(Graf<V> & G) : _graf(G)
{
}

template <class V>
SciezkaKrytyczna<V>::~SciezkaKrytyczna()
{
	
}

//metoda znajduje sciezke krytyczna w grafie
template <class V>
void SciezkaKrytyczna<V>::ZnajdzSciezke()
{
	map<int, list<int>> najdluzszeSciezki;
	list<int> sasiedzi = _graf.PobierzSasiadow(_graf.PobierzZrodlo());
	for (list<int>::iterator it = sasiedzi.begin(); it != sasiedzi.end(); it++)
		najdluzszeSciezki[*it].push_back(*it);

	list<int> wierzcholki = _graf.PobierzWierzcholki();

	for (list<int>::iterator it = wierzcholki.begin()++; it != wierzcholki.end(); it++)
	{
		for (list<int>::iterator u = wierzcholki.begin(); u != wierzcholki.end(); u++)
		{
			sasiedzi = _graf.PobierzSasiadow(*u);
			for (list<int>::iterator v = sasiedzi.begin(); v != sasiedzi.end(); v++)
				_Max(najdluzszeSciezki, *u, *v);

		}
	}

	_sciezka = najdluzszeSciezki[_graf.PobierzUjscie()];
}

/*
	metoda przeglada sciezke krytyczna
	laczy dwa wierzcholki jezeli ich polaczenie 
		nie spowoduje powstania cyklu
		nie wydluzy sciezki krytycznej
*/
template <class V>
bool SciezkaKrytyczna<V>::SkrocSciezke()
{
	if (_graf.PobierzZrodlo() == _graf.PobierzUjscie())
		return false;

	int nrV = _graf.PobierzZrodlo();
	list<int>::iterator itU = _sciezka.begin();
	Graf<V> probnyGraf;
	Graf<V>::szacowanaLiczba++;

	while(itU != _sciezka.end())
	{
		if(_graf.ZnajdzSciezke(*itU, nrV))
		{
			nrV = *itU;
			itU++;
			continue; //wez nastepna krawedz jezeli polaczenie utworzy cykl
		}

		probnyGraf = _graf;
		V::szacowanaLiczba += _graf.LiczbaWierzcholkow(); // do probnego grafu bierzemy kopie

		probnyGraf.PolaczWierzcholki(nrV, *itU);
		SciezkaKrytyczna<V> probnaSciezka(probnyGraf);
		probnaSciezka.ZnajdzSciezke();
		if (probnaSciezka.DlugoscSciezkiKrytycznej() < DlugoscSciezkiKrytycznej())
		{
			_graf.PolaczWierzcholki(nrV, *itU);
			ZnajdzSciezke();
			return true;
		}

		nrV = *itU;
		itU++;
	}

	return false;
}

template <class V>
void SciezkaKrytyczna<V>::SkracajSciezke()
{
	ZnajdzSciezke();
	while(SkrocSciezke())
		_graf.ZapiszStrukture();
}

template <class V>
double SciezkaKrytyczna<V>::DlugoscSciezkiKrytycznej()
{
	return _DlugoscSciezki(_sciezka);
}

//metoda robi map[v] = max {map[v], map[u] + v}
template <class V>
void SciezkaKrytyczna<V>::_Max(map<int, list<int>> & mapa, int u, int v)
{
	if (_DlugoscSciezki(mapa[v]) < (_DlugoscSciezki(mapa[u]) + _graf.PobierzWierzcholek(v).h))
	{
		mapa[v] = mapa[u];
		mapa[v].push_back(v);
	}
}

//metoda zwraca dlugosc sciezki zapisanej w lista
template <class V>
double SciezkaKrytyczna<V>::_DlugoscSciezki(list<int> lista)
{
	double result = 0;
	double current = 0;
	bool done;

	for (list<int>::iterator it = lista.begin(); it != lista.end(); it++)
	{
		do
		{
			done = true;
			try
			{
				V & wierzcholek = _graf.PobierzWierzcholek(*it);
				current = wierzcholek.h;
			}
			catch(BladKopiiWierzcholka<V> v)
			{
				done = false;
			}
		}
		while(!done);

		result += current;
	}
	
	//if (result == 0)
	//	return INT_MAX;
	return result;
}
