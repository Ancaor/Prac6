/** @brief fichero de implementacion de la clase mutacion

*/
/**
 @brief Constructor por defecto, inicialiaza todos los campos a strings vacios
*/
//#include "enfermedad.h" 
#include "mutacion.h"
#include <string>
#include <cstring>
#include <iostream> 
#include <vector>


using namespace std;

mutacion::mutacion(){
	ID = "0";
	chr = "0";
	pos = 0; 
  	common = false;

}
/**
@brief Constructor de copia
@param m mutación de la que se copiaran los campos
*/
mutacion::mutacion(const mutacion& m){
	ID = m.getID();
	chr = m.getChr();
	pos = m.getPos();
	common = m.getCommon();
	genes = m.getGenes();
	ref_alt = m.getRef_alt();
	caf = m.getCaf();
	clnsig = m.getClnsig();
	enfermedades = m.getEnfermedades();

}
/**
 @brief Constructor con string, parsea todo el string buscando la información correcta para inicializar los campos
 @param str string que será parseado en busca de la información necesaria para crear el objeto mutacion
*/
mutacion::mutacion(const string & str) {

	setChr(str.substr(0,str.find("	",0)));
	//cout << str.substr(str.find("	",0),str.find("	",str.find("	",0)+1)-1)<< endl;
	pos = stoul(str.substr(str.find("	",0),str.find("	",str.find("	",0)+1)-1));

	size_t id_location = str.find("rs",0);
	setID(str.substr(id_location,str.find("	",id_location)-id_location));

      //RET_ALT

		size_t antes = str.find("	",id_location);

		size_t despues;

		despues = str.find("	",(antes+1));

		vector<string> auxiliar;
		auxiliar.push_back(str.substr(antes,despues-antes));

		antes = str.find_first_of("	",despues);
		despues = str.find("	",(antes+1));

		string alt = str.substr(antes,(despues-antes));

		size_t pos_comas = alt.find(",",0) ;

		if(  pos_comas == string::npos)
			auxiliar.push_back(alt);
		else{
			size_t inicio = 0;
			do{
				auxiliar.push_back(alt.substr(inicio,(pos_comas-inicio)));
				inicio = (pos_comas+1);
				pos_comas = alt.find(",",(pos_comas+1)) ;
			}while(pos_comas != string::npos);
			auxiliar.push_back(alt.substr(inicio,(alt.size()-inicio)));
		}
	ref_alt = auxiliar;

	// GENES

		vector<string> genes_string;

		size_t inicio_genes = str.find("GENEINFO=",0);
		inicio_genes = inicio_genes + 9;
		size_t fin_genes = str.find(";",inicio_genes);

		string aux_genes = str.substr(inicio_genes,(fin_genes-inicio_genes));

		size_t pos_barra = aux_genes.find("|",0);
		size_t pos_coma = aux_genes.find(",",0);

		if((pos_barra == string::npos) && (pos_coma == string::npos))
			genes_string.push_back(aux_genes);
		else{
			size_t inicio_gen = 0;
			if(pos_barra != string::npos){

				do{
					genes_string.push_back(aux_genes.substr(inicio_gen,(pos_barra-inicio_gen)));
					inicio_gen = (pos_barra+1);
					pos_barra = aux_genes.find("|",(pos_barra+1));
				}while(pos_barra != string::npos);
				genes_string.push_back(aux_genes.substr(inicio_gen,(aux_genes.size()-inicio_gen)));
			}
			else if(pos_coma != string::npos){

				do{
					genes_string.push_back(aux_genes.substr(inicio_gen,(pos_coma-inicio_gen)));
					inicio_gen = (pos_coma+1);
					pos_coma = aux_genes.find("|",(pos_coma+1));
				}while(pos_coma != string::npos);
				genes_string.push_back(aux_genes.substr(inicio_gen,(aux_genes.size()-inicio_gen)));
			}

		}
		
	genes = genes_string;
	
	// COMMON

		size_t pos_common = str.find("COMMON=",0);
		if(pos_common == string::npos)
			common = 0;
		else{
			pos_common = pos_common +7;
			common = std::stoi(str.substr(pos_common,1));
		}
	
	//CAF

		size_t pos_caf = str.find("CAF=",0);
		if(pos_caf != string::npos){
			pos_caf = pos_caf+4;
			size_t pos_caf_final = str.find(";",pos_caf);
			vector<float> caf_aux;
			
			string aux_caf = str.substr(pos_caf,(pos_caf_final-pos_caf));

			size_t inicio_comas = 0;
			for(unsigned i=0;i<(ref_alt.size()-1);i++){
				size_t coma = aux_caf.find(",",inicio_comas);
				string auxi = aux_caf.substr(inicio_comas,(coma-inicio_comas));
				if(auxi != "."){
				caf.push_back(std::stof(auxi));
				}else 
				caf.push_back(0.0);
				inicio_comas = coma+1;
			}
			string auxi_final = aux_caf.substr(inicio_comas,(aux_caf.size()-inicio_comas));
			if(auxi_final != ".")
			caf.push_back(std::stof(auxi_final));
		}else
			caf.push_back(1.0);

	//ENFERMEDAD
		
	if(str.find("CLNDBN=",0) != string::npos){

		vector<string> name;

		size_t inicio_nombre = str.find("CLNDBN=",0) +7;
		size_t cant_nombre = str.find(";",inicio_nombre)-inicio_nombre;
		string nombre = str.substr(inicio_nombre,cant_nombre+1);

		size_t inicio_i = 0;
		size_t cant_i;
		for(unsigned i=0;i<=cant_nombre;i++){
			if(nombre[i]==';' || nombre[i]==',' || nombre[i]=='|'){
				cant_i = i-inicio_i;
				name.push_back(nombre.substr(inicio_i,cant_i));
				inicio_i = i+1;

			}
		}

		vector<string> id;

		size_t inicio_id = str.find("CLNDSDBID=",0) +10;
		size_t cant_id = str.find(";",inicio_id)-inicio_id;
		string id_str = str.substr(inicio_id,cant_id+1);

		inicio_i = 0;
		cant_i = 0;
		for(unsigned i=0;i<=cant_id;i++){
			if(id_str[i]==';' || id_str[i]==',' || id_str[i]=='|'){
				cant_i = i-inicio_i;
				id.push_back(id_str.substr(inicio_i,cant_i));
				inicio_i = i+1;

			}
		}


		vector<string> db;

		size_t inicio_db = str.find("CLNDSDB=",0) +8;
		size_t cant_db = str.find(";",inicio_db)-inicio_db;
		string db_str = str.substr(inicio_db,cant_db+1);

		inicio_i = 0;
		cant_i = 0;
		for(unsigned i=0;i<=cant_db;i++){
			if(db_str[i]==';' || db_str[i]==',' || db_str[i]=='|'){
				cant_i = i-inicio_i;
				db.push_back(db_str.substr(inicio_i,cant_i));
				inicio_i = i+1;

			}
		}

		for(unsigned i=0; i<id.size(); i++)
			this->enfermedades.push_back(enfermedad(name[i],id[i],db[i]));
	}


	//CLNSIG
		if(str.find("CLNSIG=",0) != string::npos){	
			string clnsig_str = str.substr(  (str.find("CLNSIG=",0)+7)  , (str.find(";",(str.find("CLNSIG=",0)+7)) -(str.find("CLNSIG=",0)+7)) );
			
			size_t inicio_clnsig = 0;
			

			if((clnsig_str.find("|",inicio_clnsig) == string::npos)&&(clnsig_str.find(",",inicio_clnsig) == string::npos))
				clnsig.push_back(std::stoi(clnsig_str));
			else{ if(clnsig_str.find("|",inicio_clnsig) != string::npos){

					size_t fin_clnsig = clnsig_str.find("|",inicio_clnsig);
					do{
						clnsig.push_back( std::stoi(clnsig_str.substr(inicio_clnsig,(fin_clnsig-inicio_clnsig))));
						inicio_clnsig = fin_clnsig+1;
						fin_clnsig = clnsig_str.find("|",inicio_clnsig);

					}while(clnsig_str.find("|",inicio_clnsig) != string::npos);
					clnsig.push_back( std::stoi(clnsig_str.substr(inicio_clnsig,(clnsig_str.size()-inicio_clnsig))));
				   
				   }else{
				   		size_t fin_clnsig = clnsig_str.find(",",inicio_clnsig);
				   		do{
							clnsig.push_back( std::stoi(clnsig_str.substr(inicio_clnsig,(fin_clnsig-inicio_clnsig))));
							inicio_clnsig = fin_clnsig+1;
							fin_clnsig = clnsig_str.find(",",inicio_clnsig);

						}while(clnsig_str.find(",",inicio_clnsig) != string::npos);
						clnsig.push_back( std::stoi(clnsig_str.substr(inicio_clnsig,(clnsig_str.size()-inicio_clnsig))));
		
					}
			
				}


		}	
}   //para crear objeto mutacion a partir de la cadena que contiene una línea completa del fichero de entrada
 
