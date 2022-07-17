// -----------------------------------------------------------------------------
//    ASPiK Plugin Kernel File:  plugincore.cpp
//
/**
    \file   plugincore.cpp
    \author Will Pirkle
    \date   17-September-2018
    \brief  Implementation file for PluginCore object
    		- http://www.aspikplugins.com
    		- http://www.willpirkle.com
*/
// -----------------------------------------------------------------------------
#include "plugincore.h"
#include "plugindescription.h"

/**
\brief PluginCore constructor is launching pad for object initialization

Operations:
- initialize the plugin description (strings, codes, numbers, see initPluginDescriptors())
- setup the plugin's audio I/O channel support
- create the PluginParameter objects that represent the plugin parameters (see FX book if needed)
- create the presets
*/
PluginCore::PluginCore()
{
    // --- describe the plugin; call the helper to init the static parts you setup in plugindescription.h
    initPluginDescriptors();

    // --- default I/O combinations
	// --- for FX plugins
	if (getPluginType() == kFXPlugin)
	{
		addSupportedIOCombination({ kCFMono, kCFMono });
		addSupportedIOCombination({ kCFMono, kCFStereo });
		addSupportedIOCombination({ kCFStereo, kCFStereo });
	}
	else // --- synth plugins have no input, only output
	{
		addSupportedIOCombination({ kCFNone, kCFMono });
		addSupportedIOCombination({ kCFNone, kCFStereo });
	}

	// --- for sidechaining, we support mono and stereo inputs; auxOutputs reserved for future use
	addSupportedAuxIOCombination({ kCFMono, kCFNone });
	addSupportedAuxIOCombination({ kCFStereo, kCFNone });

	// --- create the parameters
    initPluginParameters();

    // --- create the presets
    initPluginPresets();
}

/**
\brief create all of your plugin parameters here

\return true if parameters were created, false if they already existed
*/
bool PluginCore::initPluginParameters()
{
	if (pluginParameterMap.size() > 0)
		return false;

    // --- Add your plugin parameter instantiation code bewtween these hex codes
	// **--0xDEA7--**

	PluginParameter* piParam = nullptr;

	piParam = new PluginParameter(0, "LowOn", "OFF, ON", "ON");
	piParam->setBoundVariable(&LowOn, boundVariableType::kInt);
	addPluginParameter(piParam);

	piParam = new PluginParameter(1, "LowMidOn", "OFF, ON", "ON");
	piParam->setBoundVariable(&LowMidOn, boundVariableType::kInt);
	addPluginParameter(piParam);

	piParam = new PluginParameter(2, "HighMidOn", "OFF, ON", "ON");
	piParam->setBoundVariable(&HighMidOn, boundVariableType::kInt);
	addPluginParameter(piParam);

	piParam = new PluginParameter(3, "TrebleOn", "OFF, ON", "ON");
	piParam->setBoundVariable(&TrebleOn, boundVariableType::kInt);
	addPluginParameter(piParam);

	piParam = new PluginParameter(4, "LowSolo", "OFF, ON", "OFF");
	piParam->setBoundVariable(&LowSolo, boundVariableType::kInt);
	addPluginParameter(piParam);

	piParam = new PluginParameter(5, "LowMidSolo", "OFF, ON", "OFF");
	piParam->setBoundVariable(&LowMidSolo, boundVariableType::kInt);
	addPluginParameter(piParam);

	piParam = new PluginParameter(6, "HighMidSolo", "OFF, ON", "OFF");
	piParam->setBoundVariable(&HighMidSolo, boundVariableType::kInt);
	addPluginParameter(piParam);

	piParam = new PluginParameter(7, "TrebleSolo", "OFF, ON", "OFF");
	piParam->setBoundVariable(&TrebleSolo, boundVariableType::kInt);
	addPluginParameter(piParam);

	piParam = new PluginParameter(8, "LowSat", "dB", controlVariableType::kDouble, 0.000000, 24.000000, 0.000000, taper::kLinearTaper);
	piParam->setBoundVariable(&LowSat, boundVariableType::kDouble);
	addPluginParameter(piParam);

	piParam = new PluginParameter(9, "LowMidSat", "dB", controlVariableType::kDouble, 0.000000, 24.000000, 0.000000, taper::kLinearTaper);
	piParam->setBoundVariable(&LowMidSat, boundVariableType::kDouble);
	addPluginParameter(piParam);

	piParam = new PluginParameter(10, "HighMidSat", "dB", controlVariableType::kDouble, 0.000000, 24.000000, 0.000000, taper::kLinearTaper);
	piParam->setBoundVariable(&HighMidSat, boundVariableType::kDouble);
	addPluginParameter(piParam);

	piParam = new PluginParameter(11, "TrebleSat", "dB", controlVariableType::kDouble, 0.000000, 24.000000, 0.000000, taper::kLinearTaper);
	piParam->setBoundVariable(&TrebleSat, boundVariableType::kDouble);
	addPluginParameter(piParam);

	piParam = new PluginParameter(12, "LowMix", "Pct", controlVariableType::kDouble, 0.000000, 100.000000, 50.000000, taper::kLinearTaper);
	piParam->setBoundVariable(&LowMix, boundVariableType::kDouble);
	addPluginParameter(piParam);

	piParam = new PluginParameter(13, "LowMidMix", "Pct", controlVariableType::kDouble, 0.000000, 100.000000, 50.000000, taper::kLinearTaper);
	piParam->setBoundVariable(&LowMidMix, boundVariableType::kDouble);
	addPluginParameter(piParam);

	piParam = new PluginParameter(14, "HighMidMix", "Pct", controlVariableType::kDouble, 0.000000, 100.000000, 50.000000, taper::kLinearTaper);
	piParam->setBoundVariable(&HighMidMix, boundVariableType::kDouble);
	addPluginParameter(piParam);


	piParam = new PluginParameter(15, "TrebleMix", "Pct", controlVariableType::kDouble, 0.000000, 100.000000, 50.000000, taper::kLinearTaper);
	piParam->setBoundVariable(&TrebleMix, boundVariableType::kDouble);
	addPluginParameter(piParam);

	piParam = new PluginParameter(16, "MasterVolume", "dB", controlVariableType::kDouble, -60.000000, 12.000000, 0.000000, taper::kLinearTaper);
	piParam->setBoundVariable(&MasterVolume, boundVariableType::kDouble);
	addPluginParameter(piParam);
    
	// **--0xEDA5--**
   
    // --- BONUS Parameter
    // --- SCALE_GUI_SIZE
    PluginParameter* piParamBonus = new PluginParameter(SCALE_GUI_SIZE, "Scale GUI", "tiny,small,medium,normal,large,giant", "normal");
    addPluginParameter(piParamBonus);

	// --- create the super fast access array
	initPluginParameterArray();

    return true;
}

