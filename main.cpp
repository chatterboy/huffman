#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
using namespace std;
#define BUFFER_SIZE 128
#define WHITE_SPACE 0x20

FILE *fin;
char buf[BUFFER_SIZE];

void init_read_file() {
	fin = fopen("input.in", "r");
}

void free_read_file() {
	fclose(fin);
}

int read_line_file() {
	memset(buf, 0, sizeof buf);
	if (fgets(buf, sizeof buf, fin) != NULL)
		return 0;
	return 1;
}

void _make_words_line() {
	char* token;
	char _buf[BUFFER_SIZE] = {0};
	strcpy(_buf, buf);
	token = strtok(_buf, " .,;:\n!?\"(_");
	while (token != NULL) {
		puts(token);
		token = strtok(NULL, " .,;:\n!?\"(_");
	}
}

void make_words_line() {
	int n;
	bool flag;
	string w;
	n = strlen(buf);
	for (int i = 0; i < n; i++) {
		if (isalpha(buf[i]))
			w.push_back(buf[i]);
		else {
			flag = false;
			if (buf[i] != WHITE_SPACE)
				if ((i-1 >= 0 && isalpha(buf[i-1])) && (i+1 < n && isalpha(buf[i+1]))) {
					flag = true;
					w.push_back(buf[i]);
				}
			if (!flag) {
				if (!w.empty())
//					printf("%s %d\n", w.c_str(), w.size());
					puts(w.c_str());
				w.clear();
			}
		}
	}
}

int main() {
	init_read_file();
	while (!read_line_file()) {
		make_words_line();
	}
	free_read_file();
}