/*
 * systeminfo.h
 *
 *  Created on: 28.06.2016
 *      Author: Michael
 */

#ifndef BSP_INC_SYSTEMINFO_H_
#define BSP_INC_SYSTEMINFO_H_

/*! @cond HIDDEN_DOXYGEN*/

#include <string>

namespace Platform {

class SystemInformation {
public:

	static std::string rtos();

	static std::string fatfs();

	static std::string build();

	static std::string compiler();

	static std::string hal();

	static std::string mac();

	static void print();

};

};

/*! @endcond */

#endif /* BSP_INC_SYSTEMINFO_H_ */
