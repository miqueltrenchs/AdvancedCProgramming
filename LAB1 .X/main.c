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
|  DESCRIPTION:   Illustrates the use of nested structures
|                    
|  REQUIREMENTS:  MPLABX 5.45
|                 XC32 v2.10
| 
|  REVISION HISTORY:
|  rev1      Denny Hopp
|            9/4/2018
|            - Original lab - code working
|  rev2      Denny Hopp
|            11/1/2018
|            - Comment additions
|            - All unions variables are accessed in the main( ) function
|  rev3      Denny Hopp
|            11/21/18
|            - comment changes
|  rev4      Denny Hopp
|            - 1/21/19
|            - comment cleanup
|  rev5      Denny Hopp
|            1/29/19
|            - project saved with proper watches selected
|  rev6      Denny Hopp
|            4/10/19
|            - int's changed to short's
|  rev7      Denny Hopp
|            4/24/19
|            - while(1); added at end of main while( ) loop
|
|MPLABX v5.20rc5
|xc32 v2.15
|  rev8      Denny Hopp
|            5/2/19
|            - builds with new MPLABX version
|MPLABX v5.20
|xc32 v2.15
|  rev9      Denny Hopp
|            5/17/19
|            - builds with new MPLABX version 
|MPLABX v5.35
|XC32 v2.30
| rev10     Denny Hopp
|           4/16/2020
|           - new MPLABX and compiler versions
|
|MPLABX v5.45
|XC32 v2.50
| rev11     Denny Hopp
|           4/23/2021
|           - new MPLABX and compiler versions
|
********************************************************************************/

//No device header files are included since there are no references to specific device 
// registers. 

//Here are three individual unions that specify LED functionality.  These unions will
// be incorporated into one structure so that access can be made to all three using
// a pointer
typedef union {
   unsigned long reg;
   struct {
      unsigned char u8rotateForwardSpeed;
      unsigned char u8rotateReverseSpeed;
      unsigned char u8speedRateChange;
      unsigned char b1rotateStatusFlags:    2;
   } member;
}LED_ROTATE_Type;

typedef union {
   unsigned long reg;
   struct {
      unsigned short u16pwmLightIntensity;
      unsigned char u8breatheSpeed;
      unsigned char b1breatheFlags:         2;
   } member;
}LED_BREATHE_Type;

typedef union {
   unsigned long reg;
   struct {
      unsigned char u8pattern[4];
   } member;
}LED_PATTERN_Type;

//Create a structure that incorporates all three individual structures
typedef struct {
    volatile LED_ROTATE_Type 	  ledRotation; 
    volatile LED_PATTERN_Type     ledPattern; 
    volatile LED_BREATHE_Type 	  ledBreathe; 
} STRUCT_LEDVariables;


//Create the instance of all unions and structures by creating the instance 
// of the inclusive structure STRUCT_LEDVariables.
STRUCT_LEDVariables STRUCT_allLEDVariables;

//Create a pointer to the STRUCT_allLEDVariables instance
STRUCT_LEDVariables *pSTRUCT_LEDVariables = &STRUCT_allLEDVariables;




/******************************************************************************************
 FUNCTION:  int main(void)
 
 DESCRIPTION:  This function simply steps through code that will load the union and
 structure members with indirect accesses using the pointer
 
 *****************************************************************************************/
int main(int argc, char** argv) 
{
//The while( ) loop continually loads values into each union member to 
// demonstrate indirect access using the pointer.  Operation is easy to evaluate
// when breakpoints are placed before each instruction and the instruction results
// are viewed in the Watch window after each step.    
   while(1)
   {
       pSTRUCT_LEDVariables->ledRotation.reg = 0xABCDECFF;
       pSTRUCT_LEDVariables->ledRotation.member.u8rotateForwardSpeed = 0x11;
       pSTRUCT_LEDVariables->ledRotation.member.u8rotateReverseSpeed = 0x22;
       pSTRUCT_LEDVariables->ledRotation.member.u8speedRateChange = 0x55;
       pSTRUCT_LEDVariables->ledRotation.member.b1rotateStatusFlags = 1;
       
       pSTRUCT_LEDVariables->ledPattern.reg = 0x11111111;
       pSTRUCT_LEDVariables->ledPattern.member.u8pattern[0] = 0xAA;
       pSTRUCT_LEDVariables->ledPattern.member.u8pattern[1] = 0xBB;
       pSTRUCT_LEDVariables->ledPattern.member.u8pattern[2] = 0xCC;
       pSTRUCT_LEDVariables->ledPattern.member.u8pattern[3] = 0xDD;
       
       pSTRUCT_LEDVariables->ledBreathe.reg = 0x12345678;
       pSTRUCT_LEDVariables->ledBreathe.member.u8breatheSpeed = 0x33;
       pSTRUCT_LEDVariables->ledBreathe.member.u16pwmLightIntensity = 0xFEDC;
       pSTRUCT_LEDVariables->ledBreathe.member.b1breatheFlags = 0b11;
       
       while(1);
   }
}
