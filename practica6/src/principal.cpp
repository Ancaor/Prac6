
#include "mutacion.h"
#include "enfermedad.h"
#include "functor.h"
#include "clinvar.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;
	
	/** @brief lee un fichero de mutaciones, linea a linea
	@param[in] s nombre del fichero
  @param[in,out] cm objeto tipo conjunto sobre el que se almacenan las mutaciones
	@return true si la lectura ha sido correcta, false en caso contrario
	*/

int main(int argc, char *argv[]){

    clinvar conjuntoMutaciones;
   // string query_str; 

    //Cargar las mutaciones en vectorSNPs
    conjuntoMutaciones.load("clinvar_20160831.vcf");
    cout << "\n";
    cout << "\n";
    cout << "\n";

    cout << "Tamaño conjunto mutaciones :" <<conjuntoMutaciones.size() << "\n";

    if(conjuntoMutaciones.erase("rs4275402"))
    	cout << "\nEXITO\n";
    
    enfermedad_iterator it;

    // encuentra la enfermedad con el ID ese.

    it = conjuntoMutaciones.find_Enf("CN178850");

    cout << it->second;


    // encuentra la mutacion con el ID ese (misma mutacion que en el anterior)

    clinvar::iterator iter;// = conjuntoMutaciones.find_Mut("CN178850");

    iter = conjuntoMutaciones.find_Mut("rs397514744");
    cout << *iter;

    // prueba de getEnfermedades()

    mutacion a = *iter;

    vector<enfermedad> enfs = conjuntoMutaciones.getEnfermedades(a);

    cout << enfs[0];

    auto lista = conjuntoMutaciones.getEnfermedades("cancer");
    cout << endl;
    cout << *lista.begin();
    cout << endl;
    cout << lista.size();

    // prueba getMuacionesEnf()

    set<IDmut> muts;

	muts = conjuntoMutaciones.getMutacionesEnf("CN178850");
	cout << endl << muts.size();
	cout << endl << *muts.begin();

	//Prueba getMutacionesGen()

	set<IDmut> muts2;

	muts2 = conjuntoMutaciones.getMutacionesGen("OTOF:9381");

	cout << endl << muts2.size();
	if(muts2.size() != 0)
		cout << endl << *muts2.begin();

	//Prueba
	set<mutacion,ProbMutaciones> pepe = conjuntoMutaciones.topKMutaciones(10,"cancer");

	for(auto ini = pepe.begin(); ini != pepe.end(); ini++){
		cout << (*ini).getID()<< "   " << (1-(*ini).getCaf()[0])<<endl;
	}



   return 0;
}
