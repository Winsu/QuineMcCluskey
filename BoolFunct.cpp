#include "BoolFunct.hpp"
#include <cctype>
#include <iterator>
#include <map>
#include <functional>

using namespace std;

BoolFunct::res_parser_l1::res_parser_l1()
{
    NE  = 0;
    NS  = 1;
    Est = BIEN_l1;
}

BoolFunct::res_parser_l1::res_parser_l1(const res_parser_l1 & arg)
{
    NE = arg.NE ;
    NS = arg.NS ;
    Est= arg.Est;
}

BoolFunct::res_parser_l1::res_parser_l1(const string & cad_in) {
	stringstream sNE,sNS;
	stringstream * p_sNx = &sNE;
	sNE.clear();
	sNS.clear();
	bool es_primer_punto_y_coma = true;
	for( int I=0; (!es_fin_de(cad_in[I]))&&(Est!=ERROR_l1) ; I++ ) {
		if (es_valido(cad_in[I])) {
			if (es_numerico(cad_in[I])) {
					(*p_sNx) << cad_in[I];
			}
			else if (no_es_numerico(cad_in[I])) {
				if (es_punto_y_coma(cad_in[I])) {
					if (es_primer_punto_y_coma) {
						es_primer_punto_y_coma = false;
						p_sNx = &sNS;
					}
					else {
						sNE >> NE;
						sNS >> NS;
						Est = BIEN_l1;
						return;
					}
				}
			}
		}
		else {
			NE         	= -1;
			NS         	= -1;
			Est 		= ERROR_l1;
			return;
		}
	}
}

BoolFunct::res_parser_nl1::res_parser_nl1(	const string & lin_in ,
											const int ne , const int ns	)
{
	string cad1out;
	string cad2out;
	cad1out.clear();
	cad2out.clear();
	int necount=0;
	int nscount=0;
	
	est_nl1		E 		= EI_nl1;
	int			index 	= 0;
	const int	maximo 	= lin_in.length();
	char 		X 		= lin_in[index];

	while ((index < maximo)&&(E != ERROR_nl1)) {
		switch(E) {
			case EI_nl1		:
				switch(X) {
					case 't'	:
					case 'T'	:
						E = EP1L_nl1;
						cad1out += 'T';
						necount++;
						break;
					case 'f'	:
					case 'F'	:
						E = EP1L_nl1;
						cad1out += 'F';
						necount++;
						break;
					case 'x'	:
					case 'X'	:
					case '-'	:
						E = EP1L_nl1;
						cad1out += 'x';
						necount++;
						break;
					case ' '	:
					case '\t'	:
						E = EI_nl1;
						break;
					case '>'	:
					case '\n'	:
					case '\0'	:
					case '\r'	:
					case '\f'	:
					default		:
						E = ERROR_nl1;
				}
				break;
			case EP1L_nl1     :
				switch(X) {
					case '>'	:
						E = EPT_nl1;
						break;
					case 't'	:
					case 'T'	:
						E = EP1L_nl1;
						cad1out += 'T';
						necount++;
						break;
					case 'f'	:
					case 'F'	:
						E = EP1L_nl1;
						cad1out += 'F';
						necount++;
						break;
					case 'X'	:
					case 'x'	:
					case '-'	:
						E = EP1L_nl1;
						cad1out += 'x';
						necount++;
						break;
					case ' '	:
					case '\t'	:
						E = EP1L_nl1;
						break;
					case '\n'	:
					case '\0'	:
					case '\r'	:
					case '\f'	:
					case ';'	:
					default		:
						E = ERROR_nl1;
				}
				break;
			case EPT_nl1	:
				switch(X) {
					case 't'	:
					case 'T'	:
						E = EP2L_nl1;
						cad2out += 'T';
						nscount++;
						break;
					case 'f'	:
					case 'F'	:
						E = EP2L_nl1;
						cad2out += 'F';
						nscount++;
						break;
					case 'X'	:
					case 'x'	:
					case '-'	:
						E = EP2L_nl1;
						cad2out += 'x';
						nscount++;
						break;
					case ' '	:
					case '\t'	:
						E = EPT_nl1;
						break;
					case '>'	:
					case '\n'	:
					case '\0'	:
					case '\r'	:
					case '\f'	:
					case ';'	:
					default		:
						E = ERROR_nl1;
				}
				break;
			case EP2L_nl1	:
				switch(X) {
					case '\n'	:
					case '\0'	:
					case '\r'	:
					case '\f'	:
					case ';'	:
						E = DEF_nl1;
						break;
					case 't'	:
					case 'T'	:
						E = EP2L_nl1;
						cad2out += 'T';
						nscount++;
						break;
					case 'f'	:
					case 'F'	:
						E = EP2L_nl1;
						cad2out += 'F';
						nscount++;
						break;
					case 'X'	:
					case 'x'	:
					case '-'	:
						E = EP2L_nl1;
						cad2out += 'x';
						nscount++;
						break;
					case ' '	:
					case '\t'	:
						E = EP2L_nl1;
						break;
					case '>'	:
					default		:
						E = ERROR_nl1;
				}
				break;
			case DEF_nl1	:
				E = DEF_nl1;
				break;
			case ERROR_nl1	:
			default			:
				E = ERROR_nl1;
		}
		index++;
		X = lin_in[index];
	}
	if (E==DEF_nl1){
		if ((nscount==ns) && (necount==ne)) E=BIEN_nl1 ;
		else 								E=ERROR_nl1;
	}
	if (E==BIEN_nl1) {
		BoolPalIn  = BoolFunct::string2bterm(cad1out);
		BoolPalOut = BoolFunct::string2bterm(cad2out);
	}
	Est = E;
}


