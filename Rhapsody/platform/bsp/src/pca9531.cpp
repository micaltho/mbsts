#include "pca9531.h"

namespace Platform {

namespace BSP {

PCA9531::PCA9531(Interface ifc, uint8_t addr):I2CDevice(ifc,addr) {}

void PCA9531::select(uint16_t id, Mode m) const {
    /* --selector data. */
    uint16_t selector=getStatus();

    /* --Configure the selector. */
    for(uint16_t i=0; i<8;i++)
        /* --Enable? */
        if (id&(1<<i)) {
            if (m==ON)
                selector|=(1<<(i*2));
            else
                selector&=~(3<<(i*2));
        }
    setStatus(selector);
}

uint16_t PCA9531::getStatus() const {
    uint16_t value=0;
    uint8_t reg=static_cast<uint8_t>(Register::LS0_AI);
    if (get(reg,value))
        return value;
    else
        return 0xffff;
}


PCA9531::LedState PCA9531::getLedStatus(Identifier led) const
{
    PCA9531::LedState state;
    uint32_t value = getStatus();
    uint32_t count = 0;
    while(led >> count) ++count;  // get number of bit from bit position.
    state = static_cast<LedState>((value >> ((count-1) << 1)) & 0x3);
    return state;

}

void PCA9531::shiftleft(uint32_t pos) const {
    /* --Shift. */
    setStatus(getStatus()<<(pos*2));
}

void PCA9531::shiftright(uint32_t pos) const {
    /* --Shift. */
    setStatus(getStatus()>>(pos*2));
}

void PCA9531::rotateleft(uint32_t pos) const {
    uint32_t n=getStatus();
    /* --Rotate. */
    setStatus(n<<(pos*2)|n>>(32-pos*2));
}

void PCA9531::rotateright(uint32_t pos) const {
    uint32_t n=getStatus();
    /* --Rotate. */
    setStatus(n>>(pos*2)|n<<(32-pos*2));
}

}

}
