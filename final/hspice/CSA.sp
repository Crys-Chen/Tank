**********************************
* xor_fakeNMOS test netlist
**********************************
* Co0有问题
.option post=2 
.lib sm046005-1j.hspice typical
.param Wp=2um Wn=1um dd=3.3V cf=0.1PF Ln=0.35um Lp=0.35um
.global VDD GND

.subckt INV IN Y_inv
    MN   Y_inv   IN    GND   GND   NMOS_3P3   W=Wn  L=Ln
    MP   Y_inv   IN    VDD   VDD   PMOS_3P3   W=Wp  L=Lp
.ENDS

* NMOS: D G S SUB 
* PMOS: D G S SUB

.subckt NOR2 IN1 IN2 Y_inv

    MN1   Y_inv   IN2    GND   GND   NMOS_3P3   W=Wn   L=0.35um
    MN2   Y_inv   IN1    GND   GND   NMOS_3P3   W=Wn   L=0.35um
    MP1   a       IN1    VDD   VDD   PMOS_3P3   W=Wp   L=0.35um
    MP2   Y_inv   IN2    a     a     PMOS_3P3   W=Wp   L=0.35um 

.ends


.subckt AND2 IN1 IN2 Y

    MN1   a       IN2    GND   GND   NMOS_3P3   W=Wn   L=Ln
    MN2   Y_inv   IN1    a     a     NMOS_3P3   W=Wn   L=Ln
    MP1   Y_inv   IN1    VDD   VDD   PMOS_3P3   W=Wp   L=Lp
    MP2   Y_inv   IN2    VDD   VDD   PMOS_3P3   W=Wp   L=Lp

    MN3   Y       Y_inv  GND   GND   NMOS_3P3   W=Wn   L=Ln
    MP3   Y       Y_inv  VDD   VDD   PMOS_3P3   W=Wp   L=Lp

.ends

.subckt NAND2 IN1 IN2 Y_inv
    MN1   a       IN2    GND   GND   NMOS_3P3   W=Wn   L=Ln
    MN2   Y_inv   IN1    a     a     NMOS_3P3   W=Wn   L=Ln
    MP1   Y_inv   IN1    VDD   VDD   PMOS_3P3   W=Wp   L=Lp
    MP2   Y_inv   IN2    VDD   VDD   PMOS_3P3   W=Wp   L=Lp
.ends


.subckt XOR2 IN1 IN2 Y

    X1   IN1   IN1_inv INV
    X2   IN2   IN2_inv INV

    Mp1 VDD   IN1        a   VDD   PMOS_3P3  L=Lp W=`Wp`
    Mp2 VDD   IN2        a   VDD   PMOS_3P3  L=Lp W=`Wp`
    Mp3 a     IN1_inv    Y   VDD   PMOS_3P3  L=Lp W=`Wp`
    Mp4 a     IN2_inv    Y   VDD   PMOS_3P3  L=Lp W=`Wp`

    Mn1 Y     IN1        b   GND   NMOS_3P3  L=Ln W=`Wn`
    Mn2 Y     IN1_inv    c   GND   NMOS_3P3  L=Ln W=`Wn`
    Mn3 b     IN2        GND GND   NMOS_3P3  L=Ln W=`Wn`
    Mn4 c     IN2_inv    GND GND   NMOS_3P3  L=Ln W=`Wn`

.ends


.subckt Manchester Ci Pi Gi_inv Di Co

    X1  Pi  Pi_inv  INV

    * MN1 Ci  Pi      1   1    NMOS_3P3    W=Wn    L=Ln
    * MP1 Ci  Pi_inv  1   1    PMOS_3P3    W=Wp    L=Lp

    * MN2 1   Di      GND  GND   NMOS_3P3    W=Wn    L=Ln
    * MP2 1   Gi_inv  VDD  VDD   PMOS_3P3    W=Wp    L=Lp

    * * MP3 1   Co      VDD  VDD   PMOS_3P3    W=Wp    L=Lp
    * X2  1   Co_inv  INV
    * X3  Co_inv   Co INV

    MN1 Ci  Pi      Co   GND    NMOS_3P3    W=Wn    L=Ln
    MP1 Ci  Pi_inv  Co   VDD    PMOS_3P3    W=Wp   L=Lp
    * MN1 Ci  Pi      Co   Co    NMOS_3P3    W=Wn2    L=Ln
    * MP1 Ci  Pi_inv  Co   Co    PMOS_3P3    W=Wp2    L=Lp

    MN2 Co   Di      GND  GND   NMOS_3P3    W=Wn    L=Ln
    MP2 Co   Gi_inv  VDD  VDD   PMOS_3P3    W=Wp    L=Lp
    
