metadata {
	definition (name: "Virtual Contact Sensor", namespace: "bjd183", author: "Bryce Durham") {
		capability "Contact Sensor"
        capability "Sensor"
        
		command "setOpen"
		command "setClosed"
	}

	simulator {
		// TODO: define status and reply messages here
	}

	tiles(scale: 2) {
		multiAttributeTile(name:"contact", type:"generic", width:6, height:4) {
			tileAttribute("device.contact", key: "PRIMARY_CONTROL") {
				attributeState "open", label: '${name}', icon:"st.contact.contact.open", backgroundColor:"#ffa81e"
				attributeState "closed", label:'${name}', icon:"st.contact.contact.closed", backgroundColor:"#79b821"
			}
		}

		main "contact"
		details "contact"
    }
}

// parse events into attributes
def parse(String description) {
	log.debug "Parsing '${description}'"
	// TODO: handle 'contact' attribute

}

def setOpen() {
    log.debug "Virtual Contact Open"
    sendEvent(name: "contact", value: "open", isStateChange: true)
}

def setClosed() {
    log.debug "Virtual Contact Closed"
    sendEvent(name: "contact", value: "closed", isStateChange: true)
}
