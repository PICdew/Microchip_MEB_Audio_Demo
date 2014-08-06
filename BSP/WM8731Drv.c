/**********************************************************************
* © 2010 Microchip Technology Inc.
*
* FileName:        WM8731Drv.h
* Dependencies:    Header (.h) files if applicable, see below
* Processor:       PIC32MX
*
************************************************************************/

#include "WM8731Drv.h"
#include "module_dyn_header.h"
#include "plib.h"

static WM8731_CODEC *thisCodec;

const static INT16 gainTable[75] = {
0x0,
0x7,
0x8,
0x9,
0xA,
0xB,
0xD,
0xE,
0x10,
0x12,
0x14,
0x17,
0x1A,
0x1D,
0x20,
0x24,
0x29,
0x2E,
0x33,
0x3A,
0x41,
0x49,
0x52,
0x5C,
0x67,
0x74,
0x82,
0x92,
0xA4,
0xB8,
0xCE,
0xE7,
0x104,
0x124,
0x147,
0x16F,
0x19C,
0x1CE,
0x207,
0x246,
0x28D,
0x2DD,
0x337,
0x39B,
0x40C,
0x48A,
0x518,
0x5B7,
0x66A,
0x732,
0x813,
0x90F,
0xA2A,
0xB68,
0xCCC,
0xE5C,
0x101D,
0x1214,
0x1449,
0x16C3,
0x198A,
0x1CA7,
0x2026,
0x2413,
0x287A,
0x2D6A,
0x32F5,
0x392C,
0x4026,
0x47FA,
0x50C3,
0x5A9D,
0x65AC,
0x7214,
0x7FFF,
};

PRIVATE void SPIInit(void){
    /****************************************
     * This function initializes the SPI module and enables it. The
     * module is configured for 32 bit DSP/PCM operation.
     * The module is configured to operate in framed slave mode. The codec will
     * provide the clock and the frame sync signal.
     ****************************************/
    SPICON = 0xE00008C0;        //

    IEC0bits.SPI1RXIE = 1;      // SPI RX Int Enabled...

    SPICONBITS.ON = 1;          // Enable SPI...
}

PRIVATE void I2CInit(void){
    /*************************************
     * Initialize the I2C module. I2C baud is specified in the WM8731Drv.h.
     *************************************/

    /* I2C is running during idle	*/
    /* IPMI is disabled			*/
    /* 7 bit slave address		*/
    /* No slew control			*/
    /* No SMBus Enabled			*/

    /* I2C Baud				*/
    /* Enable the I2C module		*/

    I2CBRG = WM8731DRV_I2CBAUD;  
    I2CCON = 0x8000;

    /* Work around for I2C errata */
    WM8731DRV_I2C2_SDA_LAT  = 0;
    WM8731DRV_I2C2_SDA_TRIS  = 0;

    I2CCONBITS.SEN = 1;					
    while(I2CCONBITS.SEN == 1);	
    I2CCONBITS.PEN = 1;
    while(I2CCONBITS.PEN);

}

