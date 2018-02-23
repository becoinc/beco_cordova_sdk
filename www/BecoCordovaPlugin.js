////////////////////////////////////////////////
// Beco, Inc
////////////////////////////////////////////////
// Beco Cordova Plugin
// JS Plugin Wrapper
////////////////////////////////////////////////

////////////////////////////////////////////////
// Dependencies
////////////////////////////////////////////////

var exec = require('cordova/exec');

////////////////////////////////////////////////
// Plugin Definition
////////////////////////////////////////////////

var BecoCordovaPlugin = {
    //=========// LIFECYCLE / CORE //=========//
    registerHandset: function(handsetId, personId, groupId, userData, success, failure){
        exec(success, failure, "BecoCordovaPlugin", "registerHandset", [handsetId, personId, groupId, userData]);
    },
    startScan: function(success, failure){
        exec(success, null, "BecoCordovaPlugin", "startScan", []);
    },
    stopScan: function(success, failure){
        exec(success, null, "BecoCordovaPlugin", "stopScan", []);
    },
    //=========// EVENT LISTENERS //=========// d d
    onReceiveLocationData: function(cb){
        if (cb == undefined) { throw new Error("Please specify a callback function!"); }
        exec(cb, null, "BecoCordovaPlugin", "onReceiveLocationData", []);
    },
    onReportError: function(cb){
        if (cb == undefined) { throw new Error("Please specify a callback function!"); }
        exec(cb, null, "BecoCordovaPlugin", "onReportError", []);
    },
    onReportAppHit: function(cb){
        if (cb == undefined) { throw new Error("Please specify a callback function!"); }
        exec(cb, null, "BecoCordovaPlugin", "onReportAppHit", []);
    },
    onReportStartScanComplete: function(cb){
        if (cb == undefined) { throw new Error("Please specify a callback function!"); }
        exec(cb, null, "BecoCordovaPlugin", "onReportStartScanComplete", []);
    },
    //=========// SETTERS //=========//
    setCredentials: function(hostname, username, plainPw){
        if (hostname == undefined) { throw new Error("Please specify a hostname!"); }
        if (username == undefined) { throw new Error("Please specify a username!"); }
        if (plainPw == undefined) { throw new Error("Please specify a password!"); }
        exec(null, null, "BecoCordovaPlugin", "setCredentials", [hostname, username, plainPw]);
    },
    setRefreshInterval: function(refreshInterval){
        if (refreshInterval == undefined) { throw new Error("Please specify a refresh interval value!"); }
        exec(null, null, "BecoCordovaPlugin", "setRefreshInterval", [refreshInterval]);
    },
    setThresholdAdjustment: function(thresholdAdjustment){
        if (thresholdAdjustment == undefined) { throw new Error("Please specify a threshold adjustment value!"); }
        exec(null, null, "BecoCordovaPlugin", "setThresholdAdjustment", [thresholdAdjustment]);
    },
    //=========// GETTERS //=========//
    getVersion: function(cb){
        //Return the Cordova plugin version
        if (cb == undefined) { throw new Error("Please specify a callback function!"); }
        cb("v1.0.5");
    },
    getPlatformVersion: function(cb){
        //Return the platform API version
        if (cb == undefined) { throw new Error("Please specify a callback function!"); }
        exec(cb, null, "BecoCordovaPlugin", "getVersion", []);
    },
    getThresholdAdjustment: function(cb){
        if (cb == undefined) { throw new Error("Please specify a callback function!"); }
        exec(cb, null, "BecoCordovaPlugin", "getThresholdAdjustment", []);
    },
    getRefreshInterval: function(cb){
        if (cb == undefined) { throw new Error("Please specify a callback function!"); }
        exec(cb, null, "BecoCordovaPlugin", "getRefreshInterval", []);
    },
    getSdkState: function(cb){
        if (cb == undefined) { throw new Error("Please specify a callback function!"); }
        exec(cb, null, "BecoCordovaPlugin", "getSdkState", []);
    },
    getHSID: function(cb){
        if (cb == undefined) { throw new Error("Please specify a callback function!"); }
        exec(cb, null, "BecoCordovaPlugin", "getHSID", []);
    }
}

module.exports = BecoCordovaPlugin;

////////////////////////////////////////////////
// End of File
////////////////////////////////////////////////