BoolFunct::res_parser_nl1::res_parser_nl1(est_nl1 arg_est,int nin,int nout):Est(arg_est)
{
	BoolPalIn.resize(nin);
	BoolPalOut.resize(nout);
}

BoolFunct::res_parser_nl1::res_parser_nl1():Est(EI_nl1)
{
	BoolPalIn.resize(1);
	BoolPalOut.resize(1);
}

BoolFunct::res_parser_nl1::res_parser_nl1(const res_parser_nl1 & arg):Est(arg.Est)
{
	BoolPalIn.resize(arg.BoolPalIn.size());
	BoolPalOut.resize(arg.BoolPalOut.size());
	BoolPalIn = arg.BoolPalIn;
	BoolPalOut = arg.BoolPalOut;
}

BoolFunct::BoolFunct(bool arg)
{
	min_MAX = arg;

	estado_nl1.Est	= res_parser_nl1::BIEN_nl1;
	estado_l1.Est	= res_parser_l1::BIEN_l1;
	estado_l1.NE	= 0;
	estado_l1.NS	= 1;
	n_terms			= 0;
	n_linea			= 0;
	ix				= false;
	ind_grupo		= 0;
	BTerm_t	palabra(1);
	if (arg)
		palabra[0]=true;
	else
		palabra[0]=false;
	bf.push_front(palabra);
}

BoolFunct::~BoolFunct(){}

const BFunct_t & BoolFunct::g_access_funct() const
{return (bf);}

bool BoolFunct::EstadoFinalParser_BIEN() const {
	return ((estado_l1.Est==res_parser_l1::BIEN_l1)and(estado_nl1.Est==res_parser_nl1::BIEN_nl1));
}

bool BoolFunct::EstadoFinalParser_ERROR() const {
	return ((estado_l1.Est==res_parser_l1::ERROR_l1)or(estado_nl1.Est==res_parser_nl1::ERROR_nl1));
}


string BoolFunct::bterm2string(BTerm_t cont) {
	string ret;		
	ret.clear();	
	IBTerm_t		it		=	cont.begin();
	c_IBTerm_t		itend	=	cont.end();
	
	for( ; it < itend ; it++ )
		if ((*it)==T3v)
			ret += 'T';
		else if ((*it)==F3v)
			ret += 'F';
		else
			ret += 'x';

	return ret;
}


BTerm_t BoolFunct::string2bterm(string arg) {
    const int n = arg.size();
	BTerm_t ret(n);
    for(int I=0; I<n; I++)
        if ((arg[I] == 'f')||(arg[I] == 'F'))
	  	    ret[I]=F3v ;
        else if ((arg[I] == 't')||(arg[I] == 'T'))
	  	    ret[I]=T3v ;
		else
			ret[I]=x3v ;
    return ret;
}

