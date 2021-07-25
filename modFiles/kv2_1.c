/* Created by Language version: 7.7.0 */
/* VECTORIZED */
#define NRN_VECTORIZED 1
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "scoplib_ansi.h"
#undef PI
#define nil 0
#include "md1redef.h"
#include "section.h"
#include "nrniv_mf.h"
#include "md2redef.h"
 
#if METHOD3
extern int _method3;
#endif

#if !NRNGPU
#undef exp
#define exp hoc_Exp
extern double hoc_Exp(double);
#endif
 
#define nrn_init _nrn_init__kv2_hh
#define _nrn_initial _nrn_initial__kv2_hh
#define nrn_cur _nrn_cur__kv2_hh
#define _nrn_current _nrn_current__kv2_hh
#define nrn_jacob _nrn_jacob__kv2_hh
#define nrn_state _nrn_state__kv2_hh
#define _net_receive _net_receive__kv2_hh 
#define states states__kv2_hh 
#define values values__kv2_hh 
 
#define _threadargscomma_ _p, _ppvar, _thread, _nt,
#define _threadargsprotocomma_ double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt,
#define _threadargs_ _p, _ppvar, _thread, _nt
#define _threadargsproto_ double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 /* Thread safe. No static _p or _ppvar. */
 
#define t _nt->_t
#define dt _nt->_dt
#define gbar _p[0]
#define ek _p[1]
#define g _p[2]
#define ninf _p[3]
#define hinf _p[4]
#define tn _p[5]
#define th _p[6]
#define ik _p[7]
#define n _p[8]
#define h _p[9]
#define Dn _p[10]
#define Dh _p[11]
#define v _p[12]
#define _g _p[13]
 
#if MAC
#if !defined(v)
#define v _mlhv
#endif
#if !defined(h)
#define h _mlhh
#endif
#endif
 
#if defined(__cplusplus)
extern "C" {
#endif
 static int hoc_nrnpointerindex =  -1;
 static Datum* _extcall_thread;
 static Prop* _extcall_prop;
 /* external NEURON variables */
 extern double celsius;
 /* declaration of user functions */
 static void _hoc_values(void);
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_prop_size(int, int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
extern Memb_func* memb_func;
 
#define NMODL_TEXT 1
#if NMODL_TEXT
static const char* nmodl_file_text;
static const char* nmodl_filename;
extern void hoc_reg_nmodl_text(int, const char*);
extern void hoc_reg_nmodl_filename(int, const char*);
#endif

 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _extcall_prop = _prop;
 }
 static void _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range(int);
 _prop = hoc_getdata_range(_mechtype);
   _setdata(_prop);
 hoc_retpushx(1.);
}
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 "setdata_kv2_hh", _hoc_setdata,
 "values_kv2_hh", _hoc_values,
 0, 0
};
 /* declare global and static user variables */
#define Cq10 Cq10_kv2_hh
 double Cq10 = 4;
#define Cth Cth_kv2_hh
 double Cth = 500;
#define Ctn Ctn_kv2_hh
 double Ctn = 5;
#define ath ath_kv2_hh
 double ath = 20;
#define atn atn_kv2_hh
 double atn = 14;
#define bth bth_kv2_hh
 double bth = 20;
#define btn btn_kv2_hh
 double btn = 20;
#define exp2 exp2_kv2_hh
 double exp2 = 2;
#define p p_kv2_hh
 double p = 0.26;
#define th0 th0_kv2_hh
 double th0 = 800;
#define tn0 tn0_kv2_hh
 double tn0 = 5;
#define vhth vhth_kv2_hh
 double vhth = 50;
#define vhtn vhtn_kv2_hh
 double vhtn = -30;
#define vch vch_kv2_hh
 double vch = -12;
#define vhh vhh_kv2_hh
 double vhh = -25;
#define vcn vcn_kv2_hh
 double vcn = -10;
