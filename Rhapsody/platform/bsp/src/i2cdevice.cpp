#include "i2cdevice.h"

/* --undef if read/write on I2C should not be printed. */
#ifdef DEBUG
//#define DEBUG_I2C
#endif

namespace Platform {

namespace BSP {


bool I2CDevice::initialize(Interface ifc, Mode mode, uint32_t speed) {
	bool retvalue=false;
	I2C_ID_T id=static_cast<I2C_ID_T>(ifc);
	/* --Configure board pinmux etc. */
	Board_I2C_Init(id);
	/* --Configure interface. */
	Chip_I2C_Init(id);
	/* --Set clock speed. */
	Chip_I2C_SetClockRate(id, speed);

	/* --Just polling mode implemented. */
	if (mode==Mode::POLLING) {
		LPC175X_6X_IRQn_Type irqid = I2C0_IRQn;
		switch (ifc) {
		case Interface::I2C0 : irqid=I2C0_IRQn; break;
		case Interface::I2C1 : irqid=I2C1_IRQn; break;
		case Interface::I2C2 : irqid=I2C2_IRQn; break;
		}
		/* --Disable IRQ. */
		NVIC_DisableIRQ(irqid);
		retvalue=(1==Chip_I2C_SetMasterEventHandler(id, Chip_I2C_EventHandlerPolling));
	}

	return retvalue;
}

bool I2CDevice::deinitialize(Interface ifc) {
	I2C_ID_T id=static_cast<I2C_ID_T>(ifc);
	Chip_I2C_DeInit(id);
	return true;
}


I2CDevice::I2CDevice(Interface ifc, uint8_t addr, uint8_t dc):interface(ifc),address(addr) {}


bool I2CDevice::read(uint8_t* buffer, uint32_t& len) const {
	I2C_ID_T id=static_cast<I2C_ID_T>(interface);
	/* --Read buffer. */
    if (lock)      lock();
	uint32_t received=Chip_I2C_MasterRead(id,address,buffer,len);
    if (unlock)    unlock();
#ifdef DEBUG_I2C
	printf("\x1b[35mI2C 0X%02X @ 0X%02X \x1b[36m<--",(unsigned)address,(unsigned)interface);
	for(uint32_t i=0;i<len;i++)
		printf(" %02X",(unsigned)buffer[i]);
	printf(" %s\x1b[0m\r\n",  received ? "\x1b[32mOK." : "\x1b[31mFAILED!");
#endif
	len=received;
	return (0!=received);
}

bool I2CDevice::write(uint8_t* buffer, uint32_t& len) const {
	I2C_ID_T id=static_cast<I2C_ID_T>(interface);
	/* --Write buffer. */
    if (lock)    lock();
	uint32_t sent=Chip_I2C_MasterSend(id,address,buffer,len);
    if (unlock)    unlock();
#ifdef DEBUG_I2C
	printf("\x1b[35mI2C 0X%02X @ 0X%02X -->",(unsigned)address,(unsigned)interface);
	for(uint32_t i=0;i<len;i++)
		printf(" %02X",(unsigned)buffer[i]);
	printf(" %s\x1b[0m\r\n",  sent ? "\x1b[32mOK." : "\x1b[31mFAILED!");
#endif
	len=sent;
	return (0!=sent);
}

bool I2CDevice::set(uint8_t cmd, uint8_t value) const {
	uint32_t len=2;
	uint8_t buffer[len];
	buffer[0]=cmd;
	buffer[1]=value;
	/* --Write 2 bytes at once. */
	if (write(buffer,len))
		return (2==len);
	return false;
}

bool I2CDevice::set(uint8_t cmd, uint16_t value) const {
	uint32_t len=3;
	uint8_t buffer[len];
	buffer[0]=cmd;
	buffer[1]=value;
	buffer[2]=value>>8;
	/* --Write 3 bytes at once. */
	if (write(buffer,len))
		return (3==len);
	return false;
}

bool I2CDevice::set(uint8_t cmd, uint32_t value) const {
	uint32_t len=5;
	uint8_t buffer[len];
	buffer[0]=cmd;
	buffer[1]=value;
	buffer[2]=value>>8;
	buffer[3]=value>>16;
	buffer[4]=value>>24;
	/* --Write 5 bytes at once. */
	if (write(buffer,len))
		return (5==len);
	return false;
}

bool I2CDevice::get(uint8_t cmd, uint8_t& value) const {
	uint32_t txLen=1, rxLen=1;
	/* --Write/read transfer with single bytes. */
	if (transfer(&cmd,txLen,&value,rxLen))
		return (1==txLen && 1==rxLen);
	return false;
}

bool I2CDevice::get(uint8_t cmd, uint16_t& value) const {
	uint32_t txLen=1, rxLen=2;
	/* --Write/read transfer with single bytes. */
	if (transfer(&cmd,txLen,(uint8_t*)&value,rxLen))
		return (1==txLen && 2==rxLen);
	return false;
}

bool I2CDevice::get(uint8_t cmd, uint32_t& value) const {
	uint32_t txLen=1, rxLen=4;
	/* --Write/read transfer with single bytes. */
	if (transfer(&cmd,txLen,(uint8_t*)&value,rxLen))
		return (1==txLen && 4==rxLen);
	return false;
}

bool I2CDevice::assignLockFct(LockFctType l,LockFctType ul) {
    lock   = l;
    unlock = ul;
    return true;
}


bool I2CDevice::transfer(uint8_t* txBuf, uint32_t& txLen, uint8_t* rxBuf, uint32_t& rxLen) const {
	bool retvalue=false;

	I2C_XFER_T transfer;

	transfer.slaveAddr=address;
	transfer.txBuff=txBuf;
	transfer.txSz=txLen;
	transfer.rxBuff=rxBuf;
	transfer.rxSz=rxLen;

#ifdef DEBUG_I2C
	printf("\x1b[35mI2C 0X%02X @ 0X%02X -->",(unsigned)address,(unsigned)interface);
	for(uint32_t i=0;i<txLen;i++)
		printf(" %02X",(unsigned)txBuf[i]);
#endif

	/* --Run write/read-transfer. */
	I2C_ID_T id=static_cast<I2C_ID_T>(interface);

	if (lock)      lock();  // make it thread save!
	Chip_I2C_MasterTransfer(id,&transfer);
    if (unlock)    unlock();
	if (I2C_STATUS_DONE == transfer.status) {
		txLen=txLen-transfer.txSz;
		rxLen=rxLen-transfer.rxSz;
		retvalue=true;
	}

#ifdef DEBUG_I2C
	printf(" \x1b[36m<--");
	for(uint32_t i=0;i<rxLen;i++)
		printf(" %02X",(unsigned)rxBuf[i]);
	printf(" %s\x1b[0m\r\n",  transfer.status==I2C_STATUS_DONE ? "\x1b[32mOK." : "\x1b[31mFAILED!");
#endif

	return retvalue;
}

} /* --Namespace BSP. */
} /* --Namespace Platform. */
