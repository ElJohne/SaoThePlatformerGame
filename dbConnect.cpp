#include <Windows.h>
#include <iostream>
#include <mysql.h>
#include <string>
#include "setups.h"
using namespace std;

int singIn(string name, string password) {

	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	int i = 0;

	conn = mysql_init(NULL);
	if (conn == NULL)
	{
		fprintf(stderr, "Error: can't create MySQL-descriptor\n");
	}
	if (!mysql_real_connect(conn, "91.235.128.251", "admin_ElJohne", "123321", "admin_saotheplatformer", 3306, NULL, 0))
	{
		fprintf(stderr, "Error: can't connect to database %s\n", mysql_error(conn));
	}
	else
	{
		fprintf(stdout, "Success!\n");
	}

	mysql_set_character_set(conn, "utf8");
	cout << "connectioncharacterset: " << mysql_character_set_name(conn) << endl;
	mysql_query(conn, "SELECT ID, Username, Password FROM account");
	if (res = mysql_store_result(conn)) {
		while (row = mysql_fetch_row(res)) {
			if (row[1] == name && row[2] == password) {
				return atoi(row[0]);
			}
		}
	} else fprintf(stderr, "%s\n", mysql_error(conn));
	return -1;
	mysql_close(conn);
}

int singUp(string name, string password) {


	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	int i = 0;

	conn = mysql_init(NULL);
	if (conn == NULL)
	{
		fprintf(stderr, "Error: can'tcreate MySQL-descriptor\n");
	}
	if (!mysql_real_connect(conn, "91.235.128.251", "admin_ElJohne", "123321", "admin_saotheplatformer", 3306, NULL, 0))
	{
		fprintf(stderr, "Error: can't connect to database %s\n", mysql_error(conn));
	}
	else
	{
		fprintf(stdout, "Success!\n");
	}

	mysql_set_character_set(conn, "utf8");
	cout << "connectioncharacterset: " << mysql_character_set_name(conn) << endl;

	mysql_query(conn, "SELECT Username FROM account");
	if (res = mysql_store_result(conn)) {
		while (row = mysql_fetch_row(res)) {
			if (row[i] == name) return -1;
		}
	}
	int tmpID = 0;
	mysql_query(conn, "SELECT ID FROM account WHERE ID = (SELECT MAX(ID) FROM account)");
	if (res = mysql_store_result(conn)) {
		while (row = mysql_fetch_row(res)) {
			tmpID = atoi(row[i]);
		}
	}
	tmpID++;
	string tmp = "INSERT INTO account VALUES(" + to_string(tmpID) + ",'" + name + "','" + password + "',0,0,'Newbye',0,0)";
	char temp[1024];
	strcpy_s(temp, tmp.c_str());
	mysql_query(conn, temp);

	mysql_close(conn);
	return tmpID;
}

void setStatus(int id);


