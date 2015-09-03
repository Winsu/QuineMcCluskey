#ifndef L3V_T_HPP
#define L3V_T_HPP

#include "definitions.hpp"

#include <iostream>
using namespace std;

class bool_l3v : private l3v {
private:
	l3v_t val;
public:
	inline operator int() const;
	inline operator unsigned int() const;
	inline operator char() const;
	inline operator unsigned char() const;
	inline bool_l3v operator ^ (bool_l3v a) const;
	inline bool_l3v operator || (bool_l3v a) const;
	inline bool_l3v operator && (bool_l3v a) const;
	inline bool_l3v operator ^ (bool a) const;
	inline bool_l3v operator || (bool a) const;
	inline bool_l3v operator && (bool a) const;
	inline bool_l3v operator ! () const;
	inline bool operator == (bool_l3v a) const;
	inline bool operator != (bool_l3v a) const;
	inline bool operator < (bool_l3v a) const;
	inline bool operator <= (bool_l3v a) const;
	inline bool operator > (bool_l3v a) const;
	inline bool operator >= (bool_l3v a) const;
	inline bool operator == (bool a) const;
	inline bool operator != (bool a) const;
	inline bool operator < (bool a) const;
	inline bool operator <= (bool a) const;
	inline bool operator > (bool a) const;
	inline bool operator >= (bool a) const;
	friend	inline bool operator == (bool a,bool_l3v b);
	friend	inline bool operator != (bool a,bool_l3v b);
	friend	inline bool operator < (bool a,bool_l3v b);
	friend	inline bool operator <= (bool a,bool_l3v b);
	friend	inline bool operator > (bool a,bool_l3v b);
	friend	inline bool operator >= (bool a,bool_l3v b);
	inline bool_l3v();
	inline bool_l3v(const bool_l3v & a);
	inline bool_l3v(bool a);
	inline bool_l3v(char a);
	inline bool_l3v(int a);
	inline const bool_l3v & operator=(const bool_l3v & a);
	inline const bool_l3v & operator=(bool a);
	inline const bool_l3v & operator=(char a);
	inline const bool_l3v & operator=(int a);
	inline const bool_l3v & operator&=(bool_l3v a);
	inline const bool_l3v & operator|=(bool_l3v a);
	inline const bool_l3v & operator^=(bool_l3v a);
	inline const bool_l3v & operator&=(bool a);
	inline const bool_l3v & operator|=(bool a);
	inline const bool_l3v & operator^=(bool a);
};

