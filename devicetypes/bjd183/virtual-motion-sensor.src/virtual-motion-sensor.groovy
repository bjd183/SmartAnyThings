metadata {
	definition (name: "Virtual Motion Sensor", namespace: "bjd183", author: "Bryce Durham") {
		capability "Motion Sensor"
        capability "Sensor"
        
		command "setActive"
		command "setInactive"
	}

	simulator {
		// TODO: define status and reply messages here
	}

	tiles(scale: 2) {
		multiAttributeTile(name:"motion", type:"generic", width:6, height:4) {
			tileAttribute("device.motion", key: "PRIMARY_CONTROL") {
				attributeState "active", label: "motion", icon:"st.motion.motion.active", backgroundColor:"#53a7c0"
				attributeState "inactive", label:"no motion", icon:"st.motion.motion.inactive", backgroundColor:"#ffffff"
			}
		}
	}
	main "motion"
	details "motion"
}

// parse events into attributes
def parse(String description) {
	log.debug "Parsing '${description}'"
	// TODO: handle 'contact' attribute

}

def setActive() {
    log.debug "Virtual Motion Active"
    sendEvent(name: "motion", value: "active", isStateChange: true)
}

def setInactive() {
    log.debug "Virtual Motion Inactive"
    sendEvent(name: "motion", value: "inactive", isStateChange: true)
}
