`timescale 1ns/1ps
module feeding_timer_tb;
  reg clk;
  reg reset;
  wire feed_out;
  // Instantiate the DUT
  feeding_timer uut (
    .clk(clk),
    .reset(reset),
    .feed_out(feed_out)
  );
  // Clock generation
  initial begin
    clk = 0;
    forever #5 clk = ~clk;   // 10ns period (100 MHz)
  end
  // Stimulus
  initial begin
    reset = 1;
    #10;
    reset = 0;
    // Run simulation for some cycles
    #200;
    $finish;
  end
  // Monitor signals
  initial begin
    $monitor("Time=%0t | Reset=%b | Feed_out=%b", $time, reset, feed_out);
  end
endmodule
