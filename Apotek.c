#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char username[50];
char password[50];
char kodeAdmin[50];

typedef struct {
	char kodeAdmin[50];
	char nama[50];
	char username[50];
	char password[50];
}Admin;

typedef struct {
	char idObat[50];
	char namaObat[50];
	int nomorRak;
	int stok;
	int harga;
	int tanggalProduksi;
	int tanggalKadaluarsa;
}Obat;

typedef struct {
	char idSupplier[50];
	char namaSupplier[50];
	int nomorHpSupplier;
	char kotaSupplier[50];
}Supplier;

typedef struct {
	char idCustomer[50];
	char namaCustomer[50];
	int nomorHpCustomer;
	char kotaCustomer[50];
}Customer;

typedef struct {
	int nomorTransaksi;
	char namaCustomer[50];
	char namaObat[50];
	int jumlahObat;
	int totalBayar;
	int tanggalTransaksi;
}Penjualan;

typedef struct {
	int nomorTransaksi;
	char namaSupplier[50];
	char namaObat[50];
	int jumlahObat;
	int totalHarga;
	int tanggalTransaksi;
}Pembelian;

Admin tambah;
Obat tambahObat;
Obat editObat;
Supplier tambahSupplier;
Supplier editSupplier;

void header();

void login();
void signup();

void menuUtama();

void manajemenData();

void kelolaDataObat();
void menambahkanDataObat();
void menampilkanDataObat();
void mengeditDataObat();
void menghapusDataObat();

void kelolaDataSupplier();
void menambahkanDataSupplier();
void menampilkanDataSupplier();
void mengeditDataSupplier();
void menghapusDataSupplier();

void kelolaDataCustomer();
void menambahkanDataCustomer();
void menampilkanDataCustomer();
void mengeditDataCustomer();
void menghapusDataCustomer();

void transaksiPenjualan();

void membuatPenjualan();
void melihatPenjualan();

void transaksiPembelian();

void membuatPembelian();
void melihatPembelian();

void pencarianData();

void cariObat();
void cariCustomer();
void cariSupplier();

void laporanTransaksi();

void laporanPenjualan();
void laporanPembelian();

int main() {
	int menu;

	system("COLOR A");
	header();

	menu:
	printf("\tHarap Login Terlebih Dahulu!\n");
	printf("\t1. Sudah Punya Akun\n");
	printf("\t2. Belum Punya Akun\n");
	printf("\tSilahkan Pilih (1/2): ");
	scanf("%d", &menu);
	switch (menu) {
	case 1:
		login();
		break;
	case 2:
		signup();
		break;
	default:
		printf("\tAnda Salah Memilih Menu!\n");
		printf("=================================================================================================\n");
		goto menu;
	}

	return 0;
}

void header() {
	printf("\n=================================================================================================\n");
	printf("\n\t\tSELAMAT DATANG DI SISTEM PENGELOLAAN APOTEK\n");
	printf("\n=================================================================================================\n");
}

void login() {
	system("CLS");
	header();
	int user = 0;
	int pass = 0;
	char temp[] = "";
	FILE* dataAdmin;

	printf("Silahkan Login!\n");
	printf("=================================================================================================\n");
	
	loginUsername:
	printf("\tUsername\t\t: ");
	scanf("%s", username);
	loginPassword:
	printf("\tPassword\t: ");
	scanf("%s", password);

	if (pass == 0 && user == 1){
		if (strcmp(password, temp) == 0){
			menuUtama();
		} else {
			goto loginPassword;
		}
	}

	dataAdmin = fopen("data admin.txt", "a+");
	while (fscanf(dataAdmin, "%s\n%[^\n]\n%s\n%s\n", tambah.kodeAdmin, tambah.nama, tambah.username, tambah.password) != EOF) {
		user = 0;
		pass = 0;
		if (strcmp(username, tambah.username) == 0){
			user = 1;
			if (strcmp(password, tambah.password) == 0){
				pass = 1;
				menuUtama();
				break;
			} else {
				pass = 0;
				strcat(temp, tambah.password);
				printf("Password Anda Salah!\n");
				goto loginPassword;
			}
		} else {
			if (strcmp(password, tambah.password) == 0){
				pass = 2;
				if (user == 1 && pass == 2){
					menuUtama();
				}
				fclose(dataAdmin);
				printf("Username atau Pasword Anda Salah!\n");
				goto loginUsername;
				break;
			} else {
				pass = 0;
			}
			
		}
	}
	if (pass == 0 && user == 1){
		printf("Password Anda Salah!\n");
		goto loginPassword;
	} else if (user == 0 && pass == 0){
		printf("Username dan Pasword Anda Salah!\n");
		goto loginUsername;
	}

	fclose(dataAdmin);
}

