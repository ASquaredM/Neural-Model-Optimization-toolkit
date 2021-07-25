/* Created by Language version: 7.7.0 */
/* NOT VECTORIZED */
#define NRN_VECTORIZED 0
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
 
#define nrn_init _nrn_init__CaDen
#define _nrn_initial _nrn_initial__CaDen
#define nrn_cur _nrn_cur__CaDen
#define _nrn_current _nrn_current__CaDen
#define nrn_jacob _nrn_jacob__CaDen
#define nrn_state _nrn_state__CaDen
#define _net_receive _net_receive__CaDen 
#define RandGenerator RandGenerator__CaDen 
#define _f_rates _f_rates__CaDen 
#define rates rates__CaDen 
#define states states__CaDen 
#define tauCorrection tauCorrection__CaDen 
 
#define _threadargscomma_ /**/
#define _threadargsprotocomma_ /**/
#define _threadargs_ /**/
#define _threadargsproto_ /**/
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 static double *_p; static Datum *_ppvar;
 
#define t nrn_threads->_t
#define dt nrn_threads->_dt
#define gcabar _p[0]
#define eca _p[1]
#define W_tau_d _p[2]
#define tailon _p[3]
#define AmpRandG _p[4]
#define Warm_Gear _p[5]
#define Warm_thresh _p[6]
#define gkcabar _p[7]
#define O_inf _p[8]
#define tRandG _p[9]
#define ical _p[10]
#define ikca _p[11]
#define gkca _p[12]
#define O _p[13]
#define W _p[14]
#define S _p[15]
#define cai _p[16]
#define DO _p[17]
#define DW _p[18]
#define DS _p[19]
#define Dcai _p[20]
#define S_inf _p[21]
#define W_inf _p[22]
#define W_tau _p[23]
#define W_tau2 _p[24]
#define df _p[25]
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
 /* external NEURON variables */
 extern double celsius;
 /* declaration of user functions */
 static void _hoc_RandGenerator(void);
 static void _hoc_d_Flag(void);
 static void _hoc_rates(void);
 static void _hoc_tauFunc(void);
 static void _hoc_tauCorrection(void);
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
 _p = _prop->param; _ppvar = _prop->dparam;
 }
 static void _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range(int);
 _prop = hoc_getdata_range(_mechtype);
   _setdata(_prop);
 hoc_retpushx(1.);
}
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 "setdata_CaDen", _hoc_setdata,
 "RandGenerator_CaDen", _hoc_RandGenerator,
 "d_Flag_CaDen", _hoc_d_Flag,
 "rates_CaDen", _hoc_rates,
 "tauFunc_CaDen", _hoc_tauFunc,
 "tauCorrection_CaDen", _hoc_tauCorrection,
 0, 0
};
#define d_Flag d_Flag_CaDen
#define tauFunc tauFunc_CaDen
 extern double d_Flag( double );
 extern double tauFunc( double , double );
 /* declare global and static user variables */
#define O_tau2 O_tau2_CaDen
 double O_tau2 = 50;
#define O_tau O_tau_CaDen
 double O_tau = 20;
#define S_tau S_tau_CaDen
 double S_tau = 40;
#define alpha alpha_CaDen
 double alpha = 1;
#define caio caio_CaDen
 double caio = 0.0001;
#define ek ek_CaDen
 double ek = -80;
#define f f_CaDen
 double f = 0.01;
#define kca kca_CaDen
 double kca = 8;
#define kd kd_CaDen
 double kd = 0.0005;
#define kappa_m kappa_m_CaDen
 double kappa_m = -6;
#define nexp nexp_CaDen
 double nexp = 10;
#define theta_m theta_m_CaDen
 double theta_m = -30;
