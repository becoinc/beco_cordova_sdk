////////////////////////////////////////////////
// Beco, Inc
// Module created by: Chris Dalke, chrisd@beco.io
////////////////////////////////////////////////
// Beco Cordova Plugin
// Java (Android) Plugin implementation
////////////////////////////////////////////////

package beco.plugin.cordova;

/*
 Bridge module between the Cordova/JS wrapper for
 the Beco API, and the Android Beco API.
 */

////////////////////////////////////////////////
// Module Imports
////////////////////////////////////////////////

import android.app.Activity;
import android.content.Context;
import android.util.Log;

import com.fasterxml.jackson.databind.ObjectMapper;

import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CallbackContext;

import org.apache.cordova.LOG;
import org.apache.cordova.PluginResult;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import org.springframework.http.HttpStatus;

import java.util.HashMap;
import java.util.Map;
import java.util.UUID;
import java.util.logging.Logger;

import io.beco.sdk.android.bas.BecoSDKDelegate;
import io.beco.sdk.android.bas.BecoSDKErrorCode;
import io.beco.sdk.android.bas.BecoSDKInterface;
import io.beco.sdk.android.bas.RegisterHandsetComplete;
import io.beco.sdk.android.bas.api.v2_0.response.ActivityResponse;
import io.beco.sdk.android.bas.api.v2_0.response.RegisterHandsetResponse;
import io.beco.sdk.android.bas.exception.CredentialsNotSetException;

////////////////////////////////////////////////
// Cordova Plugin Definition
////////////////////////////////////////////////

public class BecoCordovaPlugin extends CordovaPlugin implements BecoSDKDelegate {
    
    //Log tag identifier
    private static final String TAG = "[Beco SDK]";
    private static final boolean DEBUG = false;
    
    //Instance member variables
    private BecoSDKInterface sdk;
    private String onReceiveLocationDataCallback;
    private String onReportErrorCallback;
    private String onReportAppHitCallback;
    private String onReportStartScanCompleteCallback;
    private CallbackContext onReceiveLocationDataCallbackContext;
    private CallbackContext onReportErrorCallbackContext;
    private CallbackContext onReportAppHitCallbackContext;
    private CallbackContext onReportStartScanCompleteCallbackContext;
    
    private int refreshIntervalValue = 10;
    private int thresholdAdjustmentValue = 3;
    
    ////////////////////////////////////////////////
    // Cordova Plugin Implementation
    ////////////////////////////////////////////////
    
    /*
     pluginInitialize
     Called when the Cordova instance initializes.
     Used to create the Beco API interface.
     Parameters: *None*
     */
    @Override
    protected void pluginInitialize() {
        super.pluginInitialize();
        
        Context cordovaContext = cordova.getActivity().getApplicationContext();
        sdk = new BecoSDKInterface(cordovaContext,this);
        
        if (DEBUG) LOG.i(TAG, "Initialized Cordova Plugin.");
    }
    
    @Override
    public boolean execute(String action, JSONArray args, CallbackContext callbackContext) throws JSONException {
        if      (action.equals("startScan"))                 { startScan(callbackContext); }
        else if (action.equals("stopScan"))                  { stopScan(callbackContext); }
        else if (action.equals("registerHandset"))           { registerHandset(args.getString(0),args.getString(1),args.getString(2),args.getString(3),callbackContext); }
        else if (action.equals("onReceiveLocationData"))     { onReceiveLocationData(callbackContext); }
        else if (action.equals("onReportError"))             { onReportError(callbackContext); }
        else if (action.equals("onReportAppHit"))            { onReportAppHit(callbackContext); }
        else if (action.equals("onReportStartScanComplete")) { onReportStartScanComplete(callbackContext); }
        else if (action.equals("setCredentials"))            { setCredentials(args.getString(0),args.getString(1),args.getString(2),callbackContext); }
        else if (action.equals("setRefreshInterval"))        { setRefreshInterval(args.getString(0),callbackContext); }
        else if (action.equals("setThresholdAdjustment"))    { setThresholdAdjustment(args.getString(0),callbackContext); }
        else if (action.equals("getVersion"))                { getVersion(callbackContext); }
        else if (action.equals("getThresholdAdjustment"))    { getThresholdAdjustment(callbackContext); }
        else if (action.equals("getRefreshInterval"))        { getRefreshInterval(callbackContext); }
        else if (action.equals("getSdkState"))               { getSdkState(callbackContext); }
        else if (action.equals("getHSID"))                   { getHSID(callbackContext); }
        else { return false; }
        return true;
    }
    
