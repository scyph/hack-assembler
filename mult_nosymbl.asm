// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

  //set i to 1
  @16
  M=1

  // set sum to 0
  @17
  M=0

  // check which number is larger
  @0
  D=M
  @1
  D=D-M

  // goto loop that adds r0 using r1 as 'n'
  @26 
  D;JGT
  @11

  // loop that adds r1 using r0 as 'n'
  @16
  D=M
  @0
  D=D-M // compare i and r0
  @39 
  D;JGT // set r2 if i > r0
  @1	
  D=M
  @17
  M=M+D
  @16
  M=M+1
  @11
  0;JMP

  // loop that adds r0 using r1 as 'n'
  @16
  D=M
  @1
  D=D-M // compare i and r0
  @39	 
  D;JGT // set r2 if i > r0
  @0
  D=M
  @17
  M=M+D
  @16
  M=M+1
  @25
  0;JMP

  // set r2 to answer
  @17
  D=M
  @2
  M=D

  // END
  @43
  0;JMP