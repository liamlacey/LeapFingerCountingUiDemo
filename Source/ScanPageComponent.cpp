/*
  ==============================================================================

    ScanPageComponent.cpp
    Created: 28 Jun 2020 2:41:42pm
    Author:  Liam Lacey

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ScanPageComponent.h"
#include "MainComponent.h"

//==============================================================================
ScanPageComponent::ScanPageComponent (MainComponent *parent)
{
    parentComponent = parent;
    
    //the order these are added determines the button IDs,
    //therefore add in the order of the ButtonIds enum
    addLeapButton (1, "Find Item");
    addLeapButton (6, "Finish and Pay");
    //addLeapButton (2, "Up");
    //addLeapButton (3, "Down");
    
    addAndMakeVisible (&itemListComponent);
    itemListComponent.setEnabled(false);
    itemListComponent.setMultiLine(true);
    auto itemListString = String();
    itemListString += "Bread            £0.75\n";
    itemListString += "Oat Milk         £1.50\n";
    itemListString += "Carrots          £0.33\n";
    itemListString += "Soup             £1.25\n";
    itemListComponent.setText(itemListString);
}

ScanPageComponent::~ScanPageComponent()
{
}

void ScanPageComponent::paint (Graphics& g)
{
    
}

void ScanPageComponent::resized()
{
    const auto buttonWidth = getWidth() / 4;
    const auto buttonHeight = getHeight() / 5;
    
    getLeapButton (BUTTON_ID_FIND)->setBounds (((getWidth() / 4) * 3) - (buttonWidth / 2),
                                               buttonHeight * 1,
                                               buttonWidth,
                                               buttonHeight);
    
    getLeapButton (BUTTON_ID_FINISH)->setBounds (((getWidth() / 4) * 3) - (buttonWidth / 2),
                                                 buttonHeight * 3,
                                                 buttonWidth,
                                                 buttonHeight);
    
    //getLeapButton (BUTTON_ID_UP)->setBounds (0, buttonHeight * 4, buttonWidth, buttonHeight / 2);
    //getLeapButton (BUTTON_ID_DOWN)->setBounds (buttonWidth, buttonHeight * 4, buttonWidth, buttonHeight / 2);
    
    itemListComponent.setBounds (0, 0, getWidth() / 2, getHeight());

}

void ScanPageComponent::leapButtonClicked (Button *button)
{
    if (button == getLeapButton (BUTTON_ID_FIND))
    {
        //move to select item stage
        parentComponent->setStage (STAGE_SELECT_ITEM);
    }
    else if (button == getLeapButton (BUTTON_ID_FINISH))
    {
        //move to pay stage
        parentComponent->setStage (STAGE_PAY);
    }
}

void ScanPageComponent::leapSliderValueChanged (Slider* slider)
{
    
}