/**
\brief initialize object for a new run of audio; called just before audio streams

Operation:
- store sample rate and bit depth on audioProcDescriptor - this information is globally available to all core functions
- reset your member objects here

\param resetInfo structure of information about current audio format

\return true if operation succeeds, false otherwise
*/
bool PluginCore::reset(ResetInfo& resetInfo)
{
    // --- save for audio processing
    audioProcDescriptor.sampleRate = resetInfo.sampleRate;
    audioProcDescriptor.bitDepth = resetInfo.bitDepth;

	setAndCalcFilters();

    // --- other reset inits
    return PluginBase::reset(resetInfo);
}

/**
\brief one-time initialize function called after object creation and before the first reset( ) call

Operation:
- saves structure for the plugin to use; you can also load WAV files or state information here
*/
bool PluginCore::initialize(PluginInfo& pluginInfo)
{
	// --- add one-time init stuff here

	return true;
}

/**
\brief do anything needed prior to arrival of audio buffers

Operation:
- syncInBoundVariables when preProcessAudioBuffers is called, it is *guaranteed* that all GUI control change information
  has been applied to plugin parameters; this binds parameter changes to your underlying variables
- NOTE: postUpdatePluginParameter( ) will be called for all bound variables that are acutally updated; if you need to process
  them individually, do so in that function
- use this function to bulk-transfer the bound variable data into your plugin's member object variables

\param processInfo structure of information about *buffer* processing

\return true if operation succeeds, false otherwise
*/
bool PluginCore::preProcessAudioBuffers(ProcessBufferInfo& processInfo)
{
    // --- sync internal variables to GUI parameters; you can also do this manually if you don't
    //     want to use the auto-variable-binding
    syncInBoundVariables();






    return true;
}

void PluginCore::updateParameters() {


	LowSatRaw = pow(10, LowSat / 20);
	LowMidSatRaw = pow(10, LowMidSat / 20);
	HighMidSatRaw = pow(10, HighMidSat / 20);
	TrebleSatRaw = pow(10, TrebleSat / 20);

	LowMixRaw = LowMix / 100;
	LowMidMixRaw = LowMidMix / 100;
	HighMidMixRaw = HighMidMix / 100;
	TrebleMixRaw = TrebleMix / 100;

	MasterVolumeCooked = pow(10, MasterVolume / 20);

}

