set(sql_source_files
    sqlite3.c
    sqlite3.h
)
add_library(sql ${sql_source_files})

add_definitions(" -Os -I. -DSQLITE_OMIT_LOAD_EXTENSION -DSQLITE_THREADSAFE=0 -DSQLITE_ENABLE_FTS4 \
                  -DSQLITE_ENABLE_FTS5 -DSQLITE_ENABLE_JSON1 \
                  -DSQLITE_ENABLE_RTREE -DSQLITE_ENABLE_EXPLAIN_COMMENTS \
                  -DHAVE_USLEEP -DHAVE_READLINE ")   
