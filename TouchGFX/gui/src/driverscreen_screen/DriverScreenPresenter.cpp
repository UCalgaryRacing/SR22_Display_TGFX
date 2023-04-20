#include <gui/driverscreen_screen/DriverScreenView.hpp>
#include <gui/driverscreen_screen/DriverScreenPresenter.hpp>
#include "main.h"

DriverScreenPresenter::DriverScreenPresenter(DriverScreenView& v)
    : view(v)
{

}

void DriverScreenPresenter::activate()
{

}

void DriverScreenPresenter::deactivate()
{

}

void DriverScreenPresenter::updateGear(uint8_t value){
	view.updateGear(value);
}

void DriverScreenPresenter::updateRPM(uint16_t value){
	view.updateRPM(value);
}

void DriverScreenPresenter::updateLeftDataField1(float value){
	view.updateLeftDataField1(value);
}

void DriverScreenPresenter::updateLeftDataField2(uint8_t value){
	view.updateLeftDataField2(value);
}

void DriverScreenPresenter::updateLeftDataField3(float value){
	view.updateLeftDataField3(value);
}


void DriverScreenPresenter::updateRightDataField1(float value){
	view.updateRightDataField1(value);
}

void DriverScreenPresenter::updateRightDataField2(int16_t value){
	view.updateRightDataField2(value);
}

void DriverScreenPresenter::updateRightDataField3(uint16_t value){
	view.updateRightDataField3(value);
}

void DriverScreenPresenter::updateBatteryLow(bool state){
	view.updateBatteryLow(state);
}

void DriverScreenPresenter::updateCoolantHigh(bool state){
	view.updateCoolantHigh(state);
}

