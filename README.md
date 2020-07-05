# LeapFingerCountingUiDemo

My submission for the [Ultraleap Beyond Touchscreens competition](https://www.ultraleap.com/company/news/events/developer-competition-2020/) - using the [Leap Motion Controller](https://www.ultraleap.com/product/leap-motion-controller/) and [Leap Motion SDK](https://developer.leapmotion.com) to develop a proof of concept that allows control of any a public interface without touching a screen. 

The basic premise behind the idea for my ‘Beyond Touchscreens’ submission is a simple one - using your finger count to interact with on-screen buttons, where each button is triggered by holding up a different number of fingers. This interaction can then also be used for on-screen slider selection, where the addition of circle gestures can be used to control the selected slider value. To demo these interactions, I have created a simple 'Self Service Checkout' GUI application that runs on macOS.

LeapFingerCountingUiDemo has been developed using the C++ macOS version of the Leap Motion SDK (included) for communication with the Leap Motion Controller, as well as the [JUCE](https://juce.com) cross-platform C++ library (not included - see Requirements below) for the GUI application side. It includes an Xcode project for building on macOS, however JUCE makes it easily possible to generate Windows Visual Studio projects and Linux makefiles.

## Requirements ##

To build LeapFingerCountingUiDemo you will need to do the following:

+  Download the [JUCE](https://github.com/juce-framework/JUCE) library.
+  Link the project to the JUCE library code - the easiest way to do this is to build the [Projucer](https://github.com/juce-framework/JUCE/tree/master/extras/Projucer) application, open the [LeapFingerCountingUiDemo.jucer](https://github.com/liamlacey/LeapFingerCountingUiDemo/blob/master/LeapFingerCountingUiDemo.jucer) file, and point the project to the location of the JUCE library.

## License ##

LeapFingerCountingUiDemo is licensed under Apache 2.0. See [LICENSE](https://github.com/liamlacey/LeapFingerCountingUiDemo/blob/master/LICENSE) for more details.