void signup() {
	system("CLS");
	header();

	FILE* dataAdmin;
	dataAdmin = fopen("data admin.txt", "a+");

	printf("Silahkan Registrasi Terlebih Dahulu!\n");
	printf("=================================================================================================\n");
	signUpKodeAdmin:
	printf("\tKode Admin\t: ");
	scanf("%s", kodeAdmin);
	while (fscanf(dataAdmin, "%s\n%s\n%s\n%s\n", tambah.kodeAdmin, tambah.nama, tambah.username, tambah.password) != EOF){
		if(strcmp(kodeAdmin, tambah.kodeAdmin) == 0){
			printf("Kode Admin Sudah Terdaftar!\n");
			goto signUpKodeAdmin;
		}
	}

	getchar();
	printf("\tNama\t\t: ");
	scanf("%[^\n]", tambah.nama);

	signUpUsername:
	printf("\tUsername\t: ");
	scanf("%s", username);
	while (fscanf(dataAdmin, "%s\n%s\n%s\n%s\n", tambah.kodeAdmin, tambah.nama, tambah.username, tambah.password) != EOF){
		if(strcmp(username, tambah.username) == 0){
			printf("Username Sudah Terdaftar!\n");
			goto signUpUsername;
		}
	}
	printf("\tPassword\t: ");
	scanf("%s", tambah.password);
	fprintf(dataAdmin, "%s\n%s\n%s\n%s\n", kodeAdmin, tambah.nama, username, tambah.password);

	fclose(dataAdmin);

	login();
}

void menuUtama() {
	int pilihMenu;

	system("CLS");
	header();
	do {
		printf("%s\t \tMENU UTAMA\n", username);
		printf("=================================================================================================\n");
		printf("\t1. Manajemen Data\n");
		printf("\t2. Transaksi Penjualan\n");
		printf("\t3. Transaksi Pembelian\n");
		printf("\t4. Pencarian Data\n");
		printf("\t5. Laporan Transaksi\n");
		printf("\t6. Keluar\n");
		printf("\tSilahkan Pilih (1/2/3/4/5/6): ");
		scanf("%d", &pilihMenu);
		switch (pilihMenu) {
		case 1:
			manajemenData();
			break;
		case 2:
			transaksiPenjualan();
			break;
		case 3:
			transaksiPembelian();
			break;
		case 4:
			pencarianData();
			break;
		case 5:
			laporanTransaksi();
			break;
		case 6:
			printf("\tTerima Kasih Telah Menggunakan SIstem Ini!");
			break;
		default:
			printf("\tAnda Salah Memilih Menu!\n");
			break;
		}
	} while (pilihMenu != 6);

}

void manajemenData() {
	system("CLS");
	header();

	int menuManajemen;

	printf("%s\t\t Manajemen Data\n", username);
	printf("=================================================================================================\n");

	menuManajemen:
	printf("\t1. Kelola Data Obat\n");
	printf("\t2. Kelola Data Supplier\n");
	printf("\t3. Kelola Data Customer\n");
	printf("\tSilahkan Pilih (1/2/3): ");
	scanf("%d", &menuManajemen);
	printf("=================================================================================================\n");
	switch (menuManajemen) {
	case 1:
		kelolaDataObat();
		break;
	case 2:
		kelolaDataSupplier();
		break;
	case 3:
		kelolaDataCustomer();
		break;
	default:
		printf("\tAnda Salah Memilih Menu!\n");
		goto menuManajemen;
		break;
	}
}

void kelolaDataObat() {
	int menuDataObat;

	printf("%s\t\t Kelola Data Obat\n", username);
	printf("=================================================================================================\n");

	menuDataObat:
	printf("\t1. Menambahkan Data Obat\n");
	printf("\t2. Menampilkan Data Obat\n");
	printf("\t3. Mengedit Data Obat\n");
	printf("\t4. Menghapus Data Obat\n");
	printf("\tSilahkan Pilih (1/2/3/4): ");
	scanf("%d", &menuDataObat);
	printf("=================================================================================================\n");
	switch (menuDataObat) {
	case 1:
		menambahkanDataObat();
		break;
	case 2:
		menampilkanDataObat();
		break;
	case 3:
		mengeditDataObat();
		break;
	case 4:
		menghapusDataObat();
		break;
	default:
		printf("\tAnda Salah Memilih Menu!\n");
		goto menuDataObat;
		break;
	}
}

