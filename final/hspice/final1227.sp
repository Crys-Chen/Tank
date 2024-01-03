**********************************
* xor_fakeNMOS test netlist
**********************************
.option post=2 
.lib sm046005-1j.hspice typical
.param Wp=0.35um Wn=0.35um dd=3.3V cf=0.1PF Ln=0.35um Lp=0.35um Wp2=2um Wn2=1um
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

.subckt CLA7 P0 P1 P2 P3 P4 P5 P6 P7 G0 G1 G2 G3 G4 G5 G6 G7 C0 Co

MN71  7         P7      GND   GND   NMOS_3P3   W=Wn   L=Ln
MN61  5         P6      7     7    NMOS_3P3   W=Wn   L=Ln
MN51  3         P5      5     5     NMOS_3P3   W=Wn   L=Ln
MN41  1         P4      3     3     NMOS_3P3   W=Wn   L=Ln
MN1   b         P3      1     1     NMOS_3P3   W=Wn   L=Ln
MN2   c         P2      b     b     NMOS_3P3   W=Wn   L=Ln
MN3   d         P1      c     c     NMOS_3P3   W=Wn   L=Ln
MN4   e         P0      d     d     NMOS_3P3   W=Wn   L=Ln
MN5   Co_inv    C0      e     e     NMOS_3P3   W=Wn   L=Ln

MN72  Co_inv   G7      GND   GND   NMOS_3P3   W=Wn   L=Ln
MN62  Co_inv   G6      7     7   NMOS_3P3   W=Wn   L=Ln
MN52  Co_inv   G5      5     5   NMOS_3P3   W=Wn   L=Ln
MN42  Co_inv   G4      3     3   NMOS_3P3   W=Wn   L=Ln
MN6   Co_inv   G3      1     1     NMOS_3P3   W=Wn   L=Ln
MN7   Co_inv   G2      b     b     NMOS_3P3   W=Wn   L=Ln
MN8   Co_inv   G1      c     c     NMOS_3P3   W=Wn   L=Ln
MN9   Co_inv   G0      d     d     NMOS_3P3   W=Wn   L=Ln


MN73  8         G7      VDD   VDD   PMOS_3P3   W=Wp   L=Lp
MN63  6         G6      8     8   PMOS_3P3   W=Wp   L=Lp
MN53  4         G5      6     6   PMOS_3P3   W=Wp   L=Lp
MN43  2         G4      4     4   PMOS_3P3   W=Wp   L=Lp
MP1   i         G3      2     2     PMOS_3P3   W=Wp   L=Lp
MP2   j         G2      i     i     PMOS_3P3   W=Wp   L=Lp
MP3   k         G1      j     j     PMOS_3P3   W=Wp   L=Lp
MP4   l         G0      k     k     PMOS_3P3   W=Wp   L=Lp
MP5   Co_inv   C0      l     l     PMOS_3P3   W=Wp   L=Lp

MN74  Co_inv   P7      VDD   VDD   PMOS_3P3   W=Wp   L=Lp
MN64  Co_inv   P6      8     8   PMOS_3P3   W=Wp   L=Lp
MN54  Co_inv   P5      6     6   PMOS_3P3   W=Wp   L=Lp
MN44  Co_inv   P4      4     4   PMOS_3P3   W=Wp   L=Lp
MP6   Co_inv   P3      2     2   PMOS_3P3   W=Wp   L=Lp
MP7   Co_inv   P2      i     i     PMOS_3P3   W=Wp   L=Lp
MP8   Co_inv   P1      j     j     PMOS_3P3   W=Wp   L=Lp
MP9   Co_inv   P0      k     k     PMOS_3P3   W=Wp   L=Lp

X1    Co_inv   Co     INV

.ends


.subckt CLA6 P0 P1 P2 P3 P4 P5 P6 G0 G1 G2 G3 G4 G5 G6 C0 Co

MN61  5         P6      GND   GND   NMOS_3P3   W=Wn   L=Ln
MN51  3         P5      5     5     NMOS_3P3   W=Wn   L=Ln
MN41  1         P4      3     3     NMOS_3P3   W=Wn   L=Ln
MN1   b         P3      1     1     NMOS_3P3   W=Wn   L=Ln
MN2   c         P2      b     b     NMOS_3P3   W=Wn   L=Ln
MN3   d         P1      c     c     NMOS_3P3   W=Wn   L=Ln
MN4   e         P0      d     d     NMOS_3P3   W=Wn   L=Ln
MN5   Co_inv    C0      e     e     NMOS_3P3   W=Wn   L=Ln