void PluginCore::setAndCalcFilters() {

	LFLP_L.setFilter(0, 100.f, PluginCore::getSampleRate());
	LFHP_L.setFilter(1, 100.f, PluginCore::getSampleRate());
	MFLP_L.setFilter(0, 1000.f, PluginCore::getSampleRate());
	MFHP_L.setFilter(1, 1000.f, PluginCore::getSampleRate());
	HFLP_L.setFilter(0, 10000.f, PluginCore::getSampleRate());
	HFHP_L.setFilter(1, 10000.f, PluginCore::getSampleRate());

	LFLP_R.setFilter(0, 100.f, PluginCore::getSampleRate());
	LFHP_R.setFilter(1, 100.f, PluginCore::getSampleRate());
	MFLP_R.setFilter(0, 1000.f, PluginCore::getSampleRate());
	MFHP_R.setFilter(1, 1000.f, PluginCore::getSampleRate());
	HFLP_R.setFilter(0, 10000.f, PluginCore::getSampleRate());
	HFHP_R.setFilter(1, 10000.f, PluginCore::getSampleRate());

}

void PluginCore::setBandStates() {

	if (LowSolo == true && LowMidSolo == false && HighMidSolo == false && TrebleSolo == false) {

		LowOn = 1;
		LowMidOn = 0;
		HighMidOn = 0;
		TrebleOn = 0;

	}

	if (LowSolo == false && LowMidSolo == true && HighMidSolo == false && TrebleSolo == false) {

		LowOn = 0;
		LowMidOn = 1;
		HighMidOn = 0;
		TrebleOn = 0;

	}

	if (LowSolo == false && LowMidSolo == false && HighMidSolo == true && TrebleSolo == false) {

		LowOn = 0;
		LowMidOn = 0;
		HighMidOn = 1;
		TrebleOn = 0;

	}

	if (LowSolo == false && LowMidSolo == false && HighMidSolo == false && TrebleSolo == true) {

		LowOn = 0;
		LowMidOn = 0;
		HighMidOn = 0;
		TrebleOn = 1;

	}

	if (LowSolo == true && LowMidSolo == true && HighMidSolo == false && TrebleSolo == false) {

		LowOn = 1;
		LowMidOn = 1;
		HighMidOn = 0;
		TrebleOn = 0;

	}

	if (LowSolo == true && LowMidSolo == false && HighMidSolo == true && TrebleSolo == false) {

		LowOn = 1;
		LowMidOn = 0;
		HighMidOn = 1;
		TrebleOn = 0;

	}

	if (LowSolo == true && LowMidSolo == false && HighMidSolo == false && TrebleSolo == true) {

		LowOn = 1;
		LowMidOn = 0;
		HighMidOn = 0;
		TrebleOn = 1;

	}

	if (LowSolo == false && LowMidSolo == true && HighMidSolo == true && TrebleSolo == false) {

		LowOn = 0;
		LowMidOn = 1;
		HighMidOn = 1;
		TrebleOn = 0;

	}

	if (LowSolo == false && LowMidSolo == true && HighMidSolo == false && TrebleSolo == true) {

		LowOn = 0;
		LowMidOn = 1;
		HighMidOn = 0;
		TrebleOn = 1;

	}

	if (LowSolo == false && LowMidSolo == false && HighMidSolo == true && TrebleSolo == true) {

		LowOn = 0;
		LowMidOn = 0;
		HighMidOn = 1;
		TrebleOn = 1;

	}

	if (LowSolo == true && LowMidSolo == true && HighMidSolo == true && TrebleSolo == false) {

		LowOn = 1;
		LowMidOn = 1;
		HighMidOn = 1;
		TrebleOn = 0;

	}

	if (LowSolo == true && LowMidSolo == true && HighMidSolo == false && TrebleSolo == true) {

		LowOn = 1;
		LowMidOn = 1;
		HighMidOn = 0;
		TrebleOn = 1;

	}

	if (LowSolo == true && LowMidSolo == false && HighMidSolo == true && TrebleSolo == true) {

	LowOn = 1;
	LowMidOn = 0;
	HighMidOn = 1;
	TrebleOn = 1;

	}

	if (LowSolo == false && LowMidSolo == true && HighMidSolo == true && TrebleSolo == true) {

	LowOn = 1;
	LowMidOn = 0;
	HighMidOn = 1;
	TrebleOn = 1;

	}

	if (LowSolo == true && LowMidSolo == true && HighMidSolo == true && TrebleSolo == true) {

	LowOn = 1;
	LowMidOn = 1;
	HighMidOn = 1;
	TrebleOn = 1;

	}

	else {

		LowOn = LowOn;
		LowMidOn = LowMidOn;
		HighMidOn = HighMidOn;
		TrebleOn = TrebleOn;

	}

}

