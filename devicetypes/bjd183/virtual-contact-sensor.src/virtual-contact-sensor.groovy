metadata {
	definition (name: "Virtual Contact Sensor", namespace: "bjd183", author: "Bryce Durham") {
		capability "Contact Sensor"
        
		command "openme"
		command "closeme"
	}

	simulator {
		// TODO: define status and reply messages here
	}

	tiles {
		standardTile("contact", "device.contact", width: 2, height: 2) {
			state("open", label:'${name}', icon:"st.contact.contact.open", backgroundColor:"#ffa81e")
			state("closed", label:'${name}', icon:"st.contact.contact.closed", backgroundColor:"#79b821")
		}
        
	main(["contact"])
	details(["contact"])
	}
}

// parse events into attributes
def parse(String description) {
	log.debug "Parsing '${description}'"
	// TODO: handle 'contact' attribute

}

def openme() {
    log.debug "Virtual Contact Open"
    sendEvent(name: "contact", value: "open", isStateChange: true)
}

def closeme() {
    log.debug "Virtual Contact Closed"
    sendEvent(name: "contact", value: "closed", isStateChange: true)
}
