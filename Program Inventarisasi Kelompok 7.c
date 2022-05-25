#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
#include <conio.h>
#include "prosesFile.h"

/* Structure untuk Linked List */
struct ListNodes {
	Produk barang;
	struct ListNodes *nextPtr;
};
typedef struct ListNodes ListNode;

/* Structure untuk Binary Tree */
struct BinaryTrees {
	Produk barang;
	struct BinaryTrees *leftPtr;
	struct BinaryTrees *rightPtr;
};
typedef struct BinaryTrees BinaryTree;

/* Function prototype */

void tambahBarang(Produk realProduk1[], ListNode **headAddrPtr, BinaryTree **rootAddrPtr);
void ubahBarang(Produk realProduk1[], ListNode **headAddrPtr, BinaryTree **rootAddrPtr);
void bacaBarang(Produk realProduk1[], ListNode **headAddrPtr, BinaryTree **rootAddrPtr);
void hapusBarang(Produk realProduk1[], ListNode **headAddrPtr, BinaryTree **rootAddrPtr);
void searching(Produk realProduk1[], ListNode **headAddrPtr, BinaryTree **rootAddrPtr);
void sorting(Produk *ptrProduk, int total, char pilihan); // kriteria 8
void panduan();
void judul();

/* Linked List */
void tambahKeList(ListNode **hPtr, Produk produk1); // kriteria 9, 10
void hapusDariList(ListNode **hPtr, Produk produk1); // kriteria 11
void updateList(ListNode **hPtr, Produk produk1);
void bacaDariList(ListNode **hPtr, Produk produk1); // kriteria 11
void printList(ListNode *hPtr); // kriteria 6, 8, 11
/* Binary Tree*/
BinaryTree *createBinaryTree(Produk realProduk1[], int front, int back); // kriteria 7
void tambahKeTree(BinaryTree **rPtr, Produk produk1); // kriteria 10
BinaryTree *hapusDariTree(BinaryTree **rPtr, Produk produk1); // kriteria 11
BinaryTree *updateTree(BinaryTree **rPtr, Produk produk1);
void printInOrder(BinaryTree *rPtr); // kriteria 6, 8, 11
BinaryTree *bacaDariTree(BinaryTree **rPtr, Produk produk1); // kriteria 11
void nodeCheck(BinaryTree *rPtr);

/* Main */

int main(){
	Produk realProduk[30];
	char pilihan;
	int i;
	
	for (i = 0; i < 30; i++){ // untuk membersihkan struct sebelum akan dibaca dari file
		strcpy(realProduk[i].id,"");
		strcpy(realProduk[i].namaProduk,"");
		realProduk[i].kuantitas = 0;
	}
	bacaDariFile(realProduk); // menyalin isi dari file menjadi suatu array of struct
	
	/* Inisialisasi Linked List dari array of struct*/
	ListNode *headPtr = NULL;
	for (i = 0; i < 30; i++) {
		if(strcmp(realProduk[i].id, "")) {
			tambahKeList(&headPtr, realProduk[i]);
		}
	}

	/* Inisialisasi Binary Tree dari array of struct dengan terlebih dahulu sorting berdasarkan nama produk */
	for (i = 0; i < 30; i++) {
		if(!strcmp(realProduk[i].id, "")) {
			break;
		}
	}
	sorting(realProduk, i, '2'); // pilihan 2 merupakan pilihan untuk sorting berdasarkan nama
	BinaryTree *rootPtr = createBinaryTree(realProduk, 0, i - 1);

	do {
		judul();
		printf("\nTekan(1/2/3/4/5/6/7)):");
		printf("\n 1.) Menambah barang");
		printf("\n 2.) Menampilkan semua barang");
		printf("\n 3.) Mengubah barang");
		printf("\n 4.) Menghapus barang");
		printf("\n 5.) Mencari barang");
		printf("\n 6.) Panduan");
		printf("\n 7.) Keluar dari program\n");
		printf("\nPilihan Anda --> ");
		
		scanf("%c", &pilihan);
		fflush(stdin);
		switch(pilihan) {
			case '1':
				system("cls");
				judul();
				tambahBarang(realProduk, &headPtr, &rootPtr);
				break;			
			case '2':
				system("cls");
				judul();
        		bacaBarang(realProduk, &headPtr, &rootPtr);
				break;
			case '3':
				system("cls");
				judul();
				ubahBarang(realProduk, &headPtr, &rootPtr);
				break;				
			case '4':
				system("cls");
				judul();
				hapusBarang(realProduk, &headPtr, &rootPtr);
				break;			
			case '5':
				system("cls");
				judul();
				searching(realProduk, &headPtr, &rootPtr);
				break;
			case '6':
				judul();
				system("cls");
				panduan();
				break;
			case '7':
				printf("Terima kasih sudah menggunakan program ini!\n");
				sleep(2);
				break;
			case '\n':
				system("cls");
				break;
			default:
				printf("Pastikan input Anda sudah benar!\nMengembalikan Anda ke menu utama...");
				sleep(1);
				system("cls");
				break;
		}
	}
	while (pilihan != '7');

	// free List dan Tree sebelum termination program
	for (i = 0; i < 30; i++) {
		if(strcmp(realProduk[i].id, "")) {
			hapusDariList(&headPtr, realProduk[i]);
			hapusDariTree(&rootPtr, realProduk[i]);
		}
	}
	
	return 0;
}

