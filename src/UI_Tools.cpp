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

#include "UI_Tools.h"

#include "UiSettings.h"

#include "CoreCopy.h"

#include "UiEditorClipboard.h"
#include "UiMainWindow.h"

#include "PluginProcessor.h"

#include "UIHtmlView.h"
#include "BinaryData.h"

const juce::Image &UITool::get_curser_image() { return _curser_image; }
void UITool::mouseDrag(const juce::MouseEvent &e_)
{
    if (!(e_.getDistanceFromDragStart() > 25 || e_.getDistanceFromDragStart() < -25))
        return;

    is_draged = true;
    startDragging("", this, get_curser_image(), true);
}
void UITool::mouseUp(const juce::MouseEvent &)
{
    if (!is_draged)
        clicked();

    is_draged = false;
}
void UITool::clicked()
{
    if (!_app_instance_store->editor_config.manual_editor)
        _app_instance_store->editor_config.manual_editor =
            std::make_unique<UIHtmlView>(_app_instance_store);

    _app_instance_store->editor_config.manual_editor->try_open_question_mark();
}
UITool::UITool(const juce::String &name_) : juce::ImageButton(name_), is_draged(false) {}
void UIRubber::paint(juce::Graphics &g_)
{
    drawable->drawWithin(g_,
                         juce::Rectangle<float>(proportionOfWidth(0.1), proportionOfHeight(0.1),
                                                proportionOfWidth(0.8), proportionOfHeight(0.8)),
                         juce::RectanglePlacement::centred, 1.000f);
}

UIRubber::UIRubber(const juce::String &) : UITool("TlR")
{
    drawable = juce::DrawableImage::createFromImageData(BinaryData::rubber_svg,
                                                        BinaryData::rubber_svgSize);
}
void UIQuestion::paint(juce::Graphics &g_)
{
    drawable->drawWithin(g_,
                         juce::Rectangle<float>(proportionOfWidth(0.1), proportionOfHeight(0.1),
                                                proportionOfWidth(0.8), proportionOfHeight(0.8)),
                         juce::RectanglePlacement::centred, 1.000f);
}

