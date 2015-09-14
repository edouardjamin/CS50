<?php

  // configuration
  require("../includes/config.php");

  // if user reached page via GET (as by clicking a link or via redirect)
  if ($_SERVER["REQUEST_METHOD"] == "GET")
  {
      // else render form
      render("qote_form.php", ["title" => "Qote"]);
  }

  if ($_SERVER["REQUEST_METHOD"] == "POST")
  {
      // verify symbol is none blank
      if ($_POST["symbol"] == NULL)
          apologize("You must provide a symbol");

      $stock = lookup($_POST["symbol"]);

      if ($stock == NULL)
          apologize("You must provide a valid symbol.");

      render("qote.php", ["title" => "Quote", "symbol" => $stock["symbol"], "name" => $stock["name"], "price" => $stock["price"]]);
  }


 ?>
