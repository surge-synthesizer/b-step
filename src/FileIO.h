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

#ifndef FILEIO_H_INCLUDED
#define FILEIO_H_INCLUDED

#include "App.h"

class FileIOBase
{
  protected:
    juce::File _file;
    juce::String _name;

  protected:
    FileIOBase() {}
    ~FileIOBase() {}

  public:
    void set_file(juce::File file_to_load_) { _file = file_to_load_; }

    void set_dialog_name(const juce::String &name_) { _name = name_; }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FileIOBase)
};

template <class target_policy_class_t> class FileReader : public FileIOBase
{
    target_policy_class_t *const policy;

  public:
    FileReader(target_policy_class_t *const policy_) : policy(policy_) { _name = "LOAD FILE"; }

    void exec_and_set_to_selfmanagement()
    {
        bool native_dialog = true;
#if JUCE_IOS || JUCE_ANDROID || JUCE_LINUX
        native_dialog = false;
#endif
        juce::FileChooser fc(_name, _file, juce::String(), native_dialog);
        if (fc.browseForFileToOpen())
            policy->target_policy_class_t::put_file_to_target(fc.getResult());

        delete policy;
        delete this;
    }
    void exec_and_set_to_selfmanagement_directory()
    {
        bool native_dialog = true;
#if JUCE_IOS || JUCE_ANDROID || JUCE_LINUX
        native_dialog = false;
#endif
        juce::FileChooser fc(_name, _file, juce::String(), native_dialog);

        if (fc.browseForDirectory())
            policy->target_policy_class_t::put_file_to_target(fc.getResult());

        delete policy;
        delete this;
    }

  private:
    FileReader();    // -> delete
    ~FileReader() {} // private -> SELFKILLER!!!
};

template <class target_policy_class_t> class FileWriter : public FileIOBase
{
    target_policy_class_t *const policy;

  public:
    FileWriter(target_policy_class_t *const policy_) : policy(policy_) { _name = "SAVE FILE"; }

    void exec_and_set_to_selfmanagement()
    {
        bool native_dialog = true;
#if JUCE_IOS || JUCE_ANDROID || JUCE_LINUX
        native_dialog = false;
#endif
        juce::FileChooser fc(_name, _file, juce::String(), native_dialog);
        if (fc.browseForFileToSave(true))
            policy->target_policy_class_t::fill_file_from_source(fc.getResult());

        delete policy;
        delete this;
    }
    void exec_and_set_to_selfmanagement_directory()
    {
        bool native_dialog = true;
#if JUCE_IOS || JUCE_ANDROID || JUCE_LINUX
        native_dialog = false;
#endif
        juce::FileChooser fc(_name, _file, juce::String(), native_dialog);

        if (fc.browseForDirectory())
            policy->target_policy_class_t::fill_file_from_source(fc.getResult());

        delete policy;
        delete this;
    }

  private:
    FileWriter();    // -> delete
    ~FileWriter() {} // private -> SELFKILLER!!!
};

#endif // FILEIO_H_INCLUDED
