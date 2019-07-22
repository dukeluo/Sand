// wait for DOM to load before running JS
$(function() {

    var quakesUrl = "https://earthquake.usgs.gov/earthquakes/feed/v1.0/summary/4.5_week.geojson";
    var $quakesList = $("#quakes-list");
    var map;

    function generateEarthquakeObjects(data) {
        return $.map(data.features, function(value) {
            return {
                "id": value.id,
                "title": value.properties.title,
                "lat": value.geometry.coordinates[1],
                "lng": value.geometry.coordinates[0],
                "time": value.properties.time,
                "mag": value.properties.mag,
                "magType": value.properties.magType,
                "type": value.properties.type
            };
        })
    }

    function getEarthquakeProperty(type, earthquake) {
        return earthquake[type];
    }

    function renderTitle(titles) {
        var source = "<li class='list-group-item quake-title'> {{title}} </li>";
        var template = Handlebars.compile(source);
        var html = "";

        titles = titles.map(function (item) {
            return template(item);
        });
        html = "<ul class='list-group'>" + titles.join("\n") + "</ul>";
        $quakesList.html(html);
    }

    function initMap() {
        map = new google.maps.Map($("#map")[0], {
            center: {lat: 37.78, lng: -122.44},
            zoom: 2
        });
    }

    function addPins(locations) {
        locations.map(function(location, i) {
            return new google.maps.Marker({
                position: location,
                icon: "./earthquake.png",
                map: map,
            });
        });
    }

    $.getJSON(quakesUrl, function (data) {
        var earthquakes = generateEarthquakeObjects(data);
        var earthquakeTitles = earthquakes.map(function (item) {
            return {"title": getEarthquakeProperty("title", item)};
        });
        var earthquakeLocations = earthquakes.map(function (item) {
            return {
                "lat": getEarthquakeProperty("lat", item),
                "lng": getEarthquakeProperty("lng", item)
            };
        });

        renderTitle(earthquakeTitles);
        addPins(earthquakeLocations);
    });
    
    initMap();

});