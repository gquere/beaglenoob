/* This program interfaces with a SQLite database named test into which it inserts
 * a row, and then read all rows back. The functions used are from the sqlite3 API
 * To get values from a database, the steps to follow usually are :
 * Connection, request prepare, request execute and store, fetch row per row
 * /!\ Verify that sqlite3.c and sqlite3.h are in the same folder
 * /!\ With gcc, compile with -lsqlite3 flag
*/

#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include <string.h>

int main(void)
{
	sqlite3 *db;
	int rc, cols, retval, col, nb_rows = 0;
	char *request;
	char *
	sqlite3_stmt *stmt;
	char **queries = malloc(100*sizeof(char)*2);

	rc = sqlite3_open_v2("test.db", &db, 6, NULL);						// open the database, this actually DOES NOT test if the file exists ...
	if(rc)											// because it CREATES the db if it doesn't exit !
		{
		printf("Connection failed\n");
		sqlite3_close(db);
		return 1;
		}

	queries[0] = "SELECT * FROM test";							// SQL request
	retval = sqlite3_prepare_v2(db, queries[0], -1, &stmt, 0);				// prepare the request and store the result in stmt
	if(retval)
		{
		printf("Failed preparing the request\n");
		return 1;
		}

	cols = sqlite3_column_count(stmt);							// count the number of attributes per element
	rc = sqlite3_step(stmt);								// fetch the first row from stmt
	while(rc != SQLITE_DONE)
		{
		if(rc == SQLITE_ROW)								// there is data
			{
			nb_rows++;
			for(col=0 ; col<cols; col++)
				{
				const char *val = (const char*) sqlite3_column_text(stmt, col); // convert each attribute to char*
				printf("%s = %s\t", sqlite3_column_name(stmt, col), val);       // show the content stored in val
				}
			printf("\n");
			}
		else
			printf("Failed fetching a row");
		rc = sqlite3_step(stmt);
		}

	queries[1] = "INSERT INTO test VALUES('";
	strcat(queries[1], );
	strcat(queries[1]; "', '900;400')";
	rc = sqlite3_exec(db, queries[1], 0, 0, 0);
	if(rc)
		{
		printf("Write failed\n");
		return 1;
		}

	sqlite3_close(db);

	return 0;
}

