# Automatically generated makefile, created by the Projucer
# Don't edit this file! Your changes will be overwritten when you re-save the Projucer project!

# build with "V=1" for verbose builds
ifeq ($(V), 1)
V_AT =
else
V_AT = @
endif

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifndef STRIP
  STRIP=strip
endif

ifndef AR
  AR=ar
endif

ifndef CONFIG
  CONFIG=Debug
endif

ifeq ($(CONFIG),Debug)
  JUCE_BINDIR := build
  JUCE_LIBDIR := build
  JUCE_OBJDIR := build/intermediate/Debug
  JUCE_OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -m32
  endif

  JUCE_CPPFLAGS := $(DEPFLAGS) -DLINUX=1 -DDEBUG=1 -D_DEBUG=1 -DJUCER_LINUX_MAKE_982F74FC=1 -DJUCE_APP_VERSION=1.0.2 -DJUCE_APP_VERSION_HEX=0x10002 $(shell pkg-config --cflags alsa freetype2 libcurl x11 xext xinerama) -pthread -I../../../JuceLibraryCode -I../../../../../JUCE/modules -I../../../../gui -I../../../../audio/inc $(CPPFLAGS)
  JUCE_CFLAGS += $(JUCE_CPPFLAGS) $(TARGET_ARCH) -g -ggdb -fPIC -O0 $(CFLAGS)
  JUCE_CXXFLAGS += $(JUCE_CFLAGS) -std=c++11 $(CXXFLAGS)
  JUCE_LDFLAGS += $(TARGET_ARCH) -L$(JUCE_BINDIR) -L$(JUCE_LIBDIR) -Wl,--no-undefined -shared $(shell pkg-config --libs alsa freetype2 libcurl x11 xext xinerama) -ldl -lpthread -lrt  $(LDFLAGS)

  TARGET := synister_x32.so
  BLDCMD = $(CXX) -o $(JUCE_OUTDIR)/$(TARGET) $(OBJECTS) $(JUCE_LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(JUCE_OUTDIR)/$(TARGET) $(JUCE_OBJDIR)
endif

ifeq ($(CONFIG),Release)
  JUCE_BINDIR := build
  JUCE_LIBDIR := build
  JUCE_OBJDIR := build/intermediate/Release
  JUCE_OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -m32
  endif

  JUCE_CPPFLAGS := $(DEPFLAGS) -DLINUX=1 -DNDEBUG=1 -DJUCER_LINUX_MAKE_982F74FC=1 -DJUCE_APP_VERSION=1.0.2 -DJUCE_APP_VERSION_HEX=0x10002 $(shell pkg-config --cflags alsa freetype2 libcurl x11 xext xinerama) -pthread -I../../../JuceLibraryCode -I../../../../../JUCE/modules -I../../../../gui -I../../../../audio/inc $(CPPFLAGS)
  JUCE_CFLAGS += $(JUCE_CPPFLAGS) $(TARGET_ARCH) -fPIC -O3 $(CFLAGS)
  JUCE_CXXFLAGS += $(JUCE_CFLAGS) -std=c++11 $(CXXFLAGS)
  JUCE_LDFLAGS += $(TARGET_ARCH) -L$(JUCE_BINDIR) -L$(JUCE_LIBDIR) -Wl,--no-undefined -shared -fvisibility=hidden $(shell pkg-config --libs alsa freetype2 libcurl x11 xext xinerama) -ldl -lpthread -lrt  $(LDFLAGS)

  TARGET := synister_x32.so
  BLDCMD = $(CXX) -o $(JUCE_OUTDIR)/$(TARGET) $(OBJECTS) $(JUCE_LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(JUCE_OUTDIR)/$(TARGET) $(JUCE_OBJDIR)
endif

OBJECTS := \
  $(JUCE_OBJDIR)/FoldablePanel_e65a70ea.o \
  $(JUCE_OBJDIR)/EnvelopeCurve_961ea700.o \
  $(JUCE_OBJDIR)/CustomLookAndFeel_4e23e34e.o \
  $(JUCE_OBJDIR)/IncDecDropDown_eb6dd87e.o \
  $(JUCE_OBJDIR)/WaveformVisual_b06529c6.o \
  $(JUCE_OBJDIR)/InfoPanel_325825ff.o \
  $(JUCE_OBJDIR)/ChorusPanel_8af55b07.o \
  $(JUCE_OBJDIR)/ClippingPanel_49f61a6b.o \
  $(JUCE_OBJDIR)/LoFiPanel_af43e007.o \
  $(JUCE_OBJDIR)/EnvPanel_906d1578.o \
  $(JUCE_OBJDIR)/FiltPanel_83223dc2.o \
  $(JUCE_OBJDIR)/FxPanel_66c36b5b.o \
  $(JUCE_OBJDIR)/Env1Panel_9ccdd289.o \
  $(JUCE_OBJDIR)/LfoPanel_7120ed30.o \
  $(JUCE_OBJDIR)/OscPanel_a461a3a6.o \
  $(JUCE_OBJDIR)/SeqPanel_faaaa246.o \
  $(JUCE_OBJDIR)/MouseOverKnob_4cc14d30.o \
  $(JUCE_OBJDIR)/ModSourceBox_a030b837.o \
  $(JUCE_OBJDIR)/PluginEditor_30637ae9.o \
  $(JUCE_OBJDIR)/PlugUI_f705530b.o \
  $(JUCE_OBJDIR)/Envelope_64b6dd49.o \
  $(JUCE_OBJDIR)/LowFidelity_1bd4c32b.o \
  $(JUCE_OBJDIR)/FxChorus_2f26fe91.o \
  $(JUCE_OBJDIR)/FxClipping_c79f162d.o \
  $(JUCE_OBJDIR)/ModulationMatrix_e2f4b756.o \
  $(JUCE_OBJDIR)/FxDelay_de5d6c2.o \
  $(JUCE_OBJDIR)/StepSequencer_ff4eff56.o \
  $(JUCE_OBJDIR)/PluginProcessor_9750ba90.o \
  $(JUCE_OBJDIR)/SynthParams_22ea7c53.o \
  $(JUCE_OBJDIR)/BinaryData_51699c3.o \
  $(JUCE_OBJDIR)/juce_audio_basics_513f3ad2.o \
  $(JUCE_OBJDIR)/juce_audio_devices_7a34cb7a.o \
  $(JUCE_OBJDIR)/juce_audio_formats_2d1bce79.o \
  $(JUCE_OBJDIR)/juce_audio_plugin_client_utils_39a89566.o \
  $(JUCE_OBJDIR)/juce_audio_plugin_client_VST2_5bfe3490.o \
  $(JUCE_OBJDIR)/juce_audio_processors_d20c54ee.o \
  $(JUCE_OBJDIR)/juce_audio_utils_ae4c9f4e.o \
  $(JUCE_OBJDIR)/juce_core_d24cc263.o \
  $(JUCE_OBJDIR)/juce_data_structures_5163a25b.o \
  $(JUCE_OBJDIR)/juce_events_7676ff1d.o \
  $(JUCE_OBJDIR)/juce_graphics_338f07cf.o \
  $(JUCE_OBJDIR)/juce_gui_basics_1e3f3c0d.o \
  $(JUCE_OBJDIR)/juce_gui_extra_a15bc692.o \

.PHONY: clean

$(JUCE_OUTDIR)/$(TARGET): check-pkg-config $(OBJECTS) $(RESOURCES)
	@echo Linking synister
	-@mkdir -p $(JUCE_BINDIR)
	-@mkdir -p $(JUCE_LIBDIR)
	-@mkdir -p $(JUCE_OUTDIR)
	$(V_AT)$(BLDCMD)

check-pkg-config:
	@command -v pkg-config >/dev/null 2>&1 || { echo >&2 "pkg-config not installed. Please, install it."; exit 1; }
	@pkg-config --print-errors alsa freetype2 libcurl x11 xext xinerama

clean:
	@echo Cleaning synister
	$(V_AT)$(CLEANCMD)

strip:
	@echo Stripping synister
	-@$(STRIP) --strip-unneeded $(JUCE_OUTDIR)/$(TARGET)

$(JUCE_OBJDIR)/FoldablePanel_e65a70ea.o: ../../../../gui/FoldablePanel.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling FoldablePanel.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/EnvelopeCurve_961ea700.o: ../../../../gui/EnvelopeCurve.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling EnvelopeCurve.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CustomLookAndFeel_4e23e34e.o: ../../../../gui/CustomLookAndFeel.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CustomLookAndFeel.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/IncDecDropDown_eb6dd87e.o: ../../../../gui/IncDecDropDown.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling IncDecDropDown.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/WaveformVisual_b06529c6.o: ../../../../gui/WaveformVisual.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling WaveformVisual.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/InfoPanel_325825ff.o: ../../../../gui/panels/InfoPanel.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling InfoPanel.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ChorusPanel_8af55b07.o: ../../../../gui/panels/ChorusPanel.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ChorusPanel.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ClippingPanel_49f61a6b.o: ../../../../gui/panels/ClippingPanel.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ClippingPanel.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/LoFiPanel_af43e007.o: ../../../../gui/panels/LoFiPanel.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling LoFiPanel.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/EnvPanel_906d1578.o: ../../../../gui/panels/EnvPanel.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling EnvPanel.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/FiltPanel_83223dc2.o: ../../../../gui/panels/FiltPanel.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling FiltPanel.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/FxPanel_66c36b5b.o: ../../../../gui/panels/FxPanel.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling FxPanel.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Env1Panel_9ccdd289.o: ../../../../gui/panels/Env1Panel.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Env1Panel.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/LfoPanel_7120ed30.o: ../../../../gui/panels/LfoPanel.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling LfoPanel.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/OscPanel_a461a3a6.o: ../../../../gui/panels/OscPanel.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling OscPanel.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/SeqPanel_faaaa246.o: ../../../../gui/panels/SeqPanel.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling SeqPanel.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/MouseOverKnob_4cc14d30.o: ../../../../gui/MouseOverKnob.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling MouseOverKnob.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ModSourceBox_a030b837.o: ../../../../gui/ModSourceBox.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ModSourceBox.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PluginEditor_30637ae9.o: ../../../../gui/PluginEditor.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PluginEditor.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PlugUI_f705530b.o: ../../../../gui/PlugUI.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PlugUI.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Envelope_64b6dd49.o: ../../../../audio/src/Envelope.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Envelope.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/LowFidelity_1bd4c32b.o: ../../../../audio/src/LowFidelity.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling LowFidelity.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/FxChorus_2f26fe91.o: ../../../../audio/src/FxChorus.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling FxChorus.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/FxClipping_c79f162d.o: ../../../../audio/src/FxClipping.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling FxClipping.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ModulationMatrix_e2f4b756.o: ../../../../audio/src/ModulationMatrix.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ModulationMatrix.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/FxDelay_de5d6c2.o: ../../../../audio/src/FxDelay.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling FxDelay.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/StepSequencer_ff4eff56.o: ../../../../audio/src/StepSequencer.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling StepSequencer.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PluginProcessor_9750ba90.o: ../../../../audio/src/PluginProcessor.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PluginProcessor.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/SynthParams_22ea7c53.o: ../../../../audio/src/SynthParams.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling SynthParams.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/BinaryData_51699c3.o: ../../../JuceLibraryCode/BinaryData.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling BinaryData.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_audio_basics_513f3ad2.o: ../../../JuceLibraryCode/juce_audio_basics.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_audio_basics.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_audio_devices_7a34cb7a.o: ../../../JuceLibraryCode/juce_audio_devices.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_audio_devices.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_audio_formats_2d1bce79.o: ../../../JuceLibraryCode/juce_audio_formats.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_audio_formats.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_audio_plugin_client_utils_39a89566.o: ../../../JuceLibraryCode/juce_audio_plugin_client_utils.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_audio_plugin_client_utils.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_audio_plugin_client_VST2_5bfe3490.o: ../../../JuceLibraryCode/juce_audio_plugin_client_VST2.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_audio_plugin_client_VST2.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_audio_processors_d20c54ee.o: ../../../JuceLibraryCode/juce_audio_processors.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_audio_processors.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_audio_utils_ae4c9f4e.o: ../../../JuceLibraryCode/juce_audio_utils.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_audio_utils.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_core_d24cc263.o: ../../../JuceLibraryCode/juce_core.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_core.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_data_structures_5163a25b.o: ../../../JuceLibraryCode/juce_data_structures.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_data_structures.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_events_7676ff1d.o: ../../../JuceLibraryCode/juce_events.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_events.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_graphics_338f07cf.o: ../../../JuceLibraryCode/juce_graphics.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_graphics.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_gui_basics_1e3f3c0d.o: ../../../JuceLibraryCode/juce_gui_basics.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_gui_basics.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_gui_extra_a15bc692.o: ../../../JuceLibraryCode/juce_gui_extra.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_gui_extra.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
