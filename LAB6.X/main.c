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
|  DATE:          24 OCT 2018
|  DESCRIPTION:   Illustrates the use of function pointers implemented for
|                    code portability
|  REQUIREMENTS:  
| 
|  REVISION HISTORY:
|  rev1        Denny Hopp
|              10/24/18
|  rev2        Denny Hopp
|              11/21/18
|              - comments added 
|              - code cleanup
|  rev3        Denny Hopp
|              1/21/19
|              - comment cleanup
|  rev4        Denny Hopp
|              1/29/19
|              - project saved with proper watches selected
|  rev5        Denny Hopp
|              - int's changed to short's to get 16-bit values
|
|MPLABX v5.20rc5
|xc32 v2.15
|  rev6        Denny Hopp
|              5/2/19
|              - builds with new MPLABX version
|MPLABX v5.20
|xc32 v2.15
|  rev7      Denny Hopp
|            5/17/19
|            - builds with new MPLABX version 
|MPLABX v5.35
|XC32 v2.30
| rev8       Denny Hopp
|            4/16/2020
|            - new MPLABX and compiler versions
|MPLABX v5.45
|XC32 v2.50
|DFP v1.3.231
| rev9       Denny Hopp
|            5/6/2021
|            - new MPLABX and compiler versions
|
********************************************************************************/

//Variable declarations
unsigned short u16buffer1[16];
unsigned short u16buffer2[16];
unsigned short u16dataBufferRead;


//Two 16-bit buffers will be accessed.  The names are BUFFER1 and BUFFER2.  There
// are three functions for each buffer.  The _Initialize function will load 16
// values into the buffer.  All values are the same and are defined by u16bufferFill.
// The second function will read one location of the buffer.  The third function will 
// write one location of the buffer.

//Write 16 integer values to BUFFER1 as defined by u16bufferFill
void BUFFER1_Initialize(unsigned short u16bufferFill)
{
   unsigned char i;
   
   for(i = 0; i <= 15; i++)
   {
      u16buffer1[i] = u16bufferFill;
   }   
} 


//Read one 16-bit value from BUFFER1 at the address specified by u8index
unsigned short BUFFER1_Read(unsigned char u8index)
{
   return u16buffer1[u8index];
}   


//Write one 16-bit value to BUFFER1 at the address specified by u8index
void BUFFER1_Write(unsigned char u8index, unsigned short u16value)
{
   u16buffer1[u8index] = u16value;
}   


//Write 16 integer values to BUFFER2 as defined by u16bufferFill
void BUFFER2_Initialize(unsigned short u16bufferFill)
{
   unsigned char i;
   
   for(i = 0; i <= 15; i++)
   {
      u16buffer2[i] = u16bufferFill;
   }   
} 


//Read one 16-bit value from BUFFER2 at the address specified by u8index
unsigned short BUFFER2_Read(unsigned char u8index)
{
   return u16buffer2[u8index];
}   


//Write one 16-bit value to BUFFER2 at the address specified by u8index
void BUFFER2_Write(unsigned char u8index, unsigned short u16value)
{
   u16buffer2[u8index] = u16value;
}   



//Enumeration for two different buffers.  This enumeration will be used to select 
// which buffer to access
enum { BUFFER1, BUFFER2} buffer_configurations_t;


//Create three function pointers within a typedef structure.  These three function pointers
// will initialize, read, and write the two buffers.  The *DataInit pointer performs
// the buffer initialization.  The *DataWrite pointer writes to the buffer.  The *DataRead
// pointer reads the buffer.
typedef struct { 
   void (*DataInit)(unsigned short bufferFill); 
   void (*DataWrite)(unsigned char index, unsigned short value); 
   unsigned short (*DataRead)(unsigned char index);
} buffer_functions_t;


//The buffer_access[ ] array contains the addresses for both of the buffer
// initialize, read and write functions.  This array is placed in flash but could
// be placed in RAM instead.  

// Line 1 accesses BUFFER1 and line 2 accesses BUFFER2.
// Each line has the addresses for each function (initialize, read, write).

//The BUFFER1_Initialize address corresponds to the *DataInit function pointer.
//The BUFFER1_WRITE address corresponds to the *DataWrite function pointer.
//The BUFFER1_READ address corresponds to the *DataRead function pointer.
const buffer_functions_t buffer_access[] = {   
    {BUFFER1_Initialize, BUFFER1_Write, BUFFER1_Read },
    {BUFFER2_Initialize, BUFFER2_Write, BUFFER2_Read }
};



//Main function
int main(void)
{
//Initialize both buffers    
   buffer_access[BUFFER1].DataInit(0x55);
   buffer_access[BUFFER2].DataInit(0xAA);

    while(1)
    {
//Access the functions for each buffer using the buffer_access[ ] array        
       buffer_access[BUFFER1].DataWrite(4, 0x1234);
       u16dataBufferRead = buffer_access[BUFFER1].DataRead(4);
       
       buffer_access[BUFFER2].DataWrite(8, 0x9876);
       u16dataBufferRead = buffer_access[BUFFER2].DataRead(8);
       
       while(1);

    }
}



