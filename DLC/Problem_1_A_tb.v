module moduleName_tb;
    reg A, B, C;
    wire [0:3] F;
    wire [0:4] S;

    moduleName dut (
        .A(A),
        .B(B),
        .C(C),
        .F(F)
    );

    initial begin
        // Case 000
        A = 0; B = 0; C = 0;
        #10;
        $display("Case 000 - F[0:3] = %b", F);

        // Case 001
        A = 0; B = 0; C = 1;
        #10;
        $display("Case 001 - F[0:3] = %b", F);

        // Case 010
        A = 0; B = 1; C = 0;
        #10;
        $display("Case 010 - F[0:3] = %b", F);

        // Case 011
        A = 0; B = 1; C = 1;
        #10;
        $display("Case 011 - F[0:3] = %b", F);

        // Case 100
        A = 1; B = 0; C = 0;
        #10;
        $display("Case 100 - F[0:3] = %b", F);

        // Case 101
        A = 1; B = 0; C = 1;
        #10;
        $display("Case 101 - F[0:3] = %b", F);

        // Case 110
        A = 1; B = 1; C = 0;
        #10;
        $display("Case 110 - F[0:3] = %b", F);

        // Case 111
        A = 1; B = 1; C = 1;
        #10;
        $display("Case 111 - F[0:3] = %b", F);

    $finish;
end
endmodule