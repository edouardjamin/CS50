<form action="sell.php" method="post">
    <fieldset>
        <div class="form-group">
              <select class="form-control" name="symbol">
                <?php
                foreach ($owned as $own)
                {
                    printf("<option value='" . $own["symbol"] . "'>" . $own["symbol"] . "</option>");
                }
                 ?>
              </select>
        </div>

        <div class="form-group">
            <input class="form-control" type="text" name="number" required placeholder="Shares" />
        </div>

        <div class="form-group">
            <button type="submit" class="btn btn-default">Sell</button>
        </div>
    </fieldset>
</form>
