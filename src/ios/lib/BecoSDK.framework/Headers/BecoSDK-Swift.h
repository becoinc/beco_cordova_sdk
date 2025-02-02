// Generated by Apple Swift version 4.0.3 (swiftlang-900.0.74.1 clang-900.0.39.2)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgcc-compat"

#if !defined(__has_include)
# define __has_include(x) 0
#endif
#if !defined(__has_attribute)
# define __has_attribute(x) 0
#endif
#if !defined(__has_feature)
# define __has_feature(x) 0
#endif
#if !defined(__has_warning)
# define __has_warning(x) 0
#endif

#if __has_attribute(external_source_symbol)
# define SWIFT_STRINGIFY(str) #str
# define SWIFT_MODULE_NAMESPACE_PUSH(module_name) _Pragma(SWIFT_STRINGIFY(clang attribute push(__attribute__((external_source_symbol(language="Swift", defined_in=module_name, generated_declaration))), apply_to=any(function, enum, objc_interface, objc_category, objc_protocol))))
# define SWIFT_MODULE_NAMESPACE_POP _Pragma("clang attribute pop")
#else
# define SWIFT_MODULE_NAMESPACE_PUSH(module_name)
# define SWIFT_MODULE_NAMESPACE_POP
#endif

#if __has_include(<swift/objc-prologue.h>)
# include <swift/objc-prologue.h>
#endif

#pragma clang diagnostic ignored "-Wauto-import"
#include <objc/NSObject.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#if !defined(SWIFT_TYPEDEFS)
# define SWIFT_TYPEDEFS 1
# if __has_include(<uchar.h>)
#  include <uchar.h>
# elif !defined(__cplusplus) || __cplusplus < 201103L
typedef uint_least16_t char16_t;
typedef uint_least32_t char32_t;
# endif
typedef float swift_float2  __attribute__((__ext_vector_type__(2)));
typedef float swift_float3  __attribute__((__ext_vector_type__(3)));
typedef float swift_float4  __attribute__((__ext_vector_type__(4)));
typedef double swift_double2  __attribute__((__ext_vector_type__(2)));
typedef double swift_double3  __attribute__((__ext_vector_type__(3)));
typedef double swift_double4  __attribute__((__ext_vector_type__(4)));
typedef int swift_int2  __attribute__((__ext_vector_type__(2)));
typedef int swift_int3  __attribute__((__ext_vector_type__(3)));
typedef int swift_int4  __attribute__((__ext_vector_type__(4)));
typedef unsigned int swift_uint2  __attribute__((__ext_vector_type__(2)));
typedef unsigned int swift_uint3  __attribute__((__ext_vector_type__(3)));
typedef unsigned int swift_uint4  __attribute__((__ext_vector_type__(4)));
#endif

#if !defined(SWIFT_PASTE)
# define SWIFT_PASTE_HELPER(x, y) x##y
# define SWIFT_PASTE(x, y) SWIFT_PASTE_HELPER(x, y)
#endif
#if !defined(SWIFT_METATYPE)
# define SWIFT_METATYPE(X) Class
#endif
#if !defined(SWIFT_CLASS_PROPERTY)
# if __has_feature(objc_class_property)
#  define SWIFT_CLASS_PROPERTY(...) __VA_ARGS__
# else
#  define SWIFT_CLASS_PROPERTY(...)
# endif
#endif

