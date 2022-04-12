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

#ifndef MONO_LOOKANDFEEL
#define MONO_LOOKANDFEEL

#include "App.h"

//==============================================================================
/**
    @see LookAndFeel_V2
*/
class UiLookAndFeel : public juce::LookAndFeel_V2, public juce::DeletedAtShutdown
{
  public:
    juce::Font defaultFont;

    UiLookAndFeel();
    ~UiLookAndFeel() { clearSingletonInstance(); }

    juce_DeclareSingleton(UiLookAndFeel, false)
        //==============================================================================
        void drawButtonBackground(juce::Graphics &, juce::Button &button,
                                  const juce::Colour &backgroundColour, bool isMouseOverButton,
                                  bool isButtonDown) override;

    juce::Font getTextButtonFont(juce::TextButton &, int buttonHeight = 0) override;

    void drawButtonText(juce::Graphics &, juce::TextButton &button, bool isMouseOverButton,
                        bool isButtonDown) override;

    void drawToggleButton(juce::Graphics &, juce::ToggleButton &button, bool isMouseOverButton,
                          bool isButtonDown) override;

    void changeToggleButtonWidthToFitText(juce::ToggleButton &) override;

    void drawTickBox(juce::Graphics &, juce::Component &, float x, float y, float w, float h,
                     bool ticked, bool isEnabled, bool isMouseOverButton,
                     bool isButtonDown) override;

    void drawDrawableButton(juce::Graphics &, juce::DrawableButton &, bool isMouseOverButton,
                            bool isButtonDown) override;

    //==============================================================================
    juce::AlertWindow *createAlertWindow(const juce::String &title, const juce::String &message,
                                         const juce::String &button1, const juce::String &button2,
                                         const juce::String &button3,
                                         juce::AlertWindow::AlertIconType iconType, int numButtons,
                                         juce::Component *associatedComponent) override;

    void drawAlertBox(juce::Graphics &, juce::AlertWindow &, const juce::Rectangle<int> &textArea,
                      juce::TextLayout &) override;
    int getAlertBoxWindowFlags() override;
    int getAlertWindowButtonHeight() override;
    juce::Font getAlertWindowMessageFont() override;
    juce::Font getAlertWindowFont() override;

    //==============================================================================
    void drawProgressBar(juce::Graphics &, juce::ProgressBar &, int width, int height,
                         double progress, const juce::String &textToShow) override;
    void drawSpinningWaitAnimation(juce::Graphics &, const juce::Colour &colour, int x, int y,
                                   int w, int h) override;

    //==============================================================================
    bool areScrollbarButtonsVisible() override;
    void drawScrollbarButton(juce::Graphics &g, juce::ScrollBar &, int width, int height,
                             int buttonDirection, bool isScrollbarVertical, bool isMouseOverButton,
                             bool isButtonDown) override;

    void drawScrollbar(juce::Graphics &g, juce::ScrollBar &, int x, int y, int width, int height,
                       bool isScrollbarVertical, int thumbStartPosition, int thumbSize,
                       bool isMouseOver, bool isMouseDown) override;

    juce::ImageEffectFilter *getScrollbarEffect() override;
    int getMinimumScrollbarThumbSize(juce::ScrollBar &) override;
    int getDefaultScrollbarWidth() override;
    int getScrollbarButtonSize(juce::ScrollBar &scrollbar) override;

    //==============================================================================
    juce::Path getTickShape(float height) override;
    juce::Path getCrossShape(float height) override;

    //==============================================================================
    void drawTreeviewPlusMinusBox(juce::Graphics &, const juce::Rectangle<float> &area,
                                  juce::Colour backgroundColour, bool isOpen,
                                  bool isMouseOver) override;
    bool areLinesDrawnForTreeView(juce::TreeView &) override;
    int getTreeViewIndentSize(juce::TreeView &) override;

    //==============================================================================
    void fillTextEditorBackground(juce::Graphics &, int width, int height,
                                  juce::TextEditor &) override;
    void drawTextEditorOutline(juce::Graphics &, int width, int height,
                               juce::TextEditor &) override;
    juce::CaretComponent *createCaretComponent(juce::Component *keyFocusOwner) override;

