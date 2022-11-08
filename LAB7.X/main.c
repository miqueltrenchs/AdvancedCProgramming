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
|  DATE:          November 27 2018
|  DESCRIPTION:   Illustrates the use of arrays of pointers
|                    
|  REQUIREMENTS:  MPLABX 5.10
|                 XC32 v2.10
| 
|  REVISION HISTORY:
|
|  rev1      Denny Hopp
|            11/27/2018
|            - code working
|  rev2      Denny Hopp
|            1/21/19
|            - comment changes
|  rev3      Denny Hopp
|            1/29/19
|            - project saved with proper watches selected
|
|MPLABX v5.20rc5
|xc32 v2.15
|  rev4      Denny Hopp
|            5/2/19
|            - builds with new MPLABX version
|MPLABX v5.20
|xc32 v2.15
|  rev5      Denny Hopp
|            5/17/19
|            - builds with new MPLABX version 
|MPLABX v5.35
|XC32 v2.30
|  rev6      Denny Hopp
|            4/16/2020
|            - new MPLABX and compiler versions
|MPLABX v5.45
|XC32 v2.50
|DFP 1.3.321
|  rev7      Denny Hopp
|            5/18/2021
|            - new MPLABX and compiler versions
|
********************************************************************************/

//Create an array of pointers and initialize 4 different strings.  These strings are programmed
// into flash during programming because the 'const' keyword is used to make the pointers point
// to flash memory.  Also, create some generic variables used for the loops.
const char *p[4] = {"ALARM", "FAULT", "SENSOR", "UNLOCK"};
const char **pp = &p[0];
unsigned char y;


//Function prototype
void string_access(const char **message_pointer);


int main(int argc, char** argv) 
{
    
//Step through the following code and watch the 'y' variable.  This code will separately access each
// string in the array.  This code will pass the pointer address to the strings to the function.  It will 
// increment the double pointer to point to the next string.  This method demonstrates how to pass the 
// pointer to the function.    
   while(1)
   {
//Access "ALARM"       
       pp = &p[0];
       string_access(&*pp);

//Access "FAULT"
       pp++;
       string_access(&*pp);

//Access "SENSOR"       
       pp++;
       string_access(&*pp);

//Access "UNLOCK"       
       pp++;
       string_access(&*pp);

      while(1);
   }
}


//This function receives the address of the array pointer to the text strings.  The
// double pointer allows us to pass the address of pointers to functions.  The function
// will access each character in the string until the NULL character is reached.
void string_access(const char **message_pointer)
{
    unsigned char i;
    
    i = 0;
    do{
        y = *(*message_pointer + i);
        i++;
    } while(y != '\0');
}
