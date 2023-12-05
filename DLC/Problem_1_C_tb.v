module D_flip_flop_tb;
    reg D, CLK, ClrN, PreN;
    wire Q, Q_bar;

    D_flip_flop dut (
        .D(D),
        .CLK(CLK),
        .ClrN(ClrN),
        .PreN(PreN),
        .Q(Q),
        .Q_bar(Q_bar)
    );

    initial begin
        D = 1'b0;
        CLK = 1'b0;
        ClrN = 1'b1;
        PreN = 1'b1;

        ClrN = 1'b0;
        #5;
        $display("Test Case 1 - ClrN Low - Q=%b, Q_bar=%b", Q, Q_bar);

        ClrN = 1'b1;
        PreN = 1'b0;
        #5;
        $display("Test Case 2 - PreN Low - Q=%b, Q_bar=%b", Q, Q_bar);

        ClrN = 1'b1;
        PreN = 1'b1;
        D = 1'b1;
        #5;
        $display("Test Case 3 - D=1 - Q=%b, Q_bar=%b", Q, Q_bar);
        
        $finish;
    end
endmodule