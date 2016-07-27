//Modify YOUR_USERNAME and YOUR_PASSWORD.
//Note that dbname is YOUR_USERNAME in PostgreSQL system.
//drop table Hello if it exists in your database.
//
// compile it by
//   gcc -I/usr/include psql.c -L/usr/lib/ -lpq
//
// run it by
//   ./a.out

#include <stdlib.h>
#include <libpq-fe.h>

void error(char *mess)
{
  fprintf(stderr, "### %s\n", mess);
  exit(1);
}

int main(int argc, char **argv)
{
  int nfields, ntuples, i, j;
  PGresult *res;

  setenv("PGOPTIONS", "-c gp_session_role=utility", 1);

  //connect to database
  PGconn *conn = PQconnectdb("host=localhost port=40000 dbname=gpadmin"
                             " user=gpadmin password=gpadmin");
  if (PQstatus(conn) != CONNECTION_OK)
    error(PQerrorMessage(conn));
  
  //query the db
  res = PQexec(conn, "SELECT * FROM mysales");
  if (PQresultStatus(res) != PGRES_TUPLES_OK)
    error(PQresultErrorMessage(res));
  nfields = PQnfields(res);
  ntuples = PQntuples(res);

  for(i = 0; i < ntuples; i++)
    for(j = 0; j < nfields; j++)
      printf("[%d,%d] %s\n", i, j, PQgetvalue(res, i, j));
  PQclear(res);

  //disconnect
  PQfinish(conn);
}
