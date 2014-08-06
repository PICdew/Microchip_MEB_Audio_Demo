#ifndef _WM8731_DRV_H_
#define _WM8731_DRV_H_

#include <p32xxxx.h>
#include <GenericTypeDefs.h>
#include <sys/kmem.h>

/***********************************
 * Modify the below to suit the  application.
 **********************************/
#define WM8731DRV_STARTUP_GAIN 40

/**********************************
 * This specifies the SPI module connected to the WM8731 Digital
 * Audio Interface. In custom hardware this can be specified
 * to any valid device SPI module such as SPI2A, SPI3A etc.
 **********************************/
#define WM8731DRV_SPI_MODULE     SPI1 

/**********************************
 * This specifies the I2C module connected to the WM8731 Control
 * Interface. In custom hardware this can be specified to any 
 * valid device I2C module such as I2C1 etc.
 **********************************/
#define WM8731DRV_I2C_MODULE     I2C2    

/***********************************
 * Needed for errata fix only
 ***********************************/
#define WM8731DRV_I2C2_SDA_LAT  LATAbits.LATA3
#define WM8731DRV_I2C2_SDA_TRIS TRISAbits.TRISA3
     
/**********************************
 * This specifies the two DMA channels which the driver will use to implement
 * ping pong buffering. Channels should be consecutive with PING channel being
 * the lower of the two. For example channel 0 is ping and channel 1 is
 * pong or channel 2 is ping and channel 3 is pong.
 **********************************/
#define WM8731DRV_TX_DMA_PING_CHANNEL DCH0            
#define WM8731DRV_TX_DMA_PONG_CHANNEL DCH1            

/**********************************
 * This specifies the DMA channel which will receive data from the
 * SPI module specified by WM8731DRV_SPI_MODULE and store it
 * codec driver buffer. In custom hardware this can be specified to be any
 * valid device DMA channel such as DCH0, DCH3, DCH4 etc. It should be
 * different from WM8731DRV_TX_DMA_CHANNEL.
 **********************************/
#define WM8731DRV_RX_DMA_CHANNEL DCH2      

/**********************************
 * This macro specifies the IRQ source for WM8731DRV_TX_DMA_CHANNEL. It should
 * match the TX IRQ of the SPI module specified in WM8731DRV_SPI_MODULE.
 * Specify the interrupt vector, interrupt flag and interrupt enable for the ping
 * and pong DMA channels.
 **********************************/
#define WM8731DRV_DMA_SPI_TX_IRQ _SPI1_TX_IRQ

#define WM8731DRV_TX_PONG_DMA_VECTOR             _DMA_1_VECTOR
#define WM8731DRV_TX_PONG_DMA_IPL                ipl5
#define WM8731DRV_TX_PONG_DMA_INT_FLAG           IFS1bits.DMA1IF
#define WM8731DRV_TX_PONG_DMA_INT_ENABLE         IEC1bits.DMA1IE
#define WM8731DRV_TX_PONG_DMA_INT_PRIORITY       IPC9bits.DMA1IP
#define WM8731DRV_TX_PONG_DMA_INT_SUB_PRIORITY   IPC9bits.DMA1IS

#define WM8731DRV_TX_PING_DMA_VECTOR             _DMA_0_VECTOR
#define WM8731DRV_TX_PING_DMA_IPL                ipl5
#define WM8731DRV_TX_PING_DMA_INT_FLAG           IFS1bits.DMA0IF
#define WM8731DRV_TX_PING_DMA_INT_ENABLE         IEC1bits.DMA0IE
#define WM8731DRV_TX_PING_DMA_INT_PRIORITY       IPC9bits.DMA0IP
#define WM8731DRV_TX_PING_DMA_INT_SUB_PRIORITY   IPC9bits.DMA0IS

/**********************************
 * This macro specifies the IRQ source for WM8731DRV_RX_DMA_CHANNEL. It should
 * match the RX IRQ of the SPI module specified in WM8731DRV_SPI_MODULE.
 **********************************/
#define WM8731DRV_DMA_SPI_RX_IRQ _SPI1_RX_IRQ

