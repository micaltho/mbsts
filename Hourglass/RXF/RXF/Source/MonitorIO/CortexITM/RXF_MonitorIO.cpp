/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/MonitorIO/CortexITM/RXF_MonitorIO.cpp
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#include "RXF_CriticalSection.h"
#include "RXF_MonitorIO.h"
namespace RXF {
    
    volatile int32_t ITM_RxBuffer;        // 0x5AA55AA5 is handshake value
    
    /* @MISRA_5-2-7+5-2-8=OFF XD-0000: Convert uint32_t to pointer to access ITM data */
    volatile std::uint32_t* MonitorIO::DEMCR1((reinterpret_cast<volatile uint32_t *>(0xE000EDFCU)));
    /* @MISRA_5-2-7+5-2-8=ON (end of XD-0000) */
    
    /* @MISRA_5-2-7+5-2-8=OFF XD-0000: Convert uint32_t to pointer to access ITM data */
    volatile std::uint32_t* MonitorIO::ITM_Port32((reinterpret_cast<volatile uint32_t  *>( 0xE0000000U ) ));
    /* @MISRA_5-2-7+5-2-8=ON (end of XD-0000) */
    
    /* @MISRA_5-2-7+5-2-8=OFF XD-0000: Convert uint32_t to pointer to access ITM data */
    volatile std::uint8_t* MonitorIO::ITM_Port8((reinterpret_cast<volatile uint8_t  *>( 0xE0000000U ) ));
    /* @MISRA_5-2-7+5-2-8=ON (end of XD-0000) */
    
    const std::uint32_t MonitorIO::TRCENA1(0x01000000U);
    
    std::uint8_t MonitorIO::sendBuffer[MIO_SEND_BUFFER_SIZE];
    
    std::uint32_t MonitorIO::sendBufferReadPtr(0U);
    
    std::uint32_t MonitorIO::sendBufferWritePtr(0U);
    
    void MonitorIO::init(void) const
    {
        ITM_RxBuffer = 0x5AA55AA5;	/* this value must be exactly 0x5AA55AA5 that the monitor recocnize that no data have received */
    }
    
    std::uint8_t MonitorIO::read(void) const
    {
        uint8_t recChar;   
        
        while ( ITM_RxBuffer == 0x5AA55AA5 ){}	/* wait until data has received from the host (!!blocking!!) */
        recChar = static_cast<uint8_t>(ITM_RxBuffer);
        ITM_RxBuffer = 0x5AA55AA5;	/* reset public variable to default value */
        
        return recChar;
    }
    
    bool MonitorIO::checkDataAvailable(void) const
    {
        return !( ITM_RxBuffer == 0x5AA55AA5 );
    }
    
    void MonitorIO::sendData(void) const
    {
        while( sendBufferReadPtr != sendBufferWritePtr )
        {     
        	if ( ( *DEMCR1 & TRCENA1) == TRCENA1 )
        	{                                                                               
        		while (*ITM_Port32 == 0U ) /* while ITM FIFO is full */
        		{ 
        			; 
        		}	
        		*ITM_Port8 = sendBuffer[ sendBufferReadPtr ];	/* send data to the host */
        	}
        	sendBufferReadPtr++;
        	if( sendBufferReadPtr == MIO_SEND_BUFFER_SIZE )
        	{
        		sendBufferReadPtr = 0U;
        	}
        }
    }
    
    bool MonitorIO::addCommand(const std::uint32_t size, const std::uint8_t* const data) const
    {
        uint32_t oldSendBufferWritePtr; 
        bool retVal = false;
        CriticalSection criticalSection;
        criticalSection.lock();
        uint32_t dataAvailable = MIO_SEND_BUFFER_SIZE - ( sendBufferWritePtr - sendBufferReadPtr );
        if( dataAvailable > MIO_SEND_BUFFER_SIZE )
        {
        	dataAvailable -= MIO_SEND_BUFFER_SIZE;
        }
        if( dataAvailable >= ( size + ( 2U + MONITOR_DATA_OFFSET ) ) )
        {   		
        	oldSendBufferWritePtr = sendBufferWritePtr;
        	sendBufferWritePtr = sendBufferWritePtr + size; 
        	if( sendBufferWritePtr >= MIO_SEND_BUFFER_SIZE )
        	{
        		sendBufferWritePtr = sendBufferWritePtr - MIO_SEND_BUFFER_SIZE;
        	}
        	criticalSection.unlock();
        	for( uint32_t i = 0U; i < size; i++)
        	{       
        		/* @MISRA_5-0-15=OFF XD-0001: Cast from pointer to array to accesses data from byte stream. */
        		sendBuffer[ oldSendBufferWritePtr ] = data[ i ];      
        		/* @MISRA_5-0-15=ON (end of XD-0001) */
        		oldSendBufferWritePtr++;
        		if( oldSendBufferWritePtr == MIO_SEND_BUFFER_SIZE )
        		{
        			oldSendBufferWritePtr = 0U;
        		}
        	} 
        	retVal = true;
        }
        else
        {      
        	criticalSection.unlock();
        }                       
        return retVal;
    }
    
    void MonitorIO::addResetCommand(const std::uint32_t size, const std::uint8_t* const data) const
    {
        CriticalSection criticalSection;
        criticalSection.lock();
        for( uint32_t i = 0U; i < size; i++)
        {    
        	/* @MISRA_5-0-15=OFF XD-0001: Cast from pointer to array to accesses data from byte stream. */
        	sendBuffer[ sendBufferWritePtr ] = data[ i ];
        	/* @MISRA_5-0-15=ON (end of XD-0001) */  
        	sendBufferWritePtr++;
        	if( sendBufferWritePtr == MIO_SEND_BUFFER_SIZE )
        	{
        		sendBufferWritePtr = 0U;
        	}
        } 
        criticalSection.unlock();
        
    }
}

/*********************************************************************
	File Path	: ../Source/MonitorIO/CortexITM/RXF_MonitorIO.cpp
*********************************************************************/
