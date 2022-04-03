/*
  ==============================================================================

   This file is part of the JUCE library.
   Copyright (c) 2013 - Raw Material Software Ltd.

   Permission is granted to use this software under the terms of either:
   a) the GPL v2 (or any later version)
   b) the Affero GPL v3

   Details of these licenses can be found at: www.gnu.org/licenses

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

   ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.juce.com for more information.

  ==============================================================================
*/

#include "UiLookAndFeel.h"
#include "BinaryData.h"

juce_ImplementSingleton(UiLookAndFeel)

    namespace LookAndFeelHelpers
{
    static juce::Colour createBaseColour(juce::Colour buttonColour, bool hasKeyboardFocus,
                                         bool isMouseOverButton, bool isButtonDown) noexcept
    {
        const float sat = hasKeyboardFocus ? 1.3f : 0.9f;
        const juce::Colour baseColour(buttonColour.withMultipliedSaturation(sat));

        if (isButtonDown)
            return baseColour.contrasting(0.2f);
        if (isMouseOverButton)
            return baseColour.contrasting(0.1f);

        return baseColour;
    }

    static juce::TextLayout layoutTooltipText(const juce::String &text,
                                              juce::Colour colour) noexcept
    {
        const float tooltipFontSize = 13.0f;
        const int maxToolTipWidth = 400;

        juce::AttributedString s;
        s.setJustification(juce::Justification::centred);
        s.append(text, juce::Font(tooltipFontSize, juce::Font::bold), colour);

        juce::TextLayout tl;
        tl.createLayoutWithBalancedLineLengths(s, (float)maxToolTipWidth);
        return tl;
    }
}

//==============================================================================
UiLookAndFeel::UiLookAndFeel()
{
    BOOT(UiLookAndFeel);

    // initialise the standard set of colours..
    const std::uint32_t textButtonColour = 0xffbbbbff;
    const std::uint32_t textHighlightColour = 0x401111ee;
    const std::uint32_t standardOutlineColour = 0xb2808080;

    OUT_LOG("BOOT::UiLookAndFeel::SET-COLOURS");

    static const std::uint32_t standardColours[] = {
        juce::TextButton::buttonColourId,
        0xff000000,
        juce::TextButton::buttonOnColourId,
        0xff4444ff,
        juce::TextButton::textColourOnId,
        0xff000000,
        juce::TextButton::textColourOffId,
        0xff000000,

        juce::ToggleButton::textColourId,
        0xff000000,

        juce::TextEditor::backgroundColourId,
        0xffffffff,
        juce::TextEditor::textColourId,
        0xff000000,
        juce::TextEditor::highlightColourId,
        textHighlightColour,
        juce::TextEditor::highlightedTextColourId,
        0xff000000,
        juce::TextEditor::outlineColourId,
        0x00000000,
        juce::TextEditor::focusedOutlineColourId,
        textButtonColour,
        juce::TextEditor::shadowColourId,
        0x38000000,

        juce::CaretComponent::caretColourId,
        0xff000000,

        juce::Label::backgroundColourId,
        0x00000000,
        juce::Label::textColourId,
        GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR,
        juce::Label::outlineColourId,
        0x00000000,

        juce::ScrollBar::backgroundColourId,
        0x00000000,
        juce::ScrollBar::thumbColourId,
        0xffffffff,

        juce::TreeView::linesColourId,
        0x4c000000,
        juce::TreeView::backgroundColourId,
        0x00000000,
        juce::TreeView::dragAndDropIndicatorColourId,
        0x80ff0000,
        juce::TreeView::selectedItemBackgroundColourId,
        0x00000000,

        juce::PopupMenu::backgroundColourId,
        0xffffffff,
        juce::PopupMenu::textColourId,
        0xff000000,
        juce::PopupMenu::headerTextColourId,
        0xff000000,
        juce::PopupMenu::highlightedTextColourId,
        0xffffffff,
        juce::PopupMenu::highlightedBackgroundColourId,
        0x991111aa,

        juce::ComboBox::buttonColourId,
        0xffbbbbff,
        juce::ComboBox::outlineColourId,
        0xffff0000,
        juce::ComboBox::textColourId,
        0xffff0000,
        juce::ComboBox::backgroundColourId,
        0xff000000,
        juce::ComboBox::arrowColourId,
        0x99000000,

        juce::PropertyComponent::backgroundColourId,
        0x66ffffff,
        juce::PropertyComponent::labelTextColourId,
        GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR,

        juce::TextPropertyComponent::backgroundColourId,
        0xffffffff,
        juce::TextPropertyComponent::textColourId,
        0xffffffff,
        juce::TextPropertyComponent::outlineColourId,
        standardOutlineColour,

        juce::ListBox::backgroundColourId,
        0xffffffff,
        juce::ListBox::outlineColourId,
        standardOutlineColour,
        juce::ListBox::textColourId,
        0xff000000,

        juce::Slider::backgroundColourId,
        0x00000000,
        juce::Slider::thumbColourId,
        textButtonColour,
        juce::Slider::trackColourId,
        0x7fffffff,
        juce::Slider::rotarySliderFillColourId,
        0x00000000,
        juce::Slider::rotarySliderOutlineColourId,
        0x66000000,
        juce::Slider::textBoxTextColourId,
        juce::Colour(juce::Colours::yellowgreen).getARGB(),
        juce::Slider::textBoxBackgroundColourId,
        0xff000000,
        juce::Slider::textBoxHighlightColourId,
        textHighlightColour,
        juce::Slider::textBoxOutlineColourId,
        GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR,

        juce::ResizableWindow::backgroundColourId,
        0xff777777,
        // DocumentWindow::textColourId,               0xff000000, // (this is deliberately not set)

        juce::AlertWindow::backgroundColourId,
        0xff161616,
        juce::AlertWindow::textColourId,
        0xfff0f8ff,
        juce::AlertWindow::outlineColourId,
        0xff00ffff,

        juce::ProgressBar::backgroundColourId,
        0xffeeeeee,
        juce::ProgressBar::foregroundColourId,
        0xffaaaaee,

        juce::TooltipWindow::backgroundColourId,
        0xffeeeebb,
        juce::TooltipWindow::textColourId,
        0xff000000,
        juce::TooltipWindow::outlineColourId,
        0x4c000000,

        juce::TabbedComponent::backgroundColourId,
        0x00000000,
        juce::TabbedComponent::outlineColourId,
        0xff777777,
        juce::TabbedButtonBar::tabOutlineColourId,
        0x80000000,
        juce::TabbedButtonBar::frontOutlineColourId,
        0x90000000,

        juce::Toolbar::backgroundColourId,
        0xfff6f8f9,
        juce::Toolbar::separatorColourId,
        0x4c000000,
        juce::Toolbar::buttonMouseOverBackgroundColourId,
        0x4c0000ff,
        juce::Toolbar::buttonMouseDownBackgroundColourId,
        0x800000ff,
        juce::Toolbar::labelTextColourId,
        GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR,
        juce::Toolbar::editingModeOutlineColourId,
        0xffff0000,

        juce::DrawableButton::textColourId,
        0xff000000,
        juce::DrawableButton::textColourOnId,
        0xff000000,
        juce::DrawableButton::backgroundColourId,
        0x00000000,
        juce::DrawableButton::backgroundOnColourId,
        0xaabbbbff,

        juce::HyperlinkButton::textColourId,
        0xcc1111ee,

        juce::GroupComponent::outlineColourId,
        0x66000000,
        juce::GroupComponent::textColourId,
        0xff000000,

        juce::BubbleComponent::backgroundColourId,
        0xeeeeeebb,
        juce::BubbleComponent::outlineColourId,
        0x77000000,

        juce::DirectoryContentsDisplayComponent::highlightColourId,
        textHighlightColour,
        juce::DirectoryContentsDisplayComponent::textColourId,
        0xff000000,

        0x1000440,
        /*LassoComponent::lassoFillColourId*/ 0x66dddddd,
        0x1000441,
        /*LassoComponent::lassoOutlineColourId*/ 0x99111111,

        0x1005000,
        /*MidiKeyboardComponent::whiteNoteColourId*/ 0xffffffff,
        0x1005001,
        /*MidiKeyboardComponent::blackNoteColourId*/ 0xff000000,
        0x1005002,
        /*MidiKeyboardComponent::keySeparatorLineColourId*/ 0x66000000,
        0x1005003,
        /*MidiKeyboardComponent::mouseOverKeyOverlayColourId*/
        GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR,
        0x1005004,
        /*MidiKeyboardComponent::keyDownOverlayColourId*/
        GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR,
        0x1005005,
        /*MidiKeyboardComponent::textLabelColourId*/ 0xff000000,
        0x1005006,
        /*MidiKeyboardComponent::upDownButtonBackgroundColourId*/ 0xffd3d3d3,
        0x1005007,
        /*MidiKeyboardComponent::upDownButtonArrowColourId*/ 0xff000000,
        0x1005008,
        /*MidiKeyboardComponent::shadowColourId*/ 0x4c000000,

        0x1004500,
        /*CodeEditorComponent::backgroundColourId*/ 0xffffffff,
        0x1004502,
        /*CodeEditorComponent::highlightColourId*/ textHighlightColour,
        0x1004503,
        /*CodeEditorComponent::defaultTextColourId*/ 0xff000000,
        0x1004504,
        /*CodeEditorComponent::lineNumberBackgroundId*/ 0x44999999,
        0x1004505,
        /*CodeEditorComponent::lineNumberTextId*/ 0x44000000,

        0x1007000,
        /*ColourSelector::backgroundColourId*/ 0xffe5e5e5,
        0x1007001,
        /*ColourSelector::labelTextColourId*/ 0xff000000,

        0x100ad00,
        /*KeyMappingEditorComponent::backgroundColourId*/ 0x00000000,
        0x100ad01,
        /*KeyMappingEditorComponent::textColourId*/ 0xff000000,

        juce::FileSearchPathListComponent::backgroundColourId,
        0xffffffff,

        juce::FileChooserDialogBox::titleTextColourId,
        GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR,
    };

    OUT_LOG("BOOT::UiLookAndFeel::SET-COLOURS::DONE");

    for (int i = 0; i < juce::numElementsInArray(standardColours); i += 2)
        setColour((int)standardColours[i], juce::Colour((std::uint32_t)standardColours[i + 1]));

    defaultFont = juce::Font(juce::Typeface::createSystemTypefaceFor(
        BinaryData::FjallaOneRegular_ttf, BinaryData::FjallaOneRegular_ttfSize));
}

//==============================================================================
void UiLookAndFeel::drawButtonBackground(juce::Graphics &g, juce::Button &button,
                                         const juce::Colour &backgroundColour,
                                         bool isMouseOverButton, bool isButtonDown)
{
    // isMouseOverButton
    juce::Colour color_1 = isButtonDown ? juce::Colour(backgroundColour).darker(0.4f)
                                        : juce::Colour(backgroundColour).brighter(0.25f);
    juce::Colour color_2 = isButtonDown ? juce::Colour(backgroundColour).brighter(0.3f)
                                        : juce::Colour(backgroundColour).darker(0.3f);

    const int width = button.getWidth();
    const int height = button.getHeight();

    g.setGradientFill(juce::ColourGradient(
        color_1, 0.0f, 0.0f, juce::Colour(backgroundColour).darker(0.3f), 0.0f, height, false));
    g.fillRoundedRectangle(1, 1, width - 2, height - 2, 4);

    g.setColour(juce::Colour(0xff333333));
    g.drawRoundedRectangle(1, 1, width - 2, height - 2, 4, 1.5);
}

juce::Font UiLookAndFeel::getTextButtonFont(juce::TextButton &button, int buttonHeigh)
{
    return defaultFont; // button.getFont();
}

void UiLookAndFeel::drawButtonText(juce::Graphics &g, juce::TextButton &button,
                                   bool /*isMouseOverButton*/, bool /*isButtonDown*/)
{
    juce::Font font(getTextButtonFont(button));
    g.setFont(font.withHeight(0.6 * button.getHeight()));

    if (juce::Colour(button.findColour(juce::TextButton::buttonColourId)).getBrightness() < 0.3 &&
        button.findColour(juce::TextButton::textColourOffId).getBrightness() < 0.3)
        g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    else
        g.setColour(juce::Colour(button.findColour(juce::TextButton::textColourOffId)
                                     .withMultipliedAlpha(button.isEnabled() ? 1.0f : 0.5f)));

    const int yIndent = juce::jmin(4, button.proportionOfHeight(0.3f));
    const int cornerSize = juce::jmin(button.getHeight(), button.getWidth()) / 2;

    const int fontHeight = juce::roundToInt(font.getHeight() * 0.6f);
    const int leftIndent =
        juce::jmin(fontHeight, 2 + cornerSize / (button.isConnectedOnLeft() ? 4 : 2));
    const int rightIndent =
        juce::jmin(fontHeight, 2 + cornerSize / (button.isConnectedOnRight() ? 4 : 2));

    g.drawFittedText(button.getButtonText(), leftIndent, yIndent,
                     button.getWidth() - leftIndent - rightIndent, button.getHeight() - yIndent * 2,
                     juce::Justification::centred, 2, 0.5);
}

void UiLookAndFeel::drawTickBox(juce::Graphics &g, juce::Component &component, float x, float y,
                                float w, float h, const bool ticked, const bool isEnabled,
                                const bool isMouseOverButton, const bool isButtonDown)
{
    g.setColour(juce::Colours::black);
    g.fillRect(int(x) - 1, int(y) - 1, int(w), int(h));

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    g.drawRect(int(x) - 1, int(y) - 1, int(w), int(h), 1);

    if (ticked)
    {
        juce::Path tick;
        tick.startNewSubPath(1.5f, 3.0f);
        tick.lineTo(3.0f, 6.0f);
        tick.lineTo(6.0f, 0.0f);

        g.setColour(juce::Colours::yellowgreen);

        const juce::AffineTransform trans(
            juce::AffineTransform::scale(w / 9.0f, h / 9.0f).translated(x, y));

        g.strokePath(tick, juce::PathStrokeType(2.5f), trans);
    }
}

void UiLookAndFeel::drawToggleButton(juce::Graphics &g, juce::ToggleButton &button,
                                     bool isMouseOverButton, bool isButtonDown)
{
    float prop_h = 1.f / 25.f * button.getHeight();
    float top = prop_h * 4.f;
    float rect_size = button.getHeight() - top * 2;
    drawTickBox(g, button, 1, top, rect_size, rect_size, button.getToggleState(),
                button.isEnabled(), isMouseOverButton, isButtonDown);
}

void UiLookAndFeel::changeToggleButtonWidthToFitText(juce::ToggleButton &button) {}

void UiLookAndFeel::drawDrawableButton(juce::Graphics &g, juce::DrawableButton &button,
                                       bool /*isMouseOverButton*/, bool /*isButtonDown*/)
{
    bool toggleState = button.getToggleState();

    g.fillAll(button.findColour(toggleState ? juce::DrawableButton::backgroundOnColourId
                                            : juce::DrawableButton::backgroundColourId));

    const int textH = (button.getStyle() == juce::DrawableButton::ImageAboveTextLabel)
                          ? juce::jmin(16, button.proportionOfHeight(0.25f))
                          : 0;

    if (textH > 0)
    {
        g.setFont((float)textH);

        g.setColour(button
                        .findColour(toggleState ? juce::DrawableButton::textColourOnId
                                                : juce::DrawableButton::textColourId)
                        .withMultipliedAlpha(button.isEnabled() ? 1.0f : 0.4f));

        g.drawFittedText(button.getButtonText(), 2, button.getHeight() - textH - 1,
                         button.getWidth() - 4, textH, juce::Justification::centred, 1);
    }
}

//==============================================================================
juce::AlertWindow *UiLookAndFeel::createAlertWindow(
    const juce::String &title, const juce::String &message, const juce::String &button1,
    const juce::String &button2, const juce::String &button3,
    juce::AlertWindow::AlertIconType iconType, int numButtons, juce::Component *associatedComponent)
{
    juce::AlertWindow *aw = new juce::AlertWindow(title, message, iconType, associatedComponent);

    if (numButtons == 1)
    {
        aw->addButton(button1, 0, juce::KeyPress(juce::KeyPress::escapeKey),
                      juce::KeyPress(juce::KeyPress::returnKey));
    }
    else
    {
        const juce::KeyPress button1ShortCut((int)juce::CharacterFunctions::toLowerCase(button1[0]),
                                             0, 0);
        juce::KeyPress button2ShortCut((int)juce::CharacterFunctions::toLowerCase(button2[0]), 0,
                                       0);
        if (button1ShortCut == button2ShortCut)
            button2ShortCut = juce::KeyPress();

        if (numButtons == 2)
        {
            aw->addButton(button1, 1, juce::KeyPress(juce::KeyPress::returnKey), button1ShortCut);
            aw->addButton(button2, 0, juce::KeyPress(juce::KeyPress::escapeKey), button2ShortCut);
        }
        else if (numButtons == 3)
        {
            aw->addButton(button1, 1, button1ShortCut);
            aw->addButton(button2, 2, button2ShortCut);
            aw->addButton(button3, 0, juce::KeyPress(juce::KeyPress::escapeKey));
        }
    }

    return aw;
}