/******************************************
 * Defines the playback driver buffer size.
 * The size is specified in stereo samples.
 * Each stereo sample is made up of two 16 bit words. Increasing the buffer sizing
 * increases the availability of the buffers for input and output. But this
 * also requires more memory space. Make this 0 if playback is not required.
 * *************************************/
#define WM8731DRV_TX_BUFFER_SIZE    (1152 * 2)    

/******************************************
 * Defines the record driver buffer size.
 * The size is specified in stereo samples.
 * Each stereo sample is made up of two 16 bit words. Increasing the buffer sizing
 * increases the availability of the buffers for input and output. But this
 * also requires more memory space. Make this 0 if record is not required.
 * *************************************/
#define WM8731DRV_RX_BUFFER_SIZE    (1152 * 2)    

/***************************************
 * Specify the clockspeed at which the PIC32 connected to the codec works.
 * *************************************/
#define WM8731DRV_SYSTEM_CLOCK 80000000 
                                       
/***************************************
 * Specify the I2C address of codec. This is defined in hardware by the CSB pin
 * of the codec. Refer to WM8731 datasheet for more details
 * *************************************/
#define WM8731DRV_I2C_ADDR 0x34         

/****************************************
 * The following macros specify the start up codec configuration. Change this to
 * match the applicaiton needs. This values will be loaded by the WM8731CodecLoadStartup()
 * function. Note that you can still change the codec settings at run time using the
 * WM8731CodecIOCtl() function. Refer to the WM8731 data sheet for interpretation of
 * these values.  
 ****************************************/
#define WM8731_LINVOL_STARTUP   0x17
#define WM8731_RINVOL_STARTUP   0x17
#define WM8731_LOUT1V_STARTUP   0xFF 
#define WM8731_ROUT1V_STARTUP   0xFF 
#define WM8731_APANA_STARTUP    0x15    // Sidetone ON = 0x35, Sidetone OFF = 0x15
#define WM8731_APDIGI_STARTUP   0x00 
#define WM8731_PWR_STARTUP      0x00    // 0x00 for MICPD?.. 0x02
#define WM8731_IFACE_STARTUP    0x53
#define WM8731_SRATE_STARTUP    0x0D 

/*****************************
 * Do not change anything below this line
 *****************************/

/***********************************
 * Refer to Kernighan Ritchie for more details on the following macro
#define CAT(x,y)    x ## y
#define XCAT(x,y)   CAT(x,y)
 * These macros create the registers to use based on selection made by the user.
 **************************************/

/****************************************
 * These definitions for the selected SPI module.
 ****************************************/
#define SPICON      XCAT(XCAT(WM8731DRV_SPI_MODULE, ),CON)
#define SPICONBITS  XCAT(XCAT(WM8731DRV_SPI_MODULE, ),CONbits)
#define SPISTAT     XCAT(XCAT(WM8731DRV_SPI_MODULE, ),STAT)
#define SPISTATBITS XCAT(XCAT(WM8731DRV_SPI_MODULE, ),STATbits)
#define SPIBUF      XCAT(XCAT(WM8731DRV_SPI_MODULE, ),BUF)
#define SPIBRG      XCAT(XCAT(WM8731DRV_SPI_MODULE, ),BRG)

/****************************************
 * These definitions for the selected I2C module.
 ****************************************/
#define I2CCON      XCAT(XCAT(WM8731DRV_I2C_MODULE, ),CON)
#define I2CCONBITS  XCAT(XCAT(WM8731DRV_I2C_MODULE, ),CONbits)
#define I2CSTAT     XCAT(XCAT(WM8731DRV_I2C_MODULE, ),STAT)
#define I2CSTATBITS XCAT(XCAT(WM8731DRV_I2C_MODULE, ),STATbits)
#define I2CADD      XCAT(XCAT(WM8731DRV_I2C_MODULE, ),ADD)
#define I2CBRG      XCAT(XCAT(WM8731DRV_I2C_MODULE, ),BRG)
#define I2CTRN      XCAT(XCAT(WM8731DRV_I2C_MODULE, ),TRN)
#define I2CRCV      XCAT(XCAT(WM8731DRV_I2C_MODULE, ),RCV)

