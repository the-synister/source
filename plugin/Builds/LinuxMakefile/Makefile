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
    TARGET_ARCH := -march=native
  endif

  JUCE_CPPFLAGS := $(DEPFLAGS) -DLINUX=1 -DDEBUG=1 -D_DEBUG=1 -DJUCER_LINUX_MAKE_6D53C8B4=1 -DJUCE_APP_VERSION=1.0.2 -DJUCE_APP_VERSION_HEX=0x10002 $(shell pkg-config --cflags alsa freetype2 libcurl x11 xext xinerama) -pthread -I../../JuceLibraryCode -I../../../../JUCE/modules -I../../../gui -I../../../audio/inc $(CPPFLAGS)
  JUCE_CFLAGS += $(JUCE_CPPFLAGS) $(TARGET_ARCH) -g -ggdb -fPIC -O0 $(CFLAGS)
  JUCE_CXXFLAGS += $(JUCE_CFLAGS) -std=c++11 $(CXXFLAGS)
  JUCE_LDFLAGS += $(TARGET_ARCH) -L$(JUCE_BINDIR) -L$(JUCE_LIBDIR) -Wl,--no-undefined -shared $(shell pkg-config --libs alsa freetype2 libcurl x11 xext xinerama) -ldl -lpthread -lrt  $(LDFLAGS)

  TARGET := synister.so
  BLDCMD = $(CXX) -o $(JUCE_OUTDIR)/$(TARGET) $(OBJECTS) $(JUCE_LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(JUCE_OUTDIR)/$(TARGET) $(JUCE_OBJDIR)
endif

ifeq ($(CONFIG),Release)
  JUCE_BINDIR := build
  JUCE_LIBDIR := build
  JUCE_OBJDIR := build/intermediate/Release
  JUCE_OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  JUCE_CPPFLAGS := $(DEPFLAGS) -DLINUX=1 -DNDEBUG=1 -DJUCER_LINUX_MAKE_6D53C8B4=1 -DJUCE_APP_VERSION=1.0.2 -DJUCE_APP_VERSION_HEX=0x10002 $(shell pkg-config --cflags alsa freetype2 libcurl x11 xext xinerama) -pthread -I../../JuceLibraryCode -I../../../../JUCE/modules -I../../../gui -I../../../audio/inc $(CPPFLAGS)
  JUCE_CFLAGS += $(JUCE_CPPFLAGS) $(TARGET_ARCH) -fPIC -O3 $(CFLAGS)
  JUCE_CXXFLAGS += $(JUCE_CFLAGS) -std=c++11 $(CXXFLAGS)
  JUCE_LDFLAGS += $(TARGET_ARCH) -L$(JUCE_BINDIR) -L$(JUCE_LIBDIR) -Wl,--no-undefined -shared -fvisibility=hidden $(shell pkg-config --libs alsa freetype2 libcurl x11 xext xinerama) -ldl -lpthread -lrt  $(LDFLAGS)

  TARGET := synister.so
  BLDCMD = $(CXX) -o $(JUCE_OUTDIR)/$(TARGET) $(OBJECTS) $(JUCE_LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(JUCE_OUTDIR)/$(TARGET) $(JUCE_OBJDIR)
endif

OBJECTS := \
  $(JUCE_OBJDIR)/FoldablePanel_fa2e6abb.o \
  $(JUCE_OBJDIR)/EnvelopeCurve_a9f2a0d1.o \
  $(JUCE_OBJDIR)/CustomLookAndFeel_d48c9f.o \
  $(JUCE_OBJDIR)/IncDecDropDown_521918cd.o \
  $(JUCE_OBJDIR)/WaveformVisual_17106a15.o \
  $(JUCE_OBJDIR)/InfoPanel_9b348e8e.o \
  $(JUCE_OBJDIR)/ChorusPanel_2e59dbd6.o \
  $(JUCE_OBJDIR)/ClippingPanel_a63da37a.o \
  $(JUCE_OBJDIR)/LoFiPanel_18204896.o \
  $(JUCE_OBJDIR)/EnvPanel_ff29df09.o \
  $(JUCE_OBJDIR)/FiltPanel_ebfea651.o \
  $(JUCE_OBJDIR)/FxPanel_cd6eabaa.o \
  $(JUCE_OBJDIR)/Env1Panel_5aa3b18.o \
  $(JUCE_OBJDIR)/LfoPanel_dfddb6c1.o \
  $(JUCE_OBJDIR)/OscPanel_131e6d37.o \
  $(JUCE_OBJDIR)/SeqPanel_69676bd7.o \
  $(JUCE_OBJDIR)/MouseOverKnob_60954701.o \
  $(JUCE_OBJDIR)/ModSourceBox_45fdc046.o \
  $(JUCE_OBJDIR)/PluginEditor_d63082f8.o \
  $(JUCE_OBJDIR)/PlugUI_9d01525a.o \
  $(JUCE_OBJDIR)/Envelope_cb621d98.o \
  $(JUCE_OBJDIR)/LowFidelity_ce856c7c.o \
  $(JUCE_OBJDIR)/FxChorus_95d23ee0.o \
  $(JUCE_OBJDIR)/FxClipping_307b7ebc.o \
  $(JUCE_OBJDIR)/ModulationMatrix_4b7e38a5.o \
  $(JUCE_OBJDIR)/FxDelay_21b9d093.o \
  $(JUCE_OBJDIR)/StepSequencer_c87a9867.o \
  $(JUCE_OBJDIR)/PluginProcessor_c3fa5361.o \
  $(JUCE_OBJDIR)/SynthParams_d59b25a4.o \
  $(JUCE_OBJDIR)/BinaryData_ce4232d4.o \
  $(JUCE_OBJDIR)/juce_audio_basics_6b797ca1.o \
  $(JUCE_OBJDIR)/juce_audio_devices_a742c38b.o \
  $(JUCE_OBJDIR)/juce_audio_formats_5a29c68a.o \
  $(JUCE_OBJDIR)/juce_audio_plugin_client_utils_35fbf7.o \
  $(JUCE_OBJDIR)/juce_audio_plugin_client_VST2_fd137df.o \
  $(JUCE_OBJDIR)/juce_audio_processors_dea3173d.o \
  $(JUCE_OBJDIR)/juce_audio_utils_c7eb679f.o \
  $(JUCE_OBJDIR)/juce_core_75b14332.o \
  $(JUCE_OBJDIR)/juce_data_structures_72d3da2c.o \
  $(JUCE_OBJDIR)/juce_events_d2be882c.o \
  $(JUCE_OBJDIR)/juce_graphics_9c18891e.o \
  $(JUCE_OBJDIR)/juce_gui_basics_8a6da59c.o \
  $(JUCE_OBJDIR)/juce_gui_extra_4a026f23.o \

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

$(JUCE_OBJDIR)/FoldablePanel_fa2e6abb.o: ../../../gui/FoldablePanel.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling FoldablePanel.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/EnvelopeCurve_a9f2a0d1.o: ../../../gui/EnvelopeCurve.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling EnvelopeCurve.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CustomLookAndFeel_d48c9f.o: ../../../gui/CustomLookAndFeel.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CustomLookAndFeel.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/IncDecDropDown_521918cd.o: ../../../gui/IncDecDropDown.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling IncDecDropDown.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/WaveformVisual_17106a15.o: ../../../gui/WaveformVisual.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling WaveformVisual.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/InfoPanel_9b348e8e.o: ../../../gui/panels/InfoPanel.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling InfoPanel.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ChorusPanel_2e59dbd6.o: ../../../gui/panels/ChorusPanel.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ChorusPanel.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ClippingPanel_a63da37a.o: ../../../gui/panels/ClippingPanel.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ClippingPanel.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/LoFiPanel_18204896.o: ../../../gui/panels/LoFiPanel.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling LoFiPanel.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/EnvPanel_ff29df09.o: ../../../gui/panels/EnvPanel.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling EnvPanel.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/FiltPanel_ebfea651.o: ../../../gui/panels/FiltPanel.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling FiltPanel.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/FxPanel_cd6eabaa.o: ../../../gui/panels/FxPanel.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling FxPanel.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Env1Panel_5aa3b18.o: ../../../gui/panels/Env1Panel.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Env1Panel.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/LfoPanel_dfddb6c1.o: ../../../gui/panels/LfoPanel.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling LfoPanel.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/OscPanel_131e6d37.o: ../../../gui/panels/OscPanel.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling OscPanel.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/SeqPanel_69676bd7.o: ../../../gui/panels/SeqPanel.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling SeqPanel.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/MouseOverKnob_60954701.o: ../../../gui/MouseOverKnob.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling MouseOverKnob.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ModSourceBox_45fdc046.o: ../../../gui/ModSourceBox.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ModSourceBox.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PluginEditor_d63082f8.o: ../../../gui/PluginEditor.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PluginEditor.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PlugUI_9d01525a.o: ../../../gui/PlugUI.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PlugUI.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Envelope_cb621d98.o: ../../../audio/src/Envelope.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Envelope.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/LowFidelity_ce856c7c.o: ../../../audio/src/LowFidelity.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling LowFidelity.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/FxChorus_95d23ee0.o: ../../../audio/src/FxChorus.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling FxChorus.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/FxClipping_307b7ebc.o: ../../../audio/src/FxClipping.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling FxClipping.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ModulationMatrix_4b7e38a5.o: ../../../audio/src/ModulationMatrix.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ModulationMatrix.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/FxDelay_21b9d093.o: ../../../audio/src/FxDelay.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling FxDelay.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/StepSequencer_c87a9867.o: ../../../audio/src/StepSequencer.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling StepSequencer.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PluginProcessor_c3fa5361.o: ../../../audio/src/PluginProcessor.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PluginProcessor.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/SynthParams_d59b25a4.o: ../../../audio/src/SynthParams.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling SynthParams.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/BinaryData_ce4232d4.o: ../../JuceLibraryCode/BinaryData.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling BinaryData.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_audio_basics_6b797ca1.o: ../../JuceLibraryCode/juce_audio_basics.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_audio_basics.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_audio_devices_a742c38b.o: ../../JuceLibraryCode/juce_audio_devices.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_audio_devices.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_audio_formats_5a29c68a.o: ../../JuceLibraryCode/juce_audio_formats.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_audio_formats.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_audio_plugin_client_utils_35fbf7.o: ../../JuceLibraryCode/juce_audio_plugin_client_utils.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_audio_plugin_client_utils.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_audio_plugin_client_VST2_fd137df.o: ../../JuceLibraryCode/juce_audio_plugin_client_VST2.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_audio_plugin_client_VST2.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_audio_processors_dea3173d.o: ../../JuceLibraryCode/juce_audio_processors.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_audio_processors.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_audio_utils_c7eb679f.o: ../../JuceLibraryCode/juce_audio_utils.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_audio_utils.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_core_75b14332.o: ../../JuceLibraryCode/juce_core.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_core.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_data_structures_72d3da2c.o: ../../JuceLibraryCode/juce_data_structures.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_data_structures.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_events_d2be882c.o: ../../JuceLibraryCode/juce_events.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_events.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_graphics_9c18891e.o: ../../JuceLibraryCode/juce_graphics.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_graphics.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_gui_basics_8a6da59c.o: ../../JuceLibraryCode/juce_gui_basics.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_gui_basics.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_gui_extra_4a026f23.o: ../../JuceLibraryCode/juce_gui_extra.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_gui_extra.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