MN62  Co_inv   G6      GND   GND   NMOS_3P3   W=Wn   L=Ln
MN52  Co_inv   G5      5     5   NMOS_3P3   W=Wn   L=Ln
MN42  Co_inv   G4      3     3   NMOS_3P3   W=Wn   L=Ln
MN6   Co_inv   G3      1     1     NMOS_3P3   W=Wn   L=Ln
MN7   Co_inv   G2      b     b     NMOS_3P3   W=Wn   L=Ln
MN8   Co_inv   G1      c     c     NMOS_3P3   W=Wn   L=Ln
MN9   Co_inv   G0      d     d     NMOS_3P3   W=Wn   L=Ln

MN63  6         G6      VDD   VDD   PMOS_3P3   W=Wp   L=Lp
MN53  4         G5      6     6   PMOS_3P3   W=Wp   L=Lp
MN43  2         G4      4     4   PMOS_3P3   W=Wp   L=Lp
MP1   i         G3      2     2     PMOS_3P3   W=Wp   L=Lp
MP2   j         G2      i     i     PMOS_3P3   W=Wp   L=Lp
MP3   k         G1      j     j     PMOS_3P3   W=Wp   L=Lp
MP4   l         G0      k     k     PMOS_3P3   W=Wp   L=Lp
MP5   Co_inv   C0      l     l     PMOS_3P3   W=Wp   L=Lp

MN64  Co_inv   P6      VDD   VDD   PMOS_3P3   W=Wp   L=Lp
MN54  Co_inv   P5      6     6   PMOS_3P3   W=Wp   L=Lp
MN44  Co_inv   P4      4     4   PMOS_3P3   W=Wp   L=Lp
MP6   Co_inv   P3      2     2   PMOS_3P3   W=Wp   L=Lp
MP7   Co_inv   P2      i     i     PMOS_3P3   W=Wp   L=Lp
MP8   Co_inv   P1      j     j     PMOS_3P3   W=Wp   L=Lp
MP9   Co_inv   P0      k     k     PMOS_3P3   W=Wp   L=Lp

X1    Co_inv   Co     INV

.ends


.subckt CLA5 P0 P1 P2 P3 P4 P5 G0 G1 G2 G3 G4 G5 C0 Co

MN51  3         P5      GND   GND   NMOS_3P3   W=Wn   L=Ln
MN41  1         P4      3     3     NMOS_3P3   W=Wn   L=Ln
MN1   b         P3      1     1     NMOS_3P3   W=Wn   L=Ln
MN2   c         P2      b     b     NMOS_3P3   W=Wn   L=Ln
MN3   d         P1      c     c     NMOS_3P3   W=Wn   L=Ln
MN4   e         P0      d     d     NMOS_3P3   W=Wn   L=Ln
MN5   Co_inv    C0      e     e     NMOS_3P3   W=Wn   L=Ln

MN52  Co_inv   G5      GND   GND   NMOS_3P3   W=Wn   L=Ln
MN42  Co_inv   G4      3     3   NMOS_3P3   W=Wn   L=Ln
MN6   Co_inv   G3      1     1     NMOS_3P3   W=Wn   L=Ln
MN7   Co_inv   G2      b     b     NMOS_3P3   W=Wn   L=Ln
MN8   Co_inv   G1      c     c     NMOS_3P3   W=Wn   L=Ln
MN9   Co_inv   G0      d     d     NMOS_3P3   W=Wn   L=Ln

MN53  4         G5      VDD   VDD   PMOS_3P3   W=Wp   L=Lp
MN43  2         G4      4     4   PMOS_3P3   W=Wp   L=Lp
MP1   i         G3      2     2     PMOS_3P3   W=Wp   L=Lp
MP2   j         G2      i     i     PMOS_3P3   W=Wp   L=Lp
MP3   k         G1      j     j     PMOS_3P3   W=Wp   L=Lp
MP4   l         G0      k     k     PMOS_3P3   W=Wp   L=Lp
MP5   Co_inv   C0      l     l     PMOS_3P3   W=Wp   L=Lp

MN54  Co_inv   P5      VDD   VDD   PMOS_3P3   W=Wp   L=Lp
MN44  Co_inv   P4      4     4   PMOS_3P3   W=Wp   L=Lp
MP6   Co_inv   P3      2     2   PMOS_3P3   W=Wp   L=Lp
MP7   Co_inv   P2      i     i     PMOS_3P3   W=Wp   L=Lp
MP8   Co_inv   P1      j     j     PMOS_3P3   W=Wp   L=Lp
MP9   Co_inv   P0      k     k     PMOS_3P3   W=Wp   L=Lp

X1    Co_inv   Co     INV

.ends


