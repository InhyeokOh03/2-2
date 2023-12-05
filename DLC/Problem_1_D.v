module D_flip_flop(
    input D, input CLK,
    output reg Q, output reg Q_bar
);
    always @(posedge CLK) begin
        Q <= D;
        Q_bar <= ~D;
    end
endmodule

module serial_adder(
    input wire CLK, 
    input wire reset_n, 
    input wire [3:0] x,
    input wire [3:0] y,
    output reg [4:0] sum
);

    reg [3:0] s;
    reg [4:0] c;

    D_flip_flop d_ff_0(x[0] ^ y[0], CLK, c[1]);
    D_flip_flop d_ff_1(x[1] ^ y[1] ^ c[1], CLK, c[2]);
    D_flip_flop d_ff_2(x[2] ^ y[2] ^ c[2], CLK, c[3]);
    D_flip_flop d_ff_3(x[3] ^ y[3] ^ c[3], CLK, c[4]);

    always @(posedge CLK or negedge reset_n) begin
        if (~reset_n) begin
            s <= 4'b0000;
            c <= 5'b00000;
            sum <= 5'b00000;
        end else begin
            s <= {d_ff_0.Q, d_ff_1.Q, d_ff_2.Q, d_ff_3.Q};
            sum <= {c[4], s};
        end
    end
endmodule
