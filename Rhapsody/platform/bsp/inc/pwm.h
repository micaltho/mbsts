/**
 *  \brief     PWM definition / pwm.h
 *  \details   This class defines the interface to PWM1 for the PWM pins 1 to 6.\n
 *  of type \ref Platform::BSP::PWM
 *
 *  \author    R. Hagemann
 *  \version   1.0
 *  \date      17.10.2016
 *  \copyright HS Osnabrueck
 */

/** @file */
#ifndef PWM_H
#define PWM_H



/* --Platform includes. */

#include "board.h"

/* --BSP includes. */
#include "PortPin.h"

namespace Platform {

namespace BSP {

/*! @brief \class PWM pwm.h  "inc/pwm.h"
 *
 *  \brief This class defines the pwm.\n
 *  it can be used for the six pwm channels PWM1.1 - PWM1.6\n
 *  \note For the time being, only PWM_SINGLE_EDGE_CONTROL_MODE is supported
 *
 *  \note USAGE:\n
 *  Special care must be taken to call init methods in the right order:\n
 *  FIRST call \ref Chip_PWM_SetFrequency() This method deactivates PWM timer!\n
 *  THEN call \ref Chip_PWM_Enable() This method activates PWM timer\n
 *  FINALLY call \ref Chip_PWM_OutputEnable() to enable your channel.\n
 *  After initialization, other channels just call \ref Chip_PWM_OutputEnable()\n
 */

class PWM {
public:
	/*! \enum PWM_CHANNEL
	 * Possible channels of PWM
	 */
    typedef enum
    {
        PWM11=1,        //!< Channel 1.1, using P2.0
        PWM12=2,        //!< Channel 1.2, using P2.1
        PWM13=3,        //!< Channel 1.3, using P2.2
        PWM14=4,        //!< Channel 1.4, using P2.3
        PWM15=5,        //!< Channel 1.5, using P2.4
        PWM16=6         //!< Channel 1.6, using P2.5
    }PWM_CHANNEL;

public:
    /*! @brief Constructor
     * @param[in] pwmch channel to be used
     * @param[in] minPercent minimal value of duty cycle in percent
     * @param[in] maxPercent maximal value of duty cycle in percent
     *
     */
    PWM(PWM_CHANNEL pwmch, uint8_t minPercent=25, uint8_t maxPercent=100);

    /*! @brief Destructor disables this PWM channel
     *
     */
    ~PWM();

public:
    /*! @brief Resets all PWM registers
     * \warning be careful, this will effect all PWM channels!
     */
    void Chip_PWM_Reset(void);


    /*! @brief Stops PWM timer
     * \warning be careful, this will effect all PWM channels!
     */
    void Chip_PWM_Disable(void);

    /*! @brief Starts PWM timer
     * \warning be careful, this will effect all PWM channels!
     */
    void Chip_PWM_Enable(void);

    /*! @brief Enables PWM for this channel
     *
     */
    void Chip_PWM_OutputEnable(void);

    /*! @brief Disables PWM for this channel
     *
     */
    void Chip_PWM_OutputDisable(void);

    /*! @brief Sets PWM base frequency
     * \warning be careful, this will effect all PWM channels!
     * @param[in] data frequency in Hz
     */
    void Chip_PWM_SetFrequency(uint32_t data);


    /*! @brief Sets PWM duty cycle in percent for this channel
     * @param[in] data duty cycle in percent
     */
    void Chip_PWM_SetPulsWidthPercent(uint32_t data);

    /*! @brief Sets PWM duty cycle for this channel\n
     * value in set in given limits between minPercent and maxPercent
     * @param[in] data duty cycle as absolute value
     */
    void Chip_PWM_SetPulsWidth(uint32_t data);


    /*! @brief Gets PWM base frequency
     * @returns PWM frequency in Hz
     */
    uint32_t Chip_PWM_GetFrequency    (void) const;

    /*! @brief Gets PWM duty cycle of this channel
     * @returns PWM duty cycle in percent
     */
    uint32_t Chip_PWM_GetPulsWidth    (void) const;

    /*! @brief Gets minimal percentage of duty cycle (internal limitation)
     * @returns minimal duty cycle in Hz
     */
    uint8_t  Chip_PWM_GetMinPercent    (void) const { return m_minPercent; };

