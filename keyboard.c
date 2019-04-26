 /****************************************************************************
 Company: Dinamica y Desarrollo
 Designed by: Juan Sebastián Rincón Manrique
 Date: 04/10/2017
 Descripcion: This code allows initializatión and management
              of an 4X4 matrix keypad whitch sends the respective ASCII code
              with function keydecoder(), Remember initialize the module using
              Keyboard_Init() and call to keydecoder() once get interrupt 
	      the system will execute a loop for avoiding key bounce.
			  
 Dependencies: keyboard.h

 *****************************************************************************/
//////////////////////////////////////////////////////////////
//Libraries
//////////////////////////////////////////////////////////////

#include "keyboard.h"
   
#include "Extevents.h"

//////////////////////////////////////////////////////////////
//Exclusive ussage function header
//////////////////////////////////////////////////////////////

static void KBWaitLong(uint16_t w);

//////////////////////////////////////////////////////////////
//Matrix key interrupt handler
//////////////////////////////////////////////////////////////

#pragma vector = EXTI2_vector
__interrupt void EXTI_PORTC_IRQHandler(void){
    Exti2flag = 1;
}

///////////////////////////////////////////////////////////////////////
//  Delay that guarantie that the debounce time passed
//  several switcjhes shows a bounce time of 1/6 seconds
//  according to http://www.eng.utah.edu/~cs5780/debouncing.pdf
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// KBWaitLong is a delay that uses about 60000 
// clock cycles, it will depend on the argument of function 
// and will consume 64.6ms for a clockspeed of 2MHZ 
///////////////////////////////////////////////////////////////

static void KBWaitLong(uint16_t w){
    for (unsigned int x = (w*10000);x>0;x--){asm("nop");};   
}

void PINWaitShort(void){ //this delay uses 137 cycles for clock
  for (unsigned int x = 137;x>0;x--){asm("nop");};
}

////////////////////////////////
//Initialize the keyboard
////////////////////////////////

void Keyboard_Init(void){
  COLOUT();       //configure columns as output
  COLCERO();      //put a zero in column
  ROWIN();        //enable rows as input
  ROWPE();        //enable pull up ressistors
  ROWKBEN();      //enable keyboard rows 
  ROWKBEDG();     //detection only falling edge
}

//////////////////////////////////////////////////////////////
// FUNCTION THAT DETECTS THE PRESSED KEY
//////////////////////////////////////////////////////////////

uint8_t keydecoder(void){
  uint8_t keypress='N';
  volatile uint8_t dato=0x00;
  KBWaitLong(2);
    
  dato= ROW1DI| (ROW2DI<<1)| (ROW3DI<<2)|(ROW4DI<<3); //READ DATA FROM ROWS
  
  ROWKBDIS();      //disable rows
  COLIN();         //configurate columns as input
  COLPE();         //pull up for columns are activated
  ROWOUT();        //configurate rows as input
  ROWCERO();       //put a zero in rows
  PINWaitShort();  //waits for stabilization of inner capacitances
  
  dato= dato | (COL1DI<<4)| (COL2DI<<5)| (COL3DI<<6)| (COL4DI<<7); //READ DATA FROM COLUMNS
  
  
  switch (dato){
    
  case 0xEE: 
    keypress='1';
    break;
  case 0xDE:
    keypress='4';
    break;
  case 0xBE:
    keypress='7';
    break;
  case 0x7E:
    keypress='*';
    break;
  case 0xED: 
    keypress='2';
    break;
  case 0xDD:
    keypress='5';
    break;
  case 0xBD:
    keypress='8';
    break;
  case 0x7D:
    keypress='0';
    break;
  case 0xEB: 
    keypress='3';
    break;
  case 0xDB:
    keypress='6';
    break;
  case 0xBB:
    keypress='9';
    break;
  case 0x7B:
    keypress='#';
    break;
  case 0xE7: 
    keypress='A';
    break;
  case 0xD7:
    keypress='B';
    break;
  case 0xB7:
    keypress='C';
    break;
  case 0x77:
    keypress='D';
    break;
  default:
    keypress='N';    //Means that no key where pressed or a quick pulse 
    break;           //or more than one key where pressed
  }
  
  Keyboard_Init();   //reset the keyboard config
  return keypress;
}