#define vhn vhn_kv2_hh
 double vhn = 17.5;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "exp2_kv2_hh", "1",
 "vhn_kv2_hh", "mV",
 "vcn_kv2_hh", "mV",
 "vhh_kv2_hh", "mV",
 "vch_kv2_hh", "mV",
 "Ctn_kv2_hh", "ms",
 "vhtn_kv2_hh", "mV",
 "atn_kv2_hh", "mV",
 "btn_kv2_hh", "mV",
 "tn0_kv2_hh", "ms",
 "Cth_kv2_hh", "ms",
 "vhth_kv2_hh", "mV",
 "ath_kv2_hh", "mV",
 "bth_kv2_hh", "mV",
 "th0_kv2_hh", "ms",
 "gbar_kv2_hh", "S/cm2",
 "ek_kv2_hh", "mV",
 "g_kv2_hh", "S/cm2",
 "tn_kv2_hh", "ms",
 "th_kv2_hh", "ms",
 "ik_kv2_hh", "mA/cm2",
 0,0
};
 static double delta_t = 0.01;
 static double h0 = 0;
 static double n0 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "exp2_kv2_hh", &exp2_kv2_hh,
 "vhn_kv2_hh", &vhn_kv2_hh,
 "vcn_kv2_hh", &vcn_kv2_hh,
 "vhh_kv2_hh", &vhh_kv2_hh,
 "vch_kv2_hh", &vch_kv2_hh,
 "p_kv2_hh", &p_kv2_hh,
 "Ctn_kv2_hh", &Ctn_kv2_hh,
 "vhtn_kv2_hh", &vhtn_kv2_hh,
 "atn_kv2_hh", &atn_kv2_hh,
 "btn_kv2_hh", &btn_kv2_hh,
 "tn0_kv2_hh", &tn0_kv2_hh,
 "Cth_kv2_hh", &Cth_kv2_hh,
 "vhth_kv2_hh", &vhth_kv2_hh,
 "ath_kv2_hh", &ath_kv2_hh,
 "bth_kv2_hh", &bth_kv2_hh,
 "th0_kv2_hh", &th0_kv2_hh,
 "Cq10_kv2_hh", &Cq10_kv2_hh,
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(Prop*);
static void  nrn_init(_NrnThread*, _Memb_list*, int);
static void nrn_state(_NrnThread*, _Memb_list*, int);
 static void nrn_cur(_NrnThread*, _Memb_list*, int);
static void  nrn_jacob(_NrnThread*, _Memb_list*, int);
 
static int _ode_count(int);
static void _ode_map(int, double**, double**, double*, Datum*, double*, int);
static void _ode_spec(_NrnThread*, _Memb_list*, int);
static void _ode_matsol(_NrnThread*, _Memb_list*, int);
 
#define _cvode_ieq _ppvar[0]._i
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"kv2_hh",
 "gbar_kv2_hh",
 "ek_kv2_hh",
 0,
 "g_kv2_hh",
 "ninf_kv2_hh",
 "hinf_kv2_hh",
 "tn_kv2_hh",
 "th_kv2_hh",
 "ik_kv2_hh",
 0,
 "n_kv2_hh",
 "h_kv2_hh",
 0,
 0};
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 14, _prop);
 	/*initialize range parameters*/
 	gbar = 1;
 	ek = -80;
 	_prop->param = _p;
 	_prop->param_size = 14;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 1, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _kv2_1_reg() {
	int _vectorized = 1;
  _initlists();
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 14, 1);
  hoc_register_dparam_semantics(_mechtype, 0, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 kv2_hh D:/GP/Graduation-Project/gradProject/SpikOpt/modFiles/kv2_1.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int values(_threadargsproto_);
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[2], _dlist1[2];
 static int states(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {int _reset = 0; {
   values ( _threadargs_ ) ;
   Dn = ( ninf - n ) / tn ;
   Dh = ( hinf - h ) / th ;
   }
 return _reset;
}
 static int _ode_matsol1 (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
 values ( _threadargs_ ) ;
 Dn = Dn  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tn )) ;
 Dh = Dh  / (1. - dt*( ( ( ( - 1.0 ) ) ) / th )) ;
  return 0;
}
 /*END CVODE*/
 static int states (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) { {
   values ( _threadargs_ ) ;
    n = n + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tn)))*(- ( ( ( ninf ) ) / tn ) / ( ( ( ( - 1.0 ) ) ) / tn ) - n) ;
    h = h + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / th)))*(- ( ( ( hinf ) ) / th ) / ( ( ( ( - 1.0 ) ) ) / th ) - h) ;
   }
  return 0;
}
 
