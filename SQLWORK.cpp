#pragma once
#include "SQLWORK.h"

SQLWork::SQLWork(string FILE_NAME) {
	this->FILE_NAME = FILE_NAME;
}

void SQLWork::open() {
	if (sqlite3_open(FILE_NAME.c_str(), &dataBase)) {
		cout << "Ошибка открытия/создания БД:" << sqlite3_errmsg(dataBase);
		is_open = false;
	}
	else {
		is_open = true;
	}
}

void SQLWork::close() {
	if (sqlite3_close(dataBase) == SQLITE_BUSY) {
		cout << "Ошибка закрытия БД." << endl;
	}
	else {
		is_open = false;
	}
}

void SQLWork::show(vector<string> out_strings, vector<int> num_of_columns) {
	string sql = "SELECT * FROM " + DATA_BASE_NAME + " ;";
	int rc;
	sqlite3_prepare_v2(dataBase, sql.c_str(), -1, &stmt, NULL);

	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		for (int i = 0; i < out_strings.size(); i++) {
			cout << out_strings[i] << sqlite3_column_text(stmt, num_of_columns[i]) << endl;
		}
		cout << endl;
	}
	
	sqlite3_finalize(stmt);
}

void SQLWork::show(string sql_befor_db_name, string sql_after_db_name, vector<string> out_strings, vector<int> num_of_columns) {
	string sql = sql_befor_db_name + DATA_BASE_NAME + sql_after_db_name;
	int rc;

	sqlite3_prepare_v2(dataBase, sql.c_str(), -1, &stmt, NULL);

	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		for (int i = 0; i < out_strings.size(); i++) {
			cout << out_strings[i] << sqlite3_column_text(stmt, num_of_columns[i]) << endl;
		}
		cout << endl;
	}

	sqlite3_finalize(stmt);
}

void SQLWork::create(vector<SQL_cell> fields, string DATA_BASE_NAME) {
	this->fields = fields;
	this->DATA_BASE_NAME = DATA_BASE_NAME;
	string sql = get_create_command();

	doSQL(sql);
}

void SQLWork::push_back(vector<string> field) {
	string sql = get_push_back_command(field);
	doSQL(sql);
}

void SQLWork::update(string fild_for_update, string new_value, string rule) {
	string sql = "UPDATE " + DATA_BASE_NAME + " set " + fild_for_update + " = " + new_value + " where " + rule + " ;";
	doSQL(sql);
}

void SQLWork::delete_field(string rule) {
	string sql = "DELETE from " + DATA_BASE_NAME + " where " + rule + " ;";
	doSQL(sql);
}

void SQLWork::sort(string rule, vector<string> out_strings, vector<int> num_of_columns) {
	string sql = "SELECT * FROM " + DATA_BASE_NAME + " ORDER BY " + rule +" ;";
	int rc;
	sqlite3_prepare_v2(dataBase, sql.c_str(), -1, &stmt, NULL);

	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		for (int i = 0; i < out_strings.size(); i++) {
			cout << out_strings[i] << sqlite3_column_text(stmt, num_of_columns[i]) << endl;
		}
		cout << endl;
	}

	sqlite3_finalize(stmt);
}

string SQLWork::date_mounhth_befor(string mounth) {
	string sql = "SELECT date('now', '-" + mounth + " month');";
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

int SQLWork::get_size() {
	int size = 0, rc;
	string sql = "SELECT count(*) FROM " + DATA_BASE_NAME + " ;";
	sqlite3_prepare_v2(dataBase, sql.c_str(), -1, &stmt, NULL);

	if ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		size = sqlite3_column_int(stmt, 0);
	}
	
	sqlite3_finalize(stmt);
	return size;
}

void SQLWork::find_and_show(string field_in_BD, string field, vector<string> out_strings, vector<int> num_of_columns) {
	int rc;
	string sql = "SELECT * FROM " + DATA_BASE_NAME + " WHERE " + field_in_BD + " GLOB '" + field + "';";
	sqlite3_prepare_v2(dataBase, sql.c_str(), -1, &stmt, NULL);

	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		for (int i = 0; i < out_strings.size(); i++) {
			cout << out_strings[i] << sqlite3_column_text(stmt, num_of_columns[i]) << endl;
		}
		cout << endl;
	}

	sqlite3_finalize(stmt);
}

int SQLWork::get_int(string field_in_DB, string find_field, int field_num) {
	string sql = "SELECT * FROM " + DATA_BASE_NAME + " WHERE " + field_in_DB + " GLOB '" + find_field + "';";

	sqlite3_prepare_v2(dataBase, sql.c_str(), -1, &stmt, NULL);
	
	int rc, value = 0;
	if ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {   
		value = sqlite3_column_int(stmt, field_num);
	}

	sqlite3_finalize(stmt);
	return value;
}

double SQLWork::get_double(string field_in_DB, string find_field, int field_num) {
	string sql = "SELECT * FROM " + DATA_BASE_NAME + " WHERE " + field_in_DB + " GLOB '" + find_field + "';";

	sqlite3_prepare_v2(dataBase, sql.c_str(), -1, &stmt, NULL);
	double value = 0;
	int rc;
	if ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		value = sqlite3_column_double(stmt, field_num);
	}

	sqlite3_finalize(stmt);
	return value;
}

string SQLWork::get_text(string field_in_DB, string find_field, int field_num) {
	string text, sql = "SELECT * FROM " + DATA_BASE_NAME + " WHERE " + field_in_DB + " GLOB '" + find_field + "';";

	sqlite3_prepare_v2(dataBase, sql.c_str(), -1, &stmt, NULL);

	int rc;
	if ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		text = reinterpret_cast<const char*>(sqlite3_column_text(stmt, field_num));
	}

	sqlite3_finalize(stmt);
	return text;
}

string SQLWork::get_push_back_command(vector<string> field) {
	string sql = "INSERT INTO " + DATA_BASE_NAME + " ( ";
	for (int i = 0; i < fields.size(); i++) {
		sql += fields[i].NAME;
		if (i != fields.size() - 1) sql += ",";
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

string SQLWork::get_create_command() {
	string sql = " CREATE TABLE IF NOT EXISTS " + DATA_BASE_NAME + " ( ";

	for (int i = 0; i < fields.size(); i++) {
		sql += fields[i].NAME + " " + fields[i].TYPE;
		if (i != fields.size() - 1) sql += ",";
		sql += " ";
	}

	sql += " ); ";
	return sql;
}

bool SQLWork::doSQL(string sql) {
	if (sqlite3_exec(dataBase, sql.c_str(), callback, 0, &error))
	{
		cout << "Ошибка БД: " << error << endl;
		sqlite3_free(error);
		return false;
	}
	else {
		return true;
	}
}

int SQLWork::callback(void* data, int argc, char** argv, char** azColName) {
	for (int i = 0; i < argc; i++) {
		cout << azColName[i] << " = " << argv[i] << endl;
	}
	cout << "\n";
	return 0;
}