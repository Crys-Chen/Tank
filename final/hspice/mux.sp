**********************************
* xor_fakeNMOS test netlist
**********************************
.option post=2 
.lib sm046005-1j.hspice typical
.param Wp=2um Wn=1um dd=3.3V cf=0.1PF Ln=0.35um Lp=0.35um
.global VDD GND

.subckt INV IN Y_inv
MN   Y_inv   IN    GND   GND   NMOS_3P3   W=Wn  L=0.35um
MP   Y_inv   IN    VDD   VDD   PMOS_3P3   W=Wp  L=0.35um
.ENDS


.subckt Mux A B S Y

    X1  S   S_inv  INV

    MN1 A   S      1   1    NMOS_3P3    W=Wn    L=Ln
    MP1 A   S_inv  1   1    PMOS_3P3    W=Wp    L=Lp

    MN2 B   S_inv  1   1    NMOS_3P3    W=Wn    L=Ln
    MP2 B   S      1   1    PMOS_3P3    W=Wp    L=Lp

    X2  1   2      INV
    X3  2   Y      INV

.ends


X1 A0 B0 S0 Y Mux

VDD  VDD    GND   dd
VGND GND    0     0


.param start=20.0ns delta=0.01ns end=40.0ns

VA0    A0   GND   PWL(0ns 0V `start-delta` 0V start dd `end-delta` dd end 0V) 

VB0    B0   GND   PWL(0ns 0V `start-delta` 0V start 0.6V `end-delta` 0.6V end 0V) 

VS0    S0   GND   PWL(0ns 0V `start-delta` 0V start dd `end-delta` dd end 0V) 
.MEASURE TRAN vomax MAX V(Y_inv) FROM 10n TO 20n
.MEASURE TRAN vomin MIN V(Y_inv) FROM 20n TO 30n
.MEASURE TRAN tPHL TRIG V(A) VAL=0.5*dd RISE=1 TARG V(Y) VAL='0.5*(vomax+vomin)' FALL=1
.MEASURE TRAN tPLH TRIG V(B) VAL=0.5*dd FALL=1 TARG V(Y) VAL='0.5*(vomax+vomin)' RISE=2
.MEASURE tran tr TRIG V(Y)='0.1*(vomax-vomin)+vomin' RISE=1 TARG V(Y)='0.9*(vomax-vomin)+vomin' RISE=1
.MEASURE tran tf TRIG V(Y)='0.9*(vomax-vomin)+vomin' FALL=1 TARG V(Y)='0.1*(vomax-vomin)+vomin' FALL=1
.MEASURE tran avgPower AVG P(VDD) FROM=20ns TO=60ns

.tran  0.01ns   100nS 
.probe V(Y) p(VDD) 
**********************************
.END