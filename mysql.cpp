#include <iostream>
#include <mysql.h>
#include <string>
int main() 
{
	MYSQL_ROW row;

	MYSQL* conn = mysql_init(NULL);
	if (conn == NULL) {
		std::cerr << "mysql_init failed!" << std::endl;
		return 1;
	}

	if (mysql_real_connect(conn, "127.0.0.1", "root", "123", "demo", 3306, NULL, 0) == NULL) {
		std::cerr << "Connection failed: " << mysql_error(conn) << std::endl;
		mysql_close(conn);
		return 1;
	}

	//ÐèÒª¼ì²é×Ö·û±àÂë
	mysql_set_character_set(conn, "GBK");

	if (mysql_query(conn, "SELECT * FROM codelist where codelist.marketno=4619;")) {
		std::cerr << "Query failed: " << mysql_error(conn) << std::endl;
		mysql_close(conn);
		return 1;
	}

	MYSQL_RES* res = mysql_store_result(conn);
	while ((row = mysql_fetch_row(res)) != NULL) {
		std::cout << "Column1: " << row[0] << ", Column2: " << row[1] << ", " << row[2] << ", " << row[3] << ", " << row[4] << ", " << row[5] << ", " << row[6]
			<< ", " << row[7] << ", " << row[8] << ", " << row[9] << std::endl;
	}

	mysql_free_result(res);
	mysql_close(conn);
	std::cin.get();
	return 0;
}