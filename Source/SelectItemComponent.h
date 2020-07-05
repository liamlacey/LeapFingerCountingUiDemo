/*
  ==============================================================================

    SelectItemComponent.h
    Created: 28 Jun 2020 7:36:26pm
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
class SelectItemComponent    :  public LeapControlViewComponent
{
public:
    SelectItemComponent (MainComponent *parent);
    ~SelectItemComponent();

    void paint (Graphics&) override;
    void resized() override;
    
    void leapButtonClicked (Button *button) override;
    void leapSliderValueChanged (Slider*) override;

private:
    
    enum ButtonIds
    {
        BUTTON_ID_BREAD = 0,
        BUTTON_ID_OAT_MILK,
        BUTTON_ID_CARROTS,
        BUTTON_ID_SOUP,
        BUTTON_ID_BACK
    };
    
    MainComponent *parentComponent;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SelectItemComponent)
};
