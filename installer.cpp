#include <cstdio>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

using namespace std;

int main() {
	printf("Downloading zip...\n");
	int download_zip = system("wget github.com/dhruva-shashi/coderunner/archive/master.zip");

	if (download_zip) {
		printf("Error occured while downloading zip file\n");
		exit(0);
	}

	printf("Unzipping...\n");
	int unzip = system("unzip master.zip");

	if (unzip) {
		printf("Error occured while unzipping zip file\nInstallation terminated\n");
		system("rm master.zip");
		exit(0);
	}

	printf("Copying files to system...\n");
	int copy_coderunner = system("sudo cp coderunner-master/coderunner /bin");

	if (copy_coderunner) {
		perror("Error occured\nForced to terminate installation\n");
		system("rm master.zip");
		exit(0);
	}

	printf("Coderunner has been successfully installed\n");

	return 0;
}