#if __has_attribute(objc_runtime_name)
# define SWIFT_RUNTIME_NAME(X) __attribute__((objc_runtime_name(X)))
#else
# define SWIFT_RUNTIME_NAME(X)
#endif
#if __has_attribute(swift_name)
# define SWIFT_COMPILE_NAME(X) __attribute__((swift_name(X)))
#else
# define SWIFT_COMPILE_NAME(X)
#endif
#if __has_attribute(objc_method_family)
# define SWIFT_METHOD_FAMILY(X) __attribute__((objc_method_family(X)))
#else
# define SWIFT_METHOD_FAMILY(X)
#endif
#if __has_attribute(noescape)
# define SWIFT_NOESCAPE __attribute__((noescape))
#else
# define SWIFT_NOESCAPE
#endif
#if __has_attribute(warn_unused_result)
# define SWIFT_WARN_UNUSED_RESULT __attribute__((warn_unused_result))
#else
# define SWIFT_WARN_UNUSED_RESULT
#endif
#if __has_attribute(noreturn)
# define SWIFT_NORETURN __attribute__((noreturn))
#else
# define SWIFT_NORETURN
#endif
#if !defined(SWIFT_CLASS_EXTRA)
# define SWIFT_CLASS_EXTRA
#endif
#if !defined(SWIFT_PROTOCOL_EXTRA)
# define SWIFT_PROTOCOL_EXTRA
#endif
#if !defined(SWIFT_ENUM_EXTRA)
# define SWIFT_ENUM_EXTRA
#endif
#if !defined(SWIFT_CLASS)
# if __has_attribute(objc_subclassing_restricted)
#  define SWIFT_CLASS(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) __attribute__((objc_subclassing_restricted)) SWIFT_CLASS_EXTRA
#  define SWIFT_CLASS_NAMED(SWIFT_NAME) __attribute__((objc_subclassing_restricted)) SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_CLASS_EXTRA
# else
#  define SWIFT_CLASS(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) SWIFT_CLASS_EXTRA
#  define SWIFT_CLASS_NAMED(SWIFT_NAME) SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_CLASS_EXTRA
# endif
#endif

#if !defined(SWIFT_PROTOCOL)
# define SWIFT_PROTOCOL(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) SWIFT_PROTOCOL_EXTRA
# define SWIFT_PROTOCOL_NAMED(SWIFT_NAME) SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_PROTOCOL_EXTRA
#endif

#if !defined(SWIFT_EXTENSION)
# define SWIFT_EXTENSION(M) SWIFT_PASTE(M##_Swift_, __LINE__)
#endif

#if !defined(OBJC_DESIGNATED_INITIALIZER)
# if __has_attribute(objc_designated_initializer)
#  define OBJC_DESIGNATED_INITIALIZER __attribute__((objc_designated_initializer))
# else
#  define OBJC_DESIGNATED_INITIALIZER
# endif
#endif
#if !defined(SWIFT_ENUM_ATTR)
# if defined(__has_attribute) && __has_attribute(enum_extensibility)
#  define SWIFT_ENUM_ATTR __attribute__((enum_extensibility(open)))
# else
#  define SWIFT_ENUM_ATTR
# endif
#endif
#if !defined(SWIFT_ENUM)
# define SWIFT_ENUM(_type, _name) enum _name : _type _name; enum SWIFT_ENUM_ATTR SWIFT_ENUM_EXTRA _name : _type
# if __has_feature(generalized_swift_name)
#  define SWIFT_ENUM_NAMED(_type, _name, SWIFT_NAME) enum _name : _type _name SWIFT_COMPILE_NAME(SWIFT_NAME); enum SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_ENUM_ATTR SWIFT_ENUM_EXTRA _name : _type
# else
#  define SWIFT_ENUM_NAMED(_type, _name, SWIFT_NAME) SWIFT_ENUM(_type, _name)
# endif
#endif
#if !defined(SWIFT_UNAVAILABLE)
# define SWIFT_UNAVAILABLE __attribute__((unavailable))
#endif
#if !defined(SWIFT_UNAVAILABLE_MSG)
# define SWIFT_UNAVAILABLE_MSG(msg) __attribute__((unavailable(msg)))
#endif
#if !defined(SWIFT_AVAILABILITY)
# define SWIFT_AVAILABILITY(plat, ...) __attribute__((availability(plat, __VA_ARGS__)))
#endif
#if !defined(SWIFT_DEPRECATED)
# define SWIFT_DEPRECATED __attribute__((deprecated))
#endif
#if !defined(SWIFT_DEPRECATED_MSG)
# define SWIFT_DEPRECATED_MSG(...) __attribute__((deprecated(__VA_ARGS__)))
#endif
#if __has_feature(attribute_diagnose_if_objc)
# define SWIFT_DEPRECATED_OBJC(Msg) __attribute__((diagnose_if(1, Msg, "warning")))
#else
# define SWIFT_DEPRECATED_OBJC(Msg) SWIFT_DEPRECATED_MSG(Msg)
#endif
#if __has_feature(modules)
@import ObjectiveC;
@import Foundation;
#endif

