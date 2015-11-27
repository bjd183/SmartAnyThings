metadata {
	definition (name: "Virtual Alarm Actuator", namespace: "bjd183", author: "Bryce Durham") {
		capability "Alarm"
		capability "Actuator"
        capability "Switch"
	}

	simulator {
	}

	tiles(scale: 2) {
		multiAttributeTile(name:"alarm", type:"generic", width:6, height:4) {
			tileAttribute("device.alarm", key: "PRIMARY_CONTROL") {
				attributeState "both", label: "alarm!", action:"off",icon:"st.alarm.alarm.alarm",backgroundColor:"#e86d13"
				attributeState "siren", label: "siren!", action:"off",icon:"st.alarm.alarm.alarm", backgroundColor:"#e86d13"
                attributeState "strobe", label: "strobe!", action:"off",icon:"st.alarm.alarm.alarm", backgroundColor:"#e86d13"
				attributeState "off", label:"off", action:"siren",icon:"st.alarm.alarm.alarm", backgroundColor:"#ffffff"
			}
        }
//        standardTile("test", "device.alarm", inactiveLabel: false, decoration: "flat", width: 2, height: 2) {
//            state "default", label:'', action:"test", icon:"st.secondary.test"
//        }
//        standardTile("off", "device.alarm", inactiveLabel: false, decoration: "flat", width: 2, height: 2) {
//            state "default", label:'', action:"alarm.off", icon:"st.secondary.off"
//        }
	}
	main "alarm"
	details(["alarm"])
}

// parse events into attributes
def parse(String description) {
	log.debug "Parsing '${description}' but doing nothing (TODO?)"
}

//handle commands
def both() {
	log.info "Setting virtual alarm siren and strobe (both) on"
    sendEvent(name: "alarm", value: "both")
}

def strobe() {
	log.info "Setting virtual alarm strobe on"
    sendEvent(name: "alarm", value: "strobe")
}

def siren() {
    log.info "Setting virtual alarm siren on"
	sendEvent(name: "alarm", value: "siren")
}

def test() {
	log.info "Testing virtual alarm"
//    both()
//    delay 3000
//   off()
}

def on() {
	both()
}

def off() {
    log.info "Setting virtual alarm off"
    sendEvent(name: "alarm", value: "off")
}
