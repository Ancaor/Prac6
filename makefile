
SRC = src
INC = include
OBJ = obj
BIN = bin
LIB = lib

CXX = g++
CPPFLAGS = -std=c++11 -Wall -g -c -I$(INC)

# ******Ejecutable*******

all : $(BIN)/principal 


#Ejecutables

$(BIN)/principal:  $(OBJ)/principal.o $(OBJ)/enfermedad.o $(OBJ)/mutacion.o $(OBJ)/clinvar.o
	$(CXX)  $(OBJ)/principal.o -o $(BIN)/principal $(OBJ)/enfermedad.o $(OBJ)/mutacion.o $(OBJ)/clinvar.o

#Libreria Imagen

#$(LIB)/libimagen.a: $(OBJ)/imagen.o $(OBJ)/pgm.o $(OBJ)/byte.o $(OBJ)/cadena.o $(OBJ)/lista.o
#	ar rsv $(LIB)/libimagen.a $(OBJ)/imagen.o $(OBJ)/lista.o $(OBJ)/pgm.o $(OBJ)/byte.o $(OBJ)/#cadena.o

#compilacion de objetos

$(OBJ)/enfermedad.o: $(SRC)/enfermedad.cpp $(INC)/enfermedad.h 
	$(CXX) $(CPPFLAGS) $(SRC)/enfermedad.cpp -o $(OBJ)/enfermedad.o

$(OBJ)/mutacion.o : $(SRC)/mutacion.cpp $(INC)/mutacion.h
	$(CXX) $(CPPFLAGS)  $(SRC)/mutacion.cpp -o $(OBJ)/mutacion.o 

$(OBJ)/clinvar.o : $(SRC)/clinvar.cpp $(INC)/clinvar.h $(INC)/enfermedad.h $(INC)/mutacion.h
	$(CXX) $(CPPFLAGS)  $(SRC)/clinvar.cpp -o $(OBJ)/clinvar.o 

$(OBJ)/principal.o : $(SRC)/principal.cpp $(INC)/clinvar.h $(INC)/enfermedad.h $(INC)/mutacion.h
	$(CXX) $(CPPFLAGS)  $(SRC)/principal.cpp -o $(OBJ)/principal.o


# ************ documentación *******

documentacion:
	doxygen doc/doxys/Doxyfile

# ************ Limpieza ************

clean:
	echo "Limpiando..."
	rm $(OBJ)/*.o $(LIB)/$(LIB)*.a

mrproper: clean
	rm $(BIN)/testimagen $(BIN)/testplano $(BIN)/testarteASCII $(BIN)/arteASCII2 $(BIN)/suma

