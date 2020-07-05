/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
    :   startPageComponent (this),
        scanPageComponent (this),
        selectItemComponent (this),
        paymentComponent (this),
        finishedComponent (this)
{
    //backend...
    leapController.addListener(*this);
    
    //UI...
    
    addAndMakeVisible (&numOfFingersLabel);
    numOfFingersLabel.setJustificationType (Justification::centred);
    numOfFingersLabel.setText ("NC", dontSendNotification);
    
    addAndMakeVisible (&startPageComponent);
    addChildComponent (&scanPageComponent);
    addChildComponent (&selectItemComponent);
    addChildComponent (&paymentComponent);
    addChildComponent (&finishedComponent);
    
    //the order these are added determines the button IDs,
    //therefore add in the order of the ButtonIds enum
    addLeapButton (9, "Back");
    addLeapButton (10, "Help");

    //the order these are added determines the slider IDs,
    //therefore add in the order of the SliderIds enum
    addLeapSlider (7); //SLIDER_ID_VOLUME
    addLeapSlider (8); //SLIDER_ID_BRIGHTNESS
    
    getLeapSlider (SLIDER_ID_VOLUME)->setSliderStyle (Slider::LinearHorizontal);
    getLeapSlider (SLIDER_ID_VOLUME)->setRange (0, 100, 1);
    
    getLeapSlider (SLIDER_ID_BRIGHTNESS)->setSliderStyle (Slider::LinearHorizontal);
    getLeapSlider (SLIDER_ID_BRIGHTNESS)->setRange (1, 10, 0.1);
    
    setSize (800, 500);
    
    setStage (STAGE_START);
}

