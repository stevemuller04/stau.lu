const GoogleTrafficApi = require("./src/GoogleTrafficApi.js");
const MqttClient = require("./src/MqttClient.js");
const config = require("config");

const api = new GoogleTrafficApi(config.get("googlemapsapi.url"), config.get("googlemapsapi.key"));
const mqtt = new MqttClient(config.get("mqtt.hostname"), config.get("mqtt.port"), config.get("mqtt.username"), config.get("mqtt.password"), config.get("mqtt.topic_prefix"));

api.addRoute(0, "49.638313,5.906366", "49.619436,6.083349"); // be -> strassen
api.addRoute(1, "49.619220,6.083491", "49.638457,5.906377"); // strassen -> be
api.addRoute(2, "49.508744,5.958078", "49.591748,6.088370"); // esch -> cessange
api.addRoute(3, "49.591682,6.088172", "49.508831,5.958064"); // cessange -> esch
api.addRoute(4, "49.619436,6.083349", "49.575354,6.131336"); // strassen -> gasprich
api.addRoute(5, "49.575469,6.131362", "49.619220,6.083491"); // gasprich -> strassen
api.addRoute(6, "49.472701,6.121485", "49.579721,6.126724"); // fr -> gasprich
api.addRoute(7, "49.579756,6.126542", "49.472607,6.121311"); // gasprich -> fr
api.addRoute(8, "49.641773,6.223701", "49.575469,6.131362"); // senningen -> gasprich
api.addRoute(9, "49.575354,6.131336", "49.641682,6.223625"); // gasprich -> senningen
api.addRoute(10, "49.732990,6.500822", "49.641773,6.223701"); // de -> senningen
api.addRoute(11, "49.641682,6.223625", "49.732931,6.500981"); // senningen -> de
api.addRoute(12, "49.757086,6.091725", "49.642329,6.188627"); // mersch -> kirchberg
api.addRoute(13, "49.642375,6.188842", "49.757099,6.092002"); // kirchberg -> mersch

api.on("traffic", info =>
{
	// Compute delay (in minutes) caused by the traffic
	let delay = Math.max(0, info.current - info.normal) / 60;

	// Deduce status from delay
	let status = '-';
	if (delay >= 15)
		status = '3';
	else if (delay >= 7)
		status = '2';
	else if (delay >= 3)
		status = '1';

	// Push message to MQTT broker
	console.log("Got traffic information for route #" + info.id + ": status='" + status + "' delay=" + Math.round(delay) + "min");
	mqtt.push(info.id, status, delay);
});

mqtt.on("connect", () =>
{
	console.log("Connect to MQTT broker")
	console.log("Fetching traffic information ...")
	api.fetchAll(() => mqtt.disconnect());
});

mqtt.connect();
