#include <gui/suspensionscreen_screen/SuspensionScreenView.hpp>
#include "main.h"
#include "can.h"
#include "usart.h"
extern "C"{
		extern osMessageQueueId_t buttonQueueHandle;
//		extern osMessageQueueId_t driverDataQueueHandle;
		extern uint16_t rpm;
//		extern driverScreenData_t *driverScreenData_q;
		extern double flPot;
		extern double frPot;
		extern double rlPot;
		extern double rrPot;
		extern double frontBreak;
		extern double rearBreak;


		extern uint8_t gpsData[UARTBUFFERLENGTH];

//		driverScreenData_t *driverScreenData_r;
		uint8_t z = 0;

	}


SuspensionScreenView::SuspensionScreenView()
{

}

void SuspensionScreenView::setupScreen()
{
    SuspensionScreenViewBase::setupScreen();
}

void SuspensionScreenView::tearDownScreen()
{
    SuspensionScreenViewBase::tearDownScreen();
}

void SuspensionScreenView::UpdateSuspensionScreen(){
	if(osMessageQueueGetCount(buttonQueueHandle) > 0){
		if(osMessageQueueGet(buttonQueueHandle, &z, 0, 0) == osOK){
			handleKeyEvent(0);
		}
	}

	Unicode::snprintfFloat(tbFRPotBuffer, TBFRPOT_SIZE, "%03.3f", flPot);
	Unicode::snprintfFloat(tbFLPotBuffer, TBFLPOT_SIZE, "%03.3f", frPot);
	Unicode::snprintfFloat(tbRRPotBuffer, TBRRPOT_SIZE, "%03.3f", rlPot);
	Unicode::snprintfFloat(tbRLPotBuffer, TBRLPOT_SIZE, "%03.3f", rrPot);
	Unicode::snprintfFloat(tbFrontBreakBuffer, TBFRONTBREAK_SIZE, "%03.3f", frontBreak);
	Unicode::snprintfFloat(tbRearBreakBuffer, TBREARBREAK_SIZE, "%03.3f", rearBreak);

	Unicode::snprintfFloat(tbLatitudeBuffer, TBLATITUDE_SIZE, "%03.6f", latitude);
	Unicode::snprintfFloat(tbLongitudeBuffer, TBLONGITUDE_SIZE, "%03.6f", longitude);
	Unicode::snprintfFloat(tbAltitudeBuffer, TBALTITUDE_SIZE, "%03.6f", altitude);

	tbGPSMessage.setWideTextAction(touchgfx::WIDE_TEXT_WORDWRAP);
	Unicode::strncpy(tbGPSMessageBuffer, (char *)gpsData, TBGPSMESSAGE_SIZE);
	tbGPSMessage.invalidate();

	tbFRPot.invalidate();
	tbFLPot.invalidate();
	tbRRPot.invalidate();
	tbRLPot.invalidate();
	tbFrontBreak.invalidate();
	tbRearBreak.invalidate();
	tbLatitude.invalidate();
	tbLongitude.invalidate();
	tbAltitude.invalidate();
}

void SuspensionScreenView::ToggleTTPMS(){
	if(buttonTTPMSToggle.getState()){

	}
}