    ////////////////////////////////////////////////
    // Lifecycle / Core API Functions
    ////////////////////////////////////////////////
    
    /*----------------------------------------------
     startScan
     Starts the background scanning for beacons.
     Parameters: *None*
     */
    public void startScan(CallbackContext callbackContext){
        try {
            sdk.startScan();
            if (DEBUG) Log.i(TAG, "Started scanning for beacons...");
            callbackContext.success();
        } catch (CredentialsNotSetException e){
            callbackContext.error("Could not start scan. "+e.getMessage());
            if (DEBUG) Log.e(TAG,"Could not start scan. "+e.getMessage());
        }
    }
    
    /*----------------------------------------------
     stopScan
     Ends the background scanning for beacons.
     Parameters: *None*
     */
    public void stopScan(CallbackContext callbackContext){
        sdk.stopScan();
        if (DEBUG) Log.i(TAG,"Stopped scanning for beacons.");
        callbackContext.success();
    }
    
    
    /*----------------------------------------------
     registerHandset
     Registers a handset with the Beco API.
     Parameters:
     */
    public void registerHandset(String idfa, String personId, String groupId, String userData, final CallbackContext callbackContext){
        
        //try to map idfa to a UUID object
        //If fail, set it to null
        UUID idfaUUIDObject = null;
        if (idfa != null){
            try {
                idfaUUIDObject = UUID.fromString(idfa);
            } catch (Exception e){
                idfaUUIDObject = null;
            }
        }
        
        try {
            //Map the userdata into map object
            Map<String, Object> userDataMap = new HashMap<String,Object>();
            userDataMap.put("userData",userData);
            
            sdk.registerHandset(idfaUUIDObject, personId, groupId, userDataMap, new RegisterHandsetComplete() {
                @Override
                public void onRegisterComplete(boolean success, HttpStatus httpStatus, RegisterHandsetResponse registerHandsetResponse) {
                    ObjectMapper mapper = new ObjectMapper();
                    
                    try {
                        if (success) {
                            if (registerHandsetResponse != null) {
                                callbackContext.success(new JSONObject(mapper.writeValueAsString(registerHandsetResponse)));
                            } else {
                                callbackContext.success("Handset has already been registered, you only need to register a handset once. See the Beco Cordova User's Guide for details.");
                            }
                        } else {
                            callbackContext.error("Failed to register handset. Please verify your API credentials have been set and registerHandset parameters are valid.");
                        }
                    } catch (Exception e){
                        callbackContext.error("Could not return handset response value!");
                    }
                }
            });
        } catch (Exception e){
            if (DEBUG) LOG.e(TAG,"Failed to register handset! Invalid parameter set!");
            callbackContext.error("Failed to register handset!"+e.getMessage());
        }
    }
    
    ////////////////////////////////////////////////
    // Event Listener Functions
    ////////////////////////////////////////////////
    
    /*----------------------------------------------
     onReceiveLocationData
     Registers a callback function for the corresponding delegate function.
     Parameters: *callbackFunction*
     */
    public void onReceiveLocationData(CallbackContext callbackContext){
        onReceiveLocationDataCallbackContext = callbackContext;
        onReceiveLocationDataCallback = callbackContext.getCallbackId();
    }
    