/**
\brief frame-processing method

Operation:
- decode the plugin type - for synth plugins, fill in the rendering code; for FX plugins, delete the if(synth) portion and add your processing code
- note that MIDI events are fired for each sample interval so that MIDI is tightly sunk with audio
- doSampleAccurateParameterUpdates will perform per-sample interval smoothing

\param processFrameInfo structure of information about *frame* processing

\return true if operation succeeds, false otherwise
*/
bool PluginCore::processAudioFrame(ProcessFrameInfo& processFrameInfo)
{
    // --- fire any MIDI events for this sample interval
    processFrameInfo.midiEventQueue->fireMidiEvents(processFrameInfo.currentFrame);

	// --- do per-frame updates; VST automation and parameter smoothing
	doSampleAccurateParameterUpdates();

	updateParameters();
	setBandStates();

	

    // --- decode the channelIOConfiguration and process accordingly
    //
	// --- Synth Plugin:
	// --- Synth Plugin --- remove for FX plugins
	if (getPluginType() == kSynthPlugin)
	{
		// --- output silence: change this with your signal render code
		processFrameInfo.audioOutputFrame[0] = 0.0;
		if (processFrameInfo.channelIOConfig.outputChannelFormat == kCFStereo)
			processFrameInfo.audioOutputFrame[1] = 0.0;

		return true;	/// processed
	}

    // --- FX Plugin:
    if(processFrameInfo.channelIOConfig.inputChannelFormat == kCFMono &&
       processFrameInfo.channelIOConfig.outputChannelFormat == kCFMono)
    {
		// --- pass through code: change this with your signal processing
		double channelData = processFrameInfo.audioInputFrame[0];
		
		// duplicate signal 4 times for each band
		double LFB = channelData;
		double LMFB = channelData;
		double HMFB = channelData;
		double TFB = channelData;

		//filter each band
		LFB = LFLP_L.process(LFB);
		LMFB = LFHP_L.process(LMFB);
		LMFB = MFLP_L.process(LMFB);
		HMFB = MFHP_L.process(HMFB);
		HMFB = HFLP_L.process(HMFB);
		TFB = HFHP_L.process(TFB);

		//phase invert each adjacent band
		LMFB = -1 * LMFB;
		TFB = -1 * TFB; 

		//take dry signal of each band
		double LFBdry = LFB;
		double LMFBdry = LMFB;
		double HMFBdry = HMFB;
		double TFBdry = TFB;

		//add harmonic excitation to each band
		LFB = tanh(LowSatRaw * LFB) / tanh(LowSatRaw);
		LMFB = tanh(LowMidSatRaw * LMFB) / tanh(LowMidSatRaw);
		HMFB = tanh(HighMidSatRaw * HMFB) / tanh(HighMidSatRaw);
		TFB = tanh(TrebleSatRaw * TFB) / tanh(TrebleSatRaw);

		//blend dry signals with distorted signal
		LFB = LFBdry * (1.0f - LowMixRaw) + LFB * LowMixRaw;
		LMFB = LMFBdry * (1.0f - LowMidMixRaw) + LMFB * LowMidMixRaw;
		HMFB = HMFBdry * (1.0f - HighMidMixRaw) + HMFB * HighMidMixRaw;
		TFB = TFBdry * (1.0f - TrebleMixRaw) + TFB * TrebleMixRaw;

		//sum all bands and apply bypass on each band
		channelData = (LFB * LowOn) + (LMFB * LowMidOn) + (HMFB * HighMidOn) + (TFB * TrebleOn);

		//set master volume
		channelData = channelData * MasterVolumeCooked;

		processFrameInfo.audioOutputFrame[0] = channelData;

        return true; /// processed
    }

    // --- Mono-In/Stereo-Out
    else if(processFrameInfo.channelIOConfig.inputChannelFormat == kCFMono &&
       processFrameInfo.channelIOConfig.outputChannelFormat == kCFStereo)
    {
		// --- pass through code: change this with your signal processing
		double channelData_L = processFrameInfo.audioInputFrame[0];
		double channelData_R = processFrameInfo.audioInputFrame[0];

		double LFB_L = channelData_L;
		double LMFB_L = channelData_L;
		double HMFB_L = channelData_L;
		double TFB_L = channelData_L;

		double LFB_R = channelData_R;
		double LMFB_R = channelData_R;
		double HMFB_R = channelData_R;
		double TFB_R = channelData_R;

		LFB_L = LFLP_L.process(LFB_L);
		LFB_R = LFLP_R.process(LFB_R);
		LMFB_L = LFHP_L.process(LMFB_L);
		LMFB_L = MFLP_L.process(LMFB_L);
		LMFB_R = LFHP_R.process(LMFB_R);
		LMFB_R = MFLP_R.process(LMFB_R);
		HMFB_L = MFHP_L.process(HMFB_L);
		HMFB_L = HFLP_L.process(HMFB_L);
		HMFB_R = MFHP_R.process(HMFB_R);
		HMFB_R = HFLP_R.process(HMFB_R);
		TFB_L = HFHP_L.process(TFB_L);
		TFB_R = HFHP_R.process(TFB_R);

		LMFB_L = -1 * LMFB_L;
		LMFB_R = -1 * LMFB_R;
		TFB_L = -1 * TFB_L;
		TFB_R = -1 * TFB_R;

		double LFBdryl = LFB_L;
		double LMFBdryl = LMFB_L;
		double HMFBdryl = HMFB_L;
		double TFBdryl = TFB_L;

		double LFBdryr = LFB_R;
		double LMFBdryr = LMFB_R;
		double HMFBdryr = HMFB_R;
		double TFBdryr = TFB_R;

		LFB_L = tanh(LowSatRaw * LFB_L) / tanh(LowSatRaw);
		LMFB_L = tanh(LowMidSatRaw * LMFB_L) / tanh(LowMidSatRaw);
		HMFB_L = tanh(HighMidSatRaw * HMFB_L) / tanh(HighMidSatRaw);
		TFB_L = tanh(TrebleSatRaw * TFB_L) / tanh(TrebleSatRaw);

		LFB_R = tanh(LowSatRaw * LFB_R) / tanh(LowSatRaw);
		LMFB_R = tanh(LowMidSatRaw * LMFB_R) / tanh(LowMidSatRaw);
		HMFB_R = tanh(HighMidSatRaw * HMFB_R) / tanh(HighMidSatRaw);
		TFB_R = tanh(TrebleSatRaw * TFB_R) / tanh(TrebleSatRaw);

		LFB_L = LFBdryl * (1.0f - LowMixRaw) + LFB_L * LowMixRaw;
		LMFB_L = LMFBdryl * (1.0f - LowMidMixRaw) + LMFB_L * LowMidMixRaw;
		HMFB_L = HMFBdryl * (1.0f - HighMidMixRaw) + HMFB_L * HighMidMixRaw;
		TFB_L = TFBdryl * (1.0f - TrebleMixRaw) + TFB_L * TrebleMixRaw;

		LFB_R = LFBdryr * (1.0f - LowMixRaw) + LFB_R * LowMixRaw;
		LMFB_R = LMFBdryr * (1.0f - LowMidMixRaw) + LMFB_R * LowMidMixRaw;
		HMFB_R = HMFBdryr * (1.0f - HighMidMixRaw) + HMFB_R * HighMidMixRaw;
		TFB_R = TFBdryr * (1.0f - TrebleMixRaw) + TFB_R * TrebleMixRaw;

		channelData_L = (LFB_L * LowOn) + (LMFB_L * LowMidOn) + (HMFB_L * HighMidOn) + (TFB_L * TrebleOn);
		channelData_R = (LFB_R * LowOn) + (LMFB_R * LowMidOn) + (HMFB_R * HighMidOn) + (TFB_R * TrebleOn);

		channelData_L = channelData_L * MasterVolumeCooked;
		channelData_R = channelData_R * MasterVolumeCooked;

		processFrameInfo.audioOutputFrame[0] = channelData_L;
		processFrameInfo.audioOutputFrame[1] = channelData_R;
        return true; /// processed
    }

    // --- Stereo-In/Stereo-Out
    else if(processFrameInfo.channelIOConfig.inputChannelFormat == kCFStereo &&
       processFrameInfo.channelIOConfig.outputChannelFormat == kCFStereo)
    {
		// --- pass through code: change this with your signal processing
		double channelData_L = processFrameInfo.audioInputFrame[0];
		double channelData_R = processFrameInfo.audioInputFrame[1];

		double LFB_L = channelData_L;
		double LMFB_L = channelData_L;
		double HMFB_L = channelData_L;
		double TFB_L = channelData_L;

		double LFB_R = channelData_R;
		double LMFB_R = channelData_R;
		double HMFB_R = channelData_R;
		double TFB_R = channelData_R;

		LFB_L = LFLP_L.process(LFB_L);
		LFB_R = LFLP_R.process(LFB_R);
		LMFB_L = LFHP_L.process(LMFB_L);
		LMFB_L = MFLP_L.process(LMFB_L);
		LMFB_R = LFHP_R.process(LMFB_R);
		LMFB_R = MFLP_R.process(LMFB_R);
		HMFB_L = MFHP_L.process(HMFB_L);
		HMFB_L = HFLP_L.process(HMFB_L);
		HMFB_R = MFHP_R.process(HMFB_R);
		HMFB_R = HFLP_R.process(HMFB_R);
		TFB_L = HFHP_L.process(TFB_L);
		TFB_R = HFHP_R.process(TFB_R);

		LMFB_L = -1 * LMFB_L;
		LMFB_R = -1 * LMFB_R;
		TFB_L = -1 * TFB_L;
		TFB_R = -1 * TFB_R;

		double LFBdryl = LFB_L;
		double LMFBdryl = LMFB_L;
		double HMFBdryl = HMFB_L;
		double TFBdryl = TFB_L;

		double LFBdryr = LFB_R;
		double LMFBdryr = LMFB_R;
		double HMFBdryr = HMFB_R;
		double TFBdryr = TFB_R;

		LFB_L = tanh(LowSatRaw * LFB_L) / tanh(LowSatRaw);
		LMFB_L = tanh(LowMidSatRaw * LMFB_L) / tanh(LowMidSatRaw);
		HMFB_L = tanh(HighMidSatRaw * HMFB_L) / tanh(HighMidSatRaw);
		TFB_L = tanh(TrebleSatRaw * TFB_L) / tanh(TrebleSatRaw);

		LFB_R = tanh(LowSatRaw * LFB_R) / tanh(LowSatRaw);
		LMFB_R = tanh(LowMidSatRaw * LMFB_R) / tanh(LowMidSatRaw);
		HMFB_R = tanh(HighMidSatRaw * HMFB_R) / tanh(HighMidSatRaw);
		TFB_R = tanh(TrebleSatRaw * TFB_R) / tanh(TrebleSatRaw);

		LFB_L = LFBdryl * (1.0f - LowMixRaw) + LFB_L * LowMixRaw;
		LMFB_L = LMFBdryl * (1.0f - LowMidMixRaw) + LMFB_L * LowMidMixRaw;
		HMFB_L = HMFBdryl * (1.0f - HighMidMixRaw) + HMFB_L * HighMidMixRaw;
		TFB_L = TFBdryl * (1.0f - TrebleMixRaw) + TFB_L * TrebleMixRaw;

		LFB_R = LFBdryr * (1.0f - LowMixRaw) + LFB_R * LowMixRaw;
		LMFB_R = LMFBdryr * (1.0f - LowMidMixRaw) + LMFB_R * LowMidMixRaw;
		HMFB_R = HMFBdryr * (1.0f - HighMidMixRaw) + HMFB_R * HighMidMixRaw;
		TFB_R = TFBdryr * (1.0f - TrebleMixRaw) + TFB_R * TrebleMixRaw;


		channelData_L = (LFB_L * LowOn) + (LMFB_L * LowMidOn) + (HMFB_L * HighMidOn) + (TFB_L * TrebleOn);
		channelData_R = (LFB_R * LowOn) + (LMFB_R * LowMidOn) + (HMFB_R * HighMidOn) + (TFB_R * TrebleOn);

		channelData_L = channelData_L * MasterVolumeCooked;
		channelData_R = channelData_R * MasterVolumeCooked;

		processFrameInfo.audioOutputFrame[0] = channelData_L;
		processFrameInfo.audioOutputFrame[1] = channelData_R;

        return true; /// processed
    }

    return false; /// NOT processed
}


