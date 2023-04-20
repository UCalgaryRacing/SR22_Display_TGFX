#include <gui/driverscreen_screen/DriverScreenView.hpp>
#include "main.h"

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

void DriverScreenView::updateGear(uint8_t value){
	Unicode::snprintf(tbGearBuffer, TBGEAR_SIZE, "%d", value);
	tbRPM.invalidate();
}

void DriverScreenView::updateRPM(uint16_t value){
	Unicode::snprintf(tbRPMBuffer, TBRPM_SIZE, "%d", value);
	tbGear.invalidate();
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

