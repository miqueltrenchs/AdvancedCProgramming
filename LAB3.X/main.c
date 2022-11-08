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
|  DESCRIPTION:   Illustrates the use of arrays of structure pointers
|                    
|  REQUIREMENTS:  MPLABX 5.10
|                 XC32 v2.10
| 
|  REVISION HISTORY:
| rev1       Denny Hopp
|            9/5/2018
|            - Original lab - code working
| rev2       Denny Hopp
|            9/7/18
|            - comment cleanup
| rev3       Denny Hopp
|            9/27/18
|            - added a function that uses the pointer as the structure location to change
| rev4       Denny Hopp
|            11/9/18
|            - added a loop to access all instances of the structure
| rev5       Denny Hopp
|            11/21/18
|            - comment changes
| rev6       Denny Hopp
|            1/4/19
|            - added single pointer that is incremented
| rev7       Denny Hopp
|            1/21/19
|            - comment cleanup
| rev8       Denny Hopp
|            1/29/19
|            - project saved with proper watches selected
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
|DFP 1.3.231
| rev12     Denny Hopp
|           4/30/2020
|           - new MPLABX and compiler versions
|           - new function added to receive the address of the array of pointers
|
********************************************************************************/

//Create a structure Typedef

typedef struct{
    unsigned char u8alarmTimeSeconds;
    unsigned char u8alarmTimeMinutes;
    unsigned char u8alarmTimeHours;
}STRUCT_ALARM_Type;


//Create array of pointers to point to 5 instances of STRUCT_ALARM_Type.  Also create 5 instances of the structure.
STRUCT_ALARM_Type STRUCT_alarmDescriptor[5];
STRUCT_ALARM_Type *p_STRUCT_alarmDescriptor[5] = {&STRUCT_alarmDescriptor[0], &STRUCT_alarmDescriptor[1], 
                    &STRUCT_alarmDescriptor[2], &STRUCT_alarmDescriptor[3], &STRUCT_alarmDescriptor[4]};

//Create a single pointer to show how a single pointer can also be used for access
STRUCT_ALARM_Type *p_STRUCT_singlePointer = &STRUCT_alarmDescriptor[0];


//Function prototype for passing single pointer
void load_alarm_data_using_pointer(STRUCT_ALARM_Type *p_structure, unsigned char seconds, 
                                    unsigned char minutes, unsigned char hours);

//Function prototype for passing array of pointers
void load_alarm_data_using_pointer_array(STRUCT_ALARM_Type *p_structure[ ], unsigned char seconds, 
                                    unsigned char minutes, unsigned char hours);


int main(int argc, char** argv) 
{
   unsigned char i;
      
   
   for(i = 0; i < 5; i++)
   {    
       
//Load values directly with the pointer       
       p_STRUCT_alarmDescriptor[i]->u8alarmTimeMinutes = 1;
       p_STRUCT_alarmDescriptor[i]->u8alarmTimeSeconds = 2;
       p_STRUCT_alarmDescriptor[i]->u8alarmTimeHours = 3;
 
      
//Pass the address to change the actual alarmDescriptor location      
       load_alarm_data_using_pointer(&STRUCT_alarmDescriptor[i], 4, 5, 6);
     
//Pass the address using the pointer      
       load_alarm_data_using_pointer(p_STRUCT_alarmDescriptor[i], 7, 8, 9);
          
//Set the structure values using a single pointer
       load_alarm_data_using_pointer(p_STRUCT_singlePointer, 0xA, 0xB, 0xC);
          
//Increment the single pointer
       p_STRUCT_singlePointer++;
   }
      
//Pass array of pointers to the function
   load_alarm_data_using_pointer_array(&p_STRUCT_alarmDescriptor[0], 77, 88, 99);
      
   
   while(1);
}


//Receive one pointer and act on that location
void load_alarm_data_using_pointer(STRUCT_ALARM_Type *p_structure, unsigned char seconds, 
                                    unsigned char minutes, unsigned char hours)
{
   p_structure->u8alarmTimeSeconds = seconds;
   p_structure->u8alarmTimeMinutes = minutes;
   p_structure->u8alarmTimeHours = hours;
}


//Receive the array of pointers address and load all five instances of the array
void load_alarm_data_using_pointer_array(STRUCT_ALARM_Type *p_structure[ ], unsigned char seconds, 
                                    unsigned char minutes, unsigned char hours)
{
   unsigned char j;
    
   for(j = 0; j < 5; j++)  
   {
       p_structure[j]->u8alarmTimeSeconds = seconds; 
       p_structure[j]->u8alarmTimeMinutes = minutes;
       p_structure[j]->u8alarmTimeHours = hours;        
   }
}

