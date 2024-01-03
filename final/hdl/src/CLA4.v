`define N 4
module CLA4(Cout,S,A,B,Cin);
    output  [`N-1:0]S;//数据累加和本位
    output  Cout;//输出进位
    input   [`N-1:0]A,B;//需要相加的数
    input   Cin;//输入进位
    wire    [`N-1:0]G,P;
    wire	[`N:0]C;//分别对应Gi、Pi和Ci

    assign  C[0] = Cin;//最低进位为输入进位
    assign  P = A | B;// Pi = Ai·Bi
    assign  G = A & B;// Gi = Ai+Bi
    assign  C[1] = G[0] | (P[0]&C[0]);//对应图中 C1
    assign  C[2] = G[1] | (P[1]&G[0]) | (P[1]&P[0]&C[0]);
    assign  C[3] = G[2] | (P[2]&G[1]) | (P[2]&P[1]&G[0]) | (P[2]&P[1]&P[0]&C[0]);
    assign  C[4] = G[3] | (P[3]&G[2]) | (P[3]&P[2]&G[1]) | (P[3]&P[2]&P[1]&G[0]) | (P[3]&P[2]&P[1]&P[0]&C[0]);
    assign  S = G ^ P ^ C[`N-1:0];  
    assign  Cout = C[`N];
endmodule
