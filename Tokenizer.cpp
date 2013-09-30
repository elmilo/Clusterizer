#include "Tokenizer.h"

const char* Tokenizer::delim = ".,:;`/\"+-_(){}[]<>*&^%$#@!?~/|\\= \t\n'";

bool Tokenizer::esAlfaNum (string entrada){
  locale loc;
  for (unsigned i=0; i< entrada.length() ; i++){
    if ( !isalnum(entrada[i]) )
        return false;
        }
    return true;
}

void Tokenizer::agregarEnContenedor(char *palabra){

    int tamanio = 0;
    char *s = palabra;
    for (s = palabra; *s; s++)
        tamanio++;

    string tokenito(palabra, tamanio);
    
    if ( esAlfaNum(tokenito) ) {
        transform(tokenito.begin(),tokenito.end(),tokenito.begin(),(int (*)(int))tolower );
        posiciones.push_back(tokenito);
        }
}

/**
 * Codigo C
 * */
int Tokenizer::separarTokens(){
        char *archivoEnMemoria, *palabra, *agregada;
        FILE *fp = fopen(direccion, "r");
        struct stat sb;
 
        if (!fp)
                return 0;
 
        if (stat(direccion, &sb))
                return 0;
 
        archivoEnMemoria = (char *) malloc(sb.st_size); //<-- ¬¬
        
        if (!archivoEnMemoria) {
                fclose(fp);
                return 0;
        }
 
        fread(archivoEnMemoria, sizeof(char), sb.st_size, fp);
 
        palabra = strtok(archivoEnMemoria, delim);
        
        while(palabra != NULL) {
                agregada = strdup(palabra);
                
                agregarEnContenedor(agregada);
 
                palabra = strtok(NULL, delim);
        }
 
        free(archivoEnMemoria);
        fclose(fp);
 
        return 1;
}


void Tokenizer::normalizar (string unaFrase){
    
    const char* origen = unaFrase.c_str();
    char *frase, *palabra, *agregada;
    
    frase = strdup(origen);

    palabra = strtok(frase, delim);
    
    while(palabra != NULL) {
            
            agregada = strdup(palabra);
            
            agregarEnContenedor(agregada);

            palabra = strtok(NULL, delim);
    }
        
}


void Tokenizer::parsearArchivo (string unaDire){
    direccion = unaDire.c_str();
    separarTokens();    
    }

string Tokenizer::siguienteTermino(){

    string termino = posiciones.front();
    posiciones.pop_front();
    
    cantidad++;
    
    return termino;

};

palabraPos Tokenizer::unTermino(){
    
    palabraPos termino;
    
    

    termino.palabra = posiciones.front();
    termino.posicion = cantidad;
    posiciones.pop_front();
    
    cantidad++;
    
    return termino;

};

unsigned Tokenizer::siguientePosicion(){
    return cantidad;
};

Tokenizer::Tokenizer(string direccionArchivo){
    cantidad = 0;
    parsearArchivo(direccionArchivo);
};

bool Tokenizer::tengaTerminos(){
    
    return !(posiciones.empty());
    
};
