metadata {
	definition (name: "Virtual Motion Sensor", namespace: "bjd183", author: "Bryce Durham") {
		capability "Motion Sensor"
        
		command "setActive"
		command "setInactive"
	}

	simulator {
		// TODO: define status and reply messages here
	}

	tiles {
		standardTile("motion", "device.motion", width: 2, height: 2) {
			state("active", label:'motion', icon:"st.motion.motion.active", backgroundColor:"#ffa81e")
			state("inactive", label:'no motion', icon:"st.motion.motion.inactive", backgroundColor:"#79b821")
		}
        
	main(["motion"])
	details(["motion"])
	}
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