/**
\brief do anything needed prior to arrival of audio buffers

Operation:
- updateOutBoundVariables sends metering data to the GUI meters

\param processInfo structure of information about *buffer* processing

\return true if operation succeeds, false otherwise
*/
bool PluginCore::postProcessAudioBuffers(ProcessBufferInfo& processInfo)
{
	// --- update outbound variables; currently this is meter data only, but could be extended
	//     in the future
	updateOutBoundVariables();

    return true;
}

/**
\brief update the PluginParameter's value based on GUI control, preset, or data smoothing (thread-safe)

Operation:
- update the parameter's value (with smoothing this initiates another smoothing process)
- call postUpdatePluginParameter to do any further processing

\param controlID the control ID value of the parameter being updated
\param controlValue the new control value
\param paramInfo structure of information about why this value is being udpated (e.g as a result of a preset being loaded vs. the top of a buffer process cycle)

\return true if operation succeeds, false otherwise
*/
bool PluginCore::updatePluginParameter(int32_t controlID, double controlValue, ParameterUpdateInfo& paramInfo)
{
    // --- use base class helper
    setPIParamValue(controlID, controlValue);

    // --- do any post-processing
    postUpdatePluginParameter(controlID, controlValue, paramInfo);

    return true; /// handled
}

/**
\brief update the PluginParameter's value based on *normlaized* GUI control, preset, or data smoothing (thread-safe)

Operation:
- update the parameter's value (with smoothing this initiates another smoothing process)
- call postUpdatePluginParameter to do any further processing

\param controlID the control ID value of the parameter being updated
\param normalizedValue the new control value in normalized form
\param paramInfo structure of information about why this value is being udpated (e.g as a result of a preset being loaded vs. the top of a buffer process cycle)

\return true if operation succeeds, false otherwise
*/
bool PluginCore::updatePluginParameterNormalized(int32_t controlID, double normalizedValue, ParameterUpdateInfo& paramInfo)
{
	// --- use base class helper, returns actual value
	double controlValue = setPIParamValueNormalized(controlID, normalizedValue, paramInfo.applyTaper);

	// --- do any post-processing
	postUpdatePluginParameter(controlID, controlValue, paramInfo);

	return true; /// handled
}

