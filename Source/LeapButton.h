/*
  ==============================================================================

    LeapButton.h
    Created: 21 Jun 2020 10:56:25am
    Author:  Liam Lacey
 
 Custom JUCE::TextButton class that contains a number between 1-10 that specifies
 the finger count used to trigger the button, as well as a timer so that the button
 is only triggered after a certain amount of time which is visually displayed with
 an animation.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#define DEFAULT_BUTTON_HOLD_TIME_MS 1000
#define TIMER_INTERVAL 10

//==============================================================================
/*
*/
class LeapButton    :   public TextButton,
                        public Timer,
                        public AsyncUpdater
{
public:
    LeapButton (const int number, const int holdTimeMs = DEFAULT_BUTTON_HOLD_TIME_MS);
    ~LeapButton();

    void paint (Graphics&) override;
    void resized() override;
    void timerCallback() override;
    void handleAsyncUpdate() override;
    
    void holdStart();
    bool holdStartIfMatchingNumber (const int number);
    void holdEnd();
    bool holdEndIfMatchingNumber (const int number);
    
    void setHoldTime (const int holdTimeMs);
    
    int getButtonNumber();
    
    void setNumberDisplaySize (const int width, const int height);

private:
    
    int buttonNumber;
    
    int holdTime;
    float currentHoldTimeProgress = 0.0;
    
    bool asyncRepaint = false;
    
    int numberDisplayWidth = 0, numberDisplayHeight = 0;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LeapButton)
};