void UiLookAndFeel::drawAlertBox(juce::Graphics &g, juce::AlertWindow &alert,
                                 const juce::Rectangle<int> &textArea, juce::TextLayout &textLayout)
{
    g.fillAll(alert.findColour(juce::AlertWindow::backgroundColourId));

    int iconSpaceUsed = 0;

    const int iconWidth = 50;
    int iconSize = juce::jmin(iconWidth + 50, alert.getHeight() + 20);

    if (alert.containsAnyExtraComponents() || alert.getNumButtons() > 2)
        iconSize = juce::jmin(iconSize, textArea.getHeight() + 50);

    const juce::Rectangle<int> iconRect(iconSize / -10, iconSize / -10, iconSize, iconSize);

    if (alert.getAlertType() != juce::AlertWindow::NoIcon)
    {
        juce::Path icon;
        std::uint32_t colour;
        char character;

        if (alert.getAlertType() == juce::AlertWindow::WarningIcon)
        {
            colour = 0x55ff5555;
            character = '!';

            icon.addTriangle(iconRect.getX() + iconRect.getWidth() * 0.5f, (float)iconRect.getY(),
                             (float)iconRect.getRight(), (float)iconRect.getBottom(),
                             (float)iconRect.getX(), (float)iconRect.getBottom());

            icon = icon.createPathWithRoundedCorners(5.0f);
        }
        else
        {
            colour = alert.getAlertType() == juce::AlertWindow::InfoIcon
                         ? (std::uint32_t)0x605555ff
                         : (std::uint32_t)0x40b69900;
            character = alert.getAlertType() == juce::AlertWindow::InfoIcon ? 'i' : '?';

            icon.addEllipse((float)iconRect.getX(), (float)iconRect.getY(),
                            (float)iconRect.getWidth(), (float)iconRect.getHeight());
        }

        juce::GlyphArrangement ga;
        ga.addFittedText(juce::Font(iconRect.getHeight() * 0.9f, juce::Font::bold),
                         juce::String::charToString((juce::juce_wchar)(std::uint8_t)character),
                         (float)iconRect.getX(), (float)iconRect.getY(), (float)iconRect.getWidth(),
                         (float)iconRect.getHeight(), juce::Justification::centred, false);
        ga.createPath(icon);

        icon.setUsingNonZeroWinding(false);
        g.setColour(juce::Colour(colour));
        g.fillPath(icon);

        iconSpaceUsed = iconWidth;
    }

    g.setColour(alert.findColour(juce::AlertWindow::textColourId));

    textLayout.draw(g,
                    juce::Rectangle<int>(textArea.getX() + iconSpaceUsed, textArea.getY(),
                                         textArea.getWidth() - iconSpaceUsed, textArea.getHeight())
                        .toFloat());

    g.setColour(alert.findColour(juce::AlertWindow::outlineColourId));
    g.drawRect(0, 0, alert.getWidth(), alert.getHeight(), 2);
}

int UiLookAndFeel::getAlertBoxWindowFlags()
{
    return juce::ComponentPeer::windowAppearsOnTaskbar | juce::ComponentPeer::windowHasDropShadow;
}

int UiLookAndFeel::getAlertWindowButtonHeight()
{
    return int(
        1.f / 900 *
        juce::Desktop::getInstance().getDisplays().getPrimaryDisplay()->userArea.getHeight() * 30);
}

juce::Font UiLookAndFeel::getAlertWindowMessageFont()
{
    return defaultFont.withHeight(
        1.f / 900 *
        juce::Desktop::getInstance().getDisplays().getPrimaryDisplay()->userArea.getHeight() * 20);
}

juce::Font UiLookAndFeel::getAlertWindowFont()
{
    return defaultFont.withHeight((
        1.f / 900 *
        juce::Desktop::getInstance().getDisplays().getPrimaryDisplay()->userArea.getHeight() * 17));
}

//==============================================================================
void UiLookAndFeel::drawProgressBar(juce::Graphics &g, juce::ProgressBar &progressBar, int width,
                                    int height, double progress, const juce::String &textToShow)
{
    const juce::Colour background(progressBar.findColour(juce::ProgressBar::backgroundColourId));
    const juce::Colour foreground(progressBar.findColour(juce::ProgressBar::foregroundColourId));

    g.fillAll(background);

    if (progress >= 0.0f && progress < 1.0f)
    {
        drawGlassLozenge(g, 1.0f, 1.0f,
                         (float)juce::jlimit(0.0, width - 2.0, progress * (width - 2.0)),
                         (float)(height - 2), foreground, 0.5f, 0.0f, true, true, true, true);
    }
    else
    {
        // spinning bar..
        g.setColour(foreground);

        const int stripeWidth = height * 2;
        const int position = (int)(juce::Time::getMillisecondCounter() / 15) % stripeWidth;

        juce::Path p;

        for (float x = (float)(-position); x < width + stripeWidth; x += stripeWidth)
            p.addQuadrilateral(x, 0.0f, x + stripeWidth * 0.5f, 0.0f, x, (float)height,
                               x - stripeWidth * 0.5f, (float)height);

        juce::Image im(juce::Image::ARGB, width, height, true);

        {
            juce::Graphics g2(im);
            drawGlassLozenge(g2, 1.0f, 1.0f, (float)(width - 2), (float)(height - 2), foreground,
                             0.5f, 0.0f, true, true, true, true);
        }

        g.setTiledImageFill(im, 0, 0, 0.85f);
        g.fillPath(p);
    }

    if (textToShow.isNotEmpty())
    {
        g.setColour(juce::Colour::contrasting(background, foreground));
        g.setFont(height * 0.6f);

        g.drawText(textToShow, 0, 0, width, height, juce::Justification::centred, false);
    }
}

void UiLookAndFeel::drawSpinningWaitAnimation(juce::Graphics &g, const juce::Colour &colour, int x,
                                              int y, int w, int h)
{
    const float radius = juce::jmin(w, h) * 0.4f;
    const float thickness = radius * 0.15f;
    juce::Path p;
    p.addRoundedRectangle(radius * 0.4f, thickness * -0.5f, radius * 0.6f, thickness,
                          thickness * 0.5f);

    const float cx = x + w * 0.5f;
    const float cy = y + h * 0.5f;

    const std::uint32_t animationIndex = (juce::Time::getMillisecondCounter() / (1000 / 10)) % 12;

    for (std::uint32_t i = 0; i < 12; ++i)
    {
        const std::uint32_t n = (i + 12 - animationIndex) % 12;
        g.setColour(colour.withMultipliedAlpha((n + 1) / 12.0f));

        g.fillPath(p, juce::AffineTransform::rotation(i * (juce::MathConstants<float>::pi / 6.0f))
                          .translated(cx, cy));
    }
}

bool UiLookAndFeel::areScrollbarButtonsVisible() { return true; }

void UiLookAndFeel::drawScrollbarButton(juce::Graphics &g, juce::ScrollBar &scrollbar, int width,
                                        int height, int buttonDirection,
                                        bool /*isScrollbarVertical*/, bool /*isMouseOverButton*/,
                                        bool isButtonDown)
{
    juce::Path p;

    if (buttonDirection == 0)
        p.addTriangle(width * 0.5f, height * 0.2f, width * 0.1f, height * 0.7f, width * 0.9f,
                      height * 0.7f);
    else if (buttonDirection == 1)
        p.addTriangle(width * 0.8f, height * 0.5f, width * 0.3f, height * 0.1f, width * 0.3f,
                      height * 0.9f);
    else if (buttonDirection == 2)
        p.addTriangle(width * 0.5f, height * 0.8f, width * 0.1f, height * 0.3f, width * 0.9f,
                      height * 0.3f);
    else if (buttonDirection == 3)
        p.addTriangle(width * 0.2f, height * 0.5f, width * 0.7f, height * 0.1f, width * 0.7f,
                      height * 0.9f);

    if (isButtonDown)
        g.setColour(juce::Colour(0xff161616).contrasting(0.2f));
    else
        g.setColour(juce::Colour(0xff161616));

    g.fillPath(p);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    g.strokePath(p, juce::PathStrokeType(0.5f));
}

void UiLookAndFeel::drawScrollbar(juce::Graphics &g, juce::ScrollBar &scrollbar, int x, int y,
                                  int width, int height, bool isScrollbarVertical,
                                  int thumbStartPosition, int thumbSize, bool /*isMouseOver*/,
                                  bool /*isMouseDown*/)
{
    g.fillAll(scrollbar.findColour(juce::ScrollBar::backgroundColourId));

    juce::Path slotPath, slotPathInner, thumbPath;

    const float slotIndent = juce::jmin(width, height) > 15 ? 1.0f : 0.0f;
    const float slotIndentx2 = slotIndent * 2.0f;
    const float thumbIndent = slotIndent + 1.0f;
    const float thumbIndentx2 = thumbIndent * 2.0f;
    /*
        float gx1 = 0.0f, gy1 = 0.0f, gx2 = 0.0f, gy2 = 0.0f;
    */
    if (isScrollbarVertical)
    {
        slotPath.addRoundedRectangle(x + slotIndent, y + slotIndent, width - slotIndentx2,
                                     height - slotIndentx2, (width - slotIndentx2) * 0.2f);

        slotPathInner.addRoundedRectangle(x + slotIndent + 1, y + slotIndent + 1,
                                          width - slotIndentx2 - 2, height - slotIndentx2 - 2,
                                          (width - slotIndentx2 - 2) * 0.2f);

        if (thumbSize > 0)
            thumbPath.addRoundedRectangle(x + thumbIndent, thumbStartPosition + thumbIndent,
                                          width - thumbIndentx2, thumbSize - thumbIndentx2,
                                          (width - thumbIndentx2) * 0.2f);
        /*
        gx1 = (float) x;
        gx2 = x + width * 0.7f;
        */
    }
    else
    {
        slotPathInner.addRoundedRectangle(x + slotIndent + 1, y + slotIndent + 1,
                                          width - slotIndentx2 - 2, height - slotIndentx2 - 2,
                                          (height - slotIndentx2 - 2) * 0.2f);
        slotPath.addRoundedRectangle(x + slotIndent, y + slotIndent, width - slotIndentx2,
                                     height - slotIndentx2, (height - slotIndentx2) * 0.2f);

        if (thumbSize > 0)
            thumbPath.addRoundedRectangle(thumbStartPosition + thumbIndent, y + thumbIndent,
                                          thumbSize - thumbIndentx2, height - thumbIndentx2,
                                          (height - thumbIndentx2) * 0.2f);
        /*
        gy1 = (float) y;
        gy2 = y + height * 0.7f;
        */
    }
    /*
        g.setColour (Colour (GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
        g.fillRect (gx1, gy1, gx2, gy2);

        g.setColour (Colour (GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
        g.drawRect (0, 0, getWidth() - 0, getHeight() - 0, 2);

        g.setGradientFill (ColourGradient (trackColour1, gx1, gy1,
                                           trackColour2, gx2, gy2, false));
        g.fillPath (slotPath);

        if (isScrollbarVertical)
        {
            gx1 = x + width * 0.6f;
            gx2 = (float) x + width;
        }
        else
        {
            gy1 = y + height * 0.6f;
            gy2 = (float) y + height;
        }
    */
    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    g.fillPath(slotPath);
    g.setColour(juce::Colour(0xff161616));
    g.fillPath(slotPathInner);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    g.fillPath(thumbPath);

    g.saveState();

    if (isScrollbarVertical)
        g.reduceClipRegion(x + width / 2, y, width, height);
    else
        g.reduceClipRegion(x, y + height / 2, width, height);

    g.fillPath(thumbPath);
    g.restoreState();
    /*
        g.setColour (Colour (0x4c000000));
        g.strokePath (thumbPath, PathStrokeType (0.4f));
        */
}

juce::ImageEffectFilter *UiLookAndFeel::getScrollbarEffect() { return nullptr; }

int UiLookAndFeel::getMinimumScrollbarThumbSize(juce::ScrollBar &scrollbar)
{
    return juce::jmin(scrollbar.getWidth(), scrollbar.getHeight()) * 2;
}

int UiLookAndFeel::getDefaultScrollbarWidth() { return 18; }

int UiLookAndFeel::getScrollbarButtonSize(juce::ScrollBar &scrollbar)
{
    return 2 + (scrollbar.isVertical() ? scrollbar.getWidth() : scrollbar.getHeight());
}

//==============================================================================
juce::Path UiLookAndFeel::getTickShape(const float height)
{
    static const unsigned char tickShapeData[] = {
        109, 0,   224, 168, 68,  0,   0,  119, 67,  108, 0,   224, 172, 68,  0,   128, 146,
        67,  113, 0,   192, 148, 68,  0,  0,   219, 67,  0,   96,  110, 68,  0,   224, 56,
        68,  113, 0,   64,  51,  68,  0,  32,  130, 68,  0,   64,  20,  68,  0,   224, 162,
        68,  108, 0,   128, 3,   68,  0,  128, 168, 68,  113, 0,   128, 221, 67,  0,   192,
        175, 68,  0,   0,   207, 67,  0,  32,  179, 68,  113, 0,   0,   201, 67,  0,   224,
        173, 68,  0,   0,   181, 67,  0,  224, 161, 68,  108, 0,   128, 168, 67,  0,   128,
        154, 68,  113, 0,   128, 141, 67, 0,   192, 138, 68,  0,   128, 108, 67,  0,   64,
        131, 68,  113, 0,   0,   62,  67, 0,   128, 119, 68,  0,   0,   5,   67,  0,   128,
        114, 68,  113, 0,   0,   102, 67, 0,   192, 88,  68,  0,   128, 155, 67,  0,   192,
        88,  68,  113, 0,   0,   190, 67, 0,   192, 88,  68,  0,   128, 232, 67,  0,   224,
        131, 68,  108, 0,   128, 246, 67, 0,   192, 139, 68,  113, 0,   64,  33,  68,  0,
        128, 87,  68,  0,   0,   93,  68, 0,   224, 26,  68,  113, 0,   96,  140, 68,  0,
        128, 188, 67,  0,   224, 168, 68, 0,   0,   119, 67,  99,  101};

    juce::Path p;
    p.loadPathFromData(tickShapeData, sizeof(tickShapeData));
    p.scaleToFit(0, 0, height * 2.0f, height, true);
    return p;
}

juce::Path UiLookAndFeel::getCrossShape(const float height)
{
    static const unsigned char crossShapeData[] = {
        109, 0,   0,   17,  68,  0,   96,  145, 68,  108, 0,   192, 13,  68,  0,   192, 147, 68,
        113, 0,   0,   213, 67,  0,   64,  174, 68,  0,   0,   168, 67,  0,   64,  174, 68,  113,
        0,   0,   104, 67,  0,   64,  174, 68,  0,   0,   5,   67,  0,   64,  153, 68,  113, 0,
        0,   18,  67,  0,   64,  153, 68,  0,   0,   24,  67,  0,   64,  153, 68,  113, 0,   0,
        135, 67,  0,   64,  153, 68,  0,   128, 207, 67,  0,   224, 130, 68,  108, 0,   0,   220,
        67,  0,   0,   126, 68,  108, 0,   0,   204, 67,  0,   128, 117, 68,  113, 0,   0,   138,
        67,  0,   64,  82,  68,  0,   0,   138, 67,  0,   192, 57,  68,  113, 0,   0,   138, 67,
        0,   192, 37,  68,  0,   128, 210, 67,  0,   64,  10,  68,  113, 0,   128, 220, 67,  0,
        64,  45,  68,  0,   0,   8,   68,  0,   128, 78,  68,  108, 0,   192, 14,  68,  0,   0,
        87,  68,  108, 0,   64,  20,  68,  0,   0,   80,  68,  113, 0,   192, 57,  68,  0,   0,
        32,  68,  0,   128, 88,  68,  0,   0,   32,  68,  113, 0,   64,  112, 68,  0,   0,   32,
        68,  0,   128, 124, 68,  0,   64,  68,  68,  113, 0,   0,   121, 68,  0,   192, 67,  68,
        0,   128, 119, 68,  0,   192, 67,  68,  113, 0,   192, 108, 68,  0,   192, 67,  68,  0,
        32,  89,  68,  0,   96,  82,  68,  113, 0,   128, 69,  68,  0,   0,   97,  68,  0,   0,
        56,  68,  0,   64,  115, 68,  108, 0,   64,  49,  68,  0,   128, 124, 68,  108, 0,   192,
        55,  68,  0,   96,  129, 68,  113, 0,   0,   92,  68,  0,   224, 146, 68,  0,   192, 129,
        68,  0,   224, 146, 68,  113, 0,   64,  110, 68,  0,   64,  168, 68,  0,   64,  87,  68,
        0,   64,  168, 68,  113, 0,   128, 66,  68,  0,   64,  168, 68,  0,   64,  27,  68,  0,
        32,  150, 68,  99,  101};

    juce::Path p;
    p.loadPathFromData(crossShapeData, sizeof(crossShapeData));
    p.scaleToFit(0, 0, height * 2.0f, height, true);
    return p;
}

