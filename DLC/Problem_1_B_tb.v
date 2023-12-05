module four_bit_parallel_adder_tb;
    reg [3:0] A, B;
    reg Cin;
    wire [3:0] S;
    wire Cout;

    four_bit_parallel_adder dut (
        .A(A),
        .B(B),
        .Cin(Cin),
        .S(S),
        .Cout(Cout)
    );

    initial begin
        // Case 1: A=3, B=5, Cin=0
        A = 4'b0011;
        B = 4'b0101;
        Cin = 1'b0;
        #10;
        $display("Case 1 - A=%b, B=%b, Cin=%b, S=%b, Cout=%b", A, B, Cin, S, Cout);

        // Case 2: A=7, B=8, Cin=1
        A = 4'b0111;
        B = 4'b1000;
        Cin = 1'b1;
        #10;
        $display("Case 2 - A=%b, B=%b, Cin=%b, S=%b, Cout=%b", A, B, Cin, S, Cout);

        // Case 3: A=15, B=1, Cin=0
        A = 4'b1111;
        B = 4'b0001;
        Cin = 1'b0;
        #10;
        $display("Case 3 - A=%b, B=%b, Cin=%b, S=%b, Cout=%b", A, B, Cin, S, Cout);

        // Case 4: A=0, B=0, Cin=1
        A = 4'b0000;
        B = 4'b0000;
        Cin = 1'b1;
        #10;
        $display("Case 4 - A=%b, B=%b, Cin=%b, S=%b, Cout=%b", A, B, Cin, S, Cout);

        $finish;
    end
endmodule