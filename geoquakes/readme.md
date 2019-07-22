<p align="center">
  <img src="https://cloud.githubusercontent.com/assets/7833470/10423298/ea833a68-7079-11e5-84f8-0a925ab96893.png" width="60">
</p>

# [GeoQuakes](https://github.com/sf-wdi-24/geoquakes)

**Objective:** Display data from the USGS (United States Geological Survey) on significant earthquakes (M4.0 or greater) from the past week. The goal is to list information about each quake and display a Google Map with a pin at the epicenter of each quake.

### Part 1. Rendering Data

Take a moment to familiarize yourself with the data set by opening it in your browser: <a href="http://earthquake.usgs.gov/earthquakes/feed/v1.0/summary/4.5_week.geojson" target="_blank">earthquake data</a>

* What is the structure of the data?
  * How many earthquakes does it list?
  * How would you get the first earthquake?
    * How would you get its title?
    * How would you get its geological coordinates:
      * *latitude*?
      * *longitude*?
    * When did it happen?
      * How many hours ago is that?

Now, take a moment to familiarize yourself with the layout in `index.html`. Your short term goal is to use <a href="http://handlebarsjs.com/" target="_blank">Handlebars templating</a> to render each `title` to the `quakes-list` section of the page.

### Part 2. Add Google Maps

Your next goal is to integrate Google Maps using the <a href="https://developers.google.com/maps/documentation/javascript/tutorial" target="_blank"> Google Maps Javascript API</a>:

    * Follow the tutorial in the link above.
    * Note that you will need to sign up for an API key (see `index.html#L40`).
    * Center your map on San Francisco: `{ lat: 37.78, lng: -122.44 }`

### Part 3. Add Pins to Your Map

Once you've got the map to show up, your next goal is to drop a single pin on San Francisco.

  * Next, can you add only the first earthquake to the map?
  * Can you add pins for *all* the earthquakes to the map?
  * Can you use a custom *earthquake* icon for your pins?!

### Bonus

* Calculate how long ago the quake occurred and add it to the page (e.g. "28 hours ago"). **Hint:** Look up Handlebars custom helpers.
* Parse the title to only include the location (e.g. Instead of "M 4.2 - 1km ESE of Fontana, California", it should say "Fontana, California").
* Create a visual indicator of the magnitude of the quake. For instance, maybe a 4.0 is indicated by a "yellow" dot, a 5.0 by an "orange" dot, and anything larger is "red".


[**Preview**](https://dukeluo.me/Sand/geoquakes/index.html)