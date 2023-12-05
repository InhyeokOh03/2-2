module NAND_gate(
    input wire A,
    input wire B,
    output reg Y
);
    always @* begin
        if (A == 1) begin
            if (B == 1) begin
                Y = 0;
            end else begin
                Y = 1;
            end
        end else begin
            Y = 1;
        end
    end
endmodule

module inverter(
    input wire A,
    output reg Y
);

    always @* begin
        if (A == 1)
            Y = 0;
        else
            Y = 1;
    end
endmodule

module flash_ADC_decoder(
    input [3:0] COMP,
    output [1:0] B
);
    // Inverter
    inverter comp2_inv(COMP[2], ncomp2);
    inverter comp1_inv(COMP[1], ncomp1);
    inverter comp0_inv(COMP[0], ncomp0);
    
    // B0
    NAND_gate nand_B0_1(COMP[3], ncomp2, B0_nand1);
    NAND_gate nand_B0_2(COMP[1], ncomp0, B0_nand2);
    NAND_gate nand_B0_final(B0_nand1, B0_nand2, B[0]);

    // B1
    NAND_gate nand_B1_1(COMP[3], ncomp2, B1_nand1);
    NAND_gate nand_B1_2(COMP[2], ncomp1, B1_nand2);
    NAND_gate nand_B1_final(B1_nand1, B1_nand2, B[1]);
endmodule