/*
  ==============================================================================

    LeapSlider.h
    Created: 22 Jun 2020 5:06:48pm
    Author:  Liam Lacey
 
 Custom JUCE::Slider class that contains a number between 1-10 that specifies
 the finger count used to select the slider; a timer so that the slider
 is only selected after a certain amount of time which is visually displayed with
 an animation; and a method of updating the slider value using the Leap circle gesture.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#define DEFAULT_SLIDER_HOLD_TIME_MS 1000
#define TIMER_INTERVAL 10

//==============================================================================
/*
*/
class LeapSlider    :   public Slider,
                        public Timer,
                        public AsyncUpdater
{
public:
    LeapSlider (const int number, const int holdTimeMs = DEFAULT_SLIDER_HOLD_TIME_MS);
    ~LeapSlider();

    void paint (Graphics&) override;
    void paintOverChildren (Graphics&) override;
    void resized() override;
    void timerCallback() override;
    void handleAsyncUpdate() override;
    
    void setValueWithCircleGestureProgress (const int gestureState,
                                            const bool isClockwise,
                                            const double gestureProgress,
                                            const NotificationType notification);
    
    void holdStart();
    bool holdStartIfMatchingNumber (const int number);
    void holdEnd();
    bool holdEndIfMatchingNumber (const int number);
    
    void setSelected (const bool selected);
    bool setSelectedIfMatchingNumber (const bool selected, const int number);
    
    void clearState();
    bool clearStateIfMatchingNumber (const int number);
    
    void setHoldTime (const int holdTimeMs);
    
    int getSliderNumber();
    bool isSelected();
    
    void setNumberDisplaySize (const int width, const int height);

private:
    
    int sliderNumber;
    bool sliderIsSelected = false;
    
    int holdTime;
    float currentHoldTimeProgress = 0.0;
    
    float circleGestureStartSliderValue = 0.0;
    float circleGesutureNewSliderValue = 0.0;
    NotificationType circleGestureNotificationType;
    
    bool asyncRepaint = false;
    bool asyncUpdateSliderValue = false;
    
    int numberDisplayWidth = 0, numberDisplayHeight = 0;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LeapSlider)
};
