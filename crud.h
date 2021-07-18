#pragma once
#include <mysql.h>

class System {
public:
	System(const char* server, const char* username, const char* password, const char* database, unsigned int port);
	int connect();
	int create(const char* name, int balance);
	int ListAllAccount();
	int get_balance(const char* name);
	int update(const char* oldName, int oldBalance, const char* newName, int newBalance);
	int hardDelete(const char* name, int balance);
	void close();
private:
	const char* server;
	const char* username;
	const char* password;
	const char* database;
	unsigned int port;
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
};