//==============================================================================
void UiLookAndFeel::drawTreeviewPlusMinusBox(juce::Graphics &g, const juce::Rectangle<float> &area,
                                             juce::Colour /*backgroundColour*/, bool isOpen,
                                             bool /*isMouseOver*/)
{
    const int boxSize =
        juce::roundToInt(juce::jmin(16.0f, area.getWidth(), area.getHeight()) * 0.7f) | 1;

    const int x = ((int)area.getWidth() - boxSize) / 2 + (int)area.getX();
    const int y = ((int)area.getHeight() - boxSize) / 2 + (int)area.getY();
    const int w = boxSize;
    const int h = boxSize;

    g.setColour(juce::Colour(0xe5ffffff));
    g.fillRect(x, y, w, h);

    g.setColour(juce::Colour(0x80000000));
    g.drawRect(x, y, w, h);

    const float size = boxSize / 2.0 + 1.0f;
    const float centre = (float)(boxSize / 2.0);

    g.fillRect(x + (w - size) * 0.5f, y + centre, size, 1.0f);

    if (!isOpen)
        g.fillRect(x + centre, y + (h - size) * 0.5f, 1.0f, size);
}

bool UiLookAndFeel::areLinesDrawnForTreeView(juce::TreeView &) { return true; }

int UiLookAndFeel::getTreeViewIndentSize(juce::TreeView &) { return 24; }

//==============================================================================
void UiLookAndFeel::drawBubble(juce::Graphics &g, juce::BubbleComponent &comp,
                               const juce::Point<float> &tip, const juce::Rectangle<float> &body)
{
    juce::Path p;
    p.addBubble(body.reduced(0.5f), body.getUnion(juce::Rectangle<float>(tip.x, tip.y, 1.0f, 1.0f)),
                tip, 5.0f, juce::jmin(15.0f, body.getWidth() * 0.2f, body.getHeight() * 0.2f));

    g.setColour(comp.findColour(juce::BubbleComponent::backgroundColourId));
    g.fillPath(p);

    g.setColour(comp.findColour(juce::BubbleComponent::outlineColourId));
    g.strokePath(p, juce::PathStrokeType(1.0f));
}

//==============================================================================
juce::Font UiLookAndFeel::getPopupMenuFont() { return juce::Font(17.0f); }

void UiLookAndFeel::getIdealPopupMenuItemSize(const juce::String &text, const bool isSeparator,
                                              int standardMenuItemHeight, int &idealWidth,
                                              int &idealHeight)
{
    if (isSeparator)
    {
        idealWidth = 50;
        idealHeight = standardMenuItemHeight > 0 ? standardMenuItemHeight / 2 : 10;
    }
    else
    {
        juce::Font font(getPopupMenuFont());

        if (standardMenuItemHeight > 0 && font.getHeight() > standardMenuItemHeight / 1.3f)
            font.setHeight(standardMenuItemHeight / 1.3f);

        idealHeight = standardMenuItemHeight > 0 ? standardMenuItemHeight
                                                 : juce::roundToInt(font.getHeight() * 1.3f);
        idealWidth = font.getStringWidth(text) + idealHeight * 2;
    }
}

void UiLookAndFeel::drawPopupMenuBackground(juce::Graphics &g, int width, int height)
{
    const juce::Colour background(findColour(juce::PopupMenu::backgroundColourId));

    g.fillAll(background);
    g.setColour(background.overlaidWith(juce::Colour(0x2badd8e6)));

    for (int i = 0; i < height; i += 3)
        g.fillRect(0, i, width, 1);

#if !JUCE_MAC
    g.setColour(findColour(juce::PopupMenu::textColourId).withAlpha(0.6f));
    g.drawRect(0, 0, width, height);
#endif
}

void UiLookAndFeel::drawPopupMenuUpDownArrow(juce::Graphics &g, int width, int height,
                                             bool isScrollUpArrow)
{
    const juce::Colour background(findColour(juce::PopupMenu::backgroundColourId));

    g.setGradientFill(juce::ColourGradient(background, 0.0f, height * 0.5f,
                                           background.withAlpha(0.0f), 0.0f,
                                           isScrollUpArrow ? ((float)height) : 0.0f, false));

    g.fillRect(1, 1, width - 2, height - 2);

    const float hw = width * 0.5f;
    const float arrowW = height * 0.3f;
    const float y1 = height * (isScrollUpArrow ? 0.6f : 0.3f);
    const float y2 = height * (isScrollUpArrow ? 0.3f : 0.6f);

    juce::Path p;
    p.addTriangle(hw - arrowW, y1, hw + arrowW, y1, hw, y2);

    g.setColour(findColour(juce::PopupMenu::textColourId).withAlpha(0.5f));
    g.fillPath(p);
}

void UiLookAndFeel::drawPopupMenuItem(juce::Graphics &g, const juce::Rectangle<int> &area,
                                      const bool isSeparator, const bool isActive,
                                      const bool isHighlighted, const bool isTicked,
                                      const bool hasSubMenu, const juce::String &text,
                                      const juce::String &shortcutKeyText,
                                      const juce::Drawable *icon,
                                      const juce::Colour *const textColourToUse)
{
    if (isSeparator)
    {
        juce::Rectangle<int> r(area.reduced(5, 0));
        r.removeFromTop(r.getHeight() / 2 - 1);

        g.setColour(juce::Colour(0x33000000));
        g.fillRect(r.removeFromTop(1));

        g.setColour(juce::Colour(0x66ffffff));
        g.fillRect(r.removeFromTop(1));
    }
    else
    {
        juce::Colour textColour(findColour(juce::PopupMenu::textColourId));

        if (textColourToUse != nullptr)
            textColour = *textColourToUse;

        juce::Rectangle<int> r(area.reduced(1));

        if (isHighlighted)
        {
            g.setColour(findColour(juce::PopupMenu::highlightedBackgroundColourId));
            g.fillRect(r);

            g.setColour(findColour(juce::PopupMenu::highlightedTextColourId));
        }
        else
        {
            g.setColour(textColour);
        }

        if (!isActive)
            g.setOpacity(0.3f);

        juce::Font font(getPopupMenuFont());

        const float maxFontHeight = area.getHeight() / 1.3f;

        if (font.getHeight() > maxFontHeight)
            font.setHeight(maxFontHeight);

        g.setFont(font);

        juce::Rectangle<float> iconArea(
            r.removeFromLeft((r.getHeight() * 5) / 4).reduced(3).toFloat());

        if (icon != nullptr)
        {
            icon->drawWithin(g, iconArea,
                             juce::RectanglePlacement::centred |
                                 juce::RectanglePlacement::onlyReduceInSize,
                             1.0f);
        }
        else if (isTicked)
        {
            const juce::Path tick(getTickShape(1.0f));
            g.fillPath(tick, tick.getTransformToScaleToFit(iconArea, true));
        }

        if (hasSubMenu)
        {
            const float arrowH = 0.6f * getPopupMenuFont().getAscent();

            const float x = (float)r.removeFromRight((int)arrowH).getX();
            const float halfH = (float)r.getCentreY();

            juce::Path p;
            p.addTriangle(x, halfH - arrowH * 0.5f, x, halfH + arrowH * 0.5f, x + arrowH * 0.6f,
                          halfH);

            g.fillPath(p);
        }

        r.removeFromRight(3);
        g.drawFittedText(text, r, juce::Justification::centredLeft, 1);

        if (shortcutKeyText.isNotEmpty())
        {
            juce::Font f2(font);
            f2.setHeight(f2.getHeight() * 0.75f);
            f2.setHorizontalScale(0.95f);
            g.setFont(f2);

            g.drawText(shortcutKeyText, r, juce::Justification::centredRight, true);
        }
    }
}

//==============================================================================
int UiLookAndFeel::getMenuWindowFlags() { return juce::ComponentPeer::windowHasDropShadow; }

void UiLookAndFeel::drawMenuBarBackground(juce::Graphics &g, int width, int height, bool,
                                          juce::MenuBarComponent &menuBar)
{
    const juce::Colour baseColour(LookAndFeelHelpers::createBaseColour(
        menuBar.findColour(juce::PopupMenu::backgroundColourId), false, false, false));

    if (menuBar.isEnabled())
        drawShinyButtonShape(g, -4.0f, 0.0f, width + 8.0f, (float)height, 0.0f, baseColour, 0.4f,
                             true, true, true, true);
    else
        g.fillAll(baseColour);
}

juce::Font UiLookAndFeel::getMenuBarFont(juce::MenuBarComponent &menuBar, int /*itemIndex*/,
                                         const juce::String & /*itemText*/)
{
    return juce::Font(menuBar.getHeight() * 0.7f);
}

int UiLookAndFeel::getMenuBarItemWidth(juce::MenuBarComponent &menuBar, int itemIndex,
                                       const juce::String &itemText)
{
    return getMenuBarFont(menuBar, itemIndex, itemText).getStringWidth(itemText) +
           menuBar.getHeight();
}

void UiLookAndFeel::drawMenuBarItem(juce::Graphics &g, int width, int height, int itemIndex,
                                    const juce::String &itemText, bool isMouseOverItem,
                                    bool isMenuOpen, bool /*isMouseOverBar*/,
                                    juce::MenuBarComponent &menuBar)
{
    if (!menuBar.isEnabled())
    {
        g.setColour(menuBar.findColour(juce::PopupMenu::textColourId).withMultipliedAlpha(0.5f));
    }
    else if (isMenuOpen || isMouseOverItem)
    {
        g.fillAll(menuBar.findColour(juce::PopupMenu::highlightedBackgroundColourId));
        g.setColour(menuBar.findColour(juce::PopupMenu::highlightedTextColourId));
    }
    else
    {
        g.setColour(menuBar.findColour(juce::PopupMenu::textColourId));
    }

    g.setFont(getMenuBarFont(menuBar, itemIndex, itemText));
    g.drawFittedText(itemText, 0, 0, width, height, juce::Justification::centred, 1);
}

//==============================================================================
void UiLookAndFeel::fillTextEditorBackground(juce::Graphics &g, int /*width*/, int /*height*/,
                                             juce::TextEditor &textEditor)
{
    g.fillAll(textEditor.findColour(juce::TextEditor::backgroundColourId));
}

void UiLookAndFeel::drawTextEditorOutline(juce::Graphics &g, int width, int height,
                                          juce::TextEditor &textEditor)
{
    if (textEditor.isEnabled())
    {
        if (textEditor.hasKeyboardFocus(true) && !textEditor.isReadOnly())
        {
            const int border = 2;

            g.setColour(textEditor.findColour(juce::TextEditor::focusedOutlineColourId));
            g.drawRect(0, 0, width, height, border);

            g.setOpacity(1.0f);
            const juce::Colour shadowColour(
                textEditor.findColour(juce::TextEditor::shadowColourId).withMultipliedAlpha(0.75f));
            drawBevel(g, 0, 0, width, height + 2, border + 2, shadowColour, shadowColour);
        }
        else
        {
            g.setColour(textEditor.findColour(juce::TextEditor::outlineColourId));
            g.drawRect(0, 0, width, height);

            g.setOpacity(1.0f);
            const juce::Colour shadowColour(
                textEditor.findColour(juce::TextEditor::shadowColourId));
            drawBevel(g, 0, 0, width, height + 2, 3, shadowColour, shadowColour);
        }
    }
}

juce::CaretComponent *UiLookAndFeel::createCaretComponent(juce::Component *keyFocusOwner)
{
    return new juce::CaretComponent(keyFocusOwner);
}

//==============================================================================
void UiLookAndFeel::drawComboBox(juce::Graphics &g, int width, int height, const bool isButtonDown,
                                 int buttonX, int buttonY, int buttonW, int buttonH,
                                 juce::ComboBox &box)
{
    g.fillAll(juce::Colours::black);

    if (box.isEnabled() && box.hasKeyboardFocus(false))
    {
        g.setColour(box.findColour(juce::ComboBox::buttonColourId));
        g.drawRect(0, 0, width, height, 2);
    }
    else
    {
        g.setColour(
            box.isEnabled()
                ? juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR)
                : juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR).darker());
        g.drawRect(0, 0, width, height);
    }

    const float outlineThickness = 1; // box.isEnabled() ? (isButtonDown ? 1.2f : 0.8f) : 0.3f;

    drawGlassLozenge(
        g, buttonX + outlineThickness, buttonY + outlineThickness,
        buttonW - outlineThickness * 2.0f, buttonH - outlineThickness * 2.0f,
        box.isEnabled() ? juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR)
                        : juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR).darker(),
        outlineThickness, -1.0f, true, true, true, true);

    if (box.isEnabled())
    {
        const float arrowX = 0.3f;
        const float arrowH = 0.2f;

        juce::Path p;
        p.addTriangle(buttonX + buttonW * 0.5f, buttonY + buttonH * (0.45f - arrowH),
                      buttonX + buttonW * (1.0f - arrowX), buttonY + buttonH * 0.45f,
                      buttonX + buttonW * arrowX, buttonY + buttonH * 0.45f);

        p.addTriangle(buttonX + buttonW * 0.5f, buttonY + buttonH * (0.55f + arrowH),
                      buttonX + buttonW * (1.0f - arrowX), buttonY + buttonH * 0.55f,
                      buttonX + buttonW * arrowX, buttonY + buttonH * 0.55f);

        g.setColour(juce::Colours::black);
        g.fillPath(p);
    }
}

juce::Font UiLookAndFeel::getComboBoxFont(juce::ComboBox &box)
{
    return defaultFont.withHeight(juce::jmin(15.0f, box.getHeight() * 0.85f));
}

juce::Label *UiLookAndFeel::createComboBoxTextBox(juce::ComboBox &)
{
    return new juce::Label(juce::String(), juce::String());
}

void UiLookAndFeel::positionComboBoxText(juce::ComboBox &box, juce::Label &label)
{
    label.setBounds(1, 1, box.getWidth() + 3 - box.getHeight(), box.getHeight() - 2);

    label.setFont(getComboBoxFont(box));
}

//==============================================================================
juce::Font UiLookAndFeel::getLabelFont(juce::Label &label) { return defaultFont; }

void UiLookAndFeel::drawLabel(juce::Graphics &g, juce::Label &label)
{
    g.fillAll(label.findColour(juce::Label::backgroundColourId));

    if (!label.isBeingEdited())
    {
        const float alpha = label.isEnabled() ? 1.0f : 0.5f;
        const juce::Font font(getLabelFont(label));

        juce::Colour col = label.findColour(juce::Label::textColourId).withMultipliedAlpha(alpha);

        if (!label.isEnabled())
            col = col.darker();

        g.setColour(col);
        g.setFont(font.withHeight(0.6 * label.getHeight()));

        juce::Rectangle<int> textArea(label.getBorderSize().subtractedFrom(label.getLocalBounds()));
        g.drawFittedText(label.getText(), textArea, label.getJustificationType(),
                         juce::jmax(1, (int)(label.getHeight() / font.getHeight())), 0.5);

        g.setColour(label.findColour(juce::Label::outlineColourId).withMultipliedAlpha(alpha));
    }
    else if (label.isEnabled())
    {
        g.setColour(label.findColour(juce::Label::outlineColourId));
    }

    g.drawRect(label.getLocalBounds());
}

