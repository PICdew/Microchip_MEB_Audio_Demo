/*****************************************************************************
 * Microchip MultiMedia board graphics Demo Application
 * This program shows how to use the Graphics Primitives Layer.
 *****************************************************************************
 * FileName:        GraphicsDemo.h
 * Processor:       PIC32
 * Compiler:       	MPLAB C32
 * Linker:          MPLAB LINK32
 * Company:         Microchip Technology Incorporated
 *****************************************************************************/
#ifndef _GRAPHICSDEMO_H
#define _GRAPHICSDEMO_H

#include "GenericTypeDefs.h"
#include "Graphics\Graphics.h"
#include "TouchScreen.h"

#define RED_POS     0xF800
#define GREEN_POS   0x07E0
#define BLUE_POS    0x001F

void DisplayInit(void);
void CreateGraphics(void);
void DisplayTask(void);
void TickInit(void); 
#endif
