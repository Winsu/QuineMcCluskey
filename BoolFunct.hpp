#ifndef ESTRUCTURASFUNCIONES_HPP
#define ESTRUCTURASFUNCIONES_HPP

#include "l3v_t.hpp"
#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <set>
#include <map>

using namespace std;

typedef vector<bool_l3v>					BTerm_t;
typedef vector<bool_l3v>::iterator			IBTerm_t;
typedef vector<bool_l3v>::const_iterator	c_IBTerm_t;

typedef list<BTerm_t>						BFunct_t;
typedef BFunct_t*				 			pBFunct_t;
typedef list<BTerm_t>::iterator				IBFunct_t;
typedef list<BTerm_t>::const_iterator		c_IBFunct_t;

typedef list< pair<BFunct_t,unsigned int> >	BFunct_Ord_t;
typedef BFunct_Ord_t*						pBFunct_Ord_t;
typedef BFunct_Ord_t::iterator				IBFunct_Ord_t;
typedef BFunct_Ord_t::const_iterator		c_IBFunct_Ord_t;

typedef set<BTerm_t>						Impl_Primos_set_t;
typedef Impl_Primos_set_t*					pImpl_Primos_set_t;
typedef Impl_Primos_set_t::iterator			IImpl_Primos_set_t;
typedef Impl_Primos_set_t::const_iterator	c_IImpl_Primos_set_t;

typedef set<BTerm_t>						Bolsa_Palabras_t;
typedef Bolsa_Palabras_t*					pBolsa_Palabras_t;
typedef Bolsa_Palabras_t::iterator			IBolsa_Palabras_t;
typedef Bolsa_Palabras_t::const_iterator	c_IBolsa_Palabras_t;

typedef long long unsigned int              Elem_Z_t;

typedef set< Elem_Z_t >				        Conj_Z_t;
typedef Conj_Z_t::iterator			        IConj_Z_t;
typedef Conj_Z_t::const_iterator	        c_IConj_Z_t;

typedef map< BTerm_t , Conj_Z_t >	        Funct_BTerm_Nums_t;
typedef Funct_BTerm_Nums_t::iterator		IFunct_BTerm_Nums_t;
typedef Funct_BTerm_Nums_t::const_iterator	c_IFunct_BTerm_Nums_t;

typedef map< Elem_Z_t , Bolsa_Palabras_t >	Funct_Num_BTerms_t;
typedef Funct_Num_BTerms_t::iterator		IFunct_Num_BTerms_t;
typedef Funct_Num_BTerms_t::const_iterator	c_IFunct_Num_BTerms_t;

class BoolFunct {
	class res_parser_l1 {
		friend class BoolFunct;
		enum est_l1  {ERROR_l1=false,BIEN_l1=true};
		est_l1 Est;
		int    NE;
		int    NS;
		res_parser_l1();
		res_parser_l1(const res_parser_l1 & arg);
		res_parser_l1(const string & cad_in);
	};

	class res_parser_nl1 {
		friend class BoolFunct;
		enum est_nl1 {EI_nl1,EP1L_nl1,EPT_nl1,EP2L_nl1,DEF_nl1,ERROR_nl1,BIEN_nl1};
		est_nl1		Est;
		BTerm_t		BoolPalIn;
		BTerm_t		BoolPalOut;
		res_parser_nl1();
		res_parser_nl1(est_nl1 arg_est,int nin,int nout);
		res_parser_nl1(const res_parser_nl1 & arg);
		res_parser_nl1(const string & lin_in , const int ns ,
					   const int ne );
	};

	friend class res_parser_l1;
	friend class res_parser_nl1;
public:
	res_parser_nl1		estado_nl1	;
	res_parser_l1		estado_l1	;
	bool				min_MAX		;
	int					n_terms		;
	int					n_linea		;
	unsigned int		f_k			;
	BFunct_t			bf			;
	BFunct_Ord_t		bolsa[2]	;
	bool				ix			;
	unsigned char		ind_grupo	;
	Impl_Primos_set_t	impl_primos	;
	Impl_Primos_set_t   impl_esenciales;
public: 
	BoolFunct(bool arg = true); 
	BoolFunct(const BoolFunct & arg);
	BoolFunct(istream & sin,int f_k,bool vt);
	~BoolFunct();
	bool EstadoFinalParser_BIEN() const;
	bool EstadoFinalParser_ERROR() const;
	const BFunct_t & g_access_funct() const;
	inline int g_NE() const {return this->estado_l1.NE;}
	inline int g_NS() const {return this->estado_l1.NS;}
public: 
	void ordena_por_num_1s();
	void crea_tabla_por_adyacencias();
	bool comprobar_adyacencias(const BTerm_t &,const BTerm_t &) const;
	BTerm_t operar_adyacencias(const BTerm_t &,const BTerm_t &) const;
	unsigned int cuenta_1s_de_la_palabra( IBTerm_t &, c_IBTerm_t & );
	void Generar__F_Num_Terms(Funct_BTerm_Nums_t &,Conj_Z_t &,Bolsa_Palabras_t &, Funct_Num_BTerms_t &) const;
	void Iteracion__Deteccion_Primos_Esenciales_ETC(Funct_BTerm_Nums_t &,Conj_Z_t &,Bolsa_Palabras_t &,Funct_Num_BTerms_t &) const;
	void Detectar_Terminos_Principales_y_Borrar_Los_Mas_pesados(Funct_BTerm_Nums_t &,Conj_Z_t &,Bolsa_Palabras_t &,Funct_Num_BTerms_t &) const;
	void Limpiar__F_Term_Nums__de_terminos_vacios(Funct_BTerm_Nums_t & f_term_nums);
	IBFunct_t begin();
	c_IBFunct_t end() const;
	void asignar_strings_a_listfunct(int n ,	int m ,
									 const string & cad_in		);

	
	
	static string bterm2string(BTerm_t cont);

	

	static BTerm_t string2bterm(string arg);
	void Genera_Tabla_De_Adyacencias_Por_Recurrencia();
	void Genera_Tabla_De_Implicantes_Primos() ;
	void saca_primos_esenciales();
	friend void saca_bolsa(BoolFunct &,bool);
	friend void saca_lista(BoolFunct &);
	friend void saca_conjunto(BoolFunct &);

};

void saca_mapa(Funct_BTerm_Nums_t & arg);
void saca_mapa_inverso( Funct_Num_BTerms_t & arg );
void saca_conjunto_de_palabras(Bolsa_Palabras_t & arg);

bool es_booleano(char car);
bool es_true(char car);
bool es_false(char car);
bool es_dncare(char car);
bool_l3v valor_de(char car);
bool es_separador(char car);
bool es_punto_y_coma(char car);
bool es_fin_de(char car);
bool es_numerico(char car);
bool es_significativo(char car);
bool es_blanco(char car);
bool no_es_numerico(char car);
bool es_valido(char car);
bool es_fin_de_cadena(char car);
bool es_fdl(char car);
bool es_fdc(char car);

char* fill_cstr(char c,unsigned n);

#endif // ESTRUCTURASFUNCIONES_HPP