.subckt CLA4 P0 P1 P2 P3 P4 G0 G1 G2 G3 G4 C0 Co

MN41  1         P4      GND   GND   NMOS_3P3   W=Wn   L=Ln
MN1   b         P3      1     1   NMOS_3P3   W=Wn   L=Ln
MN2   c         P2      b     b     NMOS_3P3   W=Wn   L=Ln
MN3   d         P1      c     c     NMOS_3P3   W=Wn   L=Ln
MN4   e         P0      d     d     NMOS_3P3   W=Wn   L=Ln
MN5   Co_inv    C0      e     e     NMOS_3P3   W=Wn   L=Ln

MN42  Co_inv   G4      GND   GND   NMOS_3P3   W=Wn   L=Ln
MN6   Co_inv   G3      1     1     NMOS_3P3   W=Wn   L=Ln
MN7   Co_inv   G2      b     b     NMOS_3P3   W=Wn   L=Ln
MN8   Co_inv   G1      c     c     NMOS_3P3   W=Wn   L=Ln
MN9   Co_inv   G0      d     d     NMOS_3P3   W=Wn   L=Ln

MN43  2         G4      VDD   VDD   PMOS_3P3   W=Wn   L=Ln
MP1   i         G3      2     2     PMOS_3P3   W=Wp   L=Lp
MP2   j         G2      i     i     PMOS_3P3   W=Wp   L=Lp
MP3   k         G1      j     j     PMOS_3P3   W=Wp   L=Lp
MP4   l         G0      k     k     PMOS_3P3   W=Wp   L=Lp
MP5   Co_inv   C0      l     l     PMOS_3P3   W=Wp   L=Lp


MN44  Co_inv   P4      VDD   VDD   PMOS_3P3   W=Wn   L=Ln
MP6   Co_inv   P3      2     2   PMOS_3P3   W=Wp   L=Lp
MP7   Co_inv   P2      i     i     PMOS_3P3   W=Wp   L=Lp
MP8   Co_inv   P1      j     j     PMOS_3P3   W=Wp   L=Lp
MP9   Co_inv   P0      k     k     PMOS_3P3   W=Wp   L=Lp

X1    Co_inv   Co     INV

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

X1    Co_inv   Co     INV

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

X1    Co_inv   Co     INV

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

X1    Co_inv   Co     INV

.ends

.subckt CLA0 P0 G0 C0 Co

MN4   e         P0      GND   GND   NMOS_3P3   W=Wn   L=Ln
MN5   Co_inv   C0      e     e     NMOS_3P3   W=Wn   L=Ln

MN9   Co_inv   G0      GND   GND   NMOS_3P3   W=Wn   L=Ln


MP4   l         G0      VDD   VDD   PMOS_3P3   W=Wp   L=Lp
MP5   Co_inv   C0      l     l     PMOS_3P3   W=Wp   L=Lp

MP9   Co_inv   P0      VDD   VDD   PMOS_3P3   W=Wp   L=Lp

X1    Co_inv   Co     INV

.ends



.subckt Manchester Ci Pi Gi_inv Di Co

    X1  Pi  Pi_inv  INV

    MN1 Ci  Pi      Co   GND    NMOS_3P3    W=Wn2    L=Ln
    MP1 Ci  Pi_inv  Co   VDD    PMOS_3P3    W=Wp2   L=Lp

    MN2 Co   Di      GND  GND   NMOS_3P3    W=Wn2    L=Ln
    MP2 Co   Gi_inv  VDD  VDD   PMOS_3P3    W=Wp2    L=Lp

    
.ends


.subckt Manchester4 C0 P0 P1 P2 P3 G0_inv G1_inv G2_inv G3_inv D0 D1 D2 D3 Co0 Co1 Co2 Co3

    X1  C0   P0      G0_inv     D0   Co0    Manchester
    X2  Co0  P1      G1_inv     D1   Co1    Manchester
    X3  Co1  P2      G2_inv     D2   Co2    Manchester
    X4  Co2  P3      G3_inv     D3   Co3    Manchester
        
.ends

.subckt Mux A B S Y

    X1  S   S_inv  INV

    MN1 A   S      1   1    NMOS_3P3    W=Wn2    L=Ln
    MP1 A   S_inv  1   1    PMOS_3P3    W=Wp2    L=Lp

    MN2 B   S_inv  1   1    NMOS_3P3    W=Wn2    L=Ln
    MP2 B   S      1   1    PMOS_3P3    W=Wp2    L=Lp

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
    * X1  Co01 Co00   Ci  Co0    Mux
    * XMux   Ci   Co00 Co01 Co10_true Co11 Co20 Co21 Co30_true Co31 Co0 Co1 Co2 Co3 Multiplexer

    XS0 P0 Ci  S0 XOR2
    XS1 P1 Co0 S1 XOR2
    XS2 P2 Co1 S2 XOR2
    XS3 P3 Co2 S3 XOR2

