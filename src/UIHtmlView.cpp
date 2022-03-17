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
#include "UiLookAndFeel.h"
#include "UiSettings.h"

// TODO FUTURE UPDATED (after 2.1)
// add a introduction date
// add date modifyed // mark red if it is out of date // update request
// CLOSE IF SELECTED //  DOUBLE CLICK

// TODO news notification für DEMO versionen : SALES ETC

// TODO default mail and support if nothing is selected

//[/Headers]

#include "UIHtmlView.h"

//[MiscUserDefs] You can add your own user definitions and misc code here...
#define CHECK_THREAD_EXIT(return_value)                                                            \
    if (Thread::getCurrentThread())                                                                \
        if (Thread::getCurrentThread()->threadShouldExit())                                        \
    return_value

class HTMLPArser
{
    UIHtmlView *const _view;
    const bool _show_content;
    bool _has_live_only_content;

    // TAGS WITH START AND END
    struct TagPair
    {
        const String start;
        const String end;

        const bool is_closed_tag;

        TagPair(String start_, String end_, bool is_closed_tag_)
            : start(start_), end(end_), is_closed_tag(is_closed_tag_)
        {
        }
    };

    TagPair _tag_h;
    TagPair _tag_p;
    TagPair _tag_li;
    TagPair _tag_img;
    TagPair _tag_a;

    static void clean_conten_data(String &data_)
    {
        data_ = data_.fromFirstOccurrenceOf("<!-- __CONTENT__ -->", false, true);
        data_ = data_.upToFirstOccurrenceOf("<!-- __CONTENTEO__ -->", false, true);
        TagPair exclude("<!-- EXCLUDE -->", "<!-- EXCLUDEEO -->", false);
        remove_begin_tag(exclude, data_);

        clean_comment_blocks(data_);
        clean(data_);
        replace_simple_tags(data_);

        replace_link_tags(data_);

        data_ = data_.replace("<ul>", "", true);
        data_ = data_.replace("</ul>", "", true);

        remove_empty_tags(data_);
    }
    static void clean_nav_data(String &data_)
    {
        data_ = data_.fromFirstOccurrenceOf("<!-- __NAV__ -->", false, true);
        data_ = data_.upToFirstOccurrenceOf("<!-- __NAVEO__ -->", false, true);

        TagPair exclude("<!-- EXCLUDE -->", "<!-- EXCLUDEEO -->", false);
        remove_begin_tag(exclude, data_);

        clean(data_);

        replace_simple_tags(data_);
        remove_empty_tags(data_);
    }
    static void clean_comment_blocks(String &data_)
    {
        TagPair comments("<!--", "-->", false);
        remove_begin_tag(comments, data_);
    }
    static void clean(String &data_)
    {
        TagPair script("<script", "</script>", false);
        remove_begin_tag(script, data_);

        TagPair iframe("<iframe", "</iframe>", false);
        remove_begin_tag(iframe, data_);

        TagPair font("<font", ">", false);
        remove_begin_tag(font, data_);

        TagPair span("<span", ">", false);
        remove_begin_tag(span, data_);

        TagPair div("<div", ">", false);
        remove_begin_tag(div, data_);
    }
    static void replace_simple_tags(String &string_)
    {
        string_ = string_.replace("<p><br /></p>", "", true);
        string_ = string_.replace("<br />", "\n", true);
        string_ = string_.replace("<br/>", "\n", true);
        string_ = string_.replace("<br>", "\n", true);
        string_ = string_.replace("<strong>", "", true);
        string_ = string_.replace("</strong>", "", true);
        string_ = string_.replace("<code>", "<li>", true);
        string_ = string_.replace("</code>", "</li>", true);
        string_ = string_.replace("<pre>", "", true);
        string_ = string_.replace("</pre>", "", true);
        string_ = string_.replace("<u>", "", true);
        string_ = string_.replace("</u>", "", true);
        string_ = string_.replace("<hr>", "\n", true);
        string_ = string_.replace("<hr/>", "\n", true);
        string_ = string_.replace("<ol>", "<ul>", true);
        string_ = string_.replace("</ol>", "</ul>", true);
        string_ = string_.replace("</font>", "", true);
        string_ = string_.replace("</span>", "", true);
        // string_ = string_.replace( "</div>", "", true );

        // UTF
        string_ = string_.replace("&#8221;", "\"", true);
        string_ = string_.replace("&#8220;", "\"", true);
        string_ = string_.replace("&#8217;", "'", true);
        string_ = string_.replace("&amp;", "&", true);
        string_ = string_.replace("&#8230;", "...", true);

        string_ = string_.replace("&nbsp;", " ", true);
        string_ = string_.replace("->", "⇒", true);
        string_ = string_.replace("<-", "⇐", true);
        string_ = string_.replace(">>", "⇒⇒", true);
        string_ = string_.replace("<<", "⇐⇐", true);
        string_ = string_.replace("&lt;", "⇐", true);

        // REMOVE TO MUCH SPACES TO THE NEXT
        string_ = string_.replace("</p>\n", "</p>", true);
        string_ = string_.replace("\n\n\n", "\n\n", true);
        string_ = string_.replace("\n\n\n\n", "\n\n", true);
    }
    static void replace_trailing_error_tags(String &string_)
    {
        if (string_.substring(0, 4) == "</p>")
            string_ = string_.fromFirstOccurrenceOf("</p>", false, true);
        if (string_.substring(0, 5) == "</li>")
            string_ = string_.fromFirstOccurrenceOf("</li>", false, true);
        if (string_.substring(0, 5) == "</ul>")
            string_ = string_.fromFirstOccurrenceOf("</ul>", false, true);
        if (string_.substring(0, 5) == "</h1>")
            string_ = string_.fromFirstOccurrenceOf("</h1>", false, true);
        if (string_.substring(0, 5) == "</h2>")
            string_ = string_.fromFirstOccurrenceOf("</h2>", false, true);
        if (string_.substring(0, 5) == "</h3>")
            string_ = string_.fromFirstOccurrenceOf("</h3>", false, true);
        if (string_.substring(0, 5) == "</h4>")
            string_ = string_.fromFirstOccurrenceOf("</h4>", false, true);
        if (string_.substring(0, 5) == "</h5>")
            string_ = string_.fromFirstOccurrenceOf("</h5>", false, true);
        if (string_.substring(0, 5) == "</h6>")
            string_ = string_.fromFirstOccurrenceOf("</h6>", false, true);
    }
    static void replace_link_tags(String &data_)
    {
        String result;

        bool is_a_link_inside = data_.contains("<a");
        while (is_a_link_inside)
        {
            result += data_.upToFirstOccurrenceOf("<a", false, false);   // string until <a
            data_ = data_.fromFirstOccurrenceOf("<a", false, false);     // rest data from <a...
            data_ = data_.fromFirstOccurrenceOf(">", false, false);      // remove ... >
            result += data_.upToFirstOccurrenceOf("</a>", false, false); // add >text< to result
            data_ = data_.fromFirstOccurrenceOf("</a>", false, false);

            is_a_link_inside = data_.contains("<a");
        }

        result += data_;
        data_ = result;
    }
    static void remove_begin_tag(TagPair &tag, String &data_)
    {
        String result;

        bool is_a_tag_inside = data_.contains(tag.start);
        while (is_a_tag_inside)
        {
            result += data_.upToFirstOccurrenceOf(tag.start, false, false);
            data_ = data_.fromFirstOccurrenceOf(tag.start, false, false);
            data_ = data_.fromFirstOccurrenceOf(tag.end, false, false);

            // OUT( "REMOVE BEGIN TAG");

            is_a_tag_inside = data_.contains(tag.start);
        }

        result += data_;
        data_ = result;
    }
    static void remove_empty_tags(String &data_)
    {
        data_ = data_.replace("<p></p>", "", true);
        data_ = data_.replace("<ul></ul>", "", true);
        data_ = data_.replace("<li></li>", "", true);
        data_ = data_.replace("<h1></h1>", "", true);
        data_ = data_.replace("<h2></h2>", "", true);
        data_ = data_.replace("<h3></h3>", "", true);
        data_ = data_.replace("<h4></h4>", "", true);
        data_ = data_.replace("<h5></h5>", "", true);
        data_ = data_.replace("<h6></h6>", "", true);
    }

