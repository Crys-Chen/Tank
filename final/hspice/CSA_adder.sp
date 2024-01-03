**********************************
* xor_fakeNMOS test netlist
**********************************
* Co0有问题
.option post=2 
.lib sm046005-1j.hspice typical
.param Wp=1um Wn=0.5um dd=3.3V cf=0.1PF Ln=0.35um Lp=0.35um
.global VDD GND

.subckt INV IN Y_inv
    MN   Y_inv   IN    GND   GND   NMOS_3P3   W=Wn  L=Ln
    MP   Y_inv   IN    VDD   VDD   PMOS_3P3   W=Wp  L=Lp
.ENDS

* NMOS: D G S SUB 
* PMOS: D G S SUB


.subckt FA_Co A B Ci Co

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

    X1  Co_inv  Co  INV

.ends



.subckt FA_S A B Ci Co_inv S
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

    X2  S_inv  S  INV

.ends

.subckt FA_Co4 C0 A0 A1 A2 A3 B0 B1 B2 B3 Co0 Co1 Co2 Co3
    X1  A0 B0 C0  Co0 FA_Co
    X2  A1 B1 Co0 Co1 FA_Co
    X3  A2 B2 Co1 Co2 FA_Co
    X4  A3 B3 Co2 Co3 FA_Co
.ends



.subckt Mux A B S Y

    X1  S   S_inv  INV

    MN1 A   S      1   1    NMOS_3P3    W=1um    L=Ln
    MP1 A   S_inv  1   1    PMOS_3P3    W=2um    L=Lp

    MN2 B   S_inv  1   1    NMOS_3P3    W=1um    L=Ln
    MP2 B   S      1   1    PMOS_3P3    W=2um    L=Lp

    X2  1   2      INV
    X3  2   Y      INV

.ends

.subckt Multiplexer Ci C00 C01 C10 C11 C20 C21 C30 C31 C0 C1 C2 C3

    * X0  Ci  Ci_inv INV
    
    * X1  C00 C01   Ci  C0    Mux
    * X2  C10 C11   C0  C1    Mux
    * X3  C20 C21   C1  C2    Mux
    * X4  C30 C31   C2  C3    Mux

    X1  C01 C00   Ci  C0    Mux
    X2  C11 C10   Ci  C1    Mux
    X3  C21 C20   Ci  C2    Mux
    X4  C31 C30   Ci  C3    Mux

    * X5  C0_inv C0 INV
    * X6  C1_inv C1 INV
    * X7  C2_inv C2 INV
    * X8  C3_inv C3 INV

.ends

.subckt CSA4 Ci A0 A1 A2 A3 B0 B1 B2 B3 S0 S1 S2 S3 Co3

    * Xdel0  A0 B0 D0     NOR2
    * Xdel1  A1 B1 D1     NOR2
    * Xdel2  A2 B2 D2     NOR2
    * Xdel3  A3 B3 D3     NOR2

    * Xpass0 A0 B0 P0     XOR2
    * Xpass1 A1 B1 P1     XOR2
    * Xpass2 A2 B2 P2     XOR2
    * Xpass3 A3 B3 P3     XOR2

    * Xgen0  A0 B0 G0_inv NAND2
    * Xgen1  A1 B1 G1_inv NAND2
    * Xgen2  A2 B2 G2_inv NAND2
    * Xgen3  A3 B3 G3_inv NAND2

    * Xcarry00 GND P0 P1 P2 P3 G0_inv G1_inv G2_inv G3_inv D0 D1 D2 D3 Co00 Co10 Co20 Co30 Manchester4
    * Xcarry01 VDD P0 P1 P2 P3 G0_inv G1_inv G2_inv G3_inv D0 D1 D2 D3 Co01 Co11 Co21 Co31 Manchester4
    Xcarry0 GND A0 A1 A2 A3 B0 B1 B2 B3 Co00 Co10 Co20 Co30 FA_Co4
    Xcarry1 VDD A0 A1 A2 A3 B0 B1 B2 B3 Co01 Co11 Co21 Co31 FA_Co4
    

    * X1  Co10   Co10_inv  INV
    * X2  Co10_inv   Co10_true  INV

    * X3  Co30   Co30_inv  INV
    * X4  Co30_inv   Co30_true  INV

    XMux   Ci   Co00 Co01 Co10 Co11 Co20 Co21 Co30 Co31 Co0 Co1 Co2 Co3 Multiplexer
    * XMux   Ci   Co00 Co01 Co10_true Co11 Co20 Co21 Co30_true Co31 Co0 Co1 Co2 Co3 Multiplexer

    * XS0 P0 Ci  S0 XOR2
    * XS1 P1 Co0 S1 XOR2
    * XS2 P2 Co1 S2 XOR2
    * XS3 P3 Co2 S3 XOR2

    * X0 Ci_inv Ci INV
    X0  Co0 Co0_inv INV
    X1  Co1 Co1_inv INV
    X2  Co2 Co2_inv INV
    X3  Co3 Co3_inv INV

    XS0 A0 B0 Ci  Co0_inv S0 FA_S
    XS1 A1 B1 Co0 Co1_inv S1 FA_S
    XS2 A2 B2 Co1 Co2_inv S2 FA_S
    XS3 A3 B3 Co2 Co3_inv S3 FA_S

    