#define usetable usetable_CaDen
 double usetable = 1;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "usetable_CaDen", 0, 1,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "theta_m_CaDen", "mV",
 "kappa_m_CaDen", "mV",
 "O_tau_CaDen", "ms",
 "O_tau2_CaDen", "ms",
 "nexp_CaDen", "1",
 "kd_CaDen", "mM",
 "S_tau_CaDen", "ms",
 "caio_CaDen", "mM",
 "alpha_CaDen", "cm2",
 "kca_CaDen", "1/ms",
 "ek_CaDen", "mV",
 "gcabar_CaDen", "mho/cm2",
 "eca_CaDen", "mV",
 "W_tau_d_CaDen", "ms",
 "gkcabar_CaDen", "mho/cm2",
 "cai_CaDen", "mM",
 "ical_CaDen", "mA/cm2",
 "ikca_CaDen", "mA/cm2",
 0,0
};
 static double O0 = 0;
 static double S0 = 0;
 static double W0 = 0;
 static double cai0 = 0;
 static double delta_t = 0.01;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "theta_m_CaDen", &theta_m_CaDen,
 "kappa_m_CaDen", &kappa_m_CaDen,
 "O_tau_CaDen", &O_tau_CaDen,
 "O_tau2_CaDen", &O_tau2_CaDen,
 "nexp_CaDen", &nexp_CaDen,
 "kd_CaDen", &kd_CaDen,
 "S_tau_CaDen", &S_tau_CaDen,
 "caio_CaDen", &caio_CaDen,
 "f_CaDen", &f_CaDen,
 "alpha_CaDen", &alpha_CaDen,
 "kca_CaDen", &kca_CaDen,
 "ek_CaDen", &ek_CaDen,
 "usetable_CaDen", &usetable_CaDen,
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void _ba1() ;
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
"CaDen",
 "gcabar_CaDen",
 "eca_CaDen",
 "W_tau_d_CaDen",
 "tailon_CaDen",
 "AmpRandG_CaDen",
 "Warm_Gear_CaDen",
 "Warm_thresh_CaDen",
 "gkcabar_CaDen",
 0,
 "O_inf_CaDen",
 "tRandG_CaDen",
 "ical_CaDen",
 "ikca_CaDen",
 "gkca_CaDen",
 0,
 "O_CaDen",
 "W_CaDen",
 "S_CaDen",
 "cai_CaDen",
 0,
 0};
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 27, _prop);
 	/*initialize range parameters*/
 	gcabar = 0.0003;
 	eca = 60;
 	W_tau_d = 1200;
 	tailon = 1;
 	AmpRandG = 0.5;
 	Warm_Gear = 1;
 	Warm_thresh = 0.27;
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

 void _CaDen_reg() {
	int _vectorized = 0;
  _initlists();
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 0);
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
 	hoc_reg_ba(_mechtype, _ba1, 11);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 CaDen D:/GP/Graduation-Project/gradProject/SpikOpt/modFiles/CaDen.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double FARADAY = 96485.3;
 static double R = 8.3145;
 static double *_t_O_inf;
 static double *_t_W_inf;
 static double *_t_W_tau;
static int _reset;
static char *modelname = "Motoneuron Dendrites channels";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int RandGenerator(double, double);
static int _f_rates(double);
static int rates(double);
static int tauCorrection(double);
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static void _n_rates(double);
 static int _slist1[4], _dlist1[4];
 static int states(_threadargsproto_);
 /* BEFORE BREAKPOINT */
 static void _ba1(Node*_nd, double* _pp, Datum* _ppd, Datum* _thread, _NrnThread* _nt)  {
    _p = _pp; _ppvar = _ppd;
  v = NODEV(_nd);
 }
 
