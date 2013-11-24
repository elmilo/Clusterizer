#ifndef TOKENIZER_H_INCLUDED
#define TOKENIZER_H_INCLUDED

#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>

#include <locale>
#include <algorithm>

#include <list>
#include <string>
#include <vector>
#include <set>


using namespace std;

class Tokenizer{

public:
Tokenizer(std::string direccionArchivo);

bool tengaTerminos();

string siguienteTermino();


private:
    set<string> StopWords; //Guarda las stopwords
    list<string> TokenList; //Guarda los tokens
    const char* direccion; //Direccion del archivo que se parsea

void agregarEnContenedor(string entrada);

bool perteneceAlfabeto (string entrada);

void inicializar(string direccionArchivo);

bool setearStopWords();

int separarTokens();

};

#endif
