#include <gui/suspensionscreen_screen/SuspensionScreenView.hpp>
#include "main.h"
#include "can.h"
extern "C"{
		extern osMessageQueueId_t buttonQueueHandle;
		extern osMessageQueueId_t driverDataQueueHandle;
		extern uint16_t rpm;
		extern driverScreenData_t *driverScreenData_q;
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
}
