#include <stdio.h>
#include "sqlite3.h

int main(void)
{
	sqlite3 *db;
	int rc;

	rc = sqlite3_open("test.db", &db);
	if(rc)
		{
		printf("error\n");
		sqlite3_close(db);
		return 1;
		}

	sqlite3_close(db);
	return 0;
}

