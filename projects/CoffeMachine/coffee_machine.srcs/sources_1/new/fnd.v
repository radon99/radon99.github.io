`timescale 1ns / 1ps
module fnd_controller(
    input [15:0] value,   // 4�ڸ� ���� �Է� (ex. ���� �ݾ�: 0000~9999)
    input clk,            // 100MHz Ŭ��
    output reg [6:0] seg, // 7���׸�Ʈ ���÷��� ������
    output reg [3:0] an   // 4���� 7���׸�Ʈ ���÷��� ����
    );

    reg [1:0] digit_select;
    reg [3:0] digit;
    reg [19:0] clk_div;

    // Ŭ�� ���ֱ�: 100MHz -> �� 1kHz�� ���÷��� ��ȯ
    always @(posedge clk) begin
        clk_div <= clk_div + 1;
    end

    // 4���� ���÷��� �ֱ������� ����
    always @(posedge clk_div[18]) begin
        digit_select <= digit_select + 1;
    end

    // ���õ� ���÷��̿� �´� ���� ����
    always @(*) begin
        case (digit_select)
            2'b00: digit = value[3:0];    // ù ��° �ڸ� (���� �ڸ�)
            2'b01: digit = value[7:4];    // �� ��° �ڸ� (���� �ڸ�)
            2'b10: digit = value[11:8];   // �� ��° �ڸ� (���� �ڸ�)
            2'b11: digit = value[15:12];  // �� ��° �ڸ� (õ�� �ڸ�)
            default: digit = 4'b0000;
        endcase
    end

    // ���õ� ���÷��̿� �´� ���׸�Ʈ ���
    always @(*) begin
        case (digit)
            4'd0: seg = 7'b1000000;  // ���� 0
            4'd1: seg = 7'b1111001;  // ���� 1
            4'd2: seg = 7'b0100100;  // ���� 2
            4'd3: seg = 7'b0110000;  // ���� 3
            4'd4: seg = 7'b0011001;  // ���� 4
            4'd5: seg = 7'b0010010;  // ���� 5
            4'd6: seg = 7'b0000010;  // ���� 6
            4'd7: seg = 7'b1111000;  // ���� 7
            4'd8: seg = 7'b0000000;  // ���� 8
            4'd9: seg = 7'b0010000;  // ���� 9
            default: seg = 7'b1111111;  // ��� ���׸�Ʈ ����
        endcase
    end

    // ���÷��� ���� ���� (anode ��ȣ)
    always @(*) begin
        case (digit_select)
            2'b00: an = 4'b1110;  // ù ��° ���÷��� ����
            2'b01: an = 4'b1101;  // �� ��° ���÷��� ����
            2'b10: an = 4'b1011;  // �� ��° ���÷��� ����
            2'b11: an = 4'b0111;  // �� ��° ���÷��� ����
            default: an = 4'b1111;
        endcase
    end

endmodule
