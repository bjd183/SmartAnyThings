definition(
    name: "Arduino SmartThing Contact Bridge",
    namespace: "bjd183",
    author: "Bryce Durham",
    description: "Arduino SmartThing bridge to virtual contact sensors.",
    category: "My Apps",
    iconUrl: "https://s3.amazonaws.com/smartapp-icons/MyApps/Cat-MyApps.png",
    iconX2Url: "https://s3.amazonaws.com/smartapp-icons/MyApps/Cat-MyApps@2x.png",
    iconX3Url: "https://s3.amazonaws.com/smartapp-icons/MyApps/Cat-MyApps@3x.png")

preferences {
    section("Select the Arduino SmartThing") {
		input(name:"arduino", type:"device.arduinoAnythingshield", required:true)
    }
    section("Select the bridged pin") {
		input(name:"pin",type:"enum",options:["contactPin08","contactPin09","contactPin10","contactPin11","contactPin12"],required:true)
	}
	section("Select the virtual contact sensor") {
		input(name:"virtualContact", type:"device.virtualContactSensor", required:true)
	}
}

def installed() {
	log.debug "Installed with settings: ${settings}"
	subscribe()
}

def updated() {
	log.debug "Updated with settings: ${settings}"
	unsubscribe()
	subscribe()
}

def subscribe() {
	subscribe(arduino, pin, contactHandler)
}

def contactHandler(evt)
{
	log.info "Received ($evt.name: $evt.value) from $evt.device ($evt.displayName)"
	
    if (evt.value == "open") {
    	virtualContact.setOpen()
    } else if (evt.value == "closed") {
    	virtualContact.setClosed()
    }
}