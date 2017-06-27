////////////////////////////////////////////////
// Beco, Inc
// Module created by: Chris Dalke, chrisd@beco.io
////////////////////////////////////////////////
// Beco Cordova Plugin
// Objective-C (iOS) Plugin implementation
////////////////////////////////////////////////

/*
 Bridge module between the Cordova/JS wrapper for
 the Beco API, and the iOS Beco API.
 */

////////////////////////////////////////////////
// Header imports
////////////////////////////////////////////////

#import <Cordova/CDV.h>
#import <BecoSDK/BecoSDK-Swift.h>

//Utility macro; replaces nil values with an empty string
#if !defined(StringOrEmpty)
#define StringOrEmpty(A)  (A == nil ? @"" : A)
#endif

#define debug true

////////////////////////////////////////////////
// Cordova Plugin Definition
////////////////////////////////////////////////

@interface BecoCordovaPlugin : CDVPlugin <BecoSDKDelegate> {
    
    //SDK instance
    BecoSDKInterface* sdk;
    
    //Strings that encode the callback function IDs for event functions
    //These are called from the delegate functions in this class
    NSString* onReceiveLocationDataCallbackId;
    NSString* onReportErrorCallbackId;
    NSString* onReportAppHitCallbackId;
    NSString* onReportStartScanCompleteCallbackId;
    
    //Tweak values, store a copy so we can return values via getters
    NSNumber* refreshIntervalValue;
    NSNumber* thresholdAdjustmentValue;
    NSUUID* hsid;
}

// Publically accessible API commands
// Called from the JS Wrapper
- (void)getVersion:(CDVInvokedUrlCommand*)command;
- (void)setCredentials:(CDVInvokedUrlCommand*)command;
- (void)onReceiveLocationData:(CDVInvokedUrlCommand*)command;
- (void)onReportError:(CDVInvokedUrlCommand*)command;
- (void)onReportAppHit:(CDVInvokedUrlCommand*)command;
- (void)onReportStartScanComplete:(CDVInvokedUrlCommand*)command;
- (void)registerHandset:(CDVInvokedUrlCommand*)command;
- (void)startScan:(CDVInvokedUrlCommand*)command;
- (void)stopScan:(CDVInvokedUrlCommand*)command;
- (void)setThresholdAdjustment:(CDVInvokedUrlCommand*)command;
- (void)getThresholdAdjustment:(CDVInvokedUrlCommand*)command;
- (void)setRefreshInterval:(CDVInvokedUrlCommand*)command;
- (void)getRefreshInterval:(CDVInvokedUrlCommand*)command;
- (void)getSdkState:(CDVInvokedUrlCommand*)command;
- (void)getHSID:(CDVInvokedUrlCommand*)command;

// Private delegate functions
// Registered with the API, and call whenever an event occurs
- (void)becoSdkDelegateWithReportError:(enum BecoSDKErrorCode)error;
- (void)becoSdkDelegateWithReceiveLocationData:(LocationData *)locationData;
- (void)becoSdkDelegateWithReportAppHit:(NSString *)becoId;
- (void)becoSdkDelegateWithReportStartScanComplete:(enum BecoSDKReturnStatus)reportStartScanComplete;

@end

////////////////////////////////////////////////
// Cordova Plugin Implementation
////////////////////////////////////////////////

@implementation BecoCordovaPlugin

/*
 pluginInitialize
 Called when the Cordova instance initializes.
 Used to create the Beco API interface.
 Parameters: *None*
 */
- (void)pluginInitialize
{
    //Initialize the Beco SDK
    self->sdk = [[BecoSDKInterface alloc]init];
    self->sdk.delegate = self;
    
    //Set the default hostname to Beco Production.
    self->sdk.hostname = @"api.beco.io";
    
    //Initialize basic tweak values to their defaults
    self->refreshIntervalValue = [NSNumber numberWithInt:10];
    self->thresholdAdjustmentValue = [NSNumber numberWithInt:3];
    
    //Pull ID from system since we are forcing usage of IDFV for cordova iOS
    hsid = [[UIDevice currentDevice] identifierForVendor];
    
    //Display a debug message
    //NSLog(@"[Beco SDK] Initialized Cordova Plugin.");
}

////////////////////////////////////////////////
// Lifecycle / Core API Functions
////////////////////////////////////////////////

/*----------------------------------------------
 startScan
 Starts the background scanning for beacons.
 Parameters: *None*
 */
