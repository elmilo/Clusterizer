#ifndef LOADER_H_INCLUDED
#define LOADER_H_INCLUDED

#define SEPARADOR_DIR "/"

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <fstream>
#include <dirent.h>
#include <algorithm> 
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>

using namespace std;

class Loader {

public:

	/**
	 * Constructor: recibe el directorio y extension (por defecto puede no recibirla).
	 * Inspecciona el directorio y deja ordenada la estructura con los mismos
	 * */
	Loader(string directorio, string extension);

	/**
	 * Obtener un documento en la posiciones deseada
	 * */
	string popDocumento(unsigned unaPos);

	unsigned cantidadDocIDs();
    /*void haciaDisco();
    void desdeDisco();*/
	

private:
	struct datosArchivos{
	    string nombreArchivo;
	    long tamanioArchivo;
		bool operator<(const datosArchivos& a) const{
		        return a.tamanioArchivo < tamanioArchivo;
		    }
	};
	
	vector<datosArchivos> direcciones; //guarda las direcciones de archivos que van a ser leidos

	const char * raizPpal; //raiz principal: la que se pasa para leer los archivos
	string raizPpalStr;
	
	unsigned largoRaizStr; //tamanio del string de la raiz principal

	

	/**
	 * Filtra los directorios y los archivos
	 * */
	int filtroArchivos(const struct dirent * dire, const char* raiz);

	bool filtroExtensiones(string nombreArchivo, string extension);

	/**
	 * Insertar ruta del archivo en la estructura
	 * */
	void insertar(string archivoPorAgregar, string extension, long tamanio);

	/**
	 * Borra la raiz antes de ser guardada en el vector,
	 * para que se devuelva el directorio en consideracion
	 * */
	string sacarRaizPpal(string unArchivo);

	/**
	 * Obtiene todos los archivos de la carpeta a listar.
	 * Se llama recursivamente para obtener los archivos de los subdirectorios
	 * */
	void listarArchivos(const char* unDirectorio, string extension);

	long obtenerTamanioArchivo(std::string direccionArchivo);

};

#endif
