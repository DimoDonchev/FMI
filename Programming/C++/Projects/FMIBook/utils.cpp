#include "utils.h"

char* findContent(const char* buffer, char * content) {
	int i = 0;
	while (buffer[i] != '>') {
		i++;
	}
	i++;
	int start = i;
	while (buffer[i] != '<' && i < 127) {
		content[i - start] = buffer[i];
		i++;
	}
	content[i - start] = '\0';
	return content;
}

char* findDescription(const char* buffer, char * description) {
	int i = 0;
	while (buffer[i] != 'r' || buffer[i + 1] != '=' || buffer[i + 2] != '"') {//find the start of descr=" 
		i++;
	}
	i = i + 3;
	int start = i;
	while (buffer[i] != '"' && start - i < 63) {
		description[i - start] = buffer[i];
		i++;
	}
	description[i - start] = '\0';
	return description;
}

char * findPath(const char * buffer, char * path) {
	int i = 0;
	while (buffer[i] != 'c' && buffer[i + 1] != '=' && buffer[i + 2] != '"') {// find the start of src="
		i++;
	}
	i += 3;
	int start = i;
	while (buffer[i] != '"' && i < 64) {
		path[i - start] = buffer[i];
		i++;
	}
	path[i - start] = '\0';
	return path;
}

char * findLink(const char * buffer, char * link) {
	int i = 0;
	while (buffer[i] != 'f' && buffer[i + 1] != '=' && buffer[i + 2] != '"') {// find the start of src="
		i++;
	}
	i += 3;
	int start = i;
	while (buffer[i] != '"' && i < 64) {
		link[i - start] = buffer[i];
		i++;
	}
	link[i - start] = '\0';
	return link;
}