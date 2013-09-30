#ifndef DICCIONARIO_H_INCLUDED
#define DICCIONARIO_H_INCLUDED

#include "common.h"
#include "PosicionesPorDocumento.h"


/**
 * Tipos personalizados: 
*          - un mapa con docIDs (unsigned) y clase lista de posiciones
*          - otro mapa con strings de palabras y el anterior.
 * */
typedef map<unsigned, PosicionesPorDocumento> listaD;
//typedef vector<PosicionesPorDocumento> listaD;
typedef map<string, listaD> mapaDelDiccionario;


class Diccionario{

mapaDelDiccionario diccionario;


public:

/**
 * Trata de insertar una palabra si corresponde, si no actualiza la lista
 * */
void insertar(palabraPos termino, unsigned unDocID);

/**
 * TEMPORAL
 * */
void mostrar();
    
};

#endif
