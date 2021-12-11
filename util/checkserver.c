#include <stdio.h>
#include <curl/curl.h>


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
	CURL* curl;
	CURLcode res;

	struct File ftpfile = {
		.filename = "newtransaction",
		.stream = NULL
	};

	curl_global_init(CURL_GLOBAL_DEFAULT);

	curl = curl_easy_init();

	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "ftp.guardianhost.org");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, w_fwrite);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ftpfile);
		curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);

		curl_easy_cleanup(curl);

		if (res != CURLE_OK) {
			printf("Error: %d\n", res);
		}


		flose(ftpfile.stream);
	}

	curl curl_global_meo
}
