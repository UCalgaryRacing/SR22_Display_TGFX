#ifndef DRIVERSCREENPRESENTER_HPP
#define DRIVERSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class DriverScreenView;

class DriverScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    DriverScreenPresenter(DriverScreenView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~DriverScreenPresenter() {};

    virtual void updateGear(uint8_t value);
    virtual void updateLeftDataField1(float value);
    virtual void updateLeftDataField2(uint8_t value);
    virtual void updateLeftDataField3(float value);
    virtual void updateLeftDataField4(uint8_t value);
    virtual void updateRightDataField1(float value);
    virtual void updateRightDataField2(uint8_t value); 
    virtual void updateBatteryLow(bool state);
    virtual void updateCoolantHigh(bool state);
    virtual void updateFansOn(bool state);
    virtual void updateWaterPumpsOn(bool state);
    virtual void updateFuelPumpOn(bool state);
private:
    DriverScreenPresenter();

    DriverScreenView& view;
};

#endif // DRIVERSCREENPRESENTER_HPP
