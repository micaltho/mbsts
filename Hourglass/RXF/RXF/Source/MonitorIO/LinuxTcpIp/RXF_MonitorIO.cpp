/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/MonitorIO/LinuxTcpIp/RXF_MonitorIO.cpp
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h> 
#include <fcntl.h>
#include <cerrno>
#include <netdb.h>
#include <linux/sockios.h>
#include <sys/ioctl.h>

#include "RXF_MonitorIO.h"
#include "RXF_Config.h"
namespace RXF {
    
    static int32_t sockfd;
    static uint8_t myRead()
    {
    	uint8_t data;
    	static_cast<void>( read( sockfd, &data, 1UL ) );
    	return data;
    } 
    
    RXF::MonitorIO::MIO_ConnectionStatus MonitorIO::initilized(NotConnected);
    
    void MonitorIO::init(void)
    {
        if( initilized == NotConnected )
        {   
        	/* @MISRA_5-2-7=OFF XD-0001: Cast from enum to int. */
        	sockfd = socket(AF_INET, static_cast<int_t>(SOCK_STREAM), 0);
        	/* @MISRA_5-2-7=ON (end of XD-0001) */
        	if (sockfd == 0)
        	{
        		initilized = ConnectionFailed;
        	}
        
        	else if ( connect_nonblock(sockfd, 3U) < 0 )
        	{
        	    initilized = ConnectionFailed;
        	}
        	else
        	{
        		initilized = Connected;
        	}
        }
    }
    
    std::uint8_t MonitorIO::read(void)
    {
        uint8_t data = 0U;   
        if( initilized == NotConnected ) 
        {
        	init();
        }
        if( initilized == Connected )
        {
        	data = myRead( );
        }
        else
        {
        	while( true )
        	{
        		static_cast<void>( sleep( 20U ) );
        	}
        }
        return data;
    }
    
    bool MonitorIO::checkDataAvailable(void) const
    {
        bool retVal = false;
        if( initilized == Connected )
        {
        	int32_t len;
        	static_cast<void>( ioctl(sockfd, static_cast<uint64_t>(SIOCINQ), &len) );
        	if(len  > 0)
        	{
        		retVal = true;
        	}
        }
        return retVal;
    }
    
    /* @MISRA_0-1-8=OFF XD-0000: Operation is empty but still needed from Monitor */
    void MonitorIO::sendData(void) const
    {
    }
    
    /* @MISRA_0-1-8=ON (end of XD-0000) */
    
    bool MonitorIO::addCommand(const std::uint32_t size, const std::uint8_t* const data)
    {
        if( initilized == NotConnected )
        {
        	init();
        }
        if( initilized == Connected )
        {
        	static_cast<void>(write(sockfd, data, static_cast<size_t>(size)));
        }
        return true;
    }
    
    /* @MISRA_0-1-8=OFF XD-0000: Operation is empty but still needed from Monitor */
    void MonitorIO::addResetCommand(const std::uint32_t, const std::uint8_t* const) const
    {
    }
    
    /* @MISRA_0-1-8=ON (end of XD-0000) */
    
    /* @MISRA_MIO_connect=OFF XD-0000: This operation is not MISRA compliant */
    std::int8_t MonitorIO::connect_nonblock(const std::int32_t sock, const std::uint8_t timeout)
    {
        struct sockaddr_in sa;
        struct hostent *server;
        
        server = gethostbyname(MIO_HOST_ADDRESS);
        if (server == nullptr)
        {
        	initilized = ConnectionFailed;
        	return -1;
        }                           
        
        bzero((char *) &sa, sizeof(sa));
        sa.sin_family = AF_INET;
        bcopy((char *)server->h_addr, (char *)&sa.sin_addr.s_addr, server->h_length);
        sa.sin_port = htons(MIO_HOST_PORT);
        
        int flags = 0, error = 0, ret = 0;
        fd_set  rset, wset;
        socklen_t   len = sizeof(error);
        struct timeval  ts;
        ts.tv_usec = 0;
        ts.tv_sec = timeout;
        
        //clear out descriptor sets for select
        //add socket to the descriptor sets
        FD_ZERO(&rset);
        FD_SET(sock, &rset);
        wset = rset;    //structure assignment ok
        
        //set socket nonblocking flag
        if( (flags = fcntl(sock, F_GETFL, 0)) < 0)
        {
        	return -1;
        }
         
        if(fcntl(sock, F_SETFL, flags | O_NONBLOCK) < 0)
        {
        	return -1;
        }
        //initiate non-blocking connect
        if( (ret = connect(sock, (struct sockaddr *)&sa, 16)) < 0 )
        {
        	if (errno != EINPROGRESS)
        	{
        		return -1;
            }
        }
        
        if(ret == 0)    //then connect succeeded right away
        {
        	//put socket back in blocking mode
        	if(fcntl(sock, F_SETFL, flags) < 0)
        	{
        		return -1;
        	}
        	return 0;
        }
        
        //we are waiting for connect to complete now
        if( (ret = select(sock + 1, &rset, &wset, nullptr, (timeout) ? &ts : nullptr)) < 0)
        {
        	return -1;
        }
        
        if(ret == 0)
        {   //we had a timeout
        	errno = ETIMEDOUT;
        	return -1;
        }
        
        //we had a positivite return so a descriptor is ready
        if (FD_ISSET(sock, &rset) || FD_ISSET(sock, &wset))
        {
        	if(getsockopt(sock, SOL_SOCKET, SO_ERROR, &error, &len) < 0)
        	{
        		return -1;
        	}
        }else
        {
        	return -1;
        }
        
        if(error)
        {  //check if we had a socket error
        	errno = error;
        	return -1;
        }
        
        // Should not be reached
        return 1;
    }
    
    /* @MISRA_MIO_connect=ON (end of XD-0000) */
}

/*********************************************************************
	File Path	: ../Source/MonitorIO/LinuxTcpIp/RXF_MonitorIO.cpp
*********************************************************************/