/* Section CRUD (create, read, update, delete) */

void tambahBarang(Produk realProduk1[], ListNode **headAddrPtr, BinaryTree **rootAddrPtr) {
	int i = 0, j, x;
	int sentinel;
	
	do {
		system("cls");
		judul();
		printf("\nBerapa produk yang ingin anda tambahkan?\n-> ");
		scanf(" %d", &sentinel);

		if (sentinel <= 0){
			printf("Pastikan input Anda sudah benar!");
			printf("\n\nTekan Enter untuk kembali ke main menu!\n");	
			getch();
			system("cls");
		}
	} while (sentinel <= 0);

	printf("=======================================\n");
	for (x = 0; x < 30; x++){
		if (!strcmp(realProduk1[x].id,"")){
			for (i = x; i < x + sentinel; i++){
				printf("Masukkan kode produk ke-%d: ", i+1);
				scanf(" %255[^\n]s", realProduk1[i].id);
				fflush(stdin);
				
				//cek apakah kode produk sudah ada
				for (j = 0; j < 30; j++) {
					if (j != i) {
						if(!strcmp(realProduk1[i].id, realProduk1[j].id)) { // searching dan cek apakah barang sudah ada
							strcpy(realProduk1[i].id, "");
							printf("Kode produk sudah ada! Silakan menggunakan menu ubah produk!\n");
							printf("\nTekan Enter untuk kembali ke main menu!");
							getch();
							system("cls");
							return; // ingin keluar, tetapi karena void, return nothing
						}
					}
				}
				
				printf("Masukkan nama produk ke-%d: ", i+1);
				scanf(" %255[^\n]s", realProduk1[i].namaProduk);
				fflush(stdin);
				printf("Masukkan jumlah produk yang ingin dimasukkan: ");
				scanf("%d", &realProduk1[i].kuantitas);
				
				time_t currenttime;
				time(&currenttime);
				realProduk1[i].timeInfo = currenttime;
				printf("=======================================\n");

				tambahKeList(headAddrPtr, realProduk1[i]);
				tambahKeTree(rootAddrPtr, realProduk1[i]);
			}
			break;
		}
	}
	tulisKeFile(realProduk1);
	printf("Menunggu...\n");
	sleep(2);
	system("cls");
}

