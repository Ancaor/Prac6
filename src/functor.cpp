#include <iostream>
#include <vector>
#include <cstdlib>
#include <functional>

using namespace std;

class ProbMutaciones{
	public:
		bool operator()(const mutacion & a, const mutacion & b){
			return (a<b);
		}
}
