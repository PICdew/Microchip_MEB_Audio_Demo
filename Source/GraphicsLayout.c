/*****************************************************************************
 * Microchip MultiMedia board graphics Demo Application
 * 
 *****************************************************************************
 * FileName:        GraphicsLayout.c
 * Dependencies:    GraphicsLayout.h
 * Processor:       PIC32
 * Compiler:       	MPLAB C32
 * Linker:          MPLAB LINK32
 * Company:         Microchip Technology Incorporated
 *
 *****************************************************************************/
#include "GraphicsLayout.h"
#include "Audio.h"

void ProgressBarAction(void);
void GradientFill(UINT16 left, UINT16 top, UINT16 right, UINT16 bottom, UINT16 start_color, UINT16 stop_color);

#define ID_WINDOW_AUDIO		(1)	
#define ID_PROGRESS_AUDIO	(2)
#define ID_BUTTON_PLAY		(3)
#define ID_BUTTON_STOP		(4)
#define ID_BUTTON_REC           (5)
#define ID_PICTURE_MCHP		(6)
#define ID_STATIC_TEXT		(7)

#define PB_ORIGIN_X ((GetMaxX() - 240 + 1) / 2)
#define PB_ORIGIN_Y ((40 + GetMaxY() - 130 + 1) / 2)

PROGRESSBAR     *pProgressBar;  // pointer to progress bar object for progress bar demo
BUTTON		*pButtonPlay;   //Play button object
BUTTON		*pButtonRec;    //Play button object
BUTTON 		*pButtonStop;   //Stop button object
GOL_SCHEME	*schemeMasters;

extern const FONT_FLASH     GOLFontDefault;                 // default GOL font
extern const FONT_FLASH     GOLMediumFont;                  // medium font
extern const FONT_FLASH     GOLSmallFont;                   // small font

volatile DWORD      tick = 0;                               // tick counter
extern const char   L1185835933[];
const BITMAP_FLASH  mchpIcon0 = {0,L1185835933};

volatile BOOL	PlayPressed = FALSE;
volatile BOOL	RecPressed = FALSE;
volatile int    AudioState = 2;

WORD GOLMsgCallback(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg){
    if(objMsg == BTN_MSG_PRESSED){
        if(GetObjID(pObj) == ID_BUTTON_PLAY){           // Playing...
            TurnLEDOn(LED_3);
            PlayPressed = TRUE;
            AudioState = 1;
     	}else if(GetObjID(pObj) == ID_BUTTON_STOP){     // Stop...
            TurnLEDOff(LED_2);
            TurnLEDOff(LED_3);
            PlayPressed = FALSE;
            AudioState = 2;
	}else if(GetObjID(pObj) == ID_BUTTON_REC){      // Recording...
            RecPressed = TRUE;
            AudioState = 3;
        }
    }		
    return 1;
}

WORD GOLDrawCallback(){
    ProgressBarAction();
    return 1;
}       // Each refresh of screen...

void DisplayInit(void){
    GOLInit();                  // Initialize graphics library and crete default style scheme for GOL
    SST25Init(); 		// initialize GFX3 SST25 flash SPI

    TouchInit();                // Initialize touch screen
    TickInit(); 		// enable the timer that will sample the touch screen
    if(GRAPHICS_LIBRARY_VERSION != SST25ReadWord(ADDRESS_VERSION)){
        TouchCalibration();
        TouchStoreCalibration();
    }
    // Load touch screen calibration parameters from memory
    TouchLoadCalibration();
}

