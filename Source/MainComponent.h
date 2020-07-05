/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

//==============================================================================
#include <JuceHeader.h>

#include "../LeapSDK/include/Leap.h"

#include "LeapControlViewComponent.h"
#include "StartPageComponent.h"
#include "ScanPageComponent.h"
#include "SelectItemComponent.h"
#include "PaymentComponent.h"
#include "FinishedComponent.h"

using namespace Leap;

//==============================================================================

#define NUM_FRAMES_TO_PROCESS 20

//const std::string stateNames[] = {"STATE_INVALID", "STATE_START", "STATE_UPDATE", "STATE_END"};

//==============================================================================

enum CheckoutStage
{
    STAGE_START = 0x00,
    STAGE_SCAN,
    STAGE_SELECT_ITEM,
    STAGE_PAY,
    STAGE_END
};

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public LeapControlViewComponent,
                        public Listener, //Leap::Listener
                        public AsyncUpdater,
                        public Timer
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void paintOverChildren (Graphics&) override;
    void resized() override;
    
    //LeapControlViewComponent functions
    void leapButtonClicked (Button*) override;
    void leapSliderValueChanged (Slider*) override;
    void timerCallback() override;
    
    void handleAsyncUpdate() override;
    
    //==============================================================================
    //Leap Listener callback functions
    void onConnect(const Controller&) override;
    void onDisconnect(const Controller&) override;
    void onFrame(const Controller&) override;
    
    //==============================================================================
    
    void setStage (const int newStage);

private:
    //==============================================================================
    // Your private member variables go here...
    
    //backend...
    
    void handleNewFingerCount (const int newNumFingers);
    void handleCircleGesture (const Gesture gesture);
    
    Controller leapController;
    int currentNumberOfFingers = -1;
    bool circleGestureInProgress = false;
    
    CheckoutStage currentStage = STAGE_START;
    
    //UI...
    
    Label numOfFingersLabel;
    bool asyncUpdateNumOfFingersLabel = false;
    
    int bottomBarHeight;
    
    StartPageComponent startPageComponent;
    ScanPageComponent scanPageComponent;
    SelectItemComponent selectItemComponent;
    PaymentComponent paymentComponent;
    FinishedComponent finishedComponent;
    
    enum ButtonIds
    {
        BUTTON_ID_BACK = 0,
        BUTTON_ID_HELP
    };
    
    enum SliderIds
    {
        SLIDER_ID_VOLUME = 0,
        SLIDER_ID_BRIGHTNESS
    };
    
    bool helpButtonPressed = false;
    bool asyncUpdateHelpAlert = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
