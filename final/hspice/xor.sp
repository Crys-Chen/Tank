**********************************
* xor_fakeNMOS test netlist
**********************************
.option post=2 
.lib sm046005-1j.hspice typical
.param Wp=2um Wn=1um dd=3.3V cf=0.1PF Ln=0.35um Lp=0.35um
.global VDD GND

.subckt cmos_inv IN Y_inv
MN   Y_inv   IN    GND   GND   NMOS_3P3   W=Wn  L=0.35um
MP   Y_inv   IN    VDD   VDD   PMOS_3P3   W=Wp  L=0.35um
.ENDS



.subckt XOR2 IN1 IN2 Y

X1   IN1   IN1_inv cmos_inv
X2   IN2   IN2_inv cmos_inv


    Mp1 VDD   IN1        a   VDD   PMOS_3P3  L=Lp W=`4*Wp`
    Mp2 VDD   IN2        a   VDD   PMOS_3P3  L=Lp W=`4*Wp`
    Mp3 a     IN1_inv    Y   VDD   PMOS_3P3  L=Lp W=`4*Wp`
    Mp4 a     IN2_inv    Y   VDD   PMOS_3P3  L=Lp W=`4*Wp`

    Mn1 Y     IN1        b   GND   NMOS_3P3  L=Ln W=`2*Wn`
    Mn2 Y     IN1_inv    c   GND   NMOS_3P3  L=Ln W=`2*Wn`
    Mn3 b     IN2        GND GND   NMOS_3P3  L=Ln W=`2*Wn`
    Mn4 c     IN2_inv    GND GND   NMOS_3P3  L=Ln W=`2*Wn`
.ends


X1  A B Y XOR2

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