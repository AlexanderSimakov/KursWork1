#pragma once
#include "src/sql/SQLWORK.h"

SQLWork::SQLWork(string FILE_NAME) {
	this->FILE_NAME = FILE_NAME;
}

void SQLWork::create_table_if_not_exists(vector<SQL_cell> table_fields, string DATA_BASE_NAME) {
	this->table_fields = table_fields;
	this->DATA_BASE_NAME = DATA_BASE_NAME;
	do_sql(get_created_table_sql_command());
}

string SQLWork::get_created_table_sql_command() {
	string sql = " CREATE TABLE IF NOT EXISTS " + DATA_BASE_NAME + " ( ";

	for (int i = 0; i < table_fields.size(); i++) {
		sql += table_fields[i].NAME + " " + table_fields[i].TYPE;
		if (i != table_fields.size() - 1) sql += ",";
		sql += " ";
	}

	sql += " ); ";
	return sql;
}

void SQLWork::open() {
	if (sqlite3_open(FILE_NAME.c_str(), &dataBase)) {
		cout << "DB open error:" << sqlite3_errmsg(dataBase);
	}
}

void SQLWork::close() {
	if (sqlite3_close(dataBase) == SQLITE_BUSY) {
		cout << "DB close error" << endl;
	}
}

void SQLWork::push_back(vector<string> field) {
	string sql = get_push_back_sql_command(field);
	do_sql(sql);
}

string SQLWork::get_push_back_sql_command(vector<string> field) {
	string sql = "INSERT INTO " + DATA_BASE_NAME + " ( ";
	for (int i = 0; i < table_fields.size(); i++) {
		sql += table_fields[i].NAME;
		if (i != table_fields.size() - 1) sql += ",";
		sql += " ";
	}

	sql += " ) VALUES ( ";

	for (int i = 0; i < field.size(); i++) {
		sql += field[i];
		if (i != field.size() - 1) sql += ",";
		sql += " ";
	}

	sql += " );";
	return sql;
}

void SQLWork::update(string fild_for_update, string new_value, string rule) {
	string sql = "UPDATE " + DATA_BASE_NAME + " set " + fild_for_update + " = " + new_value + " where " + rule + " ;";
	do_sql(sql);
}

void SQLWork::delete_field(string rule) {
	string sql = "DELETE from " + DATA_BASE_NAME + " where " + rule + " ;";
	do_sql(sql);
}

void SQLWork::show_table(string sql_befor_db_name, string sql_after_db_name, vector<string> out_strings, vector<int> num_of_columns, vector<int> lenght_of_columns) {
	string sql = sql_befor_db_name + DATA_BASE_NAME + sql_after_db_name;
	int rc;
	sqlite3_prepare_v2(dataBase, sql.c_str(), -1, &stmt, NULL);

	for (int i = 0; i < out_strings.size(); i++) {
		cout << " " << out_strings[i];
		print_spaces(lenght_of_columns[i] - out_strings[i].size() - 2);
		cout << "|";
	}
	cout << endl;

	string text;
	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		for (int i = 0; i < out_strings.size(); i++) {
			text = reinterpret_cast<const char*>(sqlite3_column_text(stmt, num_of_columns[i]));
			cout << " " << text;
			print_spaces(lenght_of_columns[i] - text.size() - 2);
			cout << "|";
		}
		cout << endl;
	}

	sqlite3_finalize(stmt);
}

string SQLWork::get_date_mounth_ago(string mounth_amount) {
	string sql = "SELECT date('now', '-" + mounth_amount + " month');";
	string date = "";
	int rc;
	sqlite3_prepare_v2(dataBase, sql.c_str(), -1, &stmt, NULL);
	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
		break;
	}

	sqlite3_finalize(stmt);
	return date;
}

int SQLWork::get_int(string db_field, string field_for_search, int num_of_value) {
	string sql = "SELECT * FROM " + DATA_BASE_NAME + " WHERE " + db_field + " GLOB '" + field_for_search + "';";

	sqlite3_prepare_v2(dataBase, sql.c_str(), -1, &stmt, NULL);

	int rc, value = 0;
	if ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		value = sqlite3_column_int(stmt, num_of_value);
	}

	sqlite3_finalize(stmt);
	return value;
}

string SQLWork::get_text(string db_field, string field_for_search, int num_of_value) {
	string text, sql = "SELECT * FROM " + DATA_BASE_NAME + " WHERE " + db_field + " GLOB '" + field_for_search + "';";

	sqlite3_prepare_v2(dataBase, sql.c_str(), -1, &stmt, NULL);

	int rc;
	if ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		text = reinterpret_cast<const char*>(sqlite3_column_text(stmt, num_of_value));
	}

	sqlite3_finalize(stmt);
	return text;
}

bool SQLWork::do_sql(string sql) {
	char* error = 0;
	if (sqlite3_exec(dataBase, sql.c_str(), 0, 0, &error))
	{
		cout << "DB error: " << error << endl;
		sqlite3_free(error);
		return false;
	}
	else {
		return true;
	}
}

void SQLWork::print_spaces(int amount) {
	for (int i = 0; i < amount; i++) {
		cout << " ";
	}
}