    enum TAGS
    {
        IS_H_1 = 1,
        IS_H_6 = 6,
        IS_P,
        IS_LI,
        IS_IMG,

        IS_UNKNOWN,

        IS_END_OF
    };

    // EXCLUDE THE LINE e.g. -> <p> ... </p> and return true if this was a success for the tags
    static bool get_line_for(String &data_, const TagPair &tage_pair_, String &result_)
    {
        // check if this is the tag we are looking for
        if (data_.substring(0, tage_pair_.start.length()) == tage_pair_.start)
        {
            result_ = data_.upToFirstOccurrenceOf(tage_pair_.end, false, false);     // without </p>
            result_ = result_.fromFirstOccurrenceOf(tage_pair_.start, false, false); // remove <p
            if (!tage_pair_.is_closed_tag)
                result_ = result_.fromFirstOccurrenceOf(">", false, true); // remove >   (<p ..... >
            data_ = data_.fromFirstOccurrenceOf(result_, false, false);

            return true;
        }

        return false;
    }

    TAGS get_next_parent_tag_line(String &data_, String &result_)
    {
        String tmp;
        while (true)
        {
            data_ = data_.fromFirstOccurrenceOf("<", true, true);
            if (get_line_for(data_, _tag_p, result_))
                return IS_P;
            if (get_line_for(data_, _tag_li, result_))
                return IS_LI;
            else if (get_line_for(data_, _tag_img, result_))
                return IS_IMG;
            else
                for (int i = 1; i != 7; ++i)
                {
                    TagPair h_tag(_tag_h.start + String(i), _tag_h.end + String(i) + String(">"),
                                  false);
                    if (get_line_for(data_, h_tag, result_))
                        return static_cast<TAGS>(i);
                }

            tmp = data_.fromFirstOccurrenceOf("<", false, true);

            if (tmp == "")
                return IS_END_OF;

            data_ = tmp;
        }
    }

    void parse_p(String &data_, int size_, int white_spaces_)
    {
        while (data_ != "")
        {
            // parse until "<"
            if (data_.contains("<"))
            {
                String tmp(data_.upToFirstOccurrenceOf("<", false, false));
                if (tmp != "")
                {
                    // OUT("::: PARSE SUB TEXT UNTIL '<' :: " << tmp );
                    backward_replacement(tmp);
                    _view->add_text_part(tmp, size_, white_spaces_, _show_content);
                }

                data_ = data_.fromFirstOccurrenceOf("<", true, false);
                // OUT("NEW DECODE");
                decode_content(data_);
            }
            else if (data_.contains(">"))
            {
                // OUT("::: ERROR: '>' left" << data_);
                backward_replacement(data_);
                _view->add_text_part(data_, size_, white_spaces_, _show_content);
                data_ = "";
            }
            else
            {
                // OUT("::: PARSE SUB END " << data_ << " XXXXXXXXX" );
                backward_replacement(data_);
                _view->add_text_part(data_, size_, white_spaces_, _show_content);
                data_ = "";
            }
        }
    }

    // image strings are closes and can be put away
    void parse_image(String &data_)
    {
        // exclude the link
        data_ = data_.fromFirstOccurrenceOf("src=\"", false, false);
        data_ = data_.upToFirstOccurrenceOf("\"", false, false);

        // OUT("PARSE IMAGE :: "<< data_);
        _view->add_image(data_, _show_content);
    }

    void decode_content(String &data_)
    {
        // OUT( "DECODE CONTENT ::: " << data_ << " ::: CONTENT END");
        while (data_.length())
        {
            String result;
            TAGS tag = get_next_parent_tag_line(data_, result);

            if (tag <= IS_H_6)
                parse_p(result, static_cast<int>(tag), 0);
            else
            {
                switch (tag)
                {
                case IS_P:
                    parse_p(result, 7, 3);
                    break;
                case IS_LI:
                    parse_p(result = String("- ") + result, 7, 10);
                    break;
                case IS_IMG:
                    parse_image(result);
                    break;
                case IS_END_OF:
                    return;
                default:
                    break;
                }
            }

            replace_trailing_error_tags(data_);
            replace_trailing_error_tags(data_); // security
        }
    }

