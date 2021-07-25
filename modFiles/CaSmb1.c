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
 
#define nrn_init _nrn_init__CaSmb1
#define _nrn_initial _nrn_initial__CaSmb1
#define nrn_cur _nrn_cur__CaSmb1
#define _nrn_current _nrn_current__CaSmb1
#define nrn_jacob _nrn_jacob__CaSmb1
#define nrn_state _nrn_state__CaSmb1
#define _net_receive _net_receive__CaSmb1 
#define evaluate_fct evaluate_fct__CaSmb1 
#define states states__CaSmb1 
 
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
#define gcanbar _p[0]
#define gcalbar _p[1]
#define gkcabar _p[2]
#define eca _p[3]
#define ican _p[4]
#define ical _p[5]
#define ikca _p[6]
#define gkca _p[7]
#define gcan _p[8]
#define gcal _p[9]
#define mn_inf _p[10]
#define hn_inf _p[11]
#define ml_inf _p[12]
#define tau_mn _p[13]
#define tau_hn _p[14]
#define tau_ml _p[15]
#define mn _p[16]
#define hn _p[17]
#define ml _p[18]
#define cai _p[19]
#define Dmn _p[20]
#define Dhn _p[21]
#define Dml _p[22]
#define Dcai _p[23]
#define tadj _p[24]
#define v _p[25]
#define _g _p[26]
 
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
 static void _hoc_evaluate_fct(void);
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
 "setdata_CaSmb1", _hoc_setdata,
 "evaluate_fct_CaSmb1", _hoc_evaluate_fct,
 0, 0
};
 /* declare global and static user variables */
#define alpha alpha_CaSmb1
 double alpha = 1;
#define caio caio_CaSmb1
 double caio = 0.0001;
#define cao cao_CaSmb1
 double cao = 2;
#define ek ek_CaSmb1
 double ek = -80;
#define f f_CaSmb1
 double f = 0.01;
#define kca kca_CaSmb1
 double kca = 4;
#define kd kd_CaSmb1
 double kd = 0.0002;
#define kml kml_CaSmb1
 double kml = -3.7;
#define mlexp mlexp_CaSmb1
 double mlexp = 1;
#define nexp nexp_CaSmb1
 double nexp = 2;
#define thetaml thetaml_CaSmb1
 double thetaml = 45.8;
#define tml tml_CaSmb1
 double tml = 400;
#define thetahn thetahn_CaSmb1
 double thetahn = 40;
#define thn thn_CaSmb1
 double thn = 50;
#define thetamn thetamn_CaSmb1
 double thetamn = 22;
#define tmn tmn_CaSmb1
 double tmn = 15;
