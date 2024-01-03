**********************************
* xor_fakeNMOS test netlist
**********************************
.option post=2 
.lib sm046005-1j.hspice typical
.param Wp=2um Wn=1um dd=3.3V cf=0.1PF Ln=0.35um Lp=0.35um
.global VDD GND

.subckt cmos_inv IN Y_inv
MN   Y_inv   IN    GND   GND   NMOS_3P3   W=Wn  L=Ln
MP   Y_inv   IN    VDD   VDD   PMOS_3P3   W=Wp  L=Lp
.ENDS

* NMOS: D G S SUB 
* PMOS: D G S SUB


.subckt AND2 IN1 IN2 Y
MN1   a       IN2    GND   GND   NMOS_3P3   W=Wn   L=Ln
MN2   Y_inv   IN1    a     a     NMOS_3P3   W=Wn   L=Ln
MP1   Y_inv   IN1    VDD   VDD   PMOS_3P3   W=Wp   L=Lp
MP2   Y_inv   IN2    VDD   VDD   PMOS_3P3   W=Wp   L=Lp

MN3   Y       Y_inv  GND   GND   NMOS_3P3   W=Wn   L=Ln
MP3   Y       Y_inv  VDD   VDD   PMOS_3P3   W=Wp   L=Lp
.ends


.subckt XOR2 IN1 IN2 Y

X1   IN1   IN1_inv cmos_inv
X2   IN2   IN2_inv cmos_inv

Mp11 VDD   IN1        a   VDD   PMOS_3P3  L=Lp W=Wp
Mp12 VDD   IN2        a   VDD   PMOS_3P3  L=Lp W=Wp
Mp21 a     IN1_inv    Y   VDD   PMOS_3P3  L=Lp W=Wp
Mp22 a     IN2_inv    Y   VDD   PMOS_3P3  L=Lp W=Wp

Mn11 Y     IN1        b   GND   NMOS_3P3  L=Ln W=Wn
Mn12 Y     IN1_inv    c   GND   NMOS_3P3  L=Ln W=Wn
Mn21 b     IN2        GND GND   NMOS_3P3  L=Ln W=Wn
Mn22 c     IN2_inv    GND GND   NMOS_3P3  L=Ln W=Wn
.ends


.subckt CLA3 P0 P1 P2 P3 G0 G1 G2 G3 C0 Co

MN1   b         P3      GND   GND   NMOS_3P3   W=Wn   L=Ln
MN2   c         P2      b     b     NMOS_3P3   W=Wn   L=Ln
MN3   d         P1      c     c     NMOS_3P3   W=Wn   L=Ln
MN4   e         P0      d     d     NMOS_3P3   W=Wn   L=Ln
MN5   Co_inv   C0      e     e     NMOS_3P3   W=Wn   L=Ln

MN6   Co_inv   G3      GND   GND   NMOS_3P3   W=Wn   L=Ln
MN7   Co_inv   G2      b     b     NMOS_3P3   W=Wn   L=Ln
MN8   Co_inv   G1      c     c     NMOS_3P3   W=Wn   L=Ln
MN9   Co_inv   G0      d     d     NMOS_3P3   W=Wn   L=Ln


MP1   i         G3      VDD   VDD   PMOS_3P3   W=Wp   L=Lp
MP2   j         G2      i     i     PMOS_3P3   W=Wp   L=Lp
MP3   k         G1      j     j     PMOS_3P3   W=Wp   L=Lp
MP4   l         G0      k     k     PMOS_3P3   W=Wp   L=Lp
MP5   Co_inv   C0      l     l     PMOS_3P3   W=Wp   L=Lp

MP6   Co_inv   P3      VDD   VDD   PMOS_3P3   W=Wp   L=Lp
MP7   Co_inv   P2      i     i     PMOS_3P3   W=Wp   L=Lp
MP8   Co_inv   P1      j     j     PMOS_3P3   W=Wp   L=Lp
MP9   Co_inv   P0      k     k     PMOS_3P3   W=Wp   L=Lp

X1    Co_inv   Co     cmos_inv

.ends



.subckt CLA2 P0 P1 P2 G0 G1 G2 C0 Co

MN2   c         P2      GND   GND   NMOS_3P3   W=Wn   L=Ln
MN3   d         P1      c     c     NMOS_3P3   W=Wn   L=Ln
MN4   e         P0      d     d     NMOS_3P3   W=Wn   L=Ln
MN5   Co_inv   C0      e     e     NMOS_3P3   W=Wn   L=Ln

MN7   Co_inv   G2      GND   GND   NMOS_3P3   W=Wn   L=Ln
MN8   Co_inv   G1      c     c     NMOS_3P3   W=Wn   L=Ln
MN9   Co_inv   G0      d     d     NMOS_3P3   W=Wn   L=Ln


MP2   j         G2      VDD   VDD   PMOS_3P3   W=Wp   L=Lp
MP3   k         G1      j     j     PMOS_3P3   W=Wp   L=Lp
MP4   l         G0      k     k     PMOS_3P3   W=Wp   L=Lp
MP5   Co_inv   C0      l     l     PMOS_3P3   W=Wp   L=Lp

MP7   Co_inv   P2      VDD   VDD   PMOS_3P3   W=Wp   L=Lp
MP8   Co_inv   P1      j     j     PMOS_3P3   W=Wp   L=Lp
MP9   Co_inv   P0      k     k     PMOS_3P3   W=Wp   L=Lp

