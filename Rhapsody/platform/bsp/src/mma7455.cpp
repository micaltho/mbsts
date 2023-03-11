#include "mma7455.h"

namespace Platform {

namespace BSP {

MMA7455::MMA7455(Interface ifc, uint8_t addr):I2CDevice(ifc,addr) {}

bool MMA7455::control(Mode m, GRange gr) const {
	bool retvalue=false;

	/* --Get current mode. */
	uint8_t mode=modeControl();

	/* --Ok? */
	if (mode!=0xff) {
		/* --Clear lower 4 bits. */
		mode&=0xf0;
		/* --Set mode 2 bits [0:1]. */
		switch (m) {
		case STANDBY : break;
		case MEASUREMENT: mode|=0x01; break;
		case LEVEL_DETECTION : mode|=0x02; break;
		case PULSE_DETECTION : mode|=0x03; break;
		}
		/* --Set g-range 2 bits [2:3]. */
		switch (gr) {
		case RANGE_2G : mode|=(0x01)<<2; break;
		case RANGE_4G : mode|=(0x02)<<2; break;
		default : break;
		}

		retvalue=cmd(Register::MCTL,mode);

	}

	/* --Done. */
	return retvalue;
}


uint8_t MMA7455::modeControl() const {
	uint8_t value=0xff;
	return ctrl(Register::MCTL,value) ? value : 0xff;
}

uint8_t MMA7455::status() const {
	uint8_t value=0xff;
	return ctrl(Register::STATUS,value) ? value : 0xff;
}

bool MMA7455::raw(int8_t& x, int8_t& y, int8_t& z) const {
	/* --Check if data is available. */
	while ((status()&0x01)==0);

	uint32_t value;
	if (ctrl(Register::XOUT8,value)) {
		x=value;
		y=value>>8;
		z=value>>16;
		return true;
	}
	return false;
}

}

}

