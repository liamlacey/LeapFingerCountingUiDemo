/*
  ==============================================================================

    LeapButton.cpp
    Created: 21 Jun 2020 10:56:25am
    Author:  Liam Lacey

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LeapButton.h"

//==============================================================================
LeapButton::LeapButton (const int number, const int holdTimeMs)
    : holdTime(holdTimeMs)
{
    if (number > 0 && number <= 10)
        buttonNumber = number;
    else
        jassertfalse; //buttonNumber can only be between 1 and 10!
}

LeapButton::~LeapButton()
{
}

void LeapButton::paint (Graphics& g)
{
    //FIXME: correct / replace isMouseButtonDown() bits below so that the leap interaction
    //makes the buttons look like they're down / triggered?
    //Or will this be irrelevent once I've got the full UI up and running?
    //To do this we can simply instead just call TextButton::paint, however this doesn't allow us to
    //draw the hold progress animation infront of the button background but behind the button text.
    //TextButton::paint(g);
    //The below alternative for some reason leaves the buttons as if they're over and / or down once triggered the button
    //paintButton(g, Button::isOver(), Button::isDown());
    
    auto& lf = getLookAndFeel();

     //this line is pretty much a copy from TextButton::paintButton
    lf.drawButtonBackground (g, *this,
                             findColour (getToggleState() ? buttonOnColourId : buttonColourId),
                             isMouseOver(), isMouseButtonDown());
    
    //draw animation of current hold time progress
    g.setColour(Colours::red);
    g.fillRect((int)0, (int)0, (int)(getWidth() * currentHoldTimeProgress), (int)getHeight());
    
    //this line is pretty much a copy from TextButton::paintButton
    lf.drawButtonText (g, *this, isMouseOver(), isMouseButtonDown());
    
    //draw button number
    g.setColour(Colours::yellow);
    g.drawRect (0, 0, numberDisplayWidth, numberDisplayHeight);
    g.drawText (String(buttonNumber), 0, 0, numberDisplayWidth, numberDisplayHeight, Justification::centred);
}

void LeapButton::resized()
{
    if (numberDisplayWidth == 0)
        numberDisplayWidth = getHeight() / 3;
    if (numberDisplayHeight == 0)
        numberDisplayHeight = getHeight() / 3;
}

void LeapButton::timerCallback()
{
    //update hold time progress and repaint animation
    currentHoldTimeProgress += ((float)TIMER_INTERVAL / (float)holdTime);
    repaint();
    
    //if we've held for the specified amount of time
    if (currentHoldTimeProgress >= 1.0)
    {
        //trigger button click
        this->triggerClick();
        //end the hold
        holdEnd();
    }
}

void LeapButton::handleAsyncUpdate()
{
    if (asyncRepaint)
    {
        repaint();
        asyncRepaint = false;
    }
}

void LeapButton::holdStart()
{
    //start / restart hold timer
    currentHoldTimeProgress = 0;
    startTimer (TIMER_INTERVAL);
}

bool LeapButton::holdStartIfMatchingNumber (const int number)
{
    if (number == buttonNumber)
    {
        holdStart();
        return true;
    }
    else
    {
        return false;
    }
}

//safe to call from non-message threads
void LeapButton::holdEnd()
{
    if (currentHoldTimeProgress != 0)
    {
        //stop hold timer
        stopTimer();
        currentHoldTimeProgress = 0;
        
        //update hold animation
        asyncRepaint = true;
        triggerAsyncUpdate();
    }
}

bool LeapButton::holdEndIfMatchingNumber (const int number)
{
    if (number == buttonNumber)
    {
        holdEnd();
        return true;
    }
    else
    {
        return false;
    }
}

void LeapButton::setHoldTime (const int holdTimeMs)
{
    holdTime = holdTimeMs;
}

int LeapButton::getButtonNumber()
{
    return buttonNumber;
}

//safe to call from non-message threads
void LeapButton::setNumberDisplaySize (const int width, const int height)
{
    numberDisplayWidth = width;
    numberDisplayHeight = height;
    
    //update UI
    asyncRepaint = true;
    triggerAsyncUpdate();
}
