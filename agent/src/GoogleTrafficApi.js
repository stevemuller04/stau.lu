const EventEmitter = require("events");
const https = require("https");
const { URL, URLSearchParams } = require("url");

/**
 * Class which retrieves traffic information from the Google Maps API.
 * Emits the 'traffic' event when the fetchAll() method is called and
 * succeeds; the event is emitted for each route, and contains a traffic
 * information object of the form
 * {
 *     'id': the ID specified to addRoute()
 *     'normal': the time in seconds required for the route when there is NO TRAFFIC
 *     'current': the time in seconds required for the route NOW
 * }
 * @class
 */
module.exports = class GoogleTrafficApi extends EventEmitter
{
	/**
	 * Initialises a new GoogleTrafficApi instance.
	 * @param {string} api_url - The URL to the Google Maps API / distance matrix.
	 * @param {string} api_key - The Google Maps API key used to connect to the API.
	 * @constructor
	 */
	constructor(api_url, api_key)
	{
		super();
		this.api_url = api_url;
		this.api_key = api_key;
		this.routes = [];
	}

	/**
	 * Adds a new route that shall be fetched when fetchAll() is called.
	 * @param {string} id - Any string that uniquely identifies this route.
	 * The same value is emitted in the 'traffic' event.
	 * @param {string} from - Any string that identifies the starting point of the route.
	 * This string is interpreted by Google Maps.
	 * @param {string} to - Any string that identifies the destination point of the route.
	 * This string is interpreted by Google Maps.
	 * @method
	 */
	addRoute(id, from, to)
	{
		this.routes.push({ id: id, from: from, to: to });
	}

	/**
	 * Fetches the traffic information about all routes defined using addRoute().
	 * This method is asynchronous.
	 * Once information is available, the 'traffic' event will be emitted for each route.
	 * @param {function} callback - (optional) A callback which is called when the asynchronous method finishes.
	 * @method
	 */
	fetchAll(callback)
	{
		this.fetchMany(this.routes, callback);
	}

	/**
	 * Fetches the traffic information about the given routes.
	 * This method is asynchronous.
	 * Once information is available, the 'traffic' event will be emitted for each route.
	 * @param {object[]} routes - A collection of route objects, for which traffic information shall be fetched.
	 * @param {function} callback - (optional) A callback which is called when the asynchronous method finishes.
	 * @method
	 */
	fetchMany(routes, callback)
	{
		if (routes.length == 0)
			callback && callback();
		else
			this.fetchSingle(routes[0], () => this.fetchMany(routes.slice(1), callback));
	}

	/**
	 * Fetches the traffic information about the given routes.
	 * This method is asynchronous.
	 * Once information is available, the 'traffic' event will be emitted for each route.
	 * @param {object} route - The route object, for which traffic information shall be fetched.
	 * @param {function} callback - (optional) A callback which is called when the asynchronous method finishes.
	 * @method
	 */
	fetchSingle(route, callback)
	{
		// Build URL
		let url = new URL(this.api_url);
		url.searchParams.append("key", this.api_key);
		url.searchParams.append("departure_time", "now");
		url.searchParams.append("origins", route.from);
		url.searchParams.append("destinations", route.to);

		// Make HTTP request
		https.get(url.href, resp =>
		{
			let data = "";

			// Handle response content
			resp.on("end", () =>
			{
				let parsed_data = JSON.parse(data);
				if (parsed_data && parsed_data.status == "OK")
				{
					if (parsed_data.rows.length >= 1 && parsed_data.rows[0].elements.length >= 1)
					{
						let traffic_info = parsed_data.rows[0].elements[0];
						if (traffic_info.status == "OK" && traffic_info.duration && traffic_info.duration_in_traffic)
						{
							this.emit("traffic",
							{
								id: route.id,
								normal: traffic_info.duration.value,
								current: traffic_info.duration_in_traffic.value
							});
						}
					}

					// The method succeeded; call callback
					callback && callback();
				}
			});

			// Fetch response content
			// Normally this is a dangerous thing to do,
			// but we trust Google that they do not flood us
			resp.on("data", chunk => data += chunk);
		});
	}
};
