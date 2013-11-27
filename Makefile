OBJ = main.o Diccionario.o Loader.o Tokenizer.o FrecuenciasPorDocumento.o VectorSpaceModel.o
CXXFLAGS = -m32 -fmessage-length=0 -Wall
#CXXDEBUG = -O0 -g3
CXXRELEASE = -O3
LDFLAGS= -m32

#all: debug

#debug: CXX += $(CXXDEBUG)
#debug: clusterizer

release: CXX += $(CXXRELEASE)
release: clusterizer

cluster.o: cluster.cpp cluster.h
	g++ $(CXXFLAGS) $(LDFLAGS) -c cluster.cpp

kMeans.o: kMeans.h kMeans.cpp cluster.h
	g++ $(CXXFLAGS) $(LDFLAGS) -c kMeans.cpp

FrecuenciasPorDocumento.o: FrecuenciasPorDocumento.cpp FrecuenciasPorDocumento.h
	g++ $(CXXFLAGS) $(LDFLAGS) -c FrecuenciasPorDocumento.cpp

Diccionario.o: Diccionario.h Diccionario.cpp FrecuenciasPorDocumento.h
	g++ $(CXXFLAGS) $(LDFLAGS) -c Diccionario.cpp

Loader.o: Loader.cpp Loader.h
	g++ $(CXXFLAGS) $(LDFLAGS) -c Loader.cpp

Tokenizer.o: Tokenizer.cpp Tokenizer.h
	g++ $(CXXFLAGS) $(LDFLAGS) -c Tokenizer.cpp

VectorSpaceModel.o: VectorSpaceModel.cpp VectorSpaceModel.h 
	g++ $(CXXFLAGS) $(LDFLAGS) -c VectorSpaceModel.cpp
	
main.o: main.cpp
	g++ $(CXXFLAGS) $(LDFLAGS) -c main.cpp

clusterizer: main.o Diccionario.o Loader.o Tokenizer.o FrecuenciasPorDocumento.o VectorSpaceModel.o kMeans.o
	g++ -o clusterizer $(OBJ)


clean:
	rm $(OBJ) clusterizer

.PHONY = clean
