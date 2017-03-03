#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>

#include <unordered_map>
#include <openssl/sha.h>
#include "json.hpp"

using json = nlohmann::json;

using namespace std;

string GetHexRepresentation(const unsigned char * Bytes)
{
    ostringstream os;
    os.fill('0');
    os<<hex;
    for(const unsigned char * ptr=Bytes;ptr<Bytes+SHA_DIGEST_LENGTH;ptr++)
        os<<setw(2)<<(unsigned int)*ptr;

    return os.str();
}

// void writeDisk(files_hashmap s)
// {
//     ofstream output_file("files.dat", ios::binary);
//     output_file.write((char*)&s, sizeof(s));
//     output_file.close();
//
//
//     /*FILE *file = fopen("files.dat", "wb");
//
//     if (!file) {
// 		printf("Unable to open file!");
// 		return;
// 	}
//     fseek(file, 0, SEEK_END);
//
//     fwrite(&s, sizeof(s), 1, file);
//
//     fclose(file);*/
// }

// void loadDisk(files_hashmap s)
// {
//     ifstream input_file("files.dat", ios::binary);
//     input_file.read((char*)&s, sizeof(s));
//
//     /*//char *buffer;
//     long lSize;
//     FILE *file = fopen("files.dat", "rb");
//
//     if (!file) {
// 		printf("Unable to open file!");
// 		return;
// 	}
//     fseek (file , 0 , SEEK_END);
//     lSize = ftell (file);
//     rewind (file);
//
//     //buffer = (char*) malloc (sizeof(char)*lSize);
//     //s = (struct files_hashmap*)malloc(sizeof(struct files_hashmap));
//
//     fread(s, 1, sizeof(s), file);
//     fclose(file); */
// }

string getSHA1(const string& fileName) {
      size_t size_sha1;
      char *data_sha1 = NULL;
      string cks, path = "uthash.h";
      unsigned char check_sum[SHA_DIGEST_LENGTH];
      long sz;
      FILE *f;

      if(!(f = fopen(path.c_str(), "rb"))) {
          fclose(f);
          return string();
      }


      fflush(f);
      fseek(f, 0L, SEEK_END);
      sz = ftell(f);
      fseek(f, 0L, SEEK_SET);

      data_sha1 = (char*) malloc (sizeof(char)*sz);
      size_sha1 = fread(data_sha1, 1, sz, f);

      SHA1((unsigned char *)data_sha1, size_sha1, (unsigned char *)&check_sum);
      free(data_sha1);
      fclose(f);
      cks = GetHexRepresentation(check_sum);

      return cks;
}


int main(int argc, char *argv[]) {

    json locations;
    ifstream locs("locations.json");
    locs >> locations;

    unordered_map<string,string> location;

    string fname("uthash.h");
    string hash = getSHA1(fname);

    location[hash] = fname;

    cout << location.size() << endl;


    //
    //
    //
    //
    //
    // cout << cks.c_str() << endl;
    //
    //
    // //s = (struct files_hashmap*)malloc(sizeof(struct files_hashmap));
    // s = new struct files_hashmap();
    //
    // strncpy(s->checksum, cks.c_str(), SHA_DIGEST_LENGTH*2);
    // string tt=  "123.123.123.123";
    // s->server_address = tt;
    // //HASH_ADD_STR( files, checksum, s );
    // cout << s->checksum << "\naaaa" << endl << s->server_address.c_str() << endl;
    //
    // //writeDisk(*s);
    //
    // /*ofstream output_file("files.dat", ios::binary);
    // output_file.write((char*)s, sizeof(*s));
    // //output_file.write(reinterpret_cast<char*>(s), sizeof(s));
    // output_file.close();*/
    //
    // s = new struct files_hashmap();
    //
    // string t2 = "abcdefghijklmnopqrstuvwxyz12345678910124";
    //
    // strncpy(s->checksum, t2.c_str(), SHA_DIGEST_LENGTH*2);
    // string t3=  "123.123.123.1555";
    // //strncpy(s->server_address, tt.c_str(), 40);
    // s->server_address = t3;
    // HASH_ADD_STR( files, checksum, s );
    // cout << s->checksum << endl << s->server_address.c_str() << endl;
    //
    // ofstream output_file("files.dat", ios::binary);
    // output_file.write((char*)s, sizeof(*s));
    // //output_file.write(reinterpret_cast<char*>(s), sizeof(s));
    // output_file.close();
    //
    //
    // //cks += tt;
    // HASH_FIND_STR( files, cks.c_str(), s);
    // if (s) printf("a.mkv's id is %s\n", s->server_address.c_str());
    // else cout << "\nNot found\n";
    //
    // //writeDisk(s);
    // temp = (struct files_hashmap*)malloc(136);
    // //temp = new struct files_hashmap();
    // //loadDisk(*temp);
    //
    // ifstream input_file("files.dat", ios::binary);
    // //input_file.read((char*)&temp, sizeof(temp));
    // input_file.read(reinterpret_cast<char*>(temp), sizeof(temp));
    // cout << "\nsize " << sizeof(*temp);
    //
    //
    // t2 = "abcdefghijklmnop";
    //
    // //temp = (struct files_hashmap*)temp;
    //
    // HASH_FIND_STR( files, cks.c_str(), temp);
    // if (temp) printf("check_sum's location is %s\n", temp->server_address.c_str());
    // else cout << "\nNot found\n";
    //
    // HASH_ITER(hh, files, temp, tmp) {
    //     HASH_DEL(files, temp);
    //     free(temp);
    // }
    //
    // /* free the hash table contents */
    // HASH_ITER(hh, files, s, tmp) {
    //     HASH_DEL(files, s);
    //     free(s);
    // }
    return 0;
}
