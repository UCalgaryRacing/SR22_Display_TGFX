#ifndef DRIVERSCREENVIEW_HPP
#define DRIVERSCREENVIEW_HPP

#include <gui_generated/driverscreen_screen/DriverScreenViewBase.hpp>
#include <gui/driverscreen_screen/DriverScreenPresenter.hpp>

class DriverScreenView : public DriverScreenViewBase
{
public:
    DriverScreenView();
    virtual ~DriverScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void UpdateDriverScreen();

    virtual void updateGear(uint8_t value);
    virtual void updateRPM(uint16_t value);
    virtual void updateLeftDataField1(float value);
    virtual void updateLeftDataField2(uint8_t value);
    virtual void updateRightDataField1(float value);
    virtual void updateRightDataField2(int16_t value);
    virtual void updateBatteryLow(bool state);
    virtual void updateCoolantHigh(bool state);

protected:
};

#endif // DRIVERSCREENVIEW_HPP
