#Refreshes the local install for cordova plugin
#Only used for testing purposes
cordova plugin remove beco-cordova-plugin
cordova plugin add ../plugin
cordova build
