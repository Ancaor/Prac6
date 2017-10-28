
#ifndef _FUNCTOR_H_
#define _FUNCTOR_H_

#include "mutacion.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <functional>

using namespace std;

class ProbMutaciones{
	bool reverse;
	public:
		//ProbMutaciones(const bool& param=false);
		bool operator()(const mutacion & a, const mutacion & b);
};

#endif