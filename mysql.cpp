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

	//需要检查字符编码
	mysql_set_character_set(conn, "GBK");

	if (mysql_query(conn, "SELECT * FROM codelist where codelist.marketno=4619;")) {
		std::cerr << "Query failed: " << mysql_error(conn) << std::endl;
		mysql_close(conn);
		return 1;
	}

	MYSQL_RES* res = mysql_store_result(conn);
	if (res)
	{
		int num_fields = mysql_num_fields(res);

		while ((row = mysql_fetch_row(res)) != NULL) {
			for (int i = 0; i < num_fields; i++)
			{
				std::cout << row[i] << "\t";
			}
			std::cout <<  "\n";
		}
		mysql_free_result(res);
	}
	else {
		std::cerr << "获取结果集失败: " << mysql_error(conn) << std::endl;
	}

	mysql_close(conn);
	std::cin.get();
	return 0;
}