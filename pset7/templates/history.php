<div>

    <table class="table table-stripped">
      <thead>
        <tr>
            <th>Transaction</th>
            <th>Date/Time</th>
            <th>Symbol</th>
            <th>Shares</th>
            <th>Price</th>
        </tr>
      </thead>

      <tbody>
    <?php
        foreach ($positions as $position)
        {
            print("<tr>");
            print("<td>" . $position["type"] . "</td>");
            print("<td>" . $position["date"] . "</td>");
            print("<td>" . $position["symbol"] . "</td>");
            print("<td>" . $position["share"] . "</td>");
            print("<td>$ " . number_format($position["price"], 2, '.', ',') . "</td>");
            print("</tr>");
        }
    ?>
      </tbody>
</table>
</div>
