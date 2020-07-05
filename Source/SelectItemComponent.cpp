/*
  ==============================================================================

    SelectItemComponent.cpp
    Created: 28 Jun 2020 7:36:26pm
    Author:  Liam Lacey

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SelectItemComponent.h"
#include "MainComponent.h"

//==============================================================================
SelectItemComponent::SelectItemComponent (MainComponent *parent)
{
    parentComponent = parent;
    
    //the order these are added determines the button IDs,
    //therefore add in the order of the ButtonIds enum
    addLeapButton (1, "Bread");
    addLeapButton (2, "Oat Milk");
    addLeapButton (3, "Carrots");
    addLeapButton (4, "Soup");
    addLeapButton (5, "Back");
}

SelectItemComponent::~SelectItemComponent()
{
}

void SelectItemComponent::paint (Graphics& g)
{

}

void SelectItemComponent::resized()
{
    const auto buttonWidth = getWidth() / 4;
    const auto buttonHeight = getHeight() / 5;
    
    const auto controlBorder = 5;
    const auto controlBorder2 = controlBorder * 2;
    
    getLeapButton (BUTTON_ID_BREAD)->setBounds (controlBorder,
                                                controlBorder,
                                                buttonWidth - controlBorder2,
                                                buttonHeight - controlBorder2);
    
    getLeapButton (BUTTON_ID_OAT_MILK)->setBounds (controlBorder + buttonWidth,
                                                   controlBorder,
                                                   buttonWidth - controlBorder2,
                                                   buttonHeight - controlBorder2);
    
    getLeapButton (BUTTON_ID_CARROTS)->setBounds (controlBorder + (buttonWidth * 2),
                                                  controlBorder,
                                                  buttonWidth - controlBorder2,
                                                  buttonHeight - controlBorder2);
    
    getLeapButton (BUTTON_ID_SOUP)->setBounds (controlBorder + (buttonWidth * 3),
                                               controlBorder,
                                               buttonWidth - controlBorder2,
                                               buttonHeight - controlBorder2);
    
    getLeapButton (BUTTON_ID_BACK)->setBounds (controlBorder + ((getWidth() / 2) - (buttonWidth / 2)),
                                               controlBorder + buttonHeight,
                                               buttonWidth - controlBorder2,
                                               buttonHeight - controlBorder2);
}

void SelectItemComponent::leapButtonClicked (Button *button)
{
    //all buttons do the same thing
    parentComponent->setStage (STAGE_SCAN);
}

void SelectItemComponent::leapSliderValueChanged (Slider* slider)
{
    
}