    /*----------------------------------------------
     onReportError
     Registers a callback function for the corresponding delegate function.
     Parameters: *callbackFunction*
     */
    public void onReportError(CallbackContext callbackContext){
        onReportErrorCallbackContext = callbackContext;
        onReportErrorCallback = callbackContext.getCallbackId();
    }
    
    /*----------------------------------------------
     onReportAppHit
     Registers a callback function for the corresponding delegate function.
     Parameters: *callbackFunction*
     */
    public void onReportAppHit(CallbackContext callbackContext){
        onReportAppHitCallbackContext = callbackContext;
        onReportAppHitCallback = callbackContext.getCallbackId();
        if (DEBUG) LOG.w(TAG,"WARNING: appHit event is not supported on android platform! Please use onReceiveLocationData event. See the Beco Cordova SDK documentation for details.");
    }
    
    /*----------------------------------------------
     onReportStartScanComplete
     Registers a callback function for the corresponding delegate function.
     Parameters: *callbackFunction*
     */
    public void onReportStartScanComplete(CallbackContext callbackContext){
        onReportStartScanCompleteCallbackContext = callbackContext;
        onReportStartScanCompleteCallback = callbackContext.getCallbackId();
    }
    
    ////////////////////////////////////////////////
    // Delegate Functions
    ////////////////////////////////////////////////
    
    @Override
    public void reportError(BecoSDKErrorCode becoSDKErrorCode) {
        if (onReportErrorCallback != null){
            
            ObjectMapper mapper = new ObjectMapper();
            JSONObject errDataJsonObj;
            
            String[] tempStatusArray = {
                "Credential Mismatch",
                "Customer Not Found",
                "Rate Limit Exceeded",
                "Server Communication Failure",
                "Bluetooth Disabled",
                "Bluetooth Enabled",
                "Location Services Disabled",
                "Location Services Enabled"
            };
            
            HashMap<String, Object> tempHashMap = new HashMap<String, Object>();
            tempHashMap.put("errorCode", becoSDKErrorCode.ordinal());
            tempHashMap.put("errorString",tempStatusArray[becoSDKErrorCode.ordinal()]);
            
            try {
                errDataJsonObj = new JSONObject(mapper.writeValueAsString(tempHashMap));
            } catch (Exception e){
                //Do nothing if there is an error, return null response
                errDataJsonObj = null;
            }
            
            PluginResult result = new PluginResult(PluginResult.Status.OK, errDataJsonObj);
            result.setKeepCallback(true);
            
            //Display a debug message
            if (DEBUG) LOG.i(TAG,"Got reportError event. Calling callback function...");
            onReceiveLocationDataCallbackContext.sendPluginResult(result);
        }
    }
    
