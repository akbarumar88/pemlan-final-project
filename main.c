#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct
{
    char kecamatan[15];
    char kota[15];
} Alamat;

typedef struct
{
    char nama[32];
    char npm[15];
    char fakultas[20];
    char jurusan[20];
    int semester;
    Alamat alamat;
} Mahasiswa;

#define max 100
// Taruh variable size dan array global, biar bisa diakses dimana saja
int curSize = 4;
// Array kasih maxLength, kalau tidak maka terjadi eror ketika tambah/ubah data
Mahasiswa listMhs[max] = {
    { "Akbar Umar", "043", "Ilmu Komputer", "Teknik Informatika", 3, {"Suko", "Sidoarjo"} },
    { "Danil Hendra", "045", "Ilmu Komputer", "Teknik Informatika", 3, {"Suko", "Sidoarjo"} },
    { "Bayu Aji", "046", "Ilmu Komputer", "Teknik Informatika", 3, {"Suko", "Sidoarjo"} },
    { "Firman Anhar", "047", "Ilmu Komputer", "Teknik Informatika", 3, {"Suko", "Sidoarjo"} },
};

int main()
{
    displayMahasiswa();
    bool exit = false;
    while (!exit) {
        int choice;
        printf("1. Tambah Data \n");
        printf("2. Ubah Data \n");
        printf("3. Hapus Data \n");
        printf("4. Keluar \n");
        printf("5. Urut berdasarkan nama \n");
        printf("6. Urut berdasarkan NPM \n");
        printf("7. Cari berdasarkan NPM \n");
        printf("Pilihan Anda: "); scanf("%i", &choice);
        printf("\n");

        switch(choice) {
            case 1:
                tambahData();
                displayMahasiswa();
                break;

            case 2:
                ubahData();
                displayMahasiswa();
                break;

            case 3:
                hapusData();
                displayMahasiswa();
                break;

            case 4:
                exit = true;
                break;

            case 5:
                urutBy("nama");
                displayMahasiswa();
                break;

            case 6:
                urutBy("npm");
                displayMahasiswa();
                break;

            case 7:
                searchBy("npm");
                break;

            default:
                printf("Pilihan tidak tersedia\n\n");
                break;
        }
    }
    return 0;
}

void tambahData() {
    Mahasiswa m;
    printf("Nama        : "); fflush(stdin); gets(m.nama);
    printf("NPM         : "); scanf("%s", m.npm);
    printf("Fakultas    : "); fflush(stdin); gets(m.fakultas);
    printf("Jurusan     : "); fflush(stdin); gets(m.jurusan);
    printf("Semester    : "); scanf("%i", &m.semester);
    printf("Kota 	    : "); scanf("%s", m.alamat.kota);
    printf("Kecamatan   : "); scanf("%s", m.alamat.kecamatan);
    printf("\n\nData berhasil ditambahkan! \n\n");
    listMhs[curSize] = m; curSize++;
}

void ubahData() {
    if (curSize == 0) {
        printf("Tidak ada data yg bisa diubah\n\n");
        return;
    }
    int urutan, urutanIndex;
    bool salahInput=false;
    do
    {
        printf("Urutan yang akan diubah : "); scanf("%i", &urutan);
        if (urutan < 1 || urutan > curSize) {
            printf("Urutan harus antara 1 dan %i\n", curSize);
            salahInput=true;
            continue;
        }
        salahInput=false;
    }
    while (salahInput);

    urutanIndex = urutan-1;

    Mahasiswa m;
    printf("Nama        : "); fflush(stdin); gets(m.nama);
    printf("NPM         : "); scanf("%s", m.npm);
    printf("Fakultas    : "); fflush(stdin); gets(m.fakultas);
    printf("Jurusan     : "); fflush(stdin); gets(m.jurusan);
    printf("Semester    : "); scanf("%i", &m.semester);
    printf("Kota 	    : "); scanf("%s", m.alamat.kota);
    printf("Kecamatan   : "); scanf("%s", m.alamat.kecamatan);
    printf("\n\nData berhasil diubah! \n\n");
    listMhs[urutanIndex] = m;
}

