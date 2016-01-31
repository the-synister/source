/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#ifndef BINARYDATA_H_120220767_INCLUDED
#define BINARYDATA_H_120220767_INCLUDED

namespace BinaryData
{
    extern const char*   berlin_sans_demi_bold_ttf;
    const int            berlin_sans_demi_bold_ttfSize = 96852;

    extern const char*   glow_png;
    const int            glow_pngSize = 3049;

    extern const char*   vertical_slider_png;
    const int            vertical_slider_pngSize = 625;

    extern const char*   knobstrip_png;
    const int            knobstrip_pngSize = 160459;

    extern const char*   slider_thumb_png;
    const int            slider_thumb_pngSize = 4265;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 5;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}

#endif
