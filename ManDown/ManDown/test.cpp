/*
#include <stdio.h>
#include <conio.h>
#include <mysql.h>

#pragma comment(lib, "libmysql.lib")
void MysqlTest(int argc, char *argv[])
{
	char host[] = "localhost";
	char szDatabase[] = "mysql";	//mysql���е����ݿ���
	char username[] = "root";
	char password[] = "20010422";	//mysql����Ա����
	unsigned int port = 3306;
	MYSQL *conn;
	if ((conn = mysql_init((MYSQL*)0))
		&& (mysql_options(conn, MYSQL_SET_CHARSET_NAME, "gbk") == 0)
		&& mysql_real_connect(conn, host, username, password, szDatabase, port, NULL, 0))
		printf("�������ݿ�ɹ���\n");
	else
	{
		printf("�������ݿ�ʧ�ܣ�\n");
		mysql_close(conn);
		getch();
	}
	mysql_close(conn);
	getch();
}
*/

