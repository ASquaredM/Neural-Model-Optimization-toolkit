: Customized Current Clamp - Triangular Wave
: Compatibale with variable time step methods
: AMPstart: the start current
: AMPmax: the max current
: AMPend: the end current
: durA: duration of the first phase
: durB: duration of the second phase
: del: the delay


NEURON {
    POINT_PROCESS TriangleIClamp
    RANGE del, durA, durB, AMPmax, i, AMPstart, AMPend
    ELECTRODE_CURRENT i
}

UNITS { (nA) = (nanoamp)}

PARAMETER {
    del  (ms)    
    durA (ms) < 0, 1e9 >
    durB (ms) < 0, 1e9 >
    AMPstart (nA)
    AMPmax   (nA)
    AMPend   (nA) 
}

ASSIGNED { i (nA) }

INITIAL { i=0 }

BREAKPOINT {
    at_time(del)    
    at_time(del+durA)  
    at_time(del+durA+durB)  

    if (t < del) {
            i = 0
        } else if (  (t < (del+durA)) && (t > del)  ) {
            i= ((AMPmax-AMPstart)/durA)*t - (AMPmax/durA)*del + AMPstart*(del + durA)/durA
        } else if (  (t< (del+durA+durB)) && (t > (del+durA)) && (t > del)  ) {
            i= ((AMPend-AMPmax)/durB)*t + (AMPmax/durB)*(del+durA+durB) - AMPend*(del+durA)/durB
        }
}