/**
@brief Asigna un ID a la mutación
@param id string que contiene el ID que se asignará
*/
  void mutacion::setID(const string & id){
  	ID = id;
  }
/**
@brief Asigna un Cromosoma a la mutación
@param chr string que contiene el cromosoma que se asignará
*/
  void mutacion::setChr(const string & chr){
  	this->chr = chr;
  }
/**
@brief Asigna una posicion del cromosoma a la mutación
@param pos posición del cromosoma , unsigned int
*/
  void mutacion::setPos(const unsigned int & pos){
  	this->pos = pos;
  }
/**
@brief Asigna un vector de bases de genoma de referencia y alteradas a la mutación
@param ref_alt vector de bases de genoma , strings
*/
  void mutacion::setRef_alt(const std::vector<string> & ref_alt){
  	this->ref_alt = ref_alt;

  }
/**
@brief Asigna un vector de genes asociados al SNP a la mutación 
@param genes vector de genes, strings
*/  
  void mutacion::setGenes (const std::vector<string> & genes){
  	this->genes = genes;
  }  
/**
@brief Asigna a una mutación el su caracter en cuanto a frecuencia
@param common si es TRUE, la mutación es común, sin es FALSE, no lo es , bool
*/
    void mutacion::setCommon (const bool & common){
  	this->common = common;
  }