#pragma clang diagnostic ignored "-Wproperty-attribute-mismatch"
#pragma clang diagnostic ignored "-Wduplicate-method-arg"
#if __has_warning("-Wpragma-clang-attribute")
# pragma clang diagnostic ignored "-Wpragma-clang-attribute"
#endif
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma clang diagnostic ignored "-Wnullability"

SWIFT_MODULE_NAMESPACE_PUSH("BecoSDK")
@class LocationData;
enum BecoSDKErrorCode : NSInteger;
enum BecoSDKReturnStatus : NSInteger;

/// This is the interface to software external to the Beco SDK.
/// The responses are Swift objects parsed from the
/// JSON keys/objects documented in the Beco API documentation
/// at: https://dev.beco.io/v2.0/docs/apphitibeacon
/// Beco has provided, as part of the SDK, a set of data model
/// objects to parse the JSON and return first-class objects.
/// If nil, the SDK will discard any server responses.
/// These methods are all called using dispatch_async on the
/// main background queue.
SWIFT_PROTOCOL("_TtP7BecoSDK15BecoSDKDelegate_")
@protocol BecoSDKDelegate
/// Called when the Beco SDK needs to report an updated location to the
/// application.
/// You may get the same location data sent multiple times as a status
/// refresh. It is up to the user to handle this condition.
/// When no location data is available, or your location
/// is ambiguous, the locationData parameter will be nil.
/// The SDK may report an unknown location for one of several reasons:
/// <ol>
///   <li>
///     You may be out of the reliable range of your registered Beco Beacons.
///   </li>
///   <li>
///     The RF environment is such that your location is ambiguous.
///     You are neither here nor there and the SDK is informing you of that situation.
///   </li>
///   <li>
///     The handset does not have an available Internet connection
///     and you have changed locations.
///   </li>
/// </ol>
/// \param locationData The parsed out and ready to use location data.
/// Refer to the documentation of LocationData for more information.
/// When nil, the SDK is reporting the location as unknown.
///
- (void)becoSdkDelegateWithReceiveLocationData:(LocationData * _Nullable)locationData;
/// Called when the Beco SDK needs to report an error to the application.
- (void)becoSdkDelegateWithReportError:(enum BecoSDKErrorCode)error;
/// Called when the Beco SDK reported a hit to the server.
- (void)becoSdkDelegateWithReportAppHit:(NSString * _Nonnull)becoId;
/// Called to indicate start scan has completed.
- (void)becoSdkDelegateWithReportStartScanComplete:(enum BecoSDKReturnStatus)reportStartScanComplete;
@end

/// Error reporting codes for the BecoSDK delegate error reporting function.
typedef SWIFT_ENUM(NSInteger, BecoSDKErrorCode) {
/// Error code if the credentials specified do not match
/// the beacon scanned.
  BecoSDKErrorCodeCredentialMismatch = 0,
/// Error code if the credentials specified were not found.
  BecoSDKErrorCodeCustomerNotFound = 1,
/// Error code if the backend reported a rate limit violation.
  BecoSDKErrorCodeRateLimitExceeded = 2,
/// Error code reported if there was a problem executing
/// a server command.
  BecoSDKErrorCodeServerParsingError = 3,
/// Error code reported if there was a network problem communicating
/// with the Beco Cloud services.
  BecoSDKErrorCodeServerCommunicationFailure = 4,
/// Error code reported if Bluetooth is/has been disabled.
  BecoSDKErrorCodeBluetoothDisabled = 5,
/// Error code reported if Bluetooth is/has been enabled.
  BecoSDKErrorCodeBluetoothEnabled = 6,
/// Error code reported if Location Services is/has been disabled.
  BecoSDKErrorCodeLocationDisabled = 7,
/// Error code reported if Location Services is/has been enabled.
  BecoSDKErrorCodeLocationEnabled = 8,
};

@class UserInfoReply;
enum BecoSDKState : NSInteger;
@class NSDictionary;
@class RegisterHandsetReply;