    void decode_nav(String &data_, bool download_complete_nav_content_)
    {
        // OUT( "DECODE NAV ::: " << data_ << " ::: NAV END");
        int ul_deepnes = -1;
        while (data_.length())
        {
            URL url;
            String name;

            String tmp(data_.upToFirstOccurrenceOf("href=\"", false, false));

            // set the deepnes
            if (tmp.contains("<ul>"))
                ul_deepnes++;
            if (tmp.contains("</ul>"))
                ul_deepnes--;

            // OUT( "DEEPNESS " << ul_deepnes );

            // get the link and name
            data_ = data_.fromFirstOccurrenceOf("href=\"", false, false);
            url = URL(data_.upToFirstOccurrenceOf("\"", false, false));
            data_ = data_.fromFirstOccurrenceOf(">", false, false);
            name = data_.upToFirstOccurrenceOf("</a>", false, false);
            data_ = data_.fromFirstOccurrenceOf("</a>", false, false);

            if (url.isWellFormed())
            {
                _view->add_nav_link(name, url, ul_deepnes, download_complete_nav_content_);

                if (download_complete_nav_content_)
                    _view->open_url(url, false, false);
            }
        }
    }

    static void backward_replacement(String &data_)
    {
        data_ = data_.replace("⇒⇒", ">>", true);
        data_ = data_.replace("⇐⇐", "<<", true);
        data_ = data_.replace("⇒", "->", true);
        data_ = data_.replace("⇐", "<-", true);
    }

  public:
    HTMLPArser(String &data_, UIHtmlView *const view_, bool parse_nav_,
               bool download_complete_nav_content_, bool show_content_)
        : _view(view_), _show_content(show_content_), _has_live_only_content(false),

          _tag_h("<h", "</h", false), // note: uncomplete tag, will be done in a loop
          _tag_p("<p", "</p>", false), _tag_li("<li", "</li>", false), _tag_img("<img", "/>", true),
          _tag_a("<a href", "</a>", false)
    {
        if (parse_nav_ || download_complete_nav_content_)
        {
            String nav_data = data_;
            clean_nav_data(nav_data);
            decode_nav(nav_data, download_complete_nav_content_);
            backward_replacement(nav_data);
        }
        {
            _has_live_only_content = data_.contains("<!-- LIVEONLY -->");
            if (_has_live_only_content)
            {
                TagPair liveonly("<!-- LIVEONLY -->", "<!-- LIVEONLYEO -->", false);
                remove_begin_tag(liveonly, data_);
            }

            clean_conten_data(data_);

            if (_has_live_only_content)
                _view->add_text_part(
                    "This part has video or similar content which is only available in a "
                    "webbrowser. Click \"OPEN ONLINE VERSION\" at the right-bottom to open this "
                    "part in your default webbrowser.\n\n",
                    6, 0, _show_content, Colour(0xff919191));

            decode_content(data_);
            backward_replacement(data_);
        }
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HTMLPArser)
};

class NavItem : public TreeViewItem
{
    UIHtmlView *const _html_view;

    String const _name;
    URL const _url;

    ScopedPointer<Label> _label;

    String getUniqueName() const override { return _url.toString(false); }

    bool mightContainSubItems() override { return getNumSubItems(); }

    bool canBeSelected() const override
    {
        return !getNumSubItems() && _html_view->can_something_selected;
    }

    int getItemHeight() const override
    {
        float heigh_prop = 1.f / 600 * _html_view->getHeight();
        return heigh_prop * 25;
    }
    int getItemWidth() const override
    {
        float width = 1.f / 900 * _html_view->getWidth();
        return width * 200;
    }

    void click()
    {
        if (mightContainSubItems())
            setOpen(true);

        if (getNumSubItems())
        {
            NavItem *child = dynamic_cast<NavItem *>(getSubItem(0));
            if (child)
                child->click();
        }
        else
        {
            setSelected(true, true);
            _html_view->open_url(_url);
        }
    }

    void itemClicked(const MouseEvent &e) override { setSelected(true, true); }

    void itemSelectionChanged(bool isNowSelected) override
    {
        _label->setColour(Label::textColourId,
                          isNowSelected
                              ? Colours::yellow
                              : Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
        if (isNowSelected)
            click();
    }

    virtual void paintItem(Graphics &g, int width, int height) override
    {
        _label->setBounds(0, 0, width, height);
    }

    std::unique_ptr<Component> createItemComponent() override
    {
        float heigh_prop = 1.f / 600 * _html_view->getHeight();
        float width_prop = 1.f / 900 * _html_view->getWidth();

        auto comp = std::make_unique<Component>();
        comp->setBounds(0, 0, width_prop * 200, heigh_prop * 25);
        _label->setBounds(0, 0, width_prop * 200, heigh_prop * 25);
        comp->setVisible(true);
        comp->setInterceptsMouseClicks(false, false);
        comp->addChildComponent(_label);
        return comp;
    }

  public:
    NavItem(UIHtmlView *const html_view_, const String &name_, const URL &url_)
        : _html_view(html_view_), _name(name_), _url(url_), _label(nullptr)
    {
        float heigh_prop = 1.f / 600 * _html_view->getHeight();
        float width_prop = 1.f / 900 * _html_view->getWidth();

        _label = new Label();
        _label->setText(_name, dontSendNotification);
        _label->setVisible(true);
        _label->setBounds(0, 0, width_prop * 200, heigh_prop * 25);
        _label->setInterceptsMouseClicks(false, false);

        _html_view->items.add(this);
    }

    ~NavItem() { _html_view->items.removeFirstMatchingValue(this); }

    const URL &get_url() const { return _url; }
    const String &get_title() const { return _name; }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NavItem)
};

