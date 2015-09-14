You currently have $ <?php print(number_format($cash, 2, ".", ",")); ?>. Do you want to add more?

<form method="post">
    <div class="form-group">
          <input autofocus required class="form-control" type="text" name="add" placeholder="Add" />
    </div>

    <div class="form-group">
          <button class="btn btn-default" type="submit">Add!</button>
    </div>
</form>