UIQuestion::UIQuestion(const juce::String &) : UITool("TlQ")
{
    drawable = juce::DrawableImage::createFromImageData(BinaryData::question_svg,
                                                        BinaryData::question_svgSize);
}
BarCopyClipboard::BarCopyClipboard(std::uint8_t id_)
    : UIBarClipboardSettings(id_), stored_bar(new Bar(SUM_BARS + 99 + id_))
{
}
BarCopyClipboard::~BarCopyClipboard() { delete stored_bar; }
void UIClipboard::paint(juce::Graphics &g_)
{
    drawable->drawWithin(g_,
                         juce::Rectangle<float>(proportionOfWidth(0.1), proportionOfHeight(0.1),
                                                proportionOfWidth(0.8), proportionOfHeight(0.8)),
                         juce::RectanglePlacement::centred, 1.000f);
}
void UIClipboard::mouseDrag(const juce::MouseEvent &e_)
{
    if (is_draged)
        return;

    if (!(e_.getDistanceFromDragStart() > 25 || e_.getDistanceFromDragStart() < -25))
        return;

    is_draged = true;

    BarCopySourceData *source = new BarCopySourceData(_bar_copy_clipboard.stored_bar, false);

    source->is_copy_steps = _bar_copy_clipboard.is_copy_steps;
    source->is_copy_string_octave = _bar_copy_clipboard.is_copy_string_octave;
    source->is_copy_step_duration = _bar_copy_clipboard.is_copy_step_duration;
    source->is_copy_step_velocity = _bar_copy_clipboard.is_copy_step_velocity;
    source->is_copy_bar_solo = _bar_copy_clipboard.is_copy_bar_solo;
    source->is_copy_bar_groups = _bar_copy_clipboard.is_copy_bar_groups;
    source->is_copy_layer_1 = _bar_copy_clipboard.is_copy_layer_1;
    source->is_copy_layer_2 = _bar_copy_clipboard.is_copy_layer_2;
    source->is_copy_layer_3 = _bar_copy_clipboard.is_copy_layer_3;
    source->is_copy_layer_4 = _bar_copy_clipboard.is_copy_layer_4;
    source->is_copy_layer_5 = _bar_copy_clipboard.is_copy_layer_5;
    source->is_copy_layer_6 = _bar_copy_clipboard.is_copy_layer_6;
    source->is_copy_layer_7 = _bar_copy_clipboard.is_copy_layer_7;

    _curser_image =
        this->createComponentSnapshot(this->getLocalBounds()).convertedToFormat(juce::Image::ARGB);

    drag_source = std::unique_ptr<BarCopySourceData>(source);
    startDragging(BAR_CLIPBOARD_DRAG_N_DROP_IDENT, source, _curser_image, true);
}
void UIClipboard::clicked()
{
    if (!is_draged)
    {
        if (!_app_instance_store->editor_config.clipboard_editor)
            _app_instance_store->editor_config.clipboard_editor =
                std::make_unique<UiEditorClipboard>(_app_instance_store, id);
        else
            _app_instance_store->editor_config.clipboard_editor = nullptr;
    }
}
bool UIClipboard::isInterestedInDragSource(const SourceDetails &dragSourceDetails_)
{
    if (dragSourceDetails_.description.toString().compare(BAR_DRAG_N_DROP_IDENT) == 0)
        return true;
    else if (dragSourceDetails_.sourceComponent.get()->getName().compare("TlQ") == 0)
        return true;

    return false;
}
void UIClipboard::itemDropped(const SourceDetails &dragSourceDetails_)
{
    if (dragSourceDetails_.description.toString().compare(BAR_DRAG_N_DROP_IDENT) == 0)
    {
        BarCopySourceData *source =
            reinterpret_cast<BarCopySourceData *>(dragSourceDetails_.sourceComponent.get());

        Bar &target_bar = *_bar_copy_clipboard.stored_bar;
        const Bar &source_bar = *source->copy_source_bar;

        target_bar = source_bar;

        _bar_copy_clipboard.stored_bar_source_ident =
            juce::String("Snapshot of Bar ").operator+=(source_bar.id + 1) +=
            juce::String(" - click to edit");
    }
    else if (dragSourceDetails_.sourceComponent.get()->getName().compare("TlQ") == 0)
    {
        if (_app_instance_store->editor)
        {
            if (!_app_instance_store->editor_config.manual_editor)
                _app_instance_store->editor_config.manual_editor =
                    std::make_unique<UIHtmlView>(_app_instance_store);

            _app_instance_store->editor_config.manual_editor->try_open_url(
                MANUAL_URL + "experts/snapshots-and-the-clipboard");
        }
    }
}
void UIClipboard::dragOperationEnded(const juce::DragAndDropTarget::SourceDetails &d)
{
    drag_source = nullptr;
    is_draged = false;
    juce::DragAndDropContainer::dragOperationEnded(d);
}

UIClipboard::UIClipboard(AppInstanceStore *app_instance_store_,
                         GstepAudioProcessorEditor *main_window_, std::uint8_t id_)
    : UITool(""), drag_source(nullptr),

      _app_instance_store(app_instance_store_), _main_window(main_window_), id(id_),
      _bar_copy_clipboard(*_app_instance_store->bar_copy_clipboards.getUnchecked(id)),
      _editor(nullptr)
{
    if (id_ == 0)
        drawable = juce::DrawableImage::createFromImageData(BinaryData::clipboard_1_svg,
                                                            BinaryData::clipboard_1_svgSize);
    else if (id_ == 1)
        drawable = juce::DrawableImage::createFromImageData(BinaryData::clipboard_2_svg,
                                                            BinaryData::clipboard_2_svgSize);
    else if (id_ == 2)
        drawable = juce::DrawableImage::createFromImageData(BinaryData::clipboard_3_svg,
                                                            BinaryData::clipboard_3_svgSize);
    else if (id_ == 3)
        drawable = juce::DrawableImage::createFromImageData(BinaryData::clipboard_4_svg,
                                                            BinaryData::clipboard_4_svgSize);
}