bool UIHtmlView::try_open_url(const URL &source_)
{
    if (pending_download)
        return false;

    open_url(source_);
    select_item_with_url(source_);
    return true;
}
bool UIHtmlView::try_open_question_mark()
{
    if (pending_download)
        return false;

    open_question_mark_content();
    return true;
}

#include "FileIO.h"
void UIHtmlView::handleAsyncUpdate()
{
    open_url(load_async_url, false, true);
    block_views(true);
    select_item_with_url(load_async_url);
}

bool UIHtmlView::open_url(const URL &source_, bool and_download_complete_nav_content_,
                          bool show_content_)
{
    CHECK_THREAD_EXIT({
        OUT("open_url");
        return false;
    });

    if (!get_manual_folder().exists() && !and_download_complete_nav_content_)
    {
        open_question_mark_content();
        return true;
    }

    ScopedLock locked(lock);
    can_something_selected = false;
    current_url = source_;

    if (show_content_)
    {
        MessageManagerLock lock;

        current_height = 0;
        content_wrapper->removeAllChildren();
        content_wrapper->setSize(content_wrapper->getWidth(), current_height);

        editors.clear(true);
        images.clear(true);
    }

    String data;

    // CHECK IF IT ALREAD EXIST AND USE CACHE OR CREATE CACHE
    // IGNORE ANNOUNCEMENTS
    bool reload_from_server = false;
    if (current_url.toString(false).fromFirstOccurrenceOf(".com/", false, false) == "" ||
        current_url.toString(false).fromFirstOccurrenceOf(".com/", false, false) ==
            "latest-downloads")
        reload_from_server = true;

    String cache_path = current_url.toString(false);
    cache_path = cache_path.fromFirstOccurrenceOf(".com/", false, true);
    current_cache_folder = get_manual_folder().getChildFile(cache_path);
    current_cache_folder.createDirectory();
    File current_cache(current_cache_folder.getChildFile("cache"));
    if (reload_from_server)
    {
        URL online_test(MANUAL_URL + "is-online");
        if (online_test.readEntireTextStream().contains("<!-- IS-ONLINE -->"))
            current_cache.deleteFile();
    }

    bool valid_data_or_file = false;
    if (current_cache.existsAsFile())
    {
        data = current_cache.loadFileAsString();
        valid_data_or_file = data.contains("<!-- B-STEP-USER-MANUAL -->");
    }

    if (!valid_data_or_file)
    {
        data = current_url.readEntireTextStream(false);
        valid_data_or_file = data.contains("<!-- B-STEP-USER-MANUAL -->");
        if (valid_data_or_file)
            current_cache.replaceWithText(data);
    }

    bool return_value = false;
    if (valid_data_or_file)
    {
        data = data.fromFirstOccurrenceOf("<!-- B-STEP-USER-MANUAL -->", false, true);
        if (data != "")
            HTMLPArser(data, this, !nav_is_parsed, and_download_complete_nav_content_,
                       show_content_);

        nav_is_parsed = true;
        return_value = true;
    }
    else
    {
        add_text_part("Error, can not download: " +
                          source_.toString(false).fromLastOccurrenceOf("/", false, false),
                      6, 0, true, Colour(0xffff0000));
        add_text_part("Please try to re-download later or download the offline version.", 4, 10,
                      true, Colour(0xffff0000));

        return_value = false;
    }

    can_something_selected = true;

    if (get_manual_folder().exists())
        update->setButtonText(TRANS("RE-DOWNLOAD COMPLETE MANUAL"));

    return return_value;
}

bool UIHtmlView::open_question_mark_content(const URL &request_for_, bool force_redownload_)
{
    if (!get_manual_folder().exists() || force_redownload_)
    {
        if (!force_redownload_)
        {
            clear_all_views();

            add_text_part("B-STEP MANUAL", 1, 0, true, Colours::yellowgreen);
            String message("You can download the embedded manual by clicking \"DOWNLOAD COMPLETE "
                           "MANUAL\" at the left-bottom of this window.");

            message += "\n";
            message += "\n";
            message += "This will create a local copy of the online manual. ";
            message += "Need less than 10 megabyte on your disk.";
            message += "\n";
            message += "\n";
            message += "To have the latest version of the manual you can re-download the manual at "
                       "any time you like.";
            message += "\n";
            message += "\n";
            add_text_part(message, 5, 10, true, Colours::white);

            message = "";
            message +=
                "If your computer is never online you can download the manual on the forum: ";
            add_text_part(message, 5, 10, true, Colours::skyblue);
            message = "";
            message += "http://forum.monoplugs.com/offline";
            add_text_part(message, 5, 10, true, Colours::skyblue, true);
        }

        String ok_answer =
            !force_redownload_ ? "YES, DOWNLOAD NOW (recommended)." : "YES, RE-DOWNLOAD NOW.";
        if (AlertWindow::showOkCancelBox(AlertWindow::QuestionIcon, "DOWNLOAD THE MANUAL?",
                                         "Would you like to download the complete manual now? It "
                                         "need less than 10 megabyte on your disk.",
                                         ok_answer, "NO, NOT NOW", this))
        {
            if (force_redownload_)
                get_manual_folder().deleteRecursively();
            get_manual_folder().createDirectory();

            bool is_online = false;
            URL online_test(MANUAL_URL + "is-online");
            if (online_test.readEntireTextStream().contains("<!-- IS-ONLINE -->"))
                is_online = true;

            if (is_online)
            {
                clear_all_views();
                force_redownload_ = open_url(MANUAL_URL + "update-manual", false, true);
                treeView->getRootItem()->clearSubItems();
                if (force_redownload_)
                {
                    struct UpdateThread : public AutonomThread
                    {
                        UIHtmlView *const _view;
                        const URL _url_to_load_after;
                        void run()
                        {
                            _view->open_url(MANUAL_URL, true, false);
                            _view->load_async_url = _url_to_load_after;
                            _view->triggerAsyncUpdate();
                            selfkill();
                        }
                        UpdateThread(UIHtmlView *view_, const URL &url_to_load_after_)
                            : AutonomThread("B-Manual-Updater"), _view(view_),
                              _url_to_load_after(url_to_load_after_)
                        {
                            _view->block_views(false);
                            view_->pending_download = this;
                            startThread(1);
                        }
                        ~UpdateThread()
                        {
                            if (!threadShouldExit())
                                _view->pending_download = nullptr;
                        }
                    };

                    new UpdateThread(this, request_for_);

                    return true;
                }
            }
            AlertWindow::showMessageBox(AlertWindow::WarningIcon, "ERROR",
                                        "Can not connect to the manual server.\nMaybe the server "
                                        "is down or your internet connection is broken.",
                                        "OK", this);

            SESSION_ERROR_LOG("ERROR Can not connect to the manual server.");

            return false;
        }
    }
    else
    {
        open_url(MANUAL_URL + "beginner/tools");
        select_item_with_url(MANUAL_URL + "beginner/tools");

        return false;
    }

    return false;
}

