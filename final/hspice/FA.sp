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

* NMOS: D G S SUB 
* PMOS: D G S SUB

* .subckt AND2 A B Y_inv
* N1   a       B    GND   GND   NMOS_3P3   W=Wn   L=NL
* N2   Y_inv   A    a     a     NMOS_3P3   W=Wn   L=NL
* P1   Y_inv   A    VDD   VDD   PMOS_3P3   W=Wp   L=PL
* P2   Y_inv   B    VDD   VDD   PMOS_3P3   W=Wp   L=PL   
* .ends

* .subckt AND2 IN1 IN2 Y
* MN1   a       IN2    GND   GND   NMOS_3P3   W=2*Wn   L=0.35um
* MN2   Y_inv   IN1    a     a     NMOS_3P3   W=2*Wn   L=0.35um
* MP1   Y_inv   IN1    VDD   VDD   PMOS_3P3   W=Wp   L=0.35um
* MP2   Y_inv   IN2    VDD   VDD   PMOS_3P3   W=Wp   L=0.35um 

* MN3   Y       Y_inv  GND   GND   NMOS_3P3   W=Wn   L=0.35um
* MP3   Y       Y_inv  VDD   VDD   PMOS_3P3   W=Wp   L=0.35um
* .ends

.subckt adder A B Ci Co S
    MN1   1   A    GND   GND    NMOS_3P3   W=6*Wn  L=0.35um
    MN2   1   B    GND   GND    NMOS_3P3   W=6*Wn  L=0.35um
    MN3   Co_inv   Ci   1   1   NMOS_3P3   W=6*Wn  L=0.35um      

    MN4   2   B    GND   GND    NMOS_3P3   W=2*Wn  L=0.35um
    MN5   Co_inv   A    2   2   NMOS_3P3   W=2*Wn  L=0.35um

    MP1   3   A    VDD   VDD    PMOS_3P3   W=12*Wp  L=0.35um
    MP2   3   B    VDD   VDD    PMOS_3P3   W=12*Wp  L=0.35um
    MP3   Co_inv   Ci   3   3   PMOS_3P3   W=12*Wp  L=0.35um      

    MP4   4   B    VDD   VDD    PMOS_3P3   W=4*Wp  L=0.35um
    MP5   Co_inv   A    4   4   PMOS_3P3   W=4*Wp  L=0.35um


    MN6   5   A    GND   GND    NMOS_3P3   W=2*Wn  L=0.35um
    MN7   5   B    GND   GND    NMOS_3P3   W=2*Wn  L=0.35um
    MN8   5   Ci    GND   GND    NMOS_3P3   W=2*Wn  L=0.35um
    MN9   S_inv   Co_inv    5   5    NMOS_3P3   W=2*Wn  L=0.35um

    MP6   6   A    VDD   VDD    PMOS_3P3   W=4*Wp  L=0.35um
    MP7   6   B    VDD   VDD    PMOS_3P3   W=4*Wp  L=0.35um
    MP8   6   Ci    VDD   VDD    PMOS_3P3   W=4*Wp  L=0.35um
    MP9   S_inv   Co_inv    6   6    PMOS_3P3   W=4*Wp  L=0.35um

    MN10   7   B    GND   GND    NMOS_3P3   W=3*Wn  L=0.35um
    MN11   8   A    7   7    NMOS_3P3   W=3*Wn  L=0.35um
    MN12   S_inv   Ci    8   8    NMOS_3P3   W=3*Wn  L=0.35um

    MP10   9   A    VDD   VDD    PMOS_3P3   W=6*Wp  L=0.35um
    MP11   10   B    9   9    PMOS_3P3   W=6*Wp  L=0.35um
    MP12   S_inv   Ci    10   10    PMOS_3P3   W=6*Wp  L=0.35um

    X1  Co_inv  Co  cmos_inv
    X2  S_inv  S  cmos_inv


.ends

.subckt adder2 A B Ci Co S
    MN1   1   A    GND   GND    NMOS_3P3   W=Wn  L=0.35um
    MN2   1   B    GND   GND    NMOS_3P3   W=Wn  L=0.35um
    MN3   Co_inv   Ci   1   1   NMOS_3P3   W=Wn  L=0.35um      

    MN4   2   B    GND   GND    NMOS_3P3   W=Wn  L=0.35um
    MN5   Co_inv   A    2   2   NMOS_3P3   W=Wn  L=0.35um

    MP1   3   A    VDD   VDD    PMOS_3P3   W=Wp  L=0.35um
    MP2   3   B    VDD   VDD    PMOS_3P3   W=Wp  L=0.35um
    MP3   Co_inv   Ci   3   3   PMOS_3P3   W=Wp  L=0.35um      

    MP4   4   B    VDD   VDD    PMOS_3P3   W=Wp  L=0.35um
    MP5   Co_inv   A    4   4   PMOS_3P3   W=Wp  L=0.35um


    MN6   5   A    GND   GND    NMOS_3P3   W=Wn  L=0.35um
    MN7   5   B    GND   GND    NMOS_3P3   W=Wn  L=0.35um
    MN8   5   Ci    GND   GND    NMOS_3P3   W=Wn  L=0.35um
    MN9   S_inv   Co_inv    5   5    NMOS_3P3   W=Wn  L=0.35um

    MP6   6   A    VDD   VDD    PMOS_3P3   W=Wp  L=0.35um
    MP7   6   B    VDD   VDD    PMOS_3P3   W=Wp  L=0.35um
    MP8   6   Ci    VDD   VDD    PMOS_3P3   W=Wp  L=0.35um
    MP9   S_inv   Co_inv    6   6    PMOS_3P3   W=Wp  L=0.35um

    MN10   7   B    GND   GND    NMOS_3P3   W=Wn  L=0.35um
    MN11   8   A    7   7    NMOS_3P3   W=Wn  L=0.35um
    MN12   S_inv   Ci    8   8    NMOS_3P3   W=Wn  L=0.35um

    MP10   9   A    VDD   VDD    PMOS_3P3   W=Wp  L=0.35um
    MP11   10   B    9   9    PMOS_3P3   W=Wp  L=0.35um
    MP12   S_inv   Ci    10   10    PMOS_3P3   W=Wp  L=0.35um

    X1  Co_inv  Co  cmos_inv
    X2  S_inv  S  cmos_inv


.ends


X1 A0 B0 Ci Co Y adder
X2 A0 B0 Ci Co1 Y1 adder2
* X2 Y_inv Y cmos_inv

* X1 A A1 VDD GND cmos_inv
* X2 B B1 VDD GND cmos_inv
* MN1   A1  B1    Y   GND   NMOS_3P3   W=1um L=0.35um
* MP1   A1  B     Y   VDD   PMOS_3P3   W=Wp  L=0.35um
* MN2   A   B     Y   GND   NMOS_3P3   W=1um L=0.35um
* MP2   A   B1    Y   VDD   PMOS_3P3   W=Wp  L=0.35um

* X3 Y  Y_inv VDD GND cmos_inv

* CL   Y_inv    GND   cf
VDD  VDD    GND   dd
VGND GND    0     0
.param start=20.0ns delta=0.01ns end=40.0ns start2=30.0ns end2=50.0ns start3=35.0ns end3=55.0ns

VA0    A0   GND   PWL(0ns 0V `start-delta` 0V start dd `end-delta` dd end 0V) 
VB0    B0   GND   PWL(0ns 0V `start2-delta` 0V start2 dd `end2-delta` dd end2 0V) 
VC0    Ci   GND   PWL(0ns 0V `start3-delta` 0V start3 dd `end3-delta` dd end3 0V)


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