    @Override
    public void receiveLocationData(ActivityResponse activityResponse, long lastTime) {
        if (onReceiveLocationDataCallback != null){
            
            //Default OK result without any data attached
            PluginResult result = new PluginResult(PluginResult.Status.OK);
            
            //Attach data to result if the location returned isn't null
            if (activityResponse != null){
                if (DEBUG) LOG.i(TAG,"Received Location Data: Beco Id: "+activityResponse.getBecoId()+", Place: "+activityResponse.getPlace()+", Location: "+activityResponse.getLocation());
                
                ObjectMapper mapper = new ObjectMapper();
                
                /*
                 NSDictionary *locDict = @{
                 @"becoId" : locationData.becoId,
                 @"hsid" : [self->hsid UUIDString],
                 @"place" : @{
                 @"placeName" : locationData.place.placeName,
                 @"placeId" : locationData.place.placeId,
                 @"comments" : locationData.place.comments,
                 @"capacity" : [NSNumber numberWithInt:locationData.place.capacity],
                 @"floor": @{
                 @"name" : locationData.place.floor.name,
                 @"floorId" : locationData.place.floor.floorId
                 },
                 @"location": @{
                 @"locationName" : locationData.place.location.locationName,
                 @"locationId" : locationData.place.location.locationId
                 }
                 }
                 };
                 */
                
                HashMap<String, Object> tempHashMap = new HashMap<String, Object>();
                tempHashMap.put("becoId", activityResponse.getBecoId());
                tempHashMap.put("hsid",sdk.getBecoHsid());
                
                HashMap<String, Object> tempPlaceMap = new HashMap<String, Object>();
                tempPlaceMap.put("placeName",activityResponse.getPlace() != null ? activityResponse.getPlace().getPlaceName() : null);
                tempPlaceMap.put("placeId",activityResponse.getPlace() != null ? activityResponse.getPlace().getPlaceId() : null);
                tempPlaceMap.put("comments",activityResponse.getPlace() != null ? activityResponse.getPlace().getComments() : null);
                tempPlaceMap.put("capacity",null);
                
                HashMap<String, Object> tempFloorMap = new HashMap<String, Object>();
                HashMap<String, Object> tempLocationMap = new HashMap<String, Object>();
                
                try {
                    tempFloorMap.put("name",activityResponse.getPlace().getFloor().getName());
                } catch (Exception e){
                    tempFloorMap.put("name",null);
                }
                try {
                    tempFloorMap.put("floorId",activityResponse.getPlace().getFloor().getFloorId());
                } catch (Exception e){
                    tempFloorMap.put("floorId",null);
                }
                
                try {
                    tempLocationMap.put("locationName",activityResponse.getPlace().getLocation().getLocationName());
                } catch (Exception e){
                    tempLocationMap.put("locationName",null);
                }
                try {
                    tempLocationMap.put("locationId",activityResponse.getPlace().getLocation().getLocationId());
                } catch (Exception e){
                    tempLocationMap.put("locationId",null);
                }
                
                tempPlaceMap.put("floor",tempFloorMap);
                tempPlaceMap.put("location",tempLocationMap);
                
                tempHashMap.put("place",tempPlaceMap);
                
                String locationDataSerialized = null;
                JSONObject locationDataJsonObj = null;
                try {
                    locationDataSerialized = mapper.writeValueAsString(tempHashMap);
                    locationDataJsonObj = new JSONObject(locationDataSerialized);
                } catch (Exception e){
                    //Do nothing if there is an error, return null response
                    locationDataJsonObj = null;
                }
                
                //Override default result to return the location data as a serialized JSON object
                result = new PluginResult(PluginResult.Status.OK,locationDataJsonObj);
            }
            
            //Set flag to keep the callback function so we can call it multiple times
            result.setKeepCallback(true);
            
            //Display a debug message
            if (DEBUG) LOG.i(TAG,"Got receiveLocationData event. Calling callback function...");
            
            //Send the result to the callback function
            onReceiveLocationDataCallbackContext.sendPluginResult(result);
        }
    }
    
    
    @Override
    public void onStartScanComplete(boolean success) {
        if (onReportStartScanCompleteCallback != null){
            
            ObjectMapper mapper = new ObjectMapper();
            JSONObject startScanCompleteJsonObj;
            
            String[] tempStatusArray = {
                "Success",
                "Location Unauthorized",
                "Bluetooth Off",
                "Bluetooth Unsupported",
                "Bluetooth Unauthorized",
                "Bluetooth Unknown",
                "Network Error",
                "Credential Error",
                "Already Scanning",
                "Unknown Failure"};
            
            HashMap<String, Object> tempHashMap = new HashMap<String, Object>();
            tempHashMap.put("statusCode", success);
            tempHashMap.put("statusString",success ? tempStatusArray[0] : tempStatusArray[9] );
            
            try {
                startScanCompleteJsonObj = new JSONObject(mapper.writeValueAsString(tempHashMap));
            } catch (Exception e){
                //Do nothing if there is an error, return null response
                startScanCompleteJsonObj = null;
            }
            
            //If we've set a callback ID for the 'report scan complete' event, call it and return data.
            PluginResult result = new PluginResult(success ? PluginResult.Status.OK : PluginResult.Status.ERROR,startScanCompleteJsonObj);
            result.setKeepCallback(true);
            onReportStartScanCompleteCallbackContext.sendPluginResult(result);
        }
    }
    