    /*! @brief Gets maximal percentage of duty cycle (internal limitation)
     * @returns minimal duty cycle in Hz
     */
    uint8_t  Chip_PWM_GetMaxPercent    (void) const { return m_maxPercent; };

private:
    /**
     * @brief PWM register block
     */
    typedef struct {
            __IO uint32_t IR;               /*!< Interrupt Register. The IR can be written to clear interrupts. The IR can be read to identify which of eight possible interrupt sources are pending. */
            __IO uint32_t TCR;              /*!< Timer Control Register. The TCR is used to control the Timer Counter functions. The Timer Counter can be disabled or reset through the TCR. */
            __IO uint32_t TC;               /*!< Timer Counter. The 32 bit TC is incremented every PR+1 cycles of PCLK. The TC is controlled through the TCR. */
            __IO uint32_t PR;               /*!< Prescale Register. The Prescale Counter (below) is equal to this value, the next clock increments the TC and clears the PC. */
            __IO uint32_t PC;               /*!< Prescale Counter. The 32 bit PC is a counter which is incremented to the value stored in PR. When the value in PR is reached, the TC is incremented and the PC is cleared. The PC is observable and controllable through the bus interface. */
            __IO uint32_t MCR;              /*!< Match Control Register. The MCR is used to control if an interrupt is generated and if the TC is reset when a Match occurs. */
            __IO uint32_t MR0;              /*!< Match Register 0. MR0 can be enabled in the MCR to reset the TC, stop
                                             *  both the TC and PC, and/or generate an interrupt when it matches the TC.
                                             *  In addition, a match between this value and the TC sets any PWM output
                                             *  that is in single-edge mode, and sets PWM1 if it’s in double-edge mode.
                                            */
            __IO uint32_t MR1;              /*!< Match Register 1. MR1 can be enabled in the MCR to reset the TC, stop
                                             *  both the TC and PC, and/or generate an interrupt when it matches the TC.
                                             *  In addition, a match between this value and the TC clears PWM1 in either
                                             *  edge mode, and sets PWM2 if it’s in double-edge mode.
                                            */
            __IO uint32_t MR2;              /*!< Match Register 2. MR2 can be enabled in the MCR to reset the TC, stop
                                             *  both the TC and PC, and/or generate an interrupt when it matches the TC.
                                             *  In addition, a match between this value and the TC clears PWM2 in either
                                             *  edge mode, and sets PWM3 if it’s in double-edge mode.
                                            */
            __IO uint32_t MR3;              /*!< Match Register 3. MR3 can be enabled in the MCR to reset the TC, stop
                                             *  both the TC and PC, and/or generate an interrupt when it matches the TC.
                                             *  In addition, a match between this value and the TC clears PWM3 in either
                                             *  edge mode, and sets PWM4 if it’s in double-edge mode.
                                            */
            __IO uint32_t CCR;              /*!< Capture Control Register. The CCR controls which edges of the capture inputs are used to load the Capture Registers and whether or not an interrupt is generated when a capture takes place. */
            __IO uint32_t CR[4];            /*!< Capture Register. CR is loaded with the value of TC when there is an event on the CAPn.0 input. */
            /// \cond reserved address space
            __IO uint32_t RESERVED;
            /// \endcond
            __IO uint32_t MR4;              /*!< Match Register 4. MR4 can be enabled in the MCR to reset the TC, stop
                                             *  both the TC and PC, and/or generate an interrupt when it matches the TC.
                                             *  In addition, a match between this value and the TC clears PWM4 in either
                                             *  edge mode, and sets PWM5 if it’s in double-edge mode.
                                            */
            __IO uint32_t MR5;              /*!< Match Register 5. MR5 can be enabled in the MCR to reset the TC, stop
                                             *  both the TC and PC, and/or generate an interrupt when it matches the TC.
                                             *  In addition, a match between this value and the TC clears PWM5 in either
                                             *  edge mode, and sets PWM6 if it’s in double-edge mode. */
            __IO uint32_t MR6;              /*!< Match Register 6. MR6 can be enabled in the MCR to reset the TC, stop
                                             *  both the TC and PC, and/or generate an interrupt when it matches the TC.
                                             *  In addition, a match between this value and the TC clears PWM6 in either
                                             *  edge mode.
                                            */
            __IO uint32_t PCR;              /*!< PWM Control Register. Enables PWM outputs and selects PWM channel types as either single edge or double edge controlled. */
            __IO uint32_t LER;              /*!< Load Enable Register. Enables use of new PWM match values. */
            __IO uint32_t CTCR;             /*!< Count Control Register. The CTCR selects between Timer and Counter mode, and in Counter mode selects the signal and edge(s) for counting. */
    } LPC_PWM_T;

    /**
    * @brief PWM Edge mode
    */
    typedef enum
    {
     PWM_SINGLE_EDGE_CONTROL_MODE=0,        ///< MR0 is used for set and MRx for reset of PWM pin
     PWM_DOUBLE_EDGE_CONTROL_MODE=1,        ///< MR(x-1) is used for set and MRx for reset  of PWM pin
    }PWM_EDGE_CONTROL_MODE;

    /**
    * @brief PWM enable
    */
    typedef enum
    {
        PWM_OUT_DISABLED=0,   ///< Disable PWM
        PWM_OUT_ENABLED=1,    ///< Enable PWM
    }PWM_OUT_CMD;


    /**
    * @brief Match Register Config
    */
    typedef enum
    {
        PWM_MR_ENABLE_INTERRUPT = 1,  ///< an interrupt is generated when MRx matches
		                              ///  the value in the TC
		PWM_MR_RESET_ON_MATCH   = 2,  ///< the TC will be reset if MRx matches it
		PWM_MR_STOP_ON_MATCH    = 4,  ///< the TC and PC will be stopped and TCR[0] will be
		                              ///  set to 0 if MRx matches the TC
    } PWM_MATCH_CONTROL;


    PWM_CHANNEL    m_channel;
    __IO uint32_t* m_mr;
    uint32_t       m_port;
    uint32_t       m_pin;
    uint8_t        m_maxPercent;     ///< maximum percentage of duty cycle!
    uint8_t        m_minPercent;     ///< minimum percentage of duty cycle!

    void Chip_PWM_Init();

    void Chip_PWM_SetMCR(uint8_t matchReg, PWM_MATCH_CONTROL data);
    void Chip_PWM_ResetMCR(uint8_t matchReg, PWM_MATCH_CONTROL data);
    void Chip_PWM_SetPrescale(uint32_t data);
    uint32_t Chip_PWM_GetPrescale (void) const;
};

}    // of namespace BSP
}    // of namespace Platform
#endif /* PWM_H */