void bacaBarang(Produk realProduk1[], ListNode **headAddrPtr, BinaryTree **rootAddrPtr) {
	int i, last_index;
	char pilihan;
	
	system("cls");
	printf("Silakan memilih tampilan berdasarkan:");
	printf("\n 1.) Sort by ID");
	printf("\n 2.) Sort by Name");
	printf("\n 3.) Sort by Timestamp");
	printf("\nPilihan Anda --> ");
	scanf("%c", &pilihan);
	system("cls");
	fflush(stdin);

	for (i = 0; i < 30; i++) {
		if(!strcmp(realProduk1[i].id, "")) {
			last_index = i;
			break;
		}
	}

	sorting(realProduk1, last_index, pilihan);
	
	printf("----------------------------------------------------------------------------------\n");
	printf("                                  Inventarisasi  \n");
    printf("----------------------------------------------------------------------------------\n");
    printf("No. |   Kode   |    Nama Barang    |  Jumlah Barang  |         Timestamp         |\n");
    printf("----------------------------------------------------------------------------------\n");
	for (i = 0; i < last_index; i++){
		printf("%-5d", i+1);
		printf("%-11s", realProduk1[i].id);
		printf("%-22s", realProduk1[i].namaProduk);
		printf("%-17d", realProduk1[i].kuantitas);
		printf("%-s\n", asctime(localtime(&(realProduk1[i].timeInfo))));
	}
		
		printf("\nTekan:\n1. Details\n2. Main Menu\n");
		printf("\nPilihan Anda --> ");
		scanf("%c", &pilihan);
		fflush(stdin);
		switch(pilihan){			
				case '1':
			system("cls");
	printf("----------------------------------------------------------------------------------\n");
	printf("Tampilan Linked List (urutan berdasarkan ID):\n");
	printList(*headAddrPtr); // print Linked List (debug)
	printf("\n");
	printf("Tampilan Binary Tree (urutan berdasarkan nama, dalam urutan in-order): \n\n");
	printInOrder(*rootAddrPtr); // print Binary Tree (debug)
	printf("\n");
	printf("----------------------------------------------------------------------------------\n");
	printf("Rincian dari Binary Tree:\n");
	nodeCheck(*rootAddrPtr); //checking the binary tree
	printf("\n");
	printf("----------------------------------------------------------------------------------\n");
	printf("Tekan Enter untuk kembali ke main menu!");
	getch();
	system("cls");
				break;			
			case '2':
				system("cls");
				break;
			default:
				printf("Pastikan input Anda sudah benar!\n");
				sleep(1);
				system("cls");
				break;
		}

				

}

void ubahBarang(Produk realProduk1[], ListNode **headAddrPtr, BinaryTree **rootAddrPtr) {
	int i, jumlah;
	char kode[10], pilihan;

	printf("\nSilakan masukkan kode/ID barang yang ingin diupdate: ");
	scanf(" %9s", kode);
	fflush(stdin);

	for (i = 0; i < 30; i++) {
		if (!strcmp(kode, realProduk1[i].id)) {
			printf("Barang ditemukan!\n->");
			printf("Masukkan jumlah barang yang terbaru: ");
			scanf("%d", &jumlah);
			do {
				fflush(stdin);
				system("cls");
				printf("Anda yakin dengan perubahan ini:\n");
				printf("--------------------------------------------------\n");
				printf("                 Inventarisasi  \n");
   				printf("--------------------------------------------------\n");
    			printf("|   Kode   |    Nama Barang    |  Jumlah Barang  |\n");
    			printf("--------------------------------------------------\n");
    			printf("   %-11s", realProduk1[i].id);
				printf("  %-22s", realProduk1[i].namaProduk);
				printf(" %-17d\n", jumlah);
				printf("\n(Y untuk ya, n untuk tidak)\n");
				fflush(stdin);
				scanf("%c", &pilihan);
				pilihan = tolower(pilihan); // agar tidak case-sensitive
				if (pilihan == 'y') {
					realProduk1[i].kuantitas = jumlah;
					updateList(headAddrPtr, realProduk1[i]);
					updateTree(rootAddrPtr, realProduk1[i]);
					printf("Perubahan berhasil dilakukan!\n");
				}
				else if (pilihan == 'n') {
					printf("Perubahan dibatalkan!");
				}
				else {
					pilihan = 'e';
					printf("Pastikan input Anda sudah benar!");
				}
			} while (pilihan == 'e');
			break;
		}
	}
		if (i == 30) { // apabila sampai index akhir tidak ditemukan, return pesan error
		printf("Barang dengan kode %s tidak ditemukan!", kode);
	}
	tulisKeFile(realProduk1);
	printf("\nTekan Enter untuk kembali ke main menu!");
	getch();
	system("cls");
}