- (void)startScan:(CDVInvokedUrlCommand*)command
{
    [self.commandDelegate runInBackground:^{
        //Start the scan
        [self->sdk startScanAndReturnError:nil];
        
        //Display a debug message
        if (debug){ NSLog(@"[Beco SDK] Started scanning for beacons..."); }
        
        //Send a default 'OK' result
        CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];
    }];
}

/*----------------------------------------------
 stopScan
 Ends the background scanning for beacons.
 Parameters: *None*
 */
- (void)stopScan:(CDVInvokedUrlCommand*)command
{
    [self.commandDelegate runInBackground:^{
        //Stop the scan
        [self->sdk stopScan];
        
        //Display a debug message
        if (debug){ NSLog(@"[Beco SDK] Stopped scanning for beacons.");}
        
        //Send a default 'OK' result
        CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];
    }];
}

/*----------------------------------------------
 registerHandset
 Registers a handset with the Beco API.
 Parameters:
 */
- (void)registerHandset:(CDVInvokedUrlCommand*)command
{
    [self.commandDelegate runInBackground:^{
        //Send a default 'OK' result
        __block CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        
        //Display a debug message
        if (debug){ NSLog(@"[Beco SDK] Attempting to register handset...");}
        
        //Gather parameters
        NSUUID *handsetId = nil;
        NSString *userDataString = nil;
        NSString *personId = nil;
        NSString *groupId = nil;
        
        @try {
            //Handle error here if the UUID is of an invalid format
            if ([command.arguments objectAtIndex:0] != [NSNull null]){
                handsetId = [[NSUUID alloc] initWithUUIDString:[command.arguments objectAtIndex:0]];
            }
            
            if ([command.arguments objectAtIndex:1] != [NSNull null]){
                personId = [command.arguments objectAtIndex:1];
            }
            
            if ([command.arguments objectAtIndex:2] != [NSNull null]){
                groupId = [command.arguments objectAtIndex:2];
            }
            
            if ([command.arguments objectAtIndex:3] != [NSNull null]){
                userDataString = [command.arguments objectAtIndex:3];
            }
            
            NSDictionary *userDataDict = @{
                                           @"userData" : StringOrEmpty(userDataString)
                                           };
            
            //handsetId is nil because we are forcing usage of IDFV
            bool ignoredResult = [ self->sdk registerHandset: nil
                                                    personId: personId
                                                     groupId: groupId
                                                    userData: [userDataDict mutableCopy]
                                                  completion: ^void( BOOL success, RegisterHandsetReply* data )
                                  {
                                      if (success){
                                          
                                          if (data == nil) {
                                              result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"Handset has already been registered, you only need to register a handset once. See the Beco Cordova User's Guide for details."];
                                              //Display a debug message
                                              if (debug){ NSLog(@"[Beco SDK] Handset is already registered. ");}
                                          } else {
                                              //Display a debug message
                                              if (debug){ NSLog(@"[Beco SDK] Successfully registered handset!");}
                                              NSDictionary *resultDataDict = @{
                                                                               @"becoHSID" : StringOrEmpty([data.becoHSID UUIDString]),
                                                                               @"idfa" : StringOrEmpty([data.idfa UUIDString]),
                                                                               @"created" : StringOrEmpty([NSNumber numberWithLong:data.created]),
                                                                               @"createdDate" : StringOrEmpty(data.createdDate.description),
                                                                               @"personId" : StringOrEmpty(data.personId),
                                                                               @"groupId" : StringOrEmpty(data.groupId),
                                                                               @"userData" : StringOrEmpty(data.userData)
                                                                               };
                                              result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:resultDataDict];
                                          }
                                      } else {
                                          //Display a debug message
                                          if (debug){ NSLog(@"[Beco SDK] Failed to register handset!");}
                                          result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Failed to register handset. Please verify your API credentials have been set and registerHandset parameters are valid."];
                                      }
                                      
                                      [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];
                                  } ];
            
        } @catch (NSException* exception){
            result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Failed to register handset. Invalid parameter set!"];
            if (debug){ NSLog(@"Exception Reason: %@ Callstack: %@",exception.reason,[exception callStackSymbols]);}
            [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];
        }
    }];
}

////////////////////////////////////////////////
// Event Listener Functions
////////////////////////////////////////////////

/*----------------------------------------------
 onReceiveLocationData
 Registers a callback function for the corresponding delegate function.
 Parameters: *callbackFunction*
 */
- (void)onReceiveLocationData:(CDVInvokedUrlCommand*)command
{
    [self.commandDelegate runInBackground:^{
        //Display debug message
        if (debug){ NSLog(@"[Beco SDK] Registering callback function for receiveLocationData event.");}
        
        onReceiveLocationDataCallbackId = command.callbackId;
    }];
}

