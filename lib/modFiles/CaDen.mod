TITLE Motoneuron Dendrites channels
: Calcium channels (L-type with warm up) + Calcium Dynamics (sK channels) - Dendrites
: V3 >> variable tail current Parameter was added ( W_tau_d ) which controls the discharging speed for the W state.
: V4 >> the "tailon" variable was added to enable to deactivation of the tail current feature.
: V5 >> "deactivation_Flag" = "df", is introduced to sync all the pocesses of deactivation ( activate tail current , force deactivate 'w')
: V6 >> W_tau voltage rates was modifed ,as well as many units corrections.
: V8 >> new gating used to detect deactivation using the floor() function  ( V8 Light version clean)
: V9 >> adding deativating time constant for the L-type channel for the O state.
: V10>> tail activation function was returned to the old version for smooth deactivation , as d_Flag is too sharp , this update do not affect the results as all , it just give it nice shape at the initiation of deactivation after tail.
: V11>> sk dynamics has been changed , adding time constant , and change kinetics to make less sensitivity to Calcium
: V12>> random number Generation moved out of the BREAKPOINT block for calculations safety.
: V13>> (optional) AmpRand is set as a parameter to compensate for closing the RNG
: V14>>	Warm-up Gearup parameter, 
: >> Last Update June 20 , 2020
: By Mohamed.H Mousa

NEURON {
	SUFFIX CaDen

	NONSPECIFIC_CURRENT ikca
	NONSPECIFIC_CURRENT ical

	RANGE gkcabar, gcabar, eca , gkca : gkca is equivalent to O ( they both respresent the activated presentage for the L-type Ca channels and the sK respectively)
	RANGE tRandG , AmpRandG, O_inf, Warm_Gear, Warm_thresh ,tailon ,W_tau_d
}


UNITS {
	(mA)		= (milliamp)
	(mV)		= (millivolt)
	(molar)	= (1/liter)
	(mM)		= (millimolar)

	FARADAY	= (faraday) (coulomb)
	R			= (k-mole) (joule/degC)
}

PARAMETER {

	: Calcium L-type Channels
	gcabar		= 0.0003		(mho/cm2)
	eca			= 60			(mV) : if eca was constant
	theta_m		= -30     	(mV)
	kappa_m		= -6	   	(mV)
	O_tau  		= 20      	(ms)
	O_tau2 		= 50			(ms)   : deactivating time const
	W_tau_d    	= 1200		(ms)
	tailon		= 1			: unitless , keep 1 to enable the tail current , and set to zero to disable tail current
	AmpRandG	= 0.5		: Amplitude random Variable
	Warm_Gear	= 1			: (unitless) to decrease the warm-up charging time constant
	Warm_thresh	= 0.27


	: Calcium-activated Potassium Channels
	gkcabar		= 0.37418		(mho/cm2)
	nexp		= 10				(1)       : 2
	kd			= 0.0005			(mM)
	S_tau		= 40				(ms)

	: Calcium Dynamics
	caio		= 0.0001			(mM)   : steady state cai concentration
	f			= 0.01
	alpha		= 1				(cm2 mM/mC)
	kca	  		= 8				(1/ms)


	: General
	celsius 	= 36				(degC)
	ek      	= -80				(mV)
}

: the state O is similar to "ml" in the old model , "W" is the tail current watch STATE
STATE {
	O W S cai (mM)
}

ASSIGNED {
	dt      (ms)
	v       (mV)

	:kinetics variables for l-type Calcium channel
	O_inf

	: calcium activated Potassium channel sKl
	S_inf 		(ms)

	: tail current dynamics variables
	W_inf
	W_tau  		(ms)
	W_tau2 		(ms)

	:stochastic Range Variable for l-type Calcium channel
	tRandG				: time random Variable
	:AmpRandG			: Amplitude random Variable

	: current variables
	ical	(mA/cm2)
	ikca	(mA/cm2)

	gkca				: used as a gating variable for monitoring.
	df 					: used as the deactivation Flag.
}

BEFORE BREAKPOINT {
	: RandGenerator(O,O_inf) : uncomment to activate the local Random Generator
	: or put in the solve (states function here) as the derivative block only triggered once.
}

BREAKPOINT {
	SOLVE states METHOD cnexp
	ical = gcabar * ((O)*(AmpRandG*0.3 + 1)) * (v - eca)   : ohm's law for L-type Ca channel'

	gkca = S
	ikca = gkcabar *  gkca * (v - ek)					: ohm's law for sK channel'
}

DERIVATIVE states {   : exact Hodgkin-Huxley equations

		rates(v)					: calculate the O_inf , W_inf voltage steady states.
		S_inf 	= ( 1 / ((kd/(cai-0.00001))^nexp + 1) )
		df 		= d_Flag(O_inf-O)	: calulate the deactivation Flag "df" checking for deactivation
		tauCorrection(tRandG)		: Calculate W_Tau2 , to generate a constant tau for "W" state discharging

		: the states ODEs
		O'	=    (O_inf - O)*tauFunc(W,df) / (O_tau + O_tau2 * df) :
		W'	=    ( (W_inf*(1-df)) - W)/ (W_tau + W_tau2 )   :'
		S'	=	 (S_inf-S)/S_tau							:'
		cai' = f*(-(alpha*(ical))-(kca*cai))  :  to calculate concentation inside
}

UNITSOFF

INITIAL {
		rates(v)
		O   = O_inf
		W   = W_inf
		cai = caio
		S   = 0
}

PROCEDURE rates(v(mV)) {
		TABLE O_inf , W_inf , W_tau
				FROM -200 TO 100 WITH 300

		O_inf = 1/(1+ exp((v - theta_m)/kappa_m) )
		W_inf = 1/(1+exp(-(v+57)/0.8))
		W_tau = 50 + (1150/Warm_Gear)/(1+exp((v+32)/7))
}

: this function controls the effective W threshold , and detect the discharging case to activate the Sandwatch
: if input is above thresh , then the output is Zero , if less it will be one to give no effect on O_tau
FUNCTION tauFunc(W,df){ LOCAL W_thresh, observable_W
		W_thresh			= Warm_thresh :0.27
		observable_W	= tailon * W * df		: W*1 if discharging , w*0 if charging
		:tauFunc			= d_Flag(observable_W - W_thresh) 			: tail current do not decay
		:tauFunc			= 0.001 + 0.999*d_Flag(observable_W - W_thresh) 	: for unstraight steep tail current , leave leak
		tauFunc			= 0.001 + 0.999/(1+ exp((observable_W - W_thresh)/0.006)) : for smooth transition , as the d_Flag function is too sharp.
}

PROCEDURE RandGenerator(O,O_inf){
	if( O<0.03 && O_inf > 0.025){
		tRandG   = scop_random() : uniform Random number Generator ( not thread safe )
		AmpRandG = scop_random() :
		:printf("RNG A = %f ,RNG T = %f" ,AmpRandG,tRandG)
	}
}

:Calculate W_Tau2 , to generate a constant tau(discharing constant) for "W" state discharging
PROCEDURE tauCorrection(tRandG){ LOCAL tauCompansate
	 	tauCompansate		= (W_tau_d * (1 -  (0.76 *tRandG)) ) - W_tau
	 	W_tau2				= tauCompansate * df
}

FUNCTION d_Flag(Xf){
		d_Flag	= 1/(exp((floor(Xf)+1)/0.065))
}

UNITSON
