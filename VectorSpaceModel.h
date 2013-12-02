#ifndef VECTORSPACEMODEL_H_
#define VECTORSPACEMODEL_H_

#include "Diccionario.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

#include <math.h>

#include "TiposGlobales.h"

using namespace std;
//using namespace Eigen;

class VectorSpaceModel {
		
private:
	
	typedef struct Nodo {
		string token;
		TipoGuardado idf;
		} algoparacompletar;

	//Guarda las palabras nuevamente... pensar si no conviene usar el diccionario en vez
	vector<Nodo> palabras;
	vector<Nodo> palabrasDeDisco;

	//Diccionario para encontrar las palabras. HAY QUE SACAR ESTA POROG
	Diccionario* miDiccionario;
	//hay un vector por documento

	TipoMatriz matriz;
	//Guarda la cantidad de documentos para la matriz
	unsigned cantDocs;
	unsigned cantTerminos;
	
	void llenarPalabras();
	void llenarMatrizConTFIDF();
	int bbinaria(const std::string unaPalabra);
	void limpiarMatriz();
	
public:
	VectorSpaceModel();
	VectorSpaceModel(Diccionario *miDiccionario, unsigned cantDocuments);
	void procesarDocumentos();
	
	TipoMatriz getMatriz() const;
	/*void haciaDisco();
	void desdeDisco();*/
};

#endif /* VECTORSPACEMODEL_H_ */
