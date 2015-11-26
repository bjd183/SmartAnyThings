metadata {
	definition (name: "Virtual Alarm Actuator", namespace: "bjd183", author: "Bryce Durham") {
		capability "Alarm"
		capability "Actuator"
        
//		command "setBothOn"
//		command "setSirenOn"
//		command "setOff"
	}

	simulator {
	}

	tiles(scale: 2) {
		multiAttributeTile(name:"alarm", type:"generic", width:6, height:4) {
			tileAttribute("device.alarm", key: "PRIMARY_CONTROL") {
//				attributeState "both"
//                attribtueState "strobe"
                attributeState "siren", label: "alarm!", action:"alarm.off",icon:"st.alarm.alarm.alarm", backgroundColor:"#e86d13"
				attributeState "off", label:"off", action:"alarm.siren",icon:"st.alarm.alarm.alarm", backgroundColor:"#ffffff"
			}
		}
	}
	main "alarm"
	details "alarm"
}

// parse events into attributes
def parse(String description) {
	log.debug "Parsing '${description}' but doing nothing (TODO?)"
	// TODO: handle 'contact' attribute
}

//handle commands
def both() {
	log.info "Setting virtual alarm siren and strobe (both) on"
    sendEvent(name: "alarm", value: "both", isStateChange: true)
}

def strobe() {
	log.info "Setting virtual alarm strobe on"
    sendEvent(name: "alarm", value: "strobe", isStateChange: true)
}

def siren() {
    log.info "Setting virtual alarm siren on"
    sendEvent(name: "alarm", value: "siren", isStateChange: true)
}

def off() {
    log.info "Setting virtual alarm off"
    sendEvent(name: "alarm", value: "off", isStateChange: true)
}
