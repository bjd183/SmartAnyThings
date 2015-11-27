definition(
    name: "Arduino SmartThing Motion Bridge",
    namespace: "bjd183",
    author: "Bryce Durham",
    description: "Arduino SmartThing bridge to virtual motion sensors.",
    category: "My Apps",
    iconUrl: "https://s3.amazonaws.com/smartapp-icons/Convenience/Cat-Convenience.png",
    iconX2Url: "https://s3.amazonaws.com/smartapp-icons/Convenience/Cat-Convenience@2x.png",
    iconX3Url: "https://s3.amazonaws.com/smartapp-icons/Convenience/Cat-Convenience@2x.png")

preferences {
    section("Select the Arduino AnyThingShield") {
		input "arduino", "device.arduinoAnythingshield", required:true
    }
    section("Select the bridged pin") {
		input(name:"pin",type:"enum",options:["motionPin07"],required:true)
	}
	section("Select the virtual motion sensor") {
		input "motion", "device.virtualMotionSensor", required:true
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
	subscribe(arduino, pin, motionHandler)

}

def motionHandler(evt)
{
	log.info "Received ($evt.name: $evt.value) from $evt.device ($evt.displayName)"
	
    if (evt.value == "active") {
    	motion.setActive()
    } else if (evt.value == "inactive") {
    	motion.setInactive()
    }
}