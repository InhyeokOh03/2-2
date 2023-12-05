module D_flip_flop(
    input D, input CLK, input ClrN, input PreN,
    output reg Q, output reg Q_bar
);
    always @(posedge CLK or negedge ClrN or negedge PreN) begin
        if (~ClrN) begin
            Q <= 1'b0;
            Q_bar <= 1'b1;
        end else if (~PreN) begin
            Q <= 1'b1;
            Q_bar <= 1'b0;
        end else begin
            Q <= D;
            Q_bar <= ~D;
        end
    end
endmodule