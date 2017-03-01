#include <string> 
#include <stdlib.h>
#include <stdio.h>
#include "uthash.h"


#include <openssl/sha.h>

using namespace std;

struct files_hashmap {
    unsigned char *checksum;	/* key (string is WITHIN the structure) */
    string server_address;
    UT_hash_handle hh;			/* makes this structure hashable */
};

void writeDisk(files_hashmap *s)
{
    FILE *file = fopen("files.dat", "wb");

    if (!file) {
		printf("Unable to open file!");
		return;
	}

    fwrite(&s, sizeof(s), 1, file);

    fclose(file);
}

void loadDisk(files_hashmap *s)
{
    FILE *file = fopen("files.dat", "rb");

    if (!file) {
		printf("Unable to open file!");
		return;
	}
    fread(&s, sizeof(s), 1, file);
    fclose(file);       
}

int main(int argc, char *argv[]) {

	//unsigned char *cs[] = reinterpret_cast<const unsigned char *>( { "joe", "bob", "betty", NULL } );


	size_t size, total, size_sha1;
	char * data, *data_sha1 = NULL;
	string check_sum[SHA_DIGEST_LENGTH];
	long sz;
	FILE * f;

	if(!(f = fopen("uthash", "rb"))) {
		return 0;
	}

	fflush(f);
	fseek(f, 0L, SEEK_END);
	sz = ftell(f);
	fseek(f, 0L, SEEK_SET);

	data_sha1 = (char*) malloc (sizeof(char)*sz);
	size_sha1 = fread(data_sha1, 1, sz, f);

	SHA1((unsigned char *)data_sha1, size_sha1, (string *)&check_sum);
	free(data_sha1);

    const char **n; //, *names[] = { "joe", "bob", "betty", NULL };
    struct files_hashmap *s, *tmp, *files = NULL, *temp;
    int i=0;

    //for (n = cs; *n != NULL; n++) {
        s = (struct files_hashmap*)malloc(sizeof(struct files_hashmap));
        strncpy((const char*)s->checksum, check_sum, sizeof(check_sum));
        s->server_address = "123.123.123.123";
        //HASH_ADD_STR( files, checksum, s );
        HASH_ADD_KEYPTR( hh, files, s->checksum, strlen((const char*)s->checksum), s );
    //}

    HASH_FIND_STR( files, check_sum, s);
    if (s) printf("check_sum's location is %s\n", s->server_address);

    writeDisk(s);
    temp = (struct files_hashmap*)malloc(sizeof(struct files_hashmap));
    loadDisk(temp);

    HASH_FIND_STR( files, "betty", temp);
    if (temp) printf("check_sum's location is %s\n", temp->server_address);


    /* free the hash table contents */
    HASH_ITER(hh, files, s, tmp) {
		HASH_DEL(files, s);
		free(s);
    }

    HASH_ITER(hh, files, temp, tmp) {
		HASH_DEL(files, temp);
		free(temp);
    }
    return 0;
}