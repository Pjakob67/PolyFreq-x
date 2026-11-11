#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include "SynthEngine/SynthEngine.h"

class PolyfreqXProcessor : public juce::AudioProcessor
{
public:
    PolyfreqXProcessor();
    ~PolyfreqXProcessor() override = default;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override {}
    bool isBusesLayoutSupported (const BusesLayout&) const override { return true; }
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return "POLYFREQ X"; }
    bool acceptsMidi() const override  { return true; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 1.0; }

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram (int) override {}
    const juce::String getProgramName (int) override { return "Init"; }
    void changeProgramName (int, const juce::String&) override {}

    void getStateInformation (juce::MemoryBlock&) override;
    void setStateInformation (const void*, int) override;

    juce::AudioProcessorValueTreeState apvts;
    polyfreq::SynthEngine engine;

    std::atomic<float> currentRms { 0.0f };

private:
    static juce::AudioProcessorValueTreeState::ParameterLayout createLayout();
    void updateEngineParams();
    void handleMidi (const juce::MidiBuffer&, int numSamples);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PolyfreqXProcessor)
};
