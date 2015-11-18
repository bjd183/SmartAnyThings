metadata {
	definition (name: "Arduino AnyThingShield", namespace: "bjd183", author: "Bryce Durham") {
		capability "Contact Sensor"
		capability "Sensor"

		attribute "motionPin07", "string"
		attribute "contactPin08", "string"
		attribute "contactPin09", "string"
		attribute "contactPin10", "string"
		attribute "contactPin11", "string"
		attribute "contactPin12", "string"
	}

    simulator {
    }
	
    // Preferences

	// tile definitions
	tiles {
        standardTile("motionPin07", "device.motionPin07", width: 1, height: 1, canChangeIcon: true, canChangeBackground: true) {
			state("active", label:'motion', icon:"st.motion.motion.active", backgroundColor:"#53a7c0")
			state("inactive", label:'no motion', icon:"st.motion.motion.inactive", backgroundColor:"#ffffff")
 		}
        standardTile("contactPin08", "device.contactPin08", width: 1, height: 1, canChangeIcon: true, canChangeBackground: true) {
			state("open", label:'${name}', icon:"st.contact.contact.open", backgroundColor:"#ffa81e")
			state("closed", label:'${name}', icon:"st.contact.contact.closed", backgroundColor:"#79b821")
 		}
        standardTile("contactPin09", "device.contactPin09", width: 1, height: 1, canChangeIcon: true, canChangeBackground: true) {
			state("open", label:'${name}', icon:"st.contact.contact.open", backgroundColor:"#ffa81e")
			state("closed", label:'${name}', icon:"st.contact.contact.closed", backgroundColor:"#79b821")
 		}
        standardTile("contactPin10", "device.contactPin10", width: 1, height: 1, canChangeIcon: true, canChangeBackground: true) {
			state("open", label:'${name}', icon:"st.contact.contact.open", backgroundColor:"#ffa81e")
			state("closed", label:'${name}', icon:"st.contact.contact.closed", backgroundColor:"#79b821")
 		}
        standardTile("contactPin11", "device.contactPin11", width: 1, height: 1, canChangeIcon: true, canChangeBackground: true) {
			state("open", label:'${name}', icon:"st.contact.contact.open", backgroundColor:"#ffa81e")
			state("closed", label:'${name}', icon:"st.contact.contact.closed", backgroundColor:"#79b821")
 		}
        standardTile("contactPin12", "device.contactPin12", width: 1, height: 1, canChangeIcon: true, canChangeBackground: true) {
			state("open", label:'${name}', icon:"st.contact.contact.open", backgroundColor:"#ffa81e")
			state("closed", label:'${name}', icon:"st.contact.contact.closed", backgroundColor:"#79b821")
 		}

        main (["motionPin07"])
        details(["motionPin07","contactPin08","contactPin09","contactPin10","contactPin11","contactPin12"])
	}
}

def parse(String description) {
    def msg = zigbee.parse(description)?.text
    log.debug "Parse got '${msg}'"

    def parts = msg.split(" ")
    def name  = parts.length>0?parts[0].trim():null
    def value = parts.length>1?parts[1].trim():null

    name = value != "ping" ? name : null
	
    def result = createEvent(name: name, value: value, isStateChange: true)

    log.debug result

    return result
}
//no commands to implement for a read-only contact sensor