#pragma once

using namespace std;

template <class V>
class File
{
public:
	static void Write(const V &, const list<int> &);
	static V & Read(int);
private:
};

template <class V>
void File<V>::Write(const V & vertex, const list<int> & neighbours)
{
	ofstream stream;

	char * path = new char[255];
	sprintf_s(path, 255, "%s\\data\\%d", _getcwd(NULL, 0), vertex.i);

	stream.open(path);
	stream << vertex.n << " " << vertex.h << endl;
	
	list<int>::const_iterator it;
	for(it = neighbours.begin(); it != neighbours.end(); ++it)
		stream << *it << " ";
	stream << endl;

	stream.close();
	delete[] path;
}

template <class V>
V & File<V>::Read(int i)
{
	ifstream stream;

	char * path = new char[255];
	sprintf_s(path, 255, "%s\\data\\%d", _getcwd(NULL, 0), i);

	stream.open(path);

	double h;
	int n;

	stream >> n >> h;
	stream.close();
	delete[] path;

	return vertex(n, h);
}