/*CVODE*/
 static int _ode_spec1 () {_reset=0;
 {
   rates ( _threadargscomma_ v ) ;
   S_inf = ( 1.0 / ( pow( ( kd / ( cai - 0.00001 ) ) , nexp ) + 1.0 ) ) ;
   df = d_Flag ( _threadargscomma_ O_inf - O ) ;
   tauCorrection ( _threadargscomma_ tRandG ) ;
   DO = ( O_inf - O ) * tauFunc ( _threadargscomma_ W , df ) / ( O_tau + O_tau2 * df ) ;
   DW = ( ( W_inf * ( 1.0 - df ) ) - W ) / ( W_tau + W_tau2 ) ;
   DS = ( S_inf - S ) / S_tau ;
   Dcai = f * ( - ( alpha * ( ical ) ) - ( kca * cai ) ) ;
   }
 return _reset;
}
 static int _ode_matsol1 () {
 rates ( _threadargscomma_ v ) ;
 S_inf = ( 1.0 / ( pow( ( kd / ( cai - 0.00001 ) ) , nexp ) + 1.0 ) ) ;
 df = d_Flag ( _threadargscomma_ O_inf - O ) ;
 tauCorrection ( _threadargscomma_ tRandG ) ;
 DO = DO  / (1. - dt*( ( ( ( ( - 1.0 ) ) )*( tauFunc ( _threadargscomma_ W , df ) ) ) / ( O_tau + O_tau2 * df ) )) ;
 DW = DW  / (1. - dt*( ( ( ( - 1.0 ) ) ) / ( W_tau + W_tau2 ) )) ;
 DS = DS  / (1. - dt*( ( ( ( - 1.0 ) ) ) / S_tau )) ;
 Dcai = Dcai  / (1. - dt*( ( f )*( ( ( - ( ( kca )*( 1.0 ) ) ) ) ) )) ;
  return 0;
}
 /*END CVODE*/
 static int states () {_reset=0;
 {
   rates ( _threadargscomma_ v ) ;
   S_inf = ( 1.0 / ( pow( ( kd / ( cai - 0.00001 ) ) , nexp ) + 1.0 ) ) ;
   df = d_Flag ( _threadargscomma_ O_inf - O ) ;
   tauCorrection ( _threadargscomma_ tRandG ) ;
    O = O + (1. - exp(dt*(( ( ( ( - 1.0 ) ) )*( tauFunc ( _threadargscomma_ W , df ) ) ) / ( O_tau + O_tau2 * df ))))*(- ( ( ( ( O_inf ) )*( tauFunc ( _threadargscomma_ W , df ) ) ) / ( O_tau + O_tau2 * df ) ) / ( ( ( ( ( - 1.0 ) ) )*( tauFunc ( _threadargscomma_ W , df ) ) ) / ( O_tau + O_tau2 * df ) ) - O) ;
    W = W + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / ( W_tau + W_tau2 ))))*(- ( ( ( ( ( W_inf )*( ( 1.0 - df ) ) ) ) ) / ( W_tau + W_tau2 ) ) / ( ( ( ( - 1.0 ) ) ) / ( W_tau + W_tau2 ) ) - W) ;
    S = S + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / S_tau)))*(- ( ( ( S_inf ) ) / S_tau ) / ( ( ( ( - 1.0 ) ) ) / S_tau ) - S) ;
    cai = cai + (1. - exp(dt*(( f )*( ( ( - ( ( kca )*( 1.0 ) ) ) ) ))))*(- ( ( f )*( ( - ( ( alpha )*( ( ical ) ) ) ) ) ) / ( ( f )*( ( ( - ( ( kca )*( 1.0 ) ) ) ) ) ) - cai) ;
   }
  return 0;
}
 static double _mfac_rates, _tmin_rates;
 static void _check_rates();
 static void _check_rates() {
  static int _maktable=1; int _i, _j, _ix = 0;
  double _xi, _tmax;
  if (!usetable) {return;}
  if (_maktable) { double _x, _dx; _maktable=0;
   _tmin_rates =  - 200.0 ;
   _tmax =  100.0 ;
   _dx = (_tmax - _tmin_rates)/300.; _mfac_rates = 1./_dx;
   for (_i=0, _x=_tmin_rates; _i < 301; _x += _dx, _i++) {
    _f_rates(_x);
    _t_O_inf[_i] = O_inf;
    _t_W_inf[_i] = W_inf;
    _t_W_tau[_i] = W_tau;
   }
  }
 }

 static int rates(double _lv){ _check_rates();
 _n_rates(_lv);
 return 0;
 }

 static void _n_rates(double _lv){ int _i, _j;
 double _xi, _theta;
 if (!usetable) {
 _f_rates(_lv); return; 
}
 _xi = _mfac_rates * (_lv - _tmin_rates);
 if (isnan(_xi)) {
  O_inf = _xi;
  W_inf = _xi;
  W_tau = _xi;
  return;
 }
 if (_xi <= 0.) {
 O_inf = _t_O_inf[0];
 W_inf = _t_W_inf[0];
 W_tau = _t_W_tau[0];
 return; }
 if (_xi >= 300.) {
 O_inf = _t_O_inf[300];
 W_inf = _t_W_inf[300];
 W_tau = _t_W_tau[300];
 return; }
 _i = (int) _xi;
 _theta = _xi - (double)_i;
 O_inf = _t_O_inf[_i] + _theta*(_t_O_inf[_i+1] - _t_O_inf[_i]);
 W_inf = _t_W_inf[_i] + _theta*(_t_W_inf[_i+1] - _t_W_inf[_i]);
 W_tau = _t_W_tau[_i] + _theta*(_t_W_tau[_i+1] - _t_W_tau[_i]);
 }

 