void hapusBarang(Produk realProduk1[], ListNode **headAddrPtr, BinaryTree **rootAddrPtr) {
	char kode[10], pilihan;
	int i, j;

	strcpy(kode, "");
	printf("\nSilakan masukkan kode/ID barang yang ingin dihapus: ");
	scanf("%s", kode);
	fflush(stdin);

	//sequential searching, menyocokkan kode input dengan ID target
	for (i = 0; i < 30; i++) {
		if (!strcmp(kode, realProduk1[i].id)) {
			printf("Barang ditemukan!\n");
			printf("Anda yakin ingin menghapus barang dari database?\n");
			printf("--------------------------------------------------\n");
			printf("                 Inventarisasi  \n");
   			printf("--------------------------------------------------\n");
    		printf("|   Kode   |    Nama Barang    |  Jumlah Barang  |\n");
    		printf("--------------------------------------------------\n");
    		printf("   %-11s", realProduk1[i].id);
			printf("  %-22s", realProduk1[i].namaProduk);
			printf(" %-17d\n", realProduk1[i].kuantitas);
			printf("\n(Y untuk ya, n untuk tidak)\n");
			scanf("%c", &pilihan);
			pilihan = tolower(pilihan); // agar tidak case-sensitive
			do {
				if (pilihan == 'y') {
					hapusDariList(headAddrPtr, realProduk1[i]);
					hapusDariTree(rootAddrPtr, realProduk1[i]);
					for (j = i; j < 29; j++) { // 29 karena 30-1 (1 merupakan item yang dihapus dari database)
						realProduk1[j] = realProduk1[j+1]; // produk di index i akan direplace oleh produk di index setelahnya, sehingga tidak ada yang "bolong" dalam database
					}
					printf("Barang dengan kode %s telah dihapus dari database.\n", kode);
				}
				else if (pilihan = 'n') {
					printf("Tidak ada barang yang dihapus!");
				}
				else {
					pilihan = 'e';
					printf("Pastikan input Anda sudah benar!");
				}
			} while (pilihan == 'e');
			break;
		}
	}
	
	if (i == 30) { // apabila sampai index akhir tidak ditemukan, return pesan error
		printf("Barang dengan kode %s tidak ditemukan!", kode);
	}
	tulisKeFile(realProduk1);
	printf("\nTekan Enter untuk kembali ke main menu!");
	getch();
	system("cls");
}

/* Section searching and sorting */

void searching(Produk realProduk1[], ListNode **headAddrPtr, BinaryTree **rootAddrPtr) {
	int i, j, banyak, ditemukan = 0; //ditemukan untuk memberi flag bahwa ada setidaknya satu barang yang berhasil ditemukan
	
	printf("Berapa banyak pencarian barang yang ingin Anda lakukan?\n->");
	scanf("%d", &banyak);
	system("cls");
	judul();

	char nama[banyak][20];

	for (i = 0; i < banyak; i++) {
		printf("\n--------------------------------------------------\n");
		printf("Silakan masukkan nama barang yang ingin Anda cari: ");
		scanf(" %19[^\n]s\n", nama[i]);
		system("cls");
		for (j = 0; j < 30; j++) {
			if(!strcmp(nama[i], realProduk1[j].namaProduk)) {
				ditemukan = 1;
				printf("Barang ditemukan!\n");
				printf("--------------------------------------------------\n");
				printf("                 Inventarisasi  \n");
   				printf("--------------------------------------------------\n");
    			printf("|   Kode   |    Nama Barang    |  Jumlah Barang  |\n");
    			printf("--------------------------------------------------\n");
    			printf("   %-11s", realProduk1[j].id);
				printf("  %-22s", realProduk1[j].namaProduk);
				printf(" %-17d\n", realProduk1[j].kuantitas);
				printf("--------------------------------------------------\n");
				printf("| Dari List |-------------------->"); // debug
				bacaDariList(headAddrPtr, realProduk1[j]); // debug
				
				BinaryTree *nodeHasil = bacaDariTree(rootAddrPtr, realProduk1[j]);
				Produk hasil = nodeHasil -> barang;
				printf("\n| Dari Tree |-------------------->|%s, %s, %d|\n", hasil.id, hasil.namaProduk, hasil.kuantitas); 
				printf("--------------------------------------------------\n");// debug
			}
		}

		if (!ditemukan) {
			printf("Barang tidak ditemukan!\n");
		}
	}

	printf("\nTekan Enter untuk kembali ke main menu!");
	getch();
	system("cls");
}

