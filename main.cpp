#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <map>
using namespace std;
#define BUFFER_SIZE 128
#define WHITE_SPACE 0x20

FILE *fin;
char buf[BUFFER_SIZE];
map<string,int> wtb;

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

void change_to_lower(string& w) {
	int n;
	n = w.size();
	for (int i = 0; i < n; i++)
		if (isalpha(w[i]) && isupper(w[i]))
			w[i] = tolower(w[i]);
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
				if (!w.empty()) {
					change_to_lower(w);
					wtb[w]++;
				}
				w.clear();
			}
		}
	}
}

int main() {
	init_read_file();
	while (!read_line_file())
		make_words_line();
	free_read_file();
	for (auto it = wtb.begin(); it != wtb.end(); it++)
		printf("%s %d\n", it->first.c_str(), it->second);
}