/**
\brief perform any operations after the plugin parameter has been updated; this is one paradigm for
	   transferring control information into vital plugin variables or member objects. If you use this
	   method you can decode the control ID and then do any cooking that is needed. NOTE: do not
	   overwrite bound variables here - this is ONLY for any extra cooking that is required to convert
	   the GUI data to meaninful coefficients or other specific modifiers.

\param controlID the control ID value of the parameter being updated
\param controlValue the new control value
\param paramInfo structure of information about why this value is being udpated (e.g as a result of a preset being loaded vs. the top of a buffer process cycle)

\return true if operation succeeds, false otherwise
*/
bool PluginCore::postUpdatePluginParameter(int32_t controlID, double controlValue, ParameterUpdateInfo& paramInfo)
{
    // --- now do any post update cooking; be careful with VST Sample Accurate automation
    //     If enabled, then make sure the cooking functions are short and efficient otherwise disable it
    //     for the Parameter involved
    /*switch(controlID)
    {
        case 0:
        {
            return true;    /// handled
        }

        default:
            return false;   /// not handled
    }*/

    return false;
}

/**
\brief has nothing to do with actual variable or updated variable (binding)

CAUTION:
- DO NOT update underlying variables here - this is only for sending GUI updates or letting you
  know that a parameter was changed; it should not change the state of your plugin.

WARNING:
- THIS IS NOT THE PREFERRED WAY TO LINK OR COMBINE CONTROLS TOGETHER. THE PROPER METHOD IS
  TO USE A CUSTOM SUB-CONTROLLER THAT IS PART OF THE GUI OBJECT AND CODE.
  SEE http://www.willpirkle.com for more information

\param controlID the control ID value of the parameter being updated
\param actualValue the new control value

\return true if operation succeeds, false otherwise
*/
bool PluginCore::guiParameterChanged(int32_t controlID, double actualValue)
{
	/*
	switch (controlID)
	{
		case controlID::<your control here>
		{

			return true; // handled
		}

		default:
			break;
	}*/

	return false; /// not handled
}