void sorting (Produk *ptrProduk, int total, char pilihan) { // sorting dengan algoritma Bubble Sort rekursif
    int i, j, pertukaran = 0; // pertukaran sebagai flag/tanda bahwa tidak ada pertukaran yang terjadi, sehingga sort dapat diakhiri lebih awal
	Produk temp;
	
	if (total == 1)
		return;
	
	switch(pilihan) {
		case '1': // sort by ID 
			for (i = 0; i < total - 1; i++) {
				for (j = 0; j < total - i - 1; j++) {
					if (strcmp((ptrProduk + j)->id, (ptrProduk + j + 1)->id) > 0) {
						pertukaran = 1; // memberi tanda bahwa terjadi pertukaran, dan rekursi berikutnya harus dijalankan      
						temp = *(ptrProduk + j);
						*(ptrProduk + j) = *(ptrProduk + j + 1);
						*(ptrProduk + j + 1) = temp;
					}
				}
			}
			break;
			
		case '2': // sort by name 
			for (i = 0; i < total - 1; i++) {
				for (j = 0; j < total - i - 1; j++) {
					if (strcmp((ptrProduk + j)->namaProduk, (ptrProduk + j + 1)->namaProduk) > 0) {       
						pertukaran = 1; // memberi tanda bahwa terjadi pertukaran, dan rekursi berikutnya harus dijalankan
						temp = *(ptrProduk + j);
						*(ptrProduk + j) = *(ptrProduk + j + 1);
						*(ptrProduk + j + 1) = temp;
					}
				}
			}
			break;

		case '3': // sort by time
			for (i = 0; i < total - 1; i++) {
				for (j = 0; j < total - i - 1; j++) {
					if ((ptrProduk + j)->timeInfo > (ptrProduk + j + 1)->timeInfo) {
						pertukaran = 1; // memberi tanda bahwa terjadi pertukaran, dan rekursi berikutnya harus dijalankan       
						temp = *(ptrProduk + j);
						*(ptrProduk + j) = *(ptrProduk + j + 1);
						*(ptrProduk + j + 1) = temp;
					}
				}
			}
			break;

		default:
			printf("Input yang Anda masukkan tidak sesuai!\n");
			printf("Menampilkan data dengan urutan sesuai dengan penyimpanan (default)...\n\n");
		break;
	}

	/* Apabila ternyata terjadi pertukaran di dalam fungsi ini, rekursi harus dijalankan kembali.
	Akan tetapi, apabila ternyata nilai pertukaran berhasil tetap bernilai 0 hingga titik ini,
	itu tandanya tidak perlu dilakukan rekursi yang selanjutnya*/
	if (pertukaran)
    	sorting(ptrProduk, total - 1, pilihan);
}

void panduan() {
	system("cls");
	printf("\nMenambah Barang\t\t: \n->Menambahkan barang ke dalam database program dengan menginput kode barang, nama dan kuantitas yang akan disimpan dengan timestampnya masing masing.");
	printf("\n-->Berapa tipe produk yang ingin anda tambahkan? = Berapa kali user ingin menginput barang ke dalam database.");
	printf("\n-->Masukkan kode produk ke-n = Masukkan kode barang yang sesuai dengan barang ingin diinput.");
	printf("\n-->Masukkan nama produk = Masukkan nama barang yang sesuai dengan kode barang yang telah diinput sebelumnya.");
	printf("\n\nTampilan semua barang \t: \n->Menampilkan deskripsi barang di dalam tabel.");	
	printf("\n\nMenghapus barang\t: \n->Menghapus sebuah barang dari database dengan memilihnya dengan kode barang tersebut.");
	printf("\n-->Penghapusan barang yang telah dilakukan tidak dapat dibatalkan atau dikembalikan.");		
	printf("\n\nMengubah barang\t\t: \n->Mengubah sebuah barang dari database dengan memilihnya dengan kode barang tersebut.");
	printf("\n-->Pengubahan barang yang telah dilakukan tidak dapat dibatalkan atau dikembalikan.");	
	printf("\n\nExit the program\t: \n->Keluar dari Program\n\n");
	printf("Kelompok 7:\n");
	printf("Bryan Indarto Giovanni Firjatulloh - 2006531996\n");
	printf("Muhammad Billal Pizzaro Abdillahpietra - 2006466006\n");
	printf("Vincentius Adrian Abimanyu Wibowo Samudro - 2006466366\n");
	printf("\nTekan Enter untuk kembali ke main menu!\n");	
	getch();
	system("cls");	
}