//Create the Graphics objects
void CreateGraphics(void){
    schemeMasters = GOLCreateScheme();
    schemeMasters->Color0 = LIGHTBLUE;
    schemeMasters->Color1 = GRAY0;
    schemeMasters->ColorDisabled = YELLOW;
    schemeMasters->CommonBkColor = WHITE;
    schemeMasters->EmbossDkColor = BLUE;
    schemeMasters->EmbossLtColor = GRAY0;
    schemeMasters->TextColor0 = BLUE;
    schemeMasters->TextColor1 = BLUE;
    schemeMasters->pFont = (void*)&GOLMediumFont;
    
    WndCreate(
        ID_WINDOW_AUDIO,   // ID
        0,
        0,
        GetMaxX(),
        40,          // dimension
        WND_DRAW,           // will be dislayed after creation
        NULL, // icon
        (XCHAR *)" MEB_Audio_Demo",    // set text
        schemeMasters				// default GOL scheme
    );                      

    PictCreate(ID_PICTURE_MCHP,289,7,310,35,PICT_DRAW,1,(void*)&mchpIcon0,schemeMasters);
    
    pProgressBar = PbCreate(
        ID_PROGRESS_AUDIO,        // ID
	PB_ORIGIN_X + 0,
	PB_ORIGIN_Y + 0,
	PB_ORIGIN_X + 240,
	PB_ORIGIN_Y + 40,      // dimension
	PB_DRAW,               // will be dislayed after creation
	0,                     // position
	100,                   // range
	schemeMasters				   // use default scheme
    );
 
    pButtonPlay = BtnCreate(
        ID_BUTTON_PLAY,                   // object’s ID
        PB_ORIGIN_X + 0, 
        130,
        PB_ORIGIN_X + 100,
        170,   // object’s dimension
        0,                   // radius of the rounded edge
        BTN_DRAW,            // draw the object after creation
        NULL,                // no bitmap used
        (XCHAR *)"PLAY",              // use this text
        schemeMasters				 // style scheme
    );               

    pButtonRec = BtnCreate(
        ID_BUTTON_REC,                   // object’s ID
        PB_ORIGIN_X + 0,
        180,
        PB_ORIGIN_X + 100,
        220,                            // object’s dimension
        0,                              // radius of the rounded edge
        BTN_DRAW,                       // draw the object after creation
        NULL,                           // no bitmap used
        (XCHAR *)"RECORD",              // use this text
        schemeMasters				 // style scheme
    );

    pButtonStop = BtnCreate(
        ID_BUTTON_STOP,                 // object’s ID
        PB_ORIGIN_X + 140,
        160, 
        PB_ORIGIN_X + 240, 
        200,                            // object’s dimension
        0,                   // radius of the rounded edge
        BTN_DRAW,            // draw the object after creation
        NULL,                // no bitmap used
        (XCHAR *)"STOP",              // use this text
        schemeMasters				 // style scheme
    );

    GradientFill(0, 40, GetMaxX(), GetMaxY(), YELLOW, BRIGHTRED);
}
	
void DisplayTask(void){	 
    static GOL_MSG msg; // GOL message structure to interact with GOL
	
    // Drawing is done here and process messages
    if(GOLDraw()){// Draw GOL objects
    	TouchGetMsg(&msg);      // Get message from touch screen
        GOLMsg(&msg);           // Process message
    }
}	

// Progressbar action
void ProgressBarAction(void){
    unsigned long currentPos;
    if(PlayPressed == TRUE){
        currentPos = AudioPercent();
	PbSetPos(pProgressBar, currentPos);     // increase...
	SetState(pProgressBar, PB_DRAW_BAR);    // redraw bar only
	if(currentPos == 100)
            PlayPressed = FALSE;
    }
}

void GradientFill(UINT16 left, UINT16 top, UINT16 right, UINT16 bottom, UINT16 start_color, UINT16 stop_color){
    UINT16 red[2], blue[2], green[2];
    UINT16 delta_red, delta_blue, delta_green;
    UINT16 running_red, running_blue, running_green;
    UINT16 grad_red, grad_blue, grad_green;

    red[0] = start_color & RED_POS;
    blue[0] = start_color & BLUE_POS;
    green[0] = start_color & GREEN_POS;

    red[1] = stop_color & RED_POS;
    blue[1] = stop_color & BLUE_POS;
    green[1] = stop_color & GREEN_POS;

    if(red[0] > red[1])
    {
        delta_red = red[0] - red[1];
        grad_red = 0;
    } 
    else
    {
        delta_red = red[1] - red[0];
        grad_red = 1;
    } 

    if(blue[0] > blue[1])
    {
        delta_blue = blue[0] - blue[1];
        grad_blue = 0;
    } 
    else
    {
        delta_blue = blue[1] - blue[0];
        grad_blue = 1;
    } 

    if(green[0] > green[1])
    {
        delta_green = green[0] - green[1];
        grad_green = 0;
    } 
    else
    {
        delta_green = green[1] - green[0];
        grad_green = 1;
    } 

    
    delta_red >>= 11;
    delta_green >>= 5;

    if(delta_red)
        delta_red = (bottom - top) / delta_red;
    if(delta_blue)
        delta_blue = (bottom - top) / delta_blue;
    if(delta_green)
        delta_green = (bottom - top) / delta_green;

    running_red = delta_red;
    running_blue = delta_blue;
    running_green = delta_green;

    while(top < bottom)
    {
        UINT16 new_y;

        new_y = 240;

        if(running_red)
            if(running_red < new_y)
                new_y = running_red;
        
        if(running_blue)
            if(running_blue < new_y)
                new_y = running_blue;

        if(running_green)
            if(running_green < new_y)
                new_y = running_green;

        SetColor(start_color);

        Bar(left, top, right, top + new_y);

        top += new_y;

        if(delta_red)
        {
            running_red -= new_y;
            
            if(!running_red)
            {
                if(grad_red)
                    start_color += 0x0800;
                else
                    start_color -= 0x0800;

                running_red = delta_red;
            }
        }
                    
        if(delta_green)
        {
            running_green -= new_y;
            
            if(!running_green)
            {
                if(grad_green)
                    start_color += 0x0020;
                else
                    start_color -= 0x0020;

                running_green = delta_green;
            }
        }

        if(delta_blue)
        {
            running_blue -= new_y;
            
            if(!running_blue)
            {
                if(grad_blue)
                    start_color += 1;
                else
                    start_color -= 1;

                running_blue = delta_blue;
            }
        }
    }

} 