//==============================================================================
void UiLookAndFeel::drawLinearSliderBackground(juce::Graphics &g, int x, int y, int width,
                                               int height, float /*sliderPos*/,
                                               float /*minSliderPos*/, float /*maxSliderPos*/,
                                               const juce::Slider::SliderStyle /*style*/,
                                               juce::Slider &slider)
{
    const float sliderRadius = (float)(getSliderThumbRadius(slider) - 2);

    const juce::Colour trackColour(slider.findColour(juce::Slider::trackColourId));
    const juce::Colour gradCol1(trackColour.overlaidWith(
        juce::Colours::black.withAlpha(slider.isEnabled() ? 0.25f : 0.13f)));
    const juce::Colour gradCol2(trackColour.overlaidWith(juce::Colour(0x14000000)));
    juce::Path indent;

    if (slider.isHorizontal())
    {
        const float iy = y + height * 0.5f - sliderRadius * 0.5f;
        const float ih = sliderRadius;

        g.setGradientFill(juce::ColourGradient(gradCol1, 0.0f, iy, gradCol2, 0.0f, iy + ih, false));

        indent.addRoundedRectangle(x - sliderRadius * 0.5f, iy, width + sliderRadius, ih, 5.0f);
    }
    else
    {
        const float ix = x + width * 0.5f - sliderRadius * 0.5f;
        const float iw = sliderRadius;

        g.setGradientFill(juce::ColourGradient(gradCol1, ix, 0.0f, gradCol2, ix + iw, 0.0f, false));

        indent.addRoundedRectangle(ix, y - sliderRadius * 0.5f, iw, height + sliderRadius, 5.0f);
    }

    g.fillPath(indent);

    g.setColour(juce::Colour(0x4c000000));
    g.strokePath(indent, juce::PathStrokeType(0.5f));
}

void UiLookAndFeel::drawLinearSliderThumb(juce::Graphics &g, int x, int y, int width, int height,
                                          float sliderPos, float minSliderPos, float maxSliderPos,
                                          const juce::Slider::SliderStyle style,
                                          juce::Slider &slider)
{
    const float sliderRadius = (float)(getSliderThumbRadius(slider) - 2);

    juce::Colour knobColour(
        LookAndFeelHelpers::createBaseColour(slider.findColour(juce::Slider::thumbColourId),
                                             slider.hasKeyboardFocus(false) && slider.isEnabled(),
                                             slider.isMouseOverOrDragging() && slider.isEnabled(),
                                             slider.isMouseButtonDown() && slider.isEnabled()));

    const float outlineThickness = slider.isEnabled() ? 0.8f : 0.3f;

    if (style == juce::Slider::LinearHorizontal || style == juce::Slider::LinearVertical)
    {
        float kx, ky;

        if (style == juce::Slider::LinearVertical)
        {
            kx = x + width * 0.5f;
            ky = sliderPos;
        }
        else
        {
            kx = sliderPos;
            ky = y + height * 0.5f;
        }

        drawGlassSphere(g, kx - sliderRadius, ky - sliderRadius, sliderRadius * 2.0f, knobColour,
                        outlineThickness);
    }
    else
    {
        if (style == juce::Slider::ThreeValueVertical)
        {
            drawGlassSphere(g, x + width * 0.5f - sliderRadius, sliderPos - sliderRadius,
                            sliderRadius * 2.0f, knobColour, outlineThickness);
        }
        else if (style == juce::Slider::ThreeValueHorizontal)
        {
            drawGlassSphere(g, sliderPos - sliderRadius, y + height * 0.5f - sliderRadius,
                            sliderRadius * 2.0f, knobColour, outlineThickness);
        }

        if (style == juce::Slider::TwoValueVertical || style == juce::Slider::ThreeValueVertical)
        {
            const float sr = juce::jmin(sliderRadius, width * 0.4f);

            drawGlassPointer(g, juce::jmax(0.0f, x + width * 0.5f - sliderRadius * 2.0f),
                             minSliderPos - sliderRadius, sliderRadius * 2.0f, knobColour,
                             outlineThickness, 1);

            drawGlassPointer(g, juce::jmin(x + width - sliderRadius * 2.0f, x + width * 0.5f),
                             maxSliderPos - sr, sliderRadius * 2.0f, knobColour, outlineThickness,
                             3);
        }
        else if (style == juce::Slider::TwoValueHorizontal ||
                 style == juce::Slider::ThreeValueHorizontal)
        {
            const float sr = juce::jmin(sliderRadius, height * 0.4f);

            drawGlassPointer(g, minSliderPos - sr,
                             juce::jmax(0.0f, y + height * 0.5f - sliderRadius * 2.0f),
                             sliderRadius * 2.0f, knobColour, outlineThickness, 2);

            drawGlassPointer(g, maxSliderPos - sliderRadius,
                             juce::jmin(y + height - sliderRadius * 2.0f, y + height * 0.5f),
                             sliderRadius * 2.0f, knobColour, outlineThickness, 4);
        }
    }
}

void UiLookAndFeel::drawLinearSlider(juce::Graphics &g, int x, int y, int width, int height,
                                     float sliderPos, float minSliderPos, float maxSliderPos,
                                     const juce::Slider::SliderStyle style, juce::Slider &slider)
{
    g.fillAll(slider.findColour(juce::Slider::backgroundColourId));

    if (style == juce::Slider::LinearBar || style == juce::Slider::LinearBarVertical)
    {
        const bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();

        juce::Colour baseColour(LookAndFeelHelpers::createBaseColour(
            slider.findColour(juce::Slider::thumbColourId)
                .withMultipliedSaturation(slider.isEnabled() ? 1.0f : 0.5f),
            false, isMouseOver, isMouseOver || slider.isMouseButtonDown()));

        drawShinyButtonShape(
            g, (float)x, style == juce::Slider::LinearBarVertical ? sliderPos : (float)y,
            style == juce::Slider::LinearBarVertical ? (float)width : (sliderPos - x),
            style == juce::Slider::LinearBarVertical ? (height - sliderPos) : (float)height, 0.0f,
            baseColour, slider.isEnabled() ? 0.9f : 0.3f, true, true, true, true);
    }
    else
    {
        drawLinearSliderBackground(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos,
                                   style, slider);
        drawLinearSliderThumb(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style,
                              slider);
    }
}

int UiLookAndFeel::getSliderThumbRadius(juce::Slider &slider)
{
    return juce::jmin(7, slider.getHeight() / 2, slider.getWidth() / 2) + 2;
}

void UiLookAndFeel::drawRotarySlider(juce::Graphics &g, int x, int y, int width, int height,
                                     float sliderPos, const float rotaryStartAngle,
                                     const float rotaryEndAngle, juce::Slider &slider)
{
    const float radius = juce::jmin(width / 2, height / 2) - 2.0f;
    const float centreX = x + width * 0.5f;
    const float centreY = y + height * 0.5f;
    const float rx = centreX - radius;
    const float ry = centreY - radius;
    const float rw = radius * 2.0f;
    const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    juce::Colour SliderCol(
        slider.findColour(juce::Slider::rotarySliderFillColourId).withAlpha(1.0f));
    if (slider.isEnabled())
        g.setColour(SliderCol);
    else
        g.setColour(juce::Colour(0x80808080));

    const float thickness = 0.65; //* (1.f/40*slider.getWidth()); /* 0.7f; */

    {
        juce::Path filledArc;
        filledArc.addPieSegment(rx, ry, rw, rw, rotaryStartAngle, angle, thickness);
        g.fillPath(filledArc);

        g.setColour(juce::Colour(0xff000000));
        const float innerRadius = radius * thickness;
        juce::Path realKnob;
        realKnob.addEllipse(-innerRadius, -innerRadius, innerRadius * 2.0f, innerRadius * 2.0f);
        g.fillPath(realKnob, juce::AffineTransform::rotation(angle).translated(centreX, centreY));

        g.setColour(juce::Colour(SliderCol));
    }

    if (thickness > 0)
    {
        const float innerRadius = radius * 0.2f;
        juce::Path p;
        p.addTriangle(-innerRadius, 0.0f, 0.0f, -radius * thickness * 1.1f, innerRadius, 0.0f);

        p.addEllipse(-innerRadius, -innerRadius, innerRadius * 2.0f, innerRadius * 2.0f);

        g.fillPath(p, juce::AffineTransform::rotation(angle).translated(centreX, centreY));
    }

    if (slider.isEnabled())
        g.setColour(slider.findColour(juce::Slider::rotarySliderOutlineColourId));
    else
        g.setColour(juce::Colour(0xffffffff));

    juce::Path outlineArc;
    outlineArc.addPieSegment(rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, thickness);
    outlineArc.closeSubPath();

    g.strokePath(outlineArc, juce::PathStrokeType(1));
}

juce::Button *UiLookAndFeel::createSliderButton(juce::Slider &, const bool isIncrement)
{
    return new juce::TextButton(isIncrement ? "+" : "-", juce::String());
}

class UiLookAndFeel::SliderLabelComp : public juce::Label
{
  public:
    SliderLabelComp() : juce::Label(juce::String(), juce::String()) {}

    void mouseWheelMove(const juce::MouseEvent &, const juce::MouseWheelDetails &) {}
};

juce::Label *UiLookAndFeel::createSliderTextBox(juce::Slider &slider)
{
    juce::Label *const l = new SliderLabelComp();

    l->setJustificationType(juce::Justification::centred);

    l->setColour(juce::Label::textColourId, slider.findColour(juce::Slider::textBoxTextColourId));

    l->setColour(juce::Label::backgroundColourId,
                 (slider.getSliderStyle() == juce::Slider::LinearBar ||
                  slider.getSliderStyle() == juce::Slider::LinearBarVertical)
                     ? juce::Colours::transparentBlack
                     : slider.findColour(juce::Slider::textBoxBackgroundColourId));
    l->setColour(juce::Label::outlineColourId,
                 slider.findColour(juce::Slider::textBoxOutlineColourId));

    l->setColour(juce::TextEditor::textColourId,
                 slider.findColour(juce::Slider::textBoxTextColourId));

    l->setColour(juce::TextEditor::backgroundColourId,
                 slider.findColour(juce::Slider::textBoxBackgroundColourId)
                     .withAlpha((slider.getSliderStyle() == juce::Slider::LinearBar ||
                                 slider.getSliderStyle() == juce::Slider::LinearBarVertical)
                                    ? 0.7f
                                    : 1.0f));

    l->setColour(juce::TextEditor::outlineColourId,
                 slider.findColour(juce::Slider::textBoxOutlineColourId));

    l->setColour(juce::TextEditor::highlightColourId,
                 slider.findColour(juce::Slider::textBoxHighlightColourId));

    return l;
}

juce::ImageEffectFilter *UiLookAndFeel::getSliderEffect(juce::Slider &) { return nullptr; }

juce::Font UiLookAndFeel::getSliderPopupFont(juce::Slider &)
{
    return defaultFont.withHeight(15.0f);
}

int UiLookAndFeel::getSliderPopupPlacement(juce::Slider &)
{
    return juce::BubbleComponent::above | juce::BubbleComponent::below |
           juce::BubbleComponent::left | juce::BubbleComponent::right;
}

//==============================================================================
void UiLookAndFeel::getTooltipSize(const juce::String &tipText, int &width, int &height)
{
    const juce::TextLayout tl(LookAndFeelHelpers::layoutTooltipText(tipText, juce::Colours::black));

    width = (int)(tl.getWidth() + 14.0f);
    height = (int)(tl.getHeight() + 6.0f);
}

void UiLookAndFeel::drawTooltip(juce::Graphics &g, const juce::String &text, int width, int height)
{
    g.fillAll(findColour(juce::TooltipWindow::backgroundColourId));

#if !JUCE_MAC // The mac windows already have a non-optional 1 pix outline, so don't double it
              // here..
    g.setColour(findColour(juce::TooltipWindow::outlineColourId));
    g.drawRect(0, 0, width, height, 1);
#endif

    LookAndFeelHelpers::layoutTooltipText(text, findColour(juce::TooltipWindow::textColourId))
        .draw(g, juce::Rectangle<float>((float)width, (float)height));
}

//==============================================================================
juce::Button *UiLookAndFeel::createFilenameComponentBrowseButton(const juce::String &text)
{
    return new juce::TextButton(text, TRANS("click to browse for a different file"));
}

void UiLookAndFeel::layoutFilenameComponent(juce::FilenameComponent &filenameComp,
                                            juce::ComboBox *filenameBox, juce::Button *browseButton)
{
    browseButton->setSize(80, filenameComp.getHeight());

    if (juce::TextButton *const tb = dynamic_cast<juce::TextButton *>(browseButton))
        tb->changeWidthToFitText();

    browseButton->setTopRightPosition(filenameComp.getWidth(), 0);

    filenameBox->setBounds(0, 0, browseButton->getX(), filenameComp.getHeight());
}

//==============================================================================
void UiLookAndFeel::drawConcertinaPanelHeader(juce::Graphics &g, const juce::Rectangle<int> &area,
                                              bool isMouseOver, bool /*isMouseDown*/,
                                              juce::ConcertinaPanel &, juce::Component &panel)
{
    g.fillAll(juce::Colours::grey.withAlpha(isMouseOver ? 0.9f : 0.7f));
    g.setColour(juce::Colours::black.withAlpha(0.5f));
    g.drawRect(area);

    g.setColour(juce::Colours::white);
    g.setFont(juce::Font(area.getHeight() * 0.7f).boldened());
    g.drawFittedText(panel.getName(), 4, 0, area.getWidth() - 6, area.getHeight(),
                     juce::Justification::centredLeft, 1);
}

//==============================================================================
void UiLookAndFeel::drawImageButton(juce::Graphics &g, juce::Image *image, int imageX, int imageY,
                                    int imageW, int imageH, const juce::Colour &overlayColour,
                                    float imageOpacity, juce::ImageButton &button)
{
    if (!button.isEnabled())
        imageOpacity *= 0.3f;

    juce::AffineTransform t =
        juce::RectanglePlacement(juce::RectanglePlacement::stretchToFit)
            .getTransformToFit(image->getBounds().toFloat(),
                               juce::Rectangle<int>(imageX, imageY, imageW, imageH).toFloat());

    if (!overlayColour.isOpaque())
    {
        g.setOpacity(imageOpacity);
        g.drawImageTransformed(*image, t, false);
    }

    if (!overlayColour.isTransparent())
    {
        g.setColour(overlayColour);
        g.drawImageTransformed(*image, t, true);
    }
}

//==============================================================================
void UiLookAndFeel::drawCornerResizer(juce::Graphics &g, int w, int h, bool /*isMouseOver*/,
                                      bool /*isMouseDragging*/)
{
    const float lineThickness = juce::jmin(w, h) * 0.075f;

    for (float i = 0.0f; i < 1.0f; i += 0.3f)
    {
        g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
        g.drawLine(w * i + lineThickness, h + 1.0f, w + 1.0f, h * i + lineThickness, lineThickness);
    }
}

void UiLookAndFeel::drawResizableFrame(juce::Graphics &g, int w, int h,
                                       const juce::BorderSize<int> &border)
{
    if (!border.isEmpty())
    {
        const juce::Rectangle<int> fullSize(0, 0, w, h);
        const juce::Rectangle<int> centreArea(border.subtractedFrom(fullSize));

        g.saveState();

        g.excludeClipRegion(centreArea);

        g.setColour(juce::Colour(0x50000000));
        g.drawRect(fullSize);

        g.setColour(juce::Colour(0x19000000));
        g.drawRect(centreArea.expanded(1, 1));

        g.restoreState();
    }
}

//==============================================================================
void UiLookAndFeel::fillResizableWindowBackground(juce::Graphics &g, int /*w*/, int /*h*/,
                                                  const juce::BorderSize<int> & /*border*/,
                                                  juce::ResizableWindow &window)
{
    g.setColour(window.getBackgroundColour());
    g.fillRect(0, 0, window.getWidth(), window.getHeight());

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    g.drawRect(0, 0, window.getWidth(), window.getHeight(), 2);
}

void UiLookAndFeel::drawResizableWindowBorder(juce::Graphics &g, int /*w*/, int /*h*/,
                                              const juce::BorderSize<int> & /*border*/,
                                              juce::ResizableWindow &)
{
    g.fillAll(juce::Colours::black);
}