MainComponent::~MainComponent()
{
    leapController.removeListener(*this);
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void MainComponent::paintOverChildren (Graphics& g)
{
    g.setColour (Colours::white);
    g.drawLine (0, getHeight() - bottomBarHeight, getWidth(), getHeight() - bottomBarHeight, 1);
    
    //if help button has been pressed, drawn an alert
    if (helpButtonPressed)
    {
        g.setColour(Colours::red);
        g.fillRect ((getWidth() / 2) - (getWidth() / 4),
                    (getHeight() / 2) - (getHeight() / 4),
                    getWidth() / 2,
                    getHeight() / 2);
        
        g.setColour(Colours::black);
        
        g.drawRect((getWidth() / 2) - (getWidth() / 4),
                   (getHeight() / 2) - (getHeight() / 4),
                   getWidth() / 2,
                   getHeight() / 2,
                   5);
        
        g.setFont(Font(20));
        g.drawText("Help is on its way",
                   (getWidth() / 2) - (getWidth() / 4),
                   (getHeight() / 2) - (getHeight() / 4),
                   getWidth() / 2,
                   getHeight() / 2,
                   Justification::centred);
        
    } //if (helpButtonPressed)
}

void MainComponent::resized()
{
    bottomBarHeight = getHeight() / 8;
    const auto bottomBarDivider = 9;
    const auto controlBorder = 5;
    const auto controlBorder2 = controlBorder * 2;
    
    startPageComponent.setBounds (0, 0, getWidth(), getHeight() - bottomBarHeight);
    scanPageComponent.setBounds (0, 0, getWidth(), getHeight() - bottomBarHeight);
    selectItemComponent.setBounds (0, 0, getWidth(), getHeight() - bottomBarHeight);
    paymentComponent.setBounds (0, 0, getWidth(), getHeight() - bottomBarHeight);
    finishedComponent.setBounds (0, 0, getWidth(), getHeight() - bottomBarHeight);
    
    numOfFingersLabel.setBounds (controlBorder,
                                 controlBorder + (getHeight() - bottomBarHeight),
                                 (getWidth() / bottomBarDivider) - controlBorder2,
                                 (bottomBarHeight) - controlBorder2);
    
    getLeapSlider (SLIDER_ID_VOLUME)->setBounds (controlBorder + (getWidth() / bottomBarDivider),
                                                 controlBorder + (getHeight() - bottomBarHeight),
                                                 ((getWidth() / bottomBarDivider) * 3) - controlBorder2,
                                                 bottomBarHeight - controlBorder2);
    getLeapSlider (SLIDER_ID_BRIGHTNESS)->setBounds (controlBorder + ((getWidth() / bottomBarDivider) * 4),
                                                     controlBorder + (getHeight() - bottomBarHeight),
                                                     ((getWidth() / bottomBarDivider) * 3) - controlBorder2,
                                                     bottomBarHeight - controlBorder2);
    
    getLeapButton (BUTTON_ID_BACK)->setBounds (controlBorder + ((getWidth() / bottomBarDivider) * 7),
                                               controlBorder + (getHeight() - bottomBarHeight),
                                               (getWidth() / bottomBarDivider) - controlBorder2,
                                               bottomBarHeight - controlBorder2);
    getLeapButton (BUTTON_ID_HELP)->setBounds (controlBorder + ((getWidth() / bottomBarDivider) * 8),
                                               controlBorder + (getHeight() - bottomBarHeight),
                                               (getWidth() / bottomBarDivider) - controlBorder2,
                                               (bottomBarHeight) - controlBorder2);
}

void MainComponent::leapButtonClicked (Button* button)
{
    if (button == getLeapButton (BUTTON_ID_HELP))
    {
        helpButtonPressed = true;
        asyncUpdateHelpAlert = true;
        triggerAsyncUpdate();
    }
    
    else if (button == getLeapButton (BUTTON_ID_BACK))
    {
        if (currentStage == STAGE_END)
            setStage (STAGE_START);
        else if (currentStage == STAGE_PAY)
            setStage (STAGE_SCAN);
        else if (currentStage != STAGE_START)
            setStage (currentStage - 1);
    }
}

void MainComponent::leapSliderValueChanged (Slider* slider)
{
    //both slider are just dummy sliders
    if (slider == getLeapSlider (SLIDER_ID_VOLUME))
    {
        
    }
    else if (slider == getLeapSlider (SLIDER_ID_BRIGHTNESS))
    {
        
    }
}

void MainComponent::handleAsyncUpdate()
{
    if (asyncUpdateNumOfFingersLabel)
    {
        String labelString;
        
        if (leapController.isConnected())
            labelString = String (currentNumberOfFingers);
        else
            labelString = "NC";
        
        numOfFingersLabel.setText (labelString, dontSendNotification);
        
        asyncUpdateNumOfFingersLabel = false;
    }
    
    if (asyncUpdateHelpAlert)
    {
        //display alert
        repaint();
        
        //start timer so that alert is removed after a certain amount of time
        startTimer (3000);
        
        asyncUpdateHelpAlert = false;
    }
}

void MainComponent::timerCallback()
{
    //remove help alert
    helpButtonPressed = false;
    repaint();
    
    stopTimer();
}

//==============================================================================
/**
 * Called when the Leap Controller object connects to the Leap Motion software and
 * the Leap Motion hardware device is plugged in,
 * or when this Listener object is added to a Controller that is already connected.
 */

void MainComponent::onConnect(const Controller& controller)
{
    std::cout << "Connected" << std::endl;
    
    controller.enableGesture (Gesture::TYPE_CIRCLE);
    
    //update numOfFingers label to show number of extended fingers
    asyncUpdateNumOfFingersLabel = true;
    triggerAsyncUpdate();
}

//==============================================================================
/**
 * Called when the Controller object disconnects from the Leap Motion software or
 * the Leap Motion hardware is unplugged.
 */

void MainComponent::onDisconnect(const Controller& controller)
{
    std::cout << "Disonnected" << std::endl;
    
    //update numOfFingers label to show not connected
    asyncUpdateNumOfFingersLabel = true;
    triggerAsyncUpdate();
}

//==============================================================================
/**
 * Called when a new frame of Leap hand and finger tracking data is available.
 * Access the new frame data using the Controller::frame() function.
 */

void MainComponent::onFrame(const Controller& controller)
{
    //=================================
    
    //get the number of extended pointables in this frame
    const auto numOfExtendedPointables = controller.frame().pointables().extended().count();
    
    //only process this frame if the count of extended pointables hasn't changed over the
    //last NUM_FRAMES_TO_PROCESS frames (a defined hold of extended pointables).
    //This prevents accidental triggers when rearranging fingers.
    auto steadyNumOfPointables = true;
    
    for (int i = 1; i < NUM_FRAMES_TO_PROCESS; i++)
    {
        if (controller.frame(i).pointables().extended().count() != numOfExtendedPointables)
        {
            steadyNumOfPointables = false;
            break;
        }

    } // for (int i = 0; i < NUM_FRAMES_TO_PROCESS; i++)
    
    //if we've got a steady number of pointables and a new number of pointables,
    //process the finger count change.
    //FIXME: would it be better to only process if currentNumberOfFingers == 0?
    if (steadyNumOfPointables && numOfExtendedPointables != currentNumberOfFingers)
    {
        handleNewFingerCount (numOfExtendedPointables);
    }
    
    //=================================
    // Get list of gestures in the frame
    const auto gestures = controller.frame().gestures();
    
    //for each gesture in the frame
    for (int g = 0; g < gestures.count(); ++g)
    {
        const auto gesture = gestures[g];
        
        //if the gesture is the circles gesture
        if (gesture.type() == Gesture::TYPE_CIRCLE)
        {
            handleCircleGesture (gesture);
            
        } //if (gesture.type() == Gesture::TYPE_CIRCLE)
        
    } //for (int g = 0; g < gestures.count(); ++g)
}


//==============================================================================
//Handles / process a new count of fingers

void MainComponent::handleNewFingerCount (const int newNumFingers)
{
    //check if there are currently any selected sliders
    bool thereIsASliderSelected = areAnyLeapSlidersSelected();
    
    //only continue processing this finger count change if there isn't a selected slider
    //or the new finger count is 0. This is done to prevent the possible introduction of
    //the second hand (to perform a circle gesture to control the selected slider/s) from
    //changing what is selected/
    if (!thereIsASliderSelected || newNumFingers == 0)
    {
        std::cout << "Extended pointables: " << newNumFingers << std::endl;
        
        //cancel current control hold/s / selection/s (based on currentNumberOfFingers)
        
        if (currentNumberOfFingers != 0)
        {
            cancelControlHold (currentNumberOfFingers);
            
            switch (currentStage)
            {
                case STAGE_START:
                    startPageComponent.cancelControlHold (currentNumberOfFingers);
                    break;
                case STAGE_SCAN:
                    scanPageComponent.cancelControlHold (currentNumberOfFingers);
                    break;
                case STAGE_SELECT_ITEM:
                    selectItemComponent.cancelControlHold (currentNumberOfFingers);
                    break;
                case STAGE_PAY:
                    paymentComponent.cancelControlHold (currentNumberOfFingers);
                    break;
                case STAGE_END:
                    finishedComponent.cancelControlHold (currentNumberOfFingers);
                    break;
                default:
                    break;
                    
            } // switch (checkoutStage)
            
        } //if (currentNumberOfFingers != 0)
        
        //start new control hold/s (based on newNumFingers)
        
        holdStart (newNumFingers);
        
        switch (currentStage)
        {
            case STAGE_START:
                startPageComponent.holdStart (newNumFingers);
                break;
            case STAGE_SCAN:
                scanPageComponent.holdStart (newNumFingers);
                break;
            case STAGE_SELECT_ITEM:
                selectItemComponent.holdStart (newNumFingers);
                break;
            case STAGE_PAY:
                paymentComponent.holdStart (newNumFingers);
                break;
            case STAGE_END:
                finishedComponent.holdStart (newNumFingers);
                break;
            default:
                break;
                
        } // switch (checkoutStage)
        
        //if removed all fingers during a circle gesture, flag that the gesture
        //is no longer in progress
        if (newNumFingers == 0 && circleGestureInProgress)
        {
            circleGestureInProgress = false;
            DBG ("Circle gesture stopped");
        }
        
        //updated stored number of fingers
        currentNumberOfFingers = newNumFingers;
        
        //update numOfFingers label
        asyncUpdateNumOfFingersLabel = true;
        triggerAsyncUpdate();
        
    } //if (!thereIsASliderSelected || numOfExtendedPointables == 0)
}

//==============================================================================
//Function that handles / processes a Leap circle gesture

void MainComponent::handleCircleGesture (const Gesture gesture)
{
    const CircleGesture circle = gesture;
    
    //get the circle clockwiseness
    bool isClockwise;
    if (circle.pointable().direction().angleTo(circle.normal()) <= PI / 2)
        isClockwise = true;
    else
        isClockwise = false;
    
    if (gesture.state() == Leap::CircleGesture::STATE_START)
    {
        circleGestureInProgress = true;
        DBG ("Circle gesture started");
    }
    else if (gesture.state() == Leap::CircleGesture::STATE_STOP)
    {
        circleGestureInProgress = false;
        DBG ("Circle gesture stopped");
    }
    
    //update selected slider values with with the circle progress
    setSelectedLeapSliderWithCircleGesture (gesture.state(), isClockwise, circle.progress(), dontSendNotification);
    
    //            std::cout << std::string(2, ' ')
    //            << ", state: " << stateNames[gesture.state()]
    //            << ", progress: " << circle.progress()
    //            <<  ", clockwise: " << isClockwise
    //            << std::endl;
}

void MainComponent::setStage (const int newStage)
{
    if (newStage != currentStage)
    {
        //reset current stage (currentStage)
        if (currentStage == STAGE_START)
        {
            startPageComponent.clearAllControlStates();
            startPageComponent.setVisible(false);
        }
        else if (currentStage == STAGE_SCAN)
        {
            scanPageComponent.clearAllControlStates();
            scanPageComponent.setVisible(false);
        }
        else if (currentStage == STAGE_SELECT_ITEM)
        {
            selectItemComponent.clearAllControlStates();
            selectItemComponent.setVisible(false);
        }
        else if (currentStage == STAGE_PAY)
        {
            paymentComponent.clearAllControlStates();
            paymentComponent.setVisible(false);
        }
        else if (currentStage == STAGE_END)
        {
            finishedComponent.clearAllControlStates();
            finishedComponent.setVisible(false);
        }
        
        //process new stage (newStage)
        if (newStage == STAGE_START)
        {
            startPageComponent.setVisible(true);
        }
        else if (newStage == STAGE_SCAN)
        {
            scanPageComponent.setVisible(true);
        }
        else if (newStage == STAGE_SELECT_ITEM)
        {
            selectItemComponent.setVisible(true);
        }
        else if (newStage == STAGE_PAY)
        {
            paymentComponent.setVisible(true);
        }
        else if (newStage == STAGE_END)
        {
            finishedComponent.setVisible(true);
        }
        
        currentStage = (CheckoutStage)newStage;
        
    } //if (stage != currentStage)
}
