#include "BoolFunct.hpp"
#include "resources.cpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>

using namespace std;

int main(int argc, char *argv[])
{
	
	// CREATE & OPEN IFSTREAM IBTABLES
	char car = 1;
	ifstream ibtables;
	stringstream sin;
	ibtables.open(full_path.c_str());
	while (! ibtables.eof()) {
		car = ibtables.get() ;
		sin << car;
	}
	ibtables.close();
	// CLOSE IFSTREAM IBTABLES
	
	BoolFunct arg(sin,3,false);
	cout << "Truth Table " << endl;
	saca_lista(arg);
	
	arg.Genera_Tabla_De_Adyacencias_Por_Recurrencia();
	

	cout << "Prime implicants saved" << endl;

	arg.Genera_Tabla_De_Implicantes_Primos();
	
	
	cout<<"Table of Prime essentials"<<endl;
	arg.saca_primos_esenciales();

	system("PAUSE");
	return EXIT_SUCCESS;

}