void BoolFunct::asignar_strings_a_listfunct(int n,int m,const string & cad_in) {
	
    BTerm_t pal(n);

    for( int J = 0, JJ = 0 ; J < m ; J++,JJ+=(n+1) ) {
		string cpal;
		cpal.clear();
		for( int I = 0 ; I < n ; ++I ) {
			cpal += cad_in[I+JJ];
		}
		
		pal=BoolFunct::string2bterm(cpal);
		
		bf.push_back(pal);
		
    }
    return;
}

bool es_booleano(char car){
	if (isalpha(car))
			return (car=='T' || car=='t' || car=='F' || car=='f' || car=='x' || car=='X' || car=='-');
	else	return false;
}

bool es_true(char car){
	if (isalpha(car))
			return (car=='T' || car=='t');
	else	return false;
}

bool es_false(char car){
	if (isalpha(car))
			return (car=='F' || car=='f');
	else	return false;
}

bool es_dncare(char car){
	if (isalpha(car))
			return (car=='X' || car=='x' || car=='-');
	else	return false;
}

bool_l3v valor_de(char car) {
	if (es_false(car)) return F3v;
	else if (es_true(car)) return T3v;
	else return x3v;
}

bool es_separador(char car){
	return (car=='>');
}

bool es_punto_y_coma(char car){
	return (car==';');
}

bool es_fin_de(char car){
	if (car=='\0') return true;
	else return false;
}

bool es_numerico(char car){
	return (isdigit(car));
}

bool es_significativo(char car) {
	return (isdigit(car) || es_punto_y_coma(car));
}

bool es_blanco(char car) {
	return (isspace(car));
}

bool no_es_numerico(char car) {
	return (es_blanco(car) || es_punto_y_coma(car));
}

bool es_valido(char car) {
	return (es_numerico(car) || es_blanco(car) || es_punto_y_coma(car));
}

bool es_fin_de_cadena(char car) {
	return ((es_fin_de(car))                      ||  \
			(car=='@')     	                   	  ||  \
		    (car=='#')	                          ||  \
		    (car=='!')	                          ||  \
		    ((car<=((char)10))&&(!es_blanco(car)))  ||  \
		    (car=='\0')
	);
}

bool es_fdl(char car) {
	return ( (car==';') || es_blanco(car) );
}

bool es_fdc(char car) {
	return ( (car=='\n') || (car=='\0') );
}

char* fill_cstr(char* cstr, char c,unsigned n) {
	for(unsigned i=0;i<(n-1);i++) cstr[i]=c;
	cstr[n-1]='\0';
	return cstr;
}


BoolFunct::BoolFunct(istream & sin,int arg_f_k,bool vt) {
	ix						= false;
	ind_grupo				= 0;
	f_k						= arg_f_k;
	min_MAX					= vt;
	BoolFunct & cthis		= (*this);
	res_parser_l1    l1;
	res_parser_nl1   nl1;
	string str_to_be_parsed;
	str_to_be_parsed.clear();
	char cstr_to_be_parsed[128];
	fill_cstr(cstr_to_be_parsed,'\0',128);
	bool es_la_l1			= true;
	bool es_la_1a_nl1		= true;
	int n_terms				= 0;
	int n_linea				= 1;
	while ((!sin.eof()) && sin.good() && ((l1.Est!=res_parser_l1::ERROR_l1)and(nl1.Est!=res_parser_nl1::ERROR_nl1))) {
		sin.getline(cstr_to_be_parsed,128,'\n');
		if (sin.good()) {
			n_linea++;
			str_to_be_parsed = static_cast<string>(cstr_to_be_parsed);
			if (es_la_l1) {
				l1				= res_parser_l1(str_to_be_parsed);
				es_la_l1		= false;
				es_la_1a_nl1	= true;
			}
			else {
				nl1				= res_parser_nl1(str_to_be_parsed,l1.NE,l1.NS);
				if ((nl1.BoolPalOut[f_k])==((vt)?T3v:F3v)){
					bf.push_back(nl1.BoolPalIn);
					n_terms ++;
				}
				es_la_l1		= false;
				es_la_1a_nl1	= false;
			}
		}
		fill_cstr(cstr_to_be_parsed,'\0',128);
	}

	cthis.estado_l1.Est		=	l1.Est;
	cthis.estado_nl1.Est	=	nl1.Est;
	cthis.n_linea			=	n_linea;
	cthis.n_terms			=	n_terms;
	cthis.estado_l1.NE		=	l1.NE;
	cthis.estado_l1.NS		=	l1.NS;
}

