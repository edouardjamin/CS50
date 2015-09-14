<?php

    // configs
    require("../includes/config.php");

    // access db
    $rows = query("SELECT * FROM history WHERE id = ?", $_SESSION["id"]);

    $positions = [];
    foreach ($rows as $row)
    {
            $positions[] = [
                "type" => $row["type"],
                "date" => $row["date"],
                "symbol" => $row["symbol"],
                "share" => $row["share"],
                "price" => $row["price"]
            ];
    }

    render("history.php", ["title" => "History", "positions" => $positions]);
 ?>
