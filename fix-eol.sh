#!/bin/sh
echo "convert eol to LF"
juce/Introjucer.app/Contents/MacOS/Introjucer --trim-whitespace gui
juce/Introjucer.app/Contents/MacOS/Introjucer --remove-tabs gui
juce/Introjucer.app/Contents/MacOS/Introjucer --trim-whitespace audio
juce/Introjucer.app/Contents/MacOS/Introjucer --remove-tabs audio