enum
{
    PADDING_LEFT_RIGHT = 10
};

void UIHtmlView::select_item_with_url(const URL &url_)
{
    NavItem *child;
    String look_for_url =
        url_.toString(false).fromFirstOccurrenceOf(".com/", false, false); // remove redirect url;
    for (int i = 0; i != items.size(); ++i)
    {
        child = items.getUnchecked(i);
        String child_url = child->get_url().toString(false).fromFirstOccurrenceOf(
            ".com/", false, false); // remove real url
        if (child_url == look_for_url)
        {
            treeView->scrollToKeepItemVisible(child);
            child->setSelected(true, true);
            break;
        }
    }
}

#include "UiMainWindow.h"
void UIHtmlView::add_text_part(const String &text_, int height_, int white_spaces_before_,
                               bool show_content_, Colour col_, bool make_selectable_)
{
    CHECK_THREAD_EXIT({
        OUT("add_text_part");
        return;
    });
    if (!show_content_)
        return;

    TextEditor *editor = new TextEditor();
    editor->setMultiLine(true);
    editor->setReturnKeyStartsNewLine(false);
    editor->setReadOnly(true);
    editor->setScrollbarsShown(false);
    editor->setCaretVisible(false);
    if (!make_selectable_)
    {
        editor->setPopupMenuEnabled(true);
        editor->setInterceptsMouseClicks(false, false);
    }
    editor->setColour(
        TextEditor::textColourId,
        (col_ == Colour(0x00000000) ? Colour(height_ < 7 ? 0xffE57A1F : 0xffffffff) : col_));
    editor->setColour(TextEditor::backgroundColourId, Colour(0x00ffffff));
    // editor->setColour (TextEditor::outlineColourId, Colour
    // (GLOBAL_VALUE_HOLDER::get().MASTER_COLOUR));
    editor->setColour(TextEditor::shadowColourId, Colour(0x00000000));
    editor->setColour(TextEditor::highlightColourId, Colours::yellow);

    float heigh_prop = 1.f / 600 * getHeight();
    Font font = editor->getFont().withHeight(heigh_prop * (15 + (7 - height_) * 2));
    if (height_ < 5)
        font.setStyleFlags(Font::bold);
    editor->setFont(font);

    editor->setText(text_, dontSendNotification);

    int padding_left = PADDING_LEFT_RIGHT + white_spaces_before_;
    editor->setSize(content_wrapper->getWidth() - white_spaces_before_, 100);
    content_wrapper->addAndMakeVisible(editor);
    editor->setSize(content_wrapper->getWidth() - padding_left, editor->getTextHeight());
    editor->setBounds(padding_left, current_height, editor->getWidth(), editor->getHeight());

    current_height += editor->getTextHeight() + 5;
    content_wrapper->setSize(content_wrapper->getWidth(), current_height);

    editors.add(editor);
}
void UIHtmlView::add_image(const String &url_, bool show_content_)
{
    CHECK_THREAD_EXIT({
        OUT("add_image");
        return;
    });
    // CHECK IF ALREDY EXIST AND DOWNLOAD IF NOT
    File image_cache_folder = get_manual_folder().getChildFile("images");
    image_cache_folder.createDirectory();
    File image_file = image_cache_folder.getChildFile(url_.fromLastOccurrenceOf("/", false, false));

    Image image;
    if (image_file.existsAsFile())
    {
        image = ImageCache::getFromFile(image_file);
        ImageCache::setCacheTimeout(1000 * 60 * 3);
    }
    else
    {
        MemoryBlock block;
        URL(url_).readEntireBinaryStream(block);
        image_file.replaceWithData(block.getData(), block.getSize());
        image = ImageCache::getFromMemory(block.getData(), block.getSize());
        ImageCache::setCacheTimeout(1);
    }

    if (!show_content_)
        return;

    float prop = 1.f / image.getWidth() * content_wrapper->getWidth();
    image = image.rescaled(image.getWidth() * prop, image.getHeight() * prop);

    ImageButton *image_holder = new ImageButton(String());
    image_holder->setSize(image.getWidth(), image.getHeight());
    image_holder->setImages(false, true, true, image, 1.000f, Colour(0x00000000), image, 1.000f,
                            Colour(0x00000000), image, 1.000f, Colour(0x00000000));
    image_holder->setWantsKeyboardFocus(false);
    image_holder->setInterceptsMouseClicks(false, false);
    content_wrapper->addAndMakeVisible(image_holder);
    image_holder->setBounds(PADDING_LEFT_RIGHT, current_height,
                            image_holder->getWidth() - PADDING_LEFT_RIGHT,
                            image_holder->getHeight());
    current_height += image_holder->getHeight();
    content_wrapper->setSize(content_wrapper->getWidth(), current_height);

    images.add(image_holder);
}

