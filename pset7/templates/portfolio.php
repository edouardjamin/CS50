<div>

    <table class="table table-stripped">
      <thead>
        <tr>
            <th>Symbol</th>
            <th>Name</th>
            <th>Shares</th>
            <th>Price</th>
            <th>TOTAL</th>
        </tr>
      </thead>

      <tbody>
    <?php
        foreach ($positions as $position)
        {
            print("<tr>");
            print("<td>" . $position["symbol"] . "</td>");
            print("<td>" . $position["name"] . "</td>");
            print("<td>" . $position["shares"] . "</td>");
            print("<td>$ " . number_format($position["price"], 2, '.', ',') . "</td>");
            print("<td>$ " . number_format($position["price"] * $position["shares"], 2, '.', ',') . "</td>");
            print("</tr>");
        }
    ?>

          <!-- cash line -->
          <tr class="info">
              <td>CASH</td>
              <td></td>
              <td></td>
              <td></td>
              <td>$<?php extract($cash); ?>
              <?= number_format($cash, 2, '.', ',')?></td>
          </tr>
      </tbody>
</table>
</div>
