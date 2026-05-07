`timescale 1ns / 1ps  // 시간 단위 설정

module tb_test();

    // 1. 모듈 입력은 reg, 출력은 wire로 선언
    reg        clk;
    reg        rst_n;
    wire [1:0] done_sig;
    wire [2:0] d_out;

    // 2. 테스트할 모듈(DUT: Device Under Test) 인스턴스화
    test uut (
        .clk(clk),
        .rst_n(rst_n),
        .done_sig(done_sig),
        .d_out(d_out)
    );

    // 3. 클락 생성 (10ns 주기로 클락 반전 -> 100MHz)
    always #5 clk = ~clk;

    // 4. 테스트 시나리오
    initial begin
        // 초기값 설정
        clk = 0;
        rst_n = 0; // 리셋 활성화

        // 20ns 후에 리셋 해제
        #20;
        rst_n = 1;

        // 결과 관찰을 위해 충분한 시간(100ns) 동안 대기
        // d_out이 001 -> 010 -> 100 -> 001 순으로 변하는지 확인
        #100;

        // 시뮬레이션 종료
        $display("Simulation Finished!");
        $finish;
    end

    // 5. 파형 모니터링 (콘솔 출력용)
    initial begin
        $monitor("At time %t: rst_n = %b, d_out = %b, done_sig = %b", 
                 $time, rst_n, d_out, done_sig);
    end

endmodule