PRIVATE void DMAInit(WM8731_CODEC * pCodecHandle){
    /**********************************
     * This function intializes the DMA channels for TX and RX.
     **********************************/
    
    if(pCodecHandle->txBuffer != 0){
        /* This means the driver TX function is enabled. Configure the DMA TX
         * channels. Two DMA channel are used in channel chaining mode. 
         * This allows for a ping pong buffer implementation. */

       UINT pingpongFlag = pCodecHandle->pingPongBufferFlag; 
       PONG_TXDCHCON =  0x20;
       PONG_TXDCHECONBITS.CHSIRQ = WM8731DRV_DMA_SPI_TX_IRQ;
       PONG_TXDCHECONBITS.SIRQEN = 1;
       PONG_TXDCHSSA = KVA_TO_PA(pCodecHandle->ppBuffers[1].buffer);
       PONG_TXDCHDSA = KVA_TO_PA(&SPIBUF);
       PONG_TXDCHSSIZ = (WM8731DRV_TX_BUFFER_SIZE/2) * sizeof(STEREO_AUDIO_DATA);
       PONG_TXDCHDSIZ = sizeof(UINT32);
       PONG_TXDCHCSIZ = sizeof(STEREO_AUDIO_DATA);
      
       PING_TXDCHCON = 0x120;
       PING_TXDCHECONBITS.CHSIRQ = WM8731DRV_DMA_SPI_TX_IRQ;
       PING_TXDCHECONBITS.SIRQEN = 1;
       PING_TXDCHSSA = KVA_TO_PA(pCodecHandle->ppBuffers[0].buffer);
       PING_TXDCHDSA = KVA_TO_PA(&SPIBUF);
       PING_TXDCHSSIZ = (WM8731DRV_TX_BUFFER_SIZE/2) * sizeof(STEREO_AUDIO_DATA);
       PING_TXDCHDSIZ = sizeof(UINT32);
       PING_TXDCHCSIZ = sizeof(STEREO_AUDIO_DATA);
      
       PONG_TXDCHINTBITS.CHBCIF = 0;
       PONG_TXDCHINTBITS.CHBCIE = 1;
       WM8731DRV_TX_PONG_DMA_INT_FLAG = 0;
       WM8731DRV_TX_PONG_DMA_INT_PRIORITY = 5;
       WM8731DRV_TX_PONG_DMA_INT_SUB_PRIORITY = 0;
     
       PING_TXDCHINTBITS.CHBCIF = 0;
       PING_TXDCHINTBITS.CHBCIE = 1;
       WM8731DRV_TX_PING_DMA_INT_FLAG = 0;
       WM8731DRV_TX_PING_DMA_INT_PRIORITY = 5;
       WM8731DRV_TX_PING_DMA_INT_SUB_PRIORITY = 0;

       WM8731DRV_TX_PING_DMA_INT_ENABLE = 1;
       WM8731DRV_TX_PONG_DMA_INT_ENABLE = 1;

    }
    if(pCodecHandle->rxBuffer != 0){
        /* This means the driver RX function is enabled. Configure the DMA RX
         * channel. Channel is configured for continuous mode. Configure channel
         * to start transfer when interrupt is received. No DMA interrupts are
         * enabled. */
       // KVA_TO_PA() = Convert Address to Physical Address
       RXDCHCON =  0x10;                                                // DCH2CON
       RXDCHECONBITS.CHSIRQ = WM8731DRV_DMA_SPI_RX_IRQ;                 // DCH2ECON (SPI1 RX)
       RXDCHECONBITS.SIRQEN = 1;                                        // DCH2ECON "Start channel cell transfer if an interrupt matching CHSIRQ occurs"
       RXDCHDSA = KVA_TO_PA(pCodecHandle->rxBuffer);                    // Channel Destination Start Address b
       RXDCHSSA = KVA_TO_PA(&SPIBUF);                                   // Channel Source Start Address bits
       RXDCHDSIZ = WM8731DRV_RX_BUFFER_SIZE * sizeof(STEREO_AUDIO_DATA);// Channel Destination Size bits
       RXDCHSSIZ = sizeof(UINT32);                                      // Channel Source Size bits
       RXDCHCSIZ = sizeof(STEREO_AUDIO_DATA);                           // Channel Cell-Size bits
    }
    DMACONbits.ON = 1;
}

