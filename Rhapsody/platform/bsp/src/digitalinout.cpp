#include "digitalinout.h"
#include "interrupt.h"

#include "gpio_17xx_40xx.h"

namespace Platform {

namespace BSP {

/* --Manager for interrupt handling. */
static InterruptManager* iManager=nullptr;
static char memInterruptManager[sizeof(InterruptManager)];

bool DigitalInOut::initialize(bool alsoInitializeInterruptHandling) {
	bool retValue=true;

	Chip_GPIO_Init(LPC_GPIO);
	/* --If not initialize, do it. */
	if (alsoInitializeInterruptHandling) {
		/* --Already done? */
		if (iManager)
			retValue=false;
		else {
			iManager=new(memInterruptManager) InterruptManager;
			// There might be a pending interrupt before a interrupt is registered!
			// This might result in a system crash at start up (only in debug mode, as debugger will
			// not reset system registers).
			// Therefore, we disable all pin interrupts!
			 Chip_GPIOINT_SetIntFalling(LPC_GPIOINT, GPIOINT_PORT0,0);
			 Chip_GPIOINT_SetIntFalling(LPC_GPIOINT, GPIOINT_PORT2,0);
			 Chip_GPIOINT_SetIntRising(LPC_GPIOINT, GPIOINT_PORT0,0);
			 Chip_GPIOINT_SetIntRising(LPC_GPIOINT, GPIOINT_PORT2,0);

			iManager->enable();
		}
	}

	 return retValue;
}

DigitalInOut::DigitalInOut(uint8_t p, uint32_t b, Direction d): PortPin(p,b) {
	/* --Set the direction of the GPIO. */
	/* --Input direction. */
	if (Direction::INPUT==d)
		Chip_GPIO_SetPinDIRInput(LPC_GPIO,port(),pin());
	/* --Output direction. */
	else
		Chip_GPIO_SetPinDIROutput(LPC_GPIO,port(),pin());
}

void DigitalInOut::set() const {
	/* --Set the value to true (1). */
	Chip_GPIO_WritePortBit(LPC_GPIO,port(),pin(),true);
}

bool DigitalInOut::get() const {
	/* --Get the value and map to true or false. */
	return Chip_GPIO_GetPinState(LPC_GPIO,port(),pin());
}

void DigitalInOut::clear() const {
	/* --Clear the value (0). */
	Chip_GPIO_WritePortBit(LPC_GPIO,port(),pin(),false);
}

bool DigitalInOut::onInterrupt(const InterruptHandler& irq, uint32_t edge) const {
	if (iManager && iManager->attach(*this,irq))
		return (edge!=NO_EDGE ? enableInterrupt(edge) : true);
	else
		return false;
}

bool DigitalInOut::enableInterrupt(uint32_t edge) const {
	return (iManager ? iManager->enable(*this,edge) : false);
}

bool DigitalInOut::disableInterrupt() const {
	return (iManager ? iManager->disable(*this) : false);
}

bool DigitalInOut::clearPendingInterrupt() const {
    return (iManager ? iManager->clear(*this) : false);
}




}

}