void hapusData() {
    if (curSize == 0) {
        printf("Tidak ada data yg bisa dihapus\n\n");
        return;
    }
    int urutan, urutanIndex;
    bool salahInput=false;
    do
    {
        printf("Urutan yang akan dihapus : "); scanf("%i", &urutan);
        if (urutan < 1 || urutan > curSize) {
            printf("Urutan harus antara 1 dan %i\n", curSize);
            salahInput=true;
            continue;
        }
        salahInput=false;
    }
    while (salahInput);

    urutanIndex = urutan-1;
    int i;
    for (i = urutanIndex; i < curSize-1;i++) {
        listMhs[i] = listMhs[i+1];
    }
    curSize--;
    printf("\n\nData berhasil dihapus! \n\n");
}

void displayMahasiswa() {
    int i;
    for (i = 0; i < curSize; i++) {
        printf("Nama        : %s \n", listMhs[i].nama);
        printf("NPM         : %s \n", listMhs[i].npm);
        printf("Fakultas    : %s \n", listMhs[i].fakultas);
        printf("Jurusan     : %s \n", listMhs[i].jurusan);
        printf("Semester    : %i \n", listMhs[i].semester);
        printf("Alamat      : %s, %s \n\n", listMhs[i].alamat.kecamatan, listMhs[i].alamat.kota);
    }
}

// Start sorting method
void urutBy(char atribut[]) {
    int order;
    bool salahInput=false;
    // Inputkan Order (asc/desc)
    do
    {
        printf("1. Ascending\n");
        printf("2. Descending\n");
        printf("Pilih tipe order : "); scanf("%i", &order);
        printf("\n");
        // Jika salah inputan, maka continue
        if (order < 1 || order > 2) {
            printf("Pilih antara 1 atau 2! \n\n");
            salahInput=true;
            continue;
        }
        salahInput = false;
    } while (salahInput);

    // Inputkan metode sort (bubble, selection, dst.)
    int sortingType;
    do
    {
        printf("1. Bubble Sort\n");
        printf("2. Selection Sort\n");
        printf("Pilih metode pengurutan : "); scanf("%i", &sortingType);
        printf("\n");
        // Jika salah inputan, maka continue
        if (sortingType < 1 || sortingType > 2) {
            printf("Pilih antara 1 atau 2! \n\n");
            salahInput=true;
            continue;
        }
        salahInput = false;
    } while (salahInput);

    switch(sortingType) {
        case 1:
            bubbleSort(atribut, order);
            break;

        case 2:
            selectionSort(atribut, order);
            break;
    }
}

bubbleSort(char atribut[], int order) {
    /**
    * 1 = Ascending
    * 2 = Descending
    */
    int i,j;
    for (i=0; i<curSize; i++) {
        for (j = 0; j < curSize-i-1; j++) {
            bool kondisi;
            if (strcmp(atribut, "nama") == 0) {
                kondisi = order == 1
                            ? strcmp(listMhs[j].nama, listMhs[j+1].nama) > 0
                            : strcmp(listMhs[j].nama, listMhs[j+1].nama) < 0;
            } else {
                kondisi = order == 1
                            ? strcmp(listMhs[j].npm, listMhs[j+1].npm) > 0
                            : strcmp(listMhs[j].npm, listMhs[j+1].npm) < 0;
            }

            if (kondisi) {
                // Tukar nilai
                Mahasiswa temp = listMhs[j];
                listMhs[j] = listMhs[j+1];
                listMhs[j+1] = temp;
            }
        }
    }
}

selectionSort(char atribut[], int order) {
    /**
    * 1 = Ascending
    * 2 = Descending
    */
    int i,j;
    for (i = 0; i < curSize-1; i++) {
        int selected_index = i;
        for (j = i+1; j < curSize; j++) {
            bool kondisi;
            if (strcmp(atribut, "nama") == 0) {
                kondisi = order == 1
                            ? strcmp(listMhs[j].nama, listMhs[selected_index].nama) < 0
                            : strcmp(listMhs[j].nama, listMhs[selected_index].nama) > 0;
            } else {
                kondisi = order == 1
                            ? strcmp(listMhs[j].npm, listMhs[selected_index].npm) < 0
                            : strcmp(listMhs[j].npm, listMhs[selected_index].npm) > 0;
            }

            if (kondisi) {
                // Catat indeks
                selected_index = j;
            }
        }
        // Tukar nilai
        Mahasiswa temp = listMhs[i];
        listMhs[i] = listMhs[selected_index];
        listMhs[selected_index] = temp;
    }
}
// End sorting method

