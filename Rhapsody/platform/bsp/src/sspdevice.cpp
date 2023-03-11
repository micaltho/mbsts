/*
 * sspdevice.cpp
 *
 *  Created on: 21.06.2016
 *      Author: Michael
 */

#include "sspdevice.h"

//#define DEBUG_SSP


namespace Platform {

namespace BSP {

SSPDevice::SSPDevice(Interface ifc, uint8_t port, uint8_t pin):
    ssel(port,pin,DigitalInOut::Direction::OUTPUT),
    interface(ifc==Interface::SSP0 ? LPC_SSP0 : LPC_SSP1),
    sym_interface(ifc),
    lock(nullptr),
    unlock(nullptr)
{

}


bool SSPDevice::initialize(Interface ifc) {
    LPC_SSP_T* interface=(ifc==Interface::SSP0 ? LPC_SSP0 : LPC_SSP1);

    Board_SSP_Init(interface);
    Chip_SSP_Init(interface);
/*
    ssp_format.frameFormat = SSP_FRAMEFORMAT_SPI;
    ssp_format.bits = SSP_DATA_BITS;
    ssp_format.clockMode = SSP_CLOCK_MODE0;
*/

//    Chip_SSP_SetFormat(interface, SSP_FRAMEFORMAT_SPI, SSP_BITS_8, SSP_CLOCK_MODE0);

    Chip_SSP_SetFormat(interface, SSP_FRAMEFORMAT_SPI, SSP_BITS_8, SSP_CLOCK_MODE0);

    Chip_SSP_Enable(interface);

    return true;
}

bool SSPDevice::read(uint8_t* buffer, uint32_t& len) const {

    uint32_t received = len;
    /* --Run read transfer. */
    acquire();
#if 0
    Chip_SSP_DATA_SETUP_T xferConfig;

    xferConfig.tx_data = NULL;
    xferConfig.rx_data = buffer;
    xferConfig.length  = len;
    xferConfig.rx_cnt = xferConfig.tx_cnt = 0;
    Chip_SSP_RWFrames_Blocking(interface, &xferConfig);
#endif

    len = Chip_SSP_ReadFrames_Blocking(interface,buffer,len);
    release();

    return received == len;
}


bool SSPDevice::write(uint8_t* buffer, uint32_t& len) const {
    uint32_t sent=len;
    /* --Run write transfer. */
    acquire();
    len=Chip_SSP_WriteFrames_Blocking(interface,buffer,len);
#if 0
    Chip_SSP_DATA_SETUP_T xferConfig;
    xferConfig.tx_data = buffer;
    xferConfig.rx_data = NULL;
    xferConfig.length  = len;
    xferConfig.rx_cnt = xferConfig.tx_cnt = 0;
    len=Chip_SSP_RWFrames_Blocking (interface,&xferConfig);
#endif
    release();

#ifdef DEBUG_SSP
    printf("\x1b[33mSSP (%d,%d) @ 0X%02X -->",(unsigned)ssel.getPort(),(unsigned)ssel.getPin(),(unsigned)sym_interface);
    for(uint32_t i=0;i<len;i++)
        printf(" %02X",(unsigned)buffer[i]);
    printf(" %s\x1b[0m\r\n",  sent==len ? "\x1b[32mOK." : "\x1b[31mFAILED!");
#endif

    return sent==len;
}

bool SSPDevice::write(uint8_t value) const {
    uint32_t len=1;
    return write(&value,len);
}

bool SSPDevice::assignLockFct(LockFctType l,LockFctType ul) {
    lock   = l;
    unlock = ul;
    return true;
}


void SSPDevice::acquire() const {
    if (lock)      lock();
    ssel.clear();
}


void SSPDevice::release() const {
    ssel.set();
    if (unlock)    unlock();
}


}  // namespace BSP
}  // namespace Platform


