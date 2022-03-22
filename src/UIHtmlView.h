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

#ifndef __JUCE_HEADER_A50A8B6E25702864__
#define __JUCE_HEADER_A50A8B6E25702864__

//[Headers]     -- You can add your own extra header files here --
#include "App.h"
#include "UIEditorToolbar.h"

class NavItem;
//[/Headers]

//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class UIHtmlView : public UiEditor, public juce::Button::Listener, public juce::AsyncUpdater
{
  public:
    //==============================================================================
    UIHtmlView(AppInstanceStore *const app_instance_store_);
    ~UIHtmlView();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    AppInstanceStore *const _app_instance_store;

    juce::URL load_async_url;
    virtual void handleAsyncUpdate() override;
    void on_close_clicked() override;

    juce::Thread *pending_download;

  public:
    bool try_open_url(const juce::URL &source_);
    bool try_open_question_mark();

  private:
    friend class HTMLPArser;
    friend class NavItem;
    bool open_url(const juce::URL &source_, bool and_download_complete_nav_content_ = false,
                  bool show_content_ = true);
    bool open_question_mark_content(const juce::URL &request_for_ = MANUAL_URL + "beginner/tools",
                                    bool force_redownload_ = false);
    void select_item_with_url(const juce::URL &url_);
    juce::CriticalSection lock;
    int nav_is_parsed;
    juce::URL current_url;
    juce::File current_cache_folder;
    int current_height;
    void add_text_part(const juce::String &text_, int height_ /* 7 text, 1 title, 2 title (h2) */,
                       int white_spaces_before_, bool show_content_,
                       juce::Colour col_ = juce::Colour(0x00000000), bool make_selectable = false);
    void add_image(const juce::String &url_, bool show_content_);

    NavItem *last_added_item;
    int last_deppnes;
    void add_nav_link(const juce::String &text_, const juce::URL &target_, int deepness_,
                      bool and_open_it = false);

    Component *content_wrapper;
    juce::OwnedArray<juce::TextEditor> editors;
    juce::OwnedArray<juce::ImageButton> images;
    juce::Array<NavItem *> items;

    void clear_all_views();
    void block_views(bool block_);

    volatile bool can_something_selected;
    //[/UserMethods]

    void paint(juce::Graphics &g) override;
    void resized() override;
    void buttonClicked(juce::Button *buttonThatWasClicked) override;

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::Viewport> viewport;
    std::unique_ptr<juce::TreeView> treeView;
    std::unique_ptr<UiEditorToolbar> toolbar;
    std::unique_ptr<juce::TextButton> update;
    std::unique_ptr<juce::TextButton> forum;
    std::unique_ptr<juce::Label> label;
    std::unique_ptr<juce::Label> label2;
    std::unique_ptr<juce::TextButton> mail;
    std::unique_ptr<juce::Label> label3;
    std::unique_ptr<juce::TextButton> online;
    std::unique_ptr<juce::Label> label4;
    std::unique_ptr<FingerDrag> tree_view_dragger;
    std::unique_ptr<FingerDrag> viewport_dragger;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UIHtmlView)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_A50A8B6E25702864__