/// This class is the primary interface to the Beco provided iOS 9.0+ SDK.
/// The Beco SDK provides a way to enhance your iOS application with
/// real-time location and location analytics.
SWIFT_CLASS("_TtC7BecoSDK16BecoSDKInterface")
@interface BecoSDKInterface : NSObject
/// This is the default constructor for the SDK interface.
- (nonnull instancetype)init OBJC_DESIGNATED_INITIALIZER;
/// Gets information about the currently saved user credentials.
/// This returns nil if the credentials have never been loaded
/// from the server.
@property (nonatomic, readonly, strong) UserInfoReply * _Nullable userInfo;
/// Returns true if the currently saved user credentials indicate
/// an administrator login.
/// This returns ‘false’ if the credentials have never been loaded
/// from the server.
- (BOOL)getSDKUserRoleIsAdmin SWIFT_WARN_UNUSED_RESULT;
/// This is the interface to software external to the Beco SDK.
/// Location data decoded by the server will be provided asynchronously
/// to this callback. Delegate calls are performed using the
/// main queue of the Grand Central Dispatch (GCD).
/// The responses are Objects encapsulating the Beco REST API for
/// easy use.
/// If nil, the SDK will discard any server responses.
@property (nonatomic, strong) id <BecoSDKDelegate> _Nullable delegate;
/// This is the server hostname without protocol.
/// The SDK assumes and sets the protocol to HTTPS internally. HTTP
/// is not supported. The SDK also uses the default HTTPS port 443
/// for outgoing traffic.
/// All public Beco Cloud users will set this to “api.beco.io”.
/// Users with private instances of the Beco Cloud will use
/// alternate hostnames appropriate for their environment.
@property (nonatomic, copy) NSString * _Nonnull hostname;
/// Use the Threshold Adjustment to adjust positioning sensitivity.
/// We recommend using our default, set at ‘7’, however for applications
/// that require the Beco Beacons to be installed in higher ceilings
/// (5-6 meters), it will be necessary to increase the sensitivity level
/// in order to ensure higher levels of location accuracy.
/// The higher the ceiling, the higher this threshold should be.
/// For other applications, such as placing Beco Beacons on desks
/// or other very close applications (less than 1 meter), you can
/// decrease this value substantially in order to maintain
/// location precision.
/// The SDK internally configures this value to ‘5’.
/// Acceptable values are from -20 to 50 with a nominal value of 5.
@property (nonatomic) NSInteger thresholdAdjustment;
/// This value controls the SDK data update rate in seconds.
/// The update rate is the maximum time between callbacks to
/// the BecoSDKDelegate. After a callback is made on a location
/// change, this SDK will guarantee another callback in the
/// time interval set here and every interval thereafter.
/// The SDK internally configures this value to 10.
/// The valid range is 2 to 300 inclusive.
@property (nonatomic) NSInteger refreshInterval;
/// This method is for Beco engineering use only.
- (void)updateIgnoreThreshold:(NSInteger)threshold;
/// Gets the current state of the SDK.
@property (nonatomic, readonly) enum BecoSDKState sdkState;
/// A convenience function for
/// sdkState == .eBecoSdkStateScanning
/// This is deprecated and you should replace it with a proper check
/// for the expected/desired SDK State.
- (BOOL)getSDKIsScanning SWIFT_WARN_UNUSED_RESULT SWIFT_DEPRECATED;
/// This method resets all internal settings to the Beco defined
/// defaults.
/// SDK users will generally not need to use this method.
- (void)resetDefaults;
/// Registers a handset for use with the Beco Occupancy API.
/// This is equivalent to a call using the /handsets/register REST API call
/// as documented at https://dev.beco.io/docs/appregister
/// \param idfa The ID for Advertising. If nil we fill in w/ IDFV. Apps
/// using this API should follow Apple’s policy for IDFV vs IDFA use.
///
/// \param personId A customer provided identifier for this particular
/// SDK user. IDFVs can rotate and change for various reasons. Customers
/// should fill in this field with an organizationally meaningful identifer
/// which will persist even if the IDFV changes. An employee id number or
/// organizational email address are appropriate examples for this field.
/// <b>Failing to fill this in properly will severly limit analytics performance.</b>
///
/// \param groupId A customer provided identifier for grouping
/// organizational users of the Beco system. This might be a department name,
/// division name, site name or other similar relevant information.
/// <b>Failing to fill this in properly will severly limit analytics performance.</b>
///
/// \param userData Arbitrary user provided metadata to associate with the handset
/// in the form of Key <-> Object. Must be convertible to valid JSON
/// using NSJSONSerialization
/// (https://developer.apple.com/library/ios/documentation/Foundation/Reference/NSJSONSerialization_Class)
///
/// \param completion A function to call when the registration completes.
/// The data entity will reflect the Beco REST API result or error JSON data.
/// The success parameter of the callback will be true if the handset
/// is (1) already registered and the server call was skipped, or
/// (2) the server call succeeded. A non-nil rhr parameter
/// to the callback indicates a server call was made.
/// In the case that success is false and rhr is non-nil,
/// this indicates the server returned an error and details
/// should be in the rhr object.
///
///
/// returns:
/// A boolean indicating that the request started or not. If the
/// request is started, then the completion handler will be called after completion.
- (BOOL)registerHandset:(NSUUID * _Nullable)idfa personId:(NSString * _Nullable)personId groupId:(NSString * _Nullable)groupId userData:(NSDictionary * _Nullable)userData completion:(void (^ _Nullable)(BOOL, RegisterHandsetReply * _Nullable))completion SWIFT_WARN_UNUSED_RESULT;
/// Sets the server credentials for using the Beco REST API.
/// These credentials are used as part of HTTP Basic authentication
/// to access the Beco REST API server.
/// Setting a plain text password here is acceptable because
/// the SDK will encoded the password per HTTP Basic <em>and</em>
/// all communcation to the Beco servers are encrypted
/// in accordance with iOS 9.0 Apple ATS guidelines.
/// (See https://developer.apple.com/library/prerelease/ios/releasenotes/General/WhatsNewIniOS/Articles/iOS9.html)
/// Beco REST API credentials are assigned by Beco as part of your
/// order.
/// \param username The username/email address used to access the Beco REST API.
///
/// \param plainPw The plain text password used to access the Beco REST API.
///
- (void)setCredentials:(NSString * _Nonnull)username plainPw:(NSString * _Nonnull)plainPw;
/// A request to start scanning for Beco Beacons.
/// Preconditions:
/// <ul>
///   <li>
///     Delegate must be set.
///   </li>
/// </ul>
/// As this method needs to load data from the Beco server, it
/// completes asynchronously via the delegate callback function.
/// If this method is called while already scanning an “eBecoAlreadyScanning” status
/// will be returned to the delegate completion function.
///
/// throws:
/// <code>InvalidCredentialsException.NotSet</code> if the username/password are unset.
- (BOOL)startScanAndReturnError:(NSError * _Nullable * _Nullable)error;
/// Stops all operations.
- (void)stopScan;
/// Gets the version identifier string for this SDK release.
/// The version identifier string follows semantic versioning.
/// https://www.semver.org
+ (NSString * _Nonnull)getSDKVersion SWIFT_WARN_UNUSED_RESULT;
/// Force a location change report of the current location
/// from the SDK to the BecoSDKDelegate.
/// \param id An optional identifier of the last known location.
///
- (void)pushLocationChange:(NSString * _Nullable)id;
/// Return a list of all known active beacons found since
/// the last “clearBeaconList()” call.
- (NSArray<NSString *> * _Nonnull)getBeaconList SWIFT_WARN_UNUSED_RESULT;
/// Clear the list of active beacons returned from a
/// “getBeaconList()” call.
- (void)clearBeaconList;
/// Gets a string for a given BecoID that describes the beacon’s status.
/// \param id An identifier for the beacon.
///
///
/// returns:
/// A string with detailed status on the given beacon
/// or an empty string “” on an error.
- (NSString * _Nonnull)getBecoDescription:(NSString * _Nonnull)id SWIFT_WARN_UNUSED_RESULT;
/// Gets a Beacon for a given BecoID.
/// \param id An identifier for the beacon.
///
///
/// returns:
///
/// <ul>
///   <li>
///     locationData: The parsed out and ready to use location data for ‘id’.
///     Refer to the documentation of LocationData for more information.
///     When nil, the SDK is reporting the location as unknown.
///   </li>
/// </ul>
- (LocationData * _Nullable)getBeacon:(NSString * _Nonnull)id SWIFT_WARN_UNUSED_RESULT;
/// Gets the current HSID.
/// This returns nil if the credentials have never been loaded
/// from the server.
@property (nonatomic, readonly, copy) NSUUID * _Nullable currentHSID;
@end