void UIHtmlView::add_nav_link(const String &text_, const URL &target_, int deepness_,
                              bool and_open_it_)
{
    CHECK_THREAD_EXIT({
        OUT("add_nav_link");
        return;
    });

    String text = text_;
    if (text == "LATEST DOWNLOADS" || text_ == "NEWS")
        text += " (internet connection required)";

    const MessageManagerLock mmLock;
    NavItem *new_item = new NavItem(this, text, target_);
    if (last_added_item)
    {
        if (deepness_ == 0)
            treeView->getRootItem()->addSubItem(new_item);
        else if (deepness_ == last_deppnes)
        {
            TreeViewItem *parent = last_added_item->getParentItem();
            if (parent)
                parent->addSubItem(new_item);
            else
                treeView->getRootItem()->addSubItem(new_item);
        }
        else if (deepness_ > last_deppnes)
            last_added_item->addSubItem(new_item);
        else if (deepness_ < last_deppnes)
        {
            TreeViewItem *parent = last_added_item->getParentItem();
            if (parent)
            {
                parent = parent->getParentItem();
                if (parent)
                    parent->addSubItem(new_item);
                else
                    treeView->getRootItem()->addSubItem(new_item);
            }
            else
                treeView->getRootItem()->addSubItem(new_item);
        }
        else
            treeView->getRootItem()->addSubItem(new_item);
    }
    else
        treeView->getRootItem()->addSubItem(new_item);

    // if( and_open_it_ || deepness_ < 1 )
    new_item->setOpen(true);

    treeView->scrollToKeepItemVisible(new_item);

    last_added_item = new_item;
    last_deppnes = deepness_;
}

void UIHtmlView::clear_all_views()
{
    content_wrapper->removeAllChildren();
    treeView->getRootItem()->clearSubItems();
    editors.clearQuick(true);
    images.clearQuick(true);
    items.clearQuick();
    current_height = 0;
    nav_is_parsed = false;
}
void UIHtmlView::block_views(bool block_)
{
    treeView->setEnabled(block_);
    update->setVisible(block_);

    tree_view_dragger->setInterceptsMouseClicks(!block_, !block_);
}

void UIHtmlView::on_close_clicked()
{
    if (pending_download)
    {
        pending_download->signalThreadShouldExit();
        pending_download->notify();
        pending_download->waitForThreadToExit(-1);

        pending_download = nullptr;
    }

    _app_instance_store->editor_config.manual_editor = nullptr;
}
//[/MiscUserDefs]

//==============================================================================
UIHtmlView::UIHtmlView(AppInstanceStore *const app_instance_store_)
    : UiEditor("B-Manual"), _app_instance_store(app_instance_store_)
{
    addAndMakeVisible(viewport = new Viewport(String()));
    viewport->setScrollBarsShown(true, false);

    addAndMakeVisible(treeView = new TreeView("new treeview"));
    treeView->setColour(TreeView::linesColourId, Colour(0x8aff3b00));

    addAndMakeVisible(toolbar = new UiEditorToolbar(this, true, true, false));

    addAndMakeVisible(update = new TextButton(String()));
    update->setButtonText(TRANS("RE-DOWNLOAD COMPLETE MANUAL"));
    update->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight |
                              Button::ConnectedOnTop | Button::ConnectedOnBottom);
    update->addListener(this);

    addAndMakeVisible(forum = new TextButton(String()));
    forum->setButtonText(TRANS("CHECK THE FORUM"));
    forum->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight |
                             Button::ConnectedOnTop | Button::ConnectedOnBottom);
    forum->addListener(this);

    addAndMakeVisible(label = new Label("new label", TRANS("QUESTIONS TO THIS POINT: ")));
    label->setFont(Font(15.00f, Font::plain));
    label->setJustificationType(Justification::centredRight);
    label->setEditable(false, false, false);
    label->setColour(Label::textColourId,
                     Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label->setColour(TextEditor::textColourId, Colours::black);
    label->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

    addAndMakeVisible(label2 = new Label("new label", TRANS("OR\n")));
    label2->setFont(Font(15.00f, Font::plain));
    label2->setJustificationType(Justification::centred);
    label2->setEditable(false, false, false);
    label2->setColour(Label::textColourId,
                      Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label2->setColour(TextEditor::textColourId, Colours::black);
    label2->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

    addAndMakeVisible(mail = new TextButton(String()));
    mail->setButtonText(TRANS("CONTACT SUPPORT"));
    mail->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight |
                            Button::ConnectedOnTop | Button::ConnectedOnBottom);
    mail->addListener(this);

    addAndMakeVisible(label3 = new Label("new label", TRANS("|")));
    label3->setFont(Font(15.00f, Font::plain));
    label3->setJustificationType(Justification::centred);
    label3->setEditable(false, false, false);
    label3->setColour(Label::textColourId,
                      Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label3->setColour(TextEditor::textColourId, Colours::black);
    label3->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

    addAndMakeVisible(online = new TextButton(String()));
    online->setButtonText(TRANS("OPEN ONLINE VERSION"));
    online->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight |
                              Button::ConnectedOnTop | Button::ConnectedOnBottom);
    online->addListener(this);

    addAndMakeVisible(label4 = new Label("new label", TRANS("|")));
    label4->setFont(Font(15.00f, Font::plain));
    label4->setJustificationType(Justification::centred);
    label4->setEditable(false, false, false);
    label4->setColour(Label::textColourId,
                      Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label4->setColour(TextEditor::textColourId, Colours::black);
    label4->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

    addAndMakeVisible(tree_view_dragger = new FingerDrag(treeView->getViewport(), this));

    addAndMakeVisible(viewport_dragger = new FingerDrag(viewport, this));

    //[UserPreSize]
    if (!get_manual_folder().exists())
        update->setButtonText(TRANS("DOWNLOAD COMPLETE MANUAL"));

    pending_download = nullptr;
    can_something_selected = true;
    nav_is_parsed = false;
    content_wrapper = new Component();

    current_height = 0;

    String root("ROOT");
    URL url("TEST");
    treeView->setRootItem(new NavItem(this, root, url));
    treeView->setRootItemVisible(false);

    last_added_item = nullptr;
    last_deppnes = 0;

    treeView->getViewport()->setScrollBarThickness(10);
    viewport->setScrollBarThickness(10);
    //[/UserPreSize]

    setSize(900, 600);

    //[Constructor] You can add your own custom stuff here..
    content_wrapper->setVisible(true);
    viewport->setViewedComponent(content_wrapper, false);

    center_relative_and_make_visible(reinterpret_cast<Component *>(_app_instance_store->editor));
    //[/Constructor]
}

UIHtmlView::~UIHtmlView()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    on_close_clicked();

    content_wrapper->removeAllChildren();
    clear_all_views();
    treeView->deleteRootItem();
    delete viewport->getViewedComponent();
    //[/Destructor_pre]

    viewport = nullptr;
    treeView = nullptr;
    toolbar = nullptr;
    update = nullptr;
    forum = nullptr;
    label = nullptr;
    label2 = nullptr;
    mail = nullptr;
    label3 = nullptr;
    online = nullptr;
    label4 = nullptr;
    tree_view_dragger = nullptr;
    viewport_dragger = nullptr;

    //[Destructor]. You can add your own custom destruction code here..
    ImageCache::releaseUnusedImages();
    //[/Destructor]
}

