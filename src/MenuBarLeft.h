/*
** B-Step is Free and Open Source Software
**
** B-Step is made available under the Gnu General Public License, v3.0
** https://www.gnu.org/licenses/gpl-3.0.en.html; The authors of the code
** reserve the right to re-license their contributions under the MIT license in the
** future at the discretion of the project maintainers.
**
** Copyright 2014-2022 by various individuals as described by the git transaction log
**
** All source at: https://github.com/surge-synthesizer/b-step.git
**
** B-Step was a commercial product from 2014-2022, with copyright and ownership
** in that period held by Thomas Arndt at Monoplugs. Thomas made B-Step
** open source in March 2022.
*/

#ifndef __JUCE_HEADER_A2547B656C4F7F86__
#define __JUCE_HEADER_A2547B656C4F7F86__

#include "App.h"

class AppInstanceStore;
class GstepAudioProcessorEditor;

class ModelBase;

//==============================================================================
class MenuBarLeft : public juce::Component, public juce::Button::Listener
{
  public:
    //==============================================================================
    MenuBarLeft(AppInstanceStore *const app_instance_store_,
                GstepAudioProcessorEditor *const main_window_);
    ~MenuBarLeft();

    //==============================================================================
    AppInstanceStore *const _app_instance_store;
    GstepAudioProcessorEditor *const _main_window;

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
  public:
    void refresh_ui(juce::Array<Component *> &components_to_repaint_);

  private:
    void set_user_mode();

    void paint(juce::Graphics &g);
    void resized();
    void buttonClicked(juce::Button *buttonThatWasClicked);

    // Binary resources:
    static const char *_5stars_svg;
    static const int _5stars_svgSize;
    static const char *_3stars_svg;
    static const int _3stars_svgSize;
    static const char *_1stars_svg;
    static const int _1stars_svgSize;
    static const char *_5starson_svg;
    static const int _5starson_svgSize;
    static const char *_3starson_svg;
    static const int _3starson_svgSize;
    static const char *_1starson_svg;
    static const int _1starson_svgSize;

  private:
    //==============================================================================
    std::unique_ptr<ModelBase> button_layer_1;
    std::unique_ptr<ModelBase> button_layer_2;
    std::unique_ptr<ModelBase> button_layer_3;
    std::unique_ptr<ModelBase> button_layer_4;
    std::unique_ptr<ModelBase> button_layer_5;
    std::unique_ptr<ModelBase> button_layer_6;
    std::unique_ptr<ModelBase> button_layer_7;
    std::unique_ptr<juce::ImageButton> pb_lite_mode;
    std::unique_ptr<juce::ImageButton> pb_semi_mode;
    std::unique_ptr<juce::ImageButton> pb_pro_mode;
    std::unique_ptr<juce::Drawable> drawable1;
    std::unique_ptr<juce::Drawable> drawable2;
    std::unique_ptr<juce::Drawable> drawable3;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MenuBarLeft)
};

#endif // __JUCE_HEADER_A2547B656C4F7F86__
