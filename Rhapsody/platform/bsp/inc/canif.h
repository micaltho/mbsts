/*
 * canif.h
 *
 *  Created on: 13.07.2016
 *      Author: Michael
 */

#ifndef BSP_INC_CANIF_H_
#define BSP_INC_CANIF_H_

#include <cstdint>
#include <functional>

/* --LPCOpen includes. */
#include "chip.h"
#include "board.h"
#include "can_17xx_40xx.h"


namespace Platform {
namespace BSP {

extern "C" void CAN_IRQHandler();

/** @brief Interface to the CAN bus.
 *
 *  This class defines the interface to the CAN bus.
 *  Note: The jumpers J12 and J13 must be set on pins 2-3 in order to use the CAN bus on the EA base board.
 *  Note: Only LPC_CAN2 can be used on the EA base board.
 */

class CAN {
public:

	/**
	 * Defines the message type (short cut of LPCopen struct).
	 */
	using Message = CAN_MSG_T;

	/**
	 * Define interrupt handler type (short cut).
	 */
	using InterruptHandler = std::function<void(uint32_t)>;

	/**
	 * CAN hardware interface.
	 */
	enum class Interface {
		CAN1 =0,	//!< CAN Interface 1
		CAN2 =1		//!< CAN Interface 2
	};

	/**
	 * CAN internal transmit buffer.
	 */
	enum class TransmitBuffer {
		BUFFER1 =CAN_BUFFER_1,	//!< Internal CAN transmit buffer 1
		BUFFER2 =CAN_BUFFER_2,	//!< Internal CAN transmit buffer 2
		BUFFER3 =CAN_BUFFER_3,	//!< Internal CAN transmit buffer 3
		FREE_BUFFER				//!< Any free buffer (1..3)
	};

	/**
	 * CAN interrupt source (see LPC17969 hardware specification).
	 */
	enum Interrupt{
		RECEIVED =CAN_IER_RIE,                //!< RECEIVED
		TRANSMITTED_BUFFER1 =CAN_IER_TIE1,    //!< TRANSMITTED_BUFFER1
		ERROR_WARNING =CAN_IER_EIE,           //!< ERROR_WARNING
		DATA_OVERRUN =CAN_IER_DOIE,           //!< DATA_OVERRUN
		WAKE_UP =CAN_IER_WUIE,                //!< WAKE_UP
		ERROR_PASSIVE =CAN_IER_EPIE,          //!< ERROR_PASSIVE
		ARBITRATION_LOST =CAN_IER_ALIE,       //!< ARBITRATION_LOST
		BUS_ERORR =CAN_IER_BEIE,              //!< BUS_ERORR
		ID_READY =CAN_IER_IDIE,               //!< ID_READY
		TRANSMITTED_BUFFER2 =CAN_IER_TIE2,    //!< TRANSMITTED_BUFFER2
		TRANSMITTED_BUFFER3 =CAN_IER_TIE3,    //!< TRANSMITTED_BUFFER3
		NUM_INTERRUPTS =11,					  //!< NUM_INTERRUPTS
		CAPTURE_ALL = CAN_IER_BITMASK         //!< CAPTURE_ALL
	};

	/**
	 * Mode of operation (see LPC1769 hardware specification).
	 */
	enum class Mode {
		RESET = CAN_RESET_MODE,                        //!< RESET
		SELFTEST = CAN_SELFTEST_MODE,                  //!< SELFTEST
		TEST = CAN_TEST_MODE,                          //!< TEST
		LISTEN_ONLY = CAN_LISTEN_ONLY_MODE,            //!< LISTEN_ONLY
		SLEEP = CAN_SLEEP_MODE,                        //!< SLEEP
		OPERATION = CAN_OPERATION_MODE,                //!< OPERATION
		TRANSMIT_PRIORITY = CAN_TRANSMIT_PRIORITY_MODE,//!< TRANSMIT_PRIORITY
		RECEIVE_PRIORITY = CAN_RECEIVE_PRIORITY_MODE   //!< RECEIVE_PRIORITY
	};


	/**
	 * Constructor.
	 * @param ifc defines the interface connected to
	 * @param speed defines the bus speed in bit/s
	 */
	CAN(Interface ifc =Interface::CAN2, uint32_t speed =500000);

	/**
	 * Destructor.
	 */
	~CAN();

	/*! @cond HIDDEN_DOXYGEN*/

	/**
	 * Forbidden to copy/assign/... any instance of this class.
	 */
	CAN(const CAN&) = delete;
	CAN(CAN&&) = delete;
	CAN& operator=(const CAN&) = delete;
	const CAN& operator=(CAN&&) = delete;
	/*! @endcond */

	/**
	 * Set interrupt handler (can be XOR'ed).
	 * @param irq defines the mask list (see enum Interrupt)
	 * @param handler defines the interrupt handling routine, eg. as lambda expression
	 */
	void set(uint32_t irq, InterruptHandler handler);

	/**
	 * Unset interrupt handler (can by XOR'ed) and disable.
	 * @param irq defines interrupt mask to be unset.
	 */
	void unset(uint32_t irq);

	/**
	 * Enable Interrupt Handling.
	 * @return true if succeeded or false.
	 */
	bool enableInterrupt();

	/**
	 * Send a message using internal buffer (BLOCKING MODE!).
	 * @param msg defines the CAN message to send.
	 * @param useBuffer defines the internal buffer (1..3) to store message.
	 * @return true if sending succeeded or false.
	 */
	bool send(Message& msg, TransmitBuffer useBuffer = TransmitBuffer::FREE_BUFFER);

	/**
	 * Read received message from buffer.
	 * @param msg is copy of message received internal buffer.
	 * @return true if message was received or false.
	 */
	bool receive(Message& msg);

	/**
	 * Check if BusOff (Error).
	 * @return true if CAN bus is in bus off error state or false.
	 */
	bool isBusOff() const;

	/**
	 * Check if ErrorState.
	 * @return true if CAN bus is in error state or false.
	 */
	bool isError() const;

	/**
	 * Get status bits (see LPC1769 hardware specification).
	 * @return bit mask.
	 */
	uint32_t status() const;

	/**
	 * Get global status bits (see LPC1769 hardware specification).
	 * @return bit mask.
	 */
	uint32_t globalstatus() const;

	/**
	 * Get interrupt status bits (see LPC1769 hardware specification).
	 * @return bit mask.
	 */
	uint32_t istatus() const;

	/**
	 * Try to reset CAN bus (after bus off).
	 */
	void reset() const;

	/**
	 * Get current mode.
	 * @return mode enum value.
	 */
	Mode mode() const;

	/**
	 * Set or unset the mode
	 * @param nmode defines the mode
	 * @param isEnable should be true to enable otherwise false to disable the mode.
	 */
	void mode(Mode nmode, bool isEnable =true) const;

protected:

	/**
	 * Ugly but required due to mapping C interrupt to C++.
	 */
	friend void CAN_IRQHandler();

	/**
	 * Interrupt handling and dispatching (THIS IS CALLED WITHIN INTERRUPT CONTEXT!!!).
	 * @param status defines bit mask of triggered interrupts.
	 */
	void handleInterrupt(uint32_t status);

private:

	/**
	 * Internal attributes.
	 */
 	LPC_CAN_T* canif;

 	/**
 	 * Internals for interrupt handling.
 	 */
 	static CAN* handler[2];

 	/**
 	 * Local array of interrupt handlers.
 	 */
 	InterruptHandler canHandler[Interrupt::NUM_INTERRUPTS];
};

}
}



#endif /* BSP_INC_CANIF_H_ */
