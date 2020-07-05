/*
  ==============================================================================

    StartPageComponent.cpp
    Created: 28 Jun 2020 2:41:00pm
    Author:  Liam Lacey

  ==============================================================================
*/

#include <JuceHeader.h>
#include "StartPageComponent.h"
#include "MainComponent.h"

//==============================================================================
StartPageComponent::StartPageComponent (MainComponent *parent)
{
    parentComponent = parent;
    
    //the order these are added determines the button IDs,
    //therefore add in the order of the ButtonIds enum
    addLeapButton (1, "Start");
    addLeapButton (2, "Weigh own Bag");
}

StartPageComponent::~StartPageComponent()
{
    
}

void StartPageComponent::paint (Graphics& g)
{

}

void StartPageComponent::resized()
{
    const auto buttonWidth = getWidth() / 4;
    const auto buttonHeight = getHeight() / 5;
    
    getLeapButton (BUTTON_ID_START)->setBounds ((getWidth() / 2) - (buttonWidth / 2), buttonHeight * 1, buttonWidth, buttonHeight);
    getLeapButton (BUTTON_ID_WEIGHT)->setBounds ((getWidth() / 2) - (buttonWidth / 2), buttonHeight * 3, buttonWidth, buttonHeight);
}

void StartPageComponent::leapButtonClicked (Button *button)
{
    //Selecting either button does the same thing
    if (button == getLeapButton (BUTTON_ID_START) || button == getLeapButton (BUTTON_ID_WEIGHT))
    {
        //move to next stage
        parentComponent->setStage (STAGE_SCAN);
    }
}

void StartPageComponent::leapSliderValueChanged (Slider* slider)
{
    
}