static int  values ( _threadargsproto_ ) {
   double _lq10 ;
 _lq10 = pow( Cq10 , ( ( celsius - 36.0 ) / 10.0 ) ) ;
   ninf = 1.0 / ( 1.0 + exp ( ( v - vhn ) / vcn ) ) ;
   hinf = ( 1.0 - p ) / ( 1.0 + exp ( - ( v - vhh ) / vch ) ) + p ;
   tn = _lq10 * Ctn / ( exp ( ( v - vhtn ) / atn ) + exp ( - ( v - vhtn ) / btn ) ) + tn0 ;
   th = _lq10 * Cth / ( exp ( ( v - vhth ) / ath ) + exp ( - ( v - vhth ) / bth ) ) + th0 ;
    return 0; }
 
static void _hoc_values(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r = 1.;
 values ( _p, _ppvar, _thread, _nt );
 hoc_retpushx(_r);
}
 
static int _ode_count(int _type){ return 2;}
 
static void _ode_spec(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
     _ode_spec1 (_p, _ppvar, _thread, _nt);
 }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
	double* _p; Datum* _ppvar;
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 2; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static void _ode_matsol_instance1(_threadargsproto_) {
 _ode_matsol1 (_p, _ppvar, _thread, _nt);
 }
 
static void _ode_matsol(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
 _ode_matsol_instance1(_threadargs_);
 }}

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
  int _i; double _save;{
  h = h0;
  n = n0;
 {
   values ( _threadargs_ ) ;
   n = ninf ;
   h = hinf ;
   }
 
}
}

static void nrn_init(_NrnThread* _nt, _Memb_list* _ml, int _type){
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v = _v;
 initmodel(_p, _ppvar, _thread, _nt);
}
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt, double _v){double _current=0.;v=_v;{ {
   g = gbar * h * pow( n , exp2 ) ;
   ik = g * ( v - ek ) ;
   }
 _current += ik;

} return _current;
}

static void nrn_cur(_NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 _g = _nrn_current(_p, _ppvar, _thread, _nt, _v + .001);
 	{ _rhs = _nrn_current(_p, _ppvar, _thread, _nt, _v);
 	}
 _g = (_g - _rhs)/.001;
#if CACHEVEC
  if (use_cachevec) {
	VEC_RHS(_ni[_iml]) -= _rhs;
  }else
#endif
  {
	NODERHS(_nd) -= _rhs;
  }
 
}
 
}

static void nrn_jacob(_NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml];
#if CACHEVEC
  if (use_cachevec) {
	VEC_D(_ni[_iml]) += _g;
  }else
#endif
  {
     _nd = _ml->_nodelist[_iml];
	NODED(_nd) += _g;
  }
 
}
 
}

static void nrn_state(_NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v = 0.0; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _nd = _ml->_nodelist[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v=_v;
{
 {   states(_p, _ppvar, _thread, _nt);
  }}}

}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(n) - _p;  _dlist1[0] = &(Dn) - _p;
 _slist1[1] = &(h) - _p;  _dlist1[1] = &(Dh) - _p;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "kv2_1.mod";