    public void apiHit(){
        if (DEBUG) LOG.e(TAG,"Operation unsupported on Android platform.");
    }
    
    ////////////////////////////////////////////////
    // Setters
    ////////////////////////////////////////////////
    
    /*----------------------------------------------
     setCredentials
     Sets the username and password that the Beco API will use.
     Parameters: username, plainPw
     */
    public void setCredentials(String hostname, String username, String plainPw, CallbackContext callbackContext){
        sdk.setCredentials(hostname,username,plainPw);
        callbackContext.success();
        if (DEBUG) LOG.i(TAG,"Set user API credentials.");
    }
    
    
    /*----------------------------------------------
     setThresholdAdjustment
     Sets the threshold adjustment tweak value.
     Parameters: thresholdAdjustment
     */
    public void setThresholdAdjustment(String thresholdAdjustment, CallbackContext callbackContext){
        try {
            int tempVal = Integer.parseInt(thresholdAdjustment);
            sdk.setThresholdAdjustment(tempVal);
            thresholdAdjustmentValue = tempVal;
            if (DEBUG) LOG.i(TAG,"Set thresholdAdjustment tweak value.");
            callbackContext.success();
        } catch (Exception e){
            if (DEBUG) LOG.i(TAG,"Failed to set thresholdAdjustment tweak value!");
            callbackContext.error("Failed to set thresholdAdjustment tweak value! " + e.getMessage());
        }
    }
    
    /*----------------------------------------------
     setRefreshInterval
     Sets the refresh interval tweak value.
     Parameters: refreshInterval
     */
    public void setRefreshInterval(String refreshInterval, CallbackContext callbackContext){
        try {
            int tempVal = Integer.parseInt(refreshInterval);
            sdk.setHitRefresh(tempVal);
            refreshIntervalValue = tempVal;
            if (DEBUG) LOG.i(TAG,"Set refreshInterval tweak value.");
            callbackContext.success();
        } catch (Exception e){
            if (DEBUG) LOG.i(TAG,"Failed to set refreshInterval tweak value!");
            callbackContext.error("Failed to set refreshInterval tweak value! " + e.getMessage());
        }
    }
    
    ////////////////////////////////////////////////
    // Getters
    ////////////////////////////////////////////////
    
    /*----------------------------------------------
     getVersion
     Gets the version ID for the currently running Beco API.
     Parameters: *None*
     */
    public void getVersion(CallbackContext callbackContext){
        callbackContext.success(sdk.getVersion());
    }
    
    /*----------------------------------------------
     getThresholdAdjustment
     Gets the threshold adjustment tweak value
     Parameters: *None*
     */
    public void getThresholdAdjustment(CallbackContext callbackContext){
        callbackContext.success(thresholdAdjustmentValue);
    }
    
    /*----------------------------------------------
     getRefreshInterval
     Gets the refresh interval tweak value
     Parameters: *None*
     */
    public void getRefreshInterval(CallbackContext callbackContext){
        callbackContext.success(refreshIntervalValue);
    }
    
    /*----------------------------------------------
     getSdkState
     Gets the SDK state.
     Parameters: *None*
     */
    public void getSdkState(CallbackContext callbackContext){
        callbackContext.error("Operation unsupported on Android platform.");
        if (DEBUG) LOG.e(TAG,"Operation unsupported on Android platform.");
    }
    
    /*----------------------------------------------
     getHsid
     Gets the HSID for use with the Beco API.
     Parameters: *None*
     */
    public void getHSID(CallbackContext callbackContext){
        callbackContext.success(sdk.getBecoHsid().toString());
    }
}

////////////////////////////////////////////////
// End of File
////////////////////////////////////////////////