IBFunct_t BoolFunct::begin() {
	return bf.begin();
}
c_IBFunct_t BoolFunct::end() const {
	return bf.end();
}

void BoolFunct::ordena_por_num_1s() {
	ix = false;
	const unsigned int num_groups = g_NE()+1;
	IBFunct_Ord_t   it_bolsa  = bolsa[ix?1:0].begin();

	for (unsigned int i = 0; i < num_groups ; ++i){
		bolsa[ix?1:0].push_front(make_pair(BFunct_t(),num_groups-i-1));
	}

	for (unsigned int i = 0; i < num_groups-1 ; ++i){
		bolsa[ix?0:1].push_front(make_pair(BFunct_t(),num_groups-i-2));
	}

	c_IBFunct_t   	fin = bf.end();
	IBFunct_t 		it 	= bf.begin();

	for( ; it != fin ; ++it ) {

		c_IBTerm_t pfin = it->end();
		IBTerm_t   pit  = it->begin();
		unsigned int n_g = BoolFunct::cuenta_1s_de_la_palabra(pit,pfin);
		IBFunct_Ord_t   it_bolsa  = bolsa[ix?1:0].begin();
		c_IBFunct_Ord_t   fin_bolsa  = bolsa[ix?1:0].end();
	
		for(; (it_bolsa != fin_bolsa)and((*it_bolsa).second!=n_g); ++it_bolsa);
		
		(*it_bolsa).first.push_front(*it);
	}
	++ind_grupo;
}

bool BoolFunct::comprobar_adyacencias(const BTerm_t & arg1,const BTerm_t & arg2) const {
	const unsigned int sz = arg1.size();
	if (sz != arg2.size()) return false;
	else {
		unsigned int distancia_H = 0;
		for(unsigned int i=0;i<sz;++i)
			if(arg1[i]==arg2[i]) continue;
			else if ((arg1[i]==x3v)or(arg2[i]==x3v)) distancia_H+=(this->g_NE())+1;
			else ++distancia_H;
		if (distancia_H == 1) return true;
		else return false;
	}
}

BTerm_t BoolFunct::operar_adyacencias(const BTerm_t & arg1,const BTerm_t & arg2) const {
	
	BTerm_t ret(arg1);
	const unsigned int sz = arg1.size();
	unsigned int i = 0;
	for(;(i<sz)and(arg1[i]==arg2[i]);++i);
	ret[i] = x3v;
	return ret;
}

unsigned int BoolFunct::cuenta_1s_de_la_palabra(IBTerm_t & it,c_IBTerm_t & fin){
	unsigned int cuenta_de_1s = 0;
	for( ; it != fin ; ++it )
		if ((*it)==T3v) ++cuenta_de_1s;
	return cuenta_de_1s;
}