void menambahkanDataObat() {
	FILE* dataObat;
	dataObat = fopen("data obat.txt", "a+");

	printf("%s\t\t Menambahkan Data Obat\n", username);
	printf("=================================================================================================\n");
	printf("\tID Obat\t\t\t: ");
	scanf("%s", tambahObat.idObat);



	printf("\tNama Obat\t\t: ");
	scanf("%s", tambahObat.namaObat);
	printf("\tNomor Rak\t\t: ");
	scanf("%d", &tambahObat.nomorRak);
	printf("\tStok\t\t\t: ");
	scanf("%d", &tambahObat.stok);
	printf("\tHarga\t\t: ");
	scanf("%d", &tambahObat.harga);
	printf("\tTanggal Produksi (DDMMYYYY)\t: ");

	scanf("%d", &tambahObat.tanggalProduksi);
	printf("\tTanggal Kadaluarsa (DDMMYYYY)\t: ");
	scanf("%d", &tambahObat.tanggalKadaluarsa);

	fprintf(dataObat, "%s\n%s\n%d\n%d\n%d\n%d\n%d\n", tambahObat.idObat, tambahObat.namaObat, tambahObat.nomorRak, tambahObat.stok, tambahObat.harga, tambahObat.tanggalProduksi, tambahObat.tanggalKadaluarsa);

	fclose(dataObat);
}
void menampilkanDataObat() {
	FILE* dataObat;
	dataObat = fopen("data obat.txt", "a+");

	printf("%s\t\t Menampilkan Data Obat\n", username);
	printf("=================================================================================================\n");
	printf("ID Obat\t|\tNama Obat\t| Nomor Rak | Stok |    Harga    | Tanggal Produksi | Tanggal Kadaluarsa\n");
	printf("-------------------------------------------------------------------------------------------------\n");
	while (fscanf(dataObat, "%s\n%s\n%d\n%d\n%d\n%d\n%d\n", tambahObat.idObat, tambahObat.namaObat, &tambahObat.nomorRak, &tambahObat.stok, &tambahObat.harga, &tambahObat.tanggalProduksi, &tambahObat.tanggalKadaluarsa) != EOF) {
		printf("%-8s| %-22s| %-10d| %-5d| %-12d| %-17d| %-17d\n", tambahObat.idObat, tambahObat.namaObat, tambahObat.nomorRak, tambahObat.stok, tambahObat.harga, tambahObat.tanggalProduksi, tambahObat.tanggalKadaluarsa);
	}

	fclose(dataObat);
}
void mengeditDataObat() {
	char idObat[50];
	int menuUbah;
	FILE* dataObatLama,* dataObatBaru;
	dataObatLama = fopen("data obat.txt", "a+");
	dataObatBaru = fopen("data obat baru.txt", "a+");

	menampilkanDataObat();

	printf("%s\t\t Mengedit Data Obat\n", username);
	printf("=================================================================================================\n");
	printf("Pilih ID Obat: ");
	scanf("%s", idObat);

	while (fscanf(dataObatLama, "%s\n%s\n%d\n%d\n%d\n%d\n%d\n", tambahObat.idObat, tambahObat.namaObat, &tambahObat.nomorRak, &tambahObat.stok, &tambahObat.harga, &tambahObat.tanggalProduksi, &tambahObat.tanggalKadaluarsa) != EOF) {
		if (strcmp(idObat, tambahObat.idObat) != 0) {
			fprintf(dataObatBaru, "%s\n%s\n%d\n%d\n%d\n%d\n%d\n", tambahObat.idObat, tambahObat.namaObat, tambahObat.nomorRak, tambahObat.stok, tambahObat.harga, tambahObat.tanggalProduksi, tambahObat.tanggalKadaluarsa);
		}
		else {
			menuUbah:
			printf("\tData yang ingin diubah?\n");
			printf("\t1. Nama Obat\n");
			printf("\t2. Nomor Rak Obat\n");
			printf("\t3. Stok Obat\n");
			printf("\t4. Harga Obat\n");
			printf("\t5. Tanggal Produksi Obat\n");
			printf("\t6. Tanggal Kadaluarsa Obat\n");
			printf("\tPilihan Anda (1/2/3/4/5/6): ");
			scanf("%d", &menuUbah);
			switch (menuUbah){
			case 1:
				printf("\tNama baru: ");
				scanf("%s", editObat.namaObat);

				fprintf(dataObatBaru, "%s\n%s\n%d\n%d\n%d\n%d\n%d\n", tambahObat.idObat, editObat.namaObat, tambahObat.nomorRak, tambahObat.stok, tambahObat.harga, tambahObat.tanggalProduksi, tambahObat.tanggalKadaluarsa);
				break;
			case 2:
				printf("\tNomor rak baru: ");
				scanf("%s", editObat.nomorRak);

				fprintf(dataObatBaru, "%s\n%s\n%d\n%d\n%d\n%d\n%d\n", tambahObat.idObat, tambahObat.namaObat, editObat.nomorRak, tambahObat.stok, tambahObat.harga, tambahObat.tanggalProduksi, tambahObat.tanggalKadaluarsa);
				break;
			case 3:
				printf("\tStok baru: ");
				scanf("%s", editObat.stok);

				fprintf(dataObatBaru, "%s\n%s\n%d\n%d\n%d\n%d\n%d\n", tambahObat.idObat, tambahObat.namaObat, tambahObat.nomorRak, editObat.stok, tambahObat.harga, tambahObat.tanggalProduksi, tambahObat.tanggalKadaluarsa);
				break;
			case 4:
				printf("\tHarga baru: ");
				scanf("%s", editObat.harga);

				fprintf(dataObatBaru, "%s\n%s\n%d\n%d\n%d\n%d\n%d\n", tambahObat.idObat, tambahObat.namaObat, tambahObat.nomorRak, tambahObat.stok, editObat.harga, tambahObat.tanggalProduksi, tambahObat.tanggalKadaluarsa);
				break;
			case 5:
				printf("\tTanggal produksi baru: ");
				scanf("%s", editObat.tanggalProduksi);

				fprintf(dataObatBaru, "%s\n%s\n%d\n%d\n%d\n%d\n%d\n", tambahObat.idObat, tambahObat.namaObat, tambahObat.nomorRak, tambahObat.stok, tambahObat.harga, editObat.tanggalProduksi, tambahObat.tanggalKadaluarsa);
				break;
			case 6:
				printf("\tTanggal kadaluarsa baru: ");
				scanf("%s", editObat.tanggalKadaluarsa);

				fprintf(dataObatBaru, "%s\n%s\n%d\n%d\n%d\n%d\n%d\n", tambahObat.idObat, tambahObat.namaObat, tambahObat.nomorRak, tambahObat.stok, tambahObat.harga, tambahObat.tanggalProduksi, editObat.tanggalKadaluarsa);
				break;
			default:
				printf("\tAnda Salah Memilih Menu!\n");
				goto menuUbah;
				break;
			}
		}
	}

	fclose(dataObatLama);
	fclose(dataObatBaru);
	printf("\tData Berhasil diubah.!");

	remove("data obat.txt");
	rename("data obat baru.txt", "data obat.txt");

}
void menghapusDataObat() {
	char idObat[50];
	int menuUbah;
	FILE* dataObatLama, * dataObatBaru;
	dataObatLama = fopen("data obat.txt", "a+");
	dataObatBaru = fopen("data obat baru.txt", "a+");

	menampilkanDataObat();

	printf("%s\t\t Menghapus Data Obat\n", username);
	printf("=================================================================================================\n");
	printf("Pilih ID Obat: ");
	scanf("%s", idObat);
	while (fscanf(dataObatLama, "%s\n%s\n%d\n%d\n%d\n%d\n%d\n", tambahObat.idObat, tambahObat.namaObat, &tambahObat.nomorRak, &tambahObat.stok, &tambahObat.harga, &tambahObat.tanggalProduksi, &tambahObat.tanggalKadaluarsa) != EOF) {
		if (strcmp(idObat, tambahObat.idObat) != 0) {
			fprintf(dataObatBaru, "%s\n%s\n%d\n%d\n%d\n%d\n%d\n", tambahObat.idObat, tambahObat.namaObat, tambahObat.nomorRak, tambahObat.stok, tambahObat.harga, tambahObat.tanggalProduksi, tambahObat.tanggalKadaluarsa);
		}
	}

	fclose(dataObatLama);
	fclose(dataObatBaru);
	printf("\tData Berhasil diubah.!");

	remove("data obat.txt");
	rename("data obat baru.txt", "data obat.txt");
}