    //==============================================================================
    const juce::Drawable *getDefaultFolderImage() override;
    const juce::Drawable *getDefaultDocumentFileImage() override;

    juce::AttributedString createFileChooserHeaderText(const juce::String &title,
                                                       const juce::String &instructions) override;

    void drawFileBrowserRow(juce::Graphics &, int width, int height, const juce::String &filename,
                            juce::Image *icon, const juce::String &fileSizeDescription,
                            const juce::String &fileTimeDescription, bool isDirectory,
                            bool isItemSelected, int itemIndex,
                            juce::DirectoryContentsDisplayComponent &); // override;

    juce::Button *createFileBrowserGoUpButton() override;

    void layoutFileBrowserComponent(juce::FileBrowserComponent &,
                                    juce::DirectoryContentsDisplayComponent *,
                                    juce::FilePreviewComponent *, juce::ComboBox *currentPathBox,
                                    juce::TextEditor *filenameBox,
                                    juce::Button *goUpButton) override;

    //==============================================================================
    void drawBubble(juce::Graphics &, juce::BubbleComponent &, const juce::Point<float> &tip,
                    const juce::Rectangle<float> &body) override;

    void drawLasso(juce::Graphics &, juce::Component &) override;

    //==============================================================================
    void drawPopupMenuBackground(juce::Graphics &, int width, int height) override;

    void drawPopupMenuItem(juce::Graphics &, const juce::Rectangle<int> &area, bool isSeparator,
                           bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu,
                           const juce::String &text, const juce::String &shortcutKeyText,
                           const juce::Drawable *icon, const juce::Colour *textColour) override;

    juce::Font getPopupMenuFont() override;

    void drawPopupMenuUpDownArrow(juce::Graphics &, int width, int height,
                                  bool isScrollUpArrow) override;

    void getIdealPopupMenuItemSize(const juce::String &text, bool isSeparator,
                                   int standardMenuItemHeight, int &idealWidth,
                                   int &idealHeight) override;
    int getMenuWindowFlags() override;

    void drawMenuBarBackground(juce::Graphics &, int width, int height, bool isMouseOverBar,
                               juce::MenuBarComponent &) override;
    int getMenuBarItemWidth(juce::MenuBarComponent &, int itemIndex,
                            const juce::String &itemText) override;
    juce::Font getMenuBarFont(juce::MenuBarComponent &, int itemIndex,
                              const juce::String &itemText) override;
    int getDefaultMenuBarHeight() override;

    void drawMenuBarItem(juce::Graphics &, int width, int height, int itemIndex,
                         const juce::String &itemText, bool isMouseOverItem, bool isMenuOpen,
                         bool isMouseOverBar, juce::MenuBarComponent &) override;

    //==============================================================================
    void drawComboBox(juce::Graphics &, int width, int height, bool isButtonDown, int buttonX,
                      int buttonY, int buttonW, int buttonH, juce::ComboBox &) override;
    juce::Font getComboBoxFont(juce::ComboBox &) override;
    juce::Label *createComboBoxTextBox(juce::ComboBox &) override;
    void positionComboBoxText(juce::ComboBox &, juce::Label &) override;

    //==============================================================================
    void drawLabel(juce::Graphics &, juce::Label &) override;
    juce::Font getLabelFont(juce::Label &) override;

    //==============================================================================
    void drawLinearSlider(juce::Graphics &, int x, int y, int width, int height, float sliderPos,
                          float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle,
                          juce::Slider &) override;

    void drawLinearSliderBackground(juce::Graphics &, int x, int y, int width, int height,
                                    float sliderPos, float minSliderPos, float maxSliderPos,
                                    const juce::Slider::SliderStyle, juce::Slider &) override;

    void drawLinearSliderThumb(juce::Graphics &, int x, int y, int width, int height,
                               float sliderPos, float minSliderPos, float maxSliderPos,
                               const juce::Slider::SliderStyle, juce::Slider &) override;

    void drawRotarySlider(juce::Graphics &, int x, int y, int width, int height,
                          float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle,
                          juce::Slider &) override;

