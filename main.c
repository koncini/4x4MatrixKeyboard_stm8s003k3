#include <iostm8s003f3.h>
#include <string.h>
#include "DataType.h"
#include "keyboard.h"

uint8_t u8Tecla[2]={0,0};

int main( void ){
  __disable_interrupt(); 
  Keyboard_Init();
  __enable_interrupt();
  
  while(1){
    if(Exti2flag==1){
      Exti2flag=0;
      u8Tecla[0]=keydecoder();
    }
  }
}