void judul(){
	printf("=======================================\n");
	printf("      	Program Inventarisasi\n");
	printf("=======================================\n");
}

/* Fungsi tambahan (PROYEK II) */
/* Linked List */

void tambahKeList(ListNode **hPtr, Produk produk1) {
	ListNode *newPtr = NULL, *prevPtr = NULL, *currPtr = NULL; // agar tidak floating, di-assign dengan NULL saja
	newPtr = malloc(sizeof(ListNode));

	// apabila memori berhasil dialokasikan
	if (newPtr != NULL) {
		newPtr -> barang = produk1;
		newPtr -> nextPtr = NULL;
		
		// inisialisasi untuk mencari lokasi. prevPtr tidak perlu di-assign lagi karena sebelumnya sudah di-assign NULL
		currPtr = *hPtr;
		
		// proses mencari letak yang tepat
		while (currPtr != NULL && strcmp(produk1.id, (currPtr -> barang).id) > 0) {
			prevPtr = currPtr;
			currPtr = currPtr -> nextPtr;
		}

		// apabila node harus diletakkan sebelum head pointer ataupun list masih dalam keadaan kosong (dengan kata lain, while di atas tidak sempat berjalan)
		if (prevPtr == NULL) {
			newPtr -> nextPtr = *hPtr;
			*hPtr = newPtr;
		}

		else {
			prevPtr -> nextPtr = newPtr;
			newPtr -> nextPtr = currPtr;
		}
	}

	else {
		printf("\n[GAGAL] Tidak dapat mengalokasikan memori!\n");
	}
}

void hapusDariList(ListNode **hPtr, Produk produk1) {
	ListNode *tempPtr = NULL, *prevPtr = NULL, *currPtr = NULL; // agar tidak floating, di-assign dengan NULL saja

	// apabila match dengan data pertama
	if (!strcmp(produk1.id, ((*hPtr) -> barang).id)) {
		tempPtr = *hPtr;
		*hPtr = (*hPtr) -> nextPtr;
		free(tempPtr);
	}
	else {
		prevPtr = *hPtr;
		currPtr = (*hPtr) -> nextPtr;

		// mencari node tujuan
		while (currPtr != NULL && strcmp(produk1.id, (currPtr -> barang).id)) {
			prevPtr = currPtr;
			currPtr = currPtr -> nextPtr;
		}

		if (currPtr != NULL) {
			tempPtr = currPtr;
			prevPtr -> nextPtr = currPtr -> nextPtr;
			free(tempPtr);
		}
	}
}

void updateList(ListNode **hPtr, Produk produk1) {
	ListNode *prevPtr = NULL, *currPtr = NULL; // agar tidak floating, di-assign dengan NULL saja

	// apabila match dengan data pertama
	if (!strcmp(produk1.id, ((*hPtr) -> barang).id)) {
		((*hPtr) -> barang).kuantitas = produk1.kuantitas;
	}
	else {
		prevPtr = *hPtr;
		currPtr = (*hPtr) -> nextPtr;

		// mencari node tujuan
		while (currPtr != NULL && strcmp(produk1.id, (currPtr -> barang).id)) {
			prevPtr = currPtr;
			currPtr = currPtr -> nextPtr;
		}

		if (currPtr != NULL) {
			(currPtr -> barang).kuantitas = produk1.kuantitas;
		}
	}
}

