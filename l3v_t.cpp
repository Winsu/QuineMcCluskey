#include "definitions.hpp"
#include "l3v_t.hpp"
#include <iostream>

using namespace std;

ostream & operator<< (ostream & out,const bool_l3v & arg) {
	return operator<<(out,char(arg));
}

const istream & operator>> (istream & in,bool_l3v & arg) {
	char entrada;
	in >> entrada;
	arg = bool_l3v(entrada);
	return in;
}
