<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // verify if everything is filled
        if ($_POST["username"] == NULL || $_POST["password"] == NULL || $_POST["confirmation"] == NULL)
            apologize("Please fill all the fields");

        // verify if the password = confirmation
        if ($_POST["password"] != $_POST["confirmation"])
            apologize("Please verify your password and its confirmation");

        // insert new user in the database
        $newuser = query("INSERT INTO users (username, hash, cash) VALUES (?, ?, 10000.000)", $_POST["username"], crypt($_POST["password"]));

        // verify if the user is unique
        if ($newuser === false)
            apologize("This user already existed. Please choose another username");

        // get ID of the new user
        $rows = query("SELECT LAST_INSERT_ID() AS id");
        $id = $rows[0]["id"];

        // create a new session
        $_SESSION["id"] = $id;

        // redirect to main page
        redirect("/");
    }

?>
