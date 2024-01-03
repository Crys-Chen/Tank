`timescale 1 ns / 1 ps
`define N 8

module test;
    wire  [`N-1:0]S;//数据累加和本位
    wire  Cout;//输出进位
    reg   [`N-1:0]A,B;//需要相加的数
    reg   [`N-1:0]goldSum;
    reg   [`N:0]goldSum2;
    reg   goldCo;
    reg   Cin;//输入进位
    reg   clk;


    // carry_lookahead_adder_4bits adder(Cout,S,A,B,Cin);
    CLA8 adder(Cout,S,A,B,Cin);

    integer cnt,errors;

    initial begin
        A = 0'd0;
        B = 0'd0;
        Cin = 0'd0;
        errors = 0;
        cnt = 0;
    end


    initial begin
        clk = 0;
        #100 forever #60 clk = ~clk;
    end


    always @(posedge Cin) begin
        A = A + 1;
        cnt = cnt + 1;
        if(cnt % 256 == 0) begin
            B = B + 1;
        end
    end

    always@(*) begin
        goldSum = A + B + Cin;
        goldSum2 = A + B + Cin;
        goldCo = goldSum2[`N];
    end

    always @ (posedge clk)
    begin
        Cin = ~Cin;
            // check result at negedge
        $display("A=%d, B=%d, Cin=%d, S=%d, Cout=%d",A,B,Cin,S,Cout);
        if ( S !== goldSum || Cout !== goldCo) begin
            $display(" ------ERROR. A mismatch has occurred-----");
            errors = errors + 1;
        end

        if (errors == 0)
            $display("Simulation finished Successfully.");
        else if (errors > 1)
            $display("%0d ERROR! See log above for details.",errors);
        else
            $display("ERROR! See log above for details."); 
    end

endmodule