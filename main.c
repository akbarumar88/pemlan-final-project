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
    char password[30];
    Alamat alamat;
} Mahasiswa;

typedef struct {
    char step[150];
    struct node *next;
} node;
node *petunjuk1, *petunjuk2, *petunjuk3, *petunjuk4, *petunjuk5, *petunjuk6, *petunjuk7;


#define max 100
// Taruh variable size dan array global, biar bisa diakses dimana saja
int curSize = 3;
// Array kasih maxLength, kalau tidak maka terjadi eror ketika tambah/ubah data
Mahasiswa listMhs[max] = {
    { "Akbar Umar", "043", "Ilmu Komputer", "Teknik Informatika", 3, "user123", {"Suko", "Sidoarjo"} },
    { "Danil Hendra", "045", "Ilmu Komputer", "Teknik Informatika", 3, "user123", {"Suko", "Sidoarjo"} },
    { "Bayu Setiaji", "051", "Ilmu Komputer", "Teknik Informatika", 3, "user123", {"Suko", "Sidoarjo"} }
};
int userLoggedInIndex;

int binarySearch(char atribut[], char keyword[30], bool displayResult);

void tambahData() {
    Mahasiswa m;
    printf("? Nama\t\t: "); fflush(stdin); gets(m.nama);
    printf("? NPM\t\t: "); scanf("%s", m.npm);
    printf("? Fakultas\t: "); fflush(stdin); gets(m.fakultas);
    printf("? Jurusan\t: "); fflush(stdin); gets(m.jurusan);
    printf("? Semester\t: "); scanf("%i", &m.semester);
    printf("? Kota\t\t: "); scanf("%s", m.alamat.kota);
    printf("? Kecamatan\t: "); scanf("%s", m.alamat.kecamatan);
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
        printf("? Urutan yang akan diubah : "); scanf("%i", &urutan);
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
    printf("? Nama\t\t: "); fflush(stdin); gets(m.nama);
    printf("? NPM\t\t: "); scanf("%s", m.npm);
    printf("? Fakultas\t: "); fflush(stdin); gets(m.fakultas);
    printf("? Jurusan\t: "); fflush(stdin); gets(m.jurusan);
    printf("? Semester\t: "); scanf("%i", &m.semester);
    printf("? Kota\t\t: "); scanf("%s", m.alamat.kota);
    printf("? Kecamatan\t: "); scanf("%s", m.alamat.kecamatan);
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
        printf("? Urutan yang akan dihapus : "); scanf("%i", &urutan);
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
        printf("[*] Nama\t: %s \n", listMhs[i].nama);
        printf("[*] NPM\t\t: %s \n", listMhs[i].npm);
        printf("[*] Fakultas\t: %s \n", listMhs[i].fakultas);
        printf("[*] Jurusan\t: %s \n", listMhs[i].jurusan);
        printf("[*] Semester\t: %i \n", listMhs[i].semester);
        printf("[*] Alamat\t: %s, %s \n\n", listMhs[i].alamat.kecamatan, listMhs[i].alamat.kota);
    }
}

// Start sorting method
void urutBy(char atribut[]) {
    char order;
    bool salahInput=false;
    // Inputkan Order (asc/desc)
    do
    {
        printf("1. Ascending\n");
        printf("2. Descending\n");
        printf("? Pilih tipe order : "); order = getche();
        printf("\n\n");

        // Jika salah inputan, maka continue
        if (order != '1' && order != '2') {
            printf("Pilih antara 1 atau 2! \n\n");
            salahInput=true;
            continue;
        }
        salahInput = false;
    } while (salahInput);

    // Inputkan metode sort (bubble, selection, dst.)
    char sortingType;
    do
    {
        printf("1. Bubble Sort\n");
        printf("2. Selection Sort\n");
        printf("3. Insertion Sort\n");
        printf("? Pilih metode pengurutan : "); sortingType = getche();
        printf("\n\n");
        // Jika salah inputan, maka continue
        if (sortingType != '1' && sortingType != '2' && sortingType != '3') {
            printf("Pilih antara 1 atau 2! \n\n");
            salahInput=true;
            continue;
        }
        salahInput = false;
    } while (salahInput);

    switch(sortingType) {
        case '1':
            bubbleSort(atribut, order);
            break;

        case '2':
            selectionSort(atribut, order);
            break;

        case '3':
            insertionSort(atribut, order);
            break;
    }
}