// Start searching method
void searchBy(char atribut[]) {
    int search_method;
    bool salahInput=false;
    // Inputkan searching method (sequential/binary)
    do
    {
        printf("1. Sequential Search\n");
        printf("2. Binary Search\n");
        printf("3. Interpolation Search\n");
        printf("Pilih metode searching : "); scanf("%i", &search_method);
        printf("\n");
        // Jika salah inputan, maka continue
        if (search_method < 1 || search_method > 3) {
            printf("Pilih antara 1 sampai 3! \n\n");
            salahInput=true;
            continue;
        }
        salahInput = false;
    } while (salahInput);

    char keyword[30];
    printf("Inputkan NPM yang akan anda cari : "); scanf("%s", keyword);
    switch(search_method) {
        case 1:
            sequentialSearch(keyword);
            break;

        case 2:
            binarySearch(keyword);
            break;

        case 3:
            interpolationSearch(keyword);
            break;
    }
}

void sequentialSearch(char keyword[30]) {
    bool found=false;
    int i;
    for (i=0; i<curSize; i++) {
        Mahasiswa current_mhs = listMhs[i];
        // Jika data ditemukan maka:
        if (strcmp(current_mhs.npm, keyword) == 0) {
            found = true;
            break;
        }
    }

    if (!found) {
        printf("Maaf, data yang anda cari tidak ditemukan \n\n");
    } else {
        Mahasiswa current_mhs = listMhs[i];
        printf("Data yang anda cari berhasil ditemukan \n");
        printf("Nama        : %s \n", current_mhs.nama);
        printf("NPM         : %s \n", current_mhs.npm);
        printf("Fakultas    : %s \n", current_mhs.fakultas);
        printf("Jurusan     : %s \n", current_mhs.jurusan);
        printf("Semester    : %i \n", current_mhs.semester);
        printf("Alamat      : %s, %s \n\n", current_mhs.alamat.kecamatan, current_mhs.alamat.kota);
    }
}

void binarySearch(char keyword[30]) {
    // Urutkan data terlebih dahulu, by NPM ascending
    selectionSort("npm", 1);

    // Inisialisasi awal
    bool found=false;
    int l=0, r=curSize-1, m;

    while (l <= r && !found) {
        m = (l+r)/2;
        // Jika data ditemukan
        if (strcmp(keyword, listMhs[m].npm) == 0) {
            found=true;
        } else if (strcmp(keyword, listMhs[m].npm) < 0) {
            r = m-1;
        } else {
            l = m+1;
        }
    }

    if (!found) {
        printf("Maaf, data yang anda cari tidak ditemukan \n\n");
    } else {
        Mahasiswa current_mhs = listMhs[m];
        printf("Data yang anda cari berhasil ditemukan \n");
        printf("Nama        : %s \n", current_mhs.nama);
        printf("NPM         : %s \n", current_mhs.npm);
        printf("Fakultas    : %s \n", current_mhs.fakultas);
        printf("Jurusan     : %s \n", current_mhs.jurusan);
        printf("Semester    : %i \n", current_mhs.semester);
        printf("Alamat      : %s, %s \n\n", current_mhs.alamat.kecamatan, current_mhs.alamat.kota);
    }
}

void interpolationSearch(char keyword[30]) {
    // Urutkan data terlebih dahulu, by NPM ascending
    selectionSort("npm", 1);

    // Inisialisasi awal
    bool found=false;
    int l=0, r=curSize-1, m;

    while (l <= r && !found) {
        m = (l+r)/2;
        // Jika data ditemukan
        if (strcmp(keyword, listMhs[m].npm) == 0) {
            found=true;
        } else if (strcmp(keyword, listMhs[m].npm) < 0) {
            r = m-1;
        } else {
            l = m+1;
        }
    }

    if (!found) {
        printf("Maaf, data yang anda cari tidak ditemukan \n\n");
    } else {
        Mahasiswa current_mhs = listMhs[m];
        printf("Data yang anda cari berhasil ditemukan \n");
        printf("Nama        : %s \n", current_mhs.nama);
        printf("NPM         : %s \n", current_mhs.npm);
        printf("Fakultas    : %s \n", current_mhs.fakultas);
        printf("Jurusan     : %s \n", current_mhs.jurusan);
        printf("Semester    : %i \n", current_mhs.semester);
        printf("Alamat      : %s, %s \n\n", current_mhs.alamat.kecamatan, current_mhs.alamat.kota);
    }
}
// End searching method
