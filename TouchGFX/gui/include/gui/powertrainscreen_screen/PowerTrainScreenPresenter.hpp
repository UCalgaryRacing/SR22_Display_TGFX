#ifndef POWERTRAINSCREENPRESENTER_HPP
#define POWERTRAINSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class PowerTrainScreenView;

class PowerTrainScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    PowerTrainScreenPresenter(PowerTrainScreenView& v);

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

    virtual ~PowerTrainScreenPresenter() {};

private:
    PowerTrainScreenPresenter();

    PowerTrainScreenView& view;
};

#endif // POWERTRAINSCREENPRESENTER_HPP