.ends


Xpass0 A0 B0 P0 XOR2
Xpass1 A1 B1 P1 XOR2
Xpass2 A2 B2 P2 XOR2
Xpass3 A3 B3 P3 XOR2
Xpass4 A4 B4 P4 XOR2
Xpass5 A5 B5 P5 XOR2
Xpass6 A6 B6 P6 XOR2
Xpass7 A7 B7 P7 XOR2

Xgen0  A0 B0 G0 AND2
Xgen1  A1 B1 G1 AND2
Xgen2  A2 B2 G2 AND2
Xgen3  A3 B3 G3 AND2
Xgen4  A4 B4 G4 AND2
Xgen5  A5 B5 G5 AND2
Xgen6  A6 B6 G6 AND2
Xgen7  A7 B7 G7 AND2

XCo7 P0 P1 P2 P3 P4 P5 P6 P7 G0 G1 G2 G3 G4 G5 G6 G7 C0 Co7 CLA7
XCo6 P0 P1 P2 P3 P4 P5 P6 G0 G1 G2 G3 G4 G5 G6 C0 Co6 CLA6
XCo5 P0 P1 P2 P3 P4 P5 G0 G1 G2 G3 G4 G5 C0 Co5 CLA5
XCo4 P0 P1 P2 P3 P4 G0 G1 G2 G3 G4 C0 Co4 CLA4
XCo3 P0 P1 P2 P3 G0 G1 G2 G3 C0 Co3 CLA3
XCo2 P0 P1 P2 G0 G1 G2 C0 Co2 CLA2
XCo1 P0 P1 G0 G1 C0 Co1 CLA1
XCo0 P0 G0 C0 Co0 CLA0

XS0 P0 C0  S0 XOR2
XS1 P1 Co0 S1 XOR2
XS2 P2 Co1 S2 XOR2
XS3 P3 Co2 S3 XOR2
XS4 P4 Co3 S4 XOR2
XS5 P5 Co4 S5 XOR2
XS6 P6 Co5 S6 XOR2
XS7 P7 Co6 S7 XOR2


X1 Co7  A8 A9 A10 A11 B8 B9 B10 B11 S8 S9 S10 S11 Co11 CSA4
X2 Co11 A12 A13 A14 A15 B12 B13 B14 B15 S12 S13 S14 S15 Co15 CSA4


* CL   Y_inv    GND   cf
VDD  VDD    GND   dd
VGND GND    0     0

.param start=20.0ns delta=0.01ns end=40.0ns

* VIN1    A0   GND   PWL(0ns 0V `start-delta` 0V start dd `end-delta` dd end 0V) 
* VIN2    A1   GND   PWL(0ns 0V `start-delta` 0V start dd `end-delta` dd end 0V) 
* VIN3    A2   GND   PWL(0ns 0V `start-delta` 0V start 0V `end-delta` 0V end 0V) 
* VIN4    A3   GND   PWL(0ns 0V `start-delta` 0V start dd `end-delta` dd end 0V) 

* VIN5    B0   GND   PWL(0ns 0V `start-delta` 0V start 0V `end-delta` 0V end 0V) 
* VIN6    B1   GND   PWL(0ns 0V `start-delta` 0V start 0V `end-delta` 0V end 0V) 
* VIN7    B2   GND   PWL(0ns 0V `start-delta` 0V start dd `end-delta` dd end 0V) 
* VIN8    B3   GND   PWL(0ns 0V `start-delta` 0V start 0V `end-delta` 0V end 0V) 

* VIN9    C0   GND   PWL(0ns 0V `start-delta` 0V start dd `end-delta` dd end 0V)