/**
@brief Asigna un vector con la frecuencia en la población de las bases del genoma, el vector tiene tantas frecuencias como bases (ref_alt)
@param caf vector de frecuencias, float
*/
  void mutacion::setCaf (const std::vector<float> & caf){
  	this->caf = caf;
  }
/**
@brief Asigna un vector de las enfermedades asociadas a la mutación
@param enfermedades vector de enfermedades
*/  
  void mutacion::setEnfermedades (const std::vector<enfermedad> & enfermedades){
  	this->enfermedades = enfermedades;
  }
/**
@brief Asigna un vector de la relevancia clínica de cada enfermedad asociada a la mutación .
@param clnsig vector de las relevancias , int
*/  
  void mutacion::setClnsig (const std::vector<int> & clnsig){
  	this->clnsig = clnsig;
  }  
/**
@brief Devuelve el valor del ID
@returns string con el ID
*/
  string mutacion::getID( ) const{
  	return ID;
  }
/**
@brief Devuelve el valor de Chr
@returns string con el valor de chr
*/
  string mutacion::getChr( ) const{
  	return chr;
  }
/**
@brief Devuelve el valor de Pos
@returns unsigned int con el valor de chr
*/
  unsigned int mutacion::getPos( ) const{
  	return pos;
  }
/**
@brief Devuelve el vector de strings ref_alt
@returns vector<string> de ref_alt
*/  
  const std::vector<string> & mutacion::getRef_alt () const{
  	return ref_alt;
  }
/**
@brief Devuelve el vector de strings genes
@returns vector<string> de genes
*/    
  const std::vector<string> & mutacion::getGenes () const{
  	return genes;
  }
/**
@brief Devuelve el valor de common
@returns bool common
*/    
  bool mutacion::getCommon () const{
  	return common;
  }
/**
@brief Devuelve el vector de floats Caf
@returns vector<float> de caf
*/  
  const std::vector<float> & mutacion::getCaf () const{
  	return caf;
  }
