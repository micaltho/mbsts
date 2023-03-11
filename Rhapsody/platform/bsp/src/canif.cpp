/*
 * canif.cpp
 *
 *  Created on: 13.07.2016
 *      Author: Michael
 */

#include "canif.h"

namespace Platform {

namespace BSP {

/* --Registered interrupt handlers. */
CAN* CAN::handler[2]={nullptr,nullptr};

/* --Interrupt handler mapping from plain C to C++. */
extern "C" void CAN_IRQHandler() {
	/* --Check the source of the interrupt. */
	uint32_t status;
	/* --Check CAN1. */
	if (CAN::handler[0] && (status=Chip_CAN_GetIntStatus(LPC_CAN1)))
		CAN::handler[0]->handleInterrupt(status);
	/* --Check CAN2. */
	if (CAN::handler[1] && (status=Chip_CAN_GetIntStatus(LPC_CAN2)))
		CAN::handler[1]->handleInterrupt(status);
}

CAN::CAN(Interface ifc, uint32_t speed):canif(ifc==Interface::CAN1 ? LPC_CAN1: LPC_CAN2) {
	/* --Initialize the CAN bus. */
	Chip_CAN_Init(canif, LPC_CANAF, LPC_CANAF_RAM);
	Chip_CAN_SetBitRate(canif,speed);
	Chip_CAN_SetAFMode(LPC_CANAF, CAN_AF_BYBASS_MODE);
	/* --Initialize handler. */
	for(uint32_t i=0;i<Interrupt::NUM_INTERRUPTS;++i)
		canHandler[i]=nullptr;
}

bool CAN::enableInterrupt() {
	bool retvalue=false;
	/* --Check if already other class instance is registered. */
	Interface me=(canif==LPC_CAN1? Interface::CAN1 : Interface::CAN2);
	if (!handler[static_cast<uint32_t>(me)]) {
		/* --Register this object to handle interrupts. */
		handler[static_cast<uint32_t>(me)]=this;
		uint32_t bits=0;
		for(uint32_t i=0;i<Interrupt::NUM_INTERRUPTS;++i)
			if (canHandler[i])
				bits|=(1<<i);
		Chip_CAN_EnableInt(canif, bits);
		NVIC_SetPriority(CAN_IRQn, 7);
		NVIC_EnableIRQ(CAN_IRQn);
		retvalue=true;
	}
	return retvalue;
}

bool CAN::isBusOff() const {
	return Chip_CAN_GetGlobalStatus(canif)&CAN_GSR_BS;
}

bool CAN::isError() const {
	return Chip_CAN_GetGlobalStatus(canif)&CAN_GSR_ES;
}

uint32_t CAN::status() const {
	return Chip_CAN_GetStatus(canif);
}

uint32_t CAN::globalstatus() const {
	return Chip_CAN_GetGlobalStatus(canif);
}

uint32_t CAN::istatus() const {
	return Chip_CAN_GetIntStatus(canif);
}

CAN::Mode CAN::mode() const {
	return static_cast<CAN::Mode>(Chip_CAN_GetMode(canif));
}

void CAN::mode(Mode nmode, bool isEnable) const {
	Chip_CAN_SetMode(canif,static_cast<CAN_MODE_T>(nmode),isEnable?ENABLE:DISABLE);
}




void CAN::reset() const {
	/* --Check if in reset mode. */

	//set MOD RM, reset mode
//	canif->MOD |=CAN_MOD_RM;
	//write 255 to tx error counter to force bus off
	canif->GSR |= ((uint32_t)(255&0xFF)<<24);
	//wait until SR BS ist set
#if 0
	while(!(canif->GSR & CAN_GSR_BS));
	//clear tx errors
	canif->GSR |= ((uint32_t)(0&0xFF)<<24);
	//clear MOD RM
	canif->MOD = 0x00;
#endif

}




void CAN::set(uint32_t irq, InterruptHandler handler) {
	/* --Check bit position and set handler. */
	for(uint32_t i=0;i<Interrupt::NUM_INTERRUPTS;++i)
		if (irq&(1<<i))
			canHandler[i]=handler;
}

void CAN::unset(uint32_t irq) {
	/* --Disable the interrupts. */
	Chip_CAN_DisableInt(canif,irq);
	/* --Run thru and unset interrupts. */
	for(uint32_t i=0;i<Interrupt::NUM_INTERRUPTS;++i)
		if (irq&(1<<i))
			canHandler[i]=nullptr;
}

void CAN::handleInterrupt(uint32_t status) {
	/* --Check bits. */
	for(uint32_t i=0;i<11;++i)
		/* --Test if handler is available. */
		if (canHandler[i] && status&(1<<i))
			/* --Run handler. */
			canHandler[i](status);
}

CAN::~CAN() {}

bool CAN::send(Message& msg, TransmitBuffer useBuffer) {
	bool retvalue=false;
#if 0
	/* --Check bus state. */
	if (!isBusOff() && !isError()) {
		/* --Get transmit buffer id. */
		CAN_BUFFER_ID_T bid = (useBuffer==TransmitBuffer::FREE_BUFFER ?
				Chip_CAN_GetFreeTxBuf(canif) : static_cast<CAN_BUFFER_ID_T>(useBuffer));

		/* --Send. */
		if (SUCCESS==Chip_CAN_Send(canif,bid,&msg)) {
			/* --Active waiting until buffer is empty. */
			while (!isError() && (Chip_CAN_GetStatus(canif) & CAN_SR_TCS(bid))== 0) {}
			/* --Ok. */
			retvalue=!isError();
		}
	}
#endif

	CAN_BUFFER_ID_T bid = (useBuffer==TransmitBuffer::FREE_BUFFER ?
			Chip_CAN_GetFreeTxBuf(canif) : static_cast<CAN_BUFFER_ID_T>(useBuffer));

	/* --Send. */
	if (SUCCESS==Chip_CAN_Send(canif,bid,&msg)) {
		/* --Active waiting until buffer is empty. */
		while ((Chip_CAN_GetStatus(canif) & CAN_SR_TCS(bid))== 0) {}
		/* --Ok. */
		retvalue=true;
	}

	return retvalue;
}

bool CAN::receive(Message& msg) {
	return SUCCESS==Chip_CAN_Receive(canif,&msg);
}





}

}


