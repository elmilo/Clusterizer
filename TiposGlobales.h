#ifndef TIPOSGLOBALES_H
#define TIPOSGLOBALES_H

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>


typedef float TipoGuardado;

typedef Eigen::Matrix< TipoGuardado , Eigen::Dynamic , Eigen::Dynamic > TipoMatriz;
typedef Eigen::Matrix< TipoGuardado , 1, Eigen::Dynamic > TipoVectorFila;
typedef Eigen::Matrix< TipoGuardado , Eigen::Dynamic, 1 > TipoVectorColumna;

#endif
