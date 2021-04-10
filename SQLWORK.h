#pragma once
#include "sqlite3.h"
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
	void create(vector<SQL_cell> fields, string DATA_BASE_NAME);
	void open();
	void close();
	void show(vector<string> out_strings, vector<int> num_of_columns);
	void show(string sql_befor_db_name, string sql_after_db_name, vector<string> out_strings, vector<int> num_of_columns);
	void push_back(vector<string> field);
	void update(string fild_for_update, string new_value, string rule);
	void delete_field(string rule);
	void find_and_show(string field_in_BD, string field, vector<string> out_strings, vector<int> num_of_columns);
	void sort(string rule, vector<string> out_strings, vector<int> num_of_columns);
	
	int get_size();
	int get_int(string field_in_DB, string fing_field, int field_value);
	double get_double(string field_in_DB, string fing_field, int field_value);
	string get_text(string field_in_DB, string fing_field, int field_value);
	bool doSQL(string sql);

private:
	vector<SQL_cell> fields;
	string FILE_NAME = "";
	string DATA_BASE_NAME = "";
	sqlite3* dataBase = 0;
	sqlite3_stmt* stmt;
	char* error = 0;
	bool is_open = false;


	static int callback(void* data, int argc, char** argv, char** azColName);
	string get_create_command();
	string get_push_back_command(vector<string> field);
	
};