PRIVATE BOOL I2CWrite(UINT reg, UINT val){
    /* Refer to the WM8731 datasheet Table 25 for
     * details on how the control data should be written to the device. */
	BYTE byte1 = (BYTE) ((reg << 1) | (val >> 8));
	BYTE byte2 = (BYTE) (val & 0xFF);

    /* Send the start condition. Wait for the condition to complete	*/
	I2CCONBITS.SEN = 1;					
	while(I2CCONBITS.SEN == 1);		

    /* Address of the WM8731. Wait till this has been tranmitted	*/
    /* If this value is 1 then a NACK was was recieved							*/
                                              
    /* Send the stop condition if a NACK was received							*/

	I2CTRN = WM8731DRV_I2C_ADDR;		
	while(I2CSTATBITS.TRSTAT);	
	if (I2CSTATBITS.ACKSTAT){
            I2CCONBITS.PEN = 1;
            while(I2CCONBITS.PEN);
            return(FALSE);
	}
	
    /* The address of the register              */
    /* Wait till this has been tranmitted	*/
    /* If ACKSTAT value is 1 then a NACK 	*/
    /* was recieved				*/
                                              
    /* Send the stop condition if a NACK	*/
    /* was received				*/

	I2CTRN = byte1;					    
	while(I2CSTATBITS.TRSTAT);
	if (I2CSTATBITS.ACKSTAT){
		I2CCONBITS.PEN = 1;
		while(I2CCONBITS.PEN);			
        return(FALSE);							
	}
	
    /* The value of the register			*/
    /* Wait till this has been tranmitted	*/
    /* If ACKSTAT value is 1 then a NACK 	*/
    /* was recieved							*/
                                              
    /* Send the stop condition if a NACK	*/
    /* was received							*/
    
        I2CTRN = byte2;
	while(I2CSTATBITS.TRSTAT);
	if (I2CSTATBITS.ACKSTAT){
            I2CCONBITS.PEN = 1;
            while(I2CCONBITS.PEN);
            return(FALSE);
	}
    
    /* Send the stop condition	*/
	I2CCONBITS.PEN = 1;
	while(I2CCONBITS.PEN);			
	return(TRUE);

}

WM8731_CODEC * WM8731CodecOpen(WM8731_CODEC * codecHandle,
        STEREO_AUDIO_DATA* txBuffer, STEREO_AUDIO_DATA * rxBuffer, O_MODE mode) {

    UINT i;

    /* Check the open mode and assign memory pointers accordingly */
    switch(mode){
        case O_RDONLY:{
            /* Setup codec for read only*/
            codecHandle->rxBuffer = rxBuffer;
            codecHandle->txBuffer = 0;
            break;
        }
        case O_WRONLY:{
            /* Setup codec for write only */
            codecHandle->rxBuffer = 0;
            codecHandle->txBuffer = txBuffer;
            break;
        }
        case O_RDWR:{
            /* Setup codec for read and write */
            codecHandle->rxBuffer = rxBuffer;
            codecHandle->txBuffer = txBuffer;
            break;
        }
        default:
            return(NULL);
    }

    /* Initialize the circular buffer read and write pointers */
    codecHandle->rxBufferReadPtr = 0;
    codecHandle->rxBufferWritePtr = 0;
    codecHandle->txBufferReadPtr = 0;
    codecHandle->txBufferWritePtr = 0;

    /* Clear the codec driver tx buffers */
    if(codecHandle->txBuffer != 0){
        for (i = 0; i < WM8731DRV_TX_BUFFER_SIZE; i ++){
            codecHandle->txBuffer[i].audioWord = 0;
        }
    }

    codecHandle->ppBuffers[0].buffer = txBuffer; 
    codecHandle->ppBuffers[1].buffer = &(txBuffer[WM8731DRV_TX_BUFFER_SIZE/2]); 
    codecHandle->ppBuffers[0].bufferIsBusy = FALSE;
    codecHandle->ppBuffers[1].bufferIsBusy = TRUE;
    codecHandle->pingPongBufferFlag = 0;
    codecHandle->ppBuffers[0].bufferSize = WM8731DRV_TX_BUFFER_SIZE/2;
    codecHandle->ppBuffers[1].bufferSize = WM8731DRV_TX_BUFFER_SIZE/2;

    /* Start the control communication channel. The I2C module is used for this purpose. */
    I2CInit();

    /* Initialize the DMA modules */
    DMAInit(codecHandle);
    
    /* Start the codec data Interface. The SPI module is used for this purpose. */
    SPIInit();

    thisCodec = codecHandle;
    thisCodec->gain = gainTable[WM8731DRV_STARTUP_GAIN];

    return(codecHandle);
} 

