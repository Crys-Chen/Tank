**********************************
* xor_fakeNMOS test netlist
**********************************
.option post=2 
.lib sm046005-1j.hspice typical
.param Wp=2um Wn=1um dd=3.3V cf=0.1PF NL=0.35um PL=0.35um
.global VDD GND

.subckt cmos_inv IN Y_inv
MN   Y_inv   IN    GND   GND   NMOS_3P3   W=Wn  L=0.35um
MP   Y_inv   IN    VDD   VDD   PMOS_3P3   W=Wp  L=0.35um
.ENDS



.subckt OR2 IN1 IN2 Y_inv

MN1   Y_inv   IN2    GND   GND   NMOS_3P3   W=Wn   L=0.35um
MN2   Y_inv   IN1    GND   GND   NMOS_3P3   W=Wn   L=0.35um
MP1   a       IN1    VDD   VDD   PMOS_3P3   W=`2*Wp`   L=0.35um
MP2   Y_inv   IN2    a     a     PMOS_3P3   W=`2*Wp`   L=0.35um 

.ends


X1 A B Y OR2
VDD  VDD    GND   dd
VGND GND    0     0

VIN1    A   GND   PWL(0ns 0V 19.9ns 0V 20.0ns dd 39.9ns dd 40ns 0V r) 
VIN2    B   GND   PWL(0ns 0V 9.9ns 0V 10.0ns dd 29.9ns dd 30ns 0V 40ns 0V r)

.MEASURE TRAN vomax MAX V(Y) FROM 10n TO 20n
.MEASURE TRAN vomin MIN V(Y) FROM 20n TO 30n
.MEASURE TRAN tPHL TRIG V(A) VAL=0.5*dd RISE=1 TARG V(Y) VAL='0.5*(vomax+vomin)' FALL=1
.MEASURE TRAN tPLH TRIG V(B) VAL=0.5*dd FALL=1 TARG V(Y) VAL='0.5*(vomax+vomin)' RISE=2
.MEASURE tran tr TRIG V(Y)='0.1*(vomax-vomin)+vomin' RISE=1 TARG V(Y)='0.9*(vomax-vomin)+vomin' RISE=1
.MEASURE tran tf TRIG V(Y)='0.9*(vomax-vomin)+vomin' FALL=1 TARG V(Y)='0.1*(vomax-vomin)+vomin' FALL=1
.MEASURE tran avgPower AVG P(VDD) FROM=20ns TO=60ns

.tran  0.01ns   100nS 
.probe V(Y) p(VDD) 
**********************************
.END