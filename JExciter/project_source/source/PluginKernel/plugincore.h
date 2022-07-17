// -----------------------------------------------------------------------------
//    ASPiK Plugin Kernel File:  plugincore.h
//
/**
    \file   plugincore.h
    \author Will Pirkle
    \date   17-September-2018
    \brief  base class interface file for ASPiK plugincore object
    		- http://www.aspikplugins.com
    		- http://www.willpirkle.com
*/
// -----------------------------------------------------------------------------
#ifndef __pluginCore_h__
#define __pluginCore_h__

#include "pluginbase.h"
#include "LinkwitzRiley2ndOrder.h"


// **--0x7F1F--**
enum ControlID {

	LowOn = 0,
	LowMidOn = 1,
	HighMidOn = 2,
	TrebleOn = 3,
	LowSolo = 4,
	LowMidSolo = 5,
	HighMidSolo = 6,
	TrebleSolo = 7,
	LowSat = 8,
	LowMidSat = 9,
	HighMidSat = 10,
	TrebleSat = 11,
	LowMix = 12,
	LowMidMix = 13,
	HighMidMix = 14,
	TrebleMix = 15,
	MasterVolume = 16

};

// **--0x0F1F--**

/**
\class PluginCore
\ingroup ASPiK-Core
\brief
The PluginCore object is the default PluginBase derived object for ASPiK projects.
Note that you are fre to change the name of this object (as long as you change it in the compiler settings, etc...)


PluginCore Operations:
- overrides the main processing functions from the base class
- performs reset operation on sub-modules
- processes audio
- processes messages for custom views
- performs pre and post processing functions on parameters and audio (if needed)

\author Will Pirkle http://www.willpirkle.com
\remark This object is included in Designing Audio Effects Plugins in C++ 2nd Ed. by Will Pirkle
\version Revision : 1.0
\date Date : 2018 / 09 / 7
*/
class PluginCore : public PluginBase
{
public:
    PluginCore();

	/** Destructor: empty in default version */
    virtual ~PluginCore(){}

	// --- PluginBase Overrides ---
	//
	/** this is the creation function for all plugin parameters */
	bool initPluginParameters();

	/** called when plugin is loaded, a new audio file is playing or sample rate changes */
	virtual bool reset(ResetInfo& resetInfo);

	/** one-time post creation init function; pluginInfo contains path to this plugin */
	virtual bool initialize(PluginInfo& _pluginInfo);

	// --- preProcess: sync GUI parameters here; override if you don't want to use automatic variable-binding
	virtual bool preProcessAudioBuffers(ProcessBufferInfo& processInfo);

	/** process frames of data */
	virtual bool processAudioFrame(ProcessFrameInfo& processFrameInfo);

	// --- uncomment and override this for buffer processing; see base class implementation for
	//     help on breaking up buffers and getting info from processBufferInfo
	//virtual bool processAudioBuffers(ProcessBufferInfo& processBufferInfo); 

	/** preProcess: do any post-buffer processing required; default operation is to send metering data to GUI  */
	virtual bool postProcessAudioBuffers(ProcessBufferInfo& processInfo);

	/** called by host plugin at top of buffer proccess; this alters parameters prior to variable binding operation  */
	virtual bool updatePluginParameter(int32_t controlID, double controlValue, ParameterUpdateInfo& paramInfo);

	/** called by host plugin at top of buffer proccess; this alters parameters prior to variable binding operation  */
	virtual bool updatePluginParameterNormalized(int32_t controlID, double normalizedValue, ParameterUpdateInfo& paramInfo);

	/** this can be called: 1) after bound variable has been updated or 2) after smoothing occurs  */
	virtual bool postUpdatePluginParameter(int32_t controlID, double controlValue, ParameterUpdateInfo& paramInfo);

	/** this is ony called when the user makes a GUI control change */
	virtual bool guiParameterChanged(int32_t controlID, double actualValue);

	/** processMessage: messaging system; currently used for custom/special GUI operations */
	virtual bool processMessage(MessageInfo& messageInfo);