/// The result status of the start scan operation ‘startScan()’.
/// <ul>
///   <li>
///     eBecoSuccess               : The status returned when scanning has started.
///   </li>
///   <li>
///     eBecoUnauthorized          : The status returned when location services are unauthorized. Scanning is disabled.
///   </li>
///   <li>
///     eBecoBluetoothOff          : The status returned when the device has Bluetooth off.
///   </li>
///   <li>
///     eBecoBluetoothUnsupported  : The status returned when the device does not have BLE support.
///   </li>
///   <li>
///     eBecoBluetoothUnauthorized : The status returned when the app does not have Bluetooth authorization.
///   </li>
///   <li>
///     eBecoBluetoothUnknown      : A general error state returned by the underlying iOS Bluetooth API.
///   </li>
///   <li>
///     eBecoNetworkError          : Beco Server returned an error or was unable to connect to the internet. Scanning is disabled.
///   </li>
///   <li>
///     eBecoCredentials           : Missing credentials <server>/<user>/<password> for network. Scanning is disabled.
///   </li>
///   <li>
///     eBecoAlreadyScanning       : Too many calls to ‘startScan’ without ‘stopScan’.
///   </li>
/// </ul>
typedef SWIFT_ENUM(NSInteger, BecoSDKReturnStatus) {
  BecoSDKReturnStatusEBecoSuccess = 0,
  BecoSDKReturnStatusEBecoUnauthorized = 1,
  BecoSDKReturnStatusEBecoBluetoothOff = 2,
  BecoSDKReturnStatusEBecoBluetoothUnsupported = 3,
  BecoSDKReturnStatusEBecoBluetoothUnauthorized = 4,
  BecoSDKReturnStatusEBecoBluetoothUnknown = 5,
  BecoSDKReturnStatusEBecoNetworkError = 6,
  BecoSDKReturnStatusEBecoCredentials = 7,
  BecoSDKReturnStatusEBecoAlreadyScanning = 8,
};

