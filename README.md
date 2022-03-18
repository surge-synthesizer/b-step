# B-Step Sequencer

The B-Step Sequencer is a midi generating plugin and program which was originally authored by
Monoplugs and its principal Thomas Arndt. In March of 2022, after he had open sourced Monique
with the Surge team, Thomas donated the B-Step source to the Surge Synth Team.

Currently, we are seeing if it is even tractable to restore this program, although we do
have it at least compiling. If you are a developer and would like to work on B-Step, please
do get in touch!

Standard build instructions for the rest of the Surge Synth Team plant apply here too.

```
git clone https://github.com/surge-synthesizer/b-step
cd b-step
git submodule update --init --recursive
cmake -Bignore/build 
cmake --build ignore/build
```

As of now we haven't done any of the cmake work we have in our other synths, so the
VST3 and stuff will end up in places which will change, and there's no installer
or downloadable asset. But we'll get there!! Probably! We think. Perhaps?

# An important note about licensing

Just like with the rest of our team projects, we welcome any and all contributions from anyone who wants
to work on open source music software.

At the initial open-sourcing, the copyright to the B-Step source was held by Thomas. When open sourcing,
we had several projects - including a potential iOS port - which meant we had to think hard about licensing.

As such, we have decided that B-Step should be dual licened GPL3 and MIT. In some contexts, such as the
binaries which you will one day be able to download here for linux, mac, and windows, we are using the GPL3
version of JUCE, but we may want to also release in situations where open source is still possible, but GPL3
is not, and then want to use the MIT license.

As a result, we are asking individual contributors who want to contribute to B-Step to sign a CLA.
We have used the Canonical/Harmony 1.0 CLA http://selector.harmonyagreements.org with the following choices:

1. You retain copyright to your code. *We do not need you to assign copyright to us*.
2. You grant us a license to distribute your code under GPL3 or MIT; and your content under CC3 attribution

You can read the entire document [here](BStepCLA.pdf).

To agree to this document,
please add your name to the `AUTHORS` list in a git transaction where you indicate in the git log message
that you consent to the CLA. You only need to do this once, and you can do it in your first commit to the repo.
