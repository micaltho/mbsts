/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: LPCAccelerationSensor
//!	Generated Date	: Thu, 4, Aug 2022  
	File Path	: LPC1769/DefaultConfig/LPCAccelerationSensor.cpp
*********************************************************************/

#include "LPCAccelerationSensor.h"
//## package LPC1769

//## class LPCAccelerationSensor
LPCAccelerationSensor::LPCAccelerationSensor(void) : accelerationX(0), accelerationY(0), accelerationZ(0), itsMMA7455() {
    //#[ operation LPCAccelerationSensor()
    itsMMA7455.control();
    //#]
}

LPCAccelerationSensor::~LPCAccelerationSensor(void) {
}

std::int32_t LPCAccelerationSensor::readAccelerationX(void) {
    //#[ operation readAccelerationX()
    return accelerationX;
    //#]
}

std::int32_t LPCAccelerationSensor::readAccelerationY(void) {
    //#[ operation readAccelerationY()
    return accelerationY;
    //#]
}

std::int32_t LPCAccelerationSensor::readAccelerationZ(void) {
    //#[ operation readAccelerationZ()
    return accelerationZ;
    //#]
}

void LPCAccelerationSensor::readXYZ(void) {
    //#[ operation readXYZ()
    itsMMA7455.raw(accelerationX, accelerationY, accelerationZ);
    //#]
}

std::int8_t LPCAccelerationSensor::getAccelerationX(void) const {
    return accelerationX;
}

void LPCAccelerationSensor::setAccelerationX(const std::int8_t p_accelerationX) {
    accelerationX = p_accelerationX;
}

std::int8_t LPCAccelerationSensor::getAccelerationY(void) const {
    return accelerationY;
}

void LPCAccelerationSensor::setAccelerationY(const std::int8_t p_accelerationY) {
    accelerationY = p_accelerationY;
}

std::int8_t LPCAccelerationSensor::getAccelerationZ(void) const {
    return accelerationZ;
}

void LPCAccelerationSensor::setAccelerationZ(const std::int8_t p_accelerationZ) {
    accelerationZ = p_accelerationZ;
}

Platform::BSP::MMA7455* LPCAccelerationSensor::getItsMMA7455(void) const {
    return (Platform::BSP::MMA7455*) &itsMMA7455;
}

/*********************************************************************
	File Path	: LPC1769/DefaultConfig/LPCAccelerationSensor.cpp
*********************************************************************/
