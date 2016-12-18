/** @brief fichero de implementacion de la clase enfermedad

*/
/**
 @brief Constructor por defecto, inicialiaza todos los campos a strings vacios

*/


#include "enfermedad.h"
#include <string>
#include <cstring>
#include <iostream> 

using namespace std;


enfermedad::enfermedad(){
  	name = "";
	ID = "";
	database = "";
}
/**
@brief Constructor con parametros
@param name Nombre con el que se construirá la enfermedad , string
@param ID ID con el que se construirá la enfermedad, string
@param database Base de Datos con la que se construirá la enfermedad , string
*/
enfermedad::enfermedad(const string & name, const string & ID, const string & database){
	this->name = name;
	this->ID = ID;
	this->database = database;
}
  
/**
 @brief Asigna un nombre a la enfermedad
 @param name nombre asignado a la enfermedad, string
*/
void enfermedad::setName(const string & name){
	this->name = name;
}
/**
 @brief Asigna un ID a la enfermedad
 @param ID id asignado a la enfermedad, string
*/
 void enfermedad::setID(const string & ID){
 	this->ID = ID;
 }
/**
 @brief Asigna una base de datos a la enfermedad
 @param database base de datos asignada a la enfermedad, string
*/
 void enfermedad::setDatabase(const string & database){
 	this->database = database;
 }
/**
 @brief Devuelve el nombre de la enfermedad
 @returns nombre de enfermedad, string
*/
 string enfermedad::getName( ) const{
 	return name;
 }
/**
 @brief Devuelve el ID de la enfermedad
 @returns ID de enfermedad, string
*/
 string enfermedad::getID( ) const{
 	return ID;
 }
/**
 @brief Devuelve la base de datos de la enfermedad
 @returns Base de Datos de enfermedad, string
*/
 string enfermedad::getDatabase( ) const{
 	return database;
 }
/**
 @brief Asigna todos los valores de una enfermedad a otra
 @param e enfermedad que se asigna a la enfermedad que llama a la función
 @returns enfermedad con todos los campos iguales a la enfermedad pasada como parametro
*/
 enfermedad & enfermedad::operator=(const enfermedad & e){
 	this->name = e.getName();
 	this->ID = e.getID();
 	this->database = e.getDatabase();
 	return *this;
 }
/**
 @brief Escribe todos los campos del objeto en un string
 @returns string con todos los parametros
*/
 string enfermedad::toString() const{
 	return "Name: " + name + ", ID: " + ID + ", Database: " + database + "  "; 
 }

// Operadores relacionales

/**
@brief Compara si dos enfermedades son iguales
@param e enfermedad con la que comparamos
@returns bool , TRUE si son iguales y FALSE si no lo son
*/
 bool enfermedad::operator==(const enfermedad & e) const{
 	bool resultado = false;

 	if((this->name == e.getName())&&(this->ID == e.getID())&&(this->database == e.getDatabase()))
 		resultado = true;

 	return resultado;
 }
/**
 @brief Compara si dos enfermedades son distintas
 @param e enfermedad con la que comparamos
 @returns bool, TRUE si son distintas, FALSE si no lo son
*/
 bool enfermedad::operator!=(const enfermedad & e) const{
 	bool resultado = false;

 	if( (this->name != e.getName()) || (this->ID != e.getID()) || (this->database != e.getDatabase()) )
 		resultado = true;

 	return resultado;
 }
/**
 @brief Compara por orden alfabético el campo name de dos enfermedades
 @param e enfermedad con la que se compara
 @returns TRUE si la enfermedad e es mayor alfabeticamente , FALSE si no
*/
 bool enfermedad::operator<(const enfermedad & e) const{	//Orden alfabético por campo name. 
 	bool resultado = false;
 	char* this_enfermedad = new char [this->getName().length()+1];
 	strcpy(this_enfermedad,this->getName().c_str());
 	char* other_enfermedad = new char [e.getName().length()+1];
 	strcpy(other_enfermedad,e.getName().c_str());



 	if( (strcmp(this_enfermedad,other_enfermedad)) < 0 )
 		resultado = true;

 	return resultado;
 }	
/**
@brief Busca si un string está incluido en el nombre de una enfermedad
@param str string que se busca en el nombre de la enfermedad
@returns TRUE si la enfermedad contiene el string, FALSE si no
*/ 
 bool enfermedad::nameContains(const string & str) const{
 	bool resultado = false;

 	string this_nommbre=this->getName();
 	string the_string = str;

 	for(unsigned i=0; i< this_nommbre.length(); i++)
 		this_nommbre[i] = tolower(this_nommbre[i]);
 	

 	for(unsigned j=0; j<str.length();j++)
 		the_string[j] = tolower(the_string[j]);

 	if( (this_nommbre.find(the_string,0)) != std::string::npos)
 		resultado = true;

 	return resultado;
 } 
/**
@brief Sobrecarga del operador << , imprime por pantalla todos los campos de una enfermedad
@param os stream de salida
@param e enfermedad de la que se va a imprimir la información
@returns stream de salida con la información de la enfermedad
*/
 ostream& operator<< ( ostream& os, const enfermedad & e){
 	os << "Nombre: " << e.getName() << " ,ID: " << e.getID() << " ,Base de datos: " << e.getDatabase() << endl;
     
   return os;
 }
   
   
 