UINT WM8731Codec_read(WM8731_CODEC * codecHandle, STEREO_AUDIO_DATA * data, UINT nStereoSamples){
    /*************************************
     * This is a non blocking read call. The function will copy stereo data 
     * from the codec driver buffer to the application buffer . The amount of
     * data to be copied will be determined by the rxBufferWritePtr and
     * rxBufferReadPtr
     *************************************/

    UINT nReadSamples = 0;
    UINT i;

    /* Check if nothing should be read */
    if(nStereoSamples == 0) return(0);
    /* Compute the amount of data available in the codec driver receive buffer. */
    UINT rxBufferReadPtr = codecHandle->rxBufferReadPtr;
    UINT rxBufferWritePtr = RXDCHDPTR/sizeof(STEREO_AUDIO_DATA);
    STEREO_AUDIO_DATA * src = codecHandle->rxBuffer;

    if(rxBufferWritePtr == rxBufferReadPtr){
        /* This means that the buffer is empty. */
                                                //PORTSetBits(IOPORT_D, BIT_1);
        return(0);
    }else if( rxBufferWritePtr > rxBufferReadPtr){
                                                //PORTSetBits(IOPORT_D, BIT_3);
        /* This means that the codec driver is ahead of the application read */
        nReadSamples = rxBufferWritePtr - rxBufferReadPtr;
    }else{
                                                //PORTSetBits(IOPORT_C, BIT_1);
        /* This means the codec driver is ahead of the application read but
         * the write has wrapped around. */
        nReadSamples = WM8731DRV_RX_BUFFER_SIZE - rxBufferReadPtr + rxBufferWritePtr;
    }
    /* If the number of available samples is greater than those required, then
     * only read the number of required samples. */
    nReadSamples = (nReadSamples > nStereoSamples) ? nStereoSamples : nReadSamples;
    /* Store the samples in the application buffer and handle the read pointer rollover */
    for(i = 0; i < nReadSamples; i ++){
        data[i].audioWord = src[rxBufferReadPtr].audioWord;
        rxBufferReadPtr ++;
        if(rxBufferReadPtr >= WM8731DRV_RX_BUFFER_SIZE){
            rxBufferReadPtr = 0;
        }  
    }
    codecHandle->rxBufferReadPtr = rxBufferReadPtr;
    return(nReadSamples);
}

WM8731DRV_BUFFER_DESC * WM8731CodecGetEmptyBufferDesc(WM8731_CODEC * codecHandle){
    /* This function will return the buffer descriptor of an empty TX buffer. */

    if(codecHandle->ppBuffers[0].bufferIsBusy == FALSE)
        return((PING_PONG_BUFFER *)&codecHandle->ppBuffers[0]);
    if(codecHandle->ppBuffers[1].bufferIsBusy == FALSE)
        return((PING_PONG_BUFFER *)&codecHandle->ppBuffers[1]);
    return(NULL);
    
}

STEREO_AUDIO_DATA * WM8731CodecGetBufferAddress (WM8731DRV_BUFFER_DESC * bufferDescriptor){
    /* This function obtains the address of the buffer for the given buffer descriptor */
    return((STEREO_AUDIO_DATA *)(bufferDescriptor->buffer));
}

void WM8731CodecProcessBuffer(WM8731DRV_BUFFER_DESC * bufferDescriptor){
    /* This function hands over the buffer to the ping pong buffering scheme for output. */
    bufferDescriptor->bufferIsBusy = TRUE;
}