void UiLookAndFeel::drawDocumentWindowTitleBar(juce::DocumentWindow &window, juce::Graphics &g,
                                               int w, int h, int titleSpaceX, int titleSpaceW,
                                               const juce::Image *icon, bool drawTitleTextOnLeft)
{
    const bool isActive = window.isActiveWindow();

    g.fillAll(window.getBackgroundColour().contrasting(isActive ? 0.0f : 0.25f));

    juce::Font font = defaultFont.withHeight(h * 0.65f);
    g.setFont(font);

    int textW = font.getStringWidth(window.getName());
    int iconW = 0;
    int iconH = 0;

    if (icon != nullptr)
    {
        iconH = (int)font.getHeight();
        iconW = icon->getWidth() * iconH / icon->getHeight() + 4;
    }

    textW = juce::jmin(titleSpaceW, textW + iconW);
    int textX = drawTitleTextOnLeft ? titleSpaceX : juce::jmax(titleSpaceX, (w - textW) / 2);

    if (textX + textW > titleSpaceX + titleSpaceW)
        textX = titleSpaceX + titleSpaceW - textW;

    if (icon != nullptr)
    {
        g.setOpacity(isActive ? 1.0f : 0.6f);
        g.drawImageWithin(*icon, textX, (h - iconH) / 2, iconW, iconH,
                          juce::RectanglePlacement::centred, false);
        textX += iconW;
        textW -= iconW;
    }

    if (window.isColourSpecified(juce::DocumentWindow::textColourId) ||
        isColourSpecified(juce::DocumentWindow::textColourId))
        g.setColour(window.findColour(juce::DocumentWindow::textColourId));
    else
        g.setColour(window.getBackgroundColour().contrasting(isActive ? 0.7f : 0.4f));

    g.drawText(window.getName(), textX, 0, textW, h, juce::Justification::centredLeft, true);
}

//==============================================================================
class UiLookAndFeel::GlassWindowButton : public juce::Button
{
  public:
    GlassWindowButton(const juce::String &name, juce::Colour col, const juce::Path &normalShape_,
                      const juce::Path &toggledShape_) noexcept
        : juce::Button(name), colour(col), normalShape(normalShape_), toggledShape(toggledShape_)
    {
    }

    //==============================================================================
    void paintButton(juce::Graphics &g, bool isMouseOverButton, bool isButtonDown) override
    {
        float alpha = isMouseOverButton ? (isButtonDown ? 1.0f : 0.8f) : 0.55f;

        if (!isEnabled())
            alpha *= 0.5f;

        float x = 0, y = 0, diam;

        if (getWidth() < getHeight())
        {
            diam = (float)getWidth() - 4;
            y = (getHeight() - getWidth()) * 0.5f;
        }
        else
        {
            diam = (float)getHeight() - 4;
            y = (getWidth() - getHeight()) * 0.5f;
        }

        x += diam * 0.05f + 2;
        y += diam * 0.05f + 2;
        diam *= 0.9f;

        g.setColour(juce::Colour::greyLevel(0.6f).withAlpha(
            alpha)); // , 0, y + diam, Colour::greyLevel (0.6f).withAlpha (alpha), 0, y, false
        g.fillEllipse(x, y, diam, diam);

        x += 2.0f;
        y += 2.0f;
        diam -= 4.0f;

        UiLookAndFeel::drawGlassSphere(g, x, y, diam, colour, 1.0f);

        juce::Path &p = getToggleState() ? toggledShape : normalShape;

        const juce::AffineTransform t(p.getTransformToScaleToFit(x + diam * 0.3f, y + diam * 0.3f,
                                                                 diam * 0.4f, diam * 0.4f, true));

        g.setColour(juce::Colours::black.withAlpha(alpha * 0.6f));
        g.fillPath(p, t);
    }

  private:
    juce::Colour colour;
    juce::Path normalShape, toggledShape;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GlassWindowButton)
};

juce::Button *UiLookAndFeel::createDocumentWindowButton(int buttonType)
{
    juce::Path shape;
    const float crossThickness = 0.25f;

    if (buttonType == juce::DocumentWindow::closeButton)
    {
        shape.addLineSegment(juce::Line<float>(0.0f, 0.0f, 1.0f, 1.0f), crossThickness * 1.4f);
        shape.addLineSegment(juce::Line<float>(1.0f, 0.0f, 0.0f, 1.0f), crossThickness * 1.4f);

        return new GlassWindowButton("close", juce::Colour(0xff991100), shape, shape);
    }

    if (buttonType == juce::DocumentWindow::minimiseButton)
    {
        shape.addLineSegment(juce::Line<float>(0.0f, 0.5f, 1.0f, 0.5f), crossThickness);

        return new GlassWindowButton("minimise", juce::Colour(0xffdfce89), shape, shape);
    }

    if (buttonType == juce::DocumentWindow::maximiseButton)
    {
        shape.addLineSegment(juce::Line<float>(0.5f, 0.0f, 0.5f, 1.0f), crossThickness);
        shape.addLineSegment(juce::Line<float>(0.0f, 0.5f, 1.0f, 0.5f), crossThickness);

        juce::Path fullscreenShape;
        fullscreenShape.startNewSubPath(45.0f, 100.0f);
        fullscreenShape.lineTo(0.0f, 100.0f);
        fullscreenShape.lineTo(0.0f, 0.0f);
        fullscreenShape.lineTo(100.0f, 0.0f);
        fullscreenShape.lineTo(100.0f, 45.0f);
        fullscreenShape.addRectangle(45.0f, 45.0f, 100.0f, 100.0f);
        juce::PathStrokeType(30.0f).createStrokedPath(fullscreenShape, fullscreenShape);

        return new GlassWindowButton("maximise", juce::Colour(0xffdfce89), shape, fullscreenShape);
    }

    jassertfalse;
    return nullptr;
}

void UiLookAndFeel::positionDocumentWindowButtons(juce::DocumentWindow &, int titleBarX,
                                                  int titleBarY, int titleBarW, int titleBarH,
                                                  juce::Button *minimiseButton,
                                                  juce::Button *maximiseButton,
                                                  juce::Button *closeButton,
                                                  bool positionTitleBarButtonsOnLeft)
{
    const int buttonW = titleBarH - titleBarH / 8;

    int x = positionTitleBarButtonsOnLeft ? titleBarX + 4
                                          : titleBarX + titleBarW - buttonW - buttonW / 4;

    if (closeButton != nullptr)
    {
        closeButton->setBounds(x, titleBarY, buttonW, titleBarH);
        x += positionTitleBarButtonsOnLeft ? buttonW : -(buttonW + buttonW / 4);
    }

    if (positionTitleBarButtonsOnLeft)
        std::swap(minimiseButton, maximiseButton);

    if (maximiseButton != nullptr)
    {
        maximiseButton->setBounds(x, titleBarY, buttonW, titleBarH);
        x += positionTitleBarButtonsOnLeft ? buttonW : -buttonW;
    }

    if (minimiseButton != nullptr)
        minimiseButton->setBounds(x, titleBarY, buttonW, titleBarH);
}

int UiLookAndFeel::getDefaultMenuBarHeight() { return 24; }

//==============================================================================
juce::DropShadower *UiLookAndFeel::createDropShadowerForComponent(juce::Component *)
{
    return new juce::DropShadower(
        juce::DropShadow(juce::Colours::black.withAlpha(0.4f), 10, juce::Point<int>(0, 2)));
}

//==============================================================================
void UiLookAndFeel::drawStretchableLayoutResizerBar(juce::Graphics &g, int w, int h,
                                                    bool /*isVerticalBar*/, bool isMouseOver,
                                                    bool isMouseDragging)
{
    float alpha = 0.5f;

    if (isMouseOver || isMouseDragging)
    {
        g.fillAll(juce::Colour(0x190000ff));
        alpha = 1.0f;
    }

    const float cx = w * 0.5f;
    const float cy = h * 0.5f;
    const float cr = juce::jmin(w, h) * 0.4f;

    g.setGradientFill(juce::ColourGradient(juce::Colours::white.withAlpha(alpha), cx + cr * 0.1f,
                                           cy + cr, juce::Colours::black.withAlpha(alpha), cx,
                                           cy - cr * 4.0f, true));

    g.fillEllipse(cx - cr, cy - cr, cr * 2.0f, cr * 2.0f);
}

//==============================================================================
void UiLookAndFeel::drawGroupComponentOutline(juce::Graphics &g, int width, int height,
                                              const juce::String &text,
                                              const juce::Justification &position,
                                              juce::GroupComponent &group)
{
    const float textH = 15.0f;
    const float indent = 3.0f;
    const float textEdgeGap = 4.0f;
    float cs = 5.0f;

    juce::Font f(textH);

    juce::Path p;
    float x = indent;
    float y = f.getAscent() - 3.0f;
    float w = juce::jmax(0.0f, width - x * 2.0f);
    float h = juce::jmax(0.0f, height - y - indent);
    cs = juce::jmin(cs, w * 0.5f, h * 0.5f);
    const float cs2 = 2.0f * cs;

    float textW = text.isEmpty() ? 0
                                 : juce::jlimit(0.0f, juce::jmax(0.0f, w - cs2 - textEdgeGap * 2),
                                                f.getStringWidth(text) + textEdgeGap * 2.0f);
    float textX = cs + textEdgeGap;

    if (position.testFlags(juce::Justification::horizontallyCentred))
        textX = cs + (w - cs2 - textW) * 0.5f;
    else if (position.testFlags(juce::Justification::right))
        textX = w - cs - textW - textEdgeGap;

    p.startNewSubPath(x + textX + textW, y);
    p.lineTo(x + w - cs, y);

    p.addArc(x + w - cs2, y, cs2, cs2, 0, juce::MathConstants<float>::pi * 0.5f);
    p.lineTo(x + w, y + h - cs);

    p.addArc(x + w - cs2, y + h - cs2, cs2, cs2, juce::MathConstants<float>::pi * 0.5f,
             juce::MathConstants<float>::pi);
    p.lineTo(x + cs, y + h);

    p.addArc(x, y + h - cs2, cs2, cs2, juce::MathConstants<float>::pi,
             juce::MathConstants<float>::pi * 1.5f);
    p.lineTo(x, y + cs);

    p.addArc(x, y, cs2, cs2, juce::MathConstants<float>::pi * 1.5f,
             juce::MathConstants<float>::pi * 2.0f);
    p.lineTo(x + textX, y);

    const float alpha = group.isEnabled() ? 1.0f : 0.5f;

    g.setColour(group.findColour(juce::GroupComponent::outlineColourId).withMultipliedAlpha(alpha));

    g.strokePath(p, juce::PathStrokeType(2.0f));

    g.setColour(group.findColour(juce::GroupComponent::textColourId).withMultipliedAlpha(alpha));
    g.setFont(f);
    g.drawText(text, juce::roundToInt(x + textX), 0, juce::roundToInt(textW),
               juce::roundToInt(textH), juce::Justification::centred, true);
}

//==============================================================================
int UiLookAndFeel::getTabButtonOverlap(int tabDepth) { return 1 + tabDepth / 3; }

int UiLookAndFeel::getTabButtonSpaceAroundImage() { return 4; }

int UiLookAndFeel::getTabButtonBestWidth(juce::TabBarButton &button, int tabDepth)
{
    int width = juce::Font(tabDepth * 0.6f).getStringWidth(button.getButtonText().trim()) +
                getTabButtonOverlap(tabDepth) * 2;

    if (juce::Component *const extraComponent = button.getExtraComponent())
        width += button.getTabbedButtonBar().isVertical() ? extraComponent->getHeight()
                                                          : extraComponent->getWidth();

    return juce::jlimit(tabDepth * 2, tabDepth * 8, width);
}

juce::Rectangle<int> UiLookAndFeel::getTabButtonExtraComponentBounds(
    const juce::TabBarButton &button, juce::Rectangle<int> &textArea, juce::Component &comp)
{
    juce::Rectangle<int> extraComp;

    const juce::TabbedButtonBar::Orientation orientation =
        button.getTabbedButtonBar().getOrientation();

    if (button.getExtraComponentPlacement() == juce::TabBarButton::beforeText)
    {
        switch (orientation)
        {
        case juce::TabbedButtonBar::TabsAtBottom:
        case juce::TabbedButtonBar::TabsAtTop:
            extraComp = textArea.removeFromLeft(comp.getWidth());
            break;
        case juce::TabbedButtonBar::TabsAtLeft:
            extraComp = textArea.removeFromBottom(comp.getHeight());
            break;
        case juce::TabbedButtonBar::TabsAtRight:
            extraComp = textArea.removeFromTop(comp.getHeight());
            break;
        default:
            jassertfalse;
            break;
        }
    }
    else
    {
        switch (orientation)
        {
        case juce::TabbedButtonBar::TabsAtBottom:
        case juce::TabbedButtonBar::TabsAtTop:
            extraComp = textArea.removeFromRight(comp.getWidth());
            break;
        case juce::TabbedButtonBar::TabsAtLeft:
            extraComp = textArea.removeFromTop(comp.getHeight());
            break;
        case juce::TabbedButtonBar::TabsAtRight:
            extraComp = textArea.removeFromBottom(comp.getHeight());
            break;
        default:
            jassertfalse;
            break;
        }
    }

    return extraComp;
}

void UiLookAndFeel::createTabButtonShape(juce::TabBarButton &button, juce::Path &p,
                                         bool /*isMouseOver*/, bool /*isMouseDown*/)
{
    const juce::Rectangle<int> activeArea(button.getActiveArea());
    const float w = (float)activeArea.getWidth();
    const float h = (float)activeArea.getHeight();

    float length = w;
    float depth = h;

    if (button.getTabbedButtonBar().isVertical())
        std::swap(length, depth);

    const float indent = (float)getTabButtonOverlap((int)depth);
    const float overhang = 4.0f;

    switch (button.getTabbedButtonBar().getOrientation())
    {
    case juce::TabbedButtonBar::TabsAtLeft:
        p.startNewSubPath(w, 0.0f);
        p.lineTo(0.0f, indent);
        p.lineTo(0.0f, h - indent);
        p.lineTo(w, h);
        p.lineTo(w + overhang, h + overhang);
        p.lineTo(w + overhang, -overhang);
        break;

    case juce::TabbedButtonBar::TabsAtRight:
        p.startNewSubPath(0.0f, 0.0f);
        p.lineTo(w, indent);
        p.lineTo(w, h - indent);
        p.lineTo(0.0f, h);
        p.lineTo(-overhang, h + overhang);
        p.lineTo(-overhang, -overhang);
        break;

    case juce::TabbedButtonBar::TabsAtBottom:
        p.startNewSubPath(0.0f, 0.0f);
        p.lineTo(indent, h);
        p.lineTo(w - indent, h);
        p.lineTo(w, 0.0f);
        p.lineTo(w + overhang, -overhang);
        p.lineTo(-overhang, -overhang);
        break;

    default:
        p.startNewSubPath(0.0f, h);
        p.lineTo(indent, 0.0f);
        p.lineTo(w - indent, 0.0f);
        p.lineTo(w, h);
        p.lineTo(w + overhang, h + overhang);
        p.lineTo(-overhang, h + overhang);
        break;
    }

    p.closeSubPath();

    p = p.createPathWithRoundedCorners(3.0f);
}

void UiLookAndFeel::fillTabButtonShape(juce::TabBarButton &button, juce::Graphics &g,
                                       const juce::Path &path, bool /*isMouseOver*/,
                                       bool /*isMouseDown*/)
{
    const juce::Colour tabBackground(button.getTabBackgroundColour());
    const bool isFrontTab = button.isFrontTab();

    g.setColour(isFrontTab ? tabBackground : tabBackground.withMultipliedAlpha(0.9f));

    g.fillPath(path);

    g.setColour(button
                    .findColour(isFrontTab ? juce::TabbedButtonBar::frontOutlineColourId
                                           : juce::TabbedButtonBar::tabOutlineColourId,
                                false)
                    .withMultipliedAlpha(button.isEnabled() ? 1.0f : 0.5f));

    g.strokePath(path, juce::PathStrokeType(isFrontTab ? 1.0f : 0.5f));
}