void kelolaDataSupplier() {
	int menuDataSupplier;

	printf("%s\t\t Kelola Data Supplier\n", username);
	printf("=================================================================================================\n");

	menuDataSupplier:
	printf("\t1. Menambahkan Data Supplier\n");
	printf("\t2. Menampilkan Data Supplier\n");
	printf("\t3. Mengedit Data Supplier\n");
	printf("\t4. Menghapus Data Supplier\n");
	printf("\tSilahkan Pilih (1/2/3/4): ");
	scanf("%d", &menuDataSupplier);
	printf("=================================================================================================\n");
	switch (menuDataSupplier) {
	case 1:
		menambahkanDataSupplier();
		break;
	case 2:
		menampilkanDataSupplier();
		break;
	case 3:
		mengeditDataSupplier();
		break;
	case 4:
		menghapusDataSupplier();
		break;
	default:
		printf("\tAnda Salah Memilih Menu!\n");
		goto menuDataSupplier;
		break;
	}
}

void menambahkanDataSupplier() {

    FILE* dataSupplier;
	dataSupplier = fopen("data supplier.txt", "a+");

	printf("%s\t\t Menambahkan Data Supplier\n", username);
	printf("=================================================================================================\n");
	
	printf("\tID Supplier\t\t: ");
	scanf("%s", tambahSupplier.idSupplier);
	printf("\tNama Supplier\t\t: ");
	scanf("%s", tambahSupplier.namaSupplier);
	printf("\tNomor HP Supplier\t\t: ");
	scanf("%d", &tambahSupplier.nomorHpSupplier);
	printf("\tKota Supplier\t\t: ");
	scanf("%s", tambahSupplier.kotaSupplier);

	fprintf(dataSupplier, "%s\n%s\n%d\n%s\n", tambahSupplier.idSupplier, tambahSupplier.namaSupplier, tambahSupplier.nomorHpSupplier, tambahSupplier.kotaSupplier);

	fclose(dataSupplier);
}

