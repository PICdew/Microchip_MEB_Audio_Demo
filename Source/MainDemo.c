/*********************************************************************
 *
 *  Main Application Entry Point for the Graphics demo
 *
 *********************************************************************
 * FileName:        MainDemo.c
 * Dependencies:    Graphics.h
 * Processor:       PIC32
 * Compiler:        Microchip C32 v1.05 or higher
 *
 ********************************************************************/
// Include functions specific to this stack application
#include "MainDemo.h"
#include "GraphicsLayout.h"
#include "Audio.h"
#include "WM8731Drv.h"

#pragma config FPLLODIV = DIV_1, FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FWDTEN = OFF, FPBDIV = DIV_1, POSCMOD = XT, FNOSC = PRIPLL, CP = OFF

WM8731_CODEC * pCodecHandle = NULL; 
	
// Private helper functions.
// These may or may not be present in all applications.
static void InitializeBoard(void);

// Main application entry Point
int main(void){
    // Initialize application specific hardware
    InitializeBoard();
	
    //Create the graphics objects
    CreateGraphics();
	
    //All the Application tasks will be called in this infinite loop.
    while(1){
        DisplayTask();
	AudioTask();
    }
	
    return 1;
}

/****************************************************************************
  Function:
    static void InitializeBoard(void)

  Description:
    This routine initializes the hardware using definitions
    in HardwareProfile.h 
  ***************************************************************************/
static void InitializeBoard(void){

    // Enable multi-vectored interrupts
    INTEnableSystemMultiVectoredInt();
	
    // Enable optimal performance
    SYSTEMConfigPerformance(GetSystemClock());
    
    TurnLEDAllOff();
    SetLEDDirection();

    DelayMs(100);
    TurnLEDOn(LED_2);
    DelayMs(100);
    TurnLEDOn(LED_3);
    DelayMs(100);
    TurnLEDOn(LED_4);
    DelayMs(100);
    TurnLEDOn(LED_10);
    DelayMs(100);
    TurnLEDOn(LED_5);
    DelayMs(100);

    TurnLEDAllOff();
       
    CPLDInitialize();
    CPLDSetGraphicsConfiguration(GRAPHICS_HW_CONFIG);
    CPLDSetSPIFlashConfiguration(SPI_FLASH_CHANNEL);

    DisplayInit();          //Display Initialize
	
    AudioPlayInit();        // Audio codec initialize
}


