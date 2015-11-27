metadata {
	definition (name: "Virtual Contact Sensor", namespace: "bjd183", author: "Bryce Durham") {
		capability "Contact Sensor"
        capability "Sensor"
        
		command "setOpen"
		command "setClosed"
	}

	simulator {
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
	log.debug "Parsing '${description}' but doing nothing (TODO?)"
	// TODO: handle 'contact' attribute

}

def setOpen() {
    log.info "Setting virtual contact open"
    sendEvent(name: "contact", value: "open")
}

def setClosed() {
    log.info "Setting virtual contact closed"
    sendEvent(name: "contact", value: "closed")
}