void BoolFunct::crea_tabla_por_adyacencias() {
	const unsigned int num_groups		= g_NE() + 1;
		  unsigned int ind_group_act	= num_groups - ind_grupo;

	c_IBFunct_Ord_t fin_bolsa			= bolsa[ix?1:0].end();
	c_IBFunct_Ord_t fin_bolsa_real		= bolsa[ix?1:0].end()--;
	IBFunct_Ord_t   it_bolsa			= bolsa[ix?1:0].begin();
	IBFunct_Ord_t   it_bolsa_sig_group	= (++(bolsa[ix?1:0].begin()));

	bolsa[ix?0:1].clear();
	for ( int i = ind_group_act-1 ; i >= 0 ; --i){
		bolsa[ix?0:1].push_front(make_pair(BFunct_t(),i));
	}

	Bolsa_Palabras_t	adyacencias_guardadas;

	c_IBFunct_Ord_t fin_bolsa_sig		= bolsa[ix?0:1].end();
	IBFunct_Ord_t   it_bolsa_sig		= bolsa[ix?0:1].begin();

	for (;it_bolsa!=fin_bolsa_real;++it_bolsa,++it_bolsa_sig,++it_bolsa_sig_group) {
		bool con_adyacencias = false;
		IBFunct_t	it1 = (*it_bolsa).first.begin();
		c_IBFunct_t  ite1= (*it_bolsa).first.end();
		c_IBFunct_t  ite2= (*it_bolsa_sig_group).first.end();

		for(;it1!=ite1;++it1) {
			IBFunct_t	it2 = (*it_bolsa_sig_group).first.begin();
			for(;it2!=ite2;++it2) {
				if (comprobar_adyacencias(*it1,*it2)) {
					adyacencias_guardadas.insert(*it2);
					(*it_bolsa_sig).first.push_front(operar_adyacencias(*it1,*it2));
					con_adyacencias = true;
				}
			}
			if ((!con_adyacencias)and(! adyacencias_guardadas.count(*it1) )) impl_primos.insert(*it1);
		}
	}

	c_IBFunct_Ord_t fin_bolsa_uc			= bolsa[ix?1:0].end();
	IBFunct_Ord_t   it_bolsa_uc				= bolsa[ix?1:0].begin();
	for(;it_bolsa_uc!=fin_bolsa_uc;++it_bolsa_uc);
	--it_bolsa_uc;
	IBFunct_t it1 = (*it_bolsa_uc).first.begin();
	c_IBFunct_t ite1= (*it_bolsa_uc).first.end();
	for(;it1!=ite1;++it1) {
		if (! adyacencias_guardadas.count(*it1) ) impl_primos.insert(*it1);
	}

	++ind_grupo;
	ix = !(ix);
}

void BoolFunct::Genera_Tabla_De_Adyacencias_Por_Recurrencia() {
	ordena_por_num_1s();
	while(ind_grupo <= (g_NE()))
		crea_tabla_por_adyacencias();
	bolsa[0].clear();
	bolsa[1].clear();
}