static int  _f_rates (  double _lv ) {
   O_inf = 1.0 / ( 1.0 + exp ( ( _lv - theta_m ) / kappa_m ) ) ;
   W_inf = 1.0 / ( 1.0 + exp ( - ( _lv + 57.0 ) / 0.8 ) ) ;
   W_tau = 50.0 + ( 1150.0 / Warm_Gear ) / ( 1.0 + exp ( ( _lv + 32.0 ) / 7.0 ) ) ;
    return 0; }
 
static void _hoc_rates(void) {
  double _r;
    _r = 1.;
 rates (  *getarg(1) );
 hoc_retpushx(_r);
}
 
double tauFunc (  double _lW , double _ldf ) {
   double _ltauFunc;
 double _lW_thresh , _lobservable_W ;
 _lW_thresh = Warm_thresh ;
   _lobservable_W = tailon * _lW * _ldf ;
   _ltauFunc = 0.001 + 0.999 / ( 1.0 + exp ( ( _lobservable_W - _lW_thresh ) / 0.006 ) ) ;
   
return _ltauFunc;
 }
 
static void _hoc_tauFunc(void) {
  double _r;
   _r =  tauFunc (  *getarg(1) , *getarg(2) );
 hoc_retpushx(_r);
}
 
static int  RandGenerator (  double _lO , double _lO_inf ) {
   if ( _lO < 0.03  && _lO_inf > 0.025 ) {
     tRandG = scop_random ( ) ;
     AmpRandG = scop_random ( ) ;
     }
    return 0; }
 
static void _hoc_RandGenerator(void) {
  double _r;
   _r = 1.;
 RandGenerator (  *getarg(1) , *getarg(2) );
 hoc_retpushx(_r);
}
 
static int  tauCorrection (  double _ltRandG ) {
   double _ltauCompansate ;
 _ltauCompansate = ( W_tau_d * ( 1.0 - ( 0.76 * _ltRandG ) ) ) - W_tau ;
   W_tau2 = _ltauCompansate * df ;
    return 0; }
 
static void _hoc_tauCorrection(void) {
  double _r;
   _r = 1.;
 tauCorrection (  *getarg(1) );
 hoc_retpushx(_r);
}
 
double d_Flag (  double _lXf ) {
   double _ld_Flag;
 _ld_Flag = 1.0 / ( exp ( ( floor ( _lXf ) + 1.0 ) / 0.065 ) ) ;
   
return _ld_Flag;
 }
 
static void _hoc_d_Flag(void) {
  double _r;
   _r =  d_Flag (  *getarg(1) );
 hoc_retpushx(_r);
}
 
