#include <gui/driverscreen_screen/DriverScreenView.hpp>

#include "main.h"
#include "can.h"
extern "C"{
	extern osMessageQueueId_t buttonQueueHandle;
	extern osMessageQueueId_t shifterQueueHandle;
	extern driverScreenData_t *driverScreenData_q;
	uint8_t x = 0;
	uint8_t adcGear_q = 0;
}
bool batteryState = false;
bool coolantState = false;

DriverScreenView::DriverScreenView()
{

}

void DriverScreenView::setupScreen()
{
    DriverScreenViewBase::setupScreen();
}

void DriverScreenView::tearDownScreen()
{
    DriverScreenViewBase::tearDownScreen();
}

void DriverScreenView::UpdateDriverScreen(){
	if(osMessageQueueGetCount(buttonQueueHandle) > 0){
		if(osMessageQueueGet(buttonQueueHandle, &x, 0, 0) == osOK){
			handleKeyEvent(0);
		}
	}
	if(osMessageQueueGetCount(shifterQueueHandle) > 0){
		if(osMessageQueueGet(shifterQueueHandle, &adcGear_q, 0, 0) == osOK){
			updateGear(adcGear_q);
		}
	}
//	updateGear(driverScreenData_q->gear);
	updateRPM(driverScreenData_q->rpm);
	updateLeftDataField1(driverScreenData_q->leftDataField1);
	updateLeftDataField2(driverScreenData_q->leftDataField2);
	updateLeftDataField3(driverScreenData_q->leftDataField3);
	updateRightDataField1(driverScreenData_q->rightDataField1);
	updateRightDataField2(driverScreenData_q->rightDataField2);
	updateRightDataField3(driverScreenData_q->rightDataField3);
	if(batteryState != driverScreenData_q->batteryLow){
		updateBatteryLow(driverScreenData_q->batteryLow);
		batteryState = driverScreenData_q->batteryLow;
	}
	if(coolantState != driverScreenData_q->coolantHigh){
		updateCoolantHigh(driverScreenData_q->coolantHigh);
		coolantState = driverScreenData_q->coolantHigh;
	}
}


void DriverScreenView::updateGear(uint8_t value){
	Unicode::snprintf(tbGearBuffer, TBGEAR_SIZE, "%d", value);
	tbGear.invalidate();
}

void DriverScreenView::updateRPM(uint16_t value){
	Unicode::snprintf(tbRPMBuffer, TBRPM_SIZE, "%d", value);
	tbRPM.invalidate();
}

void DriverScreenView::updateLeftDataField1(float value){
	Unicode::snprintfFloat(tbLeftDataFieldData1Buffer, TBLEFTDATAFIELDDATA1_SIZE, "%03.2f", value);
	tbLeftDataFieldData1.invalidate();
}

void DriverScreenView::updateLeftDataField2(uint8_t value){
	Unicode::snprintf(tbLeftDataFieldData2Buffer, TBLEFTDATAFIELDDATA2_SIZE, "%d", value);
	tbLeftDataFieldData2.invalidate();
}

void DriverScreenView::updateLeftDataField3(float value){
	Unicode::snprintfFloat(tbLeftDataFieldData3Buffer, TBLEFTDATAFIELDDATA3_SIZE, "%03.2f", value);
	tbLeftDataFieldData3.invalidate();
}


void DriverScreenView::updateRightDataField1(float value){
	Unicode::snprintfFloat(tbRightDataFieldData1Buffer, TBRIGHTDATAFIELDDATA1_SIZE, "%03.2f", value);
	tbRightDataFieldData1.invalidate();
}

void DriverScreenView::updateRightDataField2(int16_t value){
	Unicode::snprintf(tbRightDataFieldData2Buffer, TBRIGHTDATAFIELDDATA2_SIZE, "%d", value);
	tbRightDataFieldData2.invalidate();
}

void DriverScreenView::updateRightDataField3(uint16_t value){
	Unicode::snprintf(tbRightDataFieldData3Buffer, TBRIGHTDATAFIELDDATA3_SIZE, "%d", value);
	tbRightDataFieldData3.invalidate();
}

void DriverScreenView::updateBatteryLow(bool state){
	iconBatteryLow.setVisible(state);
	iconBatteryLow.invalidate();
}

void DriverScreenView::updateCoolantHigh(bool state){
	iconCoolantHigh.setVisible(state);
	iconCoolantHigh.invalidate();
}

