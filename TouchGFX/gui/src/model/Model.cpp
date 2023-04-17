#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#ifndef SIMULATOR

	#include "main.h"
	#include "can.h"
	extern "C"{
		extern osMessageQueueId_t buttonQueueHandle;
		extern osMessageQueueId_t driverDataQueueHandle;
		driverScreenData_t *driverScreenData_r;
		uint8_t x = 0;
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
//			modelListener->updateGear(x);
//			modelListener->updateLeftDataField1(x);
//			modelListener->updateLeftDataField2(x);
//			modelListener->updateLeftDataField3(x);
//			modelListener->updateLeftDataField4(x);
//			modelListener->updateRightDataField1(x);
//			modelListener->updateRightDataField2(x);
//			modelListener->updateBatteryLow((x%2) != 0);
		}
	}
	if(osMessageQueueGetCount(driverDataQueueHandle) > 0){
		if(osMessageQueueGet(driverDataQueueHandle, &driverScreenData_r, 0, 0) == osOK){
			modelListener->updateGear(x);
			modelListener->updateLeftDataField1(driverScreenData_r->leftDataField1);
			modelListener->updateLeftDataField2(driverScreenData_r->leftDataField2);
			modelListener->updateLeftDataField3(driverScreenData_r->leftDataField3);
			modelListener->updateLeftDataField4(driverScreenData_r->leftDataField4);
			modelListener->updateRightDataField1(driverScreenData_r->rightDataField1);
			modelListener->updateRightDataField2(driverScreenData_r->rightDataField2);
			modelListener->updateBatteryLow(driverScreenData_r->batteryLow);
			modelListener->updateCoolantHigh(driverScreenData_r->coolantHigh);
			modelListener->updateFansOn(driverScreenData_r->fansOn);
			modelListener->updateWaterPumpsOn(driverScreenData_r->waterPumpsOn);
			modelListener->updateFuelPumpOn(driverScreenData_r->fuelPumpOn);
		}
	}
#endif
}
