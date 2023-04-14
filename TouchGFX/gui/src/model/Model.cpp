#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#ifndef SIMULATOR

	#include "main.h"
	extern "C"{
		extern osMessageQueueId_t buttonQueueHandle;
		uint8_t x;
	}
#endif
Model::Model() : modelListener(0)
{

}

void Model::tick()
{
#ifndef SIMULATOR
	if(osMessageQueueGetCount(buttonQueueHandle) > 0){
		if(osMessageQueueGet(buttonQueueHandle, &x, 0, 0) == osOK){
			modelListener->updateGear(x);
			modelListener->updateLeftDataField1(x);
			modelListener->updateLeftDataField2(x);
			modelListener->updateLeftDataField3(x);
			modelListener->updateLeftDataField4(x);
			modelListener->updateRightDataField1(x);
			modelListener->updateRightDataField2(x);
			modelListener->updateBatteryLow((x%2) != 0);
		}
	}
#endif
}
