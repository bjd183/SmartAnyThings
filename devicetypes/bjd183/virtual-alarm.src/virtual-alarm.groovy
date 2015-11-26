metadata {
	definition (name: "Virtual Alarm", namespace: "bjd183", author: "Bryce Durham") {
		capability "Alarm"
		capability "Actuator"
        
		command "setBothOn"
		command "setSirenOn"
		command "setOff"
	}

	simulator {
		// TODO: define status and reply messages here
	}

	tiles(scale: 2) {
		multiAttributeTile(name:"alarm", type:"generic", width:6, height:4) {
			tileAttribute("device.alarm", key: "PRIMARY_CONTROL") {
				attributeState "siren", label: "alarm!", action:"setSirenOn",icon:"st.alarm.alarm.alarm", backgroundColor:"#e86d13"
				attributeState "off", label:"off", action:"setOff",icon:"st.alarm.alarm.alarm", backgroundColor:"#ffffff"
			}
		}
	}
	main "alarm"
	details "alarm"
}

// parse events into attributes
def parse(String description) {
	log.debug "Parsing '${description}'"
	// TODO: handle 'contact' attribute

}

def setBothOn() {
	setSirenOn()
}

def setSirenOn() {
    log.debug "Virtual Alarm Siren On"
    sendEvent(name: "alarm", value: "siren", isStateChange: true)
}

def setOff() {
    log.debug "Virtual Alarm Off"
    sendEvent(name: "alarm", value: "off", isStateChange: true)
}
