/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/MonitorIO/GHS_stdio/RXF_MonitorIO.h
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
    
        void init(void);
        
        std::uint8_t read(void);
        
        bool checkDataAvailable(void);
        
        void sendData(void);
        
        bool addCommand(const std::uint32_t size, const std::uint8_t* const data);
        
        void addResetCommand(const std::uint32_t size, std::uint8_t data);
        
        ////    Attributes    ////
    
    private :
    
        static std::uint8_t sendBuffer[MIO_SEND_BUFFER_SIZE];
        
        static std::uint32_t sendBufferReadPtr;
        
        static std::uint32_t sendBufferWritePtr;
    };
}

#endif
/*********************************************************************
	File Path	: ../Source/MonitorIO/GHS_stdio/RXF_MonitorIO.h
*********************************************************************/
