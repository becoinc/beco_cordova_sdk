////////////////////////////////////////////////
// Beco, Inc
////////////////////////////////////////////////
// Beco Cordova Example
////////////////////////////////////////////////

var app = {
    // Application Constructor
    initialize: function() {
        document.addEventListener("deviceready", this.onDeviceReady, false);
    },
    onDeviceReady: function() {

        //Initialize the Beco API and associated event handlers.
        console.log("[Beco Example App] Starting Beco API.....");

        $("#statusLabel").text("Status: Loading...");

        //Set the user credentials
        var username = "<INSERT SDK USERNAME HERE>";
        var password = "<INSERT SDK PASSWORD HERE>";
        var hostname = "api.beco.io";
        BecoCordovaPlugin.setCredentials(hostname,username,password);

        //Request the location permissions (used only on android)
        var permissions = cordova.plugins.permissions;
        permissions.requestPermission(permissions.ACCESS_COARSE_LOCATION, function(){console.log("PERMISSION SUCCESS")},function(){console.log("PERMISSION FAILURE")});

        //Get the version and display it on the version label.
        BecoCordovaPlugin.getVersion(function(version){
            console.log("[Beco Example App] Got Version. Displaying on Version Label.");
            $("#versionLabel").text("Version: "+version);
        });

        //Register our event functions before we start scanning
        console.log("[Beco Example App] Registering event callback functions.");
        BecoCordovaPlugin.onReceiveLocationData(onReceiveLocationData);
        BecoCordovaPlugin.onReportError(onReportError);
        BecoCordovaPlugin.onReportAppHit(onReportAppHit);
        BecoCordovaPlugin.onReportStartScanComplete(onReportStartScanComplete);

        console.log("[Beco Example App] Registering handset...");
        BecoCordovaPlugin.registerHandset(null,username,null,null,
        function(message){
            //Success. Once the handset has been registered:
            console.log("[Beco Example App] Registered handset.");

            //start scanning for beacons
            console.log("[Beco Example App] Starting beacon scanner...");
            BecoCordovaPlugin.startScan(function(){
                //Successfully started scanning for beacons!
                console.log("[Beco Example App] Started beacon scanner.");
            });
        },
        function(message){
            //Failure, display Error
            $("#statusLabel").text("Status: Failed to register Handset!");
            console.log("[Beco Example App] Failed to register Handset! Error: "+message);
        });

        setInterval(function(){
            BecoCordovaPlugin.getSdkState(function(state){
                $("#stateLabel").text("State: ["+state.statusCode+"] " + state.statusString);
            });
        }, 1000);
    }
};

app.initialize();

////////////////////////////////////////////////
// Event Handler Functions
////////////////////////////////////////////////

// onReportError - Called when an SDK error occurs
function onReportError(errorData){
    //Error has occurred, display the error.
    var statusMessage = "API Error: "+errorData;
    $("#errorLabel").text("API Error: ["+errorData.errorCode+"] "+errorData.errorString);
    //console.log("[Beco Example App] "+statusMessage);
    console.log(errorData);
}

// onReceiveLocationData - Called when the SDK updates the location of a handset
function onReceiveLocationData(locationData){
    //Location data has been received, display it
    //Update the status label, display in a fancy table
    var locationDataTable = "";
    if (locationData == null){
        locationDataTable += "Place: Unknown";
    } else {
        locationDataTable += "<tr><td class='border-right'>Beco Id: </td><td>"+locationData.becoId      + "</td></tr>";
        locationDataTable += "<tr><td class='border-right'>Place:   </td><td>"+locationData.place.placeName   + "</td></tr>";
        locationDataTable += "<tr><td class='border-right'>Location:</td><td>"+locationData.place.location.locationName+ "</td></tr>";
    }

    $("#statusLabel").html("<table>"+locationDataTable+"</table>");
    //console.log("[Beco Example App] Status: Received Location: "+locationData);
    console.log(locationData);
}

// onReportAppHit - Called when a beacon is first detected ("hit")
function onReportAppHit(data){
    //App (Beacon) Hit
    //$("#statusLabel").text("Status: Hit Beacon "+becoId);
    //console.log("[Beco Example App] Status: Hit Beacon: "+becoId);
    console.log(data);
}

// onReportStartScanComplete - Called when the scan is started successfully
function onReportStartScanComplete(data){
    //Start Scan complete, get the status and display it
    var statusMessage = "Scan Started";
    $("#statusLabel").text("Status: ["+data.statusCode+"] "+data.statusString);
    //console.log("[Beco Example App] Status: "+statusMessage);
    console.log(data);
}

////////////////////////////////////////////////
// End of File
////////////////////////////////////////////////
