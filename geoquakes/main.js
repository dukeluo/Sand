// wait for DOM to load before running JS
$(function() {

    var quakesUrl = 'https://earthquake.usgs.gov/earthquakes/feed/v1.0/summary/4.5_week.geojson';
    var $quakesList = $('#quakes-list');
    var map;

    function getTitles(data) {
        return $.map(data.features, function (value, index) {
            return {"title": value.properties.title};
        });
    }

    function renderTitle(titles) {
        var source = "<li class='quake-title'> {{title}} </li>";
        var template = Handlebars.compile(source);
        var html = "";
        var i;

        for (i = 0; i < titles.length; i++) {
            html += template(titles[i]);
        }
        html = "<ul>" + html + "</ul>";
        $quakesList.html(html);
    }

    $.getJSON(quakesUrl, function (data) {
        renderTitle(getTitles(data));
    });

});