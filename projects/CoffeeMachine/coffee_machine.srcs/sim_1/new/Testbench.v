`timescale 1ns / 1ps

module Testbench;

    reg fifty, hundred, coffee_request, coin_return_request, clk, reset;
    wire bypass, coffee_out, coin_return;

    coffee_machine cm(.fifty(fifty), .hundred(hundred), .coffee_request(coffee_request),
                     .coin_return_request(coin_return_request), .clk(clk),
                     .reset(reset), .bypass(bypass), .coffee_out(coffee_out), .coin_return(coin_return));

    // 클록 생성
    initial begin
        clk = 0;
        forever #5 clk = ~clk;
    end

    // 입력 패턴
    initial begin
        reset = 1; #10;
        reset = 0;
        fifty = 0; hundred = 0; coffee_request = 0; coin_return_request = 0; #5;
        fifty = 1; #10; fifty = 0; #10;
        hundred = 1; #10; hundred = 0; #10;
        coffee_request = 1; #10; coffee_request = 0; #10;
        hundred = 1; #10; hundred = 0; #10;
        coin_return_request = 1; #10; coin_return_request = 0; #10;
        hundred = 1; #10; hundred = 0; #10;
    end

endmodule
