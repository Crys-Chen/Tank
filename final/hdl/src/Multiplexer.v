module Multiplexer (
    input   Cout1,Cout2,
    input   [3:0] S1,S2,
    input   sel,
    
    output  [3:0] S,
    output  Cout
    );

    assign  Cout = sel ? Cout2 : Cout1 ;
    assign  S    = sel ? S2 : S1;
    
endmodule