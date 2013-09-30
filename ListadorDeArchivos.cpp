#include "ListadorDeArchivos.h"


int ListadorDeArchivos::filtro(const struct dirent * dire, const char* raiz){
    
    /* Descartar "." y ".." , NO se listan */
    if( strncmp(dire->d_name, ".", 2) == 0
        || strncmp(dire->d_name, "..", 3) == 0 )
        return -1;
        
    /* Chequear si es directorio o no. Se pregunta por el tipo UNKNOWN tambien.
     * Devuelve 0 porque es directorio (y no se lista)
    * */
    if( dire->d_type == DT_UNKNOWN || dire->d_type == DT_DIR ){
                return 0;
                }
        /*if(dire->d_type == DT_DIR )
                return 0;*/
    /* Seguramente es un archivo corriente, y se debe listar
     * */
    return 1;
}

string ListadorDeArchivos::sacarRaizPpal (string unArchivo){
    return unArchivo.erase (0, largoRaizStr);
}

/**
 * No se usa, queda por una cuestion de honor (!)
 * */
bool ListadorDeArchivos::filtrarDirectorios(const struct dirent * dire, const char* raiz){
    return (dire->d_type == DT_REG );
}

void ListadorDeArchivos::listarArchivos(const char* unDirectorio){
        DIR *pDIR;
        struct dirent *entrada;
        string raiz (unDirectorio);
        int stopper; //estado del filtro
        
        if ( pDIR=opendir(unDirectorio) ){
                while ( entrada = readdir(pDIR) ){
                    
                        stopper = filtro(entrada, unDirectorio);
                        
                        if (stopper == 1){
                            /* Se lista porque es fichero comun */
                            string archivo(entrada->d_name);
                            string rutaDelArchivo;
                            
                            //Si es la raizPpal NO se agrega el cosito: "/" = SEPARADOR_DIR
                            if (raiz == raizPpalStr)
                                rutaDelArchivo = archivo;
                            else{
                                //Si es otro directorio, se agrega la barra y se borra
                                //del string el directorio raiz
                                rutaDelArchivo = raiz + SEPARADOR_DIR + archivo;
                                rutaDelArchivo = sacarRaizPpal (rutaDelArchivo);
                                }
                            
                            docIDs.push_back(rutaDelArchivo);
                            
                            }else if (stopper == 0) {
                                /* Se hace llamada recursiva por ser directorio
                                 * Se descarta en otro caso
                                 **/
                                string directorioRama (entrada->d_name);
                                string rama;
                                
                                rama = raiz + SEPARADOR_DIR + directorioRama;
                                
                                listarArchivos(rama.c_str());
                                }
                }
                closedir(pDIR);
        }
}


ListadorDeArchivos::ListadorDeArchivos (string directorio){
    raizPpalStr = directorio;
    raizPpal = directorio.c_str();
    largoRaizStr = directorio.length();
    
    listarArchivos(raizPpal); //llamadas
    std::sort(docIDs.begin(), docIDs.end()); //ordena
    };

unsigned ListadorDeArchivos::tamanio(){
    return docIDs.size();
    };

string ListadorDeArchivos::documento(unsigned int i){
    if ( i<docIDs.size() )
        //Se podria devolver sin el SEPARADOR
        return raizPpalStr + SEPARADOR_DIR + docIDs[i];
    };
