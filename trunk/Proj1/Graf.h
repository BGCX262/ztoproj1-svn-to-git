#pragma once

template <class V>
class Graf
{
public:
	static double q;

	static int faktycznaLiczba;
	static int szacowanaLiczba;

	Graf();
	~Graf();

	Graf(const Graf<V> &);
	Graf<V> & operator=(const Graf<V> &);

	bool SprawdzWierzcholek(int);
	bool SprawdzKrawedz(int, int);
	void DodajKrawedz(int, int) throw(BrakWierzcholka);
	void UsunKrawedz(int, int) throw(BrakWierzcholka);

	void DodajWierzcholek(V&);
	void UsunWierzcholek(int) throw(BrakWierzcholka);
	void DodajKrawedz(V&, V&);

	list<int> & PobierzSasiadow(int) throw(BrakWierzcholka);
	int PobierzZrodlo();
	int PobierzUjscie();
	void UstawZrodlo(int);
	void UstawUjscie(int);
	V& PobierzWierzcholek(int);
	list<int> PobierzWierzcholki();

	bool ZnajdzSciezke(int, int);
	void PolaczWierzcholki(int, int);

	static V & PobierzDane(int);
	void ZapiszStrukture();
	int LiczbaWierzcholkow();

private:
	typedef map<int, list<int>> lSasiedztwa;
	typedef typename lSasiedztwa::const_iterator lSasiedztwaIt;
	typedef map<int, V> lWierzcholkow;
	typedef typename lWierzcholkow::const_iterator lWierzcholkowIt;

	void _copy(const Graf<V> &);

	static V & _PobierzDane(int);
	void _ZapiszStrukture();

	lSasiedztwa _listaSasiedztwa;
	lWierzcholkow _wierzcholki;
	int _zrodlo;
	int _ujscie;
};

template <class V>
Graf<V>::Graf()
{
	srand((unsigned int) time(NULL));
	Graf<V>::faktycznaLiczba++;
}

template <class V>
Graf<V>::~Graf()
{
}

template <class V>
Graf<V>::Graf(const Graf<V> & inny)
{
	Graf<V>::faktycznaLiczba++;
	_copy(inny);
}

template <class V>
Graf<V> & Graf<V>::operator=(const Graf<V> & inny)
{
	_copy(inny);
	return *this;
}

template <class V>
void Graf<V>::_copy(const Graf<V> & inny)
{
	// przepisujemy wartosci
	bool result;
	do
	{
		result = true;
		try
		{
			_listaSasiedztwa.clear();
			_listaSasiedztwa.insert(inny._listaSasiedztwa.begin(), inny._listaSasiedztwa.end());
		}
		catch(BladKopiiWierzcholka<V> e)
		{
			result = false;
		}
	}
	while(!result);

	do
	{
		result = true;
		try
		{
			_wierzcholki.clear();
			_wierzcholki.insert(inny._wierzcholki.begin(), inny._wierzcholki.end());
		}
		catch(BladKopiiWierzcholka<V> e)
		{
			result = false;
		}
	}
	while(!result);

	_zrodlo = inny._zrodlo;
	_ujscie = inny._ujscie;
}

template <class V>
void Graf<V>::DodajKrawedz(V & lewy, V & prawy)
{
	DodajWierzcholek(lewy);
	DodajWierzcholek(prawy);

	bool result;
	do
	{
		result = true;
		try
		{
			_listaSasiedztwa[lewy.i].push_back(prawy.i);
		}
		catch (...)
		{
			result = false;
		}
	}
	while(!result); // powtarzamy w przypadku bledu
}

template <class V>
bool Graf<V>::SprawdzWierzcholek(int wierzcholek)
{
	return (_wierzcholki.find(wierzcholek) != _wierzcholki.end());
}

template <class V>
bool Graf<V>::SprawdzKrawedz(int lewy, int prawy)
{
	for (list<int>::iterator it = _listaSasiedztwa[lewy].begin(); 
		it != _listaSasiedztwa[lewy].end();
		it++)
		if (*it == prawy)
			return true;
	return false;
}

