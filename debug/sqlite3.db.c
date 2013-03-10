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

int db_open_database(int *retval, sqlite3 **handle) {

  if (*retval = sqlite3_open("example.db", handle)) {
    printf("Database connection failed \n");
  } else {
    printf("Database connection successful \n");
  }
}


int db_table_create(int *retval, sqlite3 **handle) {
 
  char id[30] = "id integer primary key";
  char uname[30] = "uname text not null";
  char upass[30] = "upass text not null";
  char activ[30] = "activated integer";
  char times[50] = "timestamp datetime default current_timestamp";
  char buffr[300];
  int qc;

  qc = sprintf(buffr, "create table if not exists users (%s, %s, %s, %s, %s)", id, uname, upass, activ, times);
  *retval = sqlite3_exec(*handle, buffr, 0, 0, 0);
}


int db_insert(int *retval, sqlite3 **handle, char uname[30], char upass[30], int activated) {

  char buffr[150];
  int qc;

  qc = sprintf(buffr, "insert into users (uname, upass, activated) values ('%s', '%s', '%d')", uname, upass, activated);
  *retval = sqlite3_exec(*handle, buffr, 0, 0, 0);
}


int db_select(int *retval, sqlite3_stmt **stmt, sqlite3 **handle) {
  
  char buffr[300];
  int qc;

  qc = sprintf(buffr, "select * from users");
  if (*retval = sqlite3_prepare_v2(*handle, buffr, -1, stmt, 0)) {
    printf("Selecting from database faile \n");
    return -1;
  }
}


int db_print_query(int *retval, sqlite3_stmt **stmt) {

  int cols = sqlite3_column_count(*stmt);

  while(1) {
    
    *retval = sqlite3_step(*stmt);
    if (*retval == SQLITE_ROW) {
      for (int col = 0; col < cols; col++) {
        const char *val = (const char*)sqlite3_column_text(*stmt, col);
        printf("%s = %s\t", sqlite3_column_name(*stmt, col), val);
      }
      printf("\n");
    } else if (*retval == SQLITE_DONE) {
      printf("All rows fetched\n");
      break;
    } else {
      printf("Some error encountered\n");
      return -1;
    }
  }
}


int main(int argc, char** args) {

  int retval;
  int q_cnt = 5, q_size = 200, idx = 0;
  char **queries = malloc(sizeof(char) * q_cnt * q_size);
  
  sqlite3_stmt *stmt;
  sqlite3 *handle;
  
  db_open_database(&retval, &handle);

  db_table_create(&retval, &handle);
  db_insert(&retval, &handle, "user1", "user1pass", 1);
  db_insert(&retval, &handle, "user2", "user2pass", 1);

  db_select(&retval, &stmt, &handle);

  db_print_query(&retval, &stmt);

  sqlite3_close(handle);
  return 0;
}