void menampilkanDataSupplier() {
	FILE* dataSupplier;
	dataSupplier = fopen("data supplier.txt", "a+");

	printf("%s\t\t Menampilkan Data Supplier\n", username);
	printf("=================================================================================================\n");
	printf("ID Supplier\t| Nama Supplier\t| Nomor HP Supplier | Kota Supplier\n");
	printf("-------------------------------------------------------------------------------------------------\n");

	while (fscanf(dataSupplier, "%s\n%s\n%d\n%s\n", tambahSupplier.idSupplier, tambahSupplier.namaSupplier, &tambahSupplier.nomorHpSupplier, tambahSupplier.kotaSupplier) != EOF) {
		printf("%s\t| %s\t| %d\t  | %s\n", tambahSupplier.idSupplier, tambahSupplier.namaSupplier, tambahSupplier.nomorHpSupplier, tambahSupplier.kotaSupplier);
	}
	
	fclose(dataSupplier);
}

void mengeditDataSupplier() {
	FILE* dataSupplier, * dataSupplierBaru;
	char idSupplier[50];
	int found = 0;

	dataSupplier = fopen("data supplier.txt", "r");
	dataSupplierBaru = fopen("data supplier temp.txt", "w");

	printf("%s\t\t Mengedit Data Supplier\n", username);
	printf("=================================================================================================\n");
	printf("\tMasukkan ID Supplier yang Akan Diedit\t: ");
	scanf("%s", idSupplier);

	while (fscanf(dataSupplier, "%s\n%s\n%d\n%s\n", tambahSupplier.idSupplier, tambahSupplier.namaSupplier, &tambahSupplier.nomorHpSupplier, tambahSupplier.kotaSupplier) != EOF) {
		if (strcmp(tambahSupplier.idSupplier, idSupplier) == 0) {
			found = 1;
			printf("\tID Supplier\t\t\t: %s\n", tambahSupplier.idSupplier);
			printf("\tNama Supplier\t\t: %s\n", tambahSupplier.namaSupplier);
			printf("\tNomor HP Supplier\t\t: %d\n", tambahSupplier.nomorHpSupplier);
			printf("\tKota Supplier\t\t: %s\n", tambahSupplier.kotaSupplier);

			printf("\tMasukkan Data Baru:\n");
			printf("\tNama Supplier\t\t: ");
			scanf("%s", editSupplier.namaSupplier);
			printf("\tNomor HP Supplier\t\t: ");
			scanf("%d", &editSupplier.nomorHpSupplier);
			printf("\tKota Supplier\t\t: ");
			scanf("%s", editSupplier.kotaSupplier);

			fprintf(dataSupplierBaru, "%s\n%s\n%d\n%s\n", tambahSupplier.idSupplier, editSupplier.namaSupplier, editSupplier.nomorHpSupplier, editSupplier.kotaSupplier);
		}
		else {
			fprintf(dataSupplierBaru, "%s\n%s\n%d\n%s\n", tambahSupplier.idSupplier, tambahSupplier.namaSupplier, tambahSupplier.nomorHpSupplier, tambahSupplier.kotaSupplier);
		}
	}

	fclose(dataSupplier);
	fclose(dataSupplierBaru);

	if (found) {
		remove("data supplier.txt");
		rename("data supplier temp.txt", "data supplier.txt");
		printf("\tData Supplier Berhasil Diedit!\n");
	}
	else {
		remove("data supplier temp.txt");
		printf("\tData Supplier Tidak Ditemukan!\n");
	}
}