bool_l3v::operator int() const {
	return ((val==l3v::F)?((int)0):((val==l3v::T)?((int)1):((int)2)));
}
bool_l3v::operator unsigned int() const {
	return (val==l3v::F?(unsigned)0:(val==l3v::T?(unsigned)1:(unsigned)2));
}
bool_l3v::operator char() const {
	switch (val) {
		case l3v::F : return 'F';
		case l3v::T : return 'T';
		case l3v::x : return 'x';
		default : return 'x';
	}
}
bool_l3v::operator unsigned char() const {
	return (val==l3v::F?(unsigned char)0:(val==l3v::T?(unsigned char)1:(unsigned char)2));
}
bool_l3v bool_l3v::operator ^ (bool_l3v a) const {
	return (l3v::o_exclusiva_logica((l3v::l3v_t)val,(l3v::l3v_t)a.val));
}
bool_l3v bool_l3v::operator || (bool_l3v a) const {
	return (a or val);
}
bool_l3v bool_l3v::operator && (bool_l3v a) const {
	return (a and val);
}
bool_l3v bool_l3v::operator ^ (bool a) const {
	return (l3v::o_exclusiva_logica(val,a));
}
bool_l3v bool_l3v::operator || (bool a) const {
	return (l3v::disyuncion_logica(val,a));
}
bool_l3v bool_l3v::operator && (bool a) const {
	return (l3v::conjuncion_logica(val,a));
}
bool_l3v bool_l3v::operator ! () const {
	return (l3v::negacion_logica(val));
}
bool bool_l3v::operator == (bool_l3v a) const {
	return (val == a.val);
}
bool bool_l3v::operator != (bool_l3v a) const {
	return (val != a.val);
}
bool bool_l3v::operator < (bool_l3v a) const {
	return (l3v::lt(val,a.val));
}
bool bool_l3v::operator <= (bool_l3v a) const {
	return l3v::lt_eq(val,a.val);
}
bool bool_l3v::operator > (bool_l3v a) const {
	return l3v::gt(val,a.val);
}
bool bool_l3v::operator >= (bool_l3v a) const {
	return l3v::gt_eq(val,a.val);
}
bool bool_l3v::operator == (bool a) const {
	if (val==l3v::x) return false;
	else return (a == (val==l3v::T));
}
bool bool_l3v::operator != (bool a) const {
	if (val==l3v::x) return true;
	else return (a != (val==l3v::T));
}
bool bool_l3v::operator < (bool a) const {
	if (val==l3v::x) return false;
	else return (a < (val==l3v::T?true:false));
}
bool bool_l3v::operator <= (bool a) const {
	if (val==l3v::x) return false;
	else return (a <= (val==l3v::T?true:false));
}
bool bool_l3v::operator > (bool a) const {
	if (val==l3v::x) return true;
	else return (a > (val==l3v::T?true:false));
}
bool bool_l3v::operator >= (bool a) const {
	if (val==l3v::x) return true;
	else return (a >= (val==l3v::T?true:false));
}
bool operator == (bool a,bool_l3v b) {
	if (b.val==l3v::x) return false;
	else return (a == (b.val==l3v::T));
}
bool operator != (bool a,bool_l3v b) {
	if (b.val==l3v::x) return true;
	else return (a != (b.val==l3v::T));
}
bool operator < (bool a,bool_l3v b) {
	if (b.val==l3v::x) return true;
	else return (a < (b.val==l3v::T));
}
bool operator <= (bool a,bool_l3v b) {
	if (b.val==l3v::x) return true;
	else return (a <= (b.val==l3v::T));
}
bool operator > (bool a,bool_l3v b) {
	if (b.val==l3v::x) return false;
	else return (a > (b.val==l3v::T));
}
bool operator >= (bool a,bool_l3v b) {
	if (b.val==l3v::x) return false;
	else return (a >= (b.val==l3v::T));
}
bool_l3v::bool_l3v():val(l3v::F){}
bool_l3v::bool_l3v(const bool_l3v & a):val(a.val){}
bool_l3v::bool_l3v(bool a):val(a?l3v::T:l3v::F){}
bool_l3v::bool_l3v(char a):val((a=='F')?l3v::F:((a=='T')?l3v::T:l3v::x)){}
bool_l3v::bool_l3v(int a):val((a==0)?F:((a==1)?T:x)){}
const bool_l3v & bool_l3v::operator=(const bool_l3v & a){
	val=a.val;
	return (*this);
}
const bool_l3v & bool_l3v::operator=(bool a){
	val=(a?l3v::T:l3v::F);
	return (*this);
}
const bool_l3v & bool_l3v::operator=(char a){
	val=(a=='F')?l3v::F:((a=='T')?l3v::T:l3v::x);
	return (*this);
}
const bool_l3v & bool_l3v::operator=(int a){
	val=((a==0)?l3v::F:((a==1)?l3v::T:l3v::x));
	return (*this);
}
const bool_l3v & bool_l3v::operator&=(bool_l3v a) {
	val = l3v::conjuncion_logica((l3v::l3v_t)val,(l3v::l3v_t)a.val);
	return (*this);
}
const bool_l3v & bool_l3v::operator|=(bool_l3v a) {
	val = l3v::disyuncion_logica((l3v::l3v_t)val,(l3v::l3v_t)a.val);
	return (*this);
}
const bool_l3v & bool_l3v::operator^=(bool_l3v a)  {
	val = l3v::o_exclusiva_logica((l3v::l3v_t)val,(l3v::l3v_t)a.val);
	return (*this);
}
const bool_l3v & bool_l3v::operator&=(bool a) {
	val = l3v::conjuncion_logica(val,a);
	return (*this);
}
const bool_l3v & bool_l3v::operator|=(bool a) {
	val = l3v::disyuncion_logica(val,a);
	return (*this);
}
const bool_l3v & bool_l3v::operator^=(bool a)  {
	val = l3v::o_exclusiva_logica(val,a);
	return (*this);
}

const bool_l3v F3v		=	bool_l3v(l3v::g_F());
const bool_l3v f3v		=	F3v;
const bool_l3v T3v		=	bool_l3v(l3v::g_T());
const bool_l3v t3v		=	T3v;
const bool_l3v DC3v		=	bool_l3v(l3v::g_x());
const bool_l3v x3v		=	DC3v;
const bool_l3v X3v		=	DC3v;
const bool_l3v dc3v		=	DC3v;

ostream & operator<< (ostream &,const bool_l3v &);
const istream & operator>> (istream &,bool_l3v &);

#endif // L3V_T_HPP
