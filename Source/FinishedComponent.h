/*
  ==============================================================================

    FinishedComponent.h
    Created: 28 Jun 2020 8:23:27pm
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
class FinishedComponent    :    public LeapControlViewComponent
{
public:
    FinishedComponent (MainComponent *parent);
    ~FinishedComponent();

    void paint (Graphics&) override;
    void resized() override;
    
    void leapButtonClicked (Button*) override;
    void leapSliderValueChanged (Slider*) override;

private:
    
    enum ButtonIds
    {
        BUTTON_ID_SHOP_AGAIN = 0
    };
    
    MainComponent *parentComponent;
    
    Label finishedLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FinishedComponent)
};
