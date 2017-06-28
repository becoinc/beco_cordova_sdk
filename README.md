

# ![Beco Logo](https://github.com/becoinc/beco_cordova_sdk/raw/develop/readme-images/beco-logo-small.png) Beco Cordova SDK
_An Apache Cordova version of the Beco SDK with Android and iOS support._

The Beco SDK provides developers a rapid path towards iBeacon integration. While other solutions focus on providing a light wrapper to existing beacon APIs, the Beco Cordova SDK has taken the approach of providing a turn-key solution with a greatly simplified API, designed to let users leverage the power of the Beco Cloud service while being as easy to integrate as Beco Beacons are to deploy.

This README provides installation and usage instructions for developers deploying the SDK in their cross-platform Cordova application. Please read this entire document before developing with the Beco Cordova SDK.

## Table of Contents
- [Release Notes](#release-notes)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
    - [Cordova Plugin Installation](#cordova-plugin-installation)
    - [iOS Project Configuration](#ios-project-configuration)
    - [Android Project Configuration](#android-project-configuration)
        - [Sample Permissioning Code](#sample-permissioning-code)
- [SDK Overview](#sdk-overview)
- [SDK Guide](#sdk-guide)
    - [1) Initialization & Setup](#1-initialization--setup)
    - [2) Registering Handset](#2-registering-handset)
    - [3) Registering Event Callbacks](#3-registering-event-callbacks)
    - [4) Start/Stop Scanning](#4-start-stop-scanning)
    - [5) Adjusting Tweak Values](#5-adjusting-tweak-values)
    - [6) Utility / Information Functions](#6-utility-information-functions)
    - [7) Additional Functionality](#7-additional-functionality)
- [Nuances](#nuances)
    - [Bluetooth Status](#bluetooth-status)
    - [Long-Term Analytics](#long-term-analytics)
- [Example Application](#Example Application)
- [Appendix](#Appendix)
    - [License](#License)
    - [Export Statement](#Export Statement)

## Release Notes
v1.0.0 _BETA_ - Initial release of the Beco Cordova SDK. Includes support for Android and iOS. This version of the plugin supports realtime location data and long-term analytics data collection. The plugin is currently in BETA, and functionality may change in future releases.

## Prerequisites
The Beco Cordova SDK supports Cordova version ???.
It has been tested using Apache Cordova version 7.0.1

The Beco SDK requires a Bluetooth 4.0 (BLE, Bluetooth Smart) compatible iOS device running at least iOS 9.0. We have tested extensively on the iPhone 5s, iPhone 6/6+, iPad Mini and iPad Air 2 on both iOS 9.3.x and 10.3. We expect other iOS devices and versions to work similarly, but they have not been tested by Beco.

The Beco iOS SDK requires iOS 9.0 or newer. The SDK has been built with Universal (iPhone and iPad) support.

## Installation

#### Cordova Plugin Installation
    cordova plugin add https://github.com/becoinc/beco_cordova_sdk.git

#### iOS Project Configuration
There are several platform-specific settings that must be configured to deploy an application using the Beco Cordova SDK on iOS.

#### Android Project Configuration
There are several platform-specific settings that must be configured to deploy an application using the Beco Cordova SDK on Android. Most importantly, Android's recent changes to the Permissioning system require the application to request permissions at runtime, which is outside the scope of the Beco Cordova SDK. The developer may configure android permissioning via an existing plugin, as demonstrated below, or by developing their own plugin to show a custom permission dialog.

###### Sample Permissioning
A simple way to enable Android permissioning is via the `cordova-plugin-android-permissions` plugin, which provides a JS interface for the Android SDK's permissioning system.

To install `corova-plugin-android-permissions` in your project, run the following cordova command in your project directory:
```
cordova plugin add cordova-plugin-android-permissions
```

Then, once the application initializes, request permission using the following code, optionally passing in success/error callbacks to run code based on whether the application
has the correct permissions.
```javascript
var permissions = cordova.plugins.permissions;
permissions.requestPermission(permissions.ACCESS_COARSE_LOCATION, success, error);
```

If permission is already granted, the method will silently pass. If no permissions are granted, it will
display a dialog. If the app does not have location permissions when the `startScan()` method is called, the `reportStartScanComplete` event will return an error code.

## SDK Overview

Below is an outline of all the functionality provided by the Cordova SDK. Usage of the individual commands in an application is described in detail in the Using the Beco SDK section.

Note: Many of the SDK's functions operate asynchronously in the background thread. Because of this, they do not return data directly, and instead use callback functions in a similar format to many other JS frameworks. For example, to obtain the version, use the following code:

```javascript
BecoCordovaPlugin.getVersion(function(version){
    console.log("Beco SDK Version: "+version);
});
```

#### Core
Used to initialize the SDK, configure credentials and handset metadata, and start and stop the beacon scanning system.
```javascript
BecoCordovaPlugin.setCredentials(hostname, username, password);
BecoCordovaPlugin.registerHandset(handsetId, personId, groupId, userData, successCallback, failureCallback);
BecoCordovaPlugin.startScan();
BecoCordovaPlugin.stopScan();
```
#### Event Callback Functions
Used to register callback functions that will be called periodically in response to events generated by the SDK, including realtime location updates and error states.
```javascript
BecoCordovaPlugin.onReportStartScanComplete(callback);
BecoCordovaPlugin.onReceiveLocationData(callback);
BecoCordovaPlugin.onReportAppHit(callback);
BecoCordovaPlugin.onReportError(callback);
```
#### Tweak Values
Used to view/modify adjustment variables that can be used to tweak the performance of the beacon scanner.
```javascript
BecoCordovaPlugin.setThresholdAdjustment(value);
BecoCordovaPlugin.getThresholdAdjustment(callback);
BecoCordovaPlugin.setRefreshInterval(value);
BecoCordovaPlugin.getRefreshInterval(callback);
```
#### Utility / Information
Used to get various information about the Sdk, such as the version or current state of the scanner.
```javascript
BecoCordovaPlugin.getVersion(callback);
BecoCordovaPlugin.getPlatformVersion(callback);
```


## SDK Guide

#### 1) Initialization & Setup

Before using any other functionality of the SDK, your application must authenticate with the SDK. This is done using `setCredentials`, as seen below.

```javascript
BecoCordovaPlugin.setCredentials(hostname, username, password);
```
- `hostname` can be set to “api.beco.io”, to point to Beco's private cloud service.
- `username` refers to the SDK Username that has been provided via your Beco license.
- `password` refers to the SDK Password that has been provided via your Beco license.

Please note that the username/password can be hardcoded into your application, as these values are only used for authentication with the Beco SDK and Beco Cloud. User tracking utilizes a separate set of developer-defined credentials, set with the `registerHandset` function.
Once this command has been called, the rest of the Beco Cordova SDK can be used.

#### 2) Registering Handset

After the app is first installed, you must register the handset with the Beco SDK. This function configures the phone to begin to be tracked with the SDK.

```javascript
BecoCordovaPlugin.registerHandset(handsetId,
                                   personId,
                                    groupId,
                                   userData,
                    function success(){...},
                    function failure(){...});
```


It is safe to call this function at every application startup. If the handset has already been registered, the function will silently skip the handset registration and call the success function.
- `handsetId`: A UUID identifying the phone. By default, this parameter can be set to `null`, and will be auto-generated. If you are utilizing location data for advertising, this must be the IDFA provided by Apple or the Google Play Services.

- `personId`: This should be a unique, persistent identifier that will be used to identify the current user across sessions. It is important that this value stays constant across sessions in order for correct analytics data to be generated. Any plaintext string can be used for this identifier. A good value for this would be device IDFV or login username for your app, if relevant. If this is not relevant, `null` is an acceptable value, although no value will limit analytics tracking accuracy.

- `groupId`: This value should be unique, persistent identifier that will be used to identify the group the current user is a part of within an organization. It is important that this value stays constant across sessions in order for correct analytics data to be generated. A good value for this would be the department name, if deployed against multiple client groups. If this is not relevant, `null` is an acceptable value, although no value will limit analytics tracking accuracy.


- `userData`: This is an arbitrary string that can be used by your developers to save metadata associated with a headset. For example, this could be used to link a Beco Handset with a user account within an app's infrastructure. Please note that this data will only be saved if the handset is being registered for the first time. This data can be retrieved using the Beco Web API endpoints. If this is not relevant, `null` is an acceptable value.


#### 3) Registering Event Callbacks
The SDK returns real-time location data using callback functions that can be registered at any time. The SDK will call the callback functions each time new data is generated for the corresponding event. By using these event callback functions, you can obtain realtime location data from the SDK.
It is recommended that you register callback functions before beginning the scan so that your application does not miss events returned before the callbacks have been registered.

The following events are supported:

|Event Name|Callback Setter Function|
|---|---|
|reportStartScanComplete|`BecoCordovaPlugin.onReportStartScanComplete(callback)`|
|reportAppHit|`BecoCordovaPlugin.onReportAppHit(callback)`|
|receiveLocationData|`BecoCordovaPlugin.onReceiveLocationData(callback)`|
|reportError|`BecoCordovaPlugin.onReportError(callback)`|

These events are described in more detail below.

###### onReceiveLocationData

This event will return realtime location data based on the beacon scanning system.
You may get the same location data sent multiple times as a status refresh. It is up to the user to handle this condition.
When no location data is available, or the location is ambiguous, the event will receive a `null` object.

The SDK may report an unknown location for one of several reasons:
1. You may be out of the reliable range of your registered Beco Beacons.
2. The RF environment is such that your location is ambiguous. You are neither here nor there and the SDK is informing you of that situation.
3. The handset does not have an available Internet connection and you have changed locations.

The location data will be returned as a JS object, displayed here as JSON:
```JSON
{
    "errorCode" : 0,
    "errorString" : "Error String"
}
```
Depending on the configuration of your beacon, some of these fields may be left blank. Many of these fields are editable via the Beco Cloud Portal
If you wish to use these fields for realtime location data in your app, the use of `place.placeId` as an identifier is recommended. Using Beacon IDs to determine location is not advised, since multiple beacons can be grouped into a single place.

In foreground mode, the onReceiveLocationData event will be called approximately once every 10 seconds, and the frequency can be tweaked via the SDK (See “Adjusting Tweak Values”).
In background mode, the onReceiveLocationData will be called approximately once every 1-3 minutes.

###### onReportAppHit
This event will return a Beco Beacon ID corresponding to the closest beacon to the phone's location. This event is called as soon as the SDK detects a beacon and before it sends the data to the Beco Cloud to obtain more detailed information. **This event is deprecated**, and is currently disabled on Android. To access realtime location hits, please use the onReceiveLocationData event.

###### onReportError
This event will fire when an SDK error/event has occurred. The error data will be returned as a JS object, displayed here as JSON:
```JSON
{
    "errorCode" : 0,
    "errorString" : "Error String"
}
```

The following errors may occur:
|Error Code|Error String|Description|
|---|---|---|
|0|Credential Mismatch|The SDK Credentials specified do not match the beacon scanned.
|1|Customer Not Found|The SDK Credentials specified were not found as a customer.
|2|Rate Limit Exceeded|The server has reported a rate limit violation.
|3|Server Communication failure|There was a problem communicating with the Beco Cloud Services.
|4|Bluetooth Disabled|Bluetooth has been disabled. This event will not fire with the current API version (See "Nuances")
|5|Bluetooth Enabled|Bluetooth has been reenabled. This event will not fire with the current API version (See "Nuances")
|6|Location Disabled|Location Services have been disabled.
|7|Location Enabled|Location Services have been reenabled.

###### onReportStartScanComplete
This event will fire when the SDK has started scanning, and provides a way to diagnose the status of the beacon scanning system.The event data will be returned as a JS object, displayed here as JSON:
```JSON
{
    "statusCode" : 0,
    "statusString" : "Status String"
}
```

The following codes may occur:

|Status Code|Status String|Description|
|---|---|---|
|0|Success|The scan has started successfully.
|1|Unauthorized|The user has not authorized the app with the correct permissions yet.
|2|Bluetooth Off|Bluetooth is turned off. This event will not fire with the current API version (See "Nuances")
|3|Bluetooth Unsupported|Bluetooth is unsupported. This event will not fire with the current API version (See "Nuances")
|4|Bluetooth Unauthorized|Bluetooth is unauthorized. This event will not fire with the current API version (See "Nuances")
|5|Bluetooth Unknown|General Error Code
|6|Network Error|There is no cellular or WiFi connection available.
|7|Invalid Credentials|The SDK Credentials provided are invalid.
|8|Already Scanning|The SDK is already scanning for beacons.

#### 4) Start/Stop Scanning

To start scanning for beacons, call the following command:

```javascript
BecoCordovaPlugin.startScan();
```
The Beco SDK will begin scanning for beacons in the background, and will periodically call the registered event callbacks. In order for the SDK to function properly, you should call `startScan()` as soon as possible after your app has launched.

Once you call `startScan()` the SDK will continue to scan for beacons until `stopScan()` is called. The SDK will automatically stay running in the background and wake the phone up when possible to process beacon information when permitted by iOS. The SDK will also permit the app to relaunch after either a phone reboot or double-tap- home swipe-kill, as long as the phone has been unlocked at least once.

If you wish to stop scanning for beacons (For example, if the user logs out in your application, or you are not currently searching for locations), call the following command:

```javascript
BecoCordovaPlugin.stopScan();
```
However, it is recommended that you do not stop scanning for beacons after starting the scan. The Beco SDK has been designed to minimally impact battery life, and continuous scanning for beacons will allow collection of accurate long-term analytics data for your space.

#### 5) Adjusting Tweak Values
The SDK has several tweak values that can be adjusted to alter how the algorithm performs.

##### Threshold Adjustment:
This value adjusts the positioning sensitivity of the phone.

We recommend using our default, set at '3', however for applications that require the Beco Beacons to be installed in higher ceilings
(5-6 meters), it will be necessary to increase the sensitivity level in order to ensure higher levels of location accuracy.
The higher the ceiling, the higher this threshold should be.

For other applications, such as placing a Beco Beacon on a desk or other very close applications (less than 1 meter), you can
decrease this value substantially in order to maintain location precision.

This value must be determined experimentally. We recommend using the default value unless default behavior shows
poor location tracking. Acceptable values are from -20 to 50.

the threshold adjustment value can be set in the following manner:
```javascript
BecoCordovaPlugin.setThresholdAdjustment(value);
```
You can retrieve the current value of the threshold adjustment tweak using
```javascript
BecoCordovaPlugin.getThresholdAdjustment(function(value){
    console.log("Value of Threshold Adjustment: "+value);
});
```

##### Refresh Interval:
This value determines the interval at which the SDK will scan for beacons and call the event handler function. By default, this is set at 10 (seconds). The valid range is 2 to 300 inclusive. Lowering the value will result in the SDK sendings events more frequently, and higher values will result in the SDK sending events less frequently. The value can be set in the following manner:
```javascript
BecoCordovaPlugin.setRefreshInterval(value);
```
You can retrieve the current value of the refresh interval tweak using
```javascript
BecoCordovaPlugin.getRefreshInterval();
```

#### 6) Utility / Information Functions

The API provides several utility and information functions that can be used to obtain information about the API.

To get the version of the Beco Cordova SDK, use the following command:
```javascript
BecoCordovaPlugin.getVersion(function(version){
    console.log("Beco SDK Version: "+version);
});
```
To get the version of the Beco SDK for the platform (iOS or Android) that the app is running on, use the following command:
```javascript
BecoCordovaPlugin.getPlatformVersion(function(version){
    console.log("Beco SDK Platform Version: "+version);
});
```

#### 7) Additional Functionality
The Beco Cordova SDK limits its functionality to basic realtime occupancy data.
Long-term occupancy data and additional metadata about the user can be retrieved using the Beco Cloud API, documented at [https://dev.beco.io/docs](https://dev.beco.io/docs). This API can be accessed using basic Javascript connection
to the web endpoints and is compatible with the Beco Cordova SDK.

## Nuances
This section describes nuances of using the Beco SDK, and any features that are not immediately obvious but are necessary for proper usage of the API.

#### Bluetooth Status

Since the Beco SDK does not interface with Bluetooth directly, using Bluetooth via the Location Services API, it will not be aware when Bluetooth is disabled. If the application is scanning with bluetooth disabled, the `onReceiveLocationData` will receive a `null` location value, representing an `Unknown` location.

It is up to the developer to ensure their UI/UX communicates to the user that Bluetooth be enabled, even though the app itself does not require Bluetooth permissions.

Specifically, on iOS the SDK does not invoke `CBCentralManager` to detect the current phone Bluetooth enabled/disabled state. This is done to minimize user annoyance with OS pop-ups. In certain circumstances iOS will prompt the user to enable Bluetooth for Location services. If SDK customers wish to remind their app users about enabling Bluetooth, then they should invoke `CBCentralManager` as appropriate. No beacons will be detected if Bluetooth is disabled.

#### Long-Term Analytics
The Beco SDK collects long-term analytics data for the space in which your beacons have been installed. This data can be analyzed through the [Beco Cloud Portal](https://portal.beco.io/). This analytics data collection is built into the API, and does not require additional configuration.

## Example Application
An example application has been included with this repository. The example application demonstrates the functionality of the Beco Cordova SDK in a JS-based app. Before running the example application, you must insert your SDK Credentials into `www/js/index.js`, the root javascript file for the project. Once you build and run the example application on a phone and configure your Beco Beacons in your space, you should be able to walk around the space and view realtime location data. Specific configuration is described in the `README.md` within the example application directory.

## Appendix
#### License

This document, the Beco Cordova SDK and the included sample application are subject to the Beco SDK license agreement. A copy of this agreement is available at https://www.beco.io/sdk-license-agreement.pdf, and has been included in this repository in `LICENSE.md`.

#### Export Statement
You understand that the Software may contain cryptographic functions that may be subject to export restrictions, and you represent and warrant that you are not located in a country that is subject to United States export restriction or embargo, including Cuba, Iran, North Korea, Sudan, Syria or the Crimea region, and that you are not on the Department of Commerce list of Denied Persons, Unverified Parties, or affiliated with a Restricted Entity.

You agree to comply with all export, re-export and import restrictions and regulations of the Department of Commerce or other agency or authority of the United States or other applicable countries. You also agree not to transfer, or authorize the transfer of, directly or indirectly, the Software to any prohibited country, including Cuba, Iran, North Korea, Sudan, Syria or the Crimea region, or to any person or organization on or affiliated with the Department of
Commerce lists of Denied Persons, Unverified Parties or Restricted Entities, or otherwise in violation of any such restrictions or regulations.
