/**
 *  \brief     PWM implementation / pwm.c
 *  \details   This class defines the interface to PWMund the PWM pins 1 to 6.\n
 *  of type \ref Platform::BSP::PWM
 *
 *  \author    R. Hagemann
 *  \version   1.0
 *  \date      17.10.2016
 *  \copyright HS Osnabrueck
 */

#include "digitalinout.h"


#include <pwm.h>
#include "gpio_17xx_40xx.h"

using GPIO = Platform::BSP::DigitalInOut;


#define PWM11_PORT           2
#define PWM11_PIN            0    // PWM1.1 GPIO_28
#define PWM12_PORT           2
#define PWM12_PIN            1    // PWM1.2 GPIO_29
#define PWM13_PORT           2
#define PWM13_PIN            2    // PWM1.3 GPIO_30
#define PWM14_PORT           2
#define PWM14_PIN            3    // PWM1.4 GPIO_31
#define PWM15_PORT           2
#define PWM15_PIN            4    // PWM1.5 GPIO_32
#define PWM16_PORT           2
#define PWM16_PIN            5    // PWM1.6 GPIO_33


/** Timer/counter enable bit */
#define PWM_TIM_ENABLE        ((uint32_t) (1 << 0))
/** Timer/counter reset bit */
#define PWM_TIM_RESET         ((uint32_t) (1 << 1))

/** Timer/counter enable bit */
#define PWM_ENABLE            ((uint32_t) (1 << 3))
/** Timer/counter reset bit */
#define PWM_RESET             ((uint32_t) (1 << 3))



#define LPC_PWM1 ((Platform::BSP::PWM::LPC_PWM_T*) LPC_PWM1_BASE)
#define LPC_PWM     LPC_PWM1



namespace Platform {
namespace BSP {

PWM::PWM(PWM_CHANNEL pwmch,
         uint8_t     minPercent,
         uint8_t     maxPercent) :
   m_channel(pwmch),
   m_mr(0),
   m_maxPercent(maxPercent),
   m_minPercent(minPercent)

{
    Chip_PWM_Init();
    Chip_PWM_Reset();

    // MR0 will reset timer:
    Chip_PWM_SetMCR(0, PWM_MR_RESET_ON_MATCH);
}

PWM::~PWM() {
    Chip_PWM_OutputDisable();
}

void PWM::Chip_PWM_Init()
{
    switch( m_channel ){
        case PWM11: m_port = PWM11_PORT; m_pin = PWM11_PIN; m_mr = &(LPC_PWM->MR1); break;
        case PWM12: m_port = PWM12_PORT; m_pin = PWM12_PIN; m_mr = &(LPC_PWM->MR2); break;
        case PWM13: m_port = PWM13_PORT; m_pin = PWM13_PIN; m_mr = &(LPC_PWM->MR3); break;
        case PWM14: m_port = PWM14_PORT; m_pin = PWM14_PIN; m_mr = &(LPC_PWM->MR4); break;
        case PWM15: m_port = PWM15_PORT; m_pin = PWM15_PIN; m_mr = &(LPC_PWM->MR5); break;
        case PWM16: m_port = PWM16_PORT; m_pin = PWM16_PIN; m_mr = &(LPC_PWM->MR6); break;
    }
    GPIO pwm(m_port, m_pin, GPIO::Direction::OUTPUT);
    Chip_IOCON_PinMuxSet( LPC_IOCON, m_port, m_pin, IOCON_FUNC1 | IOCON_MODE_INACT);      // UM10360.pdf Seite 119
    LPC_SYSCTL->PCONP |= (1 << SYSCTL_CLOCK_PWM1);
    *m_mr = 0;
}

void PWM::Chip_PWM_Reset(void)
{
    LPC_PWM->TCR = 0x00;
    LPC_PWM->TC  = 0x01;
    LPC_PWM->PC  = 0x00;
/*
    LPC_PWM->PR  = 0x00;
    LPC_PWM->PCR = 0x00;
    LPC_PWM->MCR = 0x00;
*/
    LPC_PWM->TCR = PWM_TIM_RESET;
    while (LPC_PWM->TC != 0);

    LPC_PWM->TCR = 0x00;
}

void PWM::Chip_PWM_Disable(void)
{
//    LPC_PWM->TCR = 0x00;
    LPC_PWM->TCR &= ~PWM_TIM_RESET;
    LPC_PWM->TCR |=  PWM_RESET;
}

void PWM::Chip_PWM_Enable(void)
{
//    LPC_PWM->TCR = 0x01;
    LPC_PWM->TCR |=  PWM_TIM_ENABLE;
    LPC_PWM->TCR &= ~PWM_ENABLE;

}

void PWM::Chip_PWM_OutputEnable(void)
{
    LPC_PWM->PCR |= 1<< (8 + m_channel);
}

void PWM::Chip_PWM_OutputDisable(void)
{
    LPC_PWM->PCR &= ~(1<< (8 + m_channel));
}

void PWM::Chip_PWM_SetPrescale(uint32_t data)
{
    LPC_PWM->TCR = 0x02;
    while (LPC_PWM->TC != 0);
    LPC_PWM->PR  = data;
    LPC_PWM->TCR = 0x00;
}

uint32_t PWM::Chip_PWM_GetPrescale(void) const{
    return LPC_PWM->PR;
}

void PWM::Chip_PWM_SetFrequency(uint32_t data) // in Hz
{
    LPC_PWM->TCR = 0x02;
    while (LPC_PWM->TC != 0);
    Chip_PWM_SetPrescale(0);

    // set PWMCLK to CCLK! Per default, PWMCLK = CCLK / 4
    Chip_Clock_SetPCLKDiv(SYSCTL_PCLK_PWM1, SYSCTL_CLKDIV_1);

    LPC_PWM->MR0 = Chip_Clock_GetSystemClockRate() / data;
    LPC_PWM->TCR = 0x00;
}


uint32_t PWM::Chip_PWM_GetFrequency(void) const{
    return Chip_Clock_GetSystemClockRate() / LPC_PWM->MR0 / 4;
}


void PWM::Chip_PWM_SetPulsWidthPercent(uint32_t data)
{
    if (data<m_minPercent) data=m_minPercent;
    if (data>m_maxPercent) data=m_maxPercent;
    *m_mr = (LPC_PWM->MR0-1)*data / 100;
}

void PWM::Chip_PWM_SetPulsWidth(uint32_t data)
{
    uint32_t minval =  LPC_PWM->MR0      * m_minPercent / 100;
    uint32_t maxval = (LPC_PWM->MR0 - 1) * m_maxPercent / 100;
    if (data<minval) data=minval;
    if (data>maxval) data=maxval;
    *m_mr = data;
}


uint32_t PWM::Chip_PWM_GetPulsWidth(void) const{
    return 100 * *m_mr / LPC_PWM->MR0;
}

void PWM::Chip_PWM_SetMCR(uint8_t matchReg, PWM_MATCH_CONTROL data)
{
    LPC_PWM->TCR = 0x02;
    while (LPC_PWM->TC != 0);
    LPC_PWM->MCR |= (data << (matchReg *3));
    LPC_PWM->TCR = 0x00;
}

void PWM::Chip_PWM_ResetMCR(uint8_t matchReg, PWM_MATCH_CONTROL data)
{
    LPC_PWM->TCR = 0x02;
    while (LPC_PWM->TC != 0);
    LPC_PWM->MCR &= ~(data << (matchReg *3));
    LPC_PWM->TCR = 0x00;
}

}    // of namespace BSP
}    // of namespace Platform
