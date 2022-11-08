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
|  DESCRIPTION:   Illustrates the use of arrays of function pointers
|                    in state machines
|                    
|  REQUIREMENTS:  MPLABX 5.10
|                 XC32 v2.10
| 
|  REVISION HISTORY:
| rev1       Denny Hopp
|            9/4/2018
|            - Original lab - code working
| rev2       Denny Hopp
|            11/20/2018
|            - Comment additions
| rev3       Denny Hopp
|            11/21/2018
|            - Comment additions
| rev4       Denny Hopp
|            1/21/19
|            - Comment changes
| rev5       Denny Hopp
|            1/29/19
|            - project saved with proper watches selected
| rev6       Denny Hopp
|            4/23/19
|            - prototype for function pointer placed in flash added (it can be
|               uncommented and the existing function pointer commented out)
| rev7       Denny Hopp
|            4/24/19
|            - cleared functionState at end of while( ) loop
| rev8       Denny Hopp
|            4/30/19
|            - added function pointers in program memory
|
|MPLABX v5.20rc5
|xc32 v2.15
| rev9       Denny Hopp
|            5/2/19
|            - builds with new MPLABX version
|MPLABX v5.20
|xc32 v2.15
| rev10      Denny Hopp
|            5/17/19
|            - builds with new MPLABX version 
|MPLABX v5.35
|XC32 v2.30
| rev11     Denny Hopp
|           4/16/2020
|           - new MPLABX and compiler versions
|
|MPLABX v5.45
|XC32 v2.50
|DFP v1.3.231
| rev12     Denny Hopp
|           5/3/21
|           - new MPLABX, DFP and compiler versions
|
********************************************************************************/

//Variable declarations
unsigned char functionState = 0;
unsigned int functionResult = 0;


//Function prototypes
int function1(int x);
int function2(int y);
int function3(int z);


//Function Pointer Declarations and Initialization
// An array of function pointers is declared and the array will contain three
// addresses for function1, function2, and function3.  The array is initialized
// with the addresses of these functions.  This array will point to functions that
// are passed one int parameter and return one int parameter.
int (*funPtr[3])(int a) = { &function1, &function2, &function3 };


//Place function pointers in program memory
int (* const funPtrFlash[3])(int a) = { &function1, &function2, &function3 };

//*******************************************************************************
//Could place the function pointers in flash if desired.  Uncomment this declaration and comment 
// out the existing declaration for funPtr[ ]
//int (*funPtr[3])(int a) __attribute__((space(prog))) = { &function1, &function2, &function3};
//*******************************************************************************


//Main routine
int main(void)
{
//The functionState variable is incremented after each indirect function call so that
// the succeeding function is called next.  In each function call, a value of 2 is passed
// to the function
    while(1)
    {
//Calls function1        
        functionState = 0;
        functionResult = funPtr[functionState](2);

//Calls function 2
        functionState++;
        functionResult = funPtr[functionState](2);

//Calls function 3
        functionState++;
        functionResult = funPtr[functionState](2);
        
        functionState = 0;
        
        
//Now use function pointers in program memory

//Calls function1        
        functionState = 0;
        functionResult = funPtrFlash[functionState](2);

//Calls function 2
        functionState++;
        functionResult = funPtrFlash[functionState](2);

//Calls function 3
        functionState++;
        functionResult = funPtrFlash[functionState](2);
        
        functionState = 0;        
    }
}


//Returns the value passed to the function
int function1(int x)
{
    return x;
}

//Returns the square of the value passed to the function
int function2(int y)
{
    return y * y;
}

//Returns the cube of the value passed to the function
int function3(int z)
{
    return z * z * z;
}




