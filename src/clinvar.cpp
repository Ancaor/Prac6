#include "clinvar.h"
#include <unordered_map>
using namespace std;

clinvar::clinvar(){

}

void clinvar::load (string nombreDB){
 ifstream fe;
 string cadena;
 int contador = 0;

 cout << "Abrimos "<< nombreDB << endl;
 fe.open(nombreDB.c_str(), ifstream::in);
 if (fe.fail()){
   cerr << "Error al abrir el fichero " << nombreDB << endl;
 } 
 else {
    //leo la cabecera del fichero (líneas que comienzan con #)
    do{ 
      getline(fe,cadena,'\n'); 
    }while (cadena.find("#")==0 && !fe.eof());
   
    //leo la tabla de mutaciones, una línea cada vez
    while (!fe.eof() ){ 
        //cout << "leo:: "<< cadena << endl;
        // Invoco el constructor de mutación que recibe una cadena completa, la parsea y crea la mutación.
        mutacion mut = mutacion(cadena);
        // Insertar mutación en el conjunto
        //cout << mut;
        insert(mut);
    	contador++;
        getline(fe,cadena,'\n');
    }
    fe.close();
  //  return true;
  } // else
  //cout << contador;
  
  cout << "tamaño IDm_map: "<<IDm_map.size();
  cout << "\n tamaño gen_map: " << gen_map.size();
  cout << "\n tamaño EnfDB: " << EnfDB.size();
  cout << "\n tamaño IDenf_map: " << IDenf_map.size();

  /*
  cout << "\n LO INTERESANTE :";

  map<IDgen, list< set<mutacion>::iterator> >::iterator as = gen_map.begin();
  as++;
  as++;

  list < set < mutacion > ::iterator > a = as->second;

  cout << a.size() << "\n";

  set < mutacion > ::iterator b = *(a.begin());
  cout << *b;
  b++;
  cout <<"\n" <<*b;

*/

  fe.close();
  //return false;
}

void clinvar::insert (const mutacion & x){

	
	auto par = mutDB.insert(x);

	if (par.second == true){

		std::pair<IDmut,set<mutacion>::iterator> var (x.getID(),par.first);
		IDm_map.insert(var);

		for(auto i : x.getEnfermedades()){
			EnfDB.emplace(i.getID(),i);
		}

		for(auto i : x.getGenes()){
			gen_map[i].push_back(par.first);
		}

		for(auto i : x.getEnfermedades()){
				EnfDB.emplace(i.getID(),i);
				}

		for(auto i : x.getEnfermedades()){
			IDenf_map.emplace(i.getID(),par.first);
		}

	}

}

bool clinvar::erase (IDmut ID){
	bool exito = true;

	mutacion mut = *(IDm_map.find(ID))->second;
	IDm_map.erase(ID);

	for(auto i : mut.getGenes()){

		auto iti = (gen_map.find(i))->second.begin();		
		auto itf = (gen_map.find(i))->second.end();
		bool encontrado = false;
		while (iti != itf && !encontrado){
			if(**iti == mut){
				*(gen_map.find(i))->second.erase(iti);
				encontrado = true;
			}
			else
				iti++;
		}	
	}

	for (auto i : mut.getEnfermedades()){
		auto pareja = IDenf_map.equal_range(i.getID());
		bool encontrado = false;
		auto itini = pareja.first;

		while( itini != pareja.second && !encontrado){
			if(*(itini->second) == mut){
				itini = IDenf_map.erase(itini);
				encontrado=true;
			}
			else
				itini++;
		}

		if(IDenf_map.find(i.getID()) == IDenf_map.end()){
			EnfDB.erase(i.getID());
		}

	}

	mutDB.erase(mut);


	cout << "tamaño IDm_map: "<<IDm_map.size();
  cout << "\n tamaño gen_map: " << gen_map.size();
  cout << "\n tamaño EnfDB: " << EnfDB.size();
  cout << "\n tamaño IDenf_map: " << IDenf_map.size();

	return exito;
}

clinvar::iterator clinvar::find_Mut (IDmut ID){
	iterator it;
	it.it = IDm_map.find(ID)->second;
	return it;
}



enfermedad_iterator clinvar::find_Enf(IDenf ID){
	enfermedad_iterator it;
	it = EnfDB.find(ID); 
	return it;
}

vector<enfermedad> clinvar::getEnfermedades(mutacion & mut){
	vector<enfermedad> vec;
	vec= (*mutDB.find(mut)).getEnfermedades();
	return vec;
}

list<IDenf> clinvar::getEnfermedades(string keyword){
	list<IDenf> lista;

	for(auto it = ebegin(); it != eend() ; it++){
		if(it->second.nameContains(keyword))
			lista.push_back(it->second.getID());
	}
	return lista;
}
/*
Devuelve un conjunto ordenado (en orden creciente de IDmut) de todas las mutaciones que se encuentran aso-
ciadas a la enfermedad con identificador ID. Si no tuviese ninguna enfermedad asociada, devuelve el conjunto
vacío.
*/
set<IDmut> clinvar::getMutacionesEnf (IDenf ID){
	set<IDmut> mutaciones;

	auto pair = IDenf_map.equal_range(ID);
	
	for(auto itini  = pair.first; itini != pair.second ; itini++){
		mutaciones.insert((*itini->second).getID());
	}

	return mutaciones;
}

/*
Devuelve un conjunto de todas las mutaciones que se encuentran asociadas a un gen determinado dado por ID. Si
no tuviese ninguno, devuelve el conjunto vacío.
*/
set<IDmut> clinvar::getMutacionesGen (IDgen ID){
	set<IDmut> mutaciones;

	auto it = gen_map.find(ID);
	if(it != gen_map.end()){
		for(auto ini = (it->second).begin(); ini != (it->second).end(); ini ++){
			mutaciones.insert((**ini).getID());
		}
	}
	return mutaciones;
}

/*
Dado un string 'keyword', el sistema
recupera todas las enfermedades cuyo nombre contiene keyword, y devuelve un set ordenado de mutacio-
nes, en orden decreciente de probabilidad, con las k mutaciones más frecuentes en la población asociadas
con esas enfermedades.
*/
//set<mutacion,ProbMutaciones> clinvar::topKMutaciones (int k, string keyword){

//}





unsigned int clinvar::size(){
	return mutDB.size();
}

clinvar::iterator clinvar::begin(){
	clinvar::iterator iter;
	iter.it = mutDB.begin();
	return iter;
}

clinvar::iterator clinvar::end(){
	clinvar::iterator iter;
	iter.it = mutDB.end();
	return iter;
}



enfermedad_iterator clinvar::ebegin(){
	return EnfDB.begin();
}

enfermedad_iterator clinvar::eend(){
	return EnfDB.end();
}

////////////// IMPLEMENTACION ITERTATOR ///////////////////////

clinvar::iterator::iterator(){

}

const mutacion & clinvar::iterator::operator*(){
	return (*it);
}

///////////////////////////////////////////////////////////////


		
