//los siguientes typedef permiten identificar en las cabeceras de los métodos
//cuando un string se refiere a un ID de gen, mutacion o enfermedad, respectivamente.
#ifndef _CLINVAR_H_
#define _CLINVAR_H_

#include <functional>
#include "enfermedad.h"
#include "mutacion.h"
#include "functor.h"
#include <string>
#include <vector>
#include <iostream> 
#include <algorithm>
#include <fstream>
#include <assert.h>
#include <set>
#include <map>
#include <list>
#include <unordered_map>
#include <queue>
#include <unordered_set>


using namespace std;

typedef string IDgen;
typedef string IDmut;
typedef string IDenf;

/* @brief iterador sobre enfermedades
*/
typedef map<IDenf, enfermedad>::iterator enfermedad_iterator;

class clinvar{

public:



clinvar();
unsigned int size();
void load (string nombreDB);
void insert (const mutacion & x);
bool erase (IDmut ID);


/* @brief iterador sobre mutaciones en orden creciente de cromosoma/posicion
*/

class iterator{
	private:
		set<mutacion>::iterator it;
	public:
		friend class clinvar;
		iterator();
		const mutacion & operator*();
		iterator & operator++();
		iterator operator++(int i);
		//iterator & operator--();
		//iterator operator--(int i);
		//bool operator==(const iterator & x) const ;		  
		//bool operator!=(const iterator & x) const ;
		//iterator & operator=(const iterator & x);

	//const - no se puede modificar la mutacion y alterar el orden del set
};

/* @brief iterador sobre mutaciones considerando el orden creciente del ID del gen
*/

class gen_iterator {
	public:
		friend class clinvar;
		const mutacion & operator*();
		gen_iterator();
		//const - no se puede modificar la mutacion y alterar el orden del set
	private:
		map<IDgen, list< set<mutacion>::iterator>>::iterator itmap;
		list< set<mutacion>::iterator>::iterator itlist;
		clinvar *ptrclinvar;
};



iterator find_Mut (IDmut ID);
enfermedad_iterator find_Enf(IDenf ID);
vector<enfermedad> getEnfermedades(mutacion & mut);
list<IDenf> getEnfermedades(string keyword);
set<IDmut> getMutacionesEnf (IDenf ID);
set<IDmut> getMutacionesGen (IDgen ID);
set<mutacion,ProbMutaciones> topKMutaciones (int k, string keyword);




/* Métodos relacionados con los iteradores */
iterator begin();
iterator end();
iterator lower_bound(string cromosoma, unsigned int posicion);
iterator upper_bound(string cromosoma, unsigned int posicion);

enfermedad_iterator ebegin();
enfermedad_iterator eend();
gen_iterator gbegin();
gen_iterator gend();

private:
	friend class gen_iterator;
	friend class iterator; 

	set<mutacion> mutDB; //base de datos que contiene toda la información asociada a una mutacion
	unordered_map<IDmut,set<mutacion>::iterator> IDm_map; // Asocia IDmutacion con mutación
	map<IDgen, list< set<mutacion>::iterator> > gen_map; // Asocia genes con mutaciones
	map<IDenf,enfermedad> EnfDB; // Base de datos de enfermedades
	multimap<IDenf,set<mutacion>::iterator> IDenf_map; // Asocia enfermedad con mutaciones
};

#endif