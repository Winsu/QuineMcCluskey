#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

class l3v {
	friend class bool_l3v;
protected:
	enum l3v_t {F=(unsigned char)0,T=(unsigned char)1,x=(unsigned char)2};
private:
	inline static l3v_t conjuncion_logica(l3v_t a,l3v_t b) {
		if ((a==F)or(b==F)) return F;
		else if ((a==x)or(b==x)) return x;
		else return T;
	}
	inline static l3v_t disyuncion_logica (l3v_t a,l3v_t b) {
		if ((a==T)or(b==T)) return T;
		else if ((a==x)or(b==x)) return x;
		else return F;
	}
	inline static l3v_t o_exclusiva_logica(l3v_t a,l3v_t b) {
		if ((a==x)or(b==x)) return x;
		else if (a==b) return F;
		else return T;
	}
	inline static l3v_t negacion_logica(l3v_t a) {
		if (a==x) return x;
		else return ((a==T)?F:T);
	}
	inline static bool lt (l3v_t a,l3v_t b) {
		if ((a==F)and(b!=F)) return true;
		else if ((a==T)and(b==x)) return true;
		else return false;
	}
	inline static bool lt_eq (l3v_t a,l3v_t b) {
		if (a==F) return true;
		else if ((a==T)and(b!=F)) return true;
		else if ((a==x)and(b==x)) return true;
		else return false;
	}
	inline static bool gt (l3v_t a,l3v_t b) {
		if ((b==F)and(a!=F)) return true;
		else if ((b==T)and(a==x)) return true;
		else return false;
	}
	inline static bool gt_eq (l3v_t a,l3v_t b) {
		if (b==F) return true;
		else if ((b==T)and(a!=F)) return true;
		else if ((b==x)and(a==x)) return true;
		else return false;
	}
	inline static l3v_t disyuncion_logica(bool a,l3v_t b) {
		if ((b == x)and(!a)) return x;
		else return ((a or (b==T))?T:F);
	}
	inline static l3v_t conjuncion_logica(bool a,l3v_t b) {
		if ((b == x)and(a)) return x;
		else return ((a and (b==T))?T:F);
	}
	inline static l3v_t o_exclusiva_logica(bool a,l3v_t b) {
		if (b == x) return x;
		else return ((a xor (b==T))?T:F);
	}
	inline static l3v_t disyuncion_logica(l3v_t a,bool b) {
		if ((a == x)and(!b)) return x;
		else return (((a==T) or b)?T:F);
	}
	inline static l3v_t conjuncion_logica(l3v_t a,bool b) {
		if ((a == x)and(b)) return x;
		else return (((a==T) and b)?T:F);
	}
	inline static l3v_t o_exclusiva_logica(l3v_t a,bool b) {
		if (a == x) return x;
		else return (((a==T) xor b)?T:F);
	}
public:
	static inline const l3v_t g_F() {return F;}
	static inline const l3v_t g_T() {return T;}
	static inline const l3v_t g_x() {return x;}
};

#endif // DEFINITIONS_HPP
