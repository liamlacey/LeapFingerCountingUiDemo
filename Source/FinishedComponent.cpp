/*
  ==============================================================================

    FinishedComponent.cpp
    Created: 28 Jun 2020 8:23:27pm
    Author:  Liam Lacey

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FinishedComponent.h"
#include "MainComponent.h"

//==============================================================================
FinishedComponent::FinishedComponent (MainComponent *parent)
{
    parentComponent = parent;
    
    addAndMakeVisible (&finishedLabel);
    finishedLabel.setText ("Please take your shopping and receipt", dontSendNotification);
    finishedLabel.setJustificationType (Justification::centred);
    
    //the order these are added determines the button IDs,
    //therefore add in the order of the ButtonIds enum
    addLeapButton (1, "Shop Again");
}

FinishedComponent::~FinishedComponent()
{
}

void FinishedComponent::paint (Graphics& g)
{

}

void FinishedComponent::resized()
{
    const auto buttonWidth = getWidth() / 4;
    const auto buttonHeight = getHeight() / 5;
    
    finishedLabel.setBounds (0, buttonHeight, getWidth(), buttonHeight);
    getLeapButton(BUTTON_ID_SHOP_AGAIN)->setBounds ((getWidth() / 2) - (buttonWidth / 2), buttonHeight * 3, buttonWidth, buttonHeight);
}

void FinishedComponent::leapButtonClicked (Button *button)
{
    if (button == getLeapButton(BUTTON_ID_SHOP_AGAIN))
    {
        parentComponent->setStage (STAGE_START);
    }
}

void FinishedComponent::leapSliderValueChanged (Slider* slider)
{
    
}
