////////////////////////////////////////////////
// Beco, Inc
////////////////////////////////////////////////
// Beco Cordova Example
////////////////////////////////////////////////

//Minimal index that lets us test using the web JS console
var app = {
    // Application Constructor
    initialize: function() {
        document.addEventListener("deviceready", this.onDeviceReady, false);
    },
    onDeviceReady: function() {

        console.log("[Beco Example App] Registering event callback functions.");
        BecoCordovaPlugin.onReceiveLocationData(onReceiveLocationData);
        BecoCordovaPlugin.onReportError(onReportError);
        BecoCordovaPlugin.onReportAppHit(onReportAppHit);
        BecoCordovaPlugin.onReportStartScanComplete(onReportStartScanComplete);

        BecoCordovaPlugin.setCredentials(hostname,username,password);

        //BecoCordovaPlugin.registerHandset(null,username,null,null,function s(d){console.log(d);},function f(d){console.log("error "+d);});
        BecoCordovaPlugin.startScan();

    }
};

app.initialize();

var username = "webdemouser@beco.io";
var password = "webdemouser";
var hostname = "api.beco.io";
////////////////////////////////////////////////
// Event Handler Functions
////////////////////////////////////////////////

// onReportError - Called when an SDK error occurs
function onReportError(data){
    console.log(data);
}

// onReceiveLocationData - Called when the SDK updates the location of a handset
function onReceiveLocationData(data){
    console.log(data);
}

// onReportAppHit - Called when a beacon is first detected ("hit")
function onReportAppHit(data){
    console.log(data);
}

function onReportStartScanComplete(data){
    console.log(data);
}

////////////////////////////////////////////////
// End of File
////////////////////////////////////////////////
