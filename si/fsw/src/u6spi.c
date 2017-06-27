
int SPI(HANDLE hDevice, uint8 CSPin, uint8 CLKPin, uint8 MISOPin, uint8 MOSIPin, uint8 SPIOpts, uint8 NumSPIBytes, uint8 *SPITx uint8 *SPIRx)
{
    int ret = 0;

    //If we're trying to send an odd number of bytes, we need to add another to fill up the end of the last word
    uint8 oddByte = 0;
    if(1 == NumSPIBytes%2)
    {
        oddByte = 1;
        NumSPIBytes++;
    }

    uint8 *sendBuff, *recBuff; 
    uint16 checksumTotal = 0;
    int sendChars, recChars;
    int sendSize = 13 + NumSPIBytes; //13 command bytes 
    int recSize = 7 + NumSPIBytes; //7 response info bytes 

    sendBuff = (uint8 *)malloc(sizeof(uint8)*sendSize);
    recBuff = (uint8 *)malloc(sizeof(uint8)*recSize);

    //sendBuff[0] //Checksum8 
    sendBuff[1] = (uint8)0xF8; //command byte (says that this is a command)
    sendBuff[2] = 4 + (NumSPIBytes/2); //4 + # of SPI words (bytes/2). 
    sendBuff[3] = (uint8)0x3A; //SPI-specific command #
    //sendBuff[4] = //Checksum16(LSB)
    //sendBuff[5] = //Checksum16(MSB)
    sendBuff[6] = SPIOpts;//(uint8)0xC0 //11000000 -- MSB is AutoCS, second is DisableDirConfig, two LSB are SPIModes 0-3
    sendBuff[7] = 0; //SPI Clock Factor (0 is 100khz)
    //sendBuff[8] = // Advanced Options: bits 2-0 -- # of bits in final byte
    sendBuff[9] = CSPin;//CS Pin #
    sendBuff[10] = CLKPin; //CLK Pin #
    sendBuff[11] = MISOPin;// MISO Pin #
    sendBuff[12] =  MOSIPin;//MOSI Pin #
    sendBuff[13] =  NumSPIBytes;//# of SPI bytes to transfer
   
    //Add all SPI bytes to the command buffer, then set the last byte to 0 if we had to add one to make the # even
    if(1 == oddByte)
    {
        for(int i=0; i < (sendSize-1); i++)
        {
            sendBuff[14+i] = SPITx[i];
        }
        sendBuff[sendSize-1] = 0;
    }
    else
    {
        for(int i=0; i < sendSize; i++)
        {
            sendBuff[14+i] = SPITx[i];
        }
    }


    extendedChecksum(sendBuff, sendSize);

    //sending the command buffer to the U6 returns the number of chars sent
    sendChars = LJUSB_Write(hDevice, sendBuff, sendSize)
    if(sendChars < sendSize)
    {
        if( sendChars == 0 )
            ret = -1; //SPI Error : write failed
        else
            ret = -2; //SPI Error : did not write all of the buffer
        
        goto cleanmem; //clean up allocated memory
    }

    //receiving the response returns the number of chars received
    recChars = LJUSB_Read(hDevice, recBuff, recSize)
    if(recChars < recSize)
    {
        if( recChars == 0 )
            ret = -3; //SPI Error : read failed
        else
            ret = -4; //SPI Error : did not write all of the buffer
            //byte 6 is the error code, may want to grab and return it for further debugging

        goto cleanmem; //clean up allocated memory
    }

    //get the SPI data from the response
    for(int i=0; i < NumSPIBytes; i++)
    {
        SPIRx[i] = recBuff[7+i];
    }


    if( (uint8)(extendedChecksum8(recBuff)) != recBuff[0] )
        ret = -5; //SPI Error : read buffer has bad checksum

    if( recBuff[1] != (uint8)(0xF8) )
        ret = -6; //SPI Error : read buffer has incorrect command byte

    if( recBuff[2] != (uint8)(1+(NumSPIBytes/2))//the third response byte should be 1+NumSPIWords
        ret = -7; //SPI Error : read buffer has incorrect number of data words

    if( recBuff[3] != (uint8)(0x3A) )
        ret = -8; // SPI Error : read buffer has incorrect extended command number

    checksumTotal = extendedChecksum16(recBuff, recSize);
    if( (uint8)((checksumTotal / 256) & 0xff) != recBuff[5] || (uint8)(checksumTotal & 255) != recBuff[4] )
        ret = -9; //SPI error : read buffer has bad checksum16

cleanmem:
    free(sendBuff);
    free(recBuff);
    sendBuff = NULL;
    recBuff = NULL;

    return ret;
}