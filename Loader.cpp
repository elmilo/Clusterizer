#include "Loader.h"

/******************************************************************************/
/******************************************************************************/
/**PUBLIC**************************************************/
Loader::Loader(string directorio, string extension = "") {
    raizPpalStr = directorio;
    raizPpal = directorio.c_str();
    largoRaizStr = directorio.length();
    listarArchivos(raizPpal, extension); //llamadas
    std::sort (direcciones.begin(), direcciones.end());//ordenar de mayor a menor
}


string Loader::popDocumento(unsigned unaPos) {
    datosArchivos unArchivo = direcciones.at(unaPos);
    string Archivo = unArchivo.nombreArchivo;
    return raizPpalStr + SEPARADOR_DIR + Archivo;
}


unsigned Loader::cantidadDocIDs(){
    return direcciones.size();
}

/******************************************************************************/
/******************************************************************************/
/**PRIVATE**************************************************/

long Loader::obtenerTamanioArchivo(std::string direccionArchivo){
    struct stat stat_buf;
    int rc = stat(direccionArchivo.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}


int Loader::filtroArchivos(const struct dirent * dire, const char* raiz) {

	/* Descartar "." y ".." , NO se listan */
	if (strncmp(dire->d_name, ".", 2) == 0
			|| strncmp(dire->d_name, "..", 3) == 0)
		return -1;

	/* Chequear si es directorio o no. Se pregunta por el tipo UNKNOWN tambien.
	 * Devuelve 0 porque es directorio (y no se lista)
	 * */
	if (dire->d_type == DT_UNKNOWN || dire->d_type == DT_DIR) {
		return 0;
	}
	/*if(dire->d_type == DT_DIR )
	 return 0;*/
	/* Seguramente es un archivo corriente, y se debe listar
	 * */
	return 1;
}


string Loader::sacarRaizPpal(string unArchivo) {
	return unArchivo.erase(0, largoRaizStr);
}


bool Loader::filtroExtensiones(string nombreArchivo, string extension) {
	return nombreArchivo.find(extension) != string::npos; //Si es distinto, encuentra la extension
}


void Loader::insertar(string nombreArchivoPorAgregar, string extension, long tamanio) {
	if (filtroExtensiones(nombreArchivoPorAgregar, extension)){
        datosArchivos addendum;
        
        addendum.nombreArchivo = nombreArchivoPorAgregar;
        addendum.tamanioArchivo = tamanio;
        
		direcciones.push_back(addendum);}
}


void Loader::listarArchivos(const char* unDirectorio, string extension = "") {
	DIR *pDIR;
	struct dirent *entrada;
	string raiz(unDirectorio);
	int stopper; //estado del filtro
	pDIR = opendir(unDirectorio);
	if (pDIR != NULL) {
		while ((entrada = readdir(pDIR)) != NULL) {

			stopper = filtroArchivos(entrada, unDirectorio);

			if (stopper == 1) {
				/* Se lista porque es fichero comun */
				string archivo(entrada->d_name);
				string rutaDelArchivo;

				//Si es la raizPpal NO se agrega el cosito: "/" = SEPARADOR_DIR
				if (raiz == raizPpalStr)
					rutaDelArchivo = archivo;
				else {
					//Si es otro directorio, se agrega la barra y se borra
					//del string el directorio raiz
					rutaDelArchivo = raiz + SEPARADOR_DIR + archivo;
					rutaDelArchivo = sacarRaizPpal(rutaDelArchivo);
				}
                
				insertar(rutaDelArchivo, extension, obtenerTamanioArchivo( raizPpalStr + SEPARADOR_DIR + rutaDelArchivo) );

			} else if (stopper == 0) {
				/* Se hace llamada recursiva por ser directorio
				 * Se descarta en otro caso
				 **/
				string directorioRama(entrada->d_name);
				string rama;

				rama = raiz + SEPARADOR_DIR + directorioRama;

				listarArchivos(rama.c_str());
			}
		}
		closedir(pDIR);
	}
}
