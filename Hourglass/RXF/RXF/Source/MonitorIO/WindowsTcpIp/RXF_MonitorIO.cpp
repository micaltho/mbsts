/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/MonitorIO/WindowsTcpIp/RXF_MonitorIO.cpp
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#include "RXF_MonitorIO.h"
#include "RXF_Config.h"
namespace RXF {
    SOCKET MonitorIO::ConnectSocket;
    
    RXF::MonitorIO::MIO_ConnectionStatus MonitorIO::initilized(NotConnected);
    
    void MonitorIO::init(void)
    {
        if( initilized == NotConnected )
        {
        	WSADATA wsaData;
        	int iResult = WSAStartup( MAKEWORD( 2, 2 ), &wsaData );
        	if ( NO_ERROR != iResult ) 
        	{
        		initilized = ConnectionFailed;  
        		return;
        	}
        
        	ConnectSocket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
        	if ( ConnectSocket == INVALID_SOCKET )
        	{
        		WSACleanup();
        		initilized = ConnectionFailed;  
        		return;
        	}
        	//----------------------
        	// The sockaddr_in structure specifies the address family,
        	// IP address, and port of the server to be connected to.
        	sockaddr_in clientService;
        	clientService.sin_family = AF_INET;
        	clientService.sin_addr.s_addr = inet_addr( "127.0.0.1" );
        	clientService.sin_port = htons( MIO_TCP_PORT );
        
        	//----------------------
        	// Connect to server.
        	iResult = connect( ConnectSocket, (SOCKADDR *)& clientService, sizeof(clientService) );
        	if ( SOCKET_ERROR == iResult) 
        	{
        		WSACleanup();
        		initilized = ConnectionFailed;  
        		return;
        	}      
        	initilized = Connected;
        }
    }
    
    std::uint8_t MonitorIO::read(void)
    {
        uint8_t data;
        if( initilized == NotConnected ) 
        {
        	init();
        }
        if( initilized == Connected ) 
        {
        	recv(ConnectSocket, (char*)&data, 1, 0);
        }
        else
        {
        	while( true )
        	{
        		Sleep( 100 );
        	}
        }
        return data;
    }
    
    bool MonitorIO::checkDataAvailable(void)
    {
        return true;
    }
    
    void MonitorIO::sendData(void)
    {
    }
    
    bool MonitorIO::addCommand(const std::uint32_t size, const std::uint8_t* const data)
    {
        if( initilized == NotConnected )
        {
        	init();
        }
        if( initilized == Connected )
        {
        	send(ConnectSocket,(const char*) data, size, 0);
        }
        return true;
    }
    
    void MonitorIO::addResetCommand(const std::uint32_t size, const std::uint8_t* const data)
    {
    }
}

/*********************************************************************
	File Path	: ../Source/MonitorIO/WindowsTcpIp/RXF_MonitorIO.cpp
*********************************************************************/