UINT WM8731Codec_write(WM8731_CODEC * codecHandle, STEREO_AUDIO_DATA * data, UINT nStereoSamples){
    /*************************************
     * This is a non blocking write call. The function will copy stereo data 
     * from the application buffer to the codec driver buffer. The amount of
     * data to be copied will be determined by the txBufferWritePtr and
     * txBufferReadPtr
     *************************************/
    STEREO_AUDIO_DATA * dest;
    UINT i;
    MUL_RESULT mulResult;
    INT16 gain;
    
    /* Check if there is nothing to write */
    if(nStereoSamples == 0) return(0);
    UINT pingpongFlag = codecHandle->pingPongBufferFlag;    
    volatile PING_PONG_BUFFER * ppBuffer = &codecHandle->ppBuffers[pingpongFlag];
    if(ppBuffer->bufferIsBusy == TRUE){
        return(0);
    }
    dest = ppBuffer->buffer;
    gain = codecHandle->gain;
    for(i = 0; i < nStereoSamples; i++){
        /* Copy data from the application buffer to the codec driver buffer. */
        mulResult.result = ((INT32)(gain * data[i].leftChannel)) * 2;   
        dest[i].leftChannel = (INT16)(mulResult.hiResult);
        mulResult.result = ((INT32)(gain * data[i].rightChannel)) * 2;   
        dest[i].rightChannel = (INT16)(mulResult.hiResult);
    }
    ppBuffer->bufferIsBusy = TRUE;
    return(nStereoSamples);    
} 

void WM8731CodecIOCtl(WM8731_CODEC * codecHandle, WM8731_REGISTER commandRegister, void * data){
    /* Send the specified command to the specified WM8731 register */
    UINT command = *((UINT *)(data));
    *(BOOL *)data = I2CWrite(commandRegister, command);
}
 
UINT WM8731CodecRead(WM8731_CODEC * codecHandle, STEREO_AUDIO_DATA * data, UINT nSamples){
    /* This is a blocking implementation of the codec read function. This function will 
     * not return unless nSamples have been read. */
    UINT read = 0;
    while (read < nSamples){
        read += WM8731Codec_read(codecHandle, &data[read], (nSamples - read));
    }
    return(nSamples);
}

UINT WM8731CodecWrite(WM8731_CODEC * codecHandle, STEREO_AUDIO_DATA * data, UINT nSamples){
    /* This is a blocking implementation of the codec write function. This function will not
     * return unless nSamples have been written */
    UINT written = 0;
    while(written < nSamples){
        written += WM8731Codec_write(codecHandle, &data[written], (nSamples - written));
    }
    return(nSamples);
}

void WM8731CodecStopAudio(WM8731_CODEC * codecHandle){
    /* Stop the codec audio interface  and disable the SPI Interrupts*/
    if(codecHandle->txBuffer != 0){
        /* This means that write mode is enabled. Suspend the TX DMA channel. */
        PING_TXDCHCONBITS.CHEN = 0;
        PONG_TXDCHCONBITS.CHEN = 0;
    }
    if(codecHandle->rxBuffer != 0){
        /* This means the read mode is enabled. Suspend RX DMA Channel */
        RXDCHCONBITS.CHEN = 0;          // Channel is disabled...
    }
}

void WM8731CodecStartAudio(WM8731_CODEC * codecHandle){
    /* Enable the SPI interrupts and start the codec audio interface */
    if(codecHandle->txBuffer != 0){
        /* This means that write mode is enabled. Enable the TX interrupt. */
        PING_TXDCHCONBITS.CHEN = 1;
    }
    if(codecHandle->rxBuffer != 0){
        /* This means the read mode is enabled. Enabled RX interrupt */
         RXDCHCONBITS.CHEN = 1;         // Channel is enabled...
    }
}

void WM8731ClearTxBuffer(WM8731_CODEC * pCodecHandle){
    int i;
    if(pCodecHandle->txBuffer != 0){
        for (i = 0; i < WM8731DRV_TX_BUFFER_SIZE; i ++){
            pCodecHandle->txBuffer[i].audioWord = 0;
        }
    }
}