static int _ode_count(int _type){ return 4;}
 
static void _ode_spec(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
     _ode_spec1 ();
 }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 4; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static void _ode_matsol_instance1(_threadargsproto_) {
 _ode_matsol1 ();
 }
 
static void _ode_matsol(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
 _ode_matsol_instance1(_threadargs_);
 }}

static void initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
  O = O0;
  S = S0;
  W = W0;
  cai = cai0;
 {
   rates ( _threadargscomma_ v ) ;
   O = O_inf ;
   W = W_inf ;
   cai = caio ;
   S = 0.0 ;
   }
  _sav_indep = t; t = _save;

}
}

static void nrn_init(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
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
 initmodel();
}}

static double _nrn_current(double _v){double _current=0.;v=_v;{ {
   ical = gcabar * ( ( O ) * ( AmpRandG * 0.3 + 1.0 ) ) * ( v - eca ) ;
   gkca = S ;
   ikca = gkcabar * gkca * ( v - ek ) ;
   }
 _current += ikca;
 _current += ical;

} return _current;
}

static void nrn_cur(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
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
 _g = _nrn_current(_v + .001);
 	{ _rhs = _nrn_current(_v);
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
 
}}

static void nrn_jacob(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
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
 
}}

static void nrn_state(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; double _v = 0.0; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
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
 { error =  states();
 if(error){fprintf(stderr,"at line 110 in file CaDen.mod:\n	SOLVE states METHOD cnexp\n"); nrn_complain(_p); abort_run(error);}
 }}}

}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(O) - _p;  _dlist1[0] = &(DO) - _p;
 _slist1[1] = &(W) - _p;  _dlist1[1] = &(DW) - _p;
 _slist1[2] = &(S) - _p;  _dlist1[2] = &(DS) - _p;
 _slist1[3] = &(cai) - _p;  _dlist1[3] = &(Dcai) - _p;
   _t_O_inf = makevector(301*sizeof(double));
   _t_W_inf = makevector(301*sizeof(double));
   _t_W_tau = makevector(301*sizeof(double));
_first = 0;
}

