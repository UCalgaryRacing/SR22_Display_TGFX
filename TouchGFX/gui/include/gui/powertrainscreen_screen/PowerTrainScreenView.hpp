#ifndef POWERTRAINSCREENVIEW_HPP
#define POWERTRAINSCREENVIEW_HPP

#include <gui_generated/powertrainscreen_screen/PowerTrainScreenViewBase.hpp>
#include <gui/powertrainscreen_screen/PowerTrainScreenPresenter.hpp>

class PowerTrainScreenView : public PowerTrainScreenViewBase
{
public:
    PowerTrainScreenView();
    virtual ~PowerTrainScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void UpdatePowerTrainScreen();
protected:
};

#endif // POWERTRAINSCREENVIEW_HPP
