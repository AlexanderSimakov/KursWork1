#pragma once
#include "include/sql/sqlite3.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct SQL_cell
{
	string NAME = "";
	string TYPE = "";
};


class SQLWork
{
public:
	SQLWork(string FILE_NAME);
	void create_table_if_not_exists(vector<SQL_cell> table_fields, string DATA_BASE_NAME);
	void open();
	void close();
	void push_back(vector<string> field);
	void update(string fild_for_update, string new_value, string rule);
	void delete_field(string rule);
	
	void show_table(string sql_befor_db_name, string sql_after_db_name, vector<string> out_strings, vector<int> num_of_columns, vector<int> lenght_of_columns);
	string get_date_mounth_ago(string mounth_amount);

	int get_int(string db_field, string field_for_search, int num_of_value);
	string get_text(string db_field, string field_for_search, int num_of_value);

private:
	vector<SQL_cell> table_fields;
	string FILE_NAME = "";
	string DATA_BASE_NAME = "";
	sqlite3* dataBase = 0;
	sqlite3_stmt* stmt;

	bool do_sql(string sql);
	string get_created_table_sql_command();
	string get_push_back_sql_command(vector<string> field);
	void print_spaces(int amount);
	
};





