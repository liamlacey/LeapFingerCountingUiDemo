/*
  ==============================================================================

    LeapSlider.cpp
    Created: 22 Jun 2020 5:06:48pm
    Author:  Liam Lacey

  ==============================================================================
*/

#include <JuceHeader.h>
#include "../LeapSDK/include/Leap.h"
#include "LeapSlider.h"

//==============================================================================
LeapSlider::LeapSlider (const int number, const int holdTimeMs)
    :   holdTime(holdTimeMs)
{
    if (number > 0 && number <= 10)
        sliderNumber = number;
    else
        jassertfalse; //buttonNumber can only be between 1 and 10!
}

LeapSlider::~LeapSlider()
{
}

void LeapSlider::paint (Graphics& g)
{
    //draw 'selected' UI
    if (sliderIsSelected)
    {
        g.setColour(Colours::green);
        g.fillRect((int)0, (int)0, (int)getWidth(), (int)getHeight());
    }
    
    //draw animation of current hold time progress
    g.setColour(Colours::red);
    g.fillRect((int)0, (int)0, (int)(getWidth() * currentHoldTimeProgress), (int)getHeight());
    
    Slider::paint(g);
}

void LeapSlider::paintOverChildren (Graphics& g)
{
    //draw slider number
    g.setColour(Colours::yellow);
    g.drawRect (0, 0, numberDisplayWidth, numberDisplayHeight);
    g.drawText (String(sliderNumber), 0, 0, numberDisplayWidth, numberDisplayHeight, Justification::centred);
}

void LeapSlider::resized()
{
    if (numberDisplayWidth == 0)
        numberDisplayWidth = getHeight() / 3;
    if (numberDisplayHeight == 0)
        numberDisplayHeight = getHeight() / 3;
    
    Slider::resized();
}

void LeapSlider::timerCallback()
{
    //update hold time progress and repaint animation
    currentHoldTimeProgress += ((float)TIMER_INTERVAL / (float)holdTime);
    repaint();
    
    //if we've held for the specified amount of time
    if (currentHoldTimeProgress >= 1.0)
    {
        //set slider as 'selected'
        setSelected(true);
        //end the hold
        holdEnd();
    }
}

void LeapSlider::handleAsyncUpdate()
{
    if (asyncRepaint)
    {
        repaint();
        asyncRepaint = false;
    }
    
    if (asyncUpdateSliderValue)
    {
        Slider::setValue (circleGesutureNewSliderValue, circleGestureNotificationType);
        asyncUpdateSliderValue = false;
    }
}

//safe to call from non-message threads
void LeapSlider::setValueWithCircleGestureProgress (const int gestureState,
                                                    const bool isClockwise,
                                                    const double gestureProgress,
                                                    const NotificationType notification)
{
    //if a circle gesture start, get the current value of the slider
    if (gestureState == Leap::CircleGesture::STATE_START)
        circleGestureStartSliderValue = Slider::getValue();
    
    //set the new value of the slider to be the start value +/- the circle progress
    //where clockwise increases the value and anticlockwise decreases it
    
    //FIXME: would be nice to add a function to allow this mulitplier to be changed to
    //allow sliders to have a custom circle gesture sensitivities.
    //However this seems like a good sensitivity - increase the last number for less sensitivity,
    //decrease it for more. Is there a better equation I could use where the last number is between
    //0-1 which would be a better arbitary number range that the set function could use?
    double gestProgressMultiplier = (Slider::getMaximum() - Slider::getMinimum()) / 10.0;
    
    if (isClockwise)
        circleGesutureNewSliderValue = circleGestureStartSliderValue + (gestureProgress * gestProgressMultiplier);
    else
        circleGesutureNewSliderValue = circleGestureStartSliderValue - (gestureProgress * gestProgressMultiplier);
    
    //update the slider async (in case this function wasn't called by the message thread)
    circleGestureNotificationType = notification;
    asyncUpdateSliderValue = true;
    triggerAsyncUpdate();
}

void LeapSlider::holdStart()
{
    //start / reset hold timer
    currentHoldTimeProgress = 0;
    startTimer (TIMER_INTERVAL);
}

bool LeapSlider::holdStartIfMatchingNumber (const int number)
{
    if (number == sliderNumber)
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
void LeapSlider::holdEnd()
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

bool LeapSlider::holdEndIfMatchingNumber (const int number)
{
    if (number == sliderNumber)
    {
        holdEnd();
        return true;
    }
    else
    {
        return false;
    }
}

//safe to call from non-message threads
void LeapSlider::setSelected (const bool selected)
{
    if (sliderIsSelected != selected)
    {
        sliderIsSelected = selected;
        
        //update 'selected' UI async
        asyncRepaint = true;
        triggerAsyncUpdate();
    }
}


bool LeapSlider::setSelectedIfMatchingNumber (const bool selected, const int number)
{
    if (number == sliderNumber)
    {
        setSelected (selected);
        return true;
    }
    else
    {
        return false;
    }
}

//Ends the hold and disables the selection
void LeapSlider::clearState()
{
    holdEnd();
    setSelected (false);
}

bool LeapSlider::clearStateIfMatchingNumber (const int number)
{
    if (number == sliderNumber)
    {
        clearState();
        return true;
    }
    else
    {
        return false;
    }
}

void LeapSlider::setHoldTime (int holdTimeMs)
{
    holdTime = holdTimeMs;
}

int LeapSlider::getSliderNumber()
{
    return sliderNumber;
}

bool LeapSlider::isSelected()
{
    return sliderIsSelected;
}

//safe to call from non-message threads
void LeapSlider::setNumberDisplaySize (const int width, const int height)
{
    numberDisplayWidth = width;
    numberDisplayHeight = height;
    
    //update UI
    asyncRepaint = true;
    triggerAsyncUpdate();
}
