#ifndef VECTORSPACEMODEL_H_
#define VECTORSPACEMODEL_H_

#include "Diccionario.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

#include <eigen3/Eigen/Dense>
#include <math.h>

using namespace std;
using namespace Eigen;

typedef Matrix<float, Dynamic, Dynamic> TipoMatriz;

class VectorSpaceModel {
	
	
private:
	typedef struct Nodo {
		string token;
		float idf;
		};

	//Guarda las palabras nuevamente... pensar si no conviene usar el diccionario en vez
	vector<Nodo> palabras;

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
	VectorSpaceModel(Diccionario *miDiccionario, unsigned cantDocuments);
	void procesarDocumentos();

	//TEMPORAL:
	void mostrarMatriz();
};

#endif /* VECTORSPACEMODEL_H_ */
