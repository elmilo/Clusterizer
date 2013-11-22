#ifndef DICCIONARIO_H_INCLUDED
#define DICCIONARIO_H_INCLUDED

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <set>

#include "FrecuenciasPorDocumento.h"

using namespace std;

/**
 * Tipos personalizados: 
*          - un mapa con docIDs (unsigned) y clase FrecuenciasPorDocumento
*          - otro mapa con strings de palabras y el anterior.
 * */
typedef std::map<unsigned, FrecuenciasPorDocumento> listaD;
typedef std::map<string, listaD> mapaDelDiccionario;


class Diccionario{

public:

mapaDelDiccionario diccionario;

unsigned getCantTerminos();



/**
 * Trata de insertar una palabra si corresponde, si no actualiza la lista
 * */
       
void agregarTermino(std::string palabra, unsigned unDocID);

/**
 * TEMPORAL
 * */
void mostrar();
    
};

#endif
