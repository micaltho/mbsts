#include "interrupt.h"

#include "chip.h"

namespace Platform {

namespace BSP {

DigitalInOut::InterruptHandler InterruptManager::handler[NHANDLER] = {nullptr};

InterruptManager::InterruptManager() {
    /* --Setup internals. */
    Chip_GPIOINT_Init(LPC_GPIOINT);
    // set all handlers to failure to catch uninitialized interrupt
    for(size_t i = 0; i < NHANDLER; ++i)
    {
       if(handler[i] == nullptr)
       {
            handler[i] = failure;
       }
    }
}

void InterruptManager::failure(uint32_t t)
{
    (void)t; // to avoid compiler warnings
    /* --This should never happen. */
    while(true);
}


void InterruptManager::resolve() {
    /* --Check Port 0. */
    if (Chip_GPIOINT_IsIntPending(LPC_GPIOINT,GPIOINT_PORT0))
        resolve(GPIOINT_PORT0, 0, PORT0_NHANDLER);

    /* --Check Port 2. */
    if (Chip_GPIOINT_IsIntPending(LPC_GPIOINT,GPIOINT_PORT2))
        resolve(GPIOINT_PORT2, PORT0_NHANDLER, PORT2_NHANDLER);
}

void InterruptManager::resolve(LPC_GPIOINT_PORT_T port, uint32_t offset, NUMOFHANDLER numOfHandler)
{
    uint32_t clear=0;
    /* --Check if rising edge interrupt is enabled. */
    uint32_t status = Chip_GPIOINT_GetStatusRising(LPC_GPIOINT, port);
    if(status)
    {
      for(uint32_t pin=0;pin<numOfHandler;pin++)
      {
          if ( ((status >> pin) & 0x1) ==ENABLE)
          {
              /* --Invoke the handler (hopefully it has been defined...) */
              handler[offset+pin](DigitalInOut::RISING_EDGE);
              /* --Clear the interrupt. */
              clear|=(1<<pin);
          }
      }
    }

    /* --Check if falling edge interrupt is enabled. */
    status = Chip_GPIOINT_GetStatusFalling(LPC_GPIOINT, port);
    if(status)
    {
      for(uint32_t pin=0;pin<numOfHandler;pin++)
      {
          if ( ((status >> pin) & 0x1) ==ENABLE)
          {
              /* --Invoke the handler (hopefully it has been defined...) */
              handler[offset+pin](DigitalInOut::FALLING_EDGE);
              /* --Clear the interrupt. */
              clear|=(1<<pin);
          }
      }
    }

    Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, port ,clear);
}

bool InterruptManager::attach(const DigitalInOut& gpio, const DigitalInOut::InterruptHandler& ih) const {
    bool retValue=true;
    /* --Check port/pin of given GPIO. */
    if (isInterruptible(gpio.getPort(),gpio.getPort())) {
        /* --Port 0. */
        if (gpio.getPort()==0)
            /* --Set handler. */
            handler[gpio.getPin()]=ih;
        else
            /* --Set handler. */
            handler[gpio.getPin()+PORT0_NHANDLER]=ih;
    }
    else
        retValue=false;

    return retValue;
}

bool InterruptManager::detach(const DigitalInOut& gpio) const {
    bool retValue=false;
    size_t toRelease = NHANDLER;
    /* --Check port/pin of given GPIO. */
    if (isInterruptible(gpio.getPort(),gpio.getPort())) {
        /* --Port 0. */
        if (gpio.getPort()==0) {
            toRelease = gpio.getPin();
        }
        else {
            toRelease = gpio.getPin()+PORT0_NHANDLER;
        }
        if (toRelease < NHANDLER) {
            /* --release handler. */
            handler[toRelease] = failure;
            retValue = true;
        }
    }

    return retValue;
}


bool InterruptManager::enable(const DigitalInOut& gpio, uint32_t edge) const {
    bool retValue=true;
    /* --Check port/pin of given GPIO. */
    if (isInterruptible(gpio.getPort(),gpio.getPin())) {
        // get state of Interrupt and mask new bit...
        uint32_t myMask = 1<< gpio.getPin();

        if (isTrigger(edge,DigitalInOut::FALLING_EDGE))
        {
          uint32_t actualIntMask = Chip_GPIOINT_GetIntFalling(LPC_GPIOINT, getIntPort(gpio.getPort()));
          actualIntMask |= myMask;
          Chip_GPIOINT_SetIntFalling(LPC_GPIOINT, getIntPort(gpio.getPort()),actualIntMask);
        }

        if (isTrigger(edge,DigitalInOut::RISING_EDGE))
        {
          uint32_t actualIntMask = Chip_GPIOINT_GetIntRising(LPC_GPIOINT, getIntPort(gpio.getPort()));
          actualIntMask |= myMask;
          Chip_GPIOINT_SetIntRising(LPC_GPIOINT, getIntPort(gpio.getPort()),actualIntMask);
        }
    }
    else
        retValue=false;

    return retValue;
}

bool InterruptManager::disable(const DigitalInOut& gpio) const {
    bool retValue=true;
    /* --Check port/pin of given GPIO. */
    if (isInterruptible(gpio.getPort(),gpio.getPort())) {
        // get state of Interrupt and mask new bit...
        uint32_t myMask = 1<< gpio.getPin();

        /* --Disable falling _and_ rising edge. */
        uint32_t actualIntMask = Chip_GPIOINT_GetIntFalling(LPC_GPIOINT, getIntPort(gpio.getPort()));
        actualIntMask &= ~myMask;
        Chip_GPIOINT_SetIntFalling(LPC_GPIOINT, getIntPort(gpio.getPort()),actualIntMask);

        actualIntMask = Chip_GPIOINT_GetIntRising(LPC_GPIOINT, getIntPort(gpio.getPort()));
        actualIntMask &= ~myMask;
        Chip_GPIOINT_SetIntRising(LPC_GPIOINT, getIntPort(gpio.getPort()),actualIntMask);

    }
    else
        retValue=false;

    return retValue;
}

bool InterruptManager::clear(const DigitalInOut& gpio) const {
    bool retValue=true;
    /* --Check port/pin of given GPIO. */
    if (isInterruptible(gpio.getPort(),gpio.getPort())) {
        LPC_GPIOINT_PORT_T port = (gpio.getPort() == 0) ? GPIOINT_PORT0 : GPIOINT_PORT2;
        uint32_t pin   = gpio.getPin();
        uint32_t clear = (1<<pin);
        Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, port ,clear);

    }
    else
        retValue=false;

    return retValue;
}



void InterruptManager::enable() {
    // if FreeRTOS is used, Priority must be numerically higher than configMAX_SYSCALL_INTERRUPT_PRIORITY
    // This will allow the usage of OS calls in interrupt.
    // If FreeRTOS is not used or there is no RTOS functionality in ISR, you might increase priority
    NVIC_SetPriority(EINT3_IRQn, 6);

    NVIC_EnableIRQ(EINT3_IRQn);
}




void InterruptManager::disable() {
    NVIC_DisableIRQ(EINT3_IRQn);
}


}     // end of namespace BSP

}     // end of namespace Platform

/* --Bind the interrupt manager to global interrupt handler. */

extern "C" void EINT3_IRQHandler(void) { Platform::BSP::InterruptManager::resolve(); }