/**
\brief For Custom View and Custom Sub-Controller Operations

NOTES:
- this is for advanced users only to implement custom view and custom sub-controllers
- see the SDK for examples of use

\param messageInfo a structure containing information about the incoming message

\return true if operation succeeds, false otherwise
*/
bool PluginCore::processMessage(MessageInfo& messageInfo)
{
	// --- decode message
	switch (messageInfo.message)
	{
		// --- add customization appearance here
	case PLUGINGUI_DIDOPEN:
	{
		return false;
	}

	// --- NULL pointers so that we don't accidentally use them
	case PLUGINGUI_WILLCLOSE:
	{
		return false;
	}

	// --- update view; this will only be called if the GUI is actually open
	case PLUGINGUI_TIMERPING:
	{
		return false;
	}

	// --- register the custom view, grab the ICustomView interface
	case PLUGINGUI_REGISTER_CUSTOMVIEW:
	{

		return false;
	}

	case PLUGINGUI_REGISTER_SUBCONTROLLER:
	case PLUGINGUI_QUERY_HASUSERCUSTOM:
	case PLUGINGUI_USER_CUSTOMOPEN:
	case PLUGINGUI_USER_CUSTOMCLOSE:
	case PLUGINGUI_EXTERNAL_SET_NORMVALUE:
	case PLUGINGUI_EXTERNAL_SET_ACTUALVALUE:
	{

		return false;
	}

	default:
		break;
	}

	return false; /// not handled
}


