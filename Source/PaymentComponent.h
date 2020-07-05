/*
  ==============================================================================

    PaymentComponent.h
    Created: 28 Jun 2020 8:08:31pm
    Author:  Liam Lacey

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "LeapControlViewComponent.h"

class MainComponent;

//==============================================================================
/*
*/
class PaymentComponent    :  public LeapControlViewComponent
{
public:
    PaymentComponent (MainComponent *parent);
    ~PaymentComponent();

    void paint (Graphics&) override;
    void resized() override;
    
    void leapButtonClicked (Button *button) override;
    void leapSliderValueChanged (Slider*) override;

private:
    
    enum ButtonIds
    {
        BUTTON_ID_CARD = 0,
        BUTTON_ID_CASH
    };

    MainComponent *parentComponent;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PaymentComponent)
};