/*----------------------------------------------
 onReportError
 Registers a callback function for the corresponding delegate function.
 Parameters: *callbackFunction*
 */
- (void)onReportError:(CDVInvokedUrlCommand*)command
{
    [self.commandDelegate runInBackground:^{
        //Display debug message
        if (debug){ NSLog(@"[Beco SDK] Registering callback function for reportError event.");}
        
        onReportErrorCallbackId = command.callbackId;
    }];
}

/*----------------------------------------------
 onReportAppHit
 Registers a callback function for the corresponding delegate function.
 Parameters: *callbackFunction*
 */
- (void)onReportAppHit:(CDVInvokedUrlCommand*)command
{
    [self.commandDelegate runInBackground:^{
        //Display debug message
        if (debug){ NSLog(@"[Beco SDK] Registering callback function for reportAppHit event.");}
        
        onReportAppHitCallbackId = command.callbackId;
    }];
}

/*----------------------------------------------
 onReportStartScanComplete
 Registers a callback function for the corresponding delegate function.
 Parameters: *callbackFunction*
 */
- (void)onReportStartScanComplete:(CDVInvokedUrlCommand*)command
{
    [self.commandDelegate runInBackground:^{
        //Display debug message
        if (debug){ NSLog(@"[Beco SDK] Registering callback function for startScanComplete event.");}
        
        onReportStartScanCompleteCallbackId = command.callbackId;
    }];
}

////////////////////////////////////////////////
// Delegate Functions
////////////////////////////////////////////////

- (void)becoSdkDelegateWithReportError:(enum BecoSDKErrorCode)error
{
    [self.commandDelegate runInBackground:^{
        if (onReportErrorCallbackId != nil){
            //If we've set a callback ID for the 'report error' event, call it and return data.
            
            //Build temporary array of error code strings
            NSArray *tempStatusArray = @[@"Credential Mismatch",
                                         @"Customer Not Found",
                                         @"Rate Limit Exceeded",
                                         @"Server Communication Failure",
                                         @"Bluetooth Disabled",
                                         @"Bluetooth Enabled",
                                         @"Location Services Disabled",
                                         @"Location Services Enabled"];
            
            //encode error as JSON dictionary
            NSDictionary *messageDict = @{
                                          @"errorCode" : [NSNumber numberWithInt:error],
                                          @"errorString" : tempStatusArray[error]
                                          };
            
            CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:messageDict];
            [result setKeepCallbackAsBool:YES]; //Set flag to keep the callback function so we can call it multiple times
            
            //Display a debug message
            if (debug){ NSLog(@"[Beco SDK] Got reportError event. Calling callback function...");}
            
            [self.commandDelegate sendPluginResult:result callbackId:onReportErrorCallbackId];
        }
    }];
}

- (void)becoSdkDelegateWithReceiveLocationData:(LocationData *)locationData
{
    [self.commandDelegate runInBackground:^{
        if (onReceiveLocationDataCallbackId != nil){
            
            //Default OK result without any data attached
            CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
            
            //Attach data to result if the location returned isn't null
            if (locationData != nil){
                NSString* becoId = locationData.becoId;
                NSString* placeName = locationData.place.placeName;
                NSString* locationName = locationData.place.location.locationName;
                
                NSNumber *locCapacity =[NSNumber numberWithInt:(uint32_t)locationData.place.capacity];
                NSString *handsetId =[self->hsid UUIDString];
                
                NSDictionary *locDict = @{
                                          @"becoId" : StringOrEmpty(locationData.becoId),
                                          @"hsid" : StringOrEmpty(handsetId),
                                          @"place" : @{
                                                  @"placeName" : StringOrEmpty(locationData.place.placeName),
                                                  @"placeId" : locationData.place.placeId == nil ? @"" : [locationData.place.placeId UUIDString],
                                                  @"comments" : StringOrEmpty(locationData.place.comments),
                                                  @"capacity" : StringOrEmpty(locCapacity),
                                                  @"floor": @{
                                                          @"name" : StringOrEmpty(locationData.place.floor.name),
                                                          @"floorId" : locationData.place.floor.floorId == nil? @"" : [locationData.place.floor.floorId UUIDString]
                                                          },
                                                  @"location": @{
                                                          @"locationName" : StringOrEmpty(locationData.place.location.locationName),
                                                          @"locationId" : locationData.place.location.locationId == nil ? @"" : [locationData.place.location.locationId UUIDString]
                                                          }
                                                  }
                                          };
                
                if (debug){ NSLog(@"[Beco SDK] Received Location Data: Beco Id: %@, Place: %@, Location: %@",becoId, placeName, locationName);}
                
                //Override default result to return the location data as a dictionary
                result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:locDict];
            }
            
            //Set flag to keep the callback function so we can call it multiple times
            [result setKeepCallbackAsBool:YES];
            
            //Display a debug message
            if (debug){ NSLog(@"[Beco SDK] Got receiveLocationData event. Calling callback function...");}
            
            //Send the result to the callback function
            [self.commandDelegate sendPluginResult:result callbackId:onReceiveLocationDataCallbackId];
        }
    }];
}

