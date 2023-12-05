module flash_ADC_decoder_tb;

    reg [3:0] COMP;
    wire [1:0] B;

    flash_ADC_decoder dut (
        .COMP(COMP),
        .B(B)
    );

    initial begin

        COMP = 4'b0000;
        #10;
        $display("Case 1 - COMP = %b, B = %b", COMP, B);

        COMP = 4'b0001;
        #10;
        $display("Case 2 - COMP = %b, B = %b", COMP, B);

        COMP = 4'b0010;
        #10;
        $display("Case 3 - COMP = %b, B = %b", COMP, B);

        COMP = 4'b0011;
        #10;
        $display("Case 4 - COMP = %b, B = %b", COMP, B);

        COMP = 4'b0100;
        #10;
        $display("Case 5 - COMP = %b, B = %b", COMP, B);

        COMP = 4'b0101;
        #10;
        $display("Case 6 - COMP = %b, B = %b", COMP, B);

        COMP = 4'b0110;
        #10;
        $display("Case 7 - COMP = %b, B = %b", COMP, B);

        COMP = 4'b0111;
        #10;
        $display("Case 8 - COMP = %b, B = %b", COMP, B);

        COMP = 4'b1000;
        #10;
        $display("Case 9 - COMP = %b, B = %b", COMP, B);

        COMP = 4'b1001;
        #10;
        $display("Case 10 - COMP = %b, B = %b", COMP, B);

        COMP = 4'b1010;
        #10;
        $display("Case 11 - COMP = %b, B = %b", COMP, B);
        
        COMP = 4'b1011;
        #10;
        $display("Case 12 - COMP = %b, B = %b", COMP, B);

        COMP = 4'b1100;
        #10;
        $display("Case 13 - COMP = %b, B = %b", COMP, B);

        COMP = 4'b1101;
        #10;
        $display("Case 14 - COMP = %b, B = %b", COMP, B);

        COMP = 4'b1110;
        #10;
        $display("Case 15 - COMP = %b, B = %b", COMP, B);

        COMP = 4'b1111;

        #10;
        $display("Case 16 - COMP = %b, B = %b", COMP, B);

        $finish;
    end
endmodule
