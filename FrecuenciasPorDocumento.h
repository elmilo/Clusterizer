#ifndef FRECUENCIASPORDOCUMENTO_H_INCLUDED
#define FRECUENCIASPORDOCUMENTO_H_INCLUDED

class FrecuenciasPorDocumento{
    float freq; //guarda la frecuencia en un solo documento

public:

/**
* Constructor:
*/
FrecuenciasPorDocumento();

/**
* Para incrementar la frecuencia de una palabra
*/
void aumentarFrecuencia();

/**
* Se puede utilizar para obtener la frecuencia total por palabra 
* en todos los documento
*/
unsigned int getFrecuencia();

};

#endif
