/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/MonitorIO/SeggerRTT/RXF_MonitorIO.cpp
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#include <SEGGER_RTT.h>
#include "RXF_MonitorIO.h"
namespace RXF {
    /* @MISRA_0-1-8=OFF XD-0000: Operation is empty but still needed from Monitor */
    void MonitorIO::init(void) const
    {
    }
    
    /* @MISRA_0-1-8=ON (end of XD-0000) */
    
    std::uint8_t MonitorIO::read(void) const
    {
        uint8_t recChar;   
        (void)SEGGER_RTT_Read( 0U, &recChar, 1U );
        return( recChar );
    }
    
    bool MonitorIO::checkDataAvailable(void) const
    {
        bool retVal = false;
        if( 0U != SEGGER_RTT_HasData( 0U ) )
        {
        	retVal = true;
        }
        return retVal;
    }
    
    /* @MISRA_0-1-8=OFF XD-0000: Operation is empty but still needed from Monitor */
    void MonitorIO::sendData(void) const
    {
    }
    
    /* @MISRA_0-1-8=ON (end of XD-0000) */
    
    bool MonitorIO::addCommand(const std::uint32_t size, const std::uint8_t* const data) const
    {
        bool retVal = false;
        if( 0U != SEGGER_RTT_Write(0U, data, size ) )
        {
        	retVal = true;
        }
        return retVal;
    }
    
    void MonitorIO::addResetCommand(const std::uint32_t size, const std::uint8_t* const data) const
    {
        (void)SEGGER_RTT_Write(0U, data, size );
    }
}

/*********************************************************************
	File Path	: ../Source/MonitorIO/SeggerRTT/RXF_MonitorIO.cpp
*********************************************************************/
