/*!
	\file
	\brief Текст программы

	Файл содержит тект выполняемой программы
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/blowfish.h>


#define BUFSIZE 1024

/*!
	\brief Поясняющий вывод
*/
void usrGid() {
	printf("sssnike -e||-d -f <fileName> -p <pasWd>\n");
	printf("-e||-d	Encryption||Decription\n");
	printf("-f	File name\n");
	printf("-p	The string on the base of with the password will be created\n");
}

/*!
	\brief Функция зашифрования и расщифрования

	\param in Файловый поток ввода
	\param out Файловый поток вывода
	\param key Ключь шифрования
	\param mode Режим работы 1 - шифрования 0 - расшифровани
*/
void crypt(FILE *in, FILE *out, uint8_t* key, int mode) {
	int num = 0;
	uint8_t inbuf[BUFSIZE], outbuf[BUFSIZE];
	unsigned char iv[8] = {0};
	BF_KEY bfkey;

	BF_set_key(&bfkey, sizeof(key), key);

	for(;;) {
		int inlen = fread(inbuf, 1, BUFSIZE, in);
		if(inlen <= 0) break;
		BF_cfb64_encrypt(inbuf, outbuf, (long)inlen, &bfkey, iv, &num, mode);
		fwrite(outbuf, 1, inlen, out);
	}
}

/*!
	\brief Основаная функция

	\param argc Чсило аргументов
	\param argv Список аргументов
*/
int main (int argc, char* argv[]) {
	uint8_t en = 0;
	uint8_t de = 0;
	char* fileName = NULL;
	char* pasWd = NULL;
	char* opts = "edf:p:";
	int opt;
	while((opt=getopt(argc, argv, opts))!=-1) {
		switch(opt) {
			case 'e':
				en = 1;
				break;
			case 'd':
				de = 1;
				break;
			case 'f':
				fileName = optarg;
				break;
			case 'p':
				pasWd = optarg;
				break;
		}
	}

	if ((en == de) || !(fileName) || !(pasWd)) {
		usrGid();
		exit(1);
	}
	
	char* salt = "saltSALT";
	uint8_t key[16];


	PKCS5_PBKDF2_HMAC_SHA1(pasWd, strlen(pasWd), salt, 8, 1000, 16, key);
	
	if (en == 1) {
		FILE *inFile = fopen(fileName, "rb");
		if (!inFile) {
			printf("Cant open input file!\n");
			fclose(inFile);
			exit(1);
		}
		FILE *outFile = fopen("krypt.out", "wb");
		if (!outFile) {
			printf("Cant create output file!\n");
			fclose(outFile);
			exit(1);
		}
		crypt(inFile, outFile, key, 1);
		fclose(inFile);
		fclose(outFile);
	}
	else if (de == 1) {
		FILE *inFile = fopen(fileName, "rb");
		if (!inFile) {
			printf("Cant open input file!\n");
			fclose(inFile);
			exit(1);
		}
		FILE *outFile = fopen("dekrypt.out", "wb");
		if (!outFile) {
			printf("Cant create output file!\n");
			fclose(outFile);
			exit(1);
		}
		crypt(inFile, outFile, key, 0);
		fclose(inFile);
		fclose(outFile);
	}

	return 0;	
}