template <class V>
void Graf<V>::DodajKrawedz(int lewy, int prawy) throw(BrakWierzcholka)
{
	if(!SprawdzWierzcholek(lewy))
		throw BrakWierzcholka(lewy);
	if(!SprawdzWierzcholek(prawy))
		throw BrakWierzcholka(prawy);

	bool result;
	do
	{
		result = true;
		try
		{
			_listaSasiedztwa[lewy].push_back(prawy);
		}
		catch (...)
		{
			result = false;
		}
	}
	while(!result); // powtarzamy w przypadku bledu
}

template <class V>
void Graf<V>::UsunKrawedz(int lewy, int prawy) throw(BrakWierzcholka)
{
	if(!SprawdzWierzcholek(lewy))
		throw BrakWierzcholka(lewy);
	if(!SprawdzWierzcholek(prawy))
		throw BrakWierzcholka(prawy);
	
	bool result;
	do
	{
		result = true;
		try
		{
			_listaSasiedztwa[lewy].remove(prawy);
		}
		catch (...)
		{
			result = false;
		}
	}
	while(!result); // powtarzamy w przypadku bledu
}

template <class V>
void Graf<V>::DodajWierzcholek(V & wierzcholek)
{
	bool result;
	do
	{
		result = true;
		try
		{
			// dodajemy wierzcholek tylko jesli jeszcze go nie ma
			if(_wierzcholki.find(wierzcholek.i) == _wierzcholki.end())
			{
				_wierzcholki.insert(make_pair(wierzcholek.i, wierzcholek));
				V::szacowanaLiczba += 4; // insert i make_pair przekazuja przez wartosc - 4 kopiowania
			}
		}
		catch (...)
		{
			result = false;
		}
	}
	while(!result); // moze byc wyjatek - powtarzamy do skutku
}

template<class V>
void Graf<V>::UsunWierzcholek(int wierzcholek) throw(BrakWierzcholka)
{
	if(!SprawdzWierzcholek(wierzcholek))
		throw BrakWierzcholka(wierzcholek);

	_wierzcholki.erase(wierzcholek);
	_listaSasiedztwa.erase(wierzcholek);
}

template<class V>
list<int> & Graf<V>::PobierzSasiadow(int wierzcholek) throw(BrakWierzcholka)
{
	if(!SprawdzWierzcholek(wierzcholek))
		throw BrakWierzcholka(wierzcholek);

	return _listaSasiedztwa[wierzcholek];//.find(wierzcholek);
}

template<class V>
int Graf<V>::PobierzUjscie() { return _ujscie; }

template<class V>
int Graf<V>::PobierzZrodlo() { return _zrodlo; }

template<class V>
void Graf<V>::UstawUjscie(int ujscie) { _ujscie = ujscie; }

template<class V>
void Graf<V>::UstawZrodlo(int zrodlo) { _zrodlo = zrodlo; }

template<class V>
int Graf<V>::LiczbaWierzcholkow() { return _wierzcholki.size(); }

template<class V>
V& Graf<V>::PobierzWierzcholek(int i)
{
	if(!SprawdzWierzcholek(i))
		throw BrakWierzcholka(i); // ?

	return _wierzcholki[i];
}

template<class V>
list<int> Graf<V>::PobierzWierzcholki()
{
	list<int> result;
	for (lWierzcholkowIt it = _wierzcholki.begin(); it != _wierzcholki.end(); it++)
		result.push_back(it->first);
	return result;
}

/*
	metoda sprawdza czy istnieje sciezka skierowana
	od wierzcholka v do u
*/
template<class V>
bool Graf<V>::ZnajdzSciezke(int v, int u)
{
	list<int>::iterator it;
	for (it = _listaSasiedztwa[v].begin(); it != _listaSasiedztwa[v].end(); it++)
	{
		if ((*it) == u)
			return true;
		else
			ZnajdzSciezke((*it), u);
	}
	return false;
}