#define vtraub vtraub_CaSmb1
 double vtraub = -10;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "tmn_CaSmb1", "ms",
 "thetamn_CaSmb1", "mV",
 "thn_CaSmb1", "ms",
 "thetahn_CaSmb1", "mV",
 "tml_CaSmb1", "ms",
 "thetaml_CaSmb1", "mV",
 "kml_CaSmb1", "mV",
 "cao_CaSmb1", "mM",
 "caio_CaSmb1", "mM",
 "vtraub_CaSmb1", "mV",
 "ek_CaSmb1", "mV",
 "gcanbar_CaSmb1", "mho/cm2",
 "gcalbar_CaSmb1", "mho/cm2",
 "gkcabar_CaSmb1", "mho/cm2",
 "eca_CaSmb1", "mV",
 "ican_CaSmb1", "mA/cm2",
 "ical_CaSmb1", "mA/cm2",
 "ikca_CaSmb1", "mA/cm2",
 "gkca_CaSmb1", "mho/cm2",
 "gcan_CaSmb1", "mho/cm2",
 "gcal_CaSmb1", "mho/cm2",
 "tau_mn_CaSmb1", "ms",
 "tau_hn_CaSmb1", "ms",
 "tau_ml_CaSmb1", "ms",
 0,0
};
 static double cai0 = 0;
 static double delta_t = 0.01;
 static double hn0 = 0;
 static double ml0 = 0;
 static double mn0 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "tmn_CaSmb1", &tmn_CaSmb1,
 "thetamn_CaSmb1", &thetamn_CaSmb1,
 "thn_CaSmb1", &thn_CaSmb1,
 "thetahn_CaSmb1", &thetahn_CaSmb1,
 "mlexp_CaSmb1", &mlexp_CaSmb1,
 "tml_CaSmb1", &tml_CaSmb1,
 "thetaml_CaSmb1", &thetaml_CaSmb1,
 "kml_CaSmb1", &kml_CaSmb1,
 "nexp_CaSmb1", &nexp_CaSmb1,
 "kd_CaSmb1", &kd_CaSmb1,
 "cao_CaSmb1", &cao_CaSmb1,
 "caio_CaSmb1", &caio_CaSmb1,
 "f_CaSmb1", &f_CaSmb1,
 "alpha_CaSmb1", &alpha_CaSmb1,
 "kca_CaSmb1", &kca_CaSmb1,
 "vtraub_CaSmb1", &vtraub_CaSmb1,
 "ek_CaSmb1", &ek_CaSmb1,
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
"CaSmb1",
 "gcanbar_CaSmb1",
 "gcalbar_CaSmb1",
 "gkcabar_CaSmb1",
 0,
 "eca_CaSmb1",
 "ican_CaSmb1",
 "ical_CaSmb1",
 "ikca_CaSmb1",
 "gkca_CaSmb1",
 "gcan_CaSmb1",
 "gcal_CaSmb1",
 "mn_inf_CaSmb1",
 "hn_inf_CaSmb1",
 "ml_inf_CaSmb1",
 "tau_mn_CaSmb1",
 "tau_hn_CaSmb1",
 "tau_ml_CaSmb1",
 0,
 "mn_CaSmb1",
 "hn_CaSmb1",
 "ml_CaSmb1",
 "cai_CaSmb1",
 0,
 0};
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 27, _prop);
 	/*initialize range parameters*/
 	gcanbar = 0.072837;
 	gcalbar = 0.0002;
 	gkcabar = 0.37418;
 	_prop->param = _p;
 	_prop->param_size = 27;
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

 void _CaSmb1_reg() {
	int _vectorized = 1;
  _initlists();
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 27, 1);
  hoc_register_dparam_semantics(_mechtype, 0, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 CaSmb1 D:/GP/Graduation-Project/gradProject/SpikOpt/modFiles/CaSmb1.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double FARADAY = 96485.3;
 static double R = 8.3145;
static int _reset;
static char *modelname = "Motoneuron Soma channels";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int evaluate_fct(_threadargsprotocomma_ double);
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[4], _dlist1[4];
 static int states(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {int _reset = 0; {
   evaluate_fct ( _threadargscomma_ v ) ;
   Dmn = ( mn_inf - mn ) / tau_mn ;
   Dhn = ( hn_inf - hn ) / tau_hn ;
   Dml = ( ml_inf - ml ) / tau_ml ;
   Dcai = f * ( - ( alpha * ( ican + ical ) ) - ( kca * cai ) ) ;
   }
 return _reset;
}
 static int _ode_matsol1 (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
 evaluate_fct ( _threadargscomma_ v ) ;
 Dmn = Dmn  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau_mn )) ;
 Dhn = Dhn  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau_hn )) ;
 Dml = Dml  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau_ml )) ;
 Dcai = Dcai  / (1. - dt*( ( f )*( ( ( - ( ( kca )*( 1.0 ) ) ) ) ) )) ;
  return 0;
}
 /*END CVODE*/
 static int states (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) { {
   evaluate_fct ( _threadargscomma_ v ) ;
    mn = mn + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_mn)))*(- ( ( ( mn_inf ) ) / tau_mn ) / ( ( ( ( - 1.0 ) ) ) / tau_mn ) - mn) ;
    hn = hn + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_hn)))*(- ( ( ( hn_inf ) ) / tau_hn ) / ( ( ( ( - 1.0 ) ) ) / tau_hn ) - hn) ;
    ml = ml + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_ml)))*(- ( ( ( ml_inf ) ) / tau_ml ) / ( ( ( ( - 1.0 ) ) ) / tau_ml ) - ml) ;
    cai = cai + (1. - exp(dt*(( f )*( ( ( - ( ( kca )*( 1.0 ) ) ) ) ))))*(- ( ( f )*( ( - ( ( alpha )*( ( ican + ical ) ) ) ) ) ) / ( ( f )*( ( ( - ( ( kca )*( 1.0 ) ) ) ) ) ) - cai) ;
   }
  return 0;
}
 