#if NMODL_TEXT
static const char* nmodl_filename = "CaDen.mod";
static const char* nmodl_file_text = 
  "TITLE Motoneuron Dendrites channels\n"
  ": Calcium channels (L-type with warm up) + Calcium Dynamics (sK channels) - Dendrites\n"
  ": V3 >> variable tail current Parameter was added ( W_tau_d ) which controls the discharging speed for the W state.\n"
  ": V4 >> the \"tailon\" variable was added to enable to deactivation of the tail current feature.\n"
  ": V5 >> \"deactivation_Flag\" = \"df\", is introduced to sync all the pocesses of deactivation ( activate tail current , force deactivate 'w')\n"
  ": V6 >> W_tau voltage rates was modifed ,as well as many units corrections.\n"
  ": V8 >> new gating used to detect deactivation using the floor() function  ( V8 Light version clean)\n"
  ": V9 >> adding deativating time constant for the L-type channel for the O state.\n"
  ": V10>> tail activation function was returned to the old version for smooth deactivation , as d_Flag is too sharp , this update do not affect the results as all , it just give it nice shape at the initiation of deactivation after tail.\n"
  ": V11>> sk dynamics has been changed , adding time constant , and change kinetics to make less sensitivity to Calcium\n"
  ": V12>> random number Generation moved out of the BREAKPOINT block for calculations safety.\n"
  ": V13>> (optional) AmpRand is set as a parameter to compensate for closing the RNG\n"
  ": V14>>	Warm-up Gearup parameter, \n"
  ": >> Last Update June 20 , 2020\n"
  ": By Mohamed.H Mousa\n"
  "\n"
  "NEURON {\n"
  "	SUFFIX CaDen\n"
  "\n"
  "	NONSPECIFIC_CURRENT ikca\n"
  "	NONSPECIFIC_CURRENT ical\n"
  "\n"
  "	RANGE gkcabar, gcabar, eca , gkca : gkca is equivalent to O ( they both respresent the activated presentage for the L-type Ca channels and the sK respectively)\n"
  "	RANGE tRandG , AmpRandG, O_inf, Warm_Gear, Warm_thresh ,tailon ,W_tau_d\n"
  "}\n"
  "\n"
  "\n"
  "UNITS {\n"
  "	(mA)		= (milliamp)\n"
  "	(mV)		= (millivolt)\n"
  "	(molar)	= (1/liter)\n"
  "	(mM)		= (millimolar)\n"
  "\n"
  "	FARADAY	= (faraday) (coulomb)\n"
  "	R			= (k-mole) (joule/degC)\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "\n"
  "	: Calcium L-type Channels\n"
  "	gcabar		= 0.0003		(mho/cm2)\n"
  "	eca			= 60			(mV) : if eca was constant\n"
  "	theta_m		= -30     	(mV)\n"
  "	kappa_m		= -6	   	(mV)\n"
  "	O_tau  		= 20      	(ms)\n"
  "	O_tau2 		= 50			(ms)   : deactivating time const\n"
  "	W_tau_d    	= 1200		(ms)\n"
  "	tailon		= 1			: unitless , keep 1 to enable the tail current , and set to zero to disable tail current\n"
  "	AmpRandG	= 0.5		: Amplitude random Variable\n"
  "	Warm_Gear	= 1			: (unitless) to decrease the warm-up charging time constant\n"
  "	Warm_thresh	= 0.27\n"
  "\n"
  "\n"
  "	: Calcium-activated Potassium Channels\n"
  "	gkcabar		= 0.37418		(mho/cm2)\n"
  "	nexp		= 10				(1)       : 2\n"
  "	kd			= 0.0005			(mM)\n"
  "	S_tau		= 40				(ms)\n"
  "\n"
  "	: Calcium Dynamics\n"
  "	caio		= 0.0001			(mM)   : steady state cai concentration\n"
  "	f			= 0.01\n"
  "	alpha		= 1				(cm2 mM/mC)\n"
  "	kca	  		= 8				(1/ms)\n"
  "\n"
  "\n"
  "	: General\n"
  "	celsius 	= 36				(degC)\n"
  "	ek      	= -80				(mV)\n"
  "}\n"
  "\n"
  ": the state O is similar to \"ml\" in the old model , \"W\" is the tail current watch STATE\n"
  "STATE {\n"
  "	O W S cai (mM)\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "	dt      (ms)\n"
  "	v       (mV)\n"
  "\n"
  "	:kinetics variables for l-type Calcium channel\n"
  "	O_inf\n"
  "\n"
  "	: calcium activated Potassium channel sKl\n"
  "	S_inf 		(ms)\n"
  "\n"
  "	: tail current dynamics variables\n"
  "	W_inf\n"
  "	W_tau  		(ms)\n"
  "	W_tau2 		(ms)\n"
  "\n"
  "	:stochastic Range Variable for l-type Calcium channel\n"
  "	tRandG				: time random Variable\n"
  "	:AmpRandG			: Amplitude random Variable\n"
  "\n"
  "	: current variables\n"
  "	ical	(mA/cm2)\n"
  "	ikca	(mA/cm2)\n"
  "\n"
  "	gkca				: used as a gating variable for monitoring.\n"
  "	df 					: used as the deactivation Flag.\n"
  "}\n"
  "\n"
  "BEFORE BREAKPOINT {\n"
  "	: RandGenerator(O,O_inf) : uncomment to activate the local Random Generator\n"
  "	: or put in the solve (states function here) as the derivative block only triggered once.\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "	SOLVE states METHOD cnexp\n"
  "	ical = gcabar * ((O)*(AmpRandG*0.3 + 1)) * (v - eca)   : ohm's law for L-type Ca channel'\n"
  "\n"
  "	gkca = S\n"
  "	ikca = gkcabar *  gkca * (v - ek)					: ohm's law for sK channel'\n"
  "}\n"
  "\n"
  "DERIVATIVE states {   : exact Hodgkin-Huxley equations\n"
  "\n"
  "		rates(v)					: calculate the O_inf , W_inf voltage steady states.\n"
  "		S_inf 	= ( 1 / ((kd/(cai-0.00001))^nexp + 1) )\n"
  "		df 		= d_Flag(O_inf-O)	: calulate the deactivation Flag \"df\" checking for deactivation\n"
  "		tauCorrection(tRandG)		: Calculate W_Tau2 , to generate a constant tau for \"W\" state discharging\n"
  "\n"
  "		: the states ODEs\n"
  "		O'	=    (O_inf - O)*tauFunc(W,df) / (O_tau + O_tau2 * df) :\n"
  "		W'	=    ( (W_inf*(1-df)) - W)/ (W_tau + W_tau2 )   :'\n"
  "		S'	=	 (S_inf-S)/S_tau							:'\n"
  "		cai' = f*(-(alpha*(ical))-(kca*cai))  :  to calculate concentation inside\n"
  "}\n"
  "\n"
  "UNITSOFF\n"
  "\n"
  "INITIAL {\n"
  "		rates(v)\n"
  "		O   = O_inf\n"
  "		W   = W_inf\n"
  "		cai = caio\n"
  "		S   = 0\n"
  "}\n"
  "\n"
  "PROCEDURE rates(v(mV)) {\n"
  "		TABLE O_inf , W_inf , W_tau\n"
  "				FROM -200 TO 100 WITH 300\n"
  "\n"
  "		O_inf = 1/(1+ exp((v - theta_m)/kappa_m) )\n"
  "		W_inf = 1/(1+exp(-(v+57)/0.8))\n"
  "		W_tau = 50 + (1150/Warm_Gear)/(1+exp((v+32)/7))\n"
  "}\n"
  "\n"
  ": this function controls the effective W threshold , and detect the discharging case to activate the Sandwatch\n"
  ": if input is above thresh , then the output is Zero , if less it will be one to give no effect on O_tau\n"
  "FUNCTION tauFunc(W,df){ LOCAL W_thresh, observable_W\n"
  "		W_thresh			= Warm_thresh :0.27\n"
  "		observable_W	= tailon * W * df		: W*1 if discharging , w*0 if charging\n"
  "		:tauFunc			= d_Flag(observable_W - W_thresh) 			: tail current do not decay\n"
  "		:tauFunc			= 0.001 + 0.999*d_Flag(observable_W - W_thresh) 	: for unstraight steep tail current , leave leak\n"
  "		tauFunc			= 0.001 + 0.999/(1+ exp((observable_W - W_thresh)/0.006)) : for smooth transition , as the d_Flag function is too sharp.\n"
  "}\n"
  "\n"
  "PROCEDURE RandGenerator(O,O_inf){\n"
  "	if( O<0.03 && O_inf > 0.025){\n"
  "		tRandG   = scop_random() : uniform Random number Generator ( not thread safe )\n"
  "		AmpRandG = scop_random() :\n"
  "		:printf(\"RNG A = %f ,RNG T = %f\" ,AmpRandG,tRandG)\n"
  "	}\n"
  "}\n"
  "\n"
  ":Calculate W_Tau2 , to generate a constant tau(discharing constant) for \"W\" state discharging\n"
  "PROCEDURE tauCorrection(tRandG){ LOCAL tauCompansate\n"
  "	 	tauCompansate		= (W_tau_d * (1 -  (0.76 *tRandG)) ) - W_tau\n"
  "	 	W_tau2				= tauCompansate * df\n"
  "}\n"
  "\n"
  "FUNCTION d_Flag(Xf){\n"
  "		d_Flag	= 1/(exp((floor(Xf)+1)/0.065))\n"
  "}\n"
  "\n"
  "UNITSON\n"
  ;
#endif
