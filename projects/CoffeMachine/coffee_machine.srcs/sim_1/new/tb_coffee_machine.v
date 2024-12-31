`timescale 1ns / 1ps
module tb_coffee_machine();
    parameter
        EMPTY = 2'b00,
        FIFTY = 2'b01,
        HUND = 2'b10,
        FIFTY_HUND = 2'b11;

    reg clk, rst;
    reg sw0, sw1, btnL, btnR;
    wire [2:0] led;

    coffee_machine coffee_machine0 (clk, rst, sw0, sw1, btnL, btnR, led[2], led[1], led[0]);

    always #5 clk = ~clk;

    initial begin
        clk = 1'b0;
        rst = 1'b1; #1
        rst = 1'b0; #1
        rst = 1'b1;

        {sw0, sw1, btnL, btnR} = 4'b1000; #20 // 5ns, 15ns fifty
        {sw0, sw1, btnL, btnR} = 4'b0100; #10 // 25ns hundred
        {sw0, sw1, btnL, btnR} = 4'b0010; #10 // 35ns coffee request
        {sw0, sw1, btnL, btnR} = 4'b0100; #10 // 45ns hundred
        {sw0, sw1, btnL, btnR} = 4'b0001; #10 // 55ns coin return request
        {sw0, sw1, btnL, btnR} = 4'b0100; #10 // 65ns hundred
        $finish;
    end
endmodule