//==============================================================================
void UIHtmlView::paint(Graphics &g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll(Colour(0xff161616));

    g.setColour(Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    g.drawRect(0, 0, proportionOfWidth(1.0000f), proportionOfHeight(1.0000f), 2);

    //[UserPaint] Add your own custom painting code here..
    ResizableWindow::moved();
    //[/UserPaint]
}

void UIHtmlView::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    viewport->setBounds(proportionOfWidth(0.3222f), proportionOfHeight(0.0167f),
                        proportionOfWidth(0.6222f), proportionOfHeight(0.8917f));
    treeView->setBounds(proportionOfWidth(0.0111f), proportionOfHeight(0.0167f),
                        proportionOfWidth(0.3111f), proportionOfHeight(0.8917f));
    toolbar->setBounds(getWidth() - proportionOfWidth(0.0556f), 0, proportionOfWidth(0.0556f),
                       proportionOfHeight(0.3333f));
    update->setBounds(proportionOfWidth(0.0222f),
                      proportionOfHeight(0.9667f) - proportionOfHeight(0.0417f),
                      proportionOfWidth(0.2111f), proportionOfHeight(0.0417f));
    forum->setBounds(proportionOfWidth(0.4333f),
                     proportionOfHeight(0.9667f) - proportionOfHeight(0.0417f),
                     proportionOfWidth(0.1444f), proportionOfHeight(0.0417f));
    label->setBounds(proportionOfWidth(0.2778f),
                     proportionOfHeight(0.9667f) - proportionOfHeight(0.0417f),
                     proportionOfWidth(0.1556f), proportionOfHeight(0.0417f));
    label2->setBounds(proportionOfWidth(0.5889f),
                      proportionOfHeight(0.9667f) - proportionOfHeight(0.0417f),
                      proportionOfWidth(0.0333f), proportionOfHeight(0.0417f));
    mail->setBounds(proportionOfWidth(0.6333f),
                    proportionOfHeight(0.9667f) - proportionOfHeight(0.0417f),
                    proportionOfWidth(0.1444f), proportionOfHeight(0.0417f));
    label3->setBounds(proportionOfWidth(0.7889f),
                      proportionOfHeight(0.9667f) - proportionOfHeight(0.0417f),
                      proportionOfWidth(0.0333f), proportionOfHeight(0.0417f));
    online->setBounds(proportionOfWidth(0.9778f) - proportionOfWidth(0.1444f),
                      proportionOfHeight(0.9667f) - proportionOfHeight(0.0417f),
                      proportionOfWidth(0.1444f), proportionOfHeight(0.0417f));
    label4->setBounds(proportionOfWidth(0.2444f),
                      proportionOfHeight(0.9667f) - proportionOfHeight(0.0417f),
                      proportionOfWidth(0.0333f), proportionOfHeight(0.0417f));
    tree_view_dragger->setBounds(proportionOfWidth(0.0111f), proportionOfHeight(0.0167f),
                                 proportionOfWidth(0.3111f), proportionOfHeight(0.8917f));
    viewport_dragger->setBounds(proportionOfWidth(0.3222f), proportionOfHeight(0.0167f),
                                proportionOfWidth(0.6222f), proportionOfHeight(0.8917f));
    //[UserResized] Add your own custom resize handling here..

    ResizableWindow::resized();

    int y = 0;
    int h = 0;
    int wrapper_w = viewport->getWidth() - viewport->getScrollBarThickness() - PADDING_LEFT_RIGHT;
    for (int i = 0; i < content_wrapper->getNumChildComponents(); ++i)
    {
        Component *child = content_wrapper->getChildComponent(i);
        TextEditor *text_child;
        ImageButton *image_child;
        if ((text_child = dynamic_cast<TextEditor *>(child)))
        {
            text_child->setSize(wrapper_w - text_child->getX(), 0);
            h = text_child->getTextHeight();
            text_child->setBounds(text_child->getX(), y, wrapper_w - text_child->getX(), h);
        }
        else if ((image_child = dynamic_cast<ImageButton *>(child)))
        {
            float new_prop = 1.f / image_child->getWidth() * content_wrapper->getWidth();

            image_child->setBounds(0, y, wrapper_w, new_prop * image_child->getHeight());

            h = image_child->getHeight();
        }

        y += h;
    }

    content_wrapper->setSize(wrapper_w, y);
    //[/UserResized]
}

