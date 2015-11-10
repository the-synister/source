echo "convert eol to CRLF"
"juce\The Introjucer.exe" --trim-whitespace Source
"juce\The Introjucer.exe" --remove-tabs Source
pause