X1    Co_inv   Co     cmos_inv

.ends


.subckt CLA1 P0 P1 G0 G1 C0 Co

MN3   d         P1      GND   GND   NMOS_3P3   W=Wn   L=Ln
MN4   e         P0      d     d     NMOS_3P3   W=Wn   L=Ln
MN5   Co_inv   C0      e     e     NMOS_3P3   W=Wn   L=Ln

MN8   Co_inv   G1      GND   GND   NMOS_3P3   W=Wn   L=Ln
MN9   Co_inv   G0      d     d     NMOS_3P3   W=Wn   L=Ln


MP3   k         G1      VDD   VDD   PMOS_3P3   W=Wp   L=Lp
MP4   l         G0      k     k     PMOS_3P3   W=Wp   L=Lp
MP5   Co_inv   C0      l     l     PMOS_3P3   W=Wp   L=Lp

MP8   Co_inv   P1      VDD   VDD   PMOS_3P3   W=Wp   L=Lp
MP9   Co_inv   P0      k     k     PMOS_3P3   W=Wp   L=Lp

X1    Co_inv   Co     cmos_inv

.ends

.subckt CLA0 P0 G0 C0 Co

MN4   e         P0      GND   GND   NMOS_3P3   W=Wn   L=Ln
MN5   Co_inv   C0      e     e     NMOS_3P3   W=Wn   L=Ln

MN9   Co_inv   G0      GND   GND   NMOS_3P3   W=Wn   L=Ln


MP4   l         G0      VDD   VDD   PMOS_3P3   W=Wp   L=Lp
MP5   Co_inv   C0      l     l     PMOS_3P3   W=Wp   L=Lp

MP9   Co_inv   P0      VDD   VDD   PMOS_3P3   W=Wp   L=Lp

X1    Co_inv   Co     cmos_inv

.ends

Xpass0 A0 B0 P0 XOR2
Xpass1 A1 B1 P1 XOR2
Xpass2 A2 B2 P2 XOR2
Xpass3 A3 B3 P3 XOR2

Xgen0  A0 B0 G0 AND2
Xgen1  A1 B1 G1 AND2
Xgen2  A2 B2 G2 AND2
Xgen3  A3 B3 G3 AND2

XCo3 P0 P1 P2 P3 G0 G1 G2 G3 C0 Co3 CLA3
XCo2 P0 P1 P2 G0 G1 G2 C0 Co2 CLA2
XCo1 P0 P1 G0 G1 C0 Co1 CLA1
XCo0 P0 G0 C0 Co0 CLA0

XS0 P0 C0  S0 XOR2
XS1 P1 Co0 S1 XOR2
XS2 P2 Co1 S2 XOR2
XS3 P3 Co2 S3 XOR2

* CL   Y_inv    GND   cf
VDD  VDD    GND   dd
VGND GND    0     0

VIN1    A0   GND   PWL(0ns 0V 19.9ns 0V 20.0ns dd 39.9ns dd 40ns 0V r) 
VIN2    A1   GND   PWL(0ns 0V 9.9ns 0V 10.0ns dd 29.9ns dd 30ns 0V 40ns 0V r)
VIN3    A2   GND   PWL(0ns 0V 19.9ns 0V 20.0ns dd 39.9ns dd 40ns 0V r) 
VIN4    A3   GND   PWL(0ns 0V 9.9ns 0V 10.0ns dd 29.9ns dd 30ns 0V 40ns 0V r)

VIN5    B0   GND   PWL(0ns 0V 19.9ns 0V 20.0ns dd 39.9ns dd 40ns 0V r) 
VIN6    B1   GND   PWL(0ns 0V 9.9ns 0V 10.0ns dd 29.9ns dd 30ns 0V 40ns 0V r)
VIN7    B2   GND   PWL(0ns 0V 19.9ns 0V 20.0ns dd 39.9ns dd 40ns 0V r) 
VIN8    B3   GND   PWL(0ns 0V 9.9ns 0V 10.0ns dd 29.9ns dd 30ns 0V 40ns 0V r)

VIN9    C0   0   0 

.MEASURE TRAN vomax MAX V(Y_inv) FROM 10n TO 20n
.MEASURE TRAN vomin MIN V(Y_inv) FROM 20n TO 30n
.MEASURE TRAN tPHL TRIG V(A) VAL=0.5*dd RISE=1 TARG V(Y) VAL='0.5*(vomax+vomin)' FALL=1
.MEASURE TRAN tPLH TRIG V(B) VAL=0.5*dd FALL=1 TARG V(Y) VAL='0.5*(vomax+vomin)' RISE=2
.MEASURE tran tr TRIG V(Y)='0.1*(vomax-vomin)+vomin' RISE=1 TARG V(Y)='0.9*(vomax-vomin)+vomin' RISE=1
.MEASURE tran tf TRIG V(Y)='0.9*(vomax-vomin)+vomin' FALL=1 TARG V(Y)='0.1*(vomax-vomin)+vomin' FALL=1
.MEASURE tran avgPower AVG P(VDD) FROM=20ns TO=60ns

.tran  0.01ns   100nS 
.probe p(VDD) 
**********************************
.END