#pragma once
#pragma warning(disable: 4290)

#include <iostream>
#include <fstream>
#include <time.h>
#include <map>
#include <list>
#include <string>
#include <algorithm>
#include <direct.h> // _getcwd()
#include <windows.h> // GetTickCount()

#define PROBUJ(val) (((double)rand() / (double)RAND_MAX) > val)

#include "File.h"
#include "Wyjatki.h"
#include "Wierzcholek.h"
#include "Graf.h"
#include "GeneratorGrafu.h"
#include "AcyklicznyPodgraf.h"
#include "SciezkaKrytyczna.h"

double Wierzcholek::p = 0.0; // prawdopodobienstwo wyjatku przy kopiowaniu wierzcholka
double Graf<Wierzcholek>::q = 0.0; // prawdopodobienstwo wyjatku przy odczycie/zapisie grafu

void licz_wyjatki();
