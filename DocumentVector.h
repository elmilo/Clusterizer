/*
 * DocumentVector.h
 *
 *  Created on: 19/11/2013
 *      Author: MATRIX
 */

#ifndef DOCUMENTVECTOR_H_
#define DOCUMENTVECTOR_H_
#include <iostream>
#include  <stdlib.h>
#include  <string>
#include  <list>
#include <vector>
using namespace std;
class DocumentVector {
public:
	DocumentVector();
      //represents the tf*idf of  each document
      std::vector<float> VectorSpace;
      void setTamanio(unsigned tamanio);
      void agregarEnPos(unsigned pos, double valor);
      void mostrarVector();
	virtual ~DocumentVector();
};

#endif /* DOCUMENTVECTOR_H_ */
