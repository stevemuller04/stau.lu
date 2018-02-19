const EventEmitter = require("events");
const mqtt = require("mqtt");

/**
 * Class which pushes traffic information to an MQTT broker.
 * @class
 */
module.exports = class MqttClient extends EventEmitter
{
	/**
	 * Initialises a new MQTT client.
	 * @param {string} hostname - The hostname of the MQTT broker.
	 * @param {number} port - The port of the MQTT broker.
	 * @param {string} username - The username used to connect to the MQTT broker.
	 * @param {string} password - The password used to connect to the MQTT broker.
	 * @param {string} topic_prefix - A prefix which is prepended to the route_id in order to get a topic.
	 * Traffic information for a specific route will be published at this topic.
	 * @constructor
	 */
	constructor(hostname, port, username, password, topic_prefix)
	{
		super();
		this.hostname = hostname;
		this.port = port;
		this.username = username;
		this.password = password;
		this.topic_prefix = topic_prefix;
	}

	/**
	 * Connects to the MQTT broker.
	 * @method
	 */
	connect()
	{
		this.client = mqtt.connect("mqtt://" + this.hostname + ":" + this.port, { username: this.username, password: this.password });
		this.client.on("connect", connack => this.emit("connect", connack));
	}

	/**
	 * Closes the connection to the MQTT broker.
	 * @method
	 */
	disconnect()
	{
		this.client.end();
	}

	/**
	 * Pushes the given traffic information to the MQTT broker.
	 * @param {string} route_id - A string that uniquely defines the route related to a certain route.
	 * @param {string} traffic_status - A constant that describes the traffic status of the route.
	 * @param {number} traffic_delay - The additional delay in minutes that is caused by the traffic on the route.
	 * @method
	 */
	push(route_id, traffic_status, traffic_delay)
	{
		let traffic_delay_int = Math.min(99, Math.max(0, Math.round(traffic_delay)));
		let payload = "$" + enforceFormat(route_id, "00") + enforceFormat(traffic_status, "?") + enforceFormat(traffic_delay_int, "00");
		this.client.publish(this.topic_prefix + route_id, payload, { retain: true });
	}
};

function enforceFormat(string, fill_string)
{
	string = fill_string + string;
	return string.substring(string.length - fill_string.length);
}
