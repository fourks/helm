/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "graphical_step_sequencer.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
GraphicalStepSequencer::GraphicalStepSequencer (int num_steps)
{

    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    setNumSteps(num_steps);
    highlighted_step_ = -1;
    //[/Constructor]
}

GraphicalStepSequencer::~GraphicalStepSequencer()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void GraphicalStepSequencer::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff303030));

    //[UserPaint] Add your own custom painting code here..
    float x = 0.0f;
    float x_inc = getWidth() / (1.0f * num_steps_);
    for (int i = 0; i < num_steps_; ++i) {
        if (highlighted_step_ == i) {
            g.setColour(Colour(0xff404040));
            g.fillRect(x, 0.0f, x_inc, 1.0f * getHeight());
            g.setColour(Colour(0xff707070));
        }
        else
            g.setColour(Colour(0xff606060));

        float val = sequence_[i];
        if (val >= 0) {
            float y_start = proportionOfHeight((1.0f - val) / 2.0f);
            g.fillRoundedRectangle(x, y_start, x_inc, proportionOfHeight(0.5f) - y_start, 2.0f);
        }
        else {
            float height = proportionOfHeight(-val / 2.0f);
            g.fillRoundedRectangle(x, proportionOfHeight(0.5f), x_inc, height, 2.0f);
        }

        x += x_inc;
    }
    //[/UserPaint]
}

void GraphicalStepSequencer::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void GraphicalStepSequencer::mouseMove (const MouseEvent& e)
{
    //[UserCode_mouseMove] -- Add your code here...
    updateHover(getHoveredStep(e.getPosition().x));
    //[/UserCode_mouseMove]
}

void GraphicalStepSequencer::mouseExit (const MouseEvent& e)
{
    //[UserCode_mouseExit] -- Add your code here...
    updateHover(-1);
    //[/UserCode_mouseExit]
}

void GraphicalStepSequencer::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
    updateHover(getHoveredStep(e.getPosition().x));
    changeStep(e);
    //[/UserCode_mouseDown]
}

void GraphicalStepSequencer::mouseDrag (const MouseEvent& e)
{
    //[UserCode_mouseDrag] -- Add your code here...
    updateHover(getHoveredStep(e.getPosition().x));
    changeStep(e);
    //[/UserCode_mouseDrag]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void GraphicalStepSequencer::setNumSteps(int num_steps) {
    num_steps_ = num_steps;
    for (int i = sequence_.size(); i < num_steps_; ++i)
      sequence_.push_back(i % 2 ? 0.5f : -0.5f);
    repaint();
}

void GraphicalStepSequencer::changeStep(const MouseEvent& e) {
    int selected_step = getHoveredStep(e.getPosition().x);
    if (selected_step < 0)
        return;

    float new_value = -2.0f * e.getPosition().y / getHeight() + 1.0f;
    sequence_[selected_step] = std::max(std::min(new_value, 1.0f), -1.0f);
    repaint();
}

int GraphicalStepSequencer::getHoveredStep(float x_position) {
    int selected_step = num_steps_ * x_position / getWidth();
    if (x_position >= 0 && selected_step >= 0 && selected_step < num_steps_)
        return selected_step;
    return -1;
}

void GraphicalStepSequencer::updateHover(int step_index) {
    if (step_index == highlighted_step_)
        return;
    highlighted_step_ = step_index;
    repaint();
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="GraphicalStepSequencer" componentName=""
                 parentClasses="public Component" constructorParams="int num_steps"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="600" initialHeight="400">
  <METHODS>
    <METHOD name="mouseMove (const MouseEvent&amp; e)"/>
    <METHOD name="mouseDrag (const MouseEvent&amp; e)"/>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
    <METHOD name="mouseExit (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ff303030"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
