// --- CMAKE generated variables for your plugin

#include "pluginstructures.h"

#ifndef _plugindescription_h
#define _plugindescription_h

#define QUOTE(name) #name
#define STR(macro) QUOTE(macro)
#define AU_COCOA_VIEWFACTORY_STRING STR(AU_COCOA_VIEWFACTORY_NAME)
#define AU_COCOA_VIEW_STRING STR(AU_COCOA_VIEW_NAME)

// --- AU Plugin Cocoa View Names (flat namespace) 
#define AU_COCOA_VIEWFACTORY_NAME AUCocoaViewFactory_9C567B9D2B7D30829416BC6F6B0BFB10
#define AU_COCOA_VIEW_NAME AUCocoaView_9C567B9D2B7D30829416BC6F6B0BFB10

// --- BUNDLE IDs (MacOS Only) 
const char* kAAXBundleID = "developer.aax.jexciter.bundleID";
const char* kAUBundleID = "developer.au.jexciter.bundleID";
const char* kVST3BundleID = "developer.vst3.jexciter.bundleID";

// --- Plugin Names 
const char* kPluginName = "JExciter";
const char* kShortPluginName = "JExciter";
const char* kAUBundleName = "JExciter_AU";

// --- Plugin Type 
const pluginType kPluginType = pluginType::kFXPlugin;

// --- VST3 UUID 
const char* kVSTFUID = "{9c567b9d-2b7d-3082-9416-bc6f6b0bfb10}";

// --- 4-char codes 
const int32_t kFourCharCode = 'JEXC';
const int32_t kAAXProductID = 'JEXC';
const int32_t kManufacturerID = 'JEP';

// --- Vendor information 
const char* kVendorName = "JEPlugins";
const char* kVendorURL = "";
const char* kVendorEmail = "";

// --- Plugin Options 
const bool kWantSidechain = false;
const uint32_t kLatencyInSamples = 0;
const double kTailTimeMsec = 0;
const bool kVSTInfiniteTail = false;
const bool kVSTSAA = false;
const uint32_t kVST3SAAGranularity = 1;
const uint32_t kAAXCategory = 0;

#endif
