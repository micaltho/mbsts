/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/MonitorIO/LinuxTcpIp/RXF_MonitorIO.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_MonitorIO_H
#define RXF_MonitorIO_H

#include "RXF_Types.h"
namespace RXF {
    class MonitorIO {
    private :
    
        enum MIO_ConnectionStatus
        {
            NotConnected = 0,
            Connected = 1,
            ConnectionFailed = 2
        };
    
    public :
    
        void init(void);
        
        std::uint8_t read(void);
        
        bool checkDataAvailable(void) const;
        
        void sendData(void) const;
        
        bool addCommand(const std::uint32_t size, const std::uint8_t* const data);
        
        void addResetCommand(const std::uint32_t, const std::uint8_t* const) const;
        
        std::int8_t connect_nonblock(const std::int32_t sock, const std::uint8_t timeout);
        
        ////    Attributes    ////
    
    private :
    
        static MIO_ConnectionStatus initilized;
    };
}

#endif
/*********************************************************************
	File Path	: ../Source/MonitorIO/LinuxTcpIp/RXF_MonitorIO.h
*********************************************************************/