/// The current state of operation of the Beco SDK.
/// <ul>
///   <li>
///     eBecoSdkStateStopped        : The SDK is not scanning or doing anything. This is the initial state.
///   </li>
///   <li>
///     eBecoSdkStateStarting       : The SDK has valid credentials from setCredentials and is starting up
///   </li>
///   <li>
///     eBecoSdkStateWaitLocAuth    : The SDK is waiting for location authorization (not currently authorized)
///   </li>
///   <li>
///     eBecoSdkStateAuthorized     : The SDK has location authorization and is trying to continue starting
///   </li>
///   <li>
///     eBecoSdkStateLoadFromCloud  : The SDK is loading data from the Beco Cloud and waiting for a server reply.
///   </li>
///   <li>
///     eBecoSdkStateLoadFromCloudFailed  : The SDK failed to load data from the Beco Cloud. You can retry.
///   </li>
///   <li>
///     eBecoSdkStateScanning       : The SDK is scanning and running location
///   </li>
/// </ul>
typedef SWIFT_ENUM(NSInteger, BecoSDKState) {
  BecoSDKStateEBecoSdkStateStopped = 0,
  BecoSDKStateEBecoSdkStateStarting = 1,
  BecoSDKStateEBecoSdkStateWaitLocAuth = 2,
  BecoSDKStateEBecoSdkStateAuthorized = 3,
  BecoSDKStateEBecoSdkStateLoadFromCloud = 4,
  BecoSDKStateEBecoSdkStateLoadFromCloudFailed = 5,
  BecoSDKStateEBecoSdkStateScanning = 6,
};


/// This object is embedded in a UserInfoReply.
SWIFT_CLASS("_TtC7BecoSDK19CustomerSdkSettings")
@interface CustomerSdkSettings : NSObject
/// The background data flush interval.
/// This setting is used to trade battery consumed by radio tx/rx traffic
/// against latency of the occupancy API end points.
/// A smaller value will result in lower latency, but higher battery use.
/// The valid range is from 5 seconds to 300 seconds. The default is 60
/// if not set by the server.
@property (nonatomic) NSInteger bgHbFlushTimeSec;
- (nonnull instancetype)init OBJC_DESIGNATED_INITIALIZER;
@end