- (void)becoSdkDelegateWithReportAppHit:(NSString *)becoId
{
    [self.commandDelegate runInBackground:^{
        if (onReportAppHitCallbackId != nil){
            //If we've set a callback ID for the 'report app hit' event, call it and return data.
            
            //Report app hit as a json dict, only return becoId
            NSDictionary *messageDict = @{
                                          @"becoId" : becoId
                                          };
            
            CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:messageDict];
            [result setKeepCallbackAsBool:YES]; //Set flag to keep the callback function so we can call it multiple times
            
            //Display a debug message
            if (debug){ NSLog(@"[Beco SDK] Got appHit event. Calling callback function...");}
            
            [self.commandDelegate sendPluginResult:result callbackId:onReportAppHitCallbackId];
        }
    }];
}

- (void)becoSdkDelegateWithReportStartScanComplete:(enum BecoSDKReturnStatus)reportStartScanComplete
{
    [self.commandDelegate runInBackground:^{
        if (onReportStartScanCompleteCallbackId != nil){
            //If we've set a callback ID for the 'report scan complete' event, call it and return data.
            
            //Build temporary array of status string messages
            NSArray *tempStatusArray = @[@"Success",
                                         @"Location Unauthorized",
                                         @"Bluetooth Off",
                                         @"Bluetooth Unsupported",
                                         @"Bluetooth Unauthorized",
                                         @"Bluetooth Unknown",
                                         @"Network Error",
                                         @"Credential Error",
                                         @"Already Scanning"];
            
            //Send as JSON
            NSDictionary *messageDict = @{
                                          @"statusCode" : [NSNumber numberWithInt:reportStartScanComplete],
                                          @"statusString" : tempStatusArray[reportStartScanComplete]
                                          };
            
            CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:messageDict];
            [result setKeepCallbackAsBool:YES]; //Set flag to keep the callback function so we can call it multiple times
            
            //Display a debug message
            if (debug){ NSLog(@"[Beco SDK] Got startScanComplete event. Calling callback function...");}
            
            [self.commandDelegate sendPluginResult:result callbackId:onReportStartScanCompleteCallbackId];
        }
    }];
}

////////////////////////////////////////////////
// Setters
////////////////////////////////////////////////

/*----------------------------------------------
 setCredentials
 Sets the username and password that the Beco API will use.
 Parameters: username, plainPw
 */
- (void)setCredentials:(CDVInvokedUrlCommand*)command
{
    [self.commandDelegate runInBackground:^{
        //Configure OK result
        CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        
        @try {
            NSString *hostname = [command.arguments objectAtIndex:0]; //Get the hostname as a string
            NSString *username = [command.arguments objectAtIndex:1]; //Get the username as a string
            NSString *plainPw = [command.arguments objectAtIndex:2];  //Get the password as a string
            self->sdk.hostname = hostname; //Set the SDK hostname
            [self->sdk setCredentials:username plainPw:plainPw]; //Set the SDK credentials
            
            //Display debug message
            if (debug){ NSLog(@"[Beco SDK] Set user API credentials.");}
        }
        @catch (NSException *exception) {
            //If there's an error, return a failure result.
            result =[CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:exception.reason];
            
            //Display debug message
            if (debug){ NSLog(@"[Beco SDK] Failed to set user API credentials! %@",exception.reason);}
        }
        
        //Send the result to the passed callback function.
        [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];
    }];
}

/*----------------------------------------------
 setThresholdAdjustment
 Sets the threshold adjustment tweak value.
 Parameters: thresholdAdjustment
 */
