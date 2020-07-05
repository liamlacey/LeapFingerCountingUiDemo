/*
  ==============================================================================

    ScanPageComponent.h
    Created: 28 Jun 2020 2:41:42pm
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
class ScanPageComponent    :    public LeapControlViewComponent
{
public:
    ScanPageComponent (MainComponent *parent);
    ~ScanPageComponent();

    void paint (Graphics&) override;
    void resized() override;
    
    void leapButtonClicked (Button *button) override;
    void leapSliderValueChanged (Slider*) override;

private:
    
    enum ButtonIds
    {
        BUTTON_ID_FIND = 0,
        BUTTON_ID_FINISH,
        //BUTTON_ID_UP,
        //BUTTON_ID_DOWN
    };
    
    MainComponent *parentComponent;
    
    //dummy item list
    TextEditor itemListComponent;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ScanPageComponent)
};
