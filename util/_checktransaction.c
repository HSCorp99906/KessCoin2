#include <stdio.h>
#include <curl/curl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>

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


void die() {
	curl_global_cleanup();
	exit(0);
}


int main(int argc, char* argv[]) {
	CURL* curl;
	CURLcode res;

	signal(SIGINT, die);
		
	if (argc < 3) {
		printf("Usage: %s <username> <password>\n", argv[0]);
		return 0;
	}

	struct File ftpfile = {
		.filename = "newtransaction",
		.stream = NULL
	};

	char usrpass[50];
	sprintf(usrpass, "%s:%s", argv[1], argv[2]);

	curl_global_init(CURL_GLOBAL_DEFAULT);

	curl = curl_easy_init();

	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "ftp://ftp.guardianhost.org/domains/kesscoin.com/public_html/newtransaction");
		curl_easy_setopt(curl, CURLOPT_USERPWD, usrpass);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, m_fwrite);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ftpfile);
		curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);

		while (true) {
			res = curl_easy_perform(curl);

			if (res != CURLE_REMOTE_FILE_NOT_FOUND) {

				system(">> data.json");

				FILE* fp = fopen("data.json", "w");

				char json[200];


				time_t tm;
				time(&tm);
				char* time = ctime(&tm);

				sprintf(json, "{\n"
							   "    \"username\": \"__TRANSACTION_ALERT__\",\n"
							   "    \"content\": \"Transaction Made On %s. Checking Blockchain..\"\n"
							  "}\n", time);

				fputs(json, fp);
				fclose(fp);

				system("curl -d @data.json -H 'Content-Type: application/json' WEBHOOK URL");
				system("rm data.json");
				system("wget -qO- kesscoin.com/newtransaction >> newtransaction");

				system("bash sign.sh newtransaction");
				system("mv sha1.sign sigs/sha1.sign");
				char cmd[300];
				sprintf(cmd, "curl -T sigs/sha1.sign ftp://%s@ftp.server/secretpath/sha1.sign", usrpass);
				system(cmd);
				sprintf(cmd, "curl -T newtransaction ftp://%s@ftp.server/secretpath/sha1.sign", usrpass);
				system(cmd);
				sleep(1);
				system("mv newtransaction ../core/info");
			}

			sleep(10);
		}
	}

	curl_global_cleanup();
}
