definition(
    name: "Arduino SmartThing Alarm Bridge",
    namespace: "bjd183",
    author: "Bryce Durham",
    description: "Arduino SmartThing bridge to virtual alarm actuator.",
    category: "My Apps",
    iconUrl: "https://s3.amazonaws.com/smartapp-icons/MyApps/Cat-MyApps.png",
    iconX2Url: "https://s3.amazonaws.com/smartapp-icons/MyApps/Cat-MyApps@2x.png",
    iconX3Url: "https://s3.amazonaws.com/smartapp-icons/MyApps/Cat-MyApps@3x.png")

preferences {
    section("Select the Arduino SmartThing") {
		input(name:"arduino", type:"device.arduinoAnythingshield", required:true)
    }
    section("Select the bridged pin") {
		input(name:"pin",type:"enum",options:["alarmPin04"],required:true)
	}
	section("Select the virtual alarm actuator") {
		input(name:"virtualAlarm", type:"device.virtualAlarmActuator", required:true)
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
	subscribe(arduino, pin, arduinoHandler)
    subscribe(virtualAlarm, "alarm", virtualHandler)
}

//sync from virtual device to arduino
def virtualHandler(evt)
{
	log.info "Received ($evt.name: $evt.value) from $evt.device ($evt.displayName)"
    arduino.set(pin, evt.value)
}

//sync from arduino to virtual device
def arduinoHandler(evt)
{
	log.info "Received ($evt.name: $evt.value) from $evt.device ($evt.displayName)"
    switch (evt.value) {
    	case "siren":
        	virtualAlarm.siren()
            break
        case "strobe":
        	virtualAlarm.strobe()
            break
        case "both":
        	virtualAlarm.both()
            break
        case "off":
        	virtualAlarm.off()
            break
        default:
        	break
    }
}