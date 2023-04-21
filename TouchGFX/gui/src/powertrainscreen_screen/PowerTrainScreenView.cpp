#include <gui/powertrainscreen_screen/PowerTrainScreenView.hpp>
#include "main.h"
#include "can.h"

extern "C"{
	extern osMessageQueueId_t buttonQueueHandle;

	// EMU1 0x600
	extern uint16_t rpm;
	extern float tps;
	extern int8_t iat;
	extern int16_t map;
	extern float injpw;

	// EMU2 0x601
	extern double ai1;
	extern double ai2;
	extern double ai3;
	extern double ai4;

	// EMU3 0x602
	extern uint16_t vspd;
	extern uint8_t baro;
	extern uint8_t oilTemp;
	extern float oilPressure;
	extern float fuelPressure;
	extern int16_t coolantTemp;

	// EMU4 0x603
	extern double ignitionAngle;
	extern double dwell;
	extern double lambda;
	extern double lambcorr;
	extern uint16_t egt1;
	extern uint16_t egt2;

	// EMU5 0x604
	extern uint8_t gear;
	extern int8_t ecuTemp;
	extern uint16_t batteryVoltageECU;
	extern uint16_t errFlag;
	extern uint8_t flags1;
	extern uint8_t ethanolContent;

	extern uint16_t egt3;
	extern uint16_t egt4;
	//		driverScreenData_t *driverScreenData_r;
	uint8_t y = 0;

	}
PowerTrainScreenView::PowerTrainScreenView()
{

}

void PowerTrainScreenView::setupScreen()
{
    PowerTrainScreenViewBase::setupScreen();
}

void PowerTrainScreenView::tearDownScreen()
{
    PowerTrainScreenViewBase::tearDownScreen();
}

void PowerTrainScreenView::UpdatePowerTrainScreen(){
	if(osMessageQueueGetCount(buttonQueueHandle) > 0){
		if(osMessageQueueGet(buttonQueueHandle, &y, 0, 0) == osOK){
			handleKeyEvent(0);
		}
	}

	Unicode::snprintf(tbRPMBuffer, TBRPM_SIZE, "%d", rpm);
	Unicode::snprintfFloat(tbTPSBuffer, TBTPS_SIZE, "%03.2f", tps);
	Unicode::snprintf(tbIATBuffer, TBIAT_SIZE, "%d", iat);
	Unicode::snprintf(tbMAPBuffer, TBMAP_SIZE, "%d", map);
	Unicode::snprintfFloat(tbINJPWBuffer, TBINJPW_SIZE, "%03.2f", injpw);

	Unicode::snprintf(tbVSPDBuffer, TBVSPD_SIZE, "%d", iat);
	Unicode::snprintf(tbBaroBuffer, TBBARO_SIZE, "%d", baro);
	Unicode::snprintfFloat(tbOilTempBuffer, TBOILTEMP_SIZE, "%03.2f", oilTemp);
	Unicode::snprintfFloat(tbOilPresBuffer, TBOILPRES_SIZE, "%03.2f", oilPressure);
	Unicode::snprintfFloat(tbFuelPresBuffer, TBFUELPRES_SIZE, "%03.2f", fuelPressure);
	Unicode::snprintf(tbFuelTempBuffer, TBFUELTEMP_SIZE, "%d", coolantTemp);

	Unicode::snprintf(tbEGT3Buffer, TBEGT3_SIZE, "%d", egt3);
	Unicode::snprintf(tbEGT4Buffer, TBEGT4_SIZE, "%d", egt4);

	tbRPM.invalidate();
	tbTPS.invalidate();
	tbIAT.invalidate();
	tbMAP.invalidate();
	tbINJPW.invalidate();
	tbVSPD.invalidate();
	tbBaro.invalidate();
	tbOilTemp.invalidate();
	tbOilPres.invalidate();
	tbFuelPres.invalidate();
	tbFuelTemp.invalidate();
	tbIGNANG.invalidate();
	tbDwell.invalidate();
	tbLambda.invalidate();
	tbLambCorr.invalidate();
	tbEGT1.invalidate();
	tbEGT2.invalidate();
	tbEGT3.invalidate();
	tbEGT4.invalidate();
	tbGear.invalidate();
	tbECUTemp.invalidate();
	tbBatt.invalidate();
	tbCoolantTemp.invalidate();

}
