#include <gui/suspensionscreen_screen/SuspensionScreenView.hpp>
#include "main.h"
#include "can.h"
extern "C"{
		extern osMessageQueueId_t buttonQueueHandle;
		extern osMessageQueueId_t driverDataQueueHandle;
		extern uint16_t rpm;
		extern driverScreenData_t *driverScreenData_q;
		extern double flPot;
		extern double frPot;
		extern double rlPot;
		extern double rrPot;
		extern double frontBreak;
		extern double rearBreak;

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

	tbFRPot.invalidate();
	tbFLPot.invalidate();
	tbRRPot.invalidate();
	tbRLPot.invalidate();
	tbFrontBreak.invalidate();
	tbRearBreak.invalidate();
}