/**
\brief process a MIDI event

NOTES:
- MIDI events are 100% sample accurate; this function will be called repeatedly for every MIDI message
- see the SDK for examples of use

\param event a structure containing the MIDI event data

\return true if operation succeeds, false otherwise
*/
bool PluginCore::processMIDIEvent(midiEvent& event)
{
	return true;
}

/**
\brief (for future use)

NOTES:
- MIDI events are 100% sample accurate; this function will be called repeatedly for every MIDI message
- see the SDK for examples of use

\param vectorJoysickData a structure containing joystick data

\return true if operation succeeds, false otherwise
*/
bool PluginCore::setVectorJoystickParameters(const VectorJoystickData& vectorJoysickData)
{
	return true;
}

/**
\brief use this method to add new presets to the list

NOTES:
- see the SDK for examples of use
- for non RackAFX users that have large paramter counts, there is a secret GUI control you
  can enable to write C++ code into text files, one per preset. See the SDK or http://www.willpirkle.com for details

\return true if operation succeeds, false otherwise
*/
bool PluginCore::initPluginPresets()
{
	// **--0xFF7A--**

	// **--0xA7FF--**

    return true;
}

/**
\brief setup the plugin description strings, flags and codes; this is ordinarily done through the ASPiKreator or CMake

\return true if operation succeeds, false otherwise
*/
bool PluginCore::initPluginDescriptors()
{
    pluginDescriptor.pluginName = PluginCore::getPluginName();
    pluginDescriptor.shortPluginName = PluginCore::getShortPluginName();
    pluginDescriptor.vendorName = PluginCore::getVendorName();
    pluginDescriptor.pluginTypeCode = PluginCore::getPluginType();

	// --- describe the plugin attributes; set according to your needs
	pluginDescriptor.hasSidechain = kWantSidechain;
	pluginDescriptor.latencyInSamples = kLatencyInSamples;
	pluginDescriptor.tailTimeInMSec = kTailTimeMsec;
	pluginDescriptor.infiniteTailVST3 = kVSTInfiniteTail;

    // --- AAX
    apiSpecificInfo.aaxManufacturerID = kManufacturerID;
    apiSpecificInfo.aaxProductID = kAAXProductID;
    apiSpecificInfo.aaxBundleID = kAAXBundleID;  /* MacOS only: this MUST match the bundle identifier in your info.plist file */
    apiSpecificInfo.aaxEffectID = "aaxDeveloper.";
    apiSpecificInfo.aaxEffectID.append(PluginCore::getPluginName());
    apiSpecificInfo.aaxPluginCategoryCode = kAAXCategory;

    // --- AU
    apiSpecificInfo.auBundleID = kAUBundleID;   /* MacOS only: this MUST match the bundle identifier in your info.plist file */
    apiSpecificInfo.auBundleName = kAUBundleName;

    // --- VST3
    apiSpecificInfo.vst3FUID = PluginCore::getVSTFUID(); // OLE string format
    apiSpecificInfo.vst3BundleID = kVST3BundleID;/* MacOS only: this MUST match the bundle identifier in your info.plist file */
	apiSpecificInfo.enableVST3SampleAccurateAutomation = kVSTSAA;
	apiSpecificInfo.vst3SampleAccurateGranularity = kVST3SAAGranularity;

    // --- AU and AAX
    apiSpecificInfo.fourCharCode = PluginCore::getFourCharCode();

    return true;
}

// --- static functions required for VST3/AU only --------------------------------------------- //
const char* PluginCore::getPluginBundleName() { return kAUBundleName; }
const char* PluginCore::getPluginName(){ return kPluginName; }
const char* PluginCore::getShortPluginName(){ return kShortPluginName; }
const char* PluginCore::getVendorName(){ return kVendorName; }
const char* PluginCore::getVendorURL(){ return kVendorURL; }
const char* PluginCore::getVendorEmail(){ return kVendorEmail; }
const char* PluginCore::getAUCocoaViewFactoryName(){ return AU_COCOA_VIEWFACTORY_STRING; }
pluginType PluginCore::getPluginType(){ return kPluginType; }
const char* PluginCore::getVSTFUID(){ return kVSTFUID; }
int32_t PluginCore::getFourCharCode(){ return kFourCharCode; }
