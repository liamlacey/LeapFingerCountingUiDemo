/*
  ==============================================================================

    LeapControlViewComponent.cpp
    Created: 28 Jun 2020 8:37:40pm
    Author:  Liam Lacey

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LeapControlViewComponent.h"

//==============================================================================
LeapControlViewComponent::LeapControlViewComponent()
{

}

LeapControlViewComponent::~LeapControlViewComponent()
{
}

void LeapControlViewComponent::addLeapButton (const int buttonNumber, const String buttonText)
{
    leapButtons.add (new LeapButton (buttonNumber));
    
    const auto buttonIndex = leapButtons.size() - 1;
    
    leapButtons[buttonIndex]->addListener (this);
    leapButtons[buttonIndex]->setButtonText (buttonText);
    addAndMakeVisible (leapButtons[buttonIndex]);
}

LeapButton* LeapControlViewComponent::getLeapButton (int buttonId)
{
    if (buttonId < leapButtons.size())
        return leapButtons[buttonId];
    else
        return nullptr;
}

void LeapControlViewComponent::addLeapSlider (const int sliderNumber)
{
    leapSliders.add (new LeapSlider (sliderNumber));
    
    const auto sliderIndex = leapSliders.size() - 1;
    
    leapSliders[sliderIndex]->addListener (this);
    addAndMakeVisible (leapSliders[sliderIndex]);
}

LeapSlider* LeapControlViewComponent::getLeapSlider (const int sliderId)
{
    if (sliderId < leapSliders.size())
        return leapSliders[sliderId];
    else
        return nullptr;
}

void LeapControlViewComponent::buttonClicked (Button* button)
{
    for (int i = 0; i < leapButtons.size(); i++)
    {
        if (button == leapButtons[i])
        {
            leapButtonClicked (button);
        }
    }
}

void LeapControlViewComponent::sliderValueChanged (Slider* slider)
{
    for (int i = 0; i < leapSliders.size(); i++)
    {
        if (slider == leapSliders[i])
        {
            leapSliderValueChanged (slider);
        }
    }
}

void LeapControlViewComponent::holdStart (const int controlNum)
{
    for (int i = 0; i < leapButtons.size(); i++)
    {
        leapButtons[i]->holdStartIfMatchingNumber (controlNum);
    }
    
    for (int i = 0; i < leapSliders.size(); i++)
    {
        leapSliders[i]->holdStartIfMatchingNumber (controlNum);
    }
}

void LeapControlViewComponent::cancelControlHold (const int controlNum)
{
    for (int i = 0; i < leapButtons.size(); i++)
    {
        leapButtons[i]->holdEndIfMatchingNumber (controlNum);
    }
    
    for (int i = 0; i < leapSliders.size(); i++)
    {
        leapSliders[i]->clearStateIfMatchingNumber (controlNum);
    }
}

void LeapControlViewComponent::clearAllControlStates()
{
    for (int i = 0; i < leapButtons.size(); i++)
    {
        leapButtons[i]->holdEnd();
    }
    
    for (int i = 0; i < leapSliders.size(); i++)
    {
        leapSliders[i]->clearState();
    }
}

void LeapControlViewComponent::setSelectedLeapSliderWithCircleGesture (const int gestureState,
                                                                       const bool isClockwise,
                                                                       const double gestureProgress,
                                                                       const NotificationType notification)
{
    for (int i = 0; i < leapSliders.size(); i++)
    {
        if (leapSliders[i]->isSelected())
            leapSliders[i]->setValueWithCircleGestureProgress (gestureState, isClockwise, gestureProgress, notification);
    }
}

bool LeapControlViewComponent::areAnyLeapSlidersSelected()
{
    for (int i = 0; i < leapSliders.size(); i++)
    {
        if (leapSliders[i]->isSelected())
            return true;
    }
    
    return false;
}
