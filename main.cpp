#include <iostream>
#include "crud.h"

using namespace std;

#define server "localhost"
#define port 3306
#define database "testdb"

int main() {
	char username[100];
	char password[100];
	cout << "Username: ";
	cin >> username;
	cout << "Password: ";
	cin >> password;

	System bankAccount(server, username, password, database, port);
	if (bankAccount.connect() == 0) {
		cout << "Connection Error" << endl;
		return 1;
	}
	cout << "Balance of BigBoss = " << bankAccount.get_balance("BigBoss") << endl;
	bankAccount.close();
	return 0;
}