/*
	metoda dodaje do v krawedzie wchodzace do u i wychodzace z u
	oblicza nowe wartosci dla v, modyfikuje _zrodlo i _ujscie jezeli potrzeba
	usuwa wierzcholek u
*/
template <class V>
void Graf<V>::PolaczWierzcholki(int v, int u)
{
	list<int>::iterator it;
	lSasiedztwaIt lit;
	
	// wszystkie krawedzie wychodzace z u wychodza teraz z v
	for (it = _listaSasiedztwa[u].begin(); it != _listaSasiedztwa[u].end(); it++)
	{
		if ((*it) != v && !SprawdzKrawedz(v, (*it)))
			DodajKrawedz(v, (*it));
	}
	
	// wszystkie krawedzie wchodzace do u wchodza teraz do v
	for (lit = _listaSasiedztwa.begin(); lit != _listaSasiedztwa.end(); lit++)
		for (it = _listaSasiedztwa[lit->first].begin(); it != _listaSasiedztwa[lit->first].end(); it++)
		{
			if(*it == u)
			{
				if ((lit->first) != v && !SprawdzKrawedz(lit->first, v))
					*it = v;
			}
		}

	// policz wartosci na nowo
	_wierzcholki[v].i = v;
	_wierzcholki[v].n = _wierzcholki[v].n + _wierzcholki[u].n;
	_wierzcholki[v].h = (_wierzcholki[v].n*_wierzcholki[v].h + _wierzcholki[u].n*_wierzcholki[u].h) / (_wierzcholki[v].n + _wierzcholki[u].n);

	// jezeli u bylo zrodlem lub ujsciem, to jest nim teraz v
	if (u == _zrodlo)
		_zrodlo = v;
	if (u == _ujscie)
		_ujscie = v;

	// usun wierzcholek u
	_listaSasiedztwa.erase(u);

	lSasiedztwa::iterator sit;
	for(sit = _listaSasiedztwa.begin(); sit != _listaSasiedztwa.end(); sit++)
		(sit->second).remove(u);

	_wierzcholki.erase(u);
}

/*
	pobranie informacji (n,h) dla zadania o numerze i (np. z bazy danych)
	nale¿y zapewniæ gwarancje siln¹ - metoda rzuca wyj¹tkami z prawdopodobieñstwem q
*/
// metoda prywatna, rzucajaca wyjatkami
template <class V>
V & Graf<V>::_PobierzDane(int i)
{
	if(!PROBUJ(q))
		throw BladOdczytuGrafu(i);

	return File<V>::Read(i);
}

// metoda publiczna, probujaca wywolac wlasciwa metode ponownie w przypadku bledu
template <class V>
V & Graf <V>::PobierzDane(int i)
{
	while(true) // probujemy do skutku
	{
		try
		{
			return _PobierzDane(i);
		}
		catch (...) {}
	}
}

/*
	wstawienie informacji o grafie (np. do bazy danych)
	nale¿y zapewniæ gwarancje siln¹ - metoda rzuca wyj¹tkami z prawdopodobieñstwem q
*/
// metoda prywatna, rzucajaca wyjatkami
template <class V>
void Graf<V>::_ZapiszStrukture()
{
	if(!PROBUJ(q))
		throw BladZapisuGrafu();

	lWierzcholkowIt it;
	for(it = _wierzcholki.begin(); it != _wierzcholki.end(); ++it)
		File<V>::Write(it->second, PobierzSasiadow(it->first));
}

// metoda publiczna, probujaca wywolac wlasciwa metode ponownie w przypadku bledu
template <class V>
void Graf <V>::ZapiszStrukture()
{
	bool result;
	do // probujemy do skutku
	{
		result = true;
		try
		{
			return _ZapiszStrukture();
		}
		catch (BladZapisuGrafu ex)
		{
			result = false;
		}
	}
	while(!result);
}

int BladOdczytuGrafu::licznik = 0;
int BladZapisuGrafu::licznik = 0;
int BrakWierzcholka::licznik = 0;

int Graf<Wierzcholek>::faktycznaLiczba = 0;
int Graf<Wierzcholek>::szacowanaLiczba = 0;
