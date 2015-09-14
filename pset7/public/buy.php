<?php
    require("../includes/config.php");

    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // render form
        render("buy.php", ["title" => "Buy"]);
    }

    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
      // retreive info from form
      $symbol = strtoupper($_POST["symbol"]);
      $shares = $_POST["shares"];

      // get the value of the action
      $value = lookup($symbol);

      // verify the value is correct
      if ($value == NULL)
          apologize("This is not a correct symbol. Please check Yahoo Finance");

      // get the amount of cash
      $cash = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);

      $amount = $value["price"] * $shares;


      // if the user is too poor
      if ($amount > $cash[0]["cash"])
      {
        apologize("You do not have enough money to buy theses shares.");
      };

      // if the user has enough money
      if ($amount < $cash[0]["cash"])
      {
          // insert into database
          $insert = query("INSERT INTO shares (id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], $symbol, $shares);

          // update cash
          $updatecash = query("UPDATE users SET cash = cash - ? WHERE id = ?", $amount, $_SESSION["id"]);

          // update hostory
          $updatehistory = query("INSERT INTO history (id, type, symbol, share, price) VALUES (?, 'BUY', ?, ?, ?)", $_SESSION["id"], $symbol, $shares, $value["price"]);

          // redirect user
          redirect("/");
      };

    }

 ?>
