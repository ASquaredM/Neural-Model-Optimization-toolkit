TITLE rampclmp.mod
COMMENT
Modified from svclmp.mod, the source for SEClamp,
the standard 3 level single electrode voltage clamp.

dur1 is an interval during which the clamp's command potential vc 
remains constant at amp1.

Starting at t=dur1, vc begins to ramp toward amp2, 
which it reaches at t=dur1+dur2.

At t=dur1+dur2, vc ramps toward amp3, 
which it reaches at t=dur2+dur3.

Unlike SEClamp, RClamp is always on.
Another difference from SEClamp is the fact that dur2 and dur3 
are constrained to be >= 1e-9.

i is the injected current.

When this is used with constant dt, a very small time step 
must be used in order to obtain the correct injected current.

Do not insert several instances of this model at the same location in order to
make level changes. That is equivalent to independent clamps and they will
have incompatible internal state values.

The electrical circuit for the clamp is exceedingly simple:
vc ---'\/\/`--- cell
        rs

Note that since this is an electrode current model v refers to the
internal potential which is equivalent to the membrane potential v when
there is no extracellular membrane mechanism present but is v+vext when
one is present.
Also since i is an electrode current,
positive values of i depolarize the cell. (Normally, positive membrane currents
are outward and thus hyperpolarize the cell)
ENDCOMMENT

NEURON {
	POINT_PROCESS RampIClamp
	ELECTRODE_CURRENT i
	RANGE dur1, amp1, dur2, amp2, dur3, amp3, rs, i
}

UNITS {
	(nA) = (nanoamp)
	(mV) = (millivolt)
	(uS) = (microsiemens)
}


PARAMETER {
	rs = 1 (megohm) <1e-9, 1e9>
	dur1 (ms) 	  amp1 (mV)
	dur2 (ms) <0,1e9> amp2 (mV)
	dur3 (ms) <0,1e9> amp3 (mV)
}

ASSIGNED {
	v (mV)	: automatically v + vext when extracellular is present
	i (nA)
	tc2 (ms)
	tc3 (ms)
	k (mV/ms)
}

STATE { vc (mV) }

INITIAL {
	if (dur2<=0) {
		dur2=1e-9
	}
	if (dur3<=0) {
		dur3=1e-9
	}
	tc2 = dur1 + dur2
	tc3 = tc2 + dur3
	vc = amp1
}

BREAKPOINT {
	SOLVE rmp METHOD cnexp
	i = (vc - v)/rs
}

DERIVATIVE rmp {
	vstim()
	vc' = k
}

PROCEDURE vstim() {
	if (dur1) {at_time(dur1)}
	if (dur2) {at_time(tc2)}
	if (dur3) {at_time(tc3)}
	if (t < dur1) {
		k = 0
	}else if (t < tc2) {
		k = (amp2-amp1)/dur2
	}else if (t < tc3) {
		k = (amp3-amp2)/dur3
	}else {
		k = 0
	}
}
