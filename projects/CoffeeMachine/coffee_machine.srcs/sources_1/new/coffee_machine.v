`timescale 1ns / 1ps
module coffee_machine(
    input clk,       // 100MHz clock
    input rst,       // Reset button
    input btnU,       // 50원 입력 (Switch 0)
    input btnD,       // 100원 입력 (Switch 1)
    input btnL,      // 커피 요청 버튼 (Left Button)
    input btnR,      // 잔돈 반환 요청 버튼 (Right Button)
    output [2:0] led, // Bypass, Coffee Output, Coin Return (3 LEDs)
    output [6:0] seg, // 7-segment display output (one digit)
    output [3:0] an   // 7-segment display anodes (which display to activate)
    );

    parameter EMPTY = 2'b00,
              FIFTY = 2'b01,
              HUND = 2'b10,
              FIFTY_HUND = 2'b11;

    reg [1:0] curr_state, next_state;
    reg bypass, coff_out, coin_ret;
    reg [15:0] amount;  // 현재 금액
    wire fifty, hundred, cof_out_req, coin_ret_req;

    // 버튼 디바운싱 모듈 인스턴스
    debouncer db_fifty (.clk(clk), .btn_in(btnU), .btn_out(fifty));
    debouncer db_hundred (.clk(clk), .btn_in(btnD), .btn_out(hundred));
    debouncer db_cof_out_req (.clk(clk), .btn_in(btnL), .btn_out(cof_out_req));
    debouncer db_coin_ret_req (.clk(clk), .btn_in(btnR), .btn_out(coin_ret_req));

//     클락 디바이더 (100MHz -> 1Hz로 예시)
    reg [26:0] clk_div;
    wire slow_clk;
    
    always @(posedge clk or posedge rst) begin
        if (rst)
            clk_div <= 0;
        else
            clk_div <= clk_div + 1;
    end
    assign slow_clk = clk_div[26]; // Slow clock for FSM

    // 상태 레지스터
    always @ (posedge slow_clk or posedge rst) begin
        if (rst)
            curr_state <= EMPTY;
        else
            curr_state <= next_state;
    end

always @(*) begin // next state logic
        if (curr_state == EMPTY) begin
            case({fifty, hundred, cof_out_req, coin_ret_req})
                4'b0001: next_state = EMPTY;
                4'b0010: next_state = EMPTY;
                4'b0100: next_state = HUND;
                4'b1000: next_state = FIFTY;
                default: next_state = curr_state;
            endcase
        end
        else if (curr_state == FIFTY) begin
            case({fifty, hundred, cof_out_req, coin_ret_req})
                4'b0001: next_state = EMPTY;
                4'b0010: next_state = FIFTY;
                4'b0100: next_state = FIFTY_HUND;
                4'b1000: next_state = HUND;
                default: next_state = curr_state;
            endcase
        end
        else if (curr_state == HUND) begin
            case({fifty, hundred, cof_out_req, coin_ret_req})
                4'b0001: next_state = EMPTY;
                4'b0010: next_state = EMPTY;
                4'b0100: next_state = HUND;
                4'b1000: next_state = HUND;
                default: next_state = curr_state;
            endcase
        end
        else if (curr_state == FIFTY_HUND) begin
            case({fifty, hundred, cof_out_req, coin_ret_req})
                4'b0001: next_state = EMPTY;
                4'b0010: next_state = FIFTY;
                4'b0100: next_state = FIFTY_HUND;
                4'b1000: next_state = FIFTY_HUND;
                default: next_state = curr_state;
            endcase
        end
        else next_state = curr_state;
    end

    always @(*) begin // output logic
        if (curr_state == EMPTY) begin
            case({fifty, hundred, cof_out_req, coin_ret_req})
                4'b0001:{bypass, coff_out, coin_ret} = 3'b000;
                4'b0010:{bypass, coff_out, coin_ret} = 3'b000;
                4'b0100:{bypass, coff_out, coin_ret} = 3'b000;
                4'b1000:{bypass, coff_out, coin_ret} = 3'b000;
                default: {bypass, coff_out, coin_ret} = 3'b000;
            endcase
        end
        else if (curr_state == FIFTY) begin
            case({fifty, hundred, cof_out_req, coin_ret_req})
                4'b0001:{bypass, coff_out, coin_ret} = 3'b001;
                4'b0010:{bypass, coff_out, coin_ret} = 3'b000;
                4'b0100:{bypass, coff_out, coin_ret} = 3'b000;
                4'b1000:{bypass, coff_out, coin_ret} = 3'b000;
                default: {bypass, coff_out, coin_ret} = 3'b000;
            endcase
        end
        else if(curr_state == HUND) begin
            case({fifty, hundred, cof_out_req, coin_ret_req})
                4'b0001:{bypass, coff_out, coin_ret} = 3'b001;
                4'b0010:{bypass, coff_out, coin_ret} = 3'b010;
                4'b0100:{bypass, coff_out, coin_ret} = 3'b100;
                4'b1000:{bypass, coff_out, coin_ret} = 3'b100;
                default: {bypass, coff_out, coin_ret} = 3'b000;
            endcase
        end
        else if (curr_state == FIFTY_HUND) begin
            case({fifty, hundred, cof_out_req, coin_ret_req})
                4'b0001:{bypass, coff_out, coin_ret} = 3'b001;
                4'b0010:{bypass, coff_out, coin_ret} = 3'b010;
                4'b0100:{bypass, coff_out, coin_ret} = 3'b100;
                4'b1000:{bypass, coff_out, coin_ret} = 3'b100;
                default: {bypass, coff_out, coin_ret} = 3'b000;
            endcase
        end
        else {bypass, coff_out, coin_ret} = 3'b000;
    end

    // 금액 출력
    always @(*) begin
        case (curr_state)
            EMPTY:       amount = 16'h0000;  // 0원
            FIFTY:       amount = 16'h0050;  // 50원
            HUND:        amount = 16'h0100;  // 100원
            FIFTY_HUND:  amount = 16'h0150;  // 150원
            default:     amount = 16'h0000;  // 기본 0원
        endcase
    end

    // FND 모듈 연결
    fnd_controller fnd_inst (
        .value(amount),
        .clk(clk),
        .seg(seg),
        .an(an)
    );

    // LED 출력
    assign led = {bypass, coff_out, coin_ret};

endmodule
