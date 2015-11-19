#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include <my_global.h>
#include <mysql.h>
#pragma comment(lib, "libmysql.lib")

#define BUFFER_SIZE 512
#define _BUFFER_SIZE 65536

FILE *fout;

MYSQL *conn;
const char *server = "localhost";
const char *user = "root";
const char *password = "1234";
const char *database = "ibm";
int port = 3306;

vector<vector<string> > problem_records;

void add_backslash(string& des, string &src) {
	des.clear();
	des = "";
	for (int i = 0; i < src.size(); i++) {
		if (src[i] == '\"' || src[i] == '\'') { des += "\\\\\\"; }
		des.push_back(src[i]);
	}
}

void init_mysql_conf() {
	// not now
}

int init_mysql_conn() {
	conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, server, user, password, database, port, NULL, 0))
		return 0;
	mysql_set_character_set(conn, "euckr");
	return 1;
}

void get_all_problems_mysql() {
	int i, n;
	char sql[BUFFER_SIZE];
	MYSQL_RES *res;
	MYSQL_ROW row;
	sprintf(sql, "select * from problems");
	mysql_real_query(conn, sql, strlen(sql));
	res = mysql_store_result(conn);
	n = mysql_num_fields(res);
	while (row = mysql_fetch_row(res)) {
		vector<string> record;
		for (i = 0; i < n; i++)
			record.push_back(string(row[i]));
		if (!record[1].empty()) problem_records.push_back(record);
	}
	mysql_free_result(res);
}

void print_problems() {
	int i, j, n, m;
	n = problem_records.size();
	m = problem_records[0].size();
	fout = fopen("output.txt", "w");
	for (i = 0; i < n; i++) {
		for (j = 0; j < m-1; j++)
			fprintf(fout, "%s ", problem_records[i][j].c_str());
		fprintf(fout, "%s\n\n\n", problem_records[i][m-1].c_str());
	}
	fclose(fout);
}

void insert_backslash_problems() {
	int n;
	n = problem_records.size();
	for (int i = 0; i < n; i++) {
		string attribute = problem_records[i][1];
		add_backslash(problem_records[i][1], attribute);
	}
}

void replca_all_problems_mysql() {
	char sql[_BUFFER_SIZE];
//	fout = fopen("output.txt", "w");
	for (int i = 0; i < problem_records.size(); i++) {
		memset(sql, 0, sizeof(sql));
		sprintf(sql, "replace into problems values (\'%s\', \'%s\', \'%s\', \'%s\', \'%s\', \'%s\')",
			problem_records[i][0].c_str(), problem_records[i][1].c_str(), problem_records[i][2].c_str(),
			problem_records[i][3].c_str(), problem_records[i][4].c_str(), problem_records[i][5].c_str());
//		fprintf(fout, "%s\n\n\n\n", sql);
		mysql_real_query(conn, sql, strlen(sql));
	}
//	fclose(fout);
}

void remove_all_problems() {
	char sql[BUFFER_SIZE];
	memset(sql, 0, sizeof(sql));
	sprintf(sql, "delete from problems");
	mysql_real_query(conn, sql, strlen(sql));
}

void remove_problems_having_img() {
	vector<vector<string> > _problem_records;
	for (int i = 0; i < problem_records.size(); i++) {
		string::size_type n = problem_records[i][1].find("img");
		if (n == string::npos)
			_problem_records.push_back(problem_records[i]);
	}
	problem_records = _problem_records;
}

void remove_problems_having_img_mysql() {
	char sql[_BUFFER_SIZE];
	remove_all_problems();
	remove_problems_having_img();
	fout = fopen("output.txt", "w");
	for (int i = 0; i < problem_records.size(); i++) {
		memset(sql, 0, sizeof(sql));
		sprintf(sql, "insert into problems values (\'%s\', \'%s\', \'%s\', \'%s\', \'%s\', \'%s\')",
			problem_records[i][0].c_str(), problem_records[i][1].c_str(), problem_records[i][2].c_str(),
			problem_records[i][3].c_str(), problem_records[i][4].c_str(), problem_records[i][5].c_str());
		fprintf(fout, "%s\n\n\n", sql);
		mysql_real_query(conn, sql, strlen(sql));
	}
	fclose(fout);
}

int main() {
	init_mysql_conf();

	if (!init_mysql_conn()) {
		fprintf(stdin, "error:%s\n", mysql_error(conn));
		exit(0);
	}

	// 이미지 소스  잇는거 다 지우기
	get_all_problems_mysql();

	remove_problems_having_img_mysql();

	// 역슬래쉬 추가하기
	get_all_problems_mysql();

	insert_backslash_problems();

	replca_all_problems_mysql();
}
