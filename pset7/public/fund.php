<?php

    //config
    require("../includes/config.php");

    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // access cash
        $cash = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);

        // give the correct format
        number_format($cash[0]["cash"], 2, ".", ",");

        render("fund.php", ["title" => "Funds", "cash" => $cash[0]["cash"]]);
    }

    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // access form data
        $add = $_POST["add"];

        // verify numeric value
        if (!is_numeric($add))
            apologize("You must provide a number.");

        if ($add != NULL)
        {
          // add to database
          $query = query("UPDATE users SET cash = cash + ? WHERE id = ?", $add, $_SESSION["id"]);

          // add to history
          $history = query("INSERT INTO history (id, type, price) VALUES (?, 'FUND', ?)", $_SESSION["id"], $add);

          // redirect user
          redirect("/");
        }

        if ($add == NULL)
            apologize("Please enter a correct value.");


    }
?>