/**
@brief Devuelve el vector de strings ref_alt
@returns vector<string> de ref_alt
*/  
  const std::vector<enfermedad> & mutacion::getEnfermedades () const{
  	return enfermedades;
  }
/**
@brief Devuelve el vector de int Clnsig
@returns vector<int> de clnsig
*/

  const std::vector<int> & mutacion::getClnsig () const{
  	return clnsig;
  }
/**
@brief Sobrecarga de operador = , asigna todos los campos de m a la enfermedad indicada
@param m enfermedad de la que se copian los campos
*/
  mutacion & mutacion::operator=(const mutacion & m){
  	if(&m != this){
  		this->ID = m.getID();
		this->chr = m.getChr();
		this->pos = m.getPos();
		this->common = m.getCommon();
		this->genes = m.getGenes();
		this->ref_alt = m.getRef_alt();
		this->caf = m.getCaf();
		this->clnsig = m.getClnsig();
		this->enfermedades = m.getEnfermedades();
  	}
  	return *this;

  }
/**
@brief Compara si dos mutaciones son iguales en todos sus campos
@param m mutación con la que comparamos
@returns TRUE si son iguales, FALSE si no

*/

  bool mutacion::operator==(const mutacion & m) const{
  	bool resultado = false;

  	if( (this->ID == m.getID() )&& ( this->chr == m.getChr()) && (this->pos == m.getPos()) && (this->ref_alt == m.getRef_alt()) && (this->genes == m.getGenes()) && (this->common == m.getCommon()) && (this->caf == m.getCaf()) && (this->clnsig == this->getClnsig()) && (this->enfermedades == m.getEnfermedades())){
  		resultado = true;		
  	}
	return resultado;
  }
/**
@brief Compara según orden creciente de cromosoma dos mutaciones
@param m mutacion con la que comparamos
@returns TRUE si m es mayor, FALSE si no
*/

  bool mutacion::operator<(const mutacion & m) const{
  	bool resultado = false;

  	string comparar_this = this->chr;
  	string comparar_m = m.getChr();

  	if(this->chr == "X")
  		comparar_this = "23";
  	else if(this->chr == "Y")
  		comparar_this = "24";
  	else if(this->chr == "MT")
  		comparar_this = "25";

  	if(m.getChr() == "X")
  		comparar_m = "23";
  	else if(m.getChr() == "Y")
  		comparar_m = "24";
  	else if(m.getChr() == "MT")
  		comparar_m = "25";


  	if(std::stoi(comparar_this) < std::stoi(comparar_m)){
  		resultado = true;
  	}else if(std::stoi(comparar_this) == std::stoi(comparar_m)){
  			if(this->pos < m.getPos()){
  				resultado = true;
  			}
  		}

  	return resultado;
  	
  }  
/**
@brief Sobrecarga del operador << , imprime por pantalla todos los campos de una mutación
@param os stream de salida
@param m mutación de la que se va a imprimir la información
@returns stream de salida con la información de la mutación
*/
  ostream& operator<< ( ostream& os, const mutacion& m){
  	os << m.getChr() << "  " << m.getPos() << "  " << m.getID() << "  ";

  	for(unsigned i=0;i<m.getRef_alt().size();i++)
  		os << m.getRef_alt()[i] << "  ";

  	os << "GENEINFO=";

  	for(unsigned i=0;i<m.getGenes().size();i++)
  		os << m.getGenes()[i] << " | ";

  	os << ";" << "COMMON=" << m.getCommon() << "  ";

  	os << ";" << "CAF=" ;
  	for(unsigned i=0;i<m.getCaf().size();i++)
  		os << m.getCaf()[i] << " , ";

  	os << ";" << endl <<"ENFERMEDADES=";

  	for(unsigned i=0;i<m.getEnfermedades().size();i++)
  		os << m.getEnfermedades()[i].toString() << " ; " << endl;

  	os<< "CLNSIG= ";

  	for(unsigned i=0;i<m.getClnsig().size();i++)
  		os << m.getClnsig()[i] << " " ;

  	os <<  ";" << endl;

  	return os;

  }   //Imprimir TODOS los campos del objeto mutación.

