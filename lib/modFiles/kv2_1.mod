: HH-style Kv2.1 channel model w/ inactivation KCNB1 
:Rejuvenation model of dopamine neuron (Chan et al. 2007)
: Fits by DP Mohapatra and Josh Held
: 1/7/2005 update! - Adjusted vhn and vcn - Josh Held

: updated by Mohamed Hisham 2020

NEURON {
	SUFFIX kv2_hh
	NONSPECIFIC_CURRENT ik
	RANGE g, ninf, tn, hinf, th, gbar ,ek
	GLOBAL vhn, vcn, vhh, vch, p , exp2
	GLOBAL Ctn, vhtn, atn, btn, tn0
	GLOBAL Cth, vhth, ath, bth, th0
}

UNITS {
	(S) = (siemens)
	(mV) = (millivolt)
	(mA) = (milliamp)
}

PARAMETER {
	gbar	= 1	(S/cm2)
	ek		= -80 (mV)
	exp2	= 2	(1)

	:vhn	= 18	(mV)
	vhn	= 17.5	(mV)
	:vcn	= -18	(mV)
	vcn	= -10	(mV)

	vhh	= -25	(mV)
	vch	= -12	(mV)
	p	= .26	

	:Ctn	= 80	(ms)
	:vhtn	= -10	(mV)
	:atn	= 14	(mV)
	:btn	= 20	(mV)
	:tn0	= 5	(ms)

	Ctn	= 5	(ms)
	vhtn	= -30	(mV)
	atn	= 14	(mV)
	btn	= 20	(mV)
	tn0	= 5	(ms)

	
	Cth	= 500	(ms)
	vhth	= 50	(mV)
	ath	= 20	(mV)
	bth	= 20	(mV)
	th0	= 800	(ms)

	Cq10 	= 4
	celsius		(degC)
}

ASSIGNED {
	g       (S/cm2)
	v	(mV)
	ninf
	hinf
	tn	(ms)
	th	(ms)
	ik	(mA/cm2)
	
}

STATE {
	n
	h
}

BREAKPOINT {
	SOLVE states METHOD cnexp
	g = gbar*h*n^exp2
	ik = g*(v-ek)
}

DERIVATIVE states{
	values()
	n' = (ninf - n)/tn
	h' = (hinf - h)/th
}

INITIAL {
	values()
	n = ninf
	h = hinf
}

PROCEDURE values() {LOCAL q10
	:q10 = Cq10^((celsius-23 (degC))/10 (degC)) : original
	q10 = Cq10^((celsius-36 (degC))/10 (degC))	: updated
	ninf = 1/(1 + exp((v - vhn)/vcn))
	hinf = (1-p)/(1 + exp(-(v - vhh)/vch)) + p
	tn = q10*Ctn/(exp((v-vhtn)/atn) + exp(-(v-vhtn)/btn)) + tn0
	th = q10*Cth/(exp((v-vhth)/ath) + exp(-(v-vhth)/bth)) + th0
}