void UiLookAndFeel::drawTabButtonText(juce::TabBarButton &button, juce::Graphics &g,
                                      bool isMouseOver, bool isMouseDown)
{
    const juce::Rectangle<float> area(button.getTextArea().toFloat());

    float length = area.getWidth();
    float depth = area.getHeight();

    if (button.getTabbedButtonBar().isVertical())
        std::swap(length, depth);

    juce::Font font(depth * 0.6f);
    font.setUnderline(button.hasKeyboardFocus(false));

    juce::AffineTransform t;

    switch (button.getTabbedButtonBar().getOrientation())
    {
    case juce::TabbedButtonBar::TabsAtLeft:
        t = t.rotated(juce::MathConstants<float>::pi * -0.5f)
                .translated(area.getX(), area.getBottom());
        break;
    case juce::TabbedButtonBar::TabsAtRight:
        t = t.rotated(juce::MathConstants<float>::pi * 0.5f)
                .translated(area.getRight(), area.getY());
        break;
    case juce::TabbedButtonBar::TabsAtTop:
    case juce::TabbedButtonBar::TabsAtBottom:
        t = t.translated(area.getX(), area.getY());
        break;
    default:
        jassertfalse;
        break;
    }

    juce::Colour col;

    if (button.isFrontTab() &&
        (button.isColourSpecified(juce::TabbedButtonBar::frontTextColourId) ||
         isColourSpecified(juce::TabbedButtonBar::frontTextColourId)))
        col = findColour(juce::TabbedButtonBar::frontTextColourId);
    else if (button.isColourSpecified(juce::TabbedButtonBar::tabTextColourId) ||
             isColourSpecified(juce::TabbedButtonBar::tabTextColourId))
        col = findColour(juce::TabbedButtonBar::tabTextColourId);
    else
        col = button.getTabBackgroundColour().contrasting();

    const float alpha = button.isEnabled() ? ((isMouseOver || isMouseDown) ? 1.0f : 0.8f) : 0.3f;

    g.setColour(col.withMultipliedAlpha(alpha));
    g.setFont(font);
    g.addTransform(t);

    g.drawFittedText(button.getButtonText().trim(), 0, 0, (int)length, (int)depth,
                     juce::Justification::centred, juce::jmax(1, ((int)depth) / 12));
}

void UiLookAndFeel::drawTabButton(juce::TabBarButton &button, juce::Graphics &g, bool isMouseOver,
                                  bool isMouseDown)
{
    juce::Path tabShape;
    createTabButtonShape(button, tabShape, isMouseOver, isMouseDown);

    const juce::Rectangle<int> activeArea(button.getActiveArea());
    tabShape.applyTransform(
        juce::AffineTransform::translation((float)activeArea.getX(), (float)activeArea.getY()));

    juce::DropShadow(juce::Colours::black.withAlpha(0.5f), 2, juce::Point<int>(0, 1))
        .drawForPath(g, tabShape);

    fillTabButtonShape(button, g, tabShape, isMouseOver, isMouseDown);
    drawTabButtonText(button, g, isMouseOver, isMouseDown);
}

void UiLookAndFeel::drawTabbedButtonBarBackground(juce::TabbedButtonBar &, juce::Graphics &) {}

void UiLookAndFeel::drawTabAreaBehindFrontButton(juce::TabbedButtonBar &bar, juce::Graphics &g,
                                                 const int w, const int h)
{
    const float shadowSize = 0.2f;

    juce::Rectangle<int> shadowRect, line;
    juce::ColourGradient gradient(juce::Colours::black.withAlpha(bar.isEnabled() ? 0.25f : 0.15f),
                                  0, 0, juce::Colours::transparentBlack, 0, 0, false);

    switch (bar.getOrientation())
    {
    case juce::TabbedButtonBar::TabsAtLeft:
        gradient.point1.x = (float)w;
        gradient.point2.x = w * (1.0f - shadowSize);
        shadowRect.setBounds((int)gradient.point2.x, 0, w - (int)gradient.point2.x, h);
        line.setBounds(w - 1, 0, 1, h);
        break;

    case juce::TabbedButtonBar::TabsAtRight:
        gradient.point2.x = w * shadowSize;
        shadowRect.setBounds(0, 0, (int)gradient.point2.x, h);
        line.setBounds(0, 0, 1, h);
        break;

    case juce::TabbedButtonBar::TabsAtTop:
        gradient.point1.y = (float)h;
        gradient.point2.y = h * (1.0f - shadowSize);
        shadowRect.setBounds(0, (int)gradient.point2.y, w, h - (int)gradient.point2.y);
        line.setBounds(0, h - 1, w, 1);
        break;

    case juce::TabbedButtonBar::TabsAtBottom:
        gradient.point2.y = h * shadowSize;
        shadowRect.setBounds(0, 0, w, (int)gradient.point2.y);
        line.setBounds(0, 0, w, 1);
        break;

    default:
        break;
    }

    g.setGradientFill(gradient);
    g.fillRect(shadowRect.expanded(2, 2));

    g.setColour(juce::Colour(0x80000000));
    g.fillRect(line);
}

juce::Button *UiLookAndFeel::createTabBarExtrasButton()
{
    const float thickness = 7.0f;
    const float indent = 22.0f;

    juce::Path p;
    p.addEllipse(-10.0f, -10.0f, 120.0f, 120.0f);

    juce::DrawablePath ellipse;
    ellipse.setPath(p);
    ellipse.setFill(juce::Colour(0x99ffffff));

    p.clear();
    p.addEllipse(0.0f, 0.0f, 100.0f, 100.0f);
    p.addRectangle(indent, 50.0f - thickness, 100.0f - indent * 2.0f, thickness * 2.0f);
    p.addRectangle(50.0f - thickness, indent, thickness * 2.0f, 50.0f - indent - thickness);
    p.addRectangle(50.0f - thickness, 50.0f + thickness, thickness * 2.0f,
                   50.0f - indent - thickness);
    p.setUsingNonZeroWinding(false);

    juce::DrawablePath dp;
    dp.setPath(p);
    dp.setFill(juce::Colour(0x59000000));

    juce::DrawableComposite normalImage;
    FIXMEPORT;
    normalImage.addAndMakeVisible(*(ellipse.createCopy()));
    normalImage.addAndMakeVisible(*(dp.createCopy()));

    dp.setFill(juce::Colour(0xcc000000));

    juce::DrawableComposite overImage;
    overImage.addAndMakeVisible(*(ellipse.createCopy()));
    overImage.addAndMakeVisible(*(dp.createCopy()));

    juce::DrawableButton *db = new juce::DrawableButton("tabs", juce::DrawableButton::ImageFitted);
    db->setImages(&normalImage, &overImage, nullptr);
    return db;
}

//==============================================================================
void UiLookAndFeel::drawTableHeaderBackground(juce::Graphics &g, juce::TableHeaderComponent &header)
{
    g.fillAll(juce::Colours::white);

    juce::Rectangle<int> area(header.getLocalBounds());
    area.removeFromTop(area.getHeight() / 2);

    g.setGradientFill(juce::ColourGradient(juce::Colour(0xffe8ebf9), 0.0f, (float)area.getY(),
                                           juce::Colour(0xfff6f8f9), 0.0f, (float)area.getBottom(),
                                           false));
    g.fillRect(area);

    g.setColour(juce::Colour(0x33000000));
    g.fillRect(area.removeFromBottom(1));

    for (int i = header.getNumColumns(true); --i >= 0;)
        g.fillRect(header.getColumnPosition(i).removeFromRight(1));
}

void UiLookAndFeel::drawTableHeaderColumn(juce::Graphics &g, const juce::String &columnName,
                                          int /*columnId*/, int width, int height, bool isMouseOver,
                                          bool isMouseDown, int columnFlags)
{
    if (isMouseDown)
        g.fillAll(juce::Colour(0x8899aadd));
    else if (isMouseOver)
        g.fillAll(juce::Colour(0x5599aadd));

    juce::Rectangle<int> area(width, height);
    area.reduce(4, 0);

    if ((columnFlags & (juce::TableHeaderComponent::sortedForwards |
                        juce::TableHeaderComponent::sortedBackwards)) != 0)
    {
        juce::Path sortArrow;
        sortArrow.addTriangle(
            0.0f, 0.0f, 0.5f,
            (columnFlags & juce::TableHeaderComponent::sortedForwards) != 0 ? -0.8f : 0.8f, 1.0f,
            0.0f);

        g.setColour(juce::Colour(0x99000000));
        g.fillPath(sortArrow, sortArrow.getTransformToScaleToFit(
                                  area.removeFromRight(height / 2).reduced(2).toFloat(), true));
    }

    g.setColour(juce::Colours::black);
    g.setFont(juce::Font(height * 0.5f, juce::Font::bold));
    g.drawFittedText(columnName, area, juce::Justification::centredLeft, 1);
}

//==============================================================================
void UiLookAndFeel::drawLasso(juce::Graphics &g, juce::Component &lassoComp)
{
    const int outlineThickness = 1;

    g.fillAll(lassoComp.findColour(0x1000440 /*lassoFillColourId*/));

    g.setColour(lassoComp.findColour(0x1000441 /*lassoOutlineColourId*/));
    g.drawRect(lassoComp.getLocalBounds(), outlineThickness);
}

//==============================================================================
void UiLookAndFeel::paintToolbarBackground(juce::Graphics &g, int w, int h, juce::Toolbar &toolbar)
{
    const juce::Colour background(toolbar.findColour(juce::Toolbar::backgroundColourId));

    g.setGradientFill(juce::ColourGradient(background, 0.0f, 0.0f, background.darker(0.1f),
                                           toolbar.isVertical() ? w - 1.0f : 0.0f,
                                           toolbar.isVertical() ? 0.0f : h - 1.0f, false));
    g.fillAll();
}

juce::Button *UiLookAndFeel::createToolbarMissingItemsButton(juce::Toolbar & /*toolbar*/)
{
    return createTabBarExtrasButton();
}

void UiLookAndFeel::paintToolbarButtonBackground(juce::Graphics &g, int /*width*/, int /*height*/,
                                                 bool isMouseOver, bool isMouseDown,
                                                 juce::ToolbarItemComponent &component)
{
    if (isMouseDown)
        g.fillAll(component.findColour(juce::Toolbar::buttonMouseDownBackgroundColourId, true));
    else if (isMouseOver)
        g.fillAll(component.findColour(juce::Toolbar::buttonMouseOverBackgroundColourId, true));
}

void UiLookAndFeel::paintToolbarButtonLabel(juce::Graphics &g, int x, int y, int width, int height,
                                            const juce::String &text,
                                            juce::ToolbarItemComponent &component)
{
    g.setColour(component.findColour(juce::Toolbar::labelTextColourId, true)
                    .withAlpha(component.isEnabled() ? 1.0f : 0.25f));

    const float fontHeight = juce::jmin(14.0f, height * 0.85f);
    g.setFont(fontHeight);

    g.drawFittedText(text, x, y, width, height, juce::Justification::centred,
                     juce::jmax(1, height / (int)fontHeight));
}

//==============================================================================
void UiLookAndFeel::drawPropertyPanelSectionHeader(juce::Graphics &g, const juce::String &name,
                                                   bool isOpen, int width, int height)
{
    const float buttonSize = height * 0.75f;
    const float buttonIndent = (height - buttonSize) * 0.5f;

    drawTreeviewPlusMinusBox(
        g, juce::Rectangle<float>(buttonIndent, buttonIndent, buttonSize, buttonSize),
        juce::Colours::white, isOpen, false);

    const int textX = (int)(buttonIndent * 2.0f + buttonSize + 2.0f);

    g.setColour(juce::Colours::black);
    g.setFont(juce::Font(height * 0.7f, juce::Font::bold));
    g.drawText(name, textX, 0, width - textX - 4, height, juce::Justification::centredLeft, true);
}

void UiLookAndFeel::drawPropertyComponentBackground(juce::Graphics &g, int width, int height,
                                                    juce::PropertyComponent &component)
{
    g.setColour(component.findColour(juce::PropertyComponent::backgroundColourId));
    g.fillRect(0, 0, width, height - 1);
}

void UiLookAndFeel::drawPropertyComponentLabel(juce::Graphics &g, int, int height,
                                               juce::PropertyComponent &component)
{
    g.setColour(component.findColour(juce::PropertyComponent::labelTextColourId)
                    .withMultipliedAlpha(component.isEnabled() ? 1.0f : 0.6f));

    g.setFont(juce::jmin(height, 24) * 0.65f);

    const juce::Rectangle<int> r(getPropertyComponentContentPosition(component));

    g.drawFittedText(component.getName(), 3, r.getY(), r.getX() - 5, r.getHeight(),
                     juce::Justification::centredLeft, 2);
}

juce::Rectangle<int>
UiLookAndFeel::getPropertyComponentContentPosition(juce::PropertyComponent &component)
{
    const int textW = juce::jmin(200, component.getWidth() / 3);
    return juce::Rectangle<int>(textW, 1, component.getWidth() - textW - 1,
                                component.getHeight() - 3);
}

//==============================================================================
void UiLookAndFeel::drawCallOutBoxBackground(juce::CallOutBox &box, juce::Graphics &g,
                                             const juce::Path &path, juce::Image &cachedImage)
{
    if (cachedImage.isNull())
    {
        cachedImage = juce::Image(juce::Image::ARGB, box.getWidth(), box.getHeight(), true);
        juce::Graphics g2(cachedImage);

        juce::DropShadow(juce::Colours::black.withAlpha(0.7f), 8, juce::Point<int>(0, 2))
            .drawForPath(g2, path);
    }

    g.setColour(juce::Colours::black);
    g.drawImageAt(cachedImage, 0, 0);

    g.setColour(juce::Colour::greyLevel(0.23f).withAlpha(0.9f));
    g.fillPath(path);

    g.setColour(juce::Colours::white.withAlpha(0.8f));
    g.strokePath(path, juce::PathStrokeType(2.0f));
}

//==============================================================================
juce::AttributedString UiLookAndFeel::createFileChooserHeaderText(const juce::String &title,
                                                                  const juce::String &instructions)
{
    juce::AttributedString s;
    s.setJustification(juce::Justification::centred);

    const juce::Colour colour(findColour(juce::FileChooserDialogBox::titleTextColourId));
    s.append(title + "\n\n", juce::Font(17.0f, juce::Font::bold), colour);
    s.append(instructions, juce::Font(14.0f), colour);

    return s;
}

void UiLookAndFeel::drawFileBrowserRow(juce::Graphics &g, int width, int height,
                                       const juce::String &filename, juce::Image *icon,
                                       const juce::String &fileSizeDescription,
                                       const juce::String &fileTimeDescription,
                                       const bool isDirectory, const bool isItemSelected,
                                       const int /*itemIndex*/,
                                       juce::DirectoryContentsDisplayComponent &dcc)
{
    juce::Component *const fileListComp = dynamic_cast<juce::Component *>(&dcc);

    if (isItemSelected)
        g.fillAll(fileListComp != nullptr
                      ? fileListComp->findColour(
                            juce::DirectoryContentsDisplayComponent::highlightColourId)
                      : findColour(juce::DirectoryContentsDisplayComponent::highlightColourId));

    const int x = 32;
    g.setColour(juce::Colours::black);

    if (icon != nullptr && icon->isValid())
    {
        g.drawImageWithin(
            *icon, 2, 2, x - 4, height - 4,
            juce::RectanglePlacement::centred | juce::RectanglePlacement::onlyReduceInSize, false);
    }
    else
    {
        if (const juce::Drawable *d =
                isDirectory ? getDefaultFolderImage() : getDefaultDocumentFileImage())
            d->drawWithin(g, juce::Rectangle<float>(2.0f, 2.0f, x - 4.0f, height - 4.0f),
                          juce::RectanglePlacement::centred |
                              juce::RectanglePlacement::onlyReduceInSize,
                          1.0f);
    }

    g.setColour(
        fileListComp != nullptr
            ? fileListComp->findColour(juce::DirectoryContentsDisplayComponent::textColourId)
            : findColour(juce::DirectoryContentsDisplayComponent::textColourId));
    g.setFont(height * 0.7f);

    if (width > 450 && !isDirectory)
    {
        const int sizeX = juce::roundToInt(width * 0.7f);
        const int dateX = juce::roundToInt(width * 0.8f);

        g.drawFittedText(filename, x, 0, sizeX - x, height, juce::Justification::centredLeft, 1);

        g.setFont(height * 0.5f);
        g.setColour(juce::Colours::darkgrey);

        if (!isDirectory)
        {
            g.drawFittedText(fileSizeDescription, sizeX, 0, dateX - sizeX - 8, height,
                             juce::Justification::centredRight, 1);

            g.drawFittedText(fileTimeDescription, dateX, 0, width - 8 - dateX, height,
                             juce::Justification::centredRight, 1);
        }
    }
    else
    {
        g.drawFittedText(filename, x, 0, width - x, height, juce::Justification::centredLeft, 1);
    }
}

