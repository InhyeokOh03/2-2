module moduleName (A, B, C, F);
    input A, B, C;
    output [0:3] F;
    wire [0:4] S;
    
    assign S[0] = (~A) & (~B);
    assign S[1] = A & (~C);
    assign S[2] = B;
    assign S[3] = B & (~C);
    assign S[4] = A & C;

    assign F[0] = S[0] | S[1];
    assign F[1] = S[1] | S[2];
    assign F[2] = S[0] | S[3];
    assign F[3] = S[2] | S[4];
endmodule