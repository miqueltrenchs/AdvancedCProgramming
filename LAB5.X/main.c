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
|  DESCRIPTION:   Illustrates the use of function pointers in state machines
|                    
|  REQUIREMENTS:  MPLABX 5.10
|                 XC32 v2.10
| 
|  REVISION HISTORY:
| rev1       Denny Hopp
|            11/21/18
|            - original code modified for the Advanced C class
| rev2       Denny Hopp
|            11/21/18
|            - comment changes
| rev3       Denny Hopp
|            1/21/19
|            - comment changes
| rev4       Denny Hopp
|            1/29/19
|            - project saved with proper watches selected
| rev5       Denny Hopp
|            - RunStateMachine( ) simplified
|
|MPLABX v5.20rc5
|xc32 v2.15
| rev6       Denny Hopp
|            5/2/19
|            - builds with new MPLABX version
|MPLABX v5.20
|xc32 v2.15
| rev7       Denny Hopp
|            5/17/19
|            - builds with new MPLABX version 
|MPLABX v5.35
|XC32 v2.30
| rev8     Denny Hopp
|           4/16/2020
|           - new MPLABX and compiler versions
|MPLABX v5.45
|XC32 v2.50
|DFP 1.3.231
| rev9     Denny Hopp
|           5/5/2021
|           - new MPLABX and compiler versions
|
********************************************************************************/

//brief An enumeration of all System States for plain-language reference in source code.  
typedef enum
{
    STATE0 = 0,
    STATE1,
    STATE2
} SYSTEM_STATE;

SYSTEM_STATE gSystemState;


//These functions are called indirectly through a function pointer.  They are passed a
// value by the RunStateMachine function and return either the InputBits value that is
// passed to it or a literal value.  Each function also increments the state machine.
unsigned int function1(unsigned int InputBits, SYSTEM_STATE *State)
{
   (*State)++;

   if(InputBits == 0 && *State > 1)
      return InputBits;
   else
      return 99;
}


unsigned int function2(unsigned int InputBits, SYSTEM_STATE *State)
{
   (*State)++;

   if(InputBits == 2 && *State > 1)
      return InputBits * InputBits;
   else
      return 88;
}


unsigned int function3(unsigned int InputBits, SYSTEM_STATE *State)
{
   (*State)++;

   if(InputBits == 0 && *State > 1)
      return InputBits * InputBits * InputBits;
   else
      return 77;
}




/* Array of function pointers to functions of form 
 * 'unsigned (int fName[ ])(unsigned int, *SYSTEM_STATE)'.
 * All functions implementing state logic must have a definition of this form. */
unsigned int ( * pStateFunction[] ) ( unsigned int InputBits, SYSTEM_STATE *State ) =
{
    function1,
    function2,
    function3
};


//Function that is called to run the state machine.  It is called by the main( ) program 
// and it calls the proper function based on the State variable.
unsigned int RunStateMachine( unsigned int InputBits )
{
    return (*pStateFunction[ gSystemState ])( InputBits, &gSystemState );
}




void main(void)
{
   volatile unsigned int result1;
   volatile unsigned int result2;
   volatile unsigned int result3;

   
   while(1)
   {
       gSystemState = STATE0;
       result1 = RunStateMachine( 1 );

//gSystemState should be incremented by function
       result2 = RunStateMachine( 2 );

//gSystemState should be incremented by function
       result3 = RunStateMachine( 3 );
   }
}