/******************************************
 * These definitions are for the selected TX and RX DMA channel.
 *****************************************/
#define PING_TXDCHCON        XCAT(XCAT(WM8731DRV_TX_DMA_PING_CHANNEL, ),CON)
#define PING_TXDCHCONSET     XCAT(XCAT(WM8731DRV_TX_DMA_PING_CHANNEL, ),CONSET)
#define PING_TXDCHCONBITS    XCAT(XCAT(WM8731DRV_TX_DMA_PING_CHANNEL, ),CONbits)
#define PING_TXDCHCONCLR     XCAT(XCAT(WM8731DRV_TX_DMA_PING_CHANNEL, ),CONCLR)
#define PING_TXDCHECON       XCAT(XCAT(WM8731DRV_TX_DMA_PING_CHANNEL, ),ECON)
#define PING_TXDCHECONBITS   XCAT(XCAT(WM8731DRV_TX_DMA_PING_CHANNEL, ),ECONbits)
#define PING_TXDCHINT        XCAT(XCAT(WM8731DRV_TX_DMA_PING_CHANNEL, ),INT)
#define PING_TXDCHINTBITS    XCAT(XCAT(WM8731DRV_TX_DMA_PING_CHANNEL, ),INTbits)
#define PING_TXDCHSSA        XCAT(XCAT(WM8731DRV_TX_DMA_PING_CHANNEL, ),SSA)
#define PING_TXDCHDSA        XCAT(XCAT(WM8731DRV_TX_DMA_PING_CHANNEL, ),DSA)
#define PING_TXDCHSSIZ       XCAT(XCAT(WM8731DRV_TX_DMA_PING_CHANNEL, ),SSIZ)
#define PING_TXDCHDSIZ       XCAT(XCAT(WM8731DRV_TX_DMA_PING_CHANNEL, ),DSIZ)
#define PING_TXDCHSPTR       XCAT(XCAT(WM8731DRV_TX_DMA_PING_CHANNEL, ),SPTR)
#define PING_TXDCHDPTR       XCAT(XCAT(WM8731DRV_TX_DMA_PING_CHANNEL, ),DPTR)
#define PING_TXDCHCSIZ       XCAT(XCAT(WM8731DRV_TX_DMA_PING_CHANNEL, ),CSIZ)
#define PING_TXDCHCPTR       XCAT(XCAT(WM8731DRV_TX_DMA_PING_CHANNEL, ),CPTR)

#define PONG_TXDCHCON        XCAT(XCAT(WM8731DRV_TX_DMA_PONG_CHANNEL, ),CON)
#define PONG_TXDCHCONSET     XCAT(XCAT(WM8731DRV_TX_DMA_PONG_CHANNEL, ),CONSET)
#define PONG_TXDCHCONBITS    XCAT(XCAT(WM8731DRV_TX_DMA_PONG_CHANNEL, ),CONbits)
#define PONG_TXDCHCONCLR     XCAT(XCAT(WM8731DRV_TX_DMA_PONG_CHANNEL, ),CONCLR)
#define PONG_TXDCHECON       XCAT(XCAT(WM8731DRV_TX_DMA_PONG_CHANNEL, ),ECON)
#define PONG_TXDCHECONBITS   XCAT(XCAT(WM8731DRV_TX_DMA_PONG_CHANNEL, ),ECONbits)
#define PONG_TXDCHINT        XCAT(XCAT(WM8731DRV_TX_DMA_PONG_CHANNEL, ),INT)
#define PONG_TXDCHINTBITS    XCAT(XCAT(WM8731DRV_TX_DMA_PONG_CHANNEL, ),INTbits)
#define PONG_TXDCHSSA        XCAT(XCAT(WM8731DRV_TX_DMA_PONG_CHANNEL, ),SSA)
#define PONG_TXDCHDSA        XCAT(XCAT(WM8731DRV_TX_DMA_PONG_CHANNEL, ),DSA)
#define PONG_TXDCHSSIZ       XCAT(XCAT(WM8731DRV_TX_DMA_PONG_CHANNEL, ),SSIZ)
#define PONG_TXDCHDSIZ       XCAT(XCAT(WM8731DRV_TX_DMA_PONG_CHANNEL, ),DSIZ)
#define PONG_TXDCHSPTR       XCAT(XCAT(WM8731DRV_TX_DMA_PONG_CHANNEL, ),SPTR)
#define PONG_TXDCHDPTR       XCAT(XCAT(WM8731DRV_TX_DMA_PONG_CHANNEL, ),DPTR)
#define PONG_TXDCHCSIZ       XCAT(XCAT(WM8731DRV_TX_DMA_PONG_CHANNEL, ),CSIZ)
#define PONG_TXDCHCPTR       XCAT(XCAT(WM8731DRV_TX_DMA_PONG_CHANNEL, ),CPTR)

