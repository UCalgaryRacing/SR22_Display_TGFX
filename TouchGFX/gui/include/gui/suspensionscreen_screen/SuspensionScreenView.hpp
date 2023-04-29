#ifndef SUSPENSIONSCREENVIEW_HPP
#define SUSPENSIONSCREENVIEW_HPP

#include <gui_generated/suspensionscreen_screen/SuspensionScreenViewBase.hpp>
#include <gui/suspensionscreen_screen/SuspensionScreenPresenter.hpp>

class SuspensionScreenView : public SuspensionScreenViewBase
{
public:
    SuspensionScreenView();
    virtual ~SuspensionScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void UpdateSuspensionScreen();
protected:
};

#endif // SUSPENSIONSCREENVIEW_HPP
