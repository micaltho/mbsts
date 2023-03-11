/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/MonitorIO/SeggerRTT/RXF_MonitorIO.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_MonitorIO_H
#define RXF_MonitorIO_H

namespace RXF {
    class MonitorIO {
    public :
    
        void init(void) const;
        
        std::uint8_t read(void) const;
        
        bool checkDataAvailable(void) const;
        
        void sendData(void) const;
        
        bool addCommand(const std::uint32_t size, const std::uint8_t* const data) const;
        
        void addResetCommand(const std::uint32_t size, const std::uint8_t* const data) const;
    };
}

#endif
/*********************************************************************
	File Path	: ../Source/MonitorIO/SeggerRTT/RXF_MonitorIO.h
*********************************************************************/
