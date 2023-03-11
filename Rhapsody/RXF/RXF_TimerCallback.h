/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/generic/RXF_TimerCallback.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_TimerCallback_H
#define RXF_TimerCallback_H

namespace RXF {
    class TimerCallback {
    public :
    
        virtual void onTimeout(void) = 0;
    
    protected :
    
        /* @MISRA_0-1-8=OFF ID-0003: The Interface needs a virtual destructor, because it has virtual operations. */
        inline virtual ~TimerCallback(void)
        {
        }
        /* @MISRA_0-1-8=ON (end of ID-0003) */
    
    private :
    
        virtual TimerCallback& operator=(const TimerCallback& other) = delete;
    };
}

#endif
/*********************************************************************
	File Path	: ../Source/generic/RXF_TimerCallback.h
*********************************************************************/
