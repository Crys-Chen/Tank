module CSA (
    input   [7:0] A, B,
    input   Cin,
    output  [7:0] S,
    output  Cout
    );

    wire    sel;
    wire    Cout1, Cout2;
    wire    [3:0]S1,S2;

    CLA4    u0(sel,S[3:0],A[3:0],B[3:0],Cin);
    CLA4    u1(Cout1,S1,A[7:4],B[7:4],0);
    CLA4    u2(Cout2,S2,A[7:4],B[7:4],1);

    Multiplexer mux(Cout1,Cout2,S1,S2,sel,S[7:4],Cout);
    
endmodule