static const char* nmodl_file_text = 
  ": HH-style Kv2.1 channel model w/ inactivation KCNB1 \n"
  ":Rejuvenation model of dopamine neuron (Chan et al. 2007)\n"
  ": Fits by DP Mohapatra and Josh Held\n"
  ": 1/7/2005 update! - Adjusted vhn and vcn - Josh Held\n"
  "\n"
  ": updated by Mohamed Hisham 2020\n"
  "\n"
  "NEURON {\n"
  "	SUFFIX kv2_hh\n"
  "	NONSPECIFIC_CURRENT ik\n"
  "	RANGE g, ninf, tn, hinf, th, gbar ,ek\n"
  "	GLOBAL vhn, vcn, vhh, vch, p , exp2\n"
  "	GLOBAL Ctn, vhtn, atn, btn, tn0\n"
  "	GLOBAL Cth, vhth, ath, bth, th0\n"
  "}\n"
  "\n"
  "UNITS {\n"
  "	(S) = (siemens)\n"
  "	(mV) = (millivolt)\n"
  "	(mA) = (milliamp)\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "	gbar	= 1	(S/cm2)\n"
  "	ek		= -80 (mV)\n"
  "	exp2	= 2	(1)\n"
  "\n"
  "	:vhn	= 18	(mV)\n"
  "	vhn	= 17.5	(mV)\n"
  "	:vcn	= -18	(mV)\n"
  "	vcn	= -10	(mV)\n"
  "\n"
  "	vhh	= -25	(mV)\n"
  "	vch	= -12	(mV)\n"
  "	p	= .26	\n"
  "\n"
  "	:Ctn	= 80	(ms)\n"
  "	:vhtn	= -10	(mV)\n"
  "	:atn	= 14	(mV)\n"
  "	:btn	= 20	(mV)\n"
  "	:tn0	= 5	(ms)\n"
  "\n"
  "	Ctn	= 5	(ms)\n"
  "	vhtn	= -30	(mV)\n"
  "	atn	= 14	(mV)\n"
  "	btn	= 20	(mV)\n"
  "	tn0	= 5	(ms)\n"
  "\n"
  "	\n"
  "	Cth	= 500	(ms)\n"
  "	vhth	= 50	(mV)\n"
  "	ath	= 20	(mV)\n"
  "	bth	= 20	(mV)\n"
  "	th0	= 800	(ms)\n"
  "\n"
  "	Cq10 	= 4\n"
  "	celsius		(degC)\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "	g       (S/cm2)\n"
  "	v	(mV)\n"
  "	ninf\n"
  "	hinf\n"
  "	tn	(ms)\n"
  "	th	(ms)\n"
  "	ik	(mA/cm2)\n"
  "	\n"
  "}\n"
  "\n"
  "STATE {\n"
  "	n\n"
  "	h\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "	SOLVE states METHOD cnexp\n"
  "	g = gbar*h*n^exp2\n"
  "	ik = g*(v-ek)\n"
  "}\n"
  "\n"
  "DERIVATIVE states{\n"
  "	values()\n"
  "	n' = (ninf - n)/tn\n"
  "	h' = (hinf - h)/th\n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "	values()\n"
  "	n = ninf\n"
  "	h = hinf\n"
  "}\n"
  "\n"
  "PROCEDURE values() {LOCAL q10\n"
  "	:q10 = Cq10^((celsius-23 (degC))/10 (degC)) : original\n"
  "	q10 = Cq10^((celsius-36 (degC))/10 (degC))	: updated\n"
  "	ninf = 1/(1 + exp((v - vhn)/vcn))\n"
  "	hinf = (1-p)/(1 + exp(-(v - vhh)/vch)) + p\n"
  "	tn = q10*Ctn/(exp((v-vhtn)/atn) + exp(-(v-vhtn)/btn)) + tn0\n"
  "	th = q10*Cth/(exp((v-vhth)/ath) + exp(-(v-vhth)/bth)) + th0\n"
  "}\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "\n"
  ;
#endif