void BoolFunct::Genera_Tabla_De_Implicantes_Primos() {
  
    Funct_BTerm_Nums_t f_term_nums;
    Funct_Num_BTerms_t f_num_terms;
    Conj_Z_t           conj_terms_en_dec;
	
	BTerm_t destino(estado_l1.NE);
	unsigned char num_Xs = 0;
	vector< bool >	posiciones_Xs(static_cast<unsigned char>(estado_l1.NE));
    Conj_Z_t conj_nums;
    Elem_Z_t representacion;

	IImpl_Primos_set_t 		itip 		= impl_primos.begin();
    c_IImpl_Primos_set_t 	itip_end 	= impl_primos.end();
	for ( ; itip != itip_end ; ++itip ) {
		num_Xs = 0;
		for ( unsigned char i=0 ; i < static_cast<unsigned char>(estado_l1.NE) ; ++i ) {
			if (((*itip)[i]) == x3v) {
				++num_Xs;
				posiciones_Xs[i] =  true;
			}
			else {
				posiciones_Xs[i] = false;
			}
		}
		
		if (num_Xs == 0) {
			destino = *itip;
			representacion = 0;
			for ( unsigned char r = 0 ; r < static_cast<unsigned char>(estado_l1.NE) ; ++r ){
				representacion *= 2;
				if (destino[r]==T3v) ++representacion;
			}
			conj_nums.insert(representacion);
			conj_terms_en_dec.insert(representacion);
			f_term_nums.insert( make_pair(destino,conj_nums) );
			conj_nums.clear();
		}
		else {
			BTerm_t pal(num_Xs);
			for (unsigned char q=0 ; q < static_cast<unsigned char>(num_Xs) ; ++q )
				pal[q]=false;
			destino = *itip;
			Elem_Z_t pot_2_num_Xs = 2;
			for (unsigned char t = 1 ; t < num_Xs ; ++t)
				pot_2_num_Xs *= 2;
			for (Elem_Z_t i=0; i < pot_2_num_Xs ; ++i) {
				
				unsigned char s = 0;
				for(unsigned char t=0 ; t < static_cast<unsigned char>(estado_l1.NE) ; ++t) {
					if (posiciones_Xs[t]) {
						destino[t]=pal[s];
						++s;
					}
				}
				representacion = 0;
				for ( unsigned char r=0 ; r <static_cast<unsigned char>(estado_l1.NE) ; ++r ){
					representacion *= 2;
					if (destino[r]==T3v) ++representacion;
				}
				conj_nums.insert(representacion);
				conj_terms_en_dec.insert(representacion);
				
				bool carry = true;
				for (unsigned char p = 0; p < num_Xs ; ++p) {
					pal[p] = pal[p] xor carry;
					if ((pal[p] and carry) == T3v) carry = true;
					else carry = false;
				}
				destino = *itip;
			}
			f_term_nums.insert( make_pair(destino,conj_nums) );
			conj_nums.clear();
		}
	}
	saca_mapa(f_term_nums);
	cout << " Number of prime impliclants: " << f_term_nums.size() << endl;
	
	
	Bolsa_Palabras_t    conj_terms;
	Generar__F_Num_Terms(f_term_nums,conj_terms_en_dec,conj_terms,f_num_terms);
	saca_mapa_inverso(f_num_terms);
	Iteracion__Deteccion_Primos_Esenciales_ETC(f_term_nums,conj_nums,conj_terms,f_num_terms);
	impl_esenciales.insert(conj_terms.begin(),conj_terms.end());
	saca_conjunto_de_palabras(conj_terms);
	saca_mapa(f_term_nums);
	Generar__F_Num_Terms(f_term_nums,conj_terms_en_dec,conj_terms,f_num_terms);
	saca_mapa_inverso(f_num_terms);
	Limpiar__F_Term_Nums__de_terminos_vacios(f_term_nums);
	Generar__F_Num_Terms(f_term_nums,conj_terms_en_dec,conj_terms,f_num_terms);
	
	while(!(f_term_nums.empty())) {
		std::cout << std::endl << " Entro en un nuevo bucle porque f_term_nums no es vacio. " << std::endl;
		Detectar_Terminos_Principales_y_Borrar_Los_Mas_pesados(f_term_nums,conj_nums,conj_terms,f_num_terms);
		impl_esenciales.insert(conj_terms.begin(),conj_terms.end());
		saca_conjunto_de_palabras(conj_terms);
		saca_mapa(f_term_nums);
		Generar__F_Num_Terms(f_term_nums,conj_terms_en_dec,conj_terms,f_num_terms);
		Iteracion__Deteccion_Primos_Esenciales_ETC(f_term_nums,conj_nums,conj_terms,f_num_terms);
		impl_esenciales.insert(conj_terms.begin(),conj_terms.end());
		saca_conjunto_de_palabras(conj_terms);
		saca_mapa(f_term_nums);
		Generar__F_Num_Terms(f_term_nums,conj_terms_en_dec,conj_terms,f_num_terms);
		saca_mapa_inverso(f_num_terms);
		Limpiar__F_Term_Nums__de_terminos_vacios(f_term_nums);
		Generar__F_Num_Terms(f_term_nums,conj_terms_en_dec,conj_terms,f_num_terms);
	}
	return;
}
void BoolFunct::Limpiar__F_Term_Nums__de_terminos_vacios(Funct_BTerm_Nums_t & f_term_nums) {
	Bolsa_Palabras_t bolsa_terminos;
	c_IFunct_BTerm_Nums_t it_end = f_term_nums.end();
	IFunct_BTerm_Nums_t   it     = f_term_nums.begin();
	for( ;it != it_end; ++it) {
		if ((it->second).empty()) {
			bolsa_terminos.insert(it->first);
		}
	}
	c_IBolsa_Palabras_t it_bp_end = bolsa_terminos.end();
	IBolsa_Palabras_t   it_bp     = bolsa_terminos.begin();
	for( ;it_bp != it_bp_end; ++it_bp) {
		f_term_nums.erase(*it_bp);
	}
	return;
}
void BoolFunct::Generar__F_Num_Terms(Funct_BTerm_Nums_t & f_term_nums,
                                     Conj_Z_t & conj_terms_en_dec,
									 Bolsa_Palabras_t & conj_terms,
									 Funct_Num_BTerms_t & f_num_terms) const {
	
	conj_terms.clear();
	f_num_terms.clear();
	c_IConj_Z_t itz_end = conj_terms_en_dec.end();
	IConj_Z_t   itz     = conj_terms_en_dec.begin();
	for( ; itz != itz_end ; ++itz ){
		
		c_IFunct_BTerm_Nums_t it_bt_nums_end = f_term_nums.end();
		IFunct_BTerm_Nums_t it_bt_nums = f_term_nums.begin();
		for( ; it_bt_nums != it_bt_nums_end ; ++it_bt_nums ) {
			if (it_bt_nums->second.count(*itz)>0) {
				conj_terms.insert(it_bt_nums->first);
			}
		}
		if (conj_terms.size()>0) {
			f_num_terms.insert( make_pair(*itz,conj_terms) );
		}
	    conj_terms.clear();
	}
	return;
}
void BoolFunct::Iteracion__Deteccion_Primos_Esenciales_ETC(
									 Funct_BTerm_Nums_t & f_term_nums,
                                     Conj_Z_t & conj_nums,
									 Bolsa_Palabras_t & conj_terms,
									 Funct_Num_BTerms_t & f_num_terms) const {
	conj_terms.clear();
	BTerm_t palabra;
	IFunct_Num_BTerms_t it_num_bts = f_num_terms.begin();
	c_IFunct_Num_BTerms_t it_num_bts_end = f_num_terms.end();
	for( ; it_num_bts != it_num_bts_end ; ++it_num_bts ) {
		if((it_num_bts->second.size())==1) {
			palabra = (*(it_num_bts->second.begin()));
			conj_terms.insert(palabra);
			conj_nums = f_term_nums[palabra];
			IConj_Z_t it_Z = conj_nums.begin();
			c_IConj_Z_t it_Z_end = conj_nums.end();
			for( ; it_Z != it_Z_end ; ++it_Z ) {
				c_IBolsa_Palabras_t it_1_end = f_num_terms[*it_Z].end();
				IBolsa_Palabras_t   it_1 = f_num_terms[*it_Z].begin();
				for( ; it_1 != it_1_end ; ++ it_1 ) {
					f_term_nums[*it_1].erase(*it_Z);
				}
			}
		}
		f_term_nums.erase(palabra);
	}
	return;
}

