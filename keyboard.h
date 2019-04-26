 /****************************************************************************
 Company: Dinamica y desarrollo
 Designed by: Juan Sebastián Rincón Manrique 
 Date: 29/09/2017
 Description: With this file several Macros got created to allow a
              versatil usage of the matrix keypad
              
 Dependencies: DataType.h

 *****************************************************************************
 *
 *                C1    C2    C3   C4
 *
 *       _____________________________________
 *      /                                     \
 *     |   __________________________________  |
 *     |  |                                 |  |
 *     |  |                                 |  |
 *     |  |      ___   ___   ___   ___      |  |
 *     |  |     |   | |   | |   | |   |     |  |
 *   F1|  |     | 1 | | 2 | | 3 | | A |     |  |
 *     |  |     |___| |___| |___| |___|     |  |
 *     |  |      ___   ___   ___   ___      |  |
 *     |  |     |   | |   | |   | |   |     |  |
 *   F2|  |     | 4 | | 5 | | 6 | | B |     |  |
 *     |  |     |___| |___| |___| |___|     |  |
 *     |  |      ___   ___   ___   ___      |  |
 *     |  |     |   | |   | |   | |   |     |  |
 *   F3|  |     | 7 | | 8 | | 9 | | C |     |  |
 *     |  |     |___| |___| |___| |___|     |  |
 *     |  |      ___   ___   ___   ___      |  |
 *     |  |     |   | |   | |   | |   |     |  |
 *   F4|  |     | * | | 0 | | # | | D |     |  |
 *     |  |     |___| |___| |___| |___|     |  |
 *     |  |                                 |  |
 *     |  |                                 |  |
 *     |  |_________________________________|  |
 *     |            _______________            |
 *     |           | | | | | | | | |           |
 *     |           |*|*|*|*|*|*|*|*|           |
 *     |           |_|_|_|_|_|_|_|_|           |
 *      \_________/_________________\_________/
 *              /                     \
 *             |  |  |  |  |  |  |  |  |    
 *             |C1|C2|C3|C4|R1|R2|R3|R4|
 *             |__|__|__|__|__|__|__|__|
 * 

 ***********************************************/

#include "DataType.h"
#include "Extevents.h"
#include <iostm8s003f3.h>
#include <intrinsics.h>
   
/***********************************************
KEYBOARD Settings
***********************************************/
   
//CONTROL
#define ROW1D              PC_ODR_ODR4
#define ROW2D              PC_ODR_ODR5
#define ROW3D              PC_ODR_ODR6
#define ROW4D              PC_ODR_ODR7

#define COL1D              PB_ODR_ODR5 //REQUIRES EXTRA PULL UP
#define COL2D              PB_ODR_ODR4 //REQUIRES EXTRA PULL UP
#define COL3D              PC_ODR_ODR3
#define COL4D              PD_ODR_ODR1

//DATA
#define ROW1DI             PC_IDR_IDR4
#define ROW2DI             PC_IDR_IDR5
#define ROW3DI             PC_IDR_IDR6
#define ROW4DI             PC_IDR_IDR7

#define COL1DI             PB_IDR_IDR5 //REQUIRES EXTRA PULL UP
#define COL2DI             PB_IDR_IDR4 //REQUIRES EXTRA PULL UP
#define COL3DI             PC_IDR_IDR3
#define COL4DI             PD_IDR_IDR1

//DATA DIRECTION
#define ROW1DD            PC_DDR_DDR4
#define ROW2DD            PC_DDR_DDR5
#define ROW3DD            PC_DDR_DDR6
#define ROW4DD            PC_DDR_DDR7

#define COL1DD            PB_DDR_DDR5 //REQUIRES EXTRA PULL UP
#define COL2DD            PB_DDR_DDR4 //REQUIRES EXTRA PULL UP
#define COL3DD            PC_DDR_DDR3
#define COL4DD            PD_DDR_DDR1

//CONTROL REGISTERS 1 (Pull up mode)
#define ROW1PE            PC_CR1_C14
#define ROW2PE            PC_CR1_C15
#define ROW3PE            PC_CR1_C16
#define ROW4PE            PC_CR1_C17

#define COL1PE            PB_CR1_C15 //REQUIRES EXTRA PULL UP
#define COL2PE            PB_CR1_C14 //REQUIRES EXTRA PULL UP
#define COL3PE            PC_CR1_C13
#define COL4PE            PD_CR1_C11
 
//CONTROL REGISTERS 2 (Interrupts) JUST INTERRUPTS FOR ROWS
#define ROW1IE            PC_CR2_C24
#define ROW2IE            PC_CR2_C25
#define ROW3IE            PC_CR2_C26
#define ROW4IE            PC_CR2_C27
 
//KEYBOARD SENSITIVITY (Falling edge)
#define ROWSKBEDGC        EXTI_CR1_PCIS

#define COLOUT()           COL1DD=1; COL2DD=1; COL3DD=1; COL4DD=1
#define COLCERO()          COL1D=0; COL1D=0; COL1D=0; COL1D=0
#define COLIN()            COL1DD=0; COL2DD=0; COL3DD=0; COL4DD=0
#define COLPE()            COL1PE=1; COL2PE=1; COL3PE=1; COL4PE=1

#define ROWOUT()           ROW1DD=1; ROW2DD=1; ROW3DD=1; ROW4DD=1
#define ROWCERO()          ROW1D=0 ; ROW1D=0 ; ROW1D=0 ; ROW1D=0
#define ROWIN()            ROW1DD=0; ROW2DD=0; ROW3DD=0; ROW4DD=0
#define ROWPE()            ROW1PE=1; ROW2PE=1; ROW3PE=1; ROW4PE=1
#define ROWKBEN()          ROW1IE=1; ROW2IE=1; ROW3IE=1; ROW4IE=1
#define ROWKBDIS()         ROW1IE=0; ROW2IE=0; ROW3IE=0; ROW4IE=0
#define ROWKBEDG()         ROWSKBEDGC=0x2

/**************************************************
* Function headers and Flag
**************************************************/

void Keyboard_Init(void);

uint8_t keydecoder(void);




