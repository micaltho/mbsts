/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/MonitorIO/WindowsTcpIp/RXF_MonitorIO.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_MonitorIO_H
#define RXF_MonitorIO_H

#include "cstdint"
#include <winsock.h>
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
        
        bool checkDataAvailable(void);
        
        void sendData(void);
        
        bool addCommand(const std::uint32_t size, const std::uint8_t* const data);
        
        void addResetCommand(const std::uint32_t size, const std::uint8_t* const data);
        
        ////    Attributes    ////
    
    private :
    
        static SOCKET ConnectSocket;
        
        static MIO_ConnectionStatus initilized;
    };
}

#endif
/*********************************************************************
	File Path	: ../Source/MonitorIO/WindowsTcpIp/RXF_MonitorIO.h
*********************************************************************/
