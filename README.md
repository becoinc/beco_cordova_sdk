

# ![Beco Logo](https://github.com/becoinc/beco_cordova_sdk/raw/develop/readme-images/beco-logo-small.png) Beco Cordova SDK
An Apache Cordova version of the Beco SDK with Android and iOS support.

The Beco SDK provides developers a rapid path towards iBeacon integration. While other solutions focus on providing a light wrapper to existing beacon APIs, the Beco Cordova SDK has taken the approach of providing a turn-key solution with a greatly simplified API, designed to let users leverage the power of the Beco Cloud service while being as easy to integrate as Beco Beacons are to deploy.

This README provides installation and usage instructions for developers deploying the SDK in their cross-platform Cordova application.

### Table of Contents
- [Release Notes](#release-notes)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
    - [Cordova Plugin Installation](#cordova-plugin-installation)
    - [iOS Project Configuration](#ios-project-configuration)
    - [Android Project Configuration](#android-project-configuration)
        - [Sample Permissioning Code](#sample-permissioning-code)
- [SDK Overview](#sdk-overview)
- [SDK Guide](#sdk-guide)
    -[1) Initialization & Setup](#1-initialization--setup)
    -[2) Registering Handset](#2-registering-handset)
    -[3) Registering Event Callbacks](#3-registering-event-callbacks)
    -[4) Start/Stop Scanning](#4-start-stop-scanning)
    -[5) Adjusting Tweak Values](#5-adjusting-tweak-values)
    -[6) Utility / Information Functions](#6-utility-information-functions)
    -[7) Additional Functionality](#7-additional-functionality)
- [Nuances](#nuances)
    - [Bluetooth Disabled](#bluetooth-disabled)
    - [Long-Term Analytics](#long-term-analytics)
- [Example Application](#Example Application)
- [Appendix](#Appendix)
    - [License](#License)
    - [Export Statement](#Export Statement)

### Release Notes
v1.0.0 _BETA_ - Initial release of the Beco Cordova SDK. Includes support for Android and iOS. This version of the plugin supports realtime location data and long-term analytics data collection. The plugin is currently in BETA, and functionality may change in future releases.

### Prerequisites
The Beco Cordova SDK supports Cordova version ???.
It has been tested using Apache Cordova version 7.0.1

The Beco SDK requires a Bluetooth 4.0 (BLE, Bluetooth Smart) compatible iOS device running at least iOS 9.0. We have tested extensively on the iPhone 5s, iPhone 6/6+, iPad Mini and iPad Air 2 on both iOS 9.3.x and 10.3. We expect other iOS devices and versions to work similarly, but they have not been tested by Beco.

The Beco iOS SDK requires iOS 9.0 or newer. The SDK has been built with Universal (iPhone and iPad) support.

### Installation

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
display a dialog.

Alternatively,

### SDK Overview

#### API

An outline of all the functionality provided by the Cordova SDK. Usage of the individual commands in an application is described in detail in the *Using the Beco SDK* section.

Core
```javascript
BecoCordovaPlugin.setCredentials(hostname, username, password);
BecoCordovaPlugin.registerHandset(handsetId, personId, groupId, userData, successCallback, failureCallback);
BecoCordovaPlugin.startScan();
BecoCordovaPlugin.stopScan();
```
Event Callback Functions
```javascript
BecoCordovaPlugin.onReportStartScanComplete(callback);
BecoCordovaPlugin.onReceiveLocationData(callback);
BecoCordovaPlugin.onReportAppHit(callback);
BecoCordovaPlugin.onReportError(callback);
```
Tweak Values
```javascript
BecoCordovaPlugin.setThresholdAdjustment(value);
BecoCordovaPlugin.getThresholdAdjustment(callback);
BecoCordovaPlugin.setRefreshInterval(value);
BecoCordovaPlugin.getRefreshInterval(callback);
```
Utility / Information
```javascript
BecoCordovaPlugin.getVersion(callback);
BecoCordovaPlugin.getPlatformVersion(callback);
BecoCordovaPlugin.getSdkState(callback);
```

### SDK Guide

#### 1) Initialization & Setup

Before using any other functionality of the SDK, your application must authenticate with the SDK. This is done using `setCredentials`, as seen below.

```javascript
BecoCordovaPlugin.setCredentials(hostname, username, password);
```
- *hostname* can be set to “api.beco.io”, to point to Beco's private cloud service.
- *username* refers to the username that has been provided via your Beco license.
- *password* refers to the password that has been provided via your Beco license.

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


It is safe to call this function at the start of your application without developing . If the handset has already been registered, the function will silently skip the handset registration and call the success handler.

- handsetId: If you are utilizing location data for advertising, this must be the IDFA provided by Apple or the Google Play Services. Otherwise, this parameter can be set to null.

- personId: This should be a unique, persistent identifier that will be used to identify the current user across sessions. It is important that this value stays constant across sessions in order for correct analytics data to be generated. Any plaintext string can be used for this identifier. A good value for this would be device IDFV or login username.

- groupId: This value should be unique


- userData: This is an arbitrary string that can be used by your developers to save data associated with a headset. Please note that this data will only be saved if the handset is being registered for the first time.




#### 3) Registering Event Callbacks
The SDK returns real-time location data using callback functions that can be registered at any time. The SDK will call the callback functions each time new data is generated for the corresponding event.

The following events are supported:

###### onReceiveLocationData


In foreground mode, the onReceiveLocationData event will be called approximately once every 10 seconds, and the frequency can be tweaked via the SDK (See “Adjusting Tweak Values”).

In background mode, the onReceiveLocationData will be called approximately once every 1-3 minutes.


In order to minimize



###### onReportAppHit
Note: This event is deprecated. To access realtime location hits, please use the onReceiveLocationData event.
###### onReportError
This event will fire when an SDK error/event has occurred.
The following error events may occur:
###### onReportStartScanComplete
This event will fire when the SDK has started scanning, and provides a way to diagnose the status of the beacon scanning system.
The following codes may occur:


using an Event Callback pattern. You can register a function using the following

It is recommended that you register callback functions before beginning the scan so that your application does not miss events returned before the callbacks have been registered.

#### 4) Start/Stop Scanning

To start scanning for beacons, call the following command:

```javascript
BecoCordovaPlugin.startScan();
```
The Beco SDK will begin scanning for beacons in the background, and will periodically call the registered event callbacks.

Once you call `startScan()` the SDK will continue to scan for beacons until `stopScan()` is called. The SDK will automatically stay running in the background and wake the phone up when possible to process beacon information when permitted by iOS. The SDK will also permit the app to relaunch after either a phone reboot or double-tap- home swipe-kill, as long as the phone has been unlocked at least once.

In order for the SDK to function properly, you should call `startScan()` as soon as possible after your app has launched.

If you wish to stop scanning for beacons (For example, if the user logs out in your application, or you are not currently searching for locations), call the following command:

```javascript
BecoCordovaPlugin.stopScan();
```
However, it is recommended that you do not stop scanning for beacons after starting the scan. The Beco SDK has been designed to minimally impact battery life, and continuous scanning for beacons will allow collection of accurate long-term analytics data for your space.

#### 5) Adjusting Tweak Values
The SDK has several tweak values that can be adjusted to alter how the algorithm performs.

###### Threshold Adjustment:
This value determines the sensitivity of the phone, and can be set in the following manner:
```javascript
BecoCordovaPlugin.setThresholdAdjustment(value);
```
You can retrieve the current value of the threshold adjustment tweak using
```javascript
BecoCordovaPlugin.getThresholdAdjustment(function(value){
    console.log("Value of Threshold Adjustment: "+value);
});
```

###### Refresh Interval:
This value determines the interval at which the SDK will scan for beacons and call the event handler function. By default, this is set at 10 (seconds). The value can be set in the following manner:
```javascript
BecoCordovaPlugin.setRefreshInterval(value);
```
You can retrieve the current value of the refresh interval tweak using
```javascript
BecoCordovaPlugin.getRefreshInterval();
```

#### 6) Utility / Information Functions

The API provides several utility and information functions that can be used to.

#### 7) Additional Functionality
The Beco Cordova SDK limits its functionality to basic realtime occupancy data.
Long-term occupancy data and additional metadata about the user can be retrieved using the Beco Cloud API, documented at [https://dev.beco.io/docs](https://dev.beco.io/docs). This API can be accessed using basic Javascript connection
to the web endpoints.

Some basic examples are shown below:

### Nuances
This section describes nuances of using the Beco SDK, and any features that are not immediately obvious but are necessary for proper usage of the API.

#### Bluetooth Disabled

Since the Beco SDK does not interface with Bluetooth directly, using Bluetooth via the Location Services API, it will not be aware when Bluetooth is disabled. If the application is scanning with bluetooth disabled, the `onReceiveLocationData` will receive a `null` location value, representing an `Unknown` location.

It is up to the developer to ensure their UI/UX communicates to the user that Bluetooth be enabled, even though the app itself does not require Bluetooth permissions.

Specifically, on iOS the SDK does not invoke CBCentralManager to detect the current phone Bluetooth enabled/disabled state. This is done to minimize user annoyance with OS pop-ups. In certain circumstances iOS will prompt the user to enable Bluetooth for Location services. If SDK customers wish to remind their app users about enabling Bluetooth, then they should invoke CBCentralManager as appropriate. No beacons will be detected if Bluetooth is disabled.

#### Long-Term Analytics
The Beco SDK collects long-term analytics data for the space in which your beacons have been installed. This data can be analyzed through the [Beco Cloud Portal](https://portal.beco.io/). This analytics data collection is built into the API, and does not require additional configuration.

### Example Application
An example application has been included with this repository. The example application demonstrates the functionality of the Beco Cordova SDK in a JS-based app.

### Appendix
#### License

This document, the Beco Cordova SDK and the included sample application are subject to the Beco SDK license agreement. A copy of this agreement is available at https://www.beco.io/sdk-license-agreement.pdf, and has been included in this repository in `LICENSE.md`.

#### Export Statement
You understand that the Software may contain cryptographic functions that may be subject to export restrictions, and you represent and warrant that you are not located in a country that is subject to United States export restriction or embargo, including Cuba, Iran, North Korea, Sudan, Syria or the Crimea region, and that you are not on the Department of Commerce list of Denied Persons, Unverified Parties, or affiliated with a Restricted Entity.

You agree to comply with all export, re-export and import restrictions and regulations of the Department of Commerce or other agency or authority of the United States or other applicable countries. You also agree not to transfer, or authorize the transfer of, directly or indirectly, the Software to any prohibited country, including Cuba, Iran, North Korea, Sudan, Syria or the Crimea region, or to any person or organization on or affiliated with the Department of
Commerce lists of Denied Persons, Unverified Parties or Restricted Entities, or otherwise in violation of any such restrictions or regulations.