    int getSliderThumbRadius(juce::Slider &) override;
    juce::Button *createSliderButton(juce::Slider &, bool isIncrement) override;
    juce::Label *createSliderTextBox(juce::Slider &) override;
    juce::ImageEffectFilter *getSliderEffect(juce::Slider &) override;
    juce::Font getSliderPopupFont(juce::Slider &) override;
    int getSliderPopupPlacement(juce::Slider &) override;

    //==============================================================================
    void getTooltipSize(const juce::String &tipText, int &width, int &height); // override;
    void drawTooltip(juce::Graphics &, const juce::String &text, int width, int height) override;

    //==============================================================================
    juce::Button *createFilenameComponentBrowseButton(const juce::String &text) override;
    void layoutFilenameComponent(juce::FilenameComponent &filenameComp, juce::ComboBox *filenameBox,
                                 juce::Button *browseButton) override;

    //==============================================================================
    void drawConcertinaPanelHeader(juce::Graphics &, const juce::Rectangle<int> &area,
                                   bool isMouseOver, bool isMouseDown, juce::ConcertinaPanel &,
                                   juce::Component &panel) override;

    //==============================================================================
    void drawCornerResizer(juce::Graphics &, int w, int h, bool isMouseOver,
                           bool isMouseDragging) override;
    void drawResizableFrame(juce::Graphics &, int w, int h, const juce::BorderSize<int> &) override;

    //==============================================================================
    void fillResizableWindowBackground(juce::Graphics &, int w, int h,
                                       const juce::BorderSize<int> &,
                                       juce::ResizableWindow &) override;
    void drawResizableWindowBorder(juce::Graphics &, int w, int h,
                                   const juce::BorderSize<int> &border,
                                   juce::ResizableWindow &) override;

    //==============================================================================
    void drawDocumentWindowTitleBar(juce::DocumentWindow &, juce::Graphics &, int w, int h,
                                    int titleSpaceX, int titleSpaceW, const juce::Image *icon,
                                    bool drawTitleTextOnLeft) override;

    juce::Button *createDocumentWindowButton(int buttonType) override;

    void positionDocumentWindowButtons(juce::DocumentWindow &, int titleBarX, int titleBarY,
                                       int titleBarW, int titleBarH, juce::Button *minimiseButton,
                                       juce::Button *maximiseButton, juce::Button *closeButton,
                                       bool positionTitleBarButtonsOnLeft) override;

    //==============================================================================
    juce::DropShadower *createDropShadowerForComponent(juce::Component *); // override;

    //==============================================================================
    void drawStretchableLayoutResizerBar(juce::Graphics &, int w, int h, bool isVerticalBar,
                                         bool isMouseOver, bool isMouseDragging) override;

    //==============================================================================
    void drawGroupComponentOutline(juce::Graphics &, int w, int h, const juce::String &text,
                                   const juce::Justification &, juce::GroupComponent &) override;

    //==============================================================================
    int getTabButtonSpaceAroundImage() override;
    int getTabButtonOverlap(int tabDepth) override;
    int getTabButtonBestWidth(juce::TabBarButton &, int tabDepth) override;
    juce::Rectangle<int> getTabButtonExtraComponentBounds(const juce::TabBarButton &,
                                                          juce::Rectangle<int> &textArea,
                                                          juce::Component &extraComp) override;

    void drawTabButton(juce::TabBarButton &, juce::Graphics &, bool isMouseOver,
                       bool isMouseDown) override;
    void drawTabButtonText(juce::TabBarButton &, juce::Graphics &, bool isMouseOver,
                           bool isMouseDown) override;
    void drawTabbedButtonBarBackground(juce::TabbedButtonBar &, juce::Graphics &) override;
    void drawTabAreaBehindFrontButton(juce::TabbedButtonBar &, juce::Graphics &, int w,
                                      int h) override;

    void createTabButtonShape(juce::TabBarButton &, juce::Path &path, bool isMouseOver,
                              bool isMouseDown) override;
    void fillTabButtonShape(juce::TabBarButton &, juce::Graphics &, const juce::Path &path,
                            bool isMouseOver, bool isMouseDown) override;

    juce::Button *createTabBarExtrasButton() override;

    //==============================================================================
    void drawImageButton(juce::Graphics &, juce::Image *, int imageX, int imageY, int imageW,
                         int imageH, const juce::Colour &overlayColour, float imageOpacity,
                         juce::ImageButton &) override;