	/** processMIDIEvent: MIDI event processing */
	virtual bool processMIDIEvent(midiEvent& event);

	/** specialized joystick servicing (currently not used) */
	virtual bool setVectorJoystickParameters(const VectorJoystickData& vectorJoysickData);

	/** create the presets */
	bool initPluginPresets();

	// --- BEGIN USER VARIABLES AND FUNCTIONS -------------------------------------- //
	//	   Add your variables and methods here

	void setAndCalcFilters();
	void updateParameters();
	void setBandStates();




	// --- END USER VARIABLES AND FUNCTIONS -------------------------------------- //

private:
	//  **--0x07FD--**

	LinkwitzRiley2ndOrder LFLP_L, LFHP_L, MFLP_L, MFHP_L, HFLP_L, HFHP_L;
	LinkwitzRiley2ndOrder LFLP_R, LFHP_R, MFLP_R, MFHP_R, HFLP_R, HFHP_R;


	int LowOn = 1;
	enum class LowOnEnum { OFF, ON };

	int LowMidOn = 1;
	enum class LowMidOnEnum { OFF, ON };

	int HighMidOn = 1;
	enum class HighMidOnEnum { OFF, ON };

	int TrebleOn = 1;
	enum class TrebleOnEnum { OFF, ON };

	int LowSolo = 0;
	enum class LowSoloEnum { OFF, ON };

	int LowMidSolo = 0;
	enum class LowMidSoloEnum { OFF, ON };

	int HighMidSolo = 0;
	enum class HighMidSoloEnum { OFF, ON };

	int TrebleSolo = 0;
	enum class TrebleSoloEnum { OFF, ON };

	double LowSat = 0.000000;
	double LowMidSat = 0.000000;
	double HighMidSat = 0.000000;
	double TrebleSat = 0.000000;

	double LowMix = 0.0000000;
	double LowMidMix = 0.0000000;
	double HighMidMix = 0.0000000;
	double TrebleMix = 0.000000;

	double LowSatRaw;
	double LowMidSatRaw;
	double HighMidSatRaw;
	double TrebleSatRaw;

	double LowMixRaw;
	double LowMidMixRaw;
	double HighMidMixRaw;
	double TrebleMixRaw;

	double MasterVolume = 0.0000000;
	double MasterVolumeCooked = 0.00000;


	// **--0x1A7F--**
    // --- end member variables

public:
    /** static description: bundle folder name

	\return bundle folder name as a const char*
	*/
    static const char* getPluginBundleName();

    /** static description: name

	\return name as a const char*
	*/
    static const char* getPluginName();

	/** static description: short name

	\return short name as a const char*
	*/
	static const char* getShortPluginName();

	/** static description: vendor name

	\return vendor name as a const char*
	*/
	static const char* getVendorName();

	/** static description: URL

	\return URL as a const char*
	*/
	static const char* getVendorURL();

	/** static description: email

	\return email address as a const char*
	*/
	static const char* getVendorEmail();

	/** static description: Cocoa View Factory Name

	\return Cocoa View Factory Name as a const char*
	*/
	static const char* getAUCocoaViewFactoryName();

	/** static description: plugin type

	\return type (FX or Synth)
	*/
	static pluginType getPluginType();

	/** static description: VST3 GUID

	\return VST3 GUID as a const char*
	*/
	static const char* getVSTFUID();

	/** static description: 4-char code

	\return 4-char code as int
	*/
	static int32_t getFourCharCode();

	/** initalizer */
	bool initPluginDescriptors();
    
    /** Status Window Messages for hosts that can show it */
    void sendHostTextMessage(std::string messageString)
    {
        HostMessageInfo hostMessageInfo;
        hostMessageInfo.hostMessage = sendRAFXStatusWndText;
        hostMessageInfo.rafxStatusWndText.assign(messageString);
        if(pluginHostConnector)
            pluginHostConnector->sendHostMessage(hostMessageInfo);
    }

};




#endif /* defined(__pluginCore_h__) */
