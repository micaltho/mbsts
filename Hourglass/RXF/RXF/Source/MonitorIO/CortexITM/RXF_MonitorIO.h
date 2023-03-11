/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/MonitorIO/CortexITM/RXF_MonitorIO.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_MonitorIO_H
#define RXF_MonitorIO_H

#include "RXF_Config.h"
namespace RXF {
    class MonitorIO {
    public :
    
        void init(void) const;
        
        std::uint8_t read(void) const;
        
        bool checkDataAvailable(void) const;
        
        void sendData(void) const;
        
        bool addCommand(const std::uint32_t size, const std::uint8_t* const data) const;
        
        void addResetCommand(const std::uint32_t size, const std::uint8_t* const data) const;
        
        ////    Attributes    ////
    
    private :
    
        static volatile std::uint32_t* DEMCR1;
        
        static volatile std::uint32_t* ITM_Port32;
        
        static volatile std::uint8_t* ITM_Port8;
        
        static const std::uint32_t TRCENA1;
        
        static std::uint8_t sendBuffer[MIO_SEND_BUFFER_SIZE];
        
        static std::uint32_t sendBufferReadPtr;
        
        static std::uint32_t sendBufferWritePtr;
    };
}

#endif
/*********************************************************************
	File Path	: ../Source/MonitorIO/CortexITM/RXF_MonitorIO.h
*********************************************************************/
