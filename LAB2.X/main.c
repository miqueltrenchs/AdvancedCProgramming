/*****************************************************************************************

DISCLAIMER OF LIABILITY REGARDING CODE AND SERVICES

Upon your request and for your convenience Microchip Technology Incorporated
("Microchip") has modified your code.  Your acceptance and/or use of this
modified code constitutes agreement to the terms and conditions of this notice.

CODE ACCOMPANYING THIS MESSAGE AND RELATED SERVICES ARE SUPPLIED BY MICROCHIP "AS IS".
NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
TO, IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A
PARTICULAR PURPOSE APPLY TO THIS CODE, ITS INTERACTION WITH MICROCHIP?S PRODUCTS,
COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

YOU ACKNOWLEDGE AND AGREE THAT, IN NO EVENT, SHALL MICROCHIP BE
LIABLE, WHETHER IN CONTRACT, WARRANTY, TORT (INCLUDING NEGLIGENCE OR BREACH OF
STATUTORY DUTY), STRICT LIABILITY, INDEMNITY, CONTRIBUTION, OR OTHERWISE, FOR ANY
INDIRECT, SPECIAL, PUNITIVE, EXEMPLARY, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE,
FOR COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE CODE, HOWSOEVER CAUSED,
EVEN IF MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.
TO THE FULLEST EXTENT ALLOWABLE BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS
IN ANY WAY RELATED TO THIS CODE, SHALL NOT EXCEED THE PRICE YOU PAID DIRECTLY TO
MICROCHIP SPECIFICALLY TO HAVE THIS CODE DEVELOPED.

You agree that you are solely responsible for testing the code and determining its
suitability.  Microchip has no obligation to modify, test, certify, or support the code.
******************************************************************************************/

/********************************************************************************
|  
|  AUTHOR:        Denny Hopp
|  DATE:          September 4 2018
|  DESCRIPTION:   Illustrates the use of arrays of pointers
|                    
|  REQUIREMENTS:  MPLABX 5.10
|                 XC32 v2.10
| 
|  REVISION HISTORY:
| rev1       Denny Hopp
|            9/4/2018
|            - Original lab - code working
| rev2       Denny Hopp
|            11/6/18
|            - comments added
|            - while(1) loop added after last string is accessed
| rev3       Denny Hopp
|            11/21/18
|            - comment changes
| rev4       Denny Hopp
|            1/21/19
|            - comment cleanup
| rev5       Denny Hopp
|            1/29/19
|            - project saved with proper watches selected
| rev6       Denny Hopp
|            4/23/19
|            - arrays added to show placement of pointers in data and program
|               memories
| rev7       Denny Hopp
|            4/30/19
|            - used 'const' to place p[ ] in program memory
|
|MPLABX v5.20rc5
|xc32 v2.15
| rev8       Denny Hopp
|            5/2/19
|            - builds with new MPLABX version
|MPLABX v5.20
|xc32 v2.15
| rev9       Denny Hopp
|            5/17/19
|            - builds with new MPLABX version 
|
|MPLABX v5.35
|XC32 v2.30
| rev10     Denny Hopp
|           4/16/2020
|           - new MPLABX and compiler versions
|
|MPLABX v5.45
|XC32 v2.50
|DFP 1.3.231
| rev11     Denny Hopp
|           4/27/2021
|           - new MPLABX and compiler versions
|
| rev12     Denny Hopp
|           4/27/21
|           - array q has const keyword added to point to flash
|           - comment changes
********************************************************************************/

//Generic loop variables are declared
unsigned char i = 0, j = 0, y;

//Create an array of pointers and initialize 4 different strings.  These strings are programmed
// into flash during programming. The pointer is also placed in program memory. 
char *const p[4] = {"a01", "b02", "c03", "d04"};

//Create an array of pointers that reside in data memory
const char *q[4] = {"e01", "f02", "g03", "h04"};

//Let the linker place the variables and strings in flash (same as using const pointer)
const char *r[4] __attribute__((space(prog))) = {"i01", "j02", "k03", "l04"};



int main(int argc, char** argv) 
{
    
//Step through the following code and watch the 'y' variable.  This code will step through each of the strings.
// When a NULL character is found, the next string is pointed to.  The 'y' variable will contain the character
// being pointed to. 
    
//The first pass through the loop, the pointer points to the "a01" string.  When a NULL character is found, the 
// pointer is incremented and points to the "b02" string.  It will follow the same format for the third and fourth 
// strings.  When the loop counter is equal to 4, the next loop using the q[ ] array of pointers is accessed.  Finally, 
// the r[ ] array of pointers is accessed after the q[ ] pointer loop has executed four times.    
   while(1)
   {
//Step through p[ ] pointer       
      for(i = 0; i < 4; i++, j=0)
      {
         do{
             y = *(p[i] + j);
             j++;
         } while(y != '\0');
      }

//Step through q[ ] pointer      
      for(i = 0; i < 4; i++, j=0)
      {
         do{
             y = *(q[i] + j);
             j++;
         } while(y != '\0');
      }

//Step through r[ ]pointer      
      for(i = 0; i < 4; i++, j=0)
      {
         do{
             y = *(r[i] + j);
             j++;
         } while(y != '\0');
      }

      
      while(1);
   }
}
