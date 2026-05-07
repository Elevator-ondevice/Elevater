`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/06/2026 05:24:27 PM
// Design Name: 
// Module Name: test
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module test(

    input clk,
    input rst_n,
    
    input done_sig,

    input wire a [2:0],
    input wire b [2:0], 

    output reg d_out [3:0]
    );
    wire count [1:0];
    
    assign a = 4'b0000;
    assign b = 4'b0001;
    
    
    
    always@(posedge clk or negedge rst_n) begin
        d_out <= a | b;
        b = b << 1;
        count 
    end
    
    
    
    
endmodule