void bubbleSort(char atribut[], char order) {
    /**
    * 1 = Ascending
    * 2 = Descending
    */
    int i,j;
    for (i=0; i<curSize; i++) {
        for (j = 0; j < curSize-i-1; j++) {
            bool kondisi;
            if (strcmp(atribut, "nama") == 0) {
                kondisi = order == '1'
                            ? strcmp(listMhs[j].nama, listMhs[j+1].nama) > 0
                            : strcmp(listMhs[j].nama, listMhs[j+1].nama) < 0;
            } else {
                kondisi = order == '1'
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

void selectionSort(char atribut[], char order) {
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
                kondisi = order == '1'
                            ? strcmp(listMhs[j].nama, listMhs[selected_index].nama) < 0
                            : strcmp(listMhs[j].nama, listMhs[selected_index].nama) > 0;
            } else {
                kondisi = order == '1'
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

void insertionSort(char atribut[], char order) {
    /**
    * 1 = Ascending
    * 2 = Descending
    */
    int i,j;
    Mahasiswa temp;
    for (i=1; i<curSize; i++) {
        temp = listMhs[i];
        j = i-1;

        bool kondisi_compare;
        if (strcmp(atribut, "nama") == 0) {
            kondisi_compare = order == '1'
                            ? strcmp(listMhs[j].nama, temp.nama) > 0
                            : strcmp(listMhs[j].nama, temp.nama) < 0;
        } else {
            kondisi_compare = order == '1'
                            ? strcmp(listMhs[j].npm, temp.npm) > 0
                            : strcmp(listMhs[j].npm, temp.npm) < 0;
        }
        while (j>=0 && kondisi_compare) {
            //printf("nggeser ");
            listMhs[j+1] = listMhs[j];
            --j;

            // Perbarui kondisi compare, karena 'j' bergeser
            if (strcmp(atribut, "nama") == 0) {
                kondisi_compare = order == '1'
                                ? strcmp(listMhs[j].nama, temp.nama) > 0
                                : strcmp(listMhs[j].nama, temp.nama) < 0;
            } else {
                kondisi_compare = order == '1'
                                ? strcmp(listMhs[j].npm, temp.npm) > 0
                                : strcmp(listMhs[j].npm, temp.npm) < 0;
            }
        }
        listMhs[j+1] = temp;
    }
}
// End sorting method

// Start searching method
void searchBy(char atribut[]) {
    char search_method;
    bool salahInput=false;
    // Inputkan searching method (sequential/binary)
    do
    {
        printf("1. Pencarian Eksak\n");
        printf("2. Pencarian Parsial\n");
        printf("? Pilih metode searching : "); search_method = getche();
        printf("\n\n");
        // Jika salah inputan, maka continue
        if (search_method != '1' && search_method != '2') {
            printf("Pilih antara 1 sampai 2! \n\n");
            salahInput=true;
            continue;
        }
        salahInput = false;
    } while (salahInput);

    char keyword[30];
    printf("? Inputkan %s yang akan anda cari : ", atribut); fflush(stdin); gets(keyword);
    switch(search_method) {
        case '1':
            binarySearch(atribut, keyword, true);
            break;

        case '2':
            sequentialSearch(atribut, keyword);
            break;
    }
}

// Sequential Search untuk Searching Parsial
void sequentialSearch(char atribut[], char keyword[30]) {
    Mahasiswa hasil_search[max];
    int hasil_search_size=0;
    bool found=false;
    int i;
    for (i=0; i<curSize; i++) {
        Mahasiswa current_mhs = listMhs[i];
        // Percabangan kondisi
        char *search_res = strcmp(atribut, "npm") == 0
                        ? strstr(current_mhs.npm, keyword)
                        : strstr(current_mhs.nama, keyword);
        // Jika data ditemukan maka:
        if (search_res != NULL) {
            found = true;
            hasil_search[hasil_search_size] = listMhs[i];
            hasil_search_size++;
            //break;
        }
    }

    if (!found) {
        printf("Maaf, data yang anda cari tidak ditemukan \n\n");
    } else {
        printf("Data yang anda cari berhasil ditemukan \n");
        int j;
        for (j=0; j<hasil_search_size; j++) {
            Mahasiswa current_mhs = hasil_search[j];
            printf("[*] Nama\t: %s \n", current_mhs.nama);
            printf("[*] NPM\t\t: %s \n", current_mhs.npm);
            printf("[*] Fakultas\t: %s \n", current_mhs.fakultas);
            printf("[*] Jurusan\t: %s \n", current_mhs.jurusan);
            printf("[*] Semester\t: %i \n", current_mhs.semester);
            printf("[*] Alamat\t: %s, %s \n\n", current_mhs.alamat.kecamatan, current_mhs.alamat.kota);
        }
    }
}

// Binary Search untuk Searching Eksak
int binarySearch(char atribut[], char keyword[30], bool displayResult) {
    // Urutkan data terlebih dahulu, by 'atribut yang dipilih' ascending
    selectionSort(atribut, '1');

    // Inisialisasi awal
    bool found=false;
    int l=0, r=curSize-1, m;
    while (l <= r && !found) {
        m = (l+r)/2;
        // Percabangan Kondisi
        int res_compare = strcmp(atribut, "npm") == 0
                        ? strcmp(keyword, listMhs[m].npm)
                        : strcmp(keyword, listMhs[m].nama);
        // Jika data ditemukan
        if (res_compare == 0) {
            found=true;
        } else if (res_compare < 0) {
            r = m-1;
        } else {
            l = m+1;
        }
    }

    if (displayResult) {
        if (!found) {
            printf("Maaf, data yang anda cari tidak ditemukan \n\n");
        } else {
            printf("Data yang anda cari berhasil ditemukan \n");
            Mahasiswa current_mhs = listMhs[m];
            printf("[*] Nama\t: %s \n", current_mhs.nama);
            printf("[*] NPM\t\t: %s \n", current_mhs.npm);
            printf("[*] Fakultas\t: %s \n", current_mhs.fakultas);
            printf("[*] Jurusan\t: %s \n", current_mhs.jurusan);
            printf("[*] Semester\t: %i \n", current_mhs.semester);
            printf("[*] Alamat\t: %s, %s \n\n", current_mhs.alamat.kecamatan, current_mhs.alamat.kota);
        }
    }
    return found ? m : -1;
}

void fillPetunjuk() {
    // Alokasi Memori
    petunjuk1 = malloc(sizeof(node));
    petunjuk2 = malloc(sizeof(node));
    petunjuk3 = malloc(sizeof(node));
    petunjuk4 = malloc(sizeof(node));
    petunjuk5 = malloc(sizeof(node));
    petunjuk6 = malloc(sizeof(node));
    petunjuk7 = malloc(sizeof(node));

    // Assign Values
    strcpy(petunjuk1->step, "~ Selamat Datang pada aplikasi CRUD data UKM Mahasiswa \n");
    strcpy(petunjuk2->step, "~ Anda dapat melakukan operasi yang anda inginkan dengan menginputkan sesuai urutan nomor menu berikut.\n");
    strcpy(petunjuk3->step, "~ Anda dapat melakukan Tambah, Ubah, dan Hapus Mahasiswa\n");
    strcpy(petunjuk4->step, "~ Anda juga dapat melakukan Pengurutan berdasarkan Nama dan NPM secara Ascending / Descending \n");
    strcpy(petunjuk5->step, "~ Anda juga dapat melakukan Pencarian data secara eksak maupun parsial \n");
    strcpy(petunjuk6->step, "~ Jika layar sudah mulai penuh, anda dapat membersihkannya dengan maenu \"Clear Screen\" \n");
    strcpy(petunjuk7->step, "~ Selamat menggunakan aplikasi sederhana ini \n");

    // Sambungkan rantai
    petunjuk1->next = petunjuk2;
    petunjuk2->next = petunjuk3;
    petunjuk3->next = petunjuk4;
    petunjuk4->next = petunjuk5;
    petunjuk5->next = petunjuk6;
    petunjuk6->next = petunjuk7;
    petunjuk7->next = NULL;
}

void petunjukAplikasi() {
    node *temp = petunjuk1;
    while (temp != NULL) {
        printf(temp->step);
        temp = temp->next; // Assign address next-nya
    }
    printf("\n");
}

void login() {
    bool permitted = false;
    char inputNPM[15], inputPass[30];
    printf(">>---> >>---> >>---> >>---> >>--->\n");
    printf("\tLogin Aplikasi \n");
    printf("<---<< <---<< <---<< <---<< <---<<\n\n");
    printf("Harap memasukkan info yang sudah terdaftar \n");

    Mahasiswa found;
    int indexResult;
    do {
        printf("? NPM Mahasiswa\t: "); scanf("%s", &inputNPM);
        printf("? Password\t: "); scanf("%s", &inputPass);

        // Cari berdasarkan NPM nya
        indexResult = binarySearch("npm", inputNPM, false);
        if (indexResult != -1) {
            // Jika ditemukan, Apakah password valid?
            found = listMhs[indexResult];
            if (strcmp(found.password, inputPass) == 0) {
                permitted=true;
            } else {
                printf("Password yang anda maskkan salah. Harap coba lagi\n\n");
            }
        } else {
            // Jika tidak ditemukan
            printf("User dengan NPM %s tidak ditemukan.\n\n", inputNPM);
        }
    } while(!permitted);

    // Berhasil login
    userLoggedInIndex = indexResult;
    printf("\nSelamat datang kembali %s! \n\n", found.nama);
}

void ubahPassword() {
    bool valid = false;
    char oldPass[30], newPass[30];
    int chance = 3;
    Mahasiswa currentUser = listMhs[userLoggedInIndex];
    do {
        printf("? Inputkan password lama : "); scanf("%s", &oldPass);
        printf("? Inputkan password baru : "); scanf("%s", &newPass);

        if (strcmp(currentUser.password, oldPass) == 0) {
            // Jika password lama benar
            valid=true;
        } else {
            printf("Password lama salah.\n\n");
        }
        chance--;
    } while(!valid && chance > 0);

    if (!valid) {
        printf("Anda telah salah menginputkan password sebanyak 3 kali. Harap coba lagi nanti.\n\n");
        return;
    }
    // Jika password benar
    strcpy(currentUser.password, newPass);
    listMhs[userLoggedInIndex] = currentUser;
    printf("Password berhasil diubah.\n\n");
}

int main()
{
    // Autentikasi User Login
    login();

    fillPetunjuk();
    petunjukAplikasi();
    displayMahasiswa();
    while (true) {
        printf("1. Tambah Data \n");
        printf("2. Ubah Data \n");
        printf("3. Hapus Data \n");
        printf("4. Keluar \n");
        printf("5. Urut berdasarkan Nama \n");
        printf("6. Urut berdasarkan NPM \n");
        printf("7. Cari berdasarkan Nama \n");
        printf("8. Cari berdasarkan NPM \n");
        printf("9. Clear Screen \n");
        printf("h. Ubah Password \n");
        printf("l. Logout \n");
        printf("i. Petunjuk Penggunaan \n");

        char choice;
        printf("Pilihan Anda: "); choice = getche();
        printf("\n\n");

        switch(choice) {
            case '1':
                tambahData();
                displayMahasiswa();
                break;

            case '2':
                ubahData();
                displayMahasiswa();
                break;

            case '3':
                hapusData();
                displayMahasiswa();
                break;

            case '4':
                return;

            case '5':
                urutBy("nama");
                displayMahasiswa();
                break;

            case '6':
                urutBy("npm");
                displayMahasiswa();
                break;

            case '7':
                searchBy("nama");
                break;

            case '8':
                searchBy("npm");
                break;

            case '9':
                system("cls");
                break;

            case 'i':
                petunjukAplikasi();
                break;

            case 'h':
                ubahPassword();
                break;

            case 'l':
                system("cls");
                login();
                break;

            default:
                printf("Pilihan tidak tersedia\n\n");
                break;
        }
    }
    return 0;
}
// End searching method
