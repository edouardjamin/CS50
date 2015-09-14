<?php

    require(__DIR__ . "/../includes/config.php");

    // numerically indexed array of places
    $places = [];

    // search database for places matching $_GET["geo"]

    // get the GET argmnt
    $places = $_GET["geo"];

    // search into the db
    $query = query("SELECT * FROM places WHERE match(place_name, postal_code, country_code, admin_code1) against(+? IN BOOLEAN MODE)", $places);
    $places = $query;

    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>
