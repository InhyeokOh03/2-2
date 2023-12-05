module serial_adder_tb;

    reg CLK;
    reg reset_n;
    reg [3:0] x;
    reg [3:0] y;
    wire [4:0] sum;

    serial_adder dut (
        .CLK(CLK),
        .reset_n(reset_n),
        .x(x),
        .y(y),
        .sum(sum)
    );

    initial begin
        CLK = 0;
        reset_n = 0;
        x = 4'b0000;
        y = 4'b0000;
        
        #10;

        reset_n = 1;

        // Case 1
        x = 4'b1010;
        y = 4'b0111;
        #20;

        // Case 2
        x = 4'b1111;
        y = 4'b1111;
        #20;

        $finish;
    end
endmodule
