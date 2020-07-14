# Parallel Digital READ/WRITE
 This Repository consists of functions to read and write data to multiple pins with high speed on Teensy4.0 with the help of port manipulation.
 It uses only breadboard friendly pins(0-23) and has been optimised to consume less time as much as possible.
 The pins are optimised to take less memory and execution and should not be changed.
(*changing pins requires lot of changes in the code.)

There are 5 options for number of bits.
->8 BIT
->10 BIT
->12 BIT
->16 BIT
->24 BIT

There are four operations for each option.
->set_xbit
->read_xbit
->write_xbit
->safe_write_xbit
*where x can be 8,10,12,16 or 24.

8 BIT pinmap:
PINS	PORT	 INT_BIT DATA_BIT
19	    GPIO_6	    16	    0
18	    GPIO_6	    17	    1
14	    GPIO_6	    18	    2
15	    GPIO_6	    19	    3
			
17	    GPIO_6	    22	    4
16	    GPIO_6	    23	    5
22	    GPIO_6	    24	    6
23	    GPIO_6	    25	    7

10 BIT pinmap: 
PINS	PORT	 INT_BIT  DATA_BIT
19	    GPIO_6	    16	    0
18	    GPIO_6	    17	    1
14  	GPIO_6	    18	    2
15	    GPIO_6	    19	    3
			
17	    GPIO_6	    22  	4
16	    GPIO_6	    23	    5
22	    GPIO_6	    24	    6
23	    GPIO_6	    25	    7
20	    GPIO_6	    26	    8
21	    GPIO_6	    27	    9

12 BIT pinmap:
PINS	PORT	 INT_BIT  DATA_BIT
19	    GPIO_6	    16	    0
18	    GPIO_6  	17	    1
14  	GPIO_6	    18	    2
15	    GPIO_6	    19	    3
			
17	    GPIO_6  	22	    4
16	    GPIO_6  	23	    5
22	    GPIO_6  	24	    6
23  	GPIO_6	    25	    7
20  	GPIO_6	    26	    8
21	    GPIO_6	    27	    9
			
1	    GPIO_6  	2	    10
0	    GPIO_6	    3	    11

16 BIT pinmap:
PINS	PORT	 INT_BIT	DATA_BIT
10	    GPIO_7	    0	        0
12	    GPIO_7	    1	        1
11	    GPIO_7	    2	        2
13	    GPIO_7	    3	        3
			
17	    GPIO_6	    22	        4
16	    GPIO_6	    23	        5
22	    GPIO_6	    24      	6
23	    GPIO_6	    25	        7
20	    GPIO_6	    26	        8
21	    GPIO_6	    27	        9
			
1	    GPIO_6	    2	        10
0	    GPIO_6	    3	        11
			
19  	GPIO_6	    16	        12
18	    GPIO_6	    17	        13
14	    GPIO_6	    18	        14
15	    GPIO_6	    19	        15

24 BIT pinmap:
PINS	PORT	 INT_BIT	DATA_BIT
10	    GPIO_7	    0	        0
12	    GPIO_7	    1	        1
11	    GPIO_7	    2	        2
13	    GPIO_7	    3	        3
			
17	    GPIO_6	    22	        4
16  	GPIO_6	    23	        5
22	    GPIO_6	    24	        6
23	    GPIO_6	    25	        7
20	    GPIO_6	    26      	8
21  	GPIO_6	    27	        9
			
1	    GPIO_6	    2	        10
0	    GPIO_6	    3	        11
			
19  	GPIO_6	    16	        12
18  	GPIO_6	    17	        13
14  	GPIO_6  	18	        14
15  	GPIO_6	    19	        15
			
2	    GPIO_9	    4	        16
3	    GPIO_9	    5	        17
4	    GPIO_9	    6	        18
			
5	    GPIO_9	    8	        19
			
6	    GPIO_7	    10	        20
9	    GPIO_7	    11	        21
			
8	    GPIO_7	    16	        22
7	    GPIO_7	    17	        23


Setting pins in the code:
set_xbit(mode);
x is no of bits and can be 8,10,12,16,24.
mode can be INPUT, INPUT_PULLUP, INPUT_PULLDOWN, OUTPUT....
this functions sets the pin as input/output it uses the usual pinMode() function with a for loop to set the pins.

Reading data :
read_xbit();
it returns the value of the data read on the pins as an unsigned integer of suitable size. Assign its value to a variable in the code.

No_of_bits       type_of_return_value        No_of_ports      Speed
   8                    uint8_t                   1            14ns
   10                   uint16_t                  1            14ns
   12                   uint16_t                  1            14ns
   16                   uint16_t                  2           26~27ns
   24                   uint32_t                  3            40ns
you can see that no of ports affects the speed so using less no of ports is recommonded. 
*16-bit and and 24-bit can be reduced to 14ns and 27ns by using pins on the backside of the board(24,25,26,27 to be specific).


Writing data:
write_xbit(data);
x is no of bits and can be 8,10,12,16,24.
data is the parameter to be written on the data line.
This mode is faster compared to safe_write() but this method might affect other pins on the port if not managed properly.

No_of_bits       parameter_type        No_of_ports      Speed         pins_might_get_affected
    8               uint8_t                 1            3ns           0,1,20,21,24,25,26,27
    10              uint16_t                1            3ns           0,1,24,25,26,27
    12              uint16_t                1            3ns           24,25,26,27
    16              uint16_t                2           6~7ns          24,25,26,27,6,7,8,9,32
    24              uint32_t                3            10ns          24,25,26,27,29,32,33
Again no_of_ports affects the speed. Speed of 16-bit and 24-bit speed can be improved to 3ns and 7ns by using pins on the backside of the board(24,25,26,27 to be specific).

safe_write_xbit(data);
This method is same as write but it doesn't affect other pins. 
But it does it at the cost of the speed. 
No_of_bits     Speed
    8           23ns
    10          23ns
    12          23ns
    16          43ns
    24          70ns
Once again Speed of 16-bit and 24-bit speed can be improved to 23ns and 43ns by using pins on the backside of the board(24,25,26,27 to be specific).