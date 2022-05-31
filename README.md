# Program Inventarisasi dalam C
Program ini bertujuan untuk memudahkan pengguna untuk melakukan inventarisasi aset atau barang secara digital. 
Secara umum, program ini mempunyai fitur untuk menambahkan barang, mengubah jumlah barang yang sudah tersimpan, menampilkan semua barang yang berhasil tersimpan ke dalam inventarisasi, menghapus barang dari inventarisasi, dan mencari barang di dalam inventarisasi.
Karena dalam Proyek Akhir diharuskan untuk mengimplementasikan struktur data Linked List dan Binary Tree, struktur data tersebut akan ditampilkan pada fitur yang sesuai.

### Penjelasan source code
YouTube: https://www.youtube.com/watch?v=hYAY0tgyCF4

### Required: Linked List
Linked List dalam program ini digunakan untuk menyimpan data inventarisasi dan dimasukkan berdasarkan urutan ID barang menurut ASCII. Pengguna dapat menambahkan, menampilkan, mengubah, menghapus, atau mencari barang dengan menggunakan Linked List ini ketika pengguna mengaksesnya melalui menu yang tersedia. Selain mengubah *array of struct* sebagai tempat penyimpanan utama, Linked List juga dapat diubah/diakses melalui menu tersebut.

### Required: Binary Tree
Binary Tree dalam program ini digunakan untuk menyimpan data inventarisasi dan dimasukkan berdasarkan urutan nama barang menurut ASCII. Pengguna dapat menambahkan, menampilkan, mengubah, menghapus, atau mencari barang dengan menggunakan Binary Tree ini ketika pengguna mengaksesnya melalui menu yang tersedia. Selain mengubah *array of struct* sebagai tempat penyimpanan utama, Binary Tree juga dapat diubah/diakses melalui menu tersebut.

## Menambahkan barang
Pengguna akan diminta untuk memasukkan jumlah iterasi (pengulangan) penambahan barang sebelum diminta untuk memasukkan data yang terkait langsung dengan barang yang akan ditambahkan. Pengguna hanya perlu memasukkan beberapa masukan sesuai dengan yang diminta oleh program. Penambahan barang akan muncul pada tabel sebagai representasi *array of struct*, pada Linked List, dan pada Binary Tree.

## Mengubah jumlah barang
Pengguna akan diminta ID barang yang akan diubah. Apabila barang ditemukan di dalam inventarisasi, pengguna dapat memasukkan jumlah barang yang terbaru. Pembaruan jumlah barang ini akan terjadi pada tabel representasi *array of struct*, pada Linked List, dan pada Binary Tree.

## Menampilkan barang dalam inventarisasi
Pengguna akan diminta untuk memilih tampilan pengurutan data. Ada 3 pilihan yang dapat diambil:
1. berdasarkan ID,
2. berdasarkan nama, dan
3. berdasarkan waktu input pertama kali

Tabel akan ditampilkan dengan urutan sesuai dengan pilihan pengguna.
Selanjutnya, pengguna diminta untuk memberikan masukan apakah pengguna ingin melihat struktur Linked List dan Binary Tree atau ingin kembali ke menu utama. Linked List disusun berdasarkan urutan ID, sedangkan Binary Tree disusun berdasarkan urutan nama, sehingga pilihan pengguna sebelumnya **tidak berpengaruh** pada urutan kedua struktur data ini.

## Menghapus barang dari inventarisasi
Pengguna akan diminta untuk memasukkan ID barang yang ingin dihapus. Apabila barang ditemukan, pengguna akan dimintai konfirmasi untuk menghapus barang tersebut dari inventarisasi. Apabila pengguna mengonfirmasi, barang akan dihapus dari inventarisasi serta Linked List dan Binary Tree. Apabila pengguna membatalkan penghapusan, inventarisasi, Linked List, dan Binary Tree tidak akan terpengaruh.

## Mencari barang di dalam inventarisasi
Pengguna akan diminta untuk memasukkan jumlah iterasi (pengulangan) pencarian barang. Setelah itu, pengguna dapat memasukkan nama barang yang ingin dicari. Pencarian ini bersifat *case-senstive* dan mencari *exact match*, sehingga perhatian pengguna sangat diharapkan dalam menggunakan fitur ini. Pencarian pada *array of struct* akan menampilkan **semua** barang dengan nama yang cocok dengan kata kunci pencarian. Sedangkan, pencarian dari Linked List dan Binary Tree hanya dapat menampilkan **barang pertama** yang cocok dengan kata kunci pencarian.
