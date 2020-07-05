/*
  ==============================================================================

    StartPageComponent.h
    Created: 28 Jun 2020 2:41:00pm
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
class StartPageComponent    :   public LeapControlViewComponent
{
public:
    StartPageComponent (MainComponent *parent);
    ~StartPageComponent();

    void paint (Graphics&) override;
    void resized() override;
    
    void leapButtonClicked (Button *button) override;
    void leapSliderValueChanged (Slider*) override;

private:
    
    enum ButtonIds
    {
        BUTTON_ID_START = 0,
        BUTTON_ID_WEIGHT
    };
    
    MainComponent *parentComponent;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StartPageComponent)
};
