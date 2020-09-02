// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

  //set i to 1
  @I
  M=1

  // set sum to 0
  @SUM
  M=0

  // check which number is larger
  @R0
  D=M
  @R1
  D=D-M

  // goto loop that adds r0 using r1 as 'n'
  @MULT_R0
  D;JGT
  @MULT_R1

  // loop that adds r1 using r0 as 'n'
(MULT_R1)
  @I
  D=M
  @R0
  D=D-M // compare i and r0
  @SET_R2
  D;JGT // set r2 if i > r0
  @R1
  D=M
  @SUM
  M=M+D
  @I
  M=M+1
  @MULT_R1
  0;JMP

(MULT_R0)
  @I
  D=M
  @R1
  D=D-M // compare i and r0
  @SET_R2
  D;JGT // set r2 if i > r0
  @R0
  D=M
  @SUM
  M=M+D
  @I
  M=M+1
  @MULT_R0
  0;JMP

(SET_R2)
  @SUM
  D=M
  @R2
  M=D

(END)
  @END
  0;JMP