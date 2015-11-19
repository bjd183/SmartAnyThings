definition(
    name: "Arduino SmartThing Contact Bridge",
    namespace: "bjd183",
    author: "Bryce Durham",
    description: "Arduino SmartThing bridge to virtual contact sensors.",
    category: "My Apps",
    iconUrl: "https://s3.amazonaws.com/smartapp-icons/Convenience/Cat-Convenience.png",
    iconX2Url: "https://s3.amazonaws.com/smartapp-icons/Convenience/Cat-Convenience@2x.png",
    iconX3Url: "https://s3.amazonaws.com/smartapp-icons/Convenience/Cat-Convenience@2x.png")

preferences {
    section("Select the Arduino AnyThingShield") {
		input "arduino", "device.arduinoAnythingshield", required:true
    }
    section("Select the bridged pin") {
		input(name:"pin",type:"enum",options:["contactPin08","contactPin09","contactPin10","contactPin11","contactPin12"],required:true)
	}
	section("Select the virtual contact sensor") {
		input "contact", "device.virtualContactSensor", required:true
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
	log.debug "arduinoevent($evt.name; $evt.value; $evt.deviceId)"
	
    if (evt.value == "open") {
    	motion.setOpen()
    } else if (evt.value == "closed") {
    	motion.setClosed()
    }
}