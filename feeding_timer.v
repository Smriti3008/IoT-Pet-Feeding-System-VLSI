module feeding_timer(
    input clk,
    input reset,
    output reg feed_out
);
    // State encoding
    localparam IDLE = 2'b00;
    localparam FEED = 2'b01;
    localparam WAIT = 2'b10;
    reg [1:0] current_state, next_state;
    reg [3:0] counter;
    // State transition
    always @(posedge clk or posedge reset) begin
        if (reset) begin
            current_state <= IDLE;
            counter <= 0;
        end else begin
            current_state <= next_state;
            if (current_state == WAIT)
                counter <= counter + 1;
            else
                counter <= 0;
        end
    end
    // Next state logic
    always @(*) begin
        next_state = current_state;
        feed_out = 0;
        case (current_state)
            IDLE: begin
                next_state = FEED;
            end
            FEED: begin
                feed_out = 1;       // Activate feeder
                next_state = WAIT;
            end
            WAIT: begin
                if (counter >= 6)   // Delay cycles before feeding again
                    next_state = IDLE;
                else
                    next_state = WAIT;
            end
        endcase
    end
endmodule