juce::Button *UiLookAndFeel::createFileBrowserGoUpButton()
{
    juce::DrawableButton *goUpButton =
        new juce::DrawableButton("up", juce::DrawableButton::ImageOnButtonBackground);

    juce::Path arrowPath;
    arrowPath.addArrow(juce::Line<float>(50.0f, 100.0f, 50.0f, 0.0f), 40.0f, 100.0f, 50.0f);

    juce::DrawablePath arrowImage;
    arrowImage.setFill(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    arrowImage.setPath(arrowPath);

    goUpButton->setImages(&arrowImage);

    return goUpButton;
}

void UiLookAndFeel::layoutFileBrowserComponent(
    juce::FileBrowserComponent &browserComp,
    juce::DirectoryContentsDisplayComponent *fileListComponent,
    juce::FilePreviewComponent *previewComp, juce::ComboBox *currentPathBox,
    juce::TextEditor *filenameBox, juce::Button *goUpButton)
{
    const int x = 8;
    int w = browserComp.getWidth() - x - x;

    if (previewComp != nullptr)
    {
        const int previewWidth = w / 3;
        previewComp->setBounds(x + w - previewWidth, 0, previewWidth, browserComp.getHeight());

        w -= previewWidth + 4;
    }

    int y = 4;

    const int controlsHeight = 22;
    const int bottomSectionHeight = controlsHeight + 8;
    const int upButtonWidth = 50;

    currentPathBox->setBounds(x, y, w - upButtonWidth - 6, controlsHeight);
    goUpButton->setBounds(x + w - upButtonWidth, y, upButtonWidth, controlsHeight);

    y += controlsHeight + 4;

    if (juce::Component *const listAsComp = dynamic_cast<juce::Component *>(fileListComponent))
    {
        listAsComp->setBounds(x, y, w, browserComp.getHeight() - y - bottomSectionHeight);
        y = listAsComp->getBottom() + 4;
    }

    filenameBox->setBounds(x + 50, y, w - 50, controlsHeight);
}

// Pulls a drawable out of compressed valuetree data..
static juce::Drawable *loadDrawableFromData(const void *data, size_t numBytes)
{
    juce::MemoryInputStream m(data, numBytes, false);
    juce::GZIPDecompressorInputStream gz(m);
    juce::ValueTree drawable(juce::ValueTree::readFromStream(gz));
    FIXMEPORT;
    return nullptr;
    // return Drawable::createFromValueTree (drawable.getChild (0), nullptr);
}

const juce::Drawable *UiLookAndFeel::getDefaultFolderImage()
{
    if (folderImage == nullptr)
    {
        static const unsigned char drawableData[] = {
            120, 218, 197, 86,  77,  111, 27,  55,  16,  229, 182, 161, 237, 6,   61,  39,  233,
            77,  63,  192, 38,  56,  195, 225, 215, 209, 105, 210, 2,   141, 13,  20,  201, 193,
            109, 111, 178, 181, 178, 183, 145, 181, 130, 180, 110, 145, 127, 159, 199, 93,  73,
            137, 87,  53,  218, 91,  109, 192, 160, 151, 179, 156, 55,  111, 222, 188, 229, 155,
            247, 231, 87,  231, 175, 47,  222, 170, 234, 155, 229, 244, 190, 86,  213, 115, 253,
            102, 61,  253, 123, 122, 189, 168, 85,  51,  83,  213, 119, 250, 238, 221, 47,  231,
            151, 175, 223, 169, 170, 250, 121, 221, 62,  172, 84,  245, 172, 60,  63,  209, 243,
            118, 49,  171, 215, 170, 107, 87,  23,  245, 188, 83,  213, 145, 182, 167, 19,  91,
            254, 127, 223, 220, 222, 117, 37,  68,  82,  40,  143, 174, 219, 174, 107, 239, 135,
            168, 147, 18,  37,  108, 85,  245, 237, 46,  207, 70,  33,  249, 175, 211, 238, 78,
            85,  186, 28,  253, 76,  175, 73,  109, 186, 117, 251, 177, 190, 106, 102, 229, 241,
            247, 58,  24,  103, 203, 15,  101, 245, 103, 219, 44,  187, 15,  221, 39,  0,   172,
            142, 245, 125, 211, 1,   196, 205, 116, 181, 125, 114, 164, 175, 31,  186, 78,  45,
            219, 229, 31,  245, 186, 189, 106, 150, 179, 102, 121, 139, 100, 154, 240, 231, 167,
            102, 177, 64,  72,  247, 105, 213, 23,  122, 187, 158, 206, 154, 122, 217, 169, 85,
            57,  18,  1,   47,  53,  101, 107, 18,  135, 204, 167, 147, 192, 201, 216, 20,  114,
            244, 195, 62,  171, 234, 7,   125, 198, 100, 136, 216, 145, 149, 211, 9,   57,  103,
            40,  249, 72,  219, 8,   167, 170, 87,  250, 140, 162, 199, 123, 226, 3,   34,  82,
            202, 134, 131, 13,  172, 74,  170, 233, 162, 0,   177, 234, 166, 93,  180, 15,  235,
            141, 170, 206, 180, 157, 204, 231, 150, 156, 159, 207, 39,  195, 50,  214, 88,  18,
            150, 245, 205, 124, 250, 104, 169, 212, 135, 158, 19,  144, 53,  20,  112, 172, 55,
            237, 2,   132, 13,  199, 149, 130, 230, 115, 145, 112, 147, 147, 82,  61,  157, 32,
            238, 178, 253, 11,  145, 213, 138, 10,  52,  138, 38,  103, 111, 99,  164, 211, 137,
            139, 198, 35,  177, 35,  167, 212, 143, 15,  215, 205, 13,  160, 109, 163, 172, 225,
            152, 16,  232, 17,  149, 140, 103, 144, 158, 146, 90,  113, 217, 12,  6,   197, 167,
            236, 3,   54,  5,   181, 101, 73,  54,  138, 90,  245, 165, 227, 120, 18,  252, 150,
            77,  15,  242, 188, 228, 204, 81,  169, 139, 102, 249, 5,   68,  192, 145, 14,  244,
            112, 1,   145, 29,  94,  137, 96,  235, 49,  136, 151, 58,  246, 32,  88,  192, 161,
            88,  176, 76,  226, 36,  247, 24,  176, 7,   232, 62,  16,  83,  42,  155, 201, 160,
            30,  222, 65,  72,  98,  82,  76,  33,  198, 254, 197, 96,  124, 10,  150, 243, 8,
            130, 48,  228, 36,  94,  124, 6,   4,   43,  38,  0,   142, 205, 99,  30,  4,   221,
            13,  33,  230, 220, 71,  177, 65,  49,  142, 243, 150, 7,   1,   51,  20,  2,   5,
            96,  96,  84,  225, 56,  217, 188, 3,   33,  46,  24,  228, 112, 69,  69,  12,  68,
            228, 108, 242, 99,  16,  165, 118, 208, 28,  51,  200, 98,  87,  42,  74,  62,  209,
            24,  4,   206, 48,  22,  153, 125, 132, 220, 196, 56,  15,  234, 99,  216, 130, 0,
            141, 38,  74,  162, 130, 48,  35,  163, 141, 94,  196, 245, 32,  94,  104, 7,   154,
            132, 209, 40,  108, 162, 165, 232, 153, 165, 17,  4,   138, 201, 176, 135, 58,  49,
            165, 130, 122, 108, 114, 54,  28,  240, 64,  17,  89,  188, 79,  177, 116, 149, 10,
            4,   246, 91,  30,  94,  104, 112, 96,  226, 144, 131, 144, 142, 98,  78,  177, 7,
            128, 81,  242, 224, 140, 36,  249, 80,  208, 145, 196, 12,  202, 15,  16,  60,  161,
            200, 69,  187, 169, 213, 86,  198, 123, 87,  224, 255, 199, 21,  94,  105, 134, 72,
            40,  177, 245, 14,  182, 32,  232, 54,  196, 231, 100, 111, 11,  189, 168, 201, 39,
            177, 84,  102, 38,  139, 177, 168, 74,  210, 87,  174, 64,  20,  138, 160, 67,  111,
            10,  4,   98,  196, 97,  60,  158, 118, 133, 25,  111, 173, 224, 171, 37,  97,  185,
            119, 133, 221, 242, 63,  184, 194, 140, 71,  174, 240, 252, 145, 43,  72,  32,  147,
            146, 147, 4,   104, 104, 117, 134, 10,  18,  12,  107, 212, 40,  72,  148, 57,  6,
            71,  69,  135, 222, 248, 16,  160, 168, 3,   169, 144, 55,  201, 69,  41,  147, 137,
            134, 99,  50,  97,  8,   178, 85,  43,  217, 140, 201, 151, 192, 152, 10,  242, 190,
            24,  11,  59,  183, 29,  25,  42,  115, 236, 98,  14,  229, 252, 32,  80,  66,  0,
            162, 17,  136, 72,  6,   67,  5,   45,  242, 224, 10,  193, 102, 71,  50,  6,   17,
            129, 212, 18,  115, 105, 150, 80,  169, 45,  123, 222, 141, 76,  178, 70,  32,  55,
            24,  90,  217, 132, 71,  73,  200, 57,  238, 204, 3,   136, 49,  144, 185, 55,  183,
            190, 20,  137, 52,  246, 47,  113, 232, 158, 69,  35,  49,  145, 208, 129, 193, 56,
            178, 77,  135, 230, 145, 113, 22,  140, 69,  74,  20,  146, 2,   120, 218, 155, 135,
            48,  32,  10,  89,  30,  156, 165, 204, 254, 222, 193, 160, 12,  19,  49,  6,   210,
            59,  11,  70,  62,  4,   31,  15,  64,  196, 2,   157, 98,  33,  58,  1,   104, 32,
            152, 50,  31,  128, 64,  148, 183, 197, 108, 209, 89,  107, 240, 41,  75,  36,  123,
            16,  208, 108, 180, 44,  236, 250, 182, 227, 27,  20,  137, 118, 76,  60,  165, 137,
            221, 92,  94,  78,  215, 31,  235, 245, 230, 183, 242, 229, 30,  214, 251, 251, 195,
            145, 94,  148, 15,  253, 170, 221, 52,  93,  211, 46,  7,   109, 171, 81,  208, 177,
            94,  247, 119, 132, 47,  81,  186, 92,  22,  246, 7,   255, 254, 15,  7,   107, 141,
            171, 197, 191, 156, 123, 162, 135, 187, 198, 227, 131, 113, 219, 80,  159, 1,   4,
            239, 223, 231, 0,   0};

        folderImage = std::unique_ptr<juce::Drawable>(
            loadDrawableFromData(drawableData, sizeof(drawableData)));
    }

    return folderImage.get();
}

const juce::Drawable *UiLookAndFeel::getDefaultDocumentFileImage()
{
    if (documentImage == nullptr)
    {
        static const unsigned char drawableData[] = {
            120, 218, 213, 88,  77,  115, 219, 54,  16,  37,  147, 208, 246, 228, 214, 75,  155,
            246, 164, 123, 29,  12,  176, 216, 197, 199, 49,  105, 218, 94,  156, 153, 78,  114,
            72,  219, 155, 108, 75,  137, 26,  89,  212, 200, 116, 59,  233, 175, 239, 3,   105,
            201, 164, 68,  50,  158, 166, 233, 76,  196, 11,  69,  60,  173, 128, 197, 123, 139,
            183, 124, 241, 234, 217, 155, 103, 207, 207, 126, 204, 242, 7,   171, 233, 213, 44,
            203, 31,  23,  47,  54,  211, 191, 166, 231, 203, 89,  182, 184, 204, 242, 147, 226,
            195, 165, 219, 252, 125, 150, 229, 249, 207, 155, 242, 102, 157, 229, 143, 210, 227,
            199, 197, 101, 121, 113, 115, 53,  91,  85,  89,  85,  174, 207, 102, 243, 42,  203,
            143, 10,  125, 58,  209, 233, 251, 171, 197, 219, 119, 85,  250, 173, 97,  151, 30,
            157, 151, 85,  85,  94,  53,  168, 147, 132, 50,  226, 179, 252, 225, 246, 143, 174,
            179, 44,  63,  254, 101, 90,  189, 203, 242, 34,  5,   127, 84,  172, 77,  118, 93,
            109, 202, 247, 179, 55,  139, 203, 244, 248, 97,  161, 179, 63,  202, 197, 170, 122,
            93,  125, 192, 196, 242, 227, 226, 106, 81,  205, 54,  217, 197, 116, 125, 251, 228,
            168, 56,  191, 169, 170, 108, 85,  174, 126, 159, 109, 202, 55,  139, 213, 229, 98,
            245, 182, 249, 97,  254, 240, 167, 197, 114, 137, 5,   86,  31,  214, 245, 111, 175,
            203, 37,  254, 230, 162, 92,  150, 55,  155, 180, 148, 249, 237, 39,  203, 94,  215,
            127, 58,  10,  213, 245, 39,  203, 234, 249, 102, 249, 87,  47,  203, 63,  129, 204,
            49,  227, 252, 73,  225, 149, 145, 104, 131, 245, 254, 116, 34,  202, 82,  164, 16,
            153, 179, 236, 108, 177, 234, 7,   49,  41,  237, 130, 144, 167, 17,  144, 15,  42,
            104, 239, 93,  12,  35,  32,  99,  68,  9,   187, 24,  125, 7,   244, 77,  23,  36,
            164, 40,  56,  226, 61,  12,  107, 229, 130, 215, 100, 105, 24,  227, 89,  17,  246,
            211, 105, 55,  140, 49,  218, 43,  207, 100, 245, 72,  28,  195, 70,  17,  230, 201,
            118, 8,   243, 164, 139, 233, 95,  88,  23,  52,  152, 162, 54,  104, 48,  217, 237,
            105, 15,  111, 91,  107, 253, 131, 160, 118, 34,  239, 69,  128, 54,  232, 135, 101,
            121, 61,  203, 110, 169, 181, 147, 2,   253, 159, 82,  48,  180, 229, 247, 167, 74,
            193, 41,  141, 188, 35,  93,  241, 116, 18,  148, 113, 214, 120, 207, 113, 47,  19,
            109, 16,  51,  182, 153, 193, 5,   59,  2,   10,  90,  69,  114, 218, 135, 48,  2,
            50,  198, 43,  171, 189, 152, 81,  144, 88,  108, 85,  136, 78,  246, 64,  54,  42,
            163, 35,  69,  30,  3,   121, 82,  38,  98,  81,  98,  70,  64,  70,  139, 34,  111,
            163, 167, 49,  144, 13,  202, 138, 179, 58,  220, 23,  52,  180, 186, 54,  104, 48,
            79,  109, 208, 96,  198, 219, 19,  31,  220, 187, 118, 10,  6,   65,  237, 100, 222,
            139, 5,   109, 80,  191, 30,  236, 151, 162, 135, 147, 142, 30,  68,  105, 182, 58,
            6,   22,  84,  43,  229, 124, 148, 116, 97,  145, 55,  231, 139, 11,  76,  228, 16,
            37,  14,  48,  205, 145, 77,  134, 34,  176, 55,  152, 182, 200, 57,  99,  93,  204,
            144, 145, 253, 65,  97,  229, 132, 72,  104, 63,  62,  71,  21,  140, 54,  186, 41,
            226, 59,  84,  19,  63,  130, 15,  222, 235, 224, 185, 59,  104, 27,  226, 68,  101,
            153, 241, 227, 177, 248, 29,  20,  136, 26,  8,   252, 178, 183, 241, 219, 131, 137,
            160, 209, 107, 109, 92,  79,  124, 16,  211, 184, 104, 93,  77,  130, 110, 124, 2,
            65,  172, 67,  201, 60,  157, 88,  163, 2,   91,  99,  92,  216, 198, 55,  78,  69,
            75,  190, 150, 119, 84,  98,  200, 71,  150, 109, 124, 36,  204, 227, 52,  8,   33,
            229, 223, 68,  167, 173, 167, 131, 248, 137, 212, 226, 141, 19,  233, 160, 154, 248,
            144, 142, 195, 140, 137, 185, 59,  104, 15,  247, 119, 40,  126, 23,  69,  81,  200,
            242, 110, 254, 123, 20,  49,  94,  112, 110, 245, 199, 111, 241, 167, 87,  36,  252,
            101, 138, 132, 149, 22,  22,  38,  65,  134, 29,  182, 139, 24,  230, 192, 31,  144,
            184, 133, 130, 72,  44,  131, 210, 142, 111, 147, 216, 30,  76,  123, 30,  113, 206,
            242, 150, 196, 157, 65,  129, 130, 76,  180, 194, 61,  34,  225, 160, 5,   228, 233,
            160, 118, 34,  137, 26,  202, 115, 212, 29,  108, 72,  134, 243, 223, 90,  114, 226,
            199, 226, 119, 80,  6,   245, 152, 197, 122, 217, 146, 184, 53,  24,  140, 210, 30,
            21,  59,  80,  79,  124, 182, 202, 71,  207, 218, 112, 159, 72,  80,  53,  140, 109,
            68,  2,   191, 227, 217, 210, 78,  36,  94,  137, 88,  231, 82,  157, 8,   176, 61,
            0,   122, 191, 19,  137, 3,   255, 13,  39,  183, 228, 20,  193, 151, 144, 119, 166,
            79,  36,  40,  253, 156, 138, 72,  11,  181, 19,  137, 14,  46,  176, 217, 27,  180,
            135, 251, 219, 31,  255, 235, 61,  148, 165, 96,  72,  122, 118, 23,  229, 81,  52,
            135, 24,  250, 163, 183, 216, 211, 43,  17,  217, 151, 136, 253, 116, 137, 28,  53,
            188, 127, 92,  188, 221, 76,  47,  23,  169, 59,  90,  167, 144, 141, 239, 197, 86,
            104, 141, 189, 60,  157, 80,  84,  142, 140, 4,   31,  154, 241, 122, 105, 132, 41,
            107, 13,  201, 39,  86,  120, 24,  82,  114, 206, 198, 6,   96,  27,  227, 172, 36,
            232, 168, 201, 36,  219, 24,  113, 62,  163, 154, 101, 233, 143, 166, 203, 102, 26,
            141, 206, 174, 179, 252, 89,  161, 39,  243, 249, 197, 121, 186, 38,  233, 246, 146,
            211, 53,  1,   123, 56,  194, 231, 122, 143, 103, 179, 217, 60,  204, 167, 19,  147,
            110, 41,  93,  173, 219, 123, 72,  89,  248, 35,  173, 16,  220, 50,  179, 111, 60,
            181, 24,  88,  103, 156, 235, 7,   78,  248, 14,  4,   119, 78,  162, 93,  60,  112,
            35,  109, 16,  124, 126, 12,  17,  71,  67,  24,  1,   165, 142, 1,   181, 215, 248,
            56,  6,   66,  235, 193, 137, 167, 61,  22,  30,  5,   3,   27,  101, 71,  64,  169,
            25,  112, 216, 2,   63,  22,  169, 110, 43,  18,  200, 140, 129, 208, 160, 88,  44,
            220, 208, 125, 65,  67,  171, 107, 131, 6,   243, 212, 6,   13,  102, 188, 61,  241,
            225, 189, 107, 165, 96,  16,  212, 78,  230, 189, 88,  208, 6,   245, 235, 214, 237,
            235, 150, 62,  167, 110, 155, 106, 170, 53,  133, 192, 117, 193, 20,  84,  78,  74,
            174, 98,  39,  92,  156, 8,   112, 21,  46,  80,  106, 12,  209, 207, 225, 228, 16,
            113, 59,  225, 126, 87,  60,  133, 25,  209, 34,  36,  2,   99,  242, 52,  197, 48,
            30,  75,  244, 247, 212, 238, 246, 182, 173, 221, 185, 78,  215, 127, 167, 221, 162,
            163, 221, 250, 152, 217, 146, 196, 222, 145, 100, 223, 235, 105, 108, 28,  250, 149,
            212, 74,  224, 86,  2,   213, 118, 110, 119, 204, 224, 144, 208, 38,  214, 131, 200,
            14,  214, 223, 120, 189, 230, 53,  1,   193, 70,  133, 154, 131, 56,  223, 16,  229,
            48,  188, 14,  201, 205, 213, 121, 71,  233, 68,  89,  15,  124, 103, 37,  53,  26,
            11,  118, 176, 127, 169, 88,  166, 158, 219, 178, 117, 173, 83,  108, 75,  95,  55,
            68,  186, 193, 53,  246, 146, 206, 127, 6,   63,  53,  78,  58,  228, 204, 155, 224,
            113, 74,  91,  232, 221, 195, 240, 105, 215, 34,  29,  138, 64,  128, 183, 8,   130,
            233, 71,  173, 56,  54,  101, 99,  75,  186, 111, 65,  58,  28,  229, 145, 82,  19,
            152, 12,  99,  180, 81,  130, 131, 75,  234, 229, 220, 247, 53,  231, 154, 79,  205,
            185, 185, 155, 199, 249, 172, 38,  85,  253, 204, 76,  68,  95,  92,  204, 207, 255,
            221, 75,  178, 227, 14,  187, 224, 224, 97,  202, 172, 173, 219, 12,  167, 130, 133,
            9,   54,  135, 245, 92,  176, 29,  134, 165, 110, 139, 141, 18,  16,  223, 29,  188,
            183, 65,  207, 144, 106, 144, 151, 143, 128, 224, 176, 168, 110, 140, 32,  62,  56,
            110, 219, 195, 54,  235, 20,  68,  209, 216, 34,  232, 21,  6,   41,  234, 157, 39,
            211, 201, 107, 160, 230, 66,  225, 56,  153, 9,   101, 21,  37,  237, 150, 204, 14,
            115, 208, 22,  221, 54,  216, 230, 33,  116, 14,  65,  14,  44,  19,  8,   236, 73,
            71,  246, 182, 110, 125, 224, 75,  132, 195, 214, 247, 163, 36,  51,  252, 84,  76,
            124, 37,  212, 100, 88,  62,  183, 179, 76,  67,  217, 218, 242, 244, 229, 116, 243,
            126, 182, 185, 254, 21,  105, 126, 208, 220, 239, 94,  229, 30,  21,  203, 244, 202,
            117, 93,  94,  47,  170, 69,  185, 106, 246, 60,  219, 3,   29,  23,  155, 250, 109,
            237, 29,  170, 72,  175, 109, 119, 129, 127, 235, 9,   92,  20,  85,  185, 254, 72,
            220, 147, 162, 121, 235, 219, 13,  44,  144, 225, 63,  241, 244, 165, 51,  0,   0};

        documentImage = std::unique_ptr<juce::Drawable>(
            loadDrawableFromData(drawableData, sizeof(drawableData)));
    }

    return documentImage.get();
}

//==============================================================================
void UiLookAndFeel::drawLevelMeter(juce::Graphics &g, int width, int height, float level)
{
    g.setColour(juce::Colours::white.withAlpha(0.7f));
    g.fillRoundedRectangle(0.0f, 0.0f, (float)width, (float)height, 3.0f);
    g.setColour(juce::Colours::black.withAlpha(0.2f));
    g.drawRoundedRectangle(1.0f, 1.0f, width - 2.0f, height - 2.0f, 3.0f, 1.0f);

    const int totalBlocks = 7;
    const int numBlocks = juce::roundToInt(totalBlocks * level);
    const float w = (width - 6.0f) / (float)totalBlocks;

    for (int i = 0; i < totalBlocks; ++i)
    {
        if (i >= numBlocks)
            g.setColour(juce::Colours::lightblue.withAlpha(0.6f));
        else
            g.setColour(i < totalBlocks - 1 ? juce::Colours::blue.withAlpha(0.5f)
                                            : juce::Colours::red);

        g.fillRoundedRectangle(3.0f + i * w + w * 0.1f, 3.0f, w * 0.8f, height - 6.0f, w * 0.4f);
    }
}

//==============================================================================
void UiLookAndFeel::drawKeymapChangeButton(juce::Graphics &g, int width, int height,
                                           juce::Button &button, const juce::String &keyDescription)
{
    const juce::Colour textColour(
        button.findColour(0x100ad01 /*KeyMappingEditorComponent::textColourId*/, true));

    if (keyDescription.isNotEmpty())
    {
        if (button.isEnabled())
        {
            const float alpha = button.isDown() ? 0.3f : (button.isOver() ? 0.15f : 0.08f);
            g.fillAll(textColour.withAlpha(alpha));

            g.setOpacity(0.3f);
            drawBevel(g, 0, 0, width, height, 2);
        }

        g.setColour(textColour);
        g.setFont(height * 0.6f);
        g.drawFittedText(keyDescription, 3, 0, width - 6, height, juce::Justification::centred, 1);
    }
    else
    {
        const float thickness = 7.0f;
        const float indent = 22.0f;

        juce::Path p;
        p.addEllipse(0.0f, 0.0f, 100.0f, 100.0f);
        p.addRectangle(indent, 50.0f - thickness, 100.0f - indent * 2.0f, thickness * 2.0f);
        p.addRectangle(50.0f - thickness, indent, thickness * 2.0f, 50.0f - indent - thickness);
        p.addRectangle(50.0f - thickness, 50.0f + thickness, thickness * 2.0f,
                       50.0f - indent - thickness);
        p.setUsingNonZeroWinding(false);

        g.setColour(textColour.withAlpha(button.isDown() ? 0.7f : (button.isOver() ? 0.5f : 0.3f)));
        g.fillPath(p, p.getTransformToScaleToFit(2.0f, 2.0f, width - 4.0f, height - 4.0f, true));
    }

    if (button.hasKeyboardFocus(false))
    {
        g.setColour(textColour.withAlpha(0.4f));
        g.drawRect(0, 0, width, height);
    }
}

//==============================================================================
void UiLookAndFeel::drawBevel(juce::Graphics &g, const int x, const int y, const int width,
                              const int height, const int bevelThickness,
                              const juce::Colour &topLeftColour,
                              const juce::Colour &bottomRightColour, const bool useGradient,
                              const bool sharpEdgeOnOutside)
{
    if (g.clipRegionIntersects(juce::Rectangle<int>(x, y, width, height)))
    {
        juce::LowLevelGraphicsContext &context = g.getInternalContext();
        context.saveState();

        for (int i = bevelThickness; --i >= 0;)
        {
            const float op =
                useGradient ? (sharpEdgeOnOutside ? bevelThickness - i : i) / (float)bevelThickness
                            : 1.0f;

            context.setFill(topLeftColour.withMultipliedAlpha(op));
            context.fillRect(juce::Rectangle<int>(x + i, y + i, width - i * 2, 1), false);
            context.setFill(topLeftColour.withMultipliedAlpha(op * 0.75f));
            context.fillRect(juce::Rectangle<int>(x + i, y + i + 1, 1, height - i * 2 - 2), false);
            context.setFill(bottomRightColour.withMultipliedAlpha(op));
            context.fillRect(juce::Rectangle<int>(x + i, y + height - i - 1, width - i * 2, 1),
                             false);
            context.setFill(bottomRightColour.withMultipliedAlpha(op * 0.75f));
            context.fillRect(
                juce::Rectangle<int>(x + width - i - 1, y + i + 1, 1, height - i * 2 - 2), false);
        }

        context.restoreState();
    }
}

//==============================================================================
void UiLookAndFeel::drawShinyButtonShape(juce::Graphics &g, float x, float y, float w, float h,
                                         float maxCornerSize, const juce::Colour &baseColour,
                                         const float strokeWidth, const bool flatOnLeft,
                                         const bool flatOnRight, const bool flatOnTop,
                                         const bool flatOnBottom) noexcept
{
    if (w <= strokeWidth * 1.1f || h <= strokeWidth * 1.1f)
        return;

    const float cs = juce::jmin(maxCornerSize, w * 0.5f, h * 0.5f);

    juce::Path outline;
    outline.addRoundedRectangle(x, y, w, h, cs, cs, !(flatOnLeft || flatOnTop),
                                !(flatOnRight || flatOnTop), !(flatOnLeft || flatOnBottom),
                                !(flatOnRight || flatOnBottom));

    juce::ColourGradient cg(baseColour, 0.0f, y, baseColour.overlaidWith(juce::Colour(0x070000ff)),
                            0.0f, y + h, false);

    cg.addColour(0.5, baseColour.overlaidWith(juce::Colour(0x33ffffff)));
    cg.addColour(0.51, baseColour.overlaidWith(juce::Colour(0x110000ff)));

    g.setGradientFill(cg);
    g.fillPath(outline);

    g.setColour(juce::Colour(0x80000000));
    g.strokePath(outline, juce::PathStrokeType(strokeWidth));
}

//==============================================================================
void UiLookAndFeel::drawGlassSphere(juce::Graphics &g, const float x, const float y,
                                    const float diameter, const juce::Colour &colour,
                                    const float outlineThickness) noexcept
{
    if (diameter <= outlineThickness)
        return;

    juce::Path p;
    p.addEllipse(x, y, diameter, diameter);

    {
        g.setColour(colour);
        g.fillPath(p);
    }

    // g.setGradientFill (ColourGradient (Colours::white, 0, y + diameter * 0.06f,
    // Colours::transparentWhite, 0, y + diameter * 0.3f, false));
    // g.fillEllipse (x + diameter * 0.2f, y + diameter * 0.05f, diameter * 0.6f, diameter * 0.4f);

    juce::ColourGradient cg(
        juce::Colours::transparentBlack, x + diameter * 0.5f, y + diameter * 0.5f,
        juce::Colours::black.withAlpha(0.5f * outlineThickness * colour.getFloatAlpha()), x,
        y + diameter * 0.5f, true);

    // cg.addColour (0.7, Colours::transparentBlack);
    // cg.addColour (0.8, Colours::black.withAlpha (0.1f * outlineThickness));

    // g.setGradientFill (cg);
    // g.fillPath (p);

    g.setColour(juce::Colours::black.withAlpha(0.5f * colour.getFloatAlpha()));
    g.drawEllipse(x, y, diameter, diameter, outlineThickness);
}

//==============================================================================
void UiLookAndFeel::drawGlassPointer(juce::Graphics &g, const float x, const float y,
                                     const float diameter, const juce::Colour &colour,
                                     const float outlineThickness, const int direction) noexcept
{
    if (diameter <= outlineThickness)
        return;

    juce::Path p;
    p.startNewSubPath(x + diameter * 0.5f, y);
    p.lineTo(x + diameter, y + diameter * 0.6f);
    p.lineTo(x + diameter, y + diameter);
    p.lineTo(x, y + diameter);
    p.lineTo(x, y + diameter * 0.6f);
    p.closeSubPath();

    p.applyTransform(
        juce::AffineTransform::rotation(direction * (juce::MathConstants<float>::pi * 0.5f),
                                        x + diameter * 0.5f, y + diameter * 0.5f));

    {
        juce::ColourGradient cg(juce::Colours::white.overlaidWith(colour.withMultipliedAlpha(0.3f)),
                                0, y,
                                juce::Colours::white.overlaidWith(colour.withMultipliedAlpha(0.3f)),
                                0, y + diameter, false);

        cg.addColour(0.4, juce::Colours::white.overlaidWith(colour));

        g.setGradientFill(cg);
        g.fillPath(p);
    }

    juce::ColourGradient cg(
        juce::Colours::transparentBlack, x + diameter * 0.5f, y + diameter * 0.5f,
        juce::Colours::black.withAlpha(0.5f * outlineThickness * colour.getFloatAlpha()),
        x - diameter * 0.2f, y + diameter * 0.5f, true);

    cg.addColour(0.5, juce::Colours::transparentBlack);
    cg.addColour(0.7, juce::Colours::black.withAlpha(0.07f * outlineThickness));

    g.setGradientFill(cg);
    g.fillPath(p);

    g.setColour(juce::Colours::black.withAlpha(0.5f * colour.getFloatAlpha()));
    g.strokePath(p, juce::PathStrokeType(outlineThickness));
}

//==============================================================================
void UiLookAndFeel::drawGlassLozenge(juce::Graphics &g, const float x, const float y,
                                     const float width, const float height,
                                     const juce::Colour &colour, const float outlineThickness,
                                     const float cornerSize, const bool flatOnLeft,
                                     const bool flatOnRight, const bool flatOnTop,
                                     const bool flatOnBottom) noexcept
{
    if (width <= outlineThickness || height <= outlineThickness)
        return;

    juce::Path outline;
    outline.addRectangle(x, y, width, height);

    {
        g.setColour(colour);
        g.fillPath(outline);
    }
}
