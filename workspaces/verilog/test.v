module test (
    input            clk,
    input            rst_n,
    output reg [1:0] done_sig,
    output reg [2:0] d_out
);

    // 내부 신호 선언
    reg [2:0] a;
    reg [2:0] b;

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            // 리셋 시 초기 상태
            a <= 3'b111;      // AND 연산에서 상대 비트를 그대로 통과시키기 위해 111로 설정
            b <= 3'b001;      // 시작 값
            d_out <= 3'b000;
            done_sig <= 2'b00;
        end else begin
            // 1. AND 연산 수행: (111 & 001) -> (111 & 010) -> (111 & 100)
            d_out <= a & b;
            
            // 2. b를 시프트하여 다음 연산 준비
            if (b == 3'b100) begin
                b <= 3'b001;  // 100 다음엔 다시 001로 돌아감
            end else begin
                b <= b << 1;  // 왼쪽으로 한 칸 시프트
            end

            // 3. 완료 신호 표시
            done_sig <= 2'b01;
        end
    end

endmodule