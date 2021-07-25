#include <stdio.h>
#include "hocdec.h"
#define IMPORT extern __declspec(dllimport)
IMPORT int nrnmpi_myid, nrn_nobanner_;

extern void _CaDen_reg();
extern void _CaSmb1_reg();
extern void _hb1_reg();
extern void _info_reg();
extern void _KdrIsb1_reg();
extern void _KdrSmb1_reg();
extern void _kv2_1_reg();
extern void _Llvab1_reg();
extern void _NafIsb1_reg();
extern void _NafSmb1_reg();
extern void _NapIsb1_reg();
extern void _RampIClamp_reg();
extern void _TriangleIClamp_reg();

void modl_reg(){
	//nrn_mswindll_stdio(stdin, stdout, stderr);
    if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
	fprintf(stderr, "Additional mechanisms from files\n");

fprintf(stderr," CaDen.mod");
fprintf(stderr," CaSmb1.mod");
fprintf(stderr," hb1.mod");
fprintf(stderr," info.mod");
fprintf(stderr," KdrIsb1.mod");
fprintf(stderr," KdrSmb1.mod");
fprintf(stderr," kv2_1.mod");
fprintf(stderr," Llvab1.mod");
fprintf(stderr," NafIsb1.mod");
fprintf(stderr," NafSmb1.mod");
fprintf(stderr," NapIsb1.mod");
fprintf(stderr," RampIClamp.mod");
fprintf(stderr," TriangleIClamp.mod");
fprintf(stderr, "\n");
    }
_CaDen_reg();
_CaSmb1_reg();
_hb1_reg();
_info_reg();
_KdrIsb1_reg();
_KdrSmb1_reg();
_kv2_1_reg();
_Llvab1_reg();
_NafIsb1_reg();
_NafSmb1_reg();
_NapIsb1_reg();
_RampIClamp_reg();
_TriangleIClamp_reg();
}
