typedef struct { // struktur penyimpanan data
	char id[10];
	char namaProduk[20];
	int kuantitas;
	time_t timeInfo;
} Produk;

void tulisKeFile(Produk realProduk1[]) {
	int i;

	FILE *output;
    output = fopen("data.txt", "w");
    if (output == NULL) {
        printf("Error ketika membuka/membuat file!");
        exit(1);
    }

    for (i = 0; i < 30; i++) {
		if(strcmp(realProduk1[i].id, "")) {
			fwrite(realProduk1 + i, sizeof(Produk), 1, output);
		}
    }

	fclose(output);
}

void bacaDariFile(Produk realProduk1[]) {
	int i;
	FILE *input;
	input = fopen("data.txt", "r");
	if (input == NULL) {
		printf("Error dalam membaca file!");
		printf("\nMembuat file penyimpanan yang baru ...");
		sleep(2);
		system("cls");
		tulisKeFile(realProduk1);
	}
	else {
		for (i = 0; i < 30; i++) {
			fread(realProduk1 + i, sizeof(Produk), 1, input);
		}
	}
	
	fclose(input);
}