void WM8731CodecLoadStartup(WM8731_CODEC * pCodecHandle){
    /* This function loads the codec register with the starup values
     * specified in WM8731Drv.h file */

    UINT command = 0;
    
    command = 0x80;
    WM8731CodecIOCtl(pCodecHandle, WM8731_PWR, &command);

    /* Reset the codec */
    command = 0;
    WM8731CodecIOCtl(pCodecHandle, WM8731_RESET, &command );
    command = 0x0;
    WM8731CodecIOCtl(pCodecHandle, WM8731_ACTIVE, &command);
    command = WM8731_APANA_STARTUP;
    WM8731CodecIOCtl(pCodecHandle, WM8731_APANA, &command);
    command = WM8731_APDIGI_STARTUP;
    WM8731CodecIOCtl(pCodecHandle, WM8731_APDIGI, &command);
    command = WM8731_PWR_STARTUP;
    WM8731CodecIOCtl(pCodecHandle, WM8731_PWR, &command );
    command = WM8731_IFACE_STARTUP;
    WM8731CodecIOCtl(pCodecHandle, WM8731_IFACE, &command );
    command = WM8731_SRATE_STARTUP;
    WM8731CodecIOCtl(pCodecHandle, WM8731_SRATE, &command );
    command = WM8731_LINVOL_STARTUP;
    WM8731CodecIOCtl(pCodecHandle, WM8731_LINVOL, &command);
    command = WM8731_RINVOL_STARTUP;
    WM8731CodecIOCtl(pCodecHandle, WM8731_RINVOL, &command);
    command = WM8731_LOUT1V_STARTUP;
    WM8731CodecIOCtl(pCodecHandle, WM8731_LOUT1V, &command);
    command = WM8731_ROUT1V_STARTUP;
    WM8731CodecIOCtl(pCodecHandle, WM8731_ROUT1V, &command);
    command = 1;
    WM8731CodecIOCtl(pCodecHandle, WM8731_ACTIVE, &command);
}

void __attribute__((vector(WM8731DRV_TX_PONG_DMA_VECTOR), 
            interrupt(WM8731DRV_TX_PONG_DMA_IPL), nomips16)) PongDMAInterruptHandler(void){
    unsigned volatile int save_gp;
    export_prologue(save_gp);

    if( PONG_TXDCHINTBITS.CHBCIF == 1){
        thisCodec->pingPongBufferFlag = 1;
        thisCodec->ppBuffers[1].bufferIsBusy = FALSE;
        PONG_TXDCHINTBITS.CHBCIF = 0;
    }
    if(thisCodec->ppBuffers[0].bufferIsBusy != TRUE){
        /* This means a buffer under run condition has occurred. Buffer 1 has been consumed by the
         * driver and it has switched to buffer 0. But buffer 0 has not been populated by the
         * application. You could place some type of a error handler here. */
        Nop();
        Nop();
        Nop();
    }
    WM8731DRV_TX_PONG_DMA_INT_FLAG = 0;
    export_epilogue(save_gp);
}

void __attribute__((vector(WM8731DRV_TX_PING_DMA_VECTOR), 
            interrupt(WM8731DRV_TX_PONG_DMA_IPL), nomips16)) PingDMAInterruptHandler(void){
    unsigned volatile int save_gp;
    export_prologue(save_gp);

    if( PING_TXDCHINTBITS.CHBCIF == 1){
        thisCodec->pingPongBufferFlag = 0;
        thisCodec->ppBuffers[0].bufferIsBusy = FALSE;
        PING_TXDCHINTBITS.CHBCIF = 0;
    }
    if(thisCodec->ppBuffers[1].bufferIsBusy != TRUE){
        /* This means a buffer under run condition has occurred. Buffer 0 has been consumed by the
         * driver and it has switched to buffer 1. But buffer 1 has not been populated by the
         * application. You could place some type of a error handler here. */
        Nop();
        Nop();
        Nop();
    }
    WM8731DRV_TX_PING_DMA_INT_FLAG = 0;
    export_epilogue(save_gp);
}

void __ISR(_SPI_1_VECTOR, ipl3)__SPI1Interrupt(void){
    // ... perform application specific operations in response to the interrupt
    PORTSetBits(IOPORT_D, BIT_1);

    //IFS0CLR = 0x03800000;

    IFS0bits.SPI1RXIF = 0;          // Be sure to clear the SPI1 interrupt flags before exiting the service routine.
}

void WM8731CodecSetVolume(INT volume){
    if(volume < 0) return;
    if(volume > 74) return;
    thisCodec->gain = gainTable[volume];
}