.ends


.subckt Manchester4 C0 P0 P1 P2 P3 G0_inv G1_inv G2_inv G3_inv D0 D1 D2 D3 Co0 Co1 Co2 Co3

    X1  C0   P0      G0_inv     D0   Co0    Manchester
    X2  Co0  P1      G1_inv     D1   Co1    Manchester
    X3  Co1  P2      G2_inv     D2   Co2    Manchester
    X4  Co2  P3      G3_inv     D3   Co3    Manchester
        
.ends

.subckt Mux A B S Y

    X1  S   S_inv  INV

    MN1 A   S      1   1    NMOS_3P3    W=Wn    L=Ln
    MP1 A   S_inv  1   1    PMOS_3P3    W=Wp    L=Lp

    MN2 B   S_inv  1   1    NMOS_3P3    W=Wn    L=Ln
    MP2 B   S      1   1    PMOS_3P3    W=Wp    L=Lp

    X2  1   2      INV
    X3  2   Y      INV

.ends

.subckt Multiplexer Ci C00 C01 C10 C11 C20 C21 C30 C31 C0 C1 C2 C3
    
    X1  C01 C00   Ci  C0    Mux
    X2  C11 C10   Ci  C1    Mux
    X3  C21 C20   Ci  C2    Mux
    X4  C31 C30   Ci  C3    Mux

.ends

.subckt CSA4 Ci A0 A1 A2 A3 B0 B1 B2 B3 S0 S1 S2 S3 Co3

    Xdel0  A0 B0 D0     NOR2
    Xdel1  A1 B1 D1     NOR2
    Xdel2  A2 B2 D2     NOR2
    Xdel3  A3 B3 D3     NOR2

    Xpass0 A0 B0 P0     XOR2
    Xpass1 A1 B1 P1     XOR2
    Xpass2 A2 B2 P2     XOR2
    Xpass3 A3 B3 P3     XOR2

    Xgen0  A0 B0 G0_inv NAND2
    Xgen1  A1 B1 G1_inv NAND2
    Xgen2  A2 B2 G2_inv NAND2
    Xgen3  A3 B3 G3_inv NAND2

    Xcarry00 GND P0 P1 P2 P3 G0_inv G1_inv G2_inv G3_inv D0 D1 D2 D3 Co00 Co10 Co20 Co30 Manchester4
    Xcarry01 VDD P0 P1 P2 P3 G0_inv G1_inv G2_inv G3_inv D0 D1 D2 D3 Co01 Co11 Co21 Co31 Manchester4

    * X1  Co10   Co10_inv  INV
    * X2  Co10_inv   Co10_true  INV

    * X3  Co30   Co30_inv  INV
    * X4  Co30_inv   Co30_true  INV

    XMux   Ci   Co00 Co01 Co10 Co11 Co20 Co21 Co30 Co31 Co0 Co1 Co2 Co3 Multiplexer
    * XMux   Ci   Co00 Co01 Co10_true Co11 Co20 Co21 Co30_true Co31 Co0 Co1 Co2 Co3 Multiplexer

    XS0 P0 Ci  S0 XOR2
    XS1 P1 Co0 S1 XOR2
    XS2 P2 Co1 S2 XOR2
    XS3 P3 Co2 S3 XOR2

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

.MEASURE TRAN vomax MAX V(C0) FROM 0n TO 20n
.MEASURE TRAN vomin MIN V(C0) FROM 0n TO 20n
.MEASURE TRAN tco TRIG V(C0) VAL=0.5*dd RISE=1 TARG V(Co7) VAL=0.5*dd RISE=1
.MEASURE TRAN tPLH TRIG V(B) VAL=0.5*dd FALL=1 TARG V(Y) VAL='0.5*(vomax+vomin)' RISE=2
.MEASURE tran tr TRIG V(Y)='0.1*(vomax-vomin)+vomin' RISE=1 TARG V(Y)='0.9*(vomax-vomin)+vomin' RISE=1
.MEASURE tran tf TRIG V(Y)='0.9*(vomax-vomin)+vomin' FALL=1 TARG V(Y)='0.1*(vomax-vomin)+vomin' FALL=1
.MEASURE tran avgPower AVG P(VDD) FROM=20ns TO=60ns

.tran  0.01ns   100nS 
.probe V(Co3)  V(Co7)  p(VDD) 
**********************************
.END