/// A Floor object as produced by the Beco API.
SWIFT_CLASS("_TtC7BecoSDK5Floor")
@interface Floor : NSObject
/// The unique identifier for this floor.
@property (nonatomic, copy) NSUUID * _Null_unspecified floorId;
/// The user-provided name of the floor. Treated as a string,
/// but the check-in app only allows -10 to 10 as integer values.
@property (nonatomic, copy) NSString * _Nullable name;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
@end


/// A Location object as produced by the Beco API.
/// Locations are the top-level of the Beco positioning hierarchy.
/// A location may have many associated departments, floors and places.
/// A location is typically associated with an entire building, tower
/// or address. For example: Store #125 would be a location.
/// Within locations, Places may be grouped by Floor and Department.
/// There is no hierarchy between floor and department.
/// Places are the finest-grain level in the hierarchy and are
/// associated 1:1 with a physical Beco Beacon.
SWIFT_CLASS("_TtC7BecoSDK8Location")
@interface Location : NSObject
/// A case-insensitive sorting of the Location by the name.
/// \param left The first location.
///
/// \param right The second location.
///
+ (BOOL)SortByName:(Location * _Nonnull)left right:(Location * _Nonnull)right SWIFT_WARN_UNUSED_RESULT;
/// The unique id for this location.
@property (nonatomic, copy) NSUUID * _Null_unspecified locationId;
/// The user-provided name for this location. May be nil.
@property (nonatomic, copy) NSString * _Nullable locationName;
/// The address associated with this location.
/// Reserved for future use. Will always be nil.
@property (nonatomic, strong) id _Nullable address;
/// The number of hours of operation associated with this
/// location.
/// This field is deprecated and will be removed in a future version.
/// The SDK will always return 24 and the field is not settable.
@property (nonatomic, readonly) NSInteger locationHours;
/// The capacity in number of people of this location.
/// A value of -1 indicates that this information in unavailable.
@property (nonatomic) NSInteger capacity;
/// Creates a Location object from a json dictionary.
/// \param fromJson A dictionary, parsed from a JSON representation of this
/// object.
///
- (nullable instancetype)initFromJson:(NSDictionary * _Nonnull)fromJson OBJC_DESIGNATED_INITIALIZER;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
@end

@class Place;

/// This is the encapsulating class for data received from the
/// Beco Location API.
/// Fields defined as implicitly unwrapped types are never nil because
/// the constructor is implemented to fail if that would occur.
/// Fields with Optional types may be nil and application code should
/// respond appropriately.
/// While this object contains the raw iBeacon information, such as
/// UUID and major and minor, we typically find that this information
/// is mostly relevant inside the SDK. We provide it here for advanced users
/// who may be interested in it.
SWIFT_CLASS("_TtC7BecoSDK12LocationData")
@interface LocationData : NSObject
@property (nonatomic, readonly) NSInteger version;
@property (nonatomic, readonly, copy) NSString * _Nonnull becoId;
@property (nonatomic, readonly, copy) NSUUID * _Nonnull proximityUUID;
@property (nonatomic, readonly) uint16_t trueMajor;
@property (nonatomic, readonly) uint16_t trueMinor;
@property (nonatomic, readonly, copy) NSString * _Nonnull redirectURL;
@property (nonatomic, readonly, strong) Place * _Nullable place;
@property (nonatomic, readonly, copy) NSUUID * _Nullable originalPlace;
@property (nonatomic, readonly, copy) NSArray<NSNumber *> * _Nonnull secure;
@property (nonatomic, readonly) NSInteger sensitivity;
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly) NSInteger scDefaultSensitivity;)
+ (NSInteger)scDefaultSensitivity SWIFT_WARN_UNUSED_RESULT;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
@end


/// This class wraps a Place object.
SWIFT_CLASS("_TtC7BecoSDK5Place")
@interface Place : NSObject
/// The unique identifier for this place.
@property (nonatomic, copy) NSUUID * _Null_unspecified placeId;
/// The name of this place. Can be nil if unset.
@property (nonatomic, copy) NSString * _Nullable placeName;
/// The floor this place is located. Can be nil if no floor was
/// set during checkin.
@property (nonatomic, strong) Floor * _Nullable floor;
/// Generic user defined comments about this place. Usually nil.
@property (nonatomic, copy) NSString * _Nullable comments;
/// The location containing this place.
/// A beacon which is not yet checked in may have a null location.
@property (nonatomic, strong) Location * _Nullable location;
/// The capacity of this place.
/// If the capacity has not been set the value -1 is used.
@property (nonatomic) NSInteger capacity;
/// Creates a Place object from a json dictionary.
/// \param fromJson A dictionary, parsed from a JSON representation of this
/// object.
///
- (nullable instancetype)initFromJson:(NSDictionary * _Nonnull)fromJson OBJC_DESIGNATED_INITIALIZER;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
@end