void menghapusDataSupplier() {
    FILE* dataSupplier, * dataSupplierBaru;
	char idSupplier[50];
	int found = 0;

	dataSupplier = fopen("data supplier.txt", "r");
	dataSupplierBaru = fopen("data supplier temp.txt", "w");

	printf("%s\t\t Menghapus Data Supplier\n", username);
	printf("=================================================================================================\n");

	printf("\tMasukkan ID Supplier yang Akan Dihapus\t: ");
	scanf("%s", idSupplier);
	
	while (fscanf(dataSupplier, "%s\n%s\n%d\n%s\n", tambahSupplier.idSupplier, tambahSupplier.namaSupplier, &tambahSupplier.nomorHpSupplier, tambahSupplier.kotaSupplier) != EOF) {
		if (strcmp(tambahSupplier.idSupplier, idSupplier) == 0) {
			found = 1;
			printf("\tData Supplier dengan ID %s Berhasil Dihapus!\n", tambahSupplier.idSupplier);
		}
		else {
			fprintf(dataSupplierBaru, "%s\n%s\n%d\n%s\n", tambahSupplier.idSupplier, tambahSupplier.namaSupplier, tambahSupplier.nomorHpSupplier, tambahSupplier.kotaSupplier);
		}
	}

	fclose(dataSupplier);
	fclose(dataSupplierBaru);

	if (found) {
		remove("data supplier.txt");
		rename("data supplier temp.txt", "data supplier.txt");
	}
	else {
		remove("data supplier temp.txt");
		printf("\tData Supplier Tidak Ditemukan!\n");
	}
}

void kelolaDataCustomer() {
	int menuDataCustomer;

	printf("%s\t\t Kelola Data Customer\n", username);
	printf("=================================================================================================\n");

	menuDataCustomer:
	printf("\t1. Menambahkan Data Customer\n");
	printf("\t2. Menampilkan Data Customer\n");
	printf("\t3. Mengedit Data Customer\n");
	printf("\t4. Menghapus Data Customer\n");
	printf("\tSilahkan Pilih (1/2/3/4): ");
	scanf("%d", &menuDataCustomer);
	printf("=================================================================================================\n");
	switch (menuDataCustomer) {
	case 1:
		menambahkanDataCustomer();
		break;
	case 2:
		menampilkanDataCustomer();
		break;
	case 3:
		mengeditDataCustomer();
		break;
	case 4:
		menghapusDataCustomer();
		break;
	default:
		printf("\tAnda Salah Memilih Menu!\n");
		goto menuDataCustomer;
		break;
	}
}

void menambahkanDataCustomer() {
	printf("%s\t\t Menambahkan Data Customer\n", username);
	printf("=================================================================================================\n");

}
void menampilkanDataCustomer() {
	printf("%s\t\t Menampilkan Data Customer\n", username);
	printf("=================================================================================================\n");

}
void mengeditDataCustomer() {
	printf("%s\t\t Mengedit Data Customer\n", username);
	printf("=================================================================================================\n");

}
void menghapusDataCustomer() {
	printf("%s\t\t Menghapus Data Customer\n", username);
	printf("=================================================================================================\n");

}

