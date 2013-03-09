/*
 * A simple sqlite3 crete, insert, select program. Helpful for debugging.
 *
 * @filename: sqlite3.db.c
 *
 * @version: 0.0.1
 *
 * @date: 2013-03-09
 *
 * @description: A simple sqlite3 test/debugger
 *
 * Compile with: gcc sqlite.db.c -o sqlite.db -l sqlite3 -std=c99
 *  
 * This example code is copied from http://milky.manishsinha.net/2009/03/30/sqlite-with-c
 *
 */

#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>

int main(int argc, char** args) {
  int retval;
  int q_cnt = 5, q_size = 150, idx = 0;
  char **queries = malloc(sizeof(char) * q_cnt * q_size);
  
  sqlite3_stmt *stmt;
  sqlite3 *handle;
  
  retval = sqlite3_open("exampledb.sqlite3", &handle);

  if (retval) {
    printf("Database connection failed \n");
    return -1;
  } else {
    printf("Connection successful\n");
  }

  char create_table[100] = "create table if not exists users (uname text primay key, pass text not null, activated integer)";
  retval = sqlite3_exec(handle, create_table, 0, 0, 0);

  queries[idx++] = "insert into users values ('user1', 'user1pass', 1)";
  retval = sqlite3_exec(handle, queries[idx-1], 0, 0, 0);

  queries[idx++] = "insert into users values ('user2', 'user2pass', 1)";
  retval = sqlite3_exec(handle, queries[idx-1], 0, 0, 0);

  queries[idx++] = "select * from users";
  retval = sqlite3_prepare_v2(handle, queries[idx-1], -1, &stmt, 0);

  if (retval) {
    printf("Selecting from database failed\n");
    return -1;
  }
  
  int cols = sqlite3_column_count(stmt);
  
  while(1) {
    
    retval = sqlite3_step(stmt);
    if (retval == SQLITE_ROW) {
      for (int col = 0; col < cols; col++) {
        const char *val = (const char*)sqlite3_column_text(stmt, col);
        printf("%s = %s\t", sqlite3_column_name(stmt, col), val);
      }
      printf("\n");
    } else if (retval == SQLITE_DONE) {
      printf("All rows fetched\n");
      break;
    } else {
      printf("Some error encountered\n");
      return -1;
    }
  }
  
  sqlite3_close(handle);
  return 0;
}


