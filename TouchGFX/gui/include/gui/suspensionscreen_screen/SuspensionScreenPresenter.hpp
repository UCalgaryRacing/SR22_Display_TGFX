#ifndef SUSPENSIONSCREENPRESENTER_HPP
#define SUSPENSIONSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class SuspensionScreenView;

class SuspensionScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    SuspensionScreenPresenter(SuspensionScreenView& v);

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

    virtual ~SuspensionScreenPresenter() {};

private:
    SuspensionScreenPresenter();

    SuspensionScreenView& view;
};

#endif // SUSPENSIONSCREENPRESENTER_HPP
