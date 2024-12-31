`timescale 1ns / 1ps
module fnd_controller(
    input [15:0] value,   // 4자리 숫자 입력 (ex. 현재 금액: 0000~9999)
    input clk,            // 100MHz 클락
    output reg [6:0] seg, // 7세그먼트 디스플레이 데이터
    output reg [3:0] an   // 4개의 7세그먼트 디스플레이 선택
    );

    reg [1:0] digit_select;
    reg [3:0] digit;
    reg [19:0] clk_div;

    // 클락 분주기: 100MHz -> 약 1kHz로 디스플레이 전환
    always @(posedge clk) begin
        clk_div <= clk_div + 1;
    end

    // 4개의 디스플레이 주기적으로 선택
    always @(posedge clk_div[18]) begin
        digit_select <= digit_select + 1;
    end

    // 선택된 디스플레이에 맞는 숫자 추출
    always @(*) begin
        case (digit_select)
            2'b00: digit = value[3:0];    // 첫 번째 자리 (일의 자리)
            2'b01: digit = value[7:4];    // 두 번째 자리 (십의 자리)
            2'b10: digit = value[11:8];   // 세 번째 자리 (백의 자리)
            2'b11: digit = value[15:12];  // 네 번째 자리 (천의 자리)
            default: digit = 4'b0000;
        endcase
    end

    // 선택된 디스플레이에 맞는 세그먼트 출력
    always @(*) begin
        case (digit)
            4'd0: seg = 7'b1000000;  // 숫자 0
            4'd1: seg = 7'b1111001;  // 숫자 1
            4'd2: seg = 7'b0100100;  // 숫자 2
            4'd3: seg = 7'b0110000;  // 숫자 3
            4'd4: seg = 7'b0011001;  // 숫자 4
            4'd5: seg = 7'b0010010;  // 숫자 5
            4'd6: seg = 7'b0000010;  // 숫자 6
            4'd7: seg = 7'b1111000;  // 숫자 7
            4'd8: seg = 7'b0000000;  // 숫자 8
            4'd9: seg = 7'b0010000;  // 숫자 9
            default: seg = 7'b1111111;  // 모든 세그먼트 꺼짐
        endcase
    end

    // 디스플레이 선택 제어 (anode 신호)
    always @(*) begin
        case (digit_select)
            2'b00: an = 4'b1110;  // 첫 번째 디스플레이 선택
            2'b01: an = 4'b1101;  // 두 번째 디스플레이 선택
            2'b10: an = 4'b1011;  // 세 번째 디스플레이 선택
            2'b11: an = 4'b0111;  // 네 번째 디스플레이 선택
            default: an = 4'b1111;
        endcase
    end

endmodule