void bacaDariList(ListNode **hPtr, Produk produk1) {
	ListNode *prevPtr = NULL, *currPtr = NULL; // agar tidak floating, di-assign dengan NULL saja

	// apabila match dengan data pertama
	if (!strcmp(produk1.id, ((*hPtr) -> barang).id)) {
		printf("|%s, %s, %d|", ((*hPtr) -> barang).id, ((*hPtr) -> barang).namaProduk, ((*hPtr) -> barang).kuantitas); // debug
	}
	else {
		prevPtr = *hPtr;
		currPtr = (*hPtr) -> nextPtr;

		// mencari node tujuan
		while (currPtr != NULL && strcmp(produk1.id, (currPtr -> barang).id)) {
			prevPtr = currPtr;
			currPtr = currPtr -> nextPtr;
		}

		if (currPtr != NULL) {
			printf("|%s, %s, %d|", (currPtr -> barang).id, (currPtr -> barang).namaProduk, (currPtr -> barang).kuantitas); // debug
		}
	}
}

// untuk keperluan debug saja, yang ditampilkan bisa diubah-ubah sesuai keperluan debug
void printList(ListNode *hPtr) {
	printf("\n");
	if (hPtr == NULL) {
		printf("Empty");
	}
	else {
		while (hPtr != NULL) {
			printf("|%s:%s:%d|\n   |\n   |\n   -->", (hPtr -> barang).id, (hPtr -> barang).namaProduk, (hPtr -> barang).kuantitas);
			hPtr = hPtr -> nextPtr;
		}
		printf("NULL");
	}
	printf("\n");
}

/* Binary Tree */

BinaryTree *createBinaryTree(Produk realProduk1[], int front, int back) {
	/* Fungsi ini dikhususkan untuk membentuk tree saat pertama kali agar balanced.
	Fungsi ini bekerja secara rekursif, dengan pertama kali mengambil pertengahan array.
	Setelah pertengahan array diambil, akan terbentuk dua array berbeda di sebelah kiri dan kanan.
	Dari array kiri dan kanan ini akan dibentuk kembali menjadi tree dengan mengambil masing2 pertengahannya, dan begitu
	seterusnya hingga seluruh elemen array terbentuk menjadi tree. */

	// base case
	if (front > back) {
		return NULL;
	}
	
	int mid = (front + back)/2;
	BinaryTree *root = malloc(sizeof(BinaryTree));
	root -> barang = realProduk1[mid];
	// membentuk sisi kiri tree secara rekursif
	root -> leftPtr = createBinaryTree(realProduk1, front, mid - 1);
	// membentuk sisi kanan tree secara rekursif
	root -> rightPtr = createBinaryTree(realProduk1, mid + 1, back);
	
	return root;
}

void tambahKeTree(BinaryTree **rPtr, Produk produk1) {
	if (*rPtr == NULL) {
		*rPtr = malloc(sizeof(BinaryTree));

		if (*rPtr != NULL) {
			(*rPtr) -> barang = produk1;
			(*rPtr) -> leftPtr = NULL;
			(*rPtr) -> rightPtr = NULL;
		}
		else {
			printf("[GAGAL] Tidak berhasil mengalokasikan memori!");
		}
	}
	
	else {
		if (strcmp(produk1.namaProduk, ((*rPtr) -> barang).namaProduk) < 0) {
			tambahKeTree(&((*rPtr) -> leftPtr), produk1);
		}
		else {
			// nama yang duplikat tidak masalah, karena ID sudah dapat dipastikan berbeda dalam fungsi utamanya
			tambahKeTree(&((*rPtr) -> rightPtr), produk1);
		}
	}
}

