#!/bin/sh
echo "convert eol to LF"
juce/Introjucer.app/Contents/MacOS/Introjucer --trim-whitespace Source
juce/Introjucer.app/Contents/MacOS/Introjucer --remove-tabs Source
