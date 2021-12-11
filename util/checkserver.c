#include <stdio.h>
#include <curl/curl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


struct File {
	const char* filename;
	FILE* stream;
};


size_t m_fwrite(void* buffer, size_t size, size_t nmemb, void* stream) {
	struct File* out = (struct File*)stream;

	if (!(out -> stream)) {
		out -> stream = fopen(out -> filename, "wb");
		if (!(out -> stream)) {
			return -1;
		}  // Failed to open file.
	}

	return fwrite(buffer, size, nmemb, out -> stream);
}


int main(int argc, char* argv[]) {

	if (argc < 4) {
		printf("Usage: %s user password file\n", argv[0]);
		return 0;
	}

	CURL* curl;
	CURLcode res;

	struct File ftpfile = {
		.filename = argv[3],
		.stream = NULL
	};

	curl_global_init(CURL_GLOBAL_DEFAULT);

	curl = curl_easy_init();

	char usrpass[50];
	sprintf(usrpass, "%s:%s", argv[1], argv[2]);

	char fullurl[65];

	if (!(argv[4])) {
		printf("Error, require argument 5.");
		curl_global_cleanup();
		return -1;
	} else {
		sprintf(fullurl, "ftp.guardianhost.org/%s", argv[4]);
	}

	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, fullurl);
		curl_easy_setopt(curl, CURLOPT_USERPWD, usrpass);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, m_fwrite);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ftpfile);
		curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);

		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);

		if (res != CURLE_OK) {
			printf("Error: %d\n", res);
			curl_global_cleanup();
			return 1;
		}


		fclose(ftpfile.stream);
	}

	if (argv[5] == "cat") {
		FILE* fp = fopen(argv[3], "r");
		size_t lineBufSize = 5;
		char* lineBuf = (char*)malloc(sizeof(char) * lineBufSize);

		while (getline(&lineBuf, &lineBufSize, fp) != -1) {
			printf("%s", lineBuf);
		}

		free(lineBuf);
	}

	curl_global_cleanup();
}
