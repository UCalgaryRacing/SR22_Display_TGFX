#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#ifndef SIMULATOR

	#include "main.h"
	#include "can.h"
	extern "C"{
		extern osMessageQueueId_t buttonQueueHandle;
		extern osMessageQueueId_t driverDataQueueHandle;
		driverScreenData_t *driverScreenData_r;
//		uint8_t x = 0;
	}
#endif
Model::Model() : modelListener(0)
{

}

void Model::tick()
{
#ifndef SIMULATOR

#endif
}
