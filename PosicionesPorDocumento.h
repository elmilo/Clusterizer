#ifndef POSICIONESPORDOCUMENTO_H_INCLUDED
#define POSICIONESPORDOCUMENTO_H_INCLUDED

#include "common.h"


using namespace std;

class PosicionesPorDocumento{
    unsigned int freq; //guarda la frecuencia de un solo documento
    list<unsigned int> posiciones; //lista de ocurrencias

public:

/**
* Constructores:
*/
PosicionesPorDocumento(unsigned int primera);
PosicionesPorDocumento();

void insertarPosicion(unsigned int una);

/**
* Se puede utilizar para obtener la frecuencia total por palabra 
* en todos los documento
*/
unsigned int getFrecuencia();

/**
* TEMPORAL
*/
void mostrarPosiciones();
};

#endif