VA0    A0   GND   PWL(0ns 0V `start-delta` 0V start dd `end-delta` dd end 0V) 
VA1    A1   GND   PWL(0ns 0V `start-delta` 0V start dd `end-delta` dd end 0V) 
VA2    A2   GND   PWL(0ns 0V `start-delta` 0V start 0V `end-delta` 0V end 0V) 
VA3    A3   GND   PWL(0ns 0V `start-delta` 0V start dd `end-delta` dd end 0V) 
VA4    A4   GND   PWL(0ns 0V `start-delta` 0V start dd `end-delta` dd end 0V) 
VA5    A5   GND   PWL(0ns 0V `start-delta` 0V start dd `end-delta` dd end 0V) 
VA6    A6   GND   PWL(0ns 0V `start-delta` 0V start 0V `end-delta` 0V end 0V) 
VA7    A7   GND   PWL(0ns 0V `start-delta` 0V start dd `end-delta` dd end 0V) 
VA8    A8   GND   PWL(0ns 0V `start-delta` 0V start dd `end-delta` dd end 0V) 
VA9    A9   GND   PWL(0ns 0V `start-delta` 0V start dd `end-delta` dd end 0V) 
VA10    A10   GND   PWL(0ns 0V `start-delta` 0V start 0V `end-delta` 0V end 0V) 
VA11    A11   GND   PWL(0ns 0V `start-delta` 0V start dd `end-delta` dd end 0V) 
VA12    A12   GND   PWL(0ns 0V `start-delta` 0V start dd `end-delta` dd end 0V) 
VA13    A13   GND   PWL(0ns 0V `start-delta` 0V start dd `end-delta` dd end 0V) 
VA14    A14   GND   PWL(0ns 0V `start-delta` 0V start 0V `end-delta` 0V end 0V) 
VA15    A15   GND   PWL(0ns 0V `start-delta` 0V start dd `end-delta` dd end 0V) 


VB0    B0   GND   PWL(0ns 0V `start-delta` 0V start 0V `end-delta` 0V end 0V) 
VB1    B1   GND   PWL(0ns 0V `start-delta` 0V start 0V `end-delta` 0V end 0V) 
VB2    B2   GND   PWL(0ns 0V `start-delta` 0V start dd `end-delta` dd end 0V) 
VB3    B3   GND   PWL(0ns 0V `start-delta` 0V start 0V `end-delta` 0V end 0V) 
VB4    B4   GND   PWL(0ns 0V `start-delta` 0V start 0V `end-delta` 0V end 0V) 
VB5    B5   GND   PWL(0ns 0V `start-delta` 0V start 0V `end-delta` 0V end 0V) 
VB6    B6   GND   PWL(0ns 0V `start-delta` 0V start dd `end-delta` dd end 0V) 
VB7    B7   GND   PWL(0ns 0V `start-delta` 0V start 0V `end-delta` 0V end 0V) 
VB8    B8   GND   PWL(0ns 0V `start-delta` 0V start 0V `end-delta` 0V end 0V) 
VB9    B9   GND   PWL(0ns 0V `start-delta` 0V start 0V `end-delta` 0V end 0V) 
VB10    B10   GND   PWL(0ns 0V `start-delta` 0V start dd `end-delta` dd end 0V) 
VB11    B11   GND   PWL(0ns 0V `start-delta` 0V start 0V `end-delta` 0V end 0V) 
VB12    B12   GND   PWL(0ns 0V `start-delta` 0V start 0V `end-delta` 0V end 0V) 
VB13    B13   GND   PWL(0ns 0V `start-delta` 0V start 0V `end-delta` 0V end 0V) 
VB14    B14   GND   PWL(0ns 0V `start-delta` 0V start dd `end-delta` dd end 0V) 
VB15    B15   GND   PWL(0ns 0V `start-delta` 0V start 0V `end-delta` 0V end 0V) 

VC0    C0   GND   PWL(0ns 0V `start-delta` 0V start dd `end-delta` dd end 0V)

.MEASURE TRAN vomax MAX V(Y_inv) FROM 10n TO 20n
.MEASURE TRAN vomin MIN V(Y_inv) FROM 20n TO 30n
.MEASURE TRAN tco_total TRIG V(C0) VAL=0.5*dd RISE=1 TARG V(Co15) VAL=0.5*dd RISE=1
.MEASURE TRAN tco_lookahead TRIG V(C0) VAL=0.5*dd RISE=1 TARG V(Co7) VAL=0.5*dd RISE=1
.MEASURE TRAN tco_select TRIG V(Co7) VAL=0.5*dd RISE=1 TARG V(Co15) VAL=0.5*dd RISE=1
.MEASURE TRAN tPLH TRIG V(B) VAL=0.5*dd FALL=1 TARG V(Y) VAL='0.5*(vomax+vomin)' RISE=2
.MEASURE tran tr TRIG V(Y)='0.1*(vomax-vomin)+vomin' RISE=1 TARG V(Y)='0.9*(vomax-vomin)+vomin' RISE=1
.MEASURE tran tf TRIG V(Y)='0.9*(vomax-vomin)+vomin' FALL=1 TARG V(Y)='0.1*(vomax-vomin)+vomin' FALL=1
.MEASURE tran avgPower AVG P(VDD) FROM=20ns TO=60ns

.tran  0.01ns   100nS 
.probe p(VDD) 
**********************************
.END