#define RXDCHCON        XCAT(XCAT(WM8731DRV_RX_DMA_CHANNEL, ),CON)      // WM8731DRV_RX_DMA_CHANNEL = DCH2 (Channel 2)
#define RXDCHCONBITS    XCAT(XCAT(WM8731DRV_RX_DMA_CHANNEL, ),CONbits)
#define RXDCHECON       XCAT(XCAT(WM8731DRV_RX_DMA_CHANNEL, ),ECON)
#define RXDCHECONBITS   XCAT(XCAT(WM8731DRV_RX_DMA_CHANNEL, ),ECONbits)
#define RXDCHINT        XCAT(XCAT(WM8731DRV_RX_DMA_CHANNEL, ),INT)
#define RXDCHSSA        XCAT(XCAT(WM8731DRV_RX_DMA_CHANNEL, ),SSA)
#define RXDCHDSA        XCAT(XCAT(WM8731DRV_RX_DMA_CHANNEL, ),DSA)
#define RXDCHSSIZ       XCAT(XCAT(WM8731DRV_RX_DMA_CHANNEL, ),SSIZ)
#define RXDCHDSIZ       XCAT(XCAT(WM8731DRV_RX_DMA_CHANNEL, ),DSIZ)
#define RXDCHSPTR       XCAT(XCAT(WM8731DRV_RX_DMA_CHANNEL, ),SPTR)
#define RXDCHDPTR       XCAT(XCAT(WM8731DRV_RX_DMA_CHANNEL, ),DPTR)
#define RXDCHCSIZ       XCAT(XCAT(WM8731DRV_RX_DMA_CHANNEL, ),CSIZ)
#define RXDCHCPTR       XCAT(XCAT(WM8731DRV_RX_DMA_CHANNEL, ),CPTR)

/************************************
 * This defines the I2C module baud rate register value. The
 * I2C module is set to operate at 100kbps. Refer to the PIC32
 * I2C FRM section for more details
 ************************************/
#define WM8731DRV_I2C_SPEED 100000
#define WM8731DRV_I2CBAUD ((WM8731DRV_SYSTEM_CLOCK/(2 * WM8731DRV_I2C_SPEED)) - 2)

/*********************************
 * Defines of a stereo audio data sample
 *********************************/
typedef union {
    struct{
        INT16 leftChannel;
        INT16 rightChannel;
    };
    UINT32 audioWord;
}STEREO_AUDIO_DATA;

/************************************
 * Ping pong buffer status. Maintains
 * data about a ping pong buffer.
 ***********************************/
typedef struct{
    STEREO_AUDIO_DATA * buffer;
    BOOL bufferIsBusy;
    UINT bufferSize;
}PING_PONG_BUFFER;

#define WM8731DRV_BUFFER_DESC PING_PONG_BUFFER 

/***********************************************
 * Codec Data Structure. Maintains the current
 * state of the codec.
 ***********************************************/