void UIHtmlView::buttonClicked(Button *buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == update)
    {
        //[UserButtonCode_update] -- add your button handler code here..
        URL online_test(MANUAL_URL + "is-online");
        {
            if (online_test.readEntireTextStream().contains("<!-- IS-ONLINE -->"))
            {
                URL url;
                if (treeView->getSelectedItem(0))
                    url = reinterpret_cast<NavItem *>(treeView->getSelectedItem(0))->get_url();
                else
                    url = MANUAL_URL + "update-manual-done";

                open_question_mark_content(url, true);
            }
            else
            {
                AlertWindow::showMessageBox(AlertWindow::WarningIcon, "ERROR",
                                            "Can not connect to the manual server.\nMaybe the "
                                            "server is down or your internet connection is broken.",
                                            "OK", this);

                SESSION_ERROR_LOG("ERROR Can not connect to the manual server.");
            }
        }
        //[/UserButtonCode_update]
    }
    else if (buttonThatWasClicked == forum)
    {
        //[UserButtonCode_forum] -- add your button handler code here..
        URL("http://forum.monoplugs.com/viewforum.php?f=47").launchInDefaultBrowser();
        //[/UserButtonCode_forum]
    }
    else if (buttonThatWasClicked == mail)
    {
        //[UserButtonCode_mail] -- add your button handler code here..
        String additional_info;
#ifndef B_STEP_STANDALONE
        additional_info = PluginHostType().getHostDescription();
        additional_info += " ";
#endif
        additional_info += SystemStats::getOperatingSystemName();

        String subject("Q: B-Step ");
        subject += String(ProjectInfo::versionString);
        subject += " (";
        subject += additional_info;
        subject += String(")");
        if (treeView->getSelectedItem(0))
        {
            NavItem *item = dynamic_cast<NavItem *>(treeView->getSelectedItem(0));
            if (item)
                subject = subject + String(" : ") + item->get_title();

            URL(String("mailto:support@monoplugs.com?subject=") + subject).launchInDefaultBrowser();
        }
        else
            URL(String("mailto:support@monoplugs.com?subject=") + subject).launchInDefaultBrowser();
        //[/UserButtonCode_mail]
    }
    else if (buttonThatWasClicked == online)
    {
        //[UserButtonCode_online] -- add your button handler code here..
        if (treeView->getSelectedItem(0))
        {
            NavItem *item = dynamic_cast<NavItem *>(treeView->getSelectedItem(0));
            if (item)
                item->get_url().launchInDefaultBrowser();
        }
        else
            URL(MANUAL_URL).launchInDefaultBrowser();
        //[/UserButtonCode_online]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]

//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="UIHtmlView" componentName=""
                 parentClasses="public UiEditor, public AsyncUpdater" constructorParams="AppInstanceStore* const app_instance_store_"
                 variableInitialisers="UiEditor(&quot;B-Manual&quot;),_app_instance_store(app_instance_store_)"
                 snapPixels="10" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="900" initialHeight="600">
  <BACKGROUND backgroundColour="ff161616">
    <RECT pos="0 0 100% 100%" fill="solid: ffffff" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffff3b0a"/>
  </BACKGROUND>
  <VIEWPORT name="" id="d0f85b5774b3a51c" memberName="viewport" virtualName=""
            explicitFocusOrder="0" pos="32.222% 1.667% 62.222% 89.167%" vscroll="1"
            hscroll="0" scrollbarThickness="18" contentType="1" jucerFile=""
            contentClass="" constructorParams=""/>
  <TREEVIEW name="new treeview" id="ef4a7251c37a4a2a" memberName="treeView"
            virtualName="" explicitFocusOrder="0" pos="1.111% 1.667% 31.111% 89.167%"
            linecol="8aff3b00" rootVisible="1" openByDefault="0"/>
  <GENERICCOMPONENT name="" id="b3ecc3f8f99fe16a" memberName="toolbar" virtualName="UiEditorToolbar"
                    explicitFocusOrder="0" pos="0Rr 0 5.556% 33.333%" class="Component"
                    params="this, true, true, false"/>
  <TEXTBUTTON name="" id="e32e1e70f7085771" memberName="update" virtualName=""
              explicitFocusOrder="0" pos="2.222% 96.667%r 21.111% 4.167%" buttonText="RE-DOWNLOAD COMPLETE MANUAL"
              connectedEdges="15" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="ba85117b979e1c7f" memberName="forum" virtualName=""
              explicitFocusOrder="0" pos="43.333% 96.667%r 14.444% 4.167%"
              buttonText="CHECK THE FORUM" connectedEdges="15" needsCallback="1"
              radioGroupId="0"/>
  <LABEL name="new label" id="b7520c7e754f5a8" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="27.778% 96.667%r 15.556% 4.167%"
         textCol="ffff3b00" edTextCol="ff000000" edBkgCol="0" labelText="QUESTIONS TO THIS POINT: "
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="34"/>
  <LABEL name="new label" id="31e2b54f7ce913dd" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="58.889% 96.667%r 3.333% 4.167%" textCol="ffff3b00"
         edTextCol="ff000000" edBkgCol="0" labelText="OR&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="" id="4b99d387f2c8024d" memberName="mail" virtualName=""
              explicitFocusOrder="0" pos="63.333% 96.667%r 14.444% 4.167%"
              buttonText="CONTACT SUPPORT" connectedEdges="15" needsCallback="1"
              radioGroupId="0"/>
  <LABEL name="new label" id="51db1a3716611c47" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="78.889% 96.667%r 3.333% 4.167%" textCol="ffff3b00"
         edTextCol="ff000000" edBkgCol="0" labelText="|" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="" id="90ff999d1e695c55" memberName="online" virtualName=""
              explicitFocusOrder="0" pos="97.778%r 96.667%r 14.444% 4.167%"
              buttonText="OPEN ONLINE VERSION" connectedEdges="15" needsCallback="1"
              radioGroupId="0"/>
  <LABEL name="new label" id="3127375dbdbe2e1c" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="24.444% 96.667%r 3.333% 4.167%" textCol="ffff3b00"
         edTextCol="ff000000" edBkgCol="0" labelText="|" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <GENERICCOMPONENT name="" id="42fcbdb763c1ae0e" memberName="tree_view_dragger"
                    virtualName="FingerDrag" explicitFocusOrder="0" pos="1.111% 1.667% 31.111% 89.167%"
                    class="FingerDrag" params="treeView-&gt;getViewport(),this"/>
  <GENERICCOMPONENT name="" id="da629782da7e7e91" memberName="viewport_dragger" virtualName="FingerDrag"
                    explicitFocusOrder="0" pos="32.222% 1.667% 62.222% 89.167%" class="FingerDrag"
                    params="viewport,this"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//[EndFile] You can add extra defines here...
//[/EndFile]