void getLevel(int id) {
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	int i = 0;

	conn = mysql_init(NULL);
	if (conn == NULL)
	{
		fprintf(stderr, "Error: can't create MySQL-descriptor\n");
	}
	if (!mysql_real_connect(conn, "91.235.128.251", "admin_ElJohne", "123321", "admin_saotheplatformer", 3306, NULL, 0))
	{
		fprintf(stderr, "Error: can't connect to database %s\n", mysql_error(conn));
	}
	else
	{
		fprintf(stdout, "Success!\n");
	}

	mysql_set_character_set(conn, "utf8");
	cout << "connectioncharacterset: " << mysql_character_set_name(conn) << endl;
	mysql_query(conn, "SELECT ID, Level FROM account"); 
	if (res = mysql_store_result(conn)) {
		while (row = mysql_fetch_row(res)) {
			if (atoi(row[0]) == id) {
				setAccountLvl(atoi(row[1]));
			}
		}
	}
	else fprintf(stderr, "%s\n", mysql_error(conn));
	mysql_close(conn);
}
void setLevel(int id, int lvl) {
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	int i = 0;

	conn = mysql_init(NULL);
	if (conn == NULL)
	{
		fprintf(stderr, "Error: can't create MySQL-descriptor\n");
	}
	if (!mysql_real_connect(conn, "91.235.128.251", "admin_ElJohne", "123321", "admin_saotheplatformer", 3306, NULL, 0))
	{
		fprintf(stderr, "Error: can't connect to database %s\n", mysql_error(conn));
	}
	else
	{
		fprintf(stdout, "Success!\n");
	}

	mysql_set_character_set(conn, "utf8");
	cout << "connectioncharacterset: " << mysql_character_set_name(conn) << endl;
	string myQuery = "UPDATE account SET Level = " + to_string(lvl) + " WHERE id = " + to_string(id);
	char myQueryChar[1024];
	strcpy_s(myQueryChar, myQuery.c_str());
	mysql_query(conn, myQueryChar); 
	mysql_close(conn);
	setStatus(id);
}
void getExp(int id) {
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	int i = 0;

	conn = mysql_init(NULL);
	if (conn == NULL)
	{
		fprintf(stderr, "Error: can't create MySQL-descriptor\n");
	}
	if (!mysql_real_connect(conn, "91.235.128.251", "admin_ElJohne", "123321", "admin_saotheplatformer", 3306, NULL, 0))
	{
		fprintf(stderr, "Error: can't connect to database %s\n", mysql_error(conn));
	}
	else
	{
		fprintf(stdout, "Success!\n");
	}

	mysql_set_character_set(conn, "utf8");
	cout << "connectioncharacterset: " << mysql_character_set_name(conn) << endl;
	mysql_query(conn, "SELECT ID, Exp FROM account"); 
	if (res = mysql_store_result(conn)) {
		while (row = mysql_fetch_row(res)) {
			if (atoi(row[0]) == id) {
				setAccountExp(atoi(row[1]));
			}
		}
	}
	else fprintf(stderr, "%s\n", mysql_error(conn));
	mysql_close(conn);
}
void setExp(int id, int exp) {
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	int expSet = 0;
	switch (getAccountLvl()) {
	case 0:
		expSet = exp;
		if (exp >= 500) {
			setLevel(id, (getAccountLvl() + 1));
			expSet = exp - 500;
		}
		break;
	case 1:
		expSet = exp;
		if (exp >= 1000) {
			setLevel(id, (getAccountLvl() + 1));
			expSet = exp - 1000;
		}
		break;
	case 2:
		expSet = exp;
		if (exp >= 3000) {
			setLevel(id, (getAccountLvl() + 1));
			expSet = exp - 3000;
		}
		break;
	case 3:
		expSet = exp;
		if (exp >= 7000) {
			setLevel(id, (getAccountLvl() + 1));
			expSet = exp - 7000;
		}
		break;
	case 4:
		expSet = exp;
		if (exp >= 10000) {
			setLevel(id, (getAccountLvl() + 1));
			expSet = exp - 10000;
		}
		break;
	case 5:
		expSet = exp;
		if (exp >= 12500) {
			setLevel(id, (getAccountLvl() + 1));
			expSet = exp - 12500;
		}
		break;
	case 6:
		expSet = exp;
		if (exp >= 15000) {
			setLevel(id, (getAccountLvl() + 1)); 
			expSet = exp - 15000;
		}
		break;
	case 7:
		expSet = exp;
		if (exp >= 20000) {
			setLevel(id, (getAccountLvl() + 1));
			expSet = exp - 20000;
		}
		break;
	case 8:
		expSet = exp;
		if (exp >= 25000) {
			setLevel(id, (getAccountLvl() + 1));
			expSet = exp - 25000;
		}
		break;
	case 9:
		expSet = exp;
		if (exp >= 30000) {
			setLevel(id, (getAccountLvl() + 1));
			expSet = exp - 30000;
		}
		break;
	case 10:
		expSet = exp;
		if (exp >= 35000) {
			setLevel(id, (getAccountLvl() + 1)); 
			expSet = exp - 35000;
		}
		break;
	case 11:
		expSet = exp;
		if (exp >= 40000) {
			setLevel(id, (getAccountLvl() + 1));
			expSet = exp - 40000;
		}
		break;
	case 12:
		expSet = exp;
		if (exp >= 45000) {
			setLevel(id, (getAccountLvl() + 1));
			expSet = exp - 45000;
		}
		break;
	case 13:
		expSet = exp;
		if (exp >= 50000) {
			setLevel(id, (getAccountLvl() + 1));
			expSet = exp - 50000;
		}
		break;
	case 14:
		expSet = exp;
		if (exp >= 55000) {
			setLevel(id, (getAccountLvl() + 1));
			expSet = exp - 55000;
		}
		break;
	case 15:
		expSet = exp;
		if (exp >= 60000) {
			setLevel(id, (getAccountLvl() + 1));
			expSet = exp - 60000;
		}
		break;
	case 16:
		expSet = exp;
		if (exp >= 70000) {
			setLevel(id, (getAccountLvl() + 1));
			expSet = exp - 70000;
		}
		break;
	case 17:
		expSet = exp;
		if (exp >= 80000) {
			setLevel(id, (getAccountLvl() + 1));
			expSet = exp - 80000;
		}
		break;
	case 18:
		expSet = exp;
		if (exp >= 90000) {
			setLevel(id, (getAccountLvl() + 1));
			expSet = exp - 90000;
		}
		break;
	case 19:
		expSet = exp;
		if (exp >= 95000) {
			setLevel(id, (getAccountLvl() + 1));
			expSet = exp - 95000;
		}
		break;
	case 20:
		expSet = exp;
		if (exp >= 100000) {
			setLevel(id, (getAccountLvl() + 1));
			expSet = exp - 100000;
		}
		break;
	case 21:
		expSet = exp;
		if (exp >= 110000) {
			setLevel(id, (getAccountLvl() + 1));
			expSet = exp - 110000;
		}
		break;
	case 22:
		expSet = exp;
		if (exp >= 120000) {
			setLevel(id, (getAccountLvl() + 1));
			expSet = exp - 120000;
		}
		break;
	case 23:
		expSet = exp;
		if (exp >= 130000) {
			setLevel(id, (getAccountLvl() + 1));
			expSet = exp - 130000;
		}
		break;
	case 24:
		expSet = exp;
		if (exp >= 140000) {
			setLevel(id, (getAccountLvl() + 1));
			expSet = exp - 140000;
		}
		break;
	case 25:
		expSet = exp;
		if (exp >= 150000) {
			setLevel(id, (getAccountLvl() + 1));
			expSet = exp - 150000;
		}
		break;
	default: expSet = exp;
	}

	conn = mysql_init(NULL);
	if (conn == NULL)
	{
		fprintf(stderr, "Error: can't create MySQL-descriptor\n");
	}
	if (!mysql_real_connect(conn, "91.235.128.251", "admin_ElJohne", "123321", "admin_saotheplatformer", 3306, NULL, 0))
	{
		fprintf(stderr, "Error: can't connect to database %s\n", mysql_error(conn));
	}
	else
	{
		fprintf(stdout, "Success!\n");
	}

	mysql_set_character_set(conn, "utf8");
	cout << "connectioncharacterset: " << mysql_character_set_name(conn) << endl;
	string myQuery = "UPDATE account SET Exp = " + to_string(expSet) + " WHERE id = " + to_string(id);
	char myQueryChar[1024];
	strcpy_s(myQueryChar, myQuery.c_str());
	mysql_query(conn, myQueryChar);
	mysql_close(conn);
	getLevel(id);
	getExp(id);
}
void getCoins(int id) {
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	int i = 0;

	conn = mysql_init(NULL);
	if (conn == NULL)
	{
		fprintf(stderr, "Error: can't create MySQL-descriptor\n");
	}
	if (!mysql_real_connect(conn, "91.235.128.251", "admin_ElJohne", "123321", "admin_saotheplatformer", 3306, NULL, 0))
	{
		fprintf(stderr, "Error: can't connect to database %s\n", mysql_error(conn));
	}
	else
	{
		fprintf(stdout, "Success!\n");
	}

	mysql_set_character_set(conn, "utf8");
	cout << "connectioncharacterset: " << mysql_character_set_name(conn) << endl;
	mysql_query(conn, "SELECT ID, Coins FROM account"); 
	if (res = mysql_store_result(conn)) {
		while (row = mysql_fetch_row(res)) {
			if (atoi(row[0]) == id) {
				setAccountCoins(atoi(row[1]));
			}
		}
	}
	else fprintf(stderr, "%s\n", mysql_error(conn));
	mysql_close(conn);
}
void setCoins(int id, int coins) {
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	conn = mysql_init(NULL);
	if (conn == NULL)
	{
		fprintf(stderr, "Error: can't create MySQL-descriptor\n");
	}
	if (!mysql_real_connect(conn, "91.235.128.251", "admin_ElJohne", "123321", "admin_saotheplatformer", 3306, NULL, 0))
	{
		fprintf(stderr, "Error: can't connect to database %s\n", mysql_error(conn));
	}
	else
	{
		fprintf(stdout, "Success!\n");
	}

	mysql_set_character_set(conn, "utf8");
	cout << "connectioncharacterset: " << mysql_character_set_name(conn) << endl;
	string myQuery = "UPDATE account SET Coins = " + to_string(coins) + " WHERE id = " + to_string(id);
	char myQueryChar[1024];
	strcpy_s(myQueryChar, myQuery.c_str());
	mysql_query(conn, myQueryChar);
	mysql_close(conn);
}
void getGold(int id) {
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	conn = mysql_init(NULL);
	if (conn == NULL)
	{
		fprintf(stderr, "Error: can't create MySQL-descriptor\n");
	}
	if (!mysql_real_connect(conn, "91.235.128.251", "admin_ElJohne", "123321", "admin_saotheplatformer", 3306, NULL, 0))
	{
		fprintf(stderr, "Error: can't connect to database %s\n", mysql_error(conn));
	}
	else
	{
		fprintf(stdout, "Success!\n");
	}

	mysql_set_character_set(conn, "utf8");
	cout << "connectioncharacterset: " << mysql_character_set_name(conn) << endl;
	mysql_query(conn, "SELECT ID, Gold FROM account"); 
	if (res = mysql_store_result(conn)) {
		while (row = mysql_fetch_row(res)) {
			if (atoi(row[0]) == id) {
				setAccountGold(atoi(row[1]));
			}
		}
	}
	else fprintf(stderr, "%s\n", mysql_error(conn));
	mysql_close(conn);
}
void setGold(int id, int gold) {
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	conn = mysql_init(NULL);
	if (conn == NULL)
	{
		fprintf(stderr, "Error: can't create MySQL-descriptor\n");
	}
	if (!mysql_real_connect(conn, "91.235.128.251", "admin_ElJohne", "123321", "admin_saotheplatformer", 3306, NULL, 0))
	{
		fprintf(stderr, "Error: can't connect to database %s\n", mysql_error(conn));
	}
	else
	{
		fprintf(stdout, "Success!\n");
	}

	mysql_set_character_set(conn, "utf8");
	cout << "connectioncharacterset: " << mysql_character_set_name(conn) << endl;
	string myQuery = "UPDATE account SET Gold = " + to_string(gold) + " WHERE id = " + to_string(id);
	char myQueryChar[1024];
	strcpy_s(myQueryChar, myQuery.c_str());
	mysql_query(conn, myQueryChar);
	mysql_close(conn);
}
void getStatus(int id) {
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	conn = mysql_init(NULL);
	if (conn == NULL)
	{
		fprintf(stderr, "Error: can't create MySQL-descriptor\n");
	}
	if (!mysql_real_connect(conn, "91.235.128.251", "admin_ElJohne", "123321", "admin_saotheplatformer", 3306, NULL, 0))
	{
		fprintf(stderr, "Error: can't connect to database %s\n", mysql_error(conn));
	}
	else
	{
		fprintf(stdout, "Success!\n");
	}

	mysql_set_character_set(conn, "utf8");
	cout << "connectioncharacterset: " << mysql_character_set_name(conn) << endl;
	mysql_query(conn, "SELECT ID, Status FROM account"); 
	if (res = mysql_store_result(conn)) {
		while (row = mysql_fetch_row(res)) {
			if (atoi(row[0]) == id) {
				setAccountStatus(row[1]);
			}
		}
	}
	else fprintf(stderr, "%s\n", mysql_error(conn));
	mysql_close(conn);
}
void setStatus(int id) {
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	int t = getAccountLvl();
	string pStatus;
	if (t == 0 || t == 1 || t == 2 || t == 3) pStatus = "Newbye";
	else if (t == 4 || t == 5 || t == 6 || t == 7) pStatus = "Egil";
	else if (t == 8 || t == 9 || t == 10 || t == 11) pStatus = "Yujio";
	else if (t == 12 || t == 13 || t == 14 || t == 15) pStatus = "Alisa";
	else if (t == 16 || t == 17 || t == 18 || t == 19) pStatus = "Asuna";
	else pStatus = "Kirito";
	conn = mysql_init(NULL);
	if (conn == NULL)
	{
		fprintf(stderr, "Error: can't create MySQL-descriptor\n");
	}
	if (!mysql_real_connect(conn, "91.235.128.251", "admin_ElJohne", "123321", "admin_saotheplatformer", 3306, NULL, 0))
	{
		fprintf(stderr, "Error: can't connect to database %s\n", mysql_error(conn));
	}
	else
	{
		fprintf(stdout, "Success!\n");
	}

	mysql_set_character_set(conn, "utf8");
	cout << "connectioncharacterset: " << mysql_character_set_name(conn) << endl;
	string myQuery = "UPDATE account SET Status = " + pStatus + " WHERE id = " + to_string(id);
	char myQueryChar[1024];
	strcpy_s(myQueryChar, myQuery.c_str());
	mysql_query(conn, myQueryChar);
	mysql_close(conn);
}
void getName(int id) {
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	conn = mysql_init(NULL);
	if (conn == NULL)
	{
		fprintf(stderr, "Error: can't create MySQL-descriptor\n");
	}
	if (!mysql_real_connect(conn, "91.235.128.251", "admin_ElJohne", "123321", "admin_saotheplatformer", 3306, NULL, 0))
	{
		fprintf(stderr, "Error: can't connect to database %s\n", mysql_error(conn));
	}
	else
	{
		fprintf(stdout, "Success!\n");
	}

	mysql_set_character_set(conn, "utf8");
	cout << "connectioncharacterset: " << mysql_character_set_name(conn) << endl;
	mysql_query(conn, "SELECT ID, Username FROM account");
	if (res = mysql_store_result(conn)) {
		while (row = mysql_fetch_row(res)) {
			if (atoi(row[0]) == id) {
				setAccountName(row[1]);
			}
		}
	}
	else fprintf(stderr, "%s\n", mysql_error(conn));
	mysql_close(conn);
}