.ends

X1 C0  A0 A1 A2 A3 B0 B1 B2 B3 S0 S1 S2 S3 Co3 CSA4
X2 Co3 A4 A5 A6 A7 B4 B5 B6 B7 S4 S5 S6 S7 Co7 CSA4

VDD  VDD    GND   dd
VGND GND    0     0

.param start=20.0ns delta=0.01ns end=40.0ns

VA0    A0   GND   PWL(0ns 0V `start-delta` 0V start dd `end-delta` dd end 0V) 
VA1    A1   GND   PWL(0ns 0V `start-delta` 0V start dd `end-delta` dd end 0V) 
VA2    A2   GND   PWL(0ns 0V `start-delta` 0V start 0V `end-delta` 0V end 0V) 
VA3    A3   GND   PWL(0ns 0V `start-delta` 0V start dd `end-delta` dd end 0V) 
VA4    A4   GND   PWL(0ns 0V `start-delta` 0V start dd `end-delta` dd end 0V) 
VA5    A5   GND   PWL(0ns 0V `start-delta` 0V start dd `end-delta` dd end 0V) 
VA6    A6   GND   PWL(0ns 0V `start-delta` 0V start 0V `end-delta` 0V end 0V) 
VA7    A7   GND   PWL(0ns 0V `start-delta` 0V start dd `end-delta` dd end 0V) 

VB0    B0   GND   PWL(0ns 0V `start-delta` 0V start 0V `end-delta` 0V end 0V) 
VB1    B1   GND   PWL(0ns 0V `start-delta` 0V start 0V `end-delta` 0V end 0V) 
VB2    B2   GND   PWL(0ns 0V `start-delta` 0V start dd `end-delta` dd end 0V) 
VB3    B3   GND   PWL(0ns 0V `start-delta` 0V start 0V `end-delta` 0V end 0V) 
VB4    B4   GND   PWL(0ns 0V `start-delta` 0V start 0V `end-delta` 0V end 0V) 
VB5    B5   GND   PWL(0ns 0V `start-delta` 0V start 0V `end-delta` 0V end 0V) 
VB6    B6   GND   PWL(0ns 0V `start-delta` 0V start dd `end-delta` dd end 0V) 
VB7    B7   GND   PWL(0ns 0V `start-delta` 0V start 0V `end-delta` 0V end 0V) 

VC0    C0   GND   PWL(0ns 0V `start-delta` 0V start dd `end-delta` dd end 0V)

.MEASURE TRAN vomax MAX V(Y_inv) FROM 10n TO 20n
.MEASURE TRAN vomin MIN V(Y_inv) FROM 20n TO 30n
.MEASURE TRAN tco_lookahead TRIG V(C0) VAL=0.5*dd RISE=1 TARG V(Co7) VAL=0.5*dd RISE=1
.MEASURE TRAN tPLH TRIG V(B) VAL=0.5*dd FALL=1 TARG V(Y) VAL='0.5*(vomax+vomin)' RISE=2
.MEASURE tran tr TRIG V(Y)='0.1*(vomax-vomin)+vomin' RISE=1 TARG V(Y)='0.9*(vomax-vomin)+vomin' RISE=1
.MEASURE tran tf TRIG V(Y)='0.9*(vomax-vomin)+vomin' FALL=1 TARG V(Y)='0.1*(vomax-vomin)+vomin' FALL=1
.MEASURE tran avgPower AVG P(VDD) FROM=20ns TO=60ns

.tran  0.01ns   100nS 
.probe V(Co3)  V(Co7)  p(VDD) 
**********************************
.END