typedef struct{
    STEREO_AUDIO_DATA * rxBuffer;
    STEREO_AUDIO_DATA * txBuffer;
    UINT16 rxBufferReadPtr;
    UINT16 txBufferReadPtr;
    UINT16 rxBufferWritePtr;
    UINT16 txBufferWritePtr;
    volatile UINT pingPongBufferFlag;
    volatile PING_PONG_BUFFER ppBuffers[2];
    INT16 gain;
}WM8731_CODEC;

typedef union{
    INT32 result;
    struct{
        UINT16 loResult;
        UINT16 hiResult;
    };
}MUL_RESULT;

/*************************************
 * This enumeration details all the 
 * WM8731 registers. Refer to the 
 * WM8731 data sheet table 29 for more
 * details.
 *************************************/

typedef enum{
    WM8731_LINVOL = 0x00,
    WM8731_RINVOL = 0x01,
    WM8731_LOUT1V = 0x02,
    WM8731_ROUT1V = 0x03,
    WM8731_APANA  = 0x04,
    WM8731_APDIGI = 0x05,
    WM8731_PWR    = 0x06,
    WM8731_IFACE  = 0x07,
    WM8731_SRATE  = 0x08,
    WM8731_ACTIVE = 0x09,
    WM8731_RESET  = 0x0F
}WM8731_REGISTER;

/****************************************
 * The following macros specify the default
 * values of the codec register. These are 
 * the values that the codec registers will
 * have after reset. 
 ****************************************/

#define WM8731_LINVOL_DEFAULT   0x97
#define WM8731_RINVOL_DEFAULT   0x97
#define WM8731_LOUT1V_DEFAULT   0x79
#define WM8731_ROUT1V_DEFAULT   0X79
#define WM8731_APANA_DEFAULT    0X0A
#define WM8731_APDIGI_DEFAULT   0x08
#define WM8731_PWR_DEFAULT      0x9F
#define WM8731_IFACE_DEFAULT    0x9F
#define WM8731_SRATE_DEFAULT    0x0
#define WM8731_ACTIVE_DEFAULT   0x0


/**********************************
 * Defines the possible read write
 * modes for the codec driver.
 *********************************/
typedef enum{
    O_RDONLY,   /* Open the codec for a read operation only */
    O_WRONLY,   /* Open the codec for write operation only   */
    O_RDWR      /* Open the codec for both read and write   */
}O_MODE;

/******************************
 * Basic Functions
 *****************************/
WM8731_CODEC * WM8731CodecOpen(WM8731_CODEC * codecHandle, STEREO_AUDIO_DATA* txBuffer, 
        STEREO_AUDIO_DATA * rxBuffer, O_MODE mode); 
UINT WM8731Codec_read(WM8731_CODEC * codecHandle, STEREO_AUDIO_DATA * data, UINT nSamples); 
UINT WM8731Codec_write(WM8731_CODEC * codecHandle, STEREO_AUDIO_DATA * data, UINT nSamples); 
void WM8731CodecIOCtl(WM8731_CODEC * codecHandle, WM8731_REGISTER commandRegister, void * data); 

/*******************************
 * Helper Functions
 ******************************/
UINT WM8731CodecRead(WM8731_CODEC * codecHandle, STEREO_AUDIO_DATA * data, UINT nSamples); 
UINT WM8731CodecWrite(WM8731_CODEC * codecHandle, STEREO_AUDIO_DATA * data, UINT nSamples); 
void WM8731CodecStopAudio(WM8731_CODEC * codecHandle);
void WM8731CodecStartAudio(WM8731_CODEC * codecHandle);
void WM8731CodecLoadStartup(WM8731_CODEC * codecHandle);
WM8731DRV_BUFFER_DESC * WM8731CodecGetEmptyBuffer(WM8731_CODEC * codecHandle);
void WM8731CodecProcessBuffer(WM8731DRV_BUFFER_DESC * bufferDescriptor);
STEREO_AUDIO_DATA * WM8731CodecGetBufferAddress (WM8731DRV_BUFFER_DESC * bufferDescriptor);
void WM8731ClearTxBuffer(WM8731_CODEC * pCodecHandle);
void WM8731CodecSetVolume(INT volume);

#endif
