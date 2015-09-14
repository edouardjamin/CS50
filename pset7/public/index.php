<?php

    // configuration
    require("../includes/config.php");

    // access the share mysql
    $rows = query("SELECT * FROM shares WHERE id = ?", $_SESSION["id"]);

    $positions = [];
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "price" => $stock["price"],
                "shares" => $row["shares"],
                "symbol" => $row["symbol"],
                "shares" => $row["shares"]
            ];
        }
    }

    // access the cash available
    $totalcash = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
    $cash = $totalcash[0];

    // render portfolio
    render("portfolio.php", [
                              "title" => "Portfolio",
                              "positions" => $positions,
                              "cash" => $cash
                            ]);



?>
