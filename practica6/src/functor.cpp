#include "functor.h"
#include "mutacion.h"
#include <iostream>
#include <queue>
#include <cstdlib>
#include <functional>

using namespace std;
		
		//ProbMutaciones::ProbMutaciones(const bool& param=false){
		//	reverse = param;
		//}

		// determina cuando una mutacion es mas probable que otra
		bool ProbMutaciones::operator()(const mutacion & a, const mutacion & b){
			float probabilidadA = 1-(a.getCaf()[0]);
			float probabilidadB = 1-(b.getCaf()[0]);
			return (probabilidadB<probabilidadA);
		}