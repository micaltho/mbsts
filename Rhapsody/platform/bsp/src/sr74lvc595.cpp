#include "sr74lvc595.h"

namespace Platform {

namespace BSP {

SR74LVC595::SR74LVC595(Interface ifc, uint8_t port, uint8_t pin, uint8_t initial):SSPDevice(ifc,port,pin) {
	/* --Set initial value. */
	set(initial);
}

bool SR74LVC595::set(uint8_t value) const {

	#if 0
	SSP_DATA_SETUP_Type xferConfig;
	xferConfig.tx_data = &value;
	xferConfig.rx_data = NULL;
	xferConfig.length = 1;

	/* --Send data. */
//	SSP_SendData(LPC_SSP1, value);
	SSP_ReadWrite(LPC_SSP1, &xferConfig, SSP_TRANSFER_POLLING);
#endif

	uint32_t len=1;

	return write(&value,len) && (1==len);
}

bool SR74LVC595::off() const {
	return set(0xff);
}

}

}
