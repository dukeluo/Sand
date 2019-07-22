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
        var source = "<li class='list-group-item quake-title'><p>{{title}} <small>({{hoursAgo}} hours ago)</small></p></li>";
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

    function addPins(earthquakes) {
        var calcLevelColor = function (mag) {
            var color = ["yellow", "orange", "red"];
            var i = Math.floor(mag-4.0);

            return i <= 2 ? color[i] : color[2];
        };

        earthquakes.forEach(function (earthquake) {
            new google.maps.Marker({
                position: new google.maps.LatLng(earthquake.lat, earthquake.lng),
                map: map,
                title: earthquake.title,
                icon: "./earthquake-"+calcLevelColor(earthquake.mag)+".svg"
            });
        });
    }

    $.getJSON(quakesUrl, function (data) {
        var earthquakes = generateEarthquakeObjects(data);
        var earthquakeTitles = earthquakes.map(function (item) {
            return {
                "title": getEarthquakeProperty("title", item),
                "hoursAgo": Math.floor((Date.now()-getEarthquakeProperty("time", item))/3600000)
            };
        });

        renderTitle(earthquakeTitles);
        addPins(earthquakes);
    });
    
    initMap();

});