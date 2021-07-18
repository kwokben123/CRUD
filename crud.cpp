#include <iostream>
#include <mysql.h>
#include <iomanip>
#include "crud.h"

using namespace std;

System::System(const char* server, const char* username, const char* password, const char* database, unsigned int port) {
	conn = mysql_init(NULL);
	this->server = server;
	this->username = username;
	this->password = password;
	this->database = database;
	this->port = port;
	res = NULL;
	row = NULL;
}

/*return 0 if successfully connected to database, return 1 otherwise*/
int System::connect() {
	return mysql_real_connect(conn, server, username, password, database, port, NULL, 0) == NULL;
}

/*return 0 if a bank account is successfully created, return 1 otherwise*/
int System::create(const char* name, int balance) {
	char query[500] = "insert into bankaccount (name, balance) values (";
	char bal[11];
	sprintf_s(bal, "%d", balance);

	strcat_s(query, "'");
	strcat_s(query, name);
	strcat_s(query, "', ");
	strcat_s(query, bal);
	strcat_s(query, ");");

	return mysql_query(conn, query);
}

/*return 0 if results are succesfully fetched, return 1 otherwise*/
int System::ListAllAccount() {
	if (mysql_query(conn, "select * from bankaccount;") != 0)
		return 1;
	res = mysql_store_result(conn);
	if (res != NULL) {
		cout << left << setw(24) << "name" << right << setw(10) << "balance" << endl;
		while (row = mysql_fetch_row(res)) {
			cout << left << setw(24) << row[1] << right << setw(10) << row[2] << endl;
		}
	}
	mysql_free_result(res);
	return 0;
}

/*return the balance if the name exists, return -1 otherwise*/
int System::get_balance(const char* name) {
	char query[500] = "select balance from bankaccount where name = '";
	strcat_s(query, name);
	strcat_s(query, "';");
	if (mysql_query(conn, query) != 0)
		return -1;
	res = mysql_store_result(conn);
	if (res != NULL) {
		row = mysql_fetch_row(res);
		mysql_free_result(res);
		return atoi(row[0]);
	}
	mysql_free_result(res);
	return -2;

	
}

/*return 0 if succesfully updates the account, return 1 otherwise*/
int System::update(const char* oldName, int oldBalance, const char* newName, int newBalance) {
	char oldBal[11];
	sprintf_s(oldBal, "%d", oldBalance);
	char newBal[11];
	sprintf_s(newBal, "%d", newBalance);

	char query[500] = "update bankaccount set name = '";
	strcat_s(query, newName);
	strcat_s(query, "', balance = ");
	strcat_s(query, newBal);
	strcat_s(query, " where (id <> 0 and name = '");
	strcat_s(query, oldName);
	strcat_s(query, "' and balance = ");
	strcat_s(query, oldBal);
	strcat_s(query, ");");

	return mysql_query(conn, query);
}

/*return 0 if succesfully deletes the account, return 1 otherwise*/
int System::hardDelete(const char* name, int balance) {
	char bal[11];
	sprintf_s(bal, "%d", balance);

	char query[500] = "delete from bankaccount where (id <> 0 and name = '";
	strcat_s(query, name);
	strcat_s(query, "' and balance = ");
	strcat_s(query, bal);
	strcat_s(query, ");");

	return mysql_query(conn, query);
}

/*Close the connection*/
void System::close() {
	mysql_close(conn);
}
