
NEURON {
	SUFFIX hb1
	NONSPECIFIC_CURRENT ih

	RANGE ghbar, eh, gh
	RANGE mh_inf
}


UNITS {
	(mA) = (milliamp)
	(mV) = (millivolt)
}

PARAMETER {

	ghbar  = 0.01	(mho/cm2)
	eh = -44 		(mV)

	tau_mh = 100	(ms)
	theta_mh = -95	(mV)
	kappa_mh = 13.5	(mV)

	celsius = 23	(degC)
}

STATE {
	mh
}

ASSIGNED {
	dt      	(ms)
	v       	(mV)

	ih     	(mA/cm2)
	gh	  	(mho/cm2)

	mh_inf

	tadj
}

BREAKPOINT {
	SOLVE states METHOD cnexp

	gh = ghbar * mh
	ih = gh * (v - eh)

}

DERIVATIVE states {   : exact Hodgkin-Huxley equations

      evaluate_fct(v)
	mh' = (mh_inf - mh) / tau_mh
}

UNITSOFF
INITIAL {

	:  Q10 was assumed to be 3
	tadj = 3.0 ^ ((celsius-36)/ 10)

	evaluate_fct(v)

	mh = mh_inf
}

PROCEDURE evaluate_fct(v(mV)) {

	mh_inf = (1 / (1 + (Exp((v - theta_mh)/ kappa_mh) ) ) )/ tadj
}

FUNCTION Exp(x) {
	if (x < -100) {
		Exp = 0
	}else{
		Exp = exp(x)
	}
} 
