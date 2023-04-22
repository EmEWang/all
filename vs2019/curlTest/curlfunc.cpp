#include "curlfunc.h"


bool curlinit()
{
	curl_global_init(CURL_GLOBAL_ALL);
	return true;
}

bool curlfill()
{
	return true;
}

bool curlget()
{
	return true;
}

bool curlpost()
{
	return true;
}

bool curlsend()
{
	return true;
}

bool curlclear()
{
	return true;
}


size_t receive_data(void* buffer, size_t size, size_t nmemb, FILE* file) {
	size_t r_size = fwrite(buffer, size, nmemb, file);
	fclose(file);
	return r_size;
}
bool curlexample1()
{
	char url[] = "http://www.baidu.com";
	char path[] = "save_file1.txt";
	FILE* file = fopen(path, "w");
	curl_global_init(CURL_GLOBAL_ALL);
	CURL* handle = curl_easy_init();
	curl_easy_setopt(handle, CURLOPT_URL, url);
	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, receive_data);
	curl_easy_setopt(handle, CURLOPT_WRITEDATA, file);
	cout << curl_easy_perform(handle);

	curl_easy_cleanup(handle);
	curl_global_cleanup();

	return true;
}

size_t receive_data2(void* buffer, size_t size, size_t nmemb, FILE* file) {
	size_t r_size = fwrite(buffer, size, nmemb, file);
	return r_size;
}
bool curlexample2()
{
	char url[] = "http://www.baidu.com";
	char path[] = "save_file2.txt";
	FILE* file = fopen(path, "w");
	curl_global_init(CURL_GLOBAL_ALL);
	CURL* handle = curl_easy_init();
	curl_easy_setopt(handle, CURLOPT_URL, url);
	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, receive_data2);
	curl_easy_setopt(handle, CURLOPT_WRITEDATA, file);
	cout << curl_easy_perform(handle);

	fclose(file);
	curl_easy_cleanup(handle);
	curl_global_cleanup();

	return true;
}

size_t receive_data3(void* buffer, size_t size, size_t nmemb, FILE* file) {
	size_t r_size = fwrite(buffer, size, nmemb, file);
	return r_size;
}
bool curlexample3()
{
	char url[] = "http://www.baidu.com";
	char path[] = "save_file3.txt";
	char pathhead[] = "save_file3_head.txt";
	FILE* file = fopen(path, "w");
	FILE* filehead = fopen(pathhead, "w");
	curl_global_init(CURL_GLOBAL_ALL);
	CURL* handle = curl_easy_init();
	curl_easy_setopt(handle, CURLOPT_URL, url);
	curl_easy_setopt(handle, CURLOPT_HEADERFUNCTION, receive_data3);
	curl_easy_setopt(handle, CURLOPT_HEADERDATA, filehead);
	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, receive_data3);
	curl_easy_setopt(handle, CURLOPT_WRITEDATA, file);
	cout << curl_easy_perform(handle);

	fclose(file);
	curl_easy_cleanup(handle);
	curl_global_cleanup();

	struct curl_slist* headers = NULL;
	headers = curl_slist_append(headers, "Accept: Agent-007");

	return true;
}


