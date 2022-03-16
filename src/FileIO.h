/*
  ==============================================================================

    FileIO.h
    Created: 23 Mar 2014 3:36:16pm
    Author:  root

  ==============================================================================
*/

#ifndef FILEIO_H_INCLUDED
#define FILEIO_H_INCLUDED

#include "App.h"

class FileIOBase
{
  protected:
    File _file;
    String _name;

  protected:
    FileIOBase() {}
    ~FileIOBase() {}

  public:
    void set_file(File file_to_load_) { _file = file_to_load_; }

    void set_dialog_name(const String &name_) { _name = name_; }

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
        FileChooser fc(_name, _file, String(), native_dialog);
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
        FileChooser fc(_name, _file, String(), native_dialog);

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
        FileChooser fc(_name, _file, String(), native_dialog);
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
        FileChooser fc(_name, _file, String(), native_dialog);

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
