
<?php

  // configuration
  require("../includes/config.php");

  if ($_SERVER["REQUEST_METHOD"] == "GET")
  {
      // query select every symbols owned
      $owned = query("SELECT symbol FROM shares WHERE id = ?", $_SESSION["id"]);

      // render page
      render("sell.php", ["title" => "Sell",
                          "owned" => $owned
                        ]);
  }

  if ($_SERVER["REQUEST_METHOD"] == "POST")
  {
      // retreive data from form
      $symbol = $_POST['symbol'];
      $shares = $_POST["number"];

      // retreive shares owned from db
      $sharesowned = query("SELECT shares FROM shares WHERE id = ? AND symbol = ?", $_SESSION["id"], $symbol);
      $ownshare = $sharesowned[0]["shares"];

      // get price of the action
      $stock = lookup($symbol);

      // the user sells every shares owned
      if ($shares == $ownshare)
      {
          // update cash
          $updatecash = query("UPDATE users SET cash = cash + ? WHERE id = ?", $stock["price"] * $shares, $_SESSION["id"]);

          // update hostory
          $updatehistory = query("INSERT INTO history (id, type, symbol, share, price) VALUES (?, 'SELL', ?, ?, ?)", $_SESSION["id"], $symbol, $shares, $stock["price"]);

          // delete form db
          $query = query("DELETE FROM shares WHERE id = ? AND symbol = ?", $_SESSION["id"], $symbol);

          // redirect user
          redirect("/");
      }

      // the user tries to sell more shares than owned
      if ($shares > $ownshare)
          apologize("You can't sell more shares than you own!");

      // the user sells less shares than owned
      if ($shares < $ownshare)
      {
          // update cash
          $updatecash = query("UPDATE users SET cash = cash + ? WHERE id = ?", $stock["price"] * $shares, $_SESSION["id"]);

          // update hostory
          $updatehistory = query("INSERT INTO history (id, type, symbol, share, price) VALUES (?, 'SELL', ?, ?, ?)", $_SESSION["id"], $symbol, $shares, $stock["price"]);

          // update database
          $query = query("UPDATE shares SET shares = shares - ? WHERE id = ? AND symbol = ?", $shares, $_SESSION["id"], $symbol);

          // redirect user
          redirect("/");
      }



  }



?>