BinaryTree *hapusDariTree(BinaryTree **rPtr, Produk produk1) {
	BinaryTree *tempPtr = NULL;
	
	// base case
	if (*rPtr == NULL) {
		return *rPtr;
	}

	// apabila input nama produk lebih kecil secara alfabetik
	if (strcmp(produk1.namaProduk, ((*rPtr) -> barang).namaProduk) < 0) {
		(*rPtr) -> leftPtr = hapusDariTree(&((*rPtr) -> leftPtr), produk1);
	}
	// apabila input nama produk sama dengan atau lebih besar secara alfabetik
	else {
		// apabila ID cocok, lanjutkan untuk menghapus
		if (!strcmp(produk1.id, ((*rPtr) -> barang).id)) {
			// apabila node mempunyai 0 atau 1 child di sebelah kanan
			if ((*rPtr) -> leftPtr == NULL) {
				tempPtr = (*rPtr) -> rightPtr;
				free(*rPtr);
				return tempPtr;
			}
			// apabila node mempunyai 0 atau 1 child di sebelah kiri
			else if ((*rPtr) -> rightPtr == NULL) {
				tempPtr = (*rPtr) -> leftPtr;
				free(*rPtr);
				return tempPtr;
			}
			// apabila node mempunyai child di sebelah kiri dan kanan
			else {
				tempPtr = (*rPtr) -> rightPtr;
				while (tempPtr != NULL && tempPtr -> leftPtr != NULL) {
					tempPtr = tempPtr -> leftPtr;
				}
				(*rPtr) -> barang = tempPtr -> barang;
				(*rPtr) -> rightPtr = hapusDariTree(&((*rPtr) -> rightPtr), tempPtr -> barang);
			}
		}
		// apabila ID tidak cocok, lanjutkan pencarian hingga ID sama
		else {
			(*rPtr) -> rightPtr = hapusDariTree(&((*rPtr) -> rightPtr), produk1);
		}
	}
	return *rPtr;
}

BinaryTree *updateTree(BinaryTree **rPtr, Produk produk1) {
	// base case
	if (*rPtr == NULL) {
		return *rPtr;
	}
	// apabila di node pertama
	else if (!strcmp(produk1.id, ((*rPtr) -> barang).id)) {
		((*rPtr) -> barang).kuantitas = produk1.kuantitas;
		return *rPtr;
	}
	// apabila di sebelah kiri (lebih kecil)
	else if (strcmp(produk1.namaProduk, ((*rPtr) -> barang).namaProduk) < 0) {
		return updateTree(&((*rPtr) -> leftPtr), produk1);
	}
	// apabila di sebelah kanan (lebih besar)
	else {
		return updateTree(&((*rPtr) -> rightPtr), produk1);
	}
}

BinaryTree *bacaDariTree(BinaryTree **rPtr, Produk produk1) {
	// base case
	if (*rPtr == NULL || !strcmp(produk1.id, ((*rPtr) -> barang).id)) {
		return *rPtr;
	}
	// apabila di sebelah kiri (lebih kecil)
	else if (strcmp(produk1.namaProduk, ((*rPtr) -> barang).namaProduk) < 0) {
		return bacaDariTree(&((*rPtr) -> leftPtr), produk1);
	}
	// apabila di sebelah kanan (lebih besar)
	else {
		return bacaDariTree(&((*rPtr) -> rightPtr), produk1);
	}
}

void printInOrder(BinaryTree *rPtr) {
	if (rPtr != NULL) {
		printInOrder(rPtr -> leftPtr);
		printf("|%s:%s:%d|\n   |\n   |\n   -->", (rPtr -> barang).id, (rPtr -> barang).namaProduk, (rPtr -> barang).kuantitas);
		printInOrder(rPtr -> rightPtr); 
	}
}

void nodeCheck(BinaryTree *rPtr){
	char spacing[50]=" ";
	
	if (rPtr == NULL){
		return;
	}
	
	else{
		printf("|%-7s:%-6s:%-3d|: ", (rPtr -> barang).id, (rPtr -> barang).namaProduk, (rPtr -> barang).kuantitas);
		
		if(rPtr->leftPtr != NULL){
			printf("\t--left |%-7s:%-6s:%-3d| ", (rPtr -> leftPtr -> barang).id, (rPtr -> leftPtr -> barang).namaProduk, (rPtr -> leftPtr -> barang).kuantitas);
		}
		
		else if(rPtr->leftPtr == NULL){
			printf("\t--left %-5sNULL%-10s",spacing, spacing);
		}
		
		if(rPtr->rightPtr != NULL){
			printf("\t--right |%-7s:%-6s:%-3d| ", (rPtr -> rightPtr -> barang).id, (rPtr -> rightPtr -> barang).namaProduk, (rPtr -> rightPtr -> barang).kuantitas);
		}
		
		else if(rPtr->rightPtr == NULL){
			printf("\t--right NULL");
		}
	
		printf("\n");
	
		nodeCheck(rPtr->leftPtr);
		nodeCheck(rPtr->rightPtr);
	}
}
