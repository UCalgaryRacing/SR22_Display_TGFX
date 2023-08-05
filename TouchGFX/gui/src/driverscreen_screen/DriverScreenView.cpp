#include <gui/driverscreen_screen/DriverScreenView.hpp>

#include "main.h"
#include "can.h"
#include "usart.h"
extern "C"{
	extern osMessageQueueId_t buttonQueueHandle;
	extern osMessageQueueId_t shifterQueueHandle;
	extern driverScreenData_t *driverScreenData_q;
	extern uint8_t gpsData[UARTBUFFERLENGTH];
	extern uint32_t lapTimeMilliSeconds;
	uint8_t x = 0;
	uint8_t adcGear_q = 0;
}
bool batteryState = false;
bool coolantState = false;
double thing = 0;

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
//			updateGear(adcGear_q);
		}
	}

	updateGear(driverScreenData_q->gear);
	updateRPM(driverScreenData_q->rpm);
	updateLapTimer(lapTimeMilliSeconds);
	updateLeftDataField1(driverScreenData_q->leftDataField1);
	updateLeftDataField2(driverScreenData_q->leftDataField2);
	updateRightDataField1(driverScreenData_q->rightDataField1);
	updateRightDataField2(driverScreenData_q->rightDataField2);
}


void DriverScreenView::updateGear(uint8_t value){
	if(value == 0){
		Unicode::snprintf(tbGearBuffer, TBGEAR_SIZE, "%c", 'N');
	}else{
		Unicode::snprintf(tbGearBuffer, TBGEAR_SIZE, "%d", value);
	}
	tbGear.invalidate();
}

void DriverScreenView::updateLapTimer(uint32_t timeMilliSeconds){
	uint32_t minutes = timeMilliSeconds / 60000;
	float seconds = (float)(timeMilliSeconds % 60000) / 1000;
	Unicode::snprintf(tbLapTimerBuffer1, TBLAPTIMERBUFFER1_SIZE, "%d", minutes);
	Unicode::snprintfFloat(tbLapTimerBuffer2, TBLAPTIMERBUFFER2_SIZE, "%.3f", seconds);
	tbLapTimer.invalidate();
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

void DriverScreenView::updateRightDataField1(float value){
	Unicode::snprintfFloat(tbRightDataFieldData1Buffer, TBRIGHTDATAFIELDDATA1_SIZE, "%03.2f", value);
	tbRightDataFieldData1.invalidate();
}

void DriverScreenView::updateRightDataField2(int16_t value){
	Unicode::snprintf(tbRightDataFieldData2Buffer, TBRIGHTDATAFIELDDATA2_SIZE, "%d", value);
	tbRightDataFieldData2.invalidate();
}


