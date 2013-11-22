#ifndef TOKENIZER_H_INCLUDED
#define TOKENIZER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <search.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <list>

#include <string>
#include <iostream>


#include <vector>
#include <fstream>
#include <iterator>
#include <set>
#include <algorithm>

using namespace std;

class Tokenizer{


public:
Tokenizer(std::string direccionArchivo);

bool tengaTerminos();

string siguienteTermino();



private:
    set<string> StopWords;
    static const char* delim;
    list<string> posiciones;
    const char* direccion;

void agregarEnContenedor(char *palabra);

bool esLetraAlfabeto (string entrada);

void inicializar(string direccionArchivo);

bool setearStopWords();
/**
 * Codigo C
 * */
int separarTokens();

};

#endif
