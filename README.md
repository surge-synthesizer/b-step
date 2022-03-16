This is in a private surge synth team repo for now because

1. I haven't scanned the resources for open 
2. I haven't set up the CLA
3. and I haven't done anything else even like that

but I wanted it up on git


# An important note about licensing

Just like with the rest of our team projects, we welcome any and all contributions from anyone who wants
to work on open source music software.

At the initial open-sourcing, the copyright to the Monique source was held by Thomas. When open sourcing,
we had several projects - including a potential iOS port - which meant we had to think hard about licensing.

As such, we have decided that Monique should be dual licened GPL3 and MIT. In some contexts, such as the
binaries which you will one day be able to download here for linux, mac, and windows, we are using the GPL3
version of JUCE, but we may want to also release in situations where open source is still possible, but GPL3
is not, and then want to use the MIT license.

As a result, we are asking individual contributors who want to contribute to Monique Mono-Synth to sign a CLA.
We have used the Canonical/Harmony 1.0 CLA http://selector.harmonyagreements.org with the following choices:

1. You retain copyright to your code. *We do not need you to assign copyright to us*.
2. You grant us a license to distribute your code under GPL3 or MIT; and your content under CC3 attribution

You can read the entire document [here](BStepCLA.pdf).

To agree to this document,
please add your name to the `AUTHORS` list in a git transaction where you indicate in the git log message
that you consent to the CLA. You only need to do this once, and you can do it in your first commit to the repo.