void BoolFunct::Detectar_Terminos_Principales_y_Borrar_Los_Mas_pesados (
				Funct_BTerm_Nums_t & f_term_nums,
				Conj_Z_t & conj_nums,
				Bolsa_Palabras_t & conj_terms,
				Funct_Num_BTerms_t & f_num_terms ) const {
	c_IFunct_BTerm_Nums_t   it_bterm_nums_end = f_term_nums.end();
	IFunct_BTerm_Nums_t		it_bterm_nums	  = f_term_nums.begin();
	IFunct_BTerm_Nums_t		it_bterm_nums_max;
	IFunct_BTerm_Nums_t		it_bterm_nums_min;

	conj_terms.clear();
	BTerm_t palabra;
	palabra.clear();
	
	c_IFunct_Num_BTerms_t it_num_bts_end = f_num_terms.end();	
	IFunct_Num_BTerms_t it_num_bts = f_num_terms.begin();
	
	unsigned int numero = it_bterm_nums->second.size();
	unsigned int numero_max = numero;
	it_bterm_nums_max = it_bterm_nums;
	unsigned int numero_min = numero;
	it_bterm_nums_min = it_bterm_nums;
	++it_bterm_nums;
	for( ; it_bterm_nums != it_bterm_nums_end ; ++it_bterm_nums ) {
		numero = it_bterm_nums->second.size();
		if (numero > numero_max) {
			numero_max = numero;
			it_bterm_nums_max = it_bterm_nums;
		}
		else if (numero < numero_min) {
			numero_min = numero;
			it_bterm_nums_min = it_bterm_nums;
		}
	}
	if (numero_max == numero_min) {
		it_bterm_nums_min	  = f_term_nums.begin();
		it_bterm_nums_max	  = ++it_bterm_nums_max; 
	}
	
	palabra.clear();
	palabra = it_bterm_nums_max->first;
	conj_terms.insert(palabra);
	conj_nums = it_bterm_nums_max->second;
	c_IConj_Z_t it_Z_end = conj_nums.end();
	IConj_Z_t it_Z = conj_nums.begin();
	for( ; it_Z != it_Z_end ; ++it_Z ) {
		c_IBolsa_Palabras_t it_1_end = f_num_terms[*it_Z].end();
		IBolsa_Palabras_t   it_1 = f_num_terms[*it_Z].begin();
		for( ; it_1 != it_1_end ; ++ it_1 ) {
			f_term_nums[*it_1].erase(*it_Z);
		}
	}
	f_term_nums.erase(palabra);
	return;
}