//Microchip Logo
const char L1185835933[] ={
    0x00,       //Compression
    0x01,       //Color depth
    0x20,0x00,  //Height
    0x20,0x00,  //Width
    ///////////////////////////////////////

    //COLOR TABLE
    ///////////////////////////////////////
    0x00,0xF8,
    0xFF,0xFF,

    ///////////////////////////////////////
    //BMP IMAGE
    ///////////////////////////////////////
    0xFF,0xFC,0x3F,0xFF,0xFF,0xC0,0x03,0xFF,0xFF,0x00,0x01,0xFF,0xFE,0x00,0x01,0xFF,0xF8,0x00,0x00,0xFF,0xF0,0x00,0x00,0x7F,0xF0,0x00,0x00,0x7F,0xE0,0x38,0x0E,0x3F,
    0xC0,0x78,0x0F,0x1F,0xC0,0x7C,0x1F,0x9F,0x80,0xFE,0x3F,0x8F,0x81,0xFE,0x3F,0xC7,0x81,0xFF,0x3F,0xC7,0x00,0xFF,0x1F,0xE3,0x04,0xFF,0x9F,0xF1,0x0E,0x7F,0xCF,0xF1,
    0x1E,0x3F,0xC7,0xF8,0x1F,0x3F,0xE7,0xFC,0x3F,0x9F,0xE3,0xFC,0xFF,0x8F,0xF3,0xFF,0xFF,0xC7,0xF1,0xFF,0xFF,0x87,0xE0,0xFF,0xFF,0x03,0xE0,0xFF,0xFE,0x03,0xC0,0x7F,
    0xFE,0x01,0x80,0x3F,0xFC,0x00,0x00,0x3F,0xF0,0x00,0x00,0x0F,0xF8,0x00,0x00,0x1F,0xFE,0x00,0x00,0x7F,0xFF,0x00,0x00,0xFF,0xFF,0xC0,0x03,0xFF,0xFF,0xFC,0x3F,0xFF,
};

#define __T4_ISR    __ISR(_TIMER_4_VECTOR, ipl1)
void __T4_ISR _T4Interrupt(void){
   tick++;
   mT4ClearIntFlag();		// Clear flag
   TouchProcessTouch();	//Process the touch action
}

/////////////////////////////////////////////////////////////////////////////
// Function: void TickInit(void)
// Input: none
// Output: none
// Overview: Initilizes the tick timer.
/////////////////////////////////////////////////////////////////////////////

/*********************************************************************
 * Section: Tick Delay
 *********************************************************************/
#define SAMPLE_PERIOD       500 // us
#define TICK_PERIOD			(GetPeripheralClock() * SAMPLE_PERIOD) / 4000000

/* */
void TickInit(void){
    // Initialize Timer4
    OpenTimer4(T4_ON | T4_PS_1_8, TICK_PERIOD);
    ConfigIntTimer4(T4_INT_ON | T4_INT_PRIOR_1);
}