void transaksiPenjualan() {
	system("CLS");
	header();
	int menuTransaksi;

	printf("%s\t \tTransaksi Penjualan\n", username);
	printf("=================================================================================================\n");
	
	menuPenjualan:
	printf("\t1. Buat Transaksi Penjualan\n");
	printf("\t2. Lihat Transaksi Penjualan\n");
	printf("Silahkan Pilih (1/2): ");
	scanf("%d", &menuTransaksi);
	printf("=================================================================================================\n");
	switch (menuTransaksi){
	case 1:
		membuatPenjualan();
		break;
	case 2:
		melihatPenjualan();
		break;
	default:
		printf("\tAnda Salah Memilih Menu!\n");
		goto menuPenjualan;
		break;
	}
}

void membuatPenjualan() {
	printf("%s\t\t Buat Transaksi Penjualan\n", username);
	printf("=================================================================================================\n");

}
void melihatPenjualan() {
	printf("%s\t\t Lihat Transaksi Penjualan\n", username);
	printf("=================================================================================================\n");

}

void transaksiPembelian() {
	system("CLS");
	header();
	int menuTransaksi;

	printf("%s\t \tTransaksi Pembelian\n", username);
	printf("=================================================================================================\n");

	menuPembelian:
	printf("\t1. Buat Transaksi Pembelian\n");
	printf("\t2. Lihat Transaksi Pembelian\n");
	printf("Silahkan Pilih (1/2): ");
	scanf("%d", &menuTransaksi);
	printf("=================================================================================================\n");
	switch (menuTransaksi) {
	case 1:
		membuatPembelian();
		break;
	case 2:
		melihatPembelian();
		break;
	default:
		printf("\tAnda Salah Memilih Menu!\n");
		goto menuPembelian;
		break;
	}
}

void membuatPembelian() {
	printf("%s\t\t Buat Transaksi Pembelian\n", username);
	printf("=================================================================================================\n");

}
void melihatPembelian() {
	printf("%s\t\t Lihat Transaksi Pembelian\n", username);
	printf("=================================================================================================\n");

}

void pencarianData() {
	system("CLS");
	header();
	int menuPencarian;
	printf("%s\t \tPencarian Data\n", username);
	printf("=================================================================================================\n");
	menuPencarian:
	printf("\t1. Cari Data Obat\n");
	printf("\t2. Cari Data Customer\n");
	printf("\t3. Cari Data Supplier\n");
	printf("Silahkan Pilih(1/2/3): ");
	scanf("%d", &menuPencarian);
	printf("=================================================================================================\n");
	switch (menuPencarian) {
	case 1:
		cariObat();
		break;
	case 2:
		cariCustomer();
		break;
	case 3:
		cariSupplier();
		break;
	default:
		printf("\tAnda Salah Memilih Menu!\n");
		goto menuPencarian;
		break;
	}
}

void cariObat() {
	printf("%s\t\t Cari Obat\n", username);
	printf("=================================================================================================\n");

}
void cariCustomer() {
	printf("%s\t\t Cari Customer\n", username);
	printf("=================================================================================================\n");

}
void cariSupplier() {
	printf("%s\t\t Cari Supplier\n", username);
	printf("=================================================================================================\n");

}

void laporanTransaksi() {
	system("CLS");
	header();
	int menuTransaksi;

	printf("%s\t \tLaporan Transaksi\n", username);
	printf("=================================================================================================\n");
	menuLaporan:
	printf("\t1. Laporan Penjualan Obat\n");
	printf("\t2. Laporan Pembelian Obat\n");
	printf("\tSilahkan Pilih (1/2): ");
	scanf("%d", &menuTransaksi);
	printf("=================================================================================================\n");
	switch (menuTransaksi) {
	case 1:
		laporanPenjualan();
		break;
	case 2:
		laporanPembelian();
		break;
	default:
		printf("\tAnda Salah Memilih Menu!\n");
		goto menuLaporan;
		break;
	}
}

void laporanPenjualan() {
	int tanggal;
	printf("%s\t\t Laporan Penjualan\n", username);
	printf("=================================================================================================\n");
	printf("\tTanggal Transaksi (DDMMYYYY): ");
	scanf("%d", &tanggal);

}

void laporanPembelian() {
	int tanggal;
	printf("%s\t\t Laporan Pembelian\n", username);
	printf("=================================================================================================\n");
	printf("\tTanggal Transaksi (DDMMYYYY): ");
	scanf("%d", &tanggal);

}


