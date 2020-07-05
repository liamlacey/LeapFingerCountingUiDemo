/*
  ==============================================================================

    PaymentComponent.cpp
    Created: 28 Jun 2020 8:08:31pm
    Author:  Liam Lacey

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PaymentComponent.h"
#include "MainComponent.h"

//==============================================================================
PaymentComponent::PaymentComponent (MainComponent *parent)
{
    parentComponent = parent;
    
    //the order these are added determines the button IDs,
    //therefore add in the order of the ButtonIds enum
    addLeapButton (1, "Card");
    addLeapButton (2, "Cash");
}

PaymentComponent::~PaymentComponent()
{
}

void PaymentComponent::paint (Graphics& g)
{
}

void PaymentComponent::resized()
{
    const auto buttonWidth = getWidth() / 4;
    const auto buttonHeight = getHeight() / 5;
    
    getLeapButton(BUTTON_ID_CARD)->setBounds ((getWidth() / 2) - (buttonWidth / 2), buttonHeight * 1, buttonWidth, buttonHeight);
    
    getLeapButton(BUTTON_ID_CASH)->setBounds ((getWidth() / 2) - (buttonWidth / 2), buttonHeight * 3, buttonWidth, buttonHeight);
}

void PaymentComponent::leapButtonClicked (Button *button)
{
    if (button == getLeapButton(BUTTON_ID_CARD) || button == getLeapButton(BUTTON_ID_CASH))
    {
        parentComponent->setStage (STAGE_END);
    }
}

void PaymentComponent::leapSliderValueChanged (Slider* slider)
{
    
}

