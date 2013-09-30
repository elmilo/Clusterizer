#ifndef LISTADORDEARCHIVOS_H_INCLUDED
#define LISTADORDEARCHIVOS_H_INCLUDED

#define SEPARADOR_DIR "/"

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <fstream>
#include <dirent.h>
#include <vector>
#include <algorithm> 


using namespace std;

class ListadorDeArchivos{

private:

vector<string> docIDs; //guarda los archivos que van a ser leidos
const char * raizPpal; //raiz principal: la que se pasa para leer los archivos
string raizPpalStr;
unsigned largoRaizStr; //tamanio del string de la raiz principal

/**
 * Filtra los directorios y los archivos
 * */
int filtro(const struct dirent * dire, const char* raiz);

/**
 * Borra la raiz antes de ser guardada en el vector, para que se devuelva el directorio
 * en consideracion
 * */
string sacarRaizPpal (string unArchivo);

//No se usa.
bool filtrarDirectorios(const struct dirent * dire, const char* raiz);

/**
 * Se llama recursivamente para obtener los archivos de los subdirectorios
 * */
void listarArchivos(const char* unDirectorio);

public:

//Constructor: inspecciona el directorio y deja ordenado el vector
ListadorDeArchivos (string directorio);

//Obtener tamanio del vector
unsigned tamanio();

//Obtener un elemento del vector
string documento(unsigned int i);
};

#endif
