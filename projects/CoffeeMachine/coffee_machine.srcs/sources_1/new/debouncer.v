`timescale 1ns / 1ps
module debouncer (
    input clk,       // FPGA 클락 (100MHz)
    input btn_in,    // 버튼 입력 신호
    output reg btn_out // 디바운싱된 출력 신호
    );

    reg [19:0] cnt;
    reg btn_sync_0, btn_sync_1;

    // 버튼 입력 신호 동기화 (메타 안정성 해결)
    always @(posedge clk) begin
        btn_sync_0 <= btn_in;
        btn_sync_1 <= btn_sync_0;
    end

    // 디바운싱 카운터
    always @(posedge clk) begin
        if (btn_sync_1 == btn_out) begin
            cnt <= 0;
        end else begin
            cnt <= cnt + 1;
            if (cnt == 20'd1000000) begin
                btn_out <= btn_sync_1;
            end
        end
    end
endmodule