- (void)setThresholdAdjustment:(CDVInvokedUrlCommand*)command
{
    [self.commandDelegate runInBackground:^{
        CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        
        @try {
            NSInteger thresholdAdjustment = (NSInteger)[command.arguments objectAtIndex:0];
            self->sdk.thresholdAdjustment = thresholdAdjustment;
            self->thresholdAdjustmentValue = [NSNumber numberWithInt:(uint32_t)thresholdAdjustment];
            
            //Display debug message
            if (debug){ NSLog(@"[Beco SDK] Set thresholdAdjustment tweak value.");}
        }
        @catch (NSException *exception) {
            //If there's an error, return a failure result.
            result =[CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:exception.reason];
            
            //Display debug message
            if (debug){ NSLog(@"[Beco SDK] Failed to set thresholdAdjustment tweak value! %@",exception.reason);}
        }
        
        //Send the result to the passed callback function.
        [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];
    }];
}


/*----------------------------------------------
 setRefreshInterval
 Sets the refresh interval tweak value.
 Parameters: refreshInterval
 */
- (void)setRefreshInterval:(CDVInvokedUrlCommand*)command
{
    [self.commandDelegate runInBackground:^{
        CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        
        @try {
            NSInteger refreshInterval = (NSInteger)[command.arguments objectAtIndex:0];
            self->sdk.refreshInterval = refreshInterval;
            self->refreshIntervalValue = [NSNumber numberWithInt:(uint32_t)refreshInterval];
            
            //Display debug message
            if (debug){ NSLog(@"[Beco SDK] Set refreshInterval tweak value.");}
        }
        @catch (NSException *exception) {
            //If there's an error, return a failure result.
            result =[CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:exception.reason];
            
            //Display debug message
            if (debug){ NSLog(@"[Beco SDK] Failed to set refreshInterval tweak value! %@",exception.reason);}
        }
        
        //Send the result to the passed callback function.
        [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];
    }];
}

////////////////////////////////////////////////
// Getters
////////////////////////////////////////////////

/*----------------------------------------------
 getVersion
 Gets the version ID for the currently running Beco API.
 Parameters: *None*
 */
- (void)getVersion:(CDVInvokedUrlCommand*)command
{
    [self.commandDelegate runInBackground:^{
        //Get the SDK version and return it as a string with the OK status
        CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:[BecoSDKInterface getSDKVersion]];
        
        //Send the result to the passed callback function.
        [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];
    }];
}

/*----------------------------------------------
 getThresholdAdjustment
 Gets the threshold adjustment tweak value
 Parameters: *None*
 */
- (void)getThresholdAdjustment:(CDVInvokedUrlCommand*)command
{
    [self.commandDelegate runInBackground:^{
        //Send a default 'OK' result with the getter value
        CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsNSInteger:self->sdk.thresholdAdjustment];
        
        [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];
    }];
}

/*----------------------------------------------
 getRefreshInterval
 Gets the refresh interval tweak value
 Parameters: *None*
 */
- (void)getRefreshInterval:(CDVInvokedUrlCommand*)command
{
    [self.commandDelegate runInBackground:^{
        //Send a default 'OK' result with the getter value
        CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsNSInteger: self->sdk.refreshInterval];
        [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];
    }];
}

/*----------------------------------------------
 getSdkState
 Gets the SDK state.
 Parameters: *None*
 */
- (void)getSdkState:(CDVInvokedUrlCommand*)command
{
    [self.commandDelegate runInBackground:^{
        NSNumber* sdkState = [NSNumber numberWithInt:self->sdk.sdkState];
        
        //Build temporary array of status string messages
        NSArray *tempStatusArray = @[@"Stopped",
                                     @"Starting",
                                     @"Waiting for Location Authorization",
                                     @"Authorized",
                                     @"Loading from Cloud",
                                     @"Loading from Cloud Failed",
                                     @"Scanning"];
        
        //Send as JSON
        NSDictionary *messageDict = @{
                                      @"statusCode" : sdkState,
                                      @"statusString" : tempStatusArray[[sdkState intValue]]
                                      };
        
        //Send a default 'OK' result with the getter JSON response
        CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:messageDict];
        
        [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];
    }];
}

/*----------------------------------------------
 getHSID
 Gets the HSID for use with the Beco API.
 Parameters: *None*
 */
- (void)getHSID:(CDVInvokedUrlCommand*)command
{
    [self.commandDelegate runInBackground:^{
        //Send a default 'OK' result with the getter value, TODO send the result as JSON
        //Just pull the IDFV straight from the system since we are forcing usage of IDFV on iOS
        CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:[self->hsid UUIDString]];
        [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];
    }];
}

@end

////////////////////////////////////////////////
// End of File
////////////////////////////////////////////////