    //==============================================================================
    void drawTableHeaderBackground(juce::Graphics &, juce::TableHeaderComponent &) override;

    void drawTableHeaderColumn(juce::Graphics &, const juce::String &columnName, int columnId,
                               int width, int height, bool isMouseOver, bool isMouseDown,
                               int columnFlags); // override;

    //==============================================================================
    void paintToolbarBackground(juce::Graphics &, int width, int height, juce::Toolbar &) override;

    juce::Button *createToolbarMissingItemsButton(juce::Toolbar &) override;

    void paintToolbarButtonBackground(juce::Graphics &, int width, int height, bool isMouseOver,
                                      bool isMouseDown, juce::ToolbarItemComponent &) override;

    void paintToolbarButtonLabel(juce::Graphics &, int x, int y, int width, int height,
                                 const juce::String &text, juce::ToolbarItemComponent &) override;

    //==============================================================================
    void drawPropertyPanelSectionHeader(juce::Graphics &, const juce::String &name, bool isOpen,
                                        int width, int height) override;
    void drawPropertyComponentBackground(juce::Graphics &, int width, int height,
                                         juce::PropertyComponent &) override;
    void drawPropertyComponentLabel(juce::Graphics &, int width, int height,
                                    juce::PropertyComponent &) override;
    juce::Rectangle<int> getPropertyComponentContentPosition(juce::PropertyComponent &) override;

    //==============================================================================
    void drawCallOutBoxBackground(juce::CallOutBox &, juce::Graphics &, const juce::Path &path,
                                  juce::Image &cachedImage) override;

    //==============================================================================
    void drawLevelMeter(juce::Graphics &, int width, int height, float level) override;

    void drawKeymapChangeButton(juce::Graphics &, int width, int height, juce::Button &button,
                                const juce::String &keyDescription) override;

    //==============================================================================
    /** Draws a 3D raised (or indented) bevel using two colours.

        The bevel is drawn inside the given rectangle, and greater bevel thicknesses
        extend inwards.

        The top-left colour is used for the top- and left-hand edges of the
        bevel; the bottom-right colour is used for the bottom- and right-hand
        edges.

        If useGradient is true, then the bevel fades out to make it look more curved
        and less angular. If sharpEdgeOnOutside is true, the outside of the bevel is
        sharp, and it fades towards the centre; if sharpEdgeOnOutside is false, then
        the centre edges are sharp and it fades towards the outside.
    */
    static void drawBevel(juce::Graphics &, int x, int y, int width, int height, int bevelThickness,
                          const juce::Colour &topLeftColour = juce::Colours::white,
                          const juce::Colour &bottomRightColour = juce::Colours::black,
                          bool useGradient = true, bool sharpEdgeOnOutside = true);

    /** Utility function to draw a shiny, glassy circle (for round LED-type buttons). */
    static void drawGlassSphere(juce::Graphics &, float x, float y, float diameter,
                                const juce::Colour &colour, float outlineThickness) noexcept;

    static void drawGlassPointer(juce::Graphics &, float x, float y, float diameter,
                                 const juce::Colour &colour, float outlineThickness,
                                 int direction) noexcept;

    /** Utility function to draw a shiny, glassy oblong (for text buttons). */
    static void drawGlassLozenge(juce::Graphics &, float x, float y, float width, float height,
                                 const juce::Colour &colour, float outlineThickness,
                                 float cornerSize, bool flatOnLeft, bool flatOnRight,
                                 bool flatOnTop, bool flatOnBottom) noexcept;

  private:
    //==============================================================================
    std::unique_ptr<juce::Drawable> folderImage, documentImage;

    void drawShinyButtonShape(juce::Graphics &, float x, float y, float w, float h,
                              float maxCornerSize, const juce::Colour &baseColour,
                              float strokeWidth, bool flatOnLeft, bool flatOnRight, bool flatOnTop,
                              bool flatOnBottom) noexcept;

    class GlassWindowButton;
    class SliderLabelComp;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiLookAndFeel)
};

#endif // JUCE_LOOKANDFEEL_V2_H_INCLUDED