static int  evaluate_fct ( _threadargsprotocomma_ double _lv ) {
   double _lv2 ;
 _lv2 = _lv - vtraub ;
   tau_mn = tmn * tadj ;
   mn_inf = 1.0 / ( 1.0 + exp ( ( _lv2 + thetamn ) / - 5.0 ) ) ;
   tau_hn = thn * tadj ;
   hn_inf = 1.0 / ( 1.0 + exp ( ( _lv2 + thetahn ) / 5.0 ) ) ;
   tau_ml = tml * tadj ;
   ml_inf = 1.0 / ( 1.0 + exp ( ( _lv2 + thetaml ) / kml ) ) ;
    return 0; }
 
static void _hoc_evaluate_fct(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r = 1.;
 evaluate_fct ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
static int _ode_count(int _type){ return 4;}
 
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
	for (_i=0; _i < 4; ++_i) {
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
  cai = cai0;
  hn = hn0;
  ml = ml0;
  mn = mn0;
 {
   tadj = pow( 3.0 , ( ( celsius - 36.0 ) / 10.0 ) ) ;
   cai = caio ;
   evaluate_fct ( _threadargscomma_ v ) ;
   mn = mn_inf ;
   hn = hn_inf ;
   ml = ml_inf ;
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
   eca = ( ( 1000.0 * R * ( celsius + 273.15 ) ) / ( 2.0 * FARADAY ) ) * log ( cao / cai ) ;
   gcan = gcanbar * mn * mn * hn ;
   ican = gcan * ( v - eca ) ;
   gcal = gcalbar * ( pow( ml , mlexp ) ) ;
   ical = gcal * ( v - eca ) ;
   gkca = gkcabar * ( ( pow( cai , nexp ) ) / ( ( pow( cai , nexp ) ) + kd ) ) ;
   ikca = gkca * ( v - ek ) ;
   }
 _current += ikca;
 _current += ican;
 _current += ical;

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
 _slist1[0] = &(mn) - _p;  _dlist1[0] = &(Dmn) - _p;
 _slist1[1] = &(hn) - _p;  _dlist1[1] = &(Dhn) - _p;
 _slist1[2] = &(ml) - _p;  _dlist1[2] = &(Dml) - _p;
 _slist1[3] = &(cai) - _p;  _dlist1[3] = &(Dcai) - _p;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "CaSmb1.mod";
static const char* nmodl_file_text = 
  "TITLE Motoneuron Soma channels\n"
  ": Calcium channels + Calcium Dynamics - Soma\n"
  "\n"
  "\n"
  "NEURON {\n"
  "	SUFFIX CaSmb1\n"
  "\n"
  "\n"
  "	NONSPECIFIC_CURRENT ikca\n"
  "	NONSPECIFIC_CURRENT ican\n"
  "	NONSPECIFIC_CURRENT ical\n"
  "\n"
  "	RANGE gkcabar, gcanbar, gcalbar, eca\n"
  "	RANGE gkca, gcan, gcal\n"
  "	RANGE mn_inf, hn_inf, ml_inf\n"
  "	RANGE tau_mn, tau_hn, tau_ml\n"
  "}\n"
  "\n"
  "\n"
  "UNITS {\n"
  "	(mA) = (milliamp)\n"
  "	(mV) = (millivolt)\n"
  "	(molar) = (1/liter)\n"
  "	(mM) = (millimolar)\n"
  "\n"
  "	FARADAY	= (faraday) (coulomb)\n"
  "	R	= (k-mole) (joule/degC)\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "\n"
  "	: Calcium N-type channels\n"
  "	gcanbar = 0.072837  (mho/cm2)	\n"
  "	tmn	= 15	    (ms)\n"
  "	thetamn	= 22	    (mV)\n"
  "	thn	= 50	    (ms)\n"
  "	thetahn	= 40	    (mV)\n"
  "\n"
  "	: Calcium L-type Channels\n"
  "	gcalbar = 0.0002    (mho/cm2)	\n"
  "	mlexp	= 1\n"
  "	tml	= 400	    (ms)\n"
  "	thetaml = 45.8	    (mV)\n"
  "	kml	= -3.7	    (mV)\n"
  "\n"
  "	: Calcium-activated Potassium Channels\n"
  "	gkcabar = 0.37418   (mho/cm2)	                    \n"
  "	nexp	= 2\n"
  "	kd	= 0.0002\n"
  "\n"
  "	: Calcium Dynamics\n"
  "	cao	= 2	    (mM)\n"
  "	caio	= .0001     (mM)\n"
  "	f	= 0.01\n"
  "	alpha	= 1\n"
  "	kca	= 4\n"
  "\n"
  "	: General\n"
  "	vtraub	= -10	    (mV)\n"
  "	celsius = 36        (degC)\n"
  "	ek= -80             (mV)\n"
  "}\n"
  "\n"
  "STATE {\n"
  "	mn hn ml cai\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "	dt      (ms)\n"
  "	v       (mV)\n"
  "	eca	(mV)\n"
  "	\n"
  "	ican	(mA/cm2)\n"
  "	ical	(mA/cm2)\n"
  "	ikca	(mA/cm2)\n"
  "\n"
  "	gkca	(mho/cm2)\n"
  "	gcan	(mho/cm2)\n"
  "	gcal	(mho/cm2)\n"
  "	\n"
  "	mn_inf\n"
  "	hn_inf\n"
  "	ml_inf\n"
  "	\n"
  "	tau_mn	(ms)\n"
  "	tau_hn	(ms)\n"
  "	tau_ml	(ms)\n"
  "\n"
  "	tadj\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "	SOLVE states METHOD cnexp\n"
  "\n"
  "	eca = ((1000 * R * (celsius + 273.15)) / (2 * FARADAY)) * log(cao/cai)\n"
  "\n"
  "	gcan = gcanbar * mn*mn*hn\n"
  "	ican = gcan * (v - eca)\n"
  "\n"
  "	gcal = gcalbar * (ml^mlexp)\n"
  "	ical = gcal * (v - eca)\n"
  "\n"
  "	gkca = gkcabar * ( (cai^nexp) / ((cai^nexp)+kd) )\n"
  "	ikca = gkca * (v - ek)\n"
  "}\n"
  "\n"
  "DERIVATIVE states {   : exact Hodgkin-Huxley equations\n"
  "\n"
  "        evaluate_fct(v)\n"
  "\n"
  "	mn' = (mn_inf - mn) / tau_mn\n"
  "	hn' = (hn_inf - hn) / tau_hn\n"
  "	ml' = (ml_inf - ml) / tau_ml\n"
  "\n"
  "	cai' = f*(-(alpha*(ican+ical))-(kca*cai))\n"
  "}\n"
  "\n"
  "UNITSOFF\n"
  "INITIAL {\n"
  "\n"
  "	:  Q10 was assumed to be 3\n"
  "	tadj = 3.0 ^ ((celsius-36)/ 10 )\n"
  "\n"
  "	cai = caio\n"
  "\n"
  "	evaluate_fct(v)\n"
  "\n"
  "	mn = mn_inf\n"
  "	hn = hn_inf\n"
  "	ml = ml_inf\n"
  "}\n"
  "\n"
  "PROCEDURE evaluate_fct(v(mV)) { LOCAL v2\n"
  "\n"
  "	v2 = v - vtraub : convert to traub convention\n"
  "	\n"
  "	tau_mn = tmn * tadj\n"
  "	mn_inf = 1 / (1+exp((v2+thetamn)/-5))\n"
  "	\n"
  "	tau_hn = thn * tadj\n"
  "	hn_inf = 1 / (1+exp((v2+thetahn)/5))\n"
  "	\n"
  "	tau_ml = tml * tadj\n"
  "	ml_inf = 1 / (1+exp((v2+thetaml)/kml))\n"
  "}\n"
  "\n"
  ;
#endif
