/* 
 * CS:APP Data Lab 
 * 
 * <Ahmet Uyar>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */

#endif
/* Copyright (C) 1991-2012 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* We do support the IEC 559 math functionality, real and complex.  */
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */
/*
 * isZero - returns 1 if x == 0, and 0 otherwise 
 *   Examples: isZero(5) = 0, isZero(0) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int isZero(int x)
{
   /* If a number is different than 0, then we can use the unary ! operation to determine whether it's not zero. */
   return !x;
}
/* 
 * implication - return x -> y in propositional logic - 0 for false, 1
 * for true
 *   Example: implication(1,1) = 1
 *            implication(1,0) = 0
 *   Legal ops: ! ~ ^ |
 *   Max ops: 5
 *   Rating: 2
 */
int implication(int x, int y)
{
   /*Using (x -> y) in propositional logic can also be expressed as not x or y. */
   return (!x) | y;
}
/* 
 * twoDigitNumberInBaseFour - return integer equivalent of (xy)_4 two digit number in base 4
 *   Example: twoDigitNumberInBaseFour(2, 3) = 11
 *   Legal ops: >> << +
 *   Max ops: 4
 *   Rating: 2
 */
unsigned twoDigitNumberInBaseFour(unsigned x, unsigned y)
{
   return (x << 2) + y; // multiplies first digit by 4^1, second digit by 4^0.
}
/*
 * multThreeEighths - multiplies by 3/8 rounding toward 0.
 *   Should exactly duplicate effect of C expression (x*3/8),
 *   including overflow behavior.
 *   Examples: multThreeEighths(77) = 28
 *             multThreeEighths(-22) = -8
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int multThreeEighths(int x)
{
   /* This function computes the desired output by first multiplying a number by 3, then right-shifts the integer by 3. Problem occurs with negative number, by two's complement, it's off by one.*/
   int timesThree = x + (x << 1);                                                          // manipulating bitwise shift.
   int xIsNegative = x >> 31;                                                              // determining whether its negative
   int y = (xIsNegative & (~(timesThree) + 1)) | ((~xIsNegative) & timesThree);            // turning to positive
   int timesThreeDivEight = y >> 3;                                                        // dividing it by 8
   return (xIsNegative & (~timesThreeDivEight + 1)) | (~xIsNegative & timesThreeDivEight); // retransform for negatives
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x)
{
   /* Manipulating the facts that x = ~x+1 in two's complement, we can understand whether an integer is nonzero. When we shift, the positive number will result in zero and the negative number will result in -1 (Oxffffffff) */
   return (((x >> 31) | ((~x + 1) >> 31))) + 1; // adding 1 at the end because result is either 0 for 0, -1 for others.
}
/* 
 * TMax - return maximum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmax(void)
{
   /* Exploiting bit shift, we can generate the max two's complement 32 bit integer. */
   int a = 1;
   a <<= 31;  // 0's will be added from right because of the property of left shift.
   return ~a; // forming its one's complement, we obtain the integer.
}
/* 
 * isOppositeSigns - if x and y has different signs then return 1, else return 0 
 *   Example: isOppositeSigns(4,-5) = 1.
 *            isOppositeSigns(3,2) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int isOppositeSigns(int x, int y)
{

   int signX = x >> 31;   // results in either 0xffffffff or 0
   int signY = y >> 31;   // results in either 0xffffffff or 0
   int a = signX ^ signY; // result in 0xffffffff if signs are different, 0 otherwise.
   return a & 0x1;        // return 0 or 1
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z)
{
   /*Forming if-else. one of the sides should be 0 depending on the condition*/

   int a = !x;                                              // results in 1 if zero, 0 if nonzero.
   return (((!a << 31) >> 31 & y)) | ((a << 31) >> 31 & z); // left side if nonzero, right side if zero. 
}
/* 
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf)
{
   /* The function first handles the NaN and infinity cases. Then, using bit manipulation we can find the signed bit, hence the sign of the number.
 * If the number is negative according to its bit sequence(having a leading 1), it is enough to flip the sign bit so that we obtain the positive representation. */

   unsigned oneToNineBits = uf >> 23; // obtaining bits that express the exponential.
   unsigned firstBit = uf >> 31;      // results in either 0xffffffff or 0.
   unsigned fractions = uf << 9;      // obtaining fractions

   if ((!((oneToNineBits & 0xff) ^ 0xff) && fractions))
   { // both infinity
      return uf;
   }

   if (firstBit)
   { // negative

      uf = uf & ~(1 << 31); // flipping the first bit of argument.
      return uf;
   }
   else
   { // non-negative
      return uf;
   }
}
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf)
{
   int exponent = ((uf >> 23) & 0xff) - 127;        // exponents. declared as int as it may be negative.
   unsigned firstBit = uf >> 31;                    // 0xffffffff if negative 0 if positive.
   unsigned result = 0;
   return result; // couldn't finish the problem. 
}
