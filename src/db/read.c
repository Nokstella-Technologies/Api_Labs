  if (mysql_query(con, "SELECT * FROM projects"))
  {
      finish_with_error(con);
  }