/// This class encapsulates the reply from
/// a request to register a handset.
SWIFT_CLASS("_TtC7BecoSDK20RegisterHandsetReply")
@interface RegisterHandsetReply : NSObject
/// The handset identifier.
@property (nonatomic, copy) NSUUID * _Nonnull becoHSID;
/// The ID for Advertising.
/// This is Apple’s IDFA provided by the iOS API.
/// On Android devices, this will be the AAID.
/// Apps which use the BecoSDK for advertising purposes should
/// retrive this field from ASIdentifierManager in the Ad Suport Framework.
/// See: https://developer.apple.com/library/ios/documentation/DeviceInformation/Reference/AdSupport_Framework/index.html
@property (nonatomic, copy) NSUUID * _Nullable idfa;
/// The date and time this handset was created in milliseconds since
/// 1-Jan-1970 00:00:00 UTC.
@property (nonatomic) uint64_t created;
/// The date this handset was created.
@property (nonatomic, readonly, copy) NSDate * _Nonnull createdDate;
/// The person identifier.
/// This is a unique identifer assigned by an SDK developer to
/// group together handsets belonging to a single person.
/// The core concept here is that a unique person may have multiple
/// devices running Beco and therefore data related to that person
/// should be aggregated by the system, which the Beco backend is
/// able to do.
@property (nonatomic, copy) NSString * _Nullable personId;
/// The group identifier.
/// This is a unique identifier assigned by an SDK developer
/// to group together personIds in a meaningful way.
/// For example: a person who is a member of the Marketing
/// department could us “Marketing” as the groupId.
@property (nonatomic, copy) NSString * _Nullable groupId;
/// Any generic metadata that was specified to be associated
/// with the handset when it was created.
/// This is SDK developer provided JSON information and is
/// entirely arbitrary.
@property (nonatomic, strong) NSDictionary * _Nullable userData;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
@end


/// This class defines a Role granted to a particular user.
/// This is part of a role based access control (RBAC) system.
/// Role based functionality is reserved for future use.
/// SDK users should not make any assumptions about
/// the continuity of Role names between SDK releases.
SWIFT_CLASS("_TtC7BecoSDK4Role")
@interface Role : NSObject
/// The text form of the role name.
@property (nonatomic, copy) NSString * _Null_unspecified roleName;
/// Generates a human readable string equivalent of this role.
@property (nonatomic, readonly, copy) NSString * _Nonnull description;
/// Implementation of Hashable
@property (nonatomic, readonly) NSInteger hashValue;
/// Implementation of Equatable
- (BOOL)isEqual:(id _Nullable)object SWIFT_WARN_UNUSED_RESULT;
/// Implementation of Hashable.
@property (nonatomic, readonly) NSUInteger hash;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
@end


/// This is the server response for the /2.0/users GET API end point.
/// See full documentation at: https://dev.beco.io/docs/users
SWIFT_CLASS("_TtC7BecoSDK13UserInfoReply")
@interface UserInfoReply : NSObject
/// The login name of the user.
@property (nonatomic, copy) NSString * _Null_unspecified userName;
/// The Roles assigned to this user.
/// Roles are used to grant permissions to users to perform certain
/// actions.
@property (nonatomic, copy) NSSet<Role *> * _Nonnull roles;
/// A date object representing the same time as the dateCreatedms.
@property (nonatomic, readonly, copy) NSDate * _Nonnull dateCreated;
/// True if the user has admin authority. Admin users are
/// allowed to check-in and edit beacons.
/// Normal users only provide location or collect analytics data,
/// depending on the account settings.
@property (nonatomic, readonly) BOOL isAdmin;
/// A human readable representation of this object.
@property (nonatomic, readonly, copy) NSString * _Nonnull description;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
@end

SWIFT_MODULE_NAMESPACE_POP
#pragma clang diagnostic pop