void  BoolFunct::saca_primos_esenciales() {
	saca_conjunto_de_palabras(impl_esenciales);
	return;
}

void saca_mapa( Funct_BTerm_Nums_t & arg ) {
	IFunct_BTerm_Nums_t 	it		=arg.begin();
	c_IFunct_BTerm_Nums_t 	itend	=arg.end();
	for ( ; it != itend ; ++it) {
			cout << " A prime implicant : " << endl;
			string salida_palabra(BoolFunct::bterm2string(it->first));
			cout << "	" << salida_palabra << endl;
			c_IConj_Z_t     itn_end = it->second.end();
			IConj_Z_t       itn     = it->second.begin();
			for( ; itn != itn_end ; ++itn) {
				cout << (*itn) << endl;
			}
			cout << " Term of prime implicant. " << endl;
	}
	cout << endl;
	return;
}

void saca_mapa_inverso( Funct_Num_BTerms_t & arg ) {
	IFunct_Num_BTerms_t 	it		=arg.begin();
	c_IFunct_Num_BTerms_t 	itend	=arg.end();
	for ( ; it != itend ; ++it) {
			cout << " A number corresponding to a miniterm: " << endl;
			cout << "	" << (it->first) << endl;
			c_IBolsa_Palabras_t   itn_end = it->second.end();
			IBolsa_Palabras_t     itn     = it->second.begin();
			for( ; itn != itn_end ; ++itn) {
			    string salida_palabra(BoolFunct::bterm2string(*itn));
				cout << salida_palabra << endl;
			}
			cout << " Term of the number corresponding of the miniterm. " << endl;
	}
	cout << endl;
	return;
}

void saca_bolsa(BoolFunct & arg,bool ind_bool) {
	IBFunct_Ord_t it2=(arg.bolsa[ind_bool?1:0]).begin();
	c_IBFunct_Ord_t fin2=(arg.bolsa[ind_bool?1:0]).end();
	for (unsigned int ind = 0 ; it2 != fin2 ; ++it2,++ind) {
		IBFunct_t itg=((*it2).first).begin();
		c_IBFunct_t fing=((*it2).first).end();
		cout << " itg es igual que fing ?	" << ((itg == fing)?("vacio"):("no vacio")) << endl;
		cout << "	Numero de Grupo es	" << (*it2).second << "	;	" << ind << endl;
		for( ; itg != fing ; ++itg) {
			string salida_palabra(BoolFunct::bterm2string(*itg));
			cout << '	' << salida_palabra << " en grupo " << (*it2).second << endl;
		}
	}
	return;
}

void saca_lista(BoolFunct & arg) {
	IBFunct_t it2=arg.bf.begin();
	c_IBFunct_t fin2=arg.bf.end();
	for (; it2 != fin2 ; ++it2) {
			string salida_palabra(BoolFunct::bterm2string(*it2));
			cout << '	' << salida_palabra << endl;
	}
	return;
}

void saca_conjunto(BoolFunct & arg) {
	IImpl_Primos_set_t it		=arg.impl_primos.begin();
	c_IImpl_Primos_set_t itend	=arg.impl_primos.end();
	for (; it != itend ; ++it) {
			string salida_palabra(BoolFunct::bterm2string(*it));
			cout << '	' << salida_palabra << endl;
	}
	return;
}

void saca_conjunto_de_palabras(Bolsa_Palabras_t & arg) {
	IBolsa_Palabras_t it		=arg.begin();
	c_IBolsa_Palabras_t itend	=arg.end();
	for (; it != itend ; ++it) {
			string salida_palabra(BoolFunct::bterm2string(*it));
			cout << '	' << salida_palabra << endl;
	}
	return;
}
