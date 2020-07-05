/*
  ==============================================================================

    LeapControlViewComponent.h
    Created: 28 Jun 2020 8:37:40pm
    Author:  Liam Lacey

  ==============================================================================
*/

/*
 
 Abstract class for creating a component class containing LeapButton objects
 and the needed functions for interacting with them.
 
 
 */

#pragma once

#include <JuceHeader.h>
#include "../LeapSDK/include/Leap.h"
#include "LeapButton.h"
#include "LeapSlider.h"

using namespace Leap;

//==============================================================================
/*
*/
class LeapControlViewComponent    : public Component,
                                    public Button::Listener,
                                    public Slider::Listener
{
public:
    LeapControlViewComponent();
    ~LeapControlViewComponent();
    
    //function to add a LeapButton object, passing in the number and text for the button.
    //this sets the buttons text, adds the listener, and makes visible.
    //use getLeapButton to set other needed Button attributes.
    void addLeapButton (const int buttonNumber, const String buttonText);
    
    //function to get a LeapButton object, where buttonId is the OwnedArray index
    LeapButton* getLeapButton (const int buttonId);
    
    //function to add a LeapSlider object, passing in the number for the slider.
    //this adds the listener and makes visible.
    //use getLeapSlider to set other needed Slider attributes.
    void addLeapSlider (const int sliderNumber);
    
    //function to get a LeapSlider object, where sliderId is the OwnedArray index
    LeapSlider* getLeapSlider (const int sliderId);
    
    //pure virutal callback function called when one of the LeapButton buttons is clicked
    virtual void leapButtonClicked (Button*) = 0;
    //pure virtual callback function called when one of the LeapSlider sliders changes value
    virtual void leapSliderValueChanged (Slider*) = 0;
    
    //function that starts the hold of the LeapButton or LeapSlider object/s that
    //have controlNum assigned to them.
    void holdStart (const int controlNum);
    //function that stops and resets the hold of the LeapButton or LeapSlider object/s that
    //have controlNum assigned to them. For LeapSlider objects this also deselects them.
    void cancelControlHold (const int controlNum);
    //function that stops and resets the hold of all LeapButton and LeapSlider objects.
    //For LeapSlider objects this also deselects them.
    void clearAllControlStates();
    
    //function that sets the value of any selected LeapSlider objects with a circle gestures progress.
    void setSelectedLeapSliderWithCircleGesture (const int gestureState,
                                                 const bool isClockwise,
                                                 const double gestureProgress,
                                                 const NotificationType notification);
    
    //returns if any LeapSlider objects are selected or not
    bool areAnyLeapSlidersSelected();

private:
    
    void buttonClicked (Button*) override;
    void sliderValueChanged (Slider* slider) override;
    
    OwnedArray <LeapButton> leapButtons;
    OwnedArray <LeapSlider> leapSliders;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LeapControlViewComponent)
};
