`timescale 1ns / 1ps
module debouncer (
    input clk,       // FPGA Ŭ�� (100MHz)
    input btn_in,    // ��ư �Է� ��ȣ
    output reg btn_out // ��ٿ�̵� ��� ��ȣ
    );

    reg [19:0] cnt;
    reg btn_sync_0, btn_sync_1;

    // ��ư �Է� ��ȣ ����ȭ (��Ÿ ������ �ذ�)
    always @(posedge clk) begin
        btn_sync_0 <= btn_in;
        btn_sync_1 <= btn_sync_0;
    end

    // ��ٿ�� ī����
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
