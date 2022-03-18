<a name="content"></a> 
# [B-Step Sequencer 2 - User Manual](http://b-step.monoplugs.com/manual) 
Last update: 31 of October 2014 - Version 2.0.2

Note: This manual is still in review. We apologize for any errors. Thank you.

<hr />

[//]: <> ( TODO: VST and AU setup )
[//]: <> ( TODO: VST AU compatibility mode. )

## New Users <a name="beginner"></a>
### [Quickie - It's your first time?](#quick-start) 
* [A few clicks to start triggering some notes (Standalone:iPad,Android,Mac,Linux,Windows,Raspberry) ](#triggering-first-notes) 
* [Getting started with the VST ](#start-vst-plugin)

### [User Interface Layout](#user-interface-layout)

### [Basic Functions](#functions-bars--steps) 
* [Playback Speed / Start & Stop](#playback-speed--start--stop) 
* [4 Strings, 16 Steps](#4-strings-16-steps) 
* [Duration and Velocity Rows](#duration-and-velocity-rows) 
* [Bar Selection and Bar Copy](#bar-selection-and-bar-copy) 
* [Bar Solo](#bar-solo)
* [Bar Mute](#bar-chain--mute) 
* [Bar Manipulations](#bar-manipulations) 
* [Bar String Octave Shifts](#bar-string-octave-shifts) 

### [Global Parameters](#global-functions) 
* [Global String Octave Shifts](#global-string-octave-shifts) 
* [Global Octave and Fine Tune](#global-octave-and-fine-tune) 
* [Global Chord Set](#global-chord-set)

### [The Chord Editor](#chord-editor) 
* [Presets](#chord-editor-presets)
* [Scales](#chord-editor-scales)

### [Tools](#tools)
* [Rubber](#tools-rubber)
* [Question](#tool-question-mark)

### [Multidrag Feature](#multidrag) 
* [Usage](#multidrag-usage) 
* [Settings](#multidrag-settings)
* [Special Drags](#special-drags)

### [**Master and Slave (Standalone)**](#master-slave)
* [Master](#master)
* [Slave](#slave)
* [Sync/Clock Thru](#slave-sync-thru)
* [MIDI Thru](#midi-thru)

### [Load/Save Projects](#load-save-project) 

<hr />

## [Presets and it's Soundsamples](#presets)
* [Arpeggios](#presets-arpeggios)
* [Drum Presets](#presets-drums)
* [Drum and MelodicPresets](#presets-drums-and-melodic)
* [Chord Progession Presets](#presets-progression)

<hr />

## [B-Step as Groovebox](#groove-box)

<hr />

## [Shuffle, Swing](#shuffle-shuffle)
* [Shuffle Grid](#shuffle-gride)
* [Shuffle Amount](#shuffle-amount) 
* [Velocity Manipulation](#shuffle-velocity)
* [Duration Manipulation](#shuffle-duration)

<hr />

## Rookie <a name="beginner"></a>

### [**What the hell are Layers?**](#layers)

### [Layer M (1st) - Basic](#layer-1) 

### [Layer S (2nd) - Step Manipulations](#layer-2)
* [Step Octave](#layer-2-step-octave) 
* [Step Chord and Use Step Chord](#layer-2-step-chord) 
* [Step Delay, Microtiming](#layer-2-step-delay)
* [Step Copy](#layer-2-step-copy)
* [Step Clean](#layer-2-step-clean) 

<hr />

## Advanced Users <a name="beginner"></a>
### [The Runlight - more than just left to right](#runlight)

### [Layer NL (3rd) - Non Linear Playback Features](#layer-3)
* [Step Probability](#layer-3-step-probability) 
* [Step Mute](#layer-3-step-mute) 
* [Start Position](#layer-3-start-position)
* [Restart Position](#layer-3-restart-position)
* [Force Position to Beat](#layer-3-force-position-to-beat)
* [Step Skip](#layer-3-step-skip)

### [Layer B (4th) - Bar Features, Poly](#layer-4)
* [Play Reverse](#layer-4-play-reverse) 
* [<< Steps >> - Move your Steps in the Bar around](#layer-4-move-steps) 
* [Force Bar 2 Chain](#layer-4-force-bar-2-chain)
* [Restart Sequence](#layer-4-restart-sequence)
* [Bar Skip](#layer-4-bar-skip)

### [Sequence Group - One Sequencer is not enough?](#layer-4-sequence-groups)
* [Define Sequence Groups](#layer-4-define-sequence-groups)
* [Sequence MIDI Output Settings - Control up to 4 Synths](#layer-4-sequence-number)

<hr />

## Experts <a name="beginner"></a>
### [Step repeats, Ratcheting - what is that?](#layer-5-sequencer-ratcheting)
### [Layer R1 (5th)  - Repeats, Ratcheting 1](#layer-5)
* [Step Repeats](#layer-5-repeats) 
* [Don't Roll Repeat](#layer-5-repeats-do-not-roll) 
* [Repeat Interval](#layer-5-repeat-interval)
* [Repeat Interval Offset](#layer-5-repeat-interval-offset)
* [Repeat Duration Offset](#layer-5-repeat-duration-offset)
* [Skip Repeat](#layer-5-repeat-skip)

### [Layer R2 (6th) - Repeats, Ratcheting 2](#layer-6)
* [Step Repeats](#layer-6-repeats) 
* [Repeat Velocity Offset](#layer-6-repeats-velocity-offset) 
* [Repeat Note Offset](#layer-6-repeat-note-offset)
* [Note up'N'down](#layer-6-note-up-and-down)
* [Free Notes](#layer-6-repeat-free-notes)
* [Repeat Probability](#layer-6-repeat-probability)

### [Layer CC (7th) - Control and Program Changes](#layer-7)
* [Send Program Changes](#layer-7-send-programm-changes) 
* [Send Control Changes](#layer-7-send-control-changes)

<hr />

## [Snapshots - Clipboard](#clipboard-sanpshots)
* [The Clipboard](#clipboard) 
* [Snapshots](#snapshots)

<hr />

## Controller Stuff <a name="beginner"></a>
### [Keyboard layout](#keyboard-control)

### [MIDI Learn](#midi-learn)
* [How to connect your Controller](#midi-learn-connect-controller)
* [How to train a MIDI Controller](#midi-learn-how-to-train)
* [Controller Feedback](#midi-feedback)
* [Learn Modes](#midi-learn-modes)
* [Load/Save Controller Maps](#midi-learn-load-save)

### [Use B-Step as MIDI Controller from your iPad or Android Tablet](#as-midi-controller)

### [Host Automation - only VST and AudioUnit](#automation-parameters)

### [**Novation Launchpad**](#novation-launchpad) 
* [How to connect the Launchpads](#how-to-connect-novation-launchpads)
* [View 8 Steps](#view-8-steps-recommend-if-you-use-one-launchpad) 
* [View Left Pad](#view-left-side-left-launchpad-if-you-use-two) 
* [View Right Pad](#view-right-side-right-launchpad-if-you-use-two) 

<hr />

### [Outro](#outro)

<hr />

### [Thanks](#thanks)

<hr />

#### [Changelog](#changelog)

</div><div class="manual">

Part by part a section will be highlighted and explained shortly.

</div><div class="manual">

[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
[//]: <> ( Quickie )
[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
<a name="quick-start"> </a>
## Quickie - It's your first time? 
<a name="triggering-first-notes"> </a>
### A few clicks to start triggering some notes (Standalone, iPad,Android,Mac,Linux,Windows,Raspberry) 
1. Open the In-Out settings (IO-settings).
2. Select your synthesizer at the Master Out (choose the right channel if your synthesizer does not listen on channel 1).
3. Close the IO-settings and push the play button -> this will start the playback of the sample project.

![B-Step Sequencer IO Settings - Quickstart](http://b-step.monoplugs.com/manual/images/b-step-sequencer-standalone-quickstart.gif)

**As Video**: <a href="javascript:show_fancy_video('http://www.youtube-nocookie.com/embed/ev-oLRccAQQ?autoplay=1')">Quick start (Standalone)</a> 

**Note**: You can start and stop B-Step by pushing the space key.


<br /> [back to top](#content) </div><div class="manual">


<a name="start-vst-plugin"> </a>
### Getting started with the VST
* <a href="javascript:show_fancy_video('http://www.youtube-nocookie.com/embed/_czLObz8Anw?autoplay=1')">Video: Using B-Step Sequencer in Ableton</a>
* <a href="javascript:show_fancy_video('http://www.youtube-nocookie.com/embed/e1NnmuepubQ?autoplay=1')">Video: Using B-Step Sequencer in Cubase</a>
[//]: <> ( * <a href="https://www.youtube.com/watch?v=x2OG_pUYr64" target="_blank">Video: Using B-Step Sequencer in Bitwig</a> )
* <a href="javascript:show_fancy_video('http://www.youtube-nocookie.com/embed/rxGulT8l9ss?autoplay=1')">Video: Using B-Step Sequencer in Cakewalk Sonar</a> (B-Step 1, but it works on the same way)<br /><br />
* <a href="http://forum.monoplugs.com/viewtopic.php?f=54&t=641#p2089" target="_blank">Forum: Using B-Step Sequencer in USINE</a> (B-Step 1, but it works on the same way)
* <a href="http://forum.monoplugs.com/viewtopic.php?f=54&t=604#p1948" target="_blank">Forum: Using B-Step Sequencer in FL Studio</a> (B-Step 1, but it works on the same way)

<hr>

**Windows VST Path:** 

- C:\Program Files\Steinberg\VstPlugIns
- C:\Program Files (x86)\Steinberg\VstPlugIns

**Mac VST, AU Path:**

- /Library/Audio/Plug-Ins/VST
- /Library/Audio/Plug-Ins/Components

**Linux VST Path:**

- ~/.vst


<br /> [back to top](#content) </div><div class="manual">


[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
[//]: <> ( User Interface )
[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
<a name="user-interface-layout"></a>
## User Interface Layout 
![B-Step Sequencer - The User Interface Layout](http://b-step.monoplugs.com/manual/images/b-step-sequencer-understand-user-interface-layout.gif)

B-Step has three basic sections.

The yellow area has parameters that modify steps. 
The blue area has bar related parameters which can be set for each bar and will be applied to it's steps.
The red area has global paramters which will be applied to all bars and it's steps.

The green marker shows the currently editable/selected bar. 
If you switch the editable bar you will change the view in the yellow area and can modify its steps.


<br /> [back to top](#content) </div><div class="manual">


[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
[//]: <> ( Basic Functions )
[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
<a name="functions-bars--steps"></a>
## Basic Functions 
<a name="playback-speed--start--stop"></a>
### Playback Speed / Start & Stop 
![B-Step Sequencer - Start, Stop and Pause](http://b-step.monoplugs.com/manual/images/b-step-sequencer-standalone-start-stop-pause.gif)

**VST only**:
Click on the three buttons for setting the playback tempo. Middle is 1 * host speed, left is 0.5 * host speed, right is 2 * host speed.

**Standalone only**:
Start, pause and stop B-Step Sequencer as master.

<br />
[back to top](#content)
<hr>

<a name="4-strings-16-steps"></a>
### 4 Strings, 16 Steps 
![B-Step Sequencer - Steps and Tracks (StringS)](http://b-step.monoplugs.com/manual/images/b-step-sequencer-steps-and-strings.gif)

4 strings (Tracks), 16 steps. Click for setting and unsetting the steps.

<br>
**Layer Note**: 
The Steps are on each layer available and have always the same functionality! 

<br />
[back to top](#content)
<hr>

<a name="duration-and-velocity-rows"></a>
### Duration and Velocity Rows (per Step) 
![B-Step Sequencer - Velocity and Duration](http://b-step.monoplugs.com/manual/images/b-step-sequencer-velocity-and-duration.gif)

You can set velocity and duration for each single step. Turn around.

* **Velocity scale:** 1 to 128
* **Duration scale:** 1/96th up to 4 whole notes

<br />
[back to top](#content)
<hr>

<a name="bar-selection-and-bar-copy"></a>
### Bar Selection and Bar Copy 
![B-Step Sequencer - Bars and Copy it](http://b-step.monoplugs.com/manual/images/b-step-sequencer-bars.gif)

Click on the bottom beige button for selecting the bar you want to edit. There are 16 bars. 

If you add steps to a new bar it will auto-chain. The blue "N" marker shows the next bar in the chain. The red "-" marker shows the bars that are in the chain. 

You can copy bars via drag and drop. If you want to reset a bar quickly, just take an empty bar, if still available and drop on a non-empty bar. Otherwise use the [rubber tool](#tools-rubber).

Create a nice bar, copy, modify. Repeat for the next bars. Enjoy.

<br>
**Note**: If you like to add an empty bar to the chain use the [Force Bar 2 Chain](#layer-4-force-bar-2-chain) feature on [Layer B (4th)](#layer-4). <br>
**Note**: If you are using a Novation Launchpad you can use the copy feature too (see [**Novation Launchpad**](#novation-launchpad)). <br>
<br>
**Layer Note**: The bar selection button row is on each layer available and has always the same functionality.

<br />
**Note:** You can browse through the bars with the cursor left and right keys or by F and number keys.

<br />
[back to top](#content)
<hr>

<a name="bar-solo"></a>
### Bar Solo 
![B-Step Sequencer - Solo Bar](http://b-step.monoplugs.com/manual/images/b-step-sequencer-bar-solo.gif)

Enable one solo button to stay on that bar or enable more than one to define a group of bars that you want to loop.

<br>
**Layer Note**:
The bar solo button row is on each layer available and has always the same functionality!

<br />
[back to top](#content)
<hr>

<a name="bar-chain--mute"></a>
### Bar Mute 
![B-Step Sequencer - Mute a Bar](http://b-step.monoplugs.com/manual/images/b-step-sequencer-bar-mute.gif)

Mutes every MIDI event that a bar can produce. This include all notes, control and program changes.

<br />
**Changelog Note**: Changed in v2.0 from "Mute & Chain" to "Mute". "Chain" you will find as [force bar2chain](#layer-4-force-bar-2-chain) on [Layer B (4th)](#layer-4).

<br />
[back to top](#content)
<hr>

<a name="bar-manipulations"></a>
### Bar Manipulations 
![B-Step Sequencer - Bar Manipulations](http://b-step.monoplugs.com/manual/images/b-step-sequencer-bar-manipulations.gif)

Each bar has 3 basic manipulation parameters.

* **Bar octave** can shift the notes in octaves up and down.
* **Bar chord** can select the chord for this bar (see [The Chord Editor](#chord-editor))
* **Bar repeats** can repeat the bar 1 to 8 times.

<br />
[back to top](#content)
<hr>

<a name="bar-string-octave-shifts"></a>
### Bar String Octave Shifts 
![B-Step Sequencer - Track Octave Shifts](http://b-step.monoplugs.com/manual/images/b-step-sequencer-bar-string-octave.gif)

You can also shift each string in octaves per bar individually. Those are added on top of what you had and will be shown as offset in the steps "-2, -1, 1, 2"

* **Scale:** -2 to 2


<br /> [back to top](#content) </div><div class="manual">


[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
[//]: <> ( Global Parameters )
[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
<a name="global-functions"></a>
## Global Parameters 
<a name="global-string-octave-shifts"></a>
### Global String Octave Shifts 
![B-Step Sequencer - Global Track Octave Shift](http://b-step.monoplugs.com/manual/images/b-step-sequencer-global-string-octave.gif)

Similar to [Bar String Octave](#bar-string-octave-shifts), but it will shift the octave for each string in each bar.

<br />
[back to top](#content)
<hr>

<a name="global-octave-and-fine-tune"></a>
### Global Octave and Fine Tune 
![B-Step Sequencer - Tune](http://b-step.monoplugs.com/manual/images/b-step-sequencer-global-octave-fine-tune.gif)

Finally we have on the right side another two master parameters, which add on top of what you had so far. Octave shifting notes in octaves. 

Fine Tune is for setting the root note or the tune of the bass guitar (transposes each string). Easy.

* **Fine Tune scale:** 1 to 12 OR A, A#, B... G# (default is E, that is relating to Bass Guitar **E** A D G tune.) 
* **Octave scale:** -3 to +3

<br />
[back to top](#content)
<hr>

<a name="global-chord-set"></a>
### Global Chord Set 
![B-Step Sequencer - Chords](http://b-step.monoplugs.com/manual/images/b-step-sequencer-global-chord-set.gif)

Will change the currently available and selected chords at the Bar Chords. 
5 Chord Sets are available with 6 Chords per set, which you can edit with the [Chord Editor](#chord-editor) - use the edit button left to open the [Chord Editor](#chord-editor).

* **Scale:** 1 to 5


<br /> [back to top](#content) </div><div class="manual">


[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
[//]: <> ( Chord Editor )
[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
<a name="chord-editor"></a>
## The Chord Editor 
![B-Step Sequencer - Chord Editor](http://b-step.monoplugs.com/manual/images/b-step-sequencer-chords-editor.gif)

To open the Chord Editor push the button left of Chord Set slider.

With the editor you can edit the six chords of the currently selected [Global Chord Set](#global-chord-set). Each slider row is one chord over the 4 strings. Right of the slider you will see the resulting note - which also depends on the [Fine Tune](#global-octave-and-fine-tune).

<a name="chord-editor-presets"></a>
### Presets 
You do not have to design every chord by yourself. You can select a chord (Preset Target) and push one of the preset buttons below (A,B,C...; Am (m = minor), Bm, Cm). Done, chord changed.

<a name="chord-editor-scales"></a>
### Scales 
If you like you can generate scale based chords randomly. Select a scale, select a Target Chord and push the button "Fill Target Chord randomly from Scale" or if you want you can do this for all chords by click the button "Fill ALL Chords randomly from scale".

<br />
**Tip:** How to make a blues chord progression: A D E? -> select chord one and assign the "A-"preset and also to chord two and three. Set transpose at chord one to 0, chord two to +5 and chord three to +7 (like in the picture above). Then assign these chords to 12 bars 1-1-1-1-2-2-1-1-3-2-1-3 (A-A-A-A-D-D-A-A-E-D-A-E) and enable some steps in those bars. Enjoy.

**Video:** <a href="javascript:show_fancy_video('http://www.youtube-nocookie.com/embed/n5nW3Ra6N44?autoplay=1')">How to create a chord progression by Tom Traxx </a>(done with B-Step 1)


<br /> [back to top](#content) </div><div class="manual">


[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
[//]: <> ( Tools )
[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
<a name="tools"></a>
## Tools 
![B-Step Sequencer - Rubber Tool](http://b-step.monoplugs.com/manual/images/b-step-sequencer-tools-rubber.gif)

<a name="tools-rubber"></a>
### Rubber 

Drag and drop the Rubber on any slider or button to reset it's state to factory default. Dropping on a bar resets the whole bar - on a runlight step the whole step will be resetted.

<a name="tool-question-mark"></a>
### Question 

By dropping the question mark on a slider or button the browser will be opend and navigate to it's element description here in the user manual.


<br /> [back to top](#content) </div><div class="manual">


[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
[//]: <> ( Multidrag )
[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
<a name="#multidrag"></a>
## Multidrag Feature 
With B-Step's powerful multidrag feature you can easily copy the state from one button/slider to more than just another one or copy a bar to more than one other in one action!

<a name="multidrag-usage"></a>
### Multidrag Usage 
![B-Step Sequencer - Multidrag](http://b-step.monoplugs.com/manual/images/b-step-sequencer-multidrag-action.gif)

On mouse controlled systems by default you start a multidrag by dragging a button/slider with the right mouse button.

On touch controlled systems by default you start a multidrag by holding a button/slider longer than 750ms without moving your finger.

If you have started a multidrag all possible targets will be marked with a "T" label. 
Then you can drag your source "S" over the targets you want and this will immediately change the states of the targets.

<br />
[back to top](#content)
<hr>

<a name="multidrag-settings"></a>
### Multidrag Settings 
![B-Step Sequencer - Multidrag Settings](http://b-step.monoplugs.com/manual/images/b-step-sequencer-multidrag.gif)

To optimize the multidrag handling you can adjust it to you needs.

* **Multidrag Right Mouse**: if disabled the multidrag feature will be on the left mouse and will be handled like on touch controlled systems.
* **Multidrag Delay**: defines the delay to start a multidrag. Default 750ms. (No effect if you use on right mouse)
* **Multidrag Sensitivity**: defines the x,y offset that you can move your finger or mouse without disabel the multidrag start timer. (No effect if you use on right mouse)

<br />
[back to top](#content)
<hr>

<a name="special-drags"></a>
### Special Drags 
A bar drag will overwrite a target bar completely. If you like to copy just a few bar settings have a look at the [Clipboard Copy Feature](#clipboard-sanpshots).

Also you can multidrag steps in the top row (see [The Runlight](#runlight)) - a source step will overwrite all settings of all layers in the target step!


<br /> [back to top](#content) </div><div class="manual">


[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
[//]: <> ( Master / Slave )
[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
<a name="master-slave"></a>
## **Master and Slave (Standalone)** 
B-Step can be used as clock master or synced in slave mode to another master like a drum machine.

![B-Step Sequencer - Slave (MIDI Clock) and Clock Master](http://b-step.monoplugs.com/manual/images/b-step-sequencer-master-slave.gif)

<a name="master"></a>
### Master 

If you like to run B-Step as master choose your slave device at "Master Output (to Synth) Ch/Port" and push the play button on the main user interface. 
B-Step will send MIDI start, stop, continue and clock to the slave. A second device you can connect to "Second Out" - this device will be feeded with the same data like the Master Out.

<a name="slave"></a>
### Slave 

To run B-Step in slave mode you have to select your clock master device (e.g. your drum machine or DAW) at "Receive Channel/Port". 
If B receives a clock at this port then B-Step stops generating it's own clock and is waiting for MIDI start, stop, continue and clock. 
All other events will be ignored on this port or you can optional forward it (see [Sync/Clock Thru](#slave-sync-thru), [MIDI Thru](#midi-thru)).

<a name="slave-sync-thru"></a>
### Sync/Clock Thru 

When B-Step is running in slave mode you can forward the received sync events (Start, Stop, Continue, Clock) to the outputs (Master Out, Sceond Out, Group 2,3 & 4). 
Just enable "MIDI Sync Thru".

<br />
**NOTE:** B-Step does also forward the events in master mode but removes any other clock event.

<a name="midi-thru"></a>
### MIDI Thru 

Similar to [Sync/Clock Thru](#slave-sync-thru), but if enabled B forwards all other events like MIDI notes, CC, PC etc.


<br /> [back to top](#content) </div><div class="manual">


[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
[//]: <> ( Load Save Project )
[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
<a name="load-save-project"></a>
### Load/Save Projects 
![B-Step Sequencer - Load and Save Projects](http://b-step.monoplugs.com/manual/images/b-step-sequencer-load-save-project.gif)

To load or save a project click on the buttons in the right bar and use the filechooser to navigate an create or load your projects. 

A project file just contains all the project parameters (file extension: "b2prj"). It does not contain: MIDI IO settings, MIDI controller or things like [Multidrag Settings](#multidrag-settings). Your trained MIDI controller will be stored in "b2patch"-files and all the other settings in "b2cfg"-files.  

By default B-Step stores all your settings and project data on shutdown and restore this on restart. 

<br />
**VST, AudioUnit:** The plugin version does NOT auto save/load data! This should be managed inside with your DAW!

**Note:** In the most editors you have the same functionailty to im- and export things like [Chord Sets](#chord-editor) , [MIDI Mappings](#midi-learn) and [Snapshots](#clipboard-sanpshots). 


<br /> [back to top](#content) </div><div class="manual">


[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
[//]: <> ( Presets )
[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
<a name="presets"></a>
## Presets and it's Soundsamples 
Project presets you can load in the right menu bar (see [Load/Save Projects](#load-save-project)).

It's up to you and your synthesizers how your set will sound, but here is an overview how the presets can sound.

<a name="presets-arpeggios"></a>
### Arpeggios 
* <audio id="player" controls><source src="presets/projects/arpeggios/arpeggio-A.mp3" type="audio/mp3">Your browser does not support the audio element.
</audio> ::: arpeggio-A
<br><br>
* <audio id="player" controls><source src="presets/projects/arpeggios/arpeggio-B.mp3" type="audio/mp3">Your browser does not support the audio element.
</audio> ::: arpeggio-B
<br><br>
* <audio id="player" controls><source src="presets/projects/arpeggios/arpeggio-C.mp3" type="audio/mp3">Your browser does not support the audio element.
</audio> ::: arpeggio-C
<br><br>
* <audio id="player" controls><source src="presets/projects/arpeggios/arpeggio-D.mp3" type="audio/mp3">Your browser does not support the audio element.
</audio> ::: arpeggio-D

<a name="presets-drums"></a>
### Drum Presets 

* <audio id="player" controls><source src="presets/projects/drums/chill.mp3" type="audio/mp3">Your browser does not support the audio element.
</audio> ::: chill
<br><br>
* <audio id="player" controls><source src="presets/projects/drums/drumNbass.mp3" type="audio/mp3">Your browser does not support the audio element.
</audio> ::: drumNbass
<br><br>
* <audio id="player" controls><source src="presets/projects/drums/drumNbass-B.mp3" type="audio/mp3">Your browser does not support the audio element.
</audio> ::: drumNbass-B
<br><br>
* <audio id="player" controls><source src="presets/projects/drums/house-A.mp3" type="audio/mp3">Your browser does not support the audio element.
</audio> ::: house-A
<br><br>
* <audio id="player" controls><source src="presets/projects/drums/house-B.mp3" type="audio/mp3">Your browser does not support the audio element.
</audio> ::: house-B
<br><br>
* <audio id="player" controls><source src="presets/projects/drums/house-C.mp3" type="audio/mp3">Your browser does not support the audio element.
</audio> ::: house-C
<br><br>
* <audio id="player" controls><source src="presets/projects/drums/house-D.mp3" type="audio/mp3">Your browser does not support the audio element.
</audio> ::: house-D
<br><br>
* <audio id="player" controls><source src="presets/projects/drums/indie.mp3" type="audio/mp3">Your browser does not support the audio element.
</audio> ::: indie
<br><br>
* <audio id="player" controls><source src="presets/projects/drums/lounge.mp3" type="audio/mp3">Your browser does not support the audio element.
</audio> ::: lounge
<br><br>
* <audio id="player" controls><source src="presets/projects/drums/step.mp3" type="audio/mp3">Your browser does not support the audio element.
</audio> ::: step
<br><br>
* <audio id="player" controls><source src="presets/projects/drums/techhouse.mp3" type="audio/mp3">Your browser does not support the audio element.
</audio> ::: techhouse
<br><br>
* <audio id="player" controls><source src="presets/projects/drums/techno-A.mp3" type="audio/mp3">Your browser does not support the audio element.
</audio> ::: techno-A
<br><br>
* <audio id="player" controls><source src="presets/projects/drums/techno-B.mp3" type="audio/mp3">Your browser does not support the audio element.
</audio> ::: techno-B
<br><br>
* <audio id="player" controls><source src="presets/projects/drums/techno-C.mp3" type="audio/mp3">Your browser does not support the audio element.
</audio> ::: techno-C
<br><br>
* <audio id="player" controls><source src="presets/projects/drums/techno-D-ratcheting.mp3" type="audio/mp3">Your browser does not support the audio element.
</audio> ::: techno-D-ratcheting
<br><br>
* <audio id="player" controls><source src="presets/projects/drums/techno-E-ratcheting.mp3" type="audio/mp3">Your browser does not support the audio element.
</audio> ::: techno-E-ratcheting

<a name="presets-drums-and-melodic"></a>
### Drum and Melodic Presets 
* <audio id="player" controls><source src="presets/projects/drum-and-melodic/drumNbass-with-arpeggio.mp3" type="audio/mp3">Your browser does not support the audio element.
</audio> ::: drumNbass-with-arpeggio
<br><br>
* <audio id="player" controls><source src="presets/projects/drum-and-melodic/drumNbass-with-arpeggio-B.mp3" type="audio/mp3">Your browser does not support the audio element.
</audio> ::: drumNbass-with-arpeggio-B
<br><br>
* <audio id="player" controls><source src="presets/projects/drum-and-melodic/epic-dub.mp3" type="audio/mp3">Your browser does not support the audio element.
</audio> ::: epic-dub

<a name="presets-progression"></a>
### Chord Progession Presets
* <audio id="player" controls><source src="presets/projects/progression/11-45.mp3" type="audio/mp3">Your browser does not support the audio element.
</audio> ::: 11-45
<br><br>
* <audio id="player" controls><source src="presets/projects/progression/12-25-softSuffle.mp3" type="audio/mp3">Your browser does not support the audio element.
</audio> ::: 12-25-softSuffle
<br><br>
* <audio id="player" controls><source src="presets/projects/progression/12-45.mp3" type="audio/mp3">Your browser does not support the audio element.
</audio> ::: 12-45
<br><br>
* <audio id="player" controls><source src="presets/projects/progression/15-64-shuffle.mp3" type="audio/mp3">Your browser does not support the audio element.
</audio> ::: 15-64-shuffle
<br><br>
* <audio id="player" controls><source src="presets/projects/progression/16-45-shuffle.mp3" type="audio/mp3">Your browser does not support the audio element.
</audio> ::: 16-45-shuffle
<br><br>
* <audio id="player" controls><source src="presets/projects/progression/45-16.mp3" type="audio/mp3">Your browser does not support the audio element.
</audio> ::: 45-16
<br><br>
* <audio id="player" controls><source src="presets/projects/progression/64-15-hardShuffle.mp3" type="audio/mp3">Your browser does not support the audio element.
</audio> ::: 64-15-hardShuffle
<br><br>
* <audio id="player" controls><source src="presets/projects/progression/andal.mp3" type="audio/mp3">Your browser does not support the audio element.
</audio> ::: andal
<br><br>
* <audio id="player" controls><source src="presets/projects/progression/blues.mp3" type="audio/mp3">Your browser does not support the audio element.
</audio> ::: blues
<br><br>
* <audio id="player" controls><source src="presets/projects/progression/pachebel.mp3" type="audio/mp3">Your browser does not support the audio element.
</audio> ::: pachebel
<br><br>
* <audio id="player" controls><source src="presets/projects/progression/qdown-softShuffle.mp3" type="audio/mp3">Your browser does not support the audio element.
</audio> ::: qdown-softShuffle
<br><br>

<br />
**Note:** If you are interested on more presets: we will publish a preset database soon there you can download new presets which currently not included. 
To keep up to date <a href="http://b-step.monoplugs.com/#newsletter">subscribe to our newsletter</a> (no spam, just information about tutorials, presets and other useful stuff).


<br /> [back to top](#content) </div><div class="manual">


[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
[//]: <> ( Groovebox )
[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
<a name="groove-box"></a>
## B-Step as Groovebox 
Since B-Step 2 it's also possible to program drum sets.

To switch in the drum mode enable the "DRUM" checkbox in the chord editor - this will simply switch to short drum names instead of note names. 
Then you can choose the instruments you need. 

![B-Step Sequencer - Groove Box](http://b-step.monoplugs.com/manual/images/b-step-sequencer-groove-box.gif)

<br />
**Video:** <a href="javascript:show_fancy_video('http://www.youtube-nocookie.com/embed/02-iXkGm7bA?autoplay=1')">Drumset with B-Step</a>

<br />
**Tip:** Check the factory presets to get some ideas and you can take a look at the [Shuffle](#shuffle-shuffle)-features. <br />
<br />
**Trouble Shooting:** Common percussion synthesizer receive it's note events at MIDI channel 10 - you should change the channel in the IO-settings if your machine does not play any sound.


<br /> [back to top](#content) </div><div class="manual">


[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
[//]: <> ( Shuffle Swing )
[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
<a name="shuffle-shuffle"></a>
## Shuffle, Swing - B-Step's groovie Heart! 
With B-Step's shuffle feature you will get the right groove in your set by a few slider changes. The shuffle feature is a global parameter and will be added to each bar or/and step.

**Video:** <a href="javascript:show_fancy_video('http://www.youtube-nocookie.com/embed/CStN8gMOhIY?autoplay=1')">Shuffle on top of an arpeggio</a> <br />
**Video:** <a href="javascript:show_fancy_video('http://www.youtube-nocookie.com/embed/SPEdBFOirkg?autoplay=1')">How to make a swinging arpeggio</a>

![B-Step Sequencer - Shuffe, Swing, Groove!](http://b-step.monoplugs.com/manual/images/b-step-sequencer-swing-shuffle.gif)

<a name="shuffle-gride"></a>
### Shuffle Grid 
To enable shuffle you have to set the first slider from the left ("shfl") to 16th, 8th or 4th. This will define the shuffle grid size or disable the whole shuffle feature ("OFF").

By setting the grid size to 16th, every second 16th will be modified (like in the picture above) - 8th will modify every second 8th and 4th every second 4th. 
The setting of the gride alone will not modify anything - the modifications will be done by the following parameters: 
[Shuffle Amount](#shuffle-amount), [Velocity Manipulation](#shuffle-velocity) and [Duration Manipulation](#shuffle-duration).

<a name="shuffle-amount"></a>
### Shuffle Amount (">>") 
The shuffle amount moves the trigger point of each step in the shuffle grid into the future - relative to it's original trigger point in 1/96th steps resolution (a clock step).

This is the basic setting to get some groove into your set.

**Se also:** [Step Delay, Microtiming](#layer-2-step-delay) has the same functionality but for each step. 

<a name="shuffle-velocity"></a>
### Velocity Manipulation 
The velocity manipulation changes (decrease) the velocity of the steps in the shuffle grid.

<a name="shuffle-duration"></a>
### Duration Manipulation 
Changes the duration of the steps in the shuffle grid - they can be longer or shorter as it's original step duration.

<hr>

**Note:** If you don't have a step enabled in the shuffle gride you will have absolutely no effect!


<br /> [back to top](#content) </div><div class="manual">


[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
[//]: <> ( Runlight )
[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
<a name="runlight"></a>
## The Runlight - more than just left to right 
The runlight is your friend! A lot of the settings that you will do in the next parts you can't see all the time. But the runlight knows what
happens and will show it to you! Basically you have to know that some things will be shown depending on which bar you have selected or what currently 
is running. Ok, let us check the next parts!

![B-Step Sequencer - Layers](http://b-step.monoplugs.com/manual/images/b-step-sequencer-runlight.gif)

**Note:** You can drag and drop a whole step also via the runlight. 


<br /> [back to top](#content) </div><div class="manual">


[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
[//]: <> ( Layers )
[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
<a name="layers"></a>
## What the hell are Layers? 
![B-Step Sequencer - Layers](http://b-step.monoplugs.com/manual/images/b-step-sequencer-layers.gif)

On the left bar you have up to 7 selectable layers - this is similar to a tabbed view. If you change to another layer all the blue marked features will be replaced with other features
(all the other elements at the user interface are fixed and have always the same functionality!).

To access all layers you have to enable the pro mode by clicking the 5 star button. The 3 star button enables only the mid skilled mode and 1 star button you can use if you are starting with B-Step
or if you do not need the other features.

<br />
**Note:** You can browse through the layers with the cursor up and down keys.


<br /> [back to top](#content) </div><div class="manual">


<a name="layer-1"></a>
## Layer M (1st) - Basic 

We already explained the features of the Main layer in [Basic Functions](#functions-bars--steps) starting with [Bar Mute](#bar-chain--mute) - 
please study this part before you go on with the next layers!

**Feature Overview:**

* [Duration and Velocity Rows](#duration-and-velocity-rows) 
* [Bar Mute](#bar-chain--mute) 
* [Bar Manipulations](#bar-manipulations)


<br /> [back to top](#content) </div><div class="manual">


[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
[//]: <> ( Layer 2 )
[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
<a name="layer-2"></a>
## Layer S (2nd) - Step Manipulations 
![B-Step Sequencer - Layer 2 - Step Manipulations](http://b-step.monoplugs.com/manual/images/b-step-sequencer-layers-2.gif)

**Feature Overview:**

* [Step Octave](#layer-2-step-octave) 
* [Step Chord and Use Step Chord](#layer-2-step-chord) 
* [Step Delay, Microtiming](#layer-2-step-delay)
* [Step Copy](#layer-2-step-copy)
* [Step Clean](#layer-2-step-clean)

<br />
[back to top](#content)
<hr>

<a name="layer-2-step-octave"></a>
### Step Octave 

Shift the octave for each step. This octave offset is added on top of what you had and will be shown  
as offset in the steps "-2, -1, 1, 2"

* **Scale:** -2 to 2

<a name="layer-2-step-chord"></a>
### Step Chord and Use Step Chord 

Define a chord for a step and overwrite the [Bar Chord](#bar-manipulations)  by enabling it with "Use Step Chord".

**See also:**

* [Bar Manipulations](#bar-manipulations) - Bar Chord
* [Global Chord Set](#global-chord-set)
* [Chord Editor](#chord-editor) 
* [Chord Editor Presets](#chord-editor-presets) 

<a name="layer-2-step-delay"></a>
### Step Delay, Microtiming 

The step delay will move the trigger point of this step to the future by 1/96th resolution to get it more groovie.

* Scale: 0/96th to 5/96th

**Se also:** [Shuffle Amount](#shuffle-amount) to do it for all steps globaly. 

<a name="layer-2-copy"></a>
### Step Copy 

Copy a step by drag and drop to an other. You can also copy a step in the top [Runlight](#runlight) row.

<br />
**Note:** will be removed in v2.x

<a name="layer-2-clean"></a>
### Step Clean 

Delete all the data of this step. You can do the same by droping the rubber tool on a step in the top [Runlight](#runlight) row.

<br />
**Note:** will be removed in v2.x


<br /> [back to top](#content) </div><div class="manual">


[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
[//]: <> ( Layer 3 )
[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
<a name="layer-3"></a>
## Layer NL (3rd) - Non Linear Playback Features
On the NL layer you have a bunch of features to go away from the liniar step by step playback of one bar.

![B-Step Sequencer - Layer 3 - Non Liniear Playback](http://b-step.monoplugs.com/manual/images/b-step-sequencer-layers-3.gif)

**Feature Overview:**

* [Step Probability](#layer-3-step-probability) 
* [Step Mute](#layer-3-step-mute) 
* [Start Position](#layer-3-start-position)
* [Restart Position](#layer-3-restart-position)
* [Force Position to Beat](#layer-3-force-position-to-beat)
* [Step Skip](#layer-3-step-skip)

<br />
[back to top](#content)
<hr>

**Video:** <a href="javascript:show_fancy_video('http://www.youtube-nocookie.com/embed/FvzIoAzWPKc?autoplay=1')">Shows the playback of the settings in the picture above which we explain in the next few points.</a>

<hr>

<a name="layer-3-step-probability"></a>
### Step Probability 
Defines with which probability the step will be triggerd. If you set it e.g. to 50% in theory the step will just triggerd every second time.

* Skale: 0% (=mute) to 100%

<a name="layer-3-step-mute"></a>
### Step Mute 
Mutes a step row.

<a name="layer-3-start-position"></a>
### Start Position 

At the step there you set the Start Position the bar playback will be begin. 
If you e.g. set the third step (like on the picture above) as Start Position the bar playback will be started at step three and not at step one.
But this Start Position will be invalidated after it's first playback. Read the next [Restart Position](#layer-3-restart-position)...

A defined Start Position will be marked at the Runlight as ">>". This label is a playback label that will be shown for the currently playing bar.

<a name="layer-3-restart-position"></a>
### Restart Position 

If your playback reach a defined Restart Position the current playback position will be setted to step one of this bar (A defined [Start Position](#layer-3-start-position) will be ignored!) (
Exception: If step one is setted to skip it will be the next unskipped step in this bar). Also will be an used Restart Position invalidated and next time you will overun this position. 

A defined Restart Position will be marked at the Runlight as "<<". This label is a playback label that will be shown for the currently playing bar and will be removed if it is invalidated.

<a name="layer-3-force-position-to-beat"></a>
### Force Position to Beat 

When you use the features [Restart Position](#layer-3-restart-position) and [Start Position](#layer-3-start-position) you are moving you playback position away from the main beat 
(e.g. another sequencer or a drum computer). To get back to the main beat you can where ever you want set a Force Position to Beat. If you reach such a point in your bar playback the current
playback pos will be settet to the main beat (this ignores [Restart Position](#layer-3-restart-position) and [Start Position](#layer-3-start-position), but not [Step Skip](#layer-3-step-skip)).

<a name="layer-3-step-skip"></a>
### Step Skip 

A skipped step is explicitly excluded from this bar sequence and will reduce the bar playback time. If you e.g. skip 4 step in a bar you change it's measurement from a 4/4 bar to and 3/4 bar.

A defined Step Skip will be marked at the Runlight as "S". This label is not a playback label and will be shown for the currently editable/selected bar!


<br /> [back to top](#content) </div><div class="manual">


[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
[//]: <> ( Layer 4 )
[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
<a name="layer-4"></a>
## Layer B (4th) - Bar Playback Features
On the B layer you have a bunch of features to go away from the liniar bar by bar playback.

![B-Step Sequencer - Bar Playback Features](http://b-step.monoplugs.com/manual/images/b-step-sequencer-layer-4.gif)

**Feature Overview:**

* [Play Reverse](#layer-4-play-reverse) 
* [<< Steps >> - Move your Steps in the Bar around](#layer-4-move-steps) 
* [Force Bar 2 Chain](#layer-4-force-bar-2-chain)
* [Restart Sequence](#layer-4-restart-sequence)
* [Bar Skip](#layer-4-bar-skip)

<br />
[back to top](#content)
<hr>

<a name="layer-4-play-reverse"> </a>
### Play Reverse

Simply starts the playback of this bar at step 16 and will go to step 1. All other playback features in this bar will be also inverted (see [Layer NL](#layer-3)).

<a name="layer-4-move-steps"></a>
### << Steps >> - Move your steps in the bar around 

You can move the steps of your bar - this only move the step trigger points and not it's settings over the layers. Turn around.

* Skale: -15 to + 15

<a name="layer-4-force-bar-2-chain"></a>
### Force Bar 2 Chain 

Add an empty bar to the chain. Will add a "-" label to it's [Bar Selection](#bar-selection-and-bar-copy) button. 

<a name="layer-4-restart-sequence"></a>
### Restart Sequence 

Similar to [Restart Position](#layer-3-restart-position) inside a bar, but for a bar in the sequence. Adds a "<<" label to it's [Bar Selection](#bar-selection-and-bar-copy) button. 

<a name="layer-4-bar-skip"></a>
### Bar Skip 

Explicitly exclude a bar from the chain. Adds a "S" label to it's [Bar Selection](#bar-selection-and-bar-copy) button. 


<br /> [back to top](#content) </div><div class="manual">


[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
[//]: <> ( Sequence Groups - Layer 4 )
[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
<a name="layer-4-sequence-groups"></a>
## Sequence Groups - One Sequencer is not enough? 
You can split B-Step in up to 4 independent sequencers which only share the [Global Parameters](#global-functions).

Basically each sequence works like a single B-Step - you can define [Bar Solo](#bar-solo)'s, you can use [Restart Sequence](#layer-4-restart-sequence) 
and you can choose a separate MIDI output for each or use the master output (default).

**The Goals:** 

* drag'N'drop bars from one to another sequencer
* move a bar from one to another sequence on the fly
* you do not need 2, 3 or 4 instances of B-Step

<a name="layer-4-define-sequence-groups"></a>
### Define Sequence Groups 
![B-Step Sequencer - Sequences](http://b-step.monoplugs.com/manual/images/b-step-sequencer-layer-4-sequences.gif)

With the sequence# sliders you can set for each bar a sequence group (by default all of the bars are in sequence one). 
Each sequence group has it own runtime colour (beige, green, yellow and blue) and the Bar Solo buttons shows in which sequence a bar is 
("|2|", "|3|", "|4|", no label = sequence 1).

The playback infos in the step runlight will be shown from the currently editable bar's sequence group. If e.g. a bar from sequence two is 
editable your step runlight will be become green and the playback infos are from sequence two.

* Skale: 1 to 4

<hr>

<a name="layer-4-sequence-number"></a>
### Sequence MIDI Output Settings - Control up to 4 Synths 
![B-Step Sequencer - Sequence Settings](http://b-step.monoplugs.com/manual/images/b-step-sequencer-layer-4-sequences-settings.gif)

To set an extra output for a sequence you have to choose your port and channel at the bottom of the IO settings editor. 
If "Use Master Out" is selected all the events will be send to the Master Out which is defined at the top.


<br /> [back to top](#content) </div><div class="manual">


[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
[//]: <> ( Layer 5 )
[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
<a name="layer-5-sequencer-ratcheting"></a>
## Step repeats, Ratcheting - what is that?
Take just one enabled step and trigger it again and again after a time X.

B-Step revolutionize sequencer ratcheting and give you a couple of options to modify your step repeat individually! 
You can change the distance between each repeat, you can change the duration for each triggered note or you can change the 
note value on each repeat!

**FREESTYLE!**

We recommend to start with this feature without reading this part and come back later to make your very own experience! 
Take a clean bar, enable a step and start repeating them by setting the number of repeats higher than 0 - take 4 or 8 to start!
All sliders at this step row on Layer R1 and R2 will modify this repeat! 
Have fun, listen what happens and see you later!

<hr>

<a name="layer-5"></a>
## Layer R1 (5th) - Repeats, Ratcheting 1
![B-Step Sequencer - Sequencer Ratcheting](http://b-step.monoplugs.com/manual/images/b-step-sequencer-layer-5.gif)

**Feature Overview:**

* [Step Repeats](#layer-5-repeats) 
* [Don't Roll Repeat](#layer-5-repeats-do-not-roll) 
* [Repeat Interval](#layer-5-repeat-interval)
* [Repeat Interval Offset](#layer-5-repeat-interval-offset)
* [Repeat Duration Offset](#layer-5-repeat-duration-offset)
* [Skip Repeat](#layer-5-repeat-skip)

<br />
[back to top](#content)
<hr>

**Video:** <a href="javascript:show_fancy_video('http://www.youtube-nocookie.com/embed/yhR2yqdKzk0?autoplay=1')">Sequencer Ratcheting with B-Step</a> <br />
**Video:** <a href="javascript:show_fancy_video('http://www.youtube-nocookie.com/embed/SPEdBFOirkg?autoplay=1')">How to make a swinging arpeggio</a>

<hr>

<a name="layer-5-repeats"></a>
### Step Repeats 

Define how many repeats this step will have. 

* Skale: 0 to 8

<a name="layer-5-repeats-do-not-roll"></a>
### Don't Roll Repeat 

If enabled the sequencer will stay on this step until the last repeat is triggerd.

<a name="layer-5-repeat-interval"></a>
### Repeat Interval 

The distance between each repeat.

 <font color="#736AFF">
 <u>&nbsp;&nbsp;&nbsp;</u>I<span style="border-top:1px solid">&nbsp;Step&nbsp;</span>I<u>
 <-int->&nbsp;</u>I<span style="border-top:1px solid">&nbsp;Rpt1&nbsp;</span>I<u>
 <-int->&nbsp;</u>I<span style="border-top:1px solid">&nbsp;Rpt2&nbsp;</span>I<u>
 <-int->&nbsp;</u>I<span style="border-top:1px solid">&nbsp;Rpt3&nbsp;</span>I<u>
 &nbsp;&nbsp;</u>
 </font>

* Skale: 1/96th to 1/8th (default 1/16th)

<a name="layer-5-repeat-interval-offset"></a>
### Repeat Interval Offset 

Increase or decrease the interval per repeat.

**Example:** We increase the interval by 1/16th.
The first repeat will be triggered after the root step after the defined [Repeat Interval](#layer-5-repeat-interval). The second repeat will be triggered after the defined [Repeat Interval](#layer-5-repeat-interval) plus 1/16th.

 <font color="#736AFF">
 <u>&nbsp;&nbsp;&nbsp;</u>I<span style="border-top:1px solid">&nbsp;Step&nbsp;</span>I<u>
 <-int->&nbsp;</u>I<span style="border-top:1px solid">&nbsp;Rpt1&nbsp;</span>I<u>
 <-int-++++++->&nbsp;</u>I<span style="border-top:1px solid">&nbsp;Rpt2&nbsp;</span>I<u>
 <-int-++++++++++++->&nbsp;</u>I<span style="border-top:1px solid">&nbsp;Rpt3&nbsp;</span>I<u>
 &nbsp;&nbsp;</u>
 </font>

* Skale: -1/8th to 1/8th per repeat

<a name="layer-5-repeat-duration-offset"></a>
### Repeat Duration Offset 

Increase or decrease the duration of each repeat.

**Example:** We increase the duration by 1/16th.
The first triggered repeat will have the root Step Duration plus 1/16th.The second repeat will have the root step duration plus 1/16th plus 1/16th.

 <font color="#736AFF">
 <u>&nbsp;&nbsp;&nbsp;</u>I<span style="border-top:1px solid">&nbsp;Step&nbsp;</span>I<u>
 <-int->&nbsp;</u>I<span style="border-top:1px solid">&nbsp;Rpt1-++++++&nbsp;</span>I<u>
 &nbsp;&nbsp;</u>
 </font>

* Skale: -1/8th to 1/8th per repeat

<br />
**Note**: The duration offset has no influence to the [Repeat Interval](#layer-5-repeat-interval) or [Repeat Duration Offset](#layer-5-repeat-duration-offset) and will not shift any repeat trigger point!

<a name="layer-5-repeat-skip"></a>
### Skip Repeat 

If enabled the repeat will not triggerd. So no need to change the [Step Repeats](#layer-5-repeats) to zero if you not need this repeat at the moment.


<br /> [back to top](#content) </div><div class="manual">


[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
[//]: <> ( Layer 6 )
[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
<a name="layer-6"></a>
## Layer R2 (6th) - Repeats, Ratcheting 2
![B-Step Sequencer - Repeats, Sequencer Ratcheting](http://b-step.monoplugs.com/manual/images/b-step-sequencer-layer-6.gif)

**Feature Overview:**

* [Step Repeats](#layer-6-repeats) 
* [Repeat Velocity Offset](#layer-6-repeats-velocity-offset) 
* [Repeat Note Offset](#layer-6-repeat-note-offset)
* [Note up'N'down](#layer-6-note-up-and-down)
* [Free Notes](#layer-6-repeat-free-notes)
* [Repeat Probability](#layer-6-repeat-probability)

<br />
[back to top](#content)
<hr>

<a name="layer-6-repeats"></a>
### Step Repeats 

Is the same feature: [Step Repeats](#layer-5-repeats) on Layer R1.

<a name="layer-6-repeats-velocity-offset"></a>
### Repeat Velocity Offset 

Similar to [Repeat Duration Offset](#layer-5-repeat-duration-offset), but in- or decrese the velocity for each repeat.

* Skale: -16 to 16

<a name="layer-6-repeat-note-offset"></a>
### Repeat Note Offset 

Similar to [Repeat Duration Offset](#layer-5-repeat-duration-offset), but in- or decrese the step root note value by halftones for each repeat. 

<br />
**Note:** When you use Note Offsets by default B-Step does not simply use Step Note value plus Repeat Note Offset. No, B replace the resulting note value by the next matching value of your choosen Bar Chord or a transponation of it - so you can be sure that the note ratcheting will always sound well to the other steps of your bar. To disable this you can use [Free Notes](#layer-6-repeat-free-notes).

* Skale: -12 to 12 (in halftones)

<a name="layer-6-note-up-and-down"></a>
### Note up'N'down 

If you use [Repeat Note Offset](#layer-6-repeat-note-offset) every repeats note will be in- or decreased. With this option you can make a mix of it. 

**Example Setup:**
 
* [Step Repeats](#layer-6-repeats) = 4
* root step notevalue = 60
* [Repeat Note Offset](#layer-6-repeat-note-offset) = 2
* [Note up'N'down](#layer-6-note-up-and-down) = enabled
* [Free Notes](#layer-6-repeat-free-notes) = enabled

**Result:**

* root step will be triggerd with note value 60
* 1st repeat has 62
* 2nd repeat has 56
* 3rd repeat has 66
* 4th repeat has 52

<a name="layer-6-repeat-free-notes"></a>
### Free Notes 

Disables the lookup for best matchin notes (explained in [Repeat Note Offset](#layer-6-repeat-note-offset)).

<a name="layer-6-repeat-probability"></a>
### Repeat Probability

The probability off any repeat steps. If you e.g. set it to 50% only every second repeat step will be triggerd (in theory).

* Skale: 0% to 100%


<br /> [back to top](#content) </div><div class="manual">


[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
[//]: <> ( Layer 7 )
[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
<a name="#layer-7"></a>
## Layer CC (7th) - Control and Program Changes
![B-Step Sequencer - Send Control Changes and Programm Changes](http://b-step.monoplugs.com/manual/images/b-step-sequencer-layer-7.gif)

**Feature Overview:**

* [Send Program Changes](#layer-7-send-programm-changes) 
* [Send Control Changes](#layer-7-send-control-changes)

<br />
[back to top](#content)
<hr>

<a name="layer-7-send-programm-changes"></a>
### Send Program Changes 

Select your program with the "Program Change"-slider and enable the "Send PC"-button to realy send it.

* Skale: 1 to 128

<a name="layer-7-send-control-changes"></a>
### Send Control Changes 

Select your controller number on the left side, define a controller value for each step and do realy send it enabeling the "Send CC"-button. With the second controller columns you can do the same.

* Skale: 1 to 128


<br /> [back to top](#content) </div><div class="manual">


[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
[//]: <> ( Snapshots Clipboard )
[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
<a name="clipboard-sanpshots"></a>
## Snapshots and the Clipboard 
![B-Step Sequencer - Snapshot](http://b-step.monoplugs.com/manual/images/b-step-sequencer-bar-snapshot.gif)

<a name="clipboard"></a>
### The Clipboard 
You can store any bar you like in one of the four clipboards for later use. To store a bar to the clipboard drag and drop it to one of the four clipboards on the right bottom.
This will make a copy of your dropped bar. To copy the stored bar back to the sequence you do the same, but start the dragging from the clipboard icon.

The goal of the clipboard: you can define what you like to copy back from the stored bar. Just click on the clipboard and set up which data you need on a back copy.
If you e.g. just need the enabled steps -> deselect all (push select all two times) and select "copy steps", then drag and drop the stored bar to your target bar.

**Tip:** Mixing projects: store a bar or more to the clipboards and load another project - now you can simply import the stored bars to the other project.

<br />
**Note:** The clipboard will not stored to disk, it is just in the runtime memory!

<a name="snapshots"></a>
### Snapshots 
If you like you can im- and export bars over the load save function on the clipboard editor to use it in this or other projects.

<br />
**Note:**: The whole bar will be im- and exported whatever you have selected at the copy options!


<br /> [back to top](#content) </div><div class="manual">


[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
[//]: <> ( Keyboard )
[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
<a name="keyboard-control"></a>
## Keyboard Layout 

* Space: start, stop
* Play/Stop Key: start, stop
* Curser up/down: switch layers
* Curser left/right: switch editable bar
* Number 1 to 10 (0): select editable bar 1 to 10
* F1 to F16: select editable bar 1 to 16


<br /> [back to top](#content) </div><div class="manual">


[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
[//]: <> ( MIDI LEARN )
[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
<a name="midi-learn"></a>
##  MIDI Learn 
<a name="midi-learn-connect-controller"></a>
###  How to connect your Controller 
![B-Step Sequencer - Connect a MIDI Controller](http://b-step.monoplugs.com/manual/images/b-step-sequencer-connect-midi-controller.gif)

Connect your MIDI conroller to your computer or tablet and open B-Step's IO settings. Select your controller at Receive 
Port to control B-Step. If your controller supports any feedback feature then you can select them at the Feedback port.

**Windows:** If you are using B-Step as VST plugin in a DAW you may be have some trouble because our DAW may be already 
"owns" your controller. You can try to connect your controller after booting your DAW or have a look at this thread: 
<a href="http://forum.monoplugs.com/viewtopic.php?f=54&t=623" title="Windows virtual MIDI" target="_blank">Windows virtual MIDI</a>

<br />
[back to top](#content)
<hr>

<a name="midi-learn-how-to-train"></a>
### How to train a MIDI Controller 
![B-Step Sequencer - MIDI Controller](http://b-step.monoplugs.com/manual/images/b-step-sequencer-learn-midi-controller.gif)

You can switch to MIDI learn mode by open the MIDI learn editor. Every trainable element will be grey and become a trainee 
by touch or click it. When you have selected a trainee you have to move/push the sliders/buttons on your MIDI controller 
(the last received controller number will be shown in the trainee marker). From now the trainee/receiver will be listen to 
your last changed controller number. Done.

As controller you can use any note or cc events all other will be ignored!

To exit the learn mode you have to close the MDI learn editor.

<a name="midi-feedback"></a>
### Controller Feedback 
Feedback will be send to every assigned controller. The refresh rate is about 30ms. See also: [How to connect your Controller](#midi-learn-connect-controller"). 

**Note:** If you have assigned a controller to more than one receiver (see [Learn Modes](#midi-learn-modes) - n:1, n:n) 
the feedback from the last trained patch will be send to your controller. 

<a name="midi-learn-modes"></a>
### Learn Modes 

**1:1 (default mode):** 
<br>A controller can only have one receiver and a receiver can only have one controller. That means if you assign a new 
controller to a receiver that already have a controller the old controller will be replaced by the new one and any other 
receiver that listen to the new controller will stop listen to!


**What can I do with: 1:n, n:1 or n:n?**

This modes especially the "1:n" gives you the posibility to train patterns that you can set by one controller action. 
E.g. assign a bunch of steps to one button at you midi controller and enable or disable all of them by one button push 
on your controller. 

Watch this video: <a href="javascript:show_fancy_video('http://www.youtube-nocookie.com/embed/LRdx88lFwzQ?autoplay=1')"> MIDI Learn - Mode 1:n</a>.

**1:n**
<br>A controller can have unlimited receivers. A new controller assignment will replace all other controllers to which 
the receiver listen to, but it does not remove this controller at any other receiver.

**n:1**
<br>A reciver can have unlimited controllers. So a new controller assignment will not replace the controllers to that 
the reciver already listen, but no other reciver will listen to this controller anymore.

**n:n:**
<br>Any receiver can listen to any controller and any controller can control any receiver. A new assignment will nothing 
change at any other patch that you have already created.

<a name="midi-learn-load-save"></a>
### Load/Save Controller Maps 

Read this section: [Load/Save Projects](#load-save-project).


<br /> [back to top](#content) </div><div class="manual">


[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
[//]: <> ( AS Controller )
[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
[//]: <> ( ## Use B-Step as MIDI Controller from your iPad or Android Tablet <a name="as-midi-controller"></a> )
[//]: <> ( ![B-Step Sequencer - MIDI Controller](http://b-step.monoplugs.com/manual/images/b-step-sequencer-as-midi-controller.gif) )
[//]: <> ( )
[//]: <> ( To use B-Step Sequencer just as MIDI controller load the "Default-Map.b2patch" and assign that software or device that you like to control at the MIDI learn In- and Out's (see [How to connect your Controller](#midi-learn-connect-controller)). )
[//]: <> ( )
[//]: <> ( In the "Default-Map.b2patch" is to every user interface element (which is learnable) a controller assigned. We don't know how your software or device works, please check it's manual )
[//]: <> ( how you can train a MIDI controller to it. )
[//]: <> ( )
[//]: <> ( <br /> [back to top](#content) </div><div class="manual"> )

[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
[//]: <> ( Host Automation )
[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
[//]: <> ( ## Host Automation - only VST and AudioUnit <a name="automation-parameters"></a> )
[//]: <> ( <br /> [back to top](#content) </div><div class="manual"> )


[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
[//]: <> ( Launchpad )
[//]: <> ( *********************************************************** )
[//]: <> ( *********************************************************** )
<a name="novation-launchpad"></a>
## Novation Launchpad 
**Video:** <a href="javascript:show_fancy_video('http://www.youtube-nocookie.com/embed/NanpC1VpuCQ?autoplay=1')"> Novation Launchpad & B-Step video tutorial</a>

<a name="how-to-connect-novation-launchpads"></a>
###  How to connect the Launchpads 
![B-Step Sequencer - Novation Launchpad](http://b-step.monoplugs.com/manual/images/b-step-sequencer-connect-novation-launchpad.gif)

Connect your Launchpad(s) to your computer or tablet and open B-Step's IO settings. Select your Launchpad(s) MIDI in and OUT at channel 1. Your Launchpad should show some lightning buttons (if not try "Refresh"). Done.

**Windows:** If you are using B-Step as VST plugin in a DAW you may be have some trouble because our DAW may be already "owns" the Launchpad. You can try to connect your Launchpad after booting your DAW or have a look at this thread: <a href="http://forum.monoplugs.com/viewtopic.php?f=54&t=623" title="Windows virtual MIDI" target="_blank">Windows virtual MIDI</a>

<br />
[back to top](#content)
<hr>

<a name="view-8-steps-recommend-if-you-use-one-launchpad"></a>
### View 8 Steps (recommend if you use one Launchpad) 
#### Page 1
![B-Step Sequencer Novation Launchad feature View 8 Steps, Page 1](http://b-step.monoplugs.com/manual-old/images/launchpad_page-1_8-step-view.png)
#### Page 2
![B-Step Sequencer Novation Launchad feature View 8 Steps, Page 2](http://b-step.monoplugs.com/manual-old/images/launchpad_page-2_8-step-view.png)

<br />
[back to top](#content)
<hr>

<a name="view-left-side-left-launchpad-if-you-use-two"></a>
### View Left Side (Left Launchpad if you use two) 
#### Page 1
![B-Step Sequencer Novation Launchad feature View Left, Page 1](http://b-step.monoplugs.com/manual-old/images/launchpad_page-1_left-view.png)
#### Page 2
![B-Step Sequencer Novation Launchad feature View Left, Page 2](http://b-step.monoplugs.com/manual-old/images/launchpad_page-2_left-view.png)

<br />
[back to top](#content)
<hr>

<a name="view-right-side-right-launchpad-if-you-use-two"></a> 
### View Right Side (Right Launchpad if you use two) 
#### Page 1
![B-Step Sequencer Novation Launchad feature View Right, Page 1](http://b-step.monoplugs.com/manual-old/images/launchpad_page-1_right-view.png)
#### Page 2
![B-Step Sequencer Novation Launchad feature View Right, Page 2](http://b-step.monoplugs.com/manual-old/images/launchpad_page-2_right-view.png)


<br /> [back to top](#content) </div><div class="manual">


<a name="outro"></a> 
### QUESTIONS, see you in  B-Step Forum  
Any questions, come to B-Step forum, [ask there](http://forum.monoplugs.com), writing to which chapter of this manual your question is related to, 
so your question plus its answer can be added into the next version of this manual. Thanks in advance. Now enjoy B-Step and your other great musical tools.


<br /> [back to top](#content) </div><div class="manual">

<a name="thanks"></a>
## SPECIAL THANKS 
- Daniel Sticherling
- Anne Dietrich | <a href="http://www.mohiniyattam.de" target="_blank">Mohiniyattam - Classical Indian Dance</a>
- TonE
- Rob Kittredge
- Sunray
- Soundklinik
- Wolfram Niessen
- Tim Charlemagne | <a href="http://www.soundmanufacture.net" target="_blank">Sound Engineering / Sounddesign</a>
- MrLucmorin
- Mr Traxx
- Moogulator | <a href="http://moogulator.com/moogulator/" target="_blank">Electronic Music Performer</a> 
- Scott George | <a href="http://cats.org" target="_blank">Abstract Cats. cats.org</a>
- Alex Fellows
- Jana Schmück | <a href="http://jana-schmueck.de/" target="_blank">Dancer, Choreographer & Dipl Tanzpädagogin</a> 
- Enrico Wetzel
- Melanie Leuchtman
- Patrick Lindner
- Marcus George
- Dieter Steffman | <a href="http://www.steffmann.de/wordpress" target="_blank">Typographer - Font Designer</a>

<br /> [back to top](#content) </div><div class="manual">

<a name="changelog"></a>
### Changelog

#### B-Step Sequencer 2.0.1; 2.0.2
    27th / 29th of May 2014 
    
- Add: Update notifier
- Fix: AudioUnit validation fails
- Fix: Was not working in FL Studio
- Fix: Chord sets was not loaded correctly with a project
- Fix: Chord set im- export bug
- Fix: Load project bug
- Fix: Step probability was broken
- Fix: Video links in help popup
- Fix: Install location linux
- Fix: A preset in the plugin trial was not loaded by default.

### B-Step Sequencer 2 - 24th of October 2014

##### New Supported Platforms:

- Android.
- Raspberry Pi.

##### New Supported Plugin Standards:

- Audio Unit.

##### New Features Overview:

- Add Sequencer Ratcheting.
- Add 4 more MIDI out to control up to 5 synths.
- Add Shuffle features.
- Add drum support.
- Add 6 layers with a bunch of features.
- Add random chords from scales.
- Add monophon and polyphon playback modes.
- Add new presets.
- Improve the user interface style.
- Add snapshot functionality.
- Redesigned MIDI learn feature.
- Add multidrag feature.
- Add snapshot feature.
- Add rubber tool.
- Add inline manual functionality.
- Move BPM slider to the main user interface.
- Add custom measurements from 1/16th per bar to much more than 4/4th.
- Change solo bar to solo bar groups.
- Add control and program changes per step.
- Fix known bugs like sync problems and improve them.

##### Some new Feature Details:

- Octave per step.
- Chords per step.
- Microtiming per step (delay).
- Step copy.
- Step probability.
- Step mute.
- Step skip.
- Custom playback features per bar.
- Custom playback features per global sequence.
- Reverse Playback.
- Moving steps in the pattern.
- Bar skip.
- CC and PC per step.

##### Sequencer Ratcheting in Detail:

- Modulate interval.
- Modulate duration.
- Modulate velocity.
- Modulate notes.
- Modulate probability.

##### Shuffle in Detail:

- Per 16th, 8th or 4th.
- Modulate velocity.
- Modulate duration.
- Modulate timing.

<br />
[back to top](#content)
<hr>

#### B-Step Sequencer 1.2.1, 1.2.2 & V1.2.3 (iPad only)
    22th of May 2014 

- User interface performance boost.
- Fix timing issues.
- Fix app switching breaks.
- Fix MIDI sync (as master).
- Fix MIDI playback stops if Audiobus app is running.
- Remove next bar in chain marker.
- Other small user interface changes.
- Add delete and browse functions to the file chooser.

<br />
[back to top](#content)
<hr>

#### B-Step Sequencer 1.2
    15th of April 2014

##### Fixes:
- Stop all playing notes if playback stops.
- Add Error messages if a MIDI port is not able to open.
- MIDI learn map will not loaded correctly.
- MIDI Thru bug.
- Restore MIDI ports on reopen B-Step.

##### Sequencer Settings:
- Add clock thru option in standalone.

##### Presets:
- Add export/import project files.
- Add export/import chord presets.
- Add export/import MIDI maps.
- Add some project presets & chord presets.

##### Sequencer Features:
- Add mute-chain | you can now play empty bars or mute a bar in the chain.
- Add master track octave offset rotaries.
- Add what's the next bar in the chain marker.
- Add panic button.

##### MIDI learn (new design):
- Add Feedback.
- Change the editor layout and MIDI learn handling.

##### User Interface:
- Clean up settings editor.
- Clean up main interface.
- Add tree different colour setups.
- Remove step was enabled marker.

##### Novation Launchpad:
- Add bar copy support (hold down one bar button (source) and click a other bar button (target) ).
- Change default MIDI channel to 1.

<br />
[back to top](#content)
<hr>

#### B-Step Sequencer 1.1
    14th of February 2014

##### OS:
* Add support for OS X 10.5 to 10.8 (Intel).

##### Hosts:
- List as instrument in Ableton Live.
- Remove support on OS X for Cubase (unsolved problems).

##### Settings:
- Add settings editor for MIDI IO.
- Add pop up for manage MIDI learn.

##### Programming/Handling:
- Add chord editor.
- Increase to max 8 repeats per bar (from 4).
- The target bar will be the selected after drag'n'drop.
- Bar-repeats, bar-offset, bar-octave will be no more copied by drag'n'drop.

##### Timing:
- Fix timing bug (VST).

##### Launchpads:
- Improved the complete launchpad map.
- Add external MIDI port handling to manage MIDI IO.

##### MIDI learn:
- Add multiple controller assignments.
- Add support for notes as controller.

##### User Interface:
- Add slider to control all duration sliders.
- Add slider to control all velocity sliders.
- Reduce UI refresh rate, feels less laggy.
- Add auto resize if the desktop area is to small.

<br />
[back to top](#content)
<hr>

#### B-Step Sequencer 1.0 - 23th of December 2013

- Release.


<br /> [back to top](#content) </div><div class="manual">


#### COPYRIGHT
VST is a trademark of Steinberg Media Technologies GmbH.<br />
AudioUnits is a trademark of Apple Computer, Inc.