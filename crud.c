#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define RESET           "\x1b[0m"

#define TEXT_BLACK        "\x1b[30m"
#define TEXT_RED          "\x1b[31m"
#define TEXT_GREEN        "\x1b[32m"
#define TEXT_YELLOW       "\x1b[33m"
#define TEXT_BLUE         "\x1b[34m"
#define TEXT_MAGENTA      "\x1b[35m"
#define TEXT_CYAN         "\x1b[36m"
#define TEXT_WHITE        "\x1b[37m"

#define BG_BLACK   "\x1b[40m"
#define BG_RED     "\x1b[41m"
#define BG_GREEN   "\x1b[42m"
#define BG_YELLOW  "\x1b[43m"
#define BG_BLUE    "\x1b[44m"
#define BG_MAGENTA "\x1b[45m"
#define BG_CYAN    "\x1b[46m"
#define BG_WHITE   "\x1b[47m"

#define TEXT_ITALIC       "\x1b[3m"
#define TEXT_BOLD         "\x1b[1m"
#define TEXT_UNDERLINE    "\x1b[4m"


// Struct Mahasiswa
struct Mahasiswa
{
    char *nam; // nama: 59
    char *nim; // nim: 12
    char *pro; // prodi: 59
    char *ema; // email: 74
    char *nhp; // no. hp: 17
};

// Array of struct Mahasiswa
struct Mahasiswa mhs[100];
int cnt_mhs = 0; // counter data yang tersimpan dalam array mhs
char *path = "data.txt"; // path file database


void pause();
void pauseClear();
void clearInputBuffer();
int isExist(const char *path);
void printHeader();
int menu();
int refreshData(const char *path);
void freeArray();
int addMahasiswa(const char *path, const char *nam, const char *nim, const char *pro, const char *ema, const char *nhp);
void getInput(const char *text, char *input, int size, char type);
void tambahData(const char *path);
int hapusMhs(const char *path);
void editMhs(const char *path);
void printMahasiswa();




int main()
{

    int choice;

    // Jika file yang dimaksud didalam variabel path tidak ditemukan, maka program keluar dengan kode 1;
    if (!isExist(path)) return 1;

    system("cls");
    printHeader();
    menu();
    freeArray();

    return 0;
}

/* Mengepause Program */
void pause() {
    printf("|!| ");
    system("pause");
}
/* Mengepause program dan membersihkan terminal */
void pauseClear() {
    pause();
    system("cls");
}

/* Menghapus / Membersihkan buffer dari input (stdin) */
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

/* Mengecek Apakah file yang dimaksud ada atau tidak */
int isExist(const char *path)
{
    FILE *file;
    if ((file = fopen(path, "r")))
    {
        fclose(file);
        return 1;
    }
    printf(TEXT_RED"|x| File not found\n"RESET);
    return 0;
}

/* Tampilan Header dari program */
void printHeader() {
    printf(BG_GREEN TEXT_WHITE TEXT_BOLD"|!|---------------------------------------------------------------------------------------------------------|!|\n");
    printf("|!|                                             PROGRAM DATABASE                                            |!|\n");
    printf("|!|                                              MAHASISWA USU                                              |!|\n");
    printf("|!|---------------------------------------------------------------------------------------------------------|!|\n" RESET);
    printf("\n");
}

/* Menampilkan Menu */
int menu()
{
    int choice;

    fflush(stdin);
    fflush(stdout);
    printf(TEXT_YELLOW"\n");
    printf("|i| Ini adalah program database mahasiswa.\n");
    printf("|i| Berikut adalah beberapa fitur dari program ini\n");
    printf("|i| 0. Keluar Program\n");
    printf("|i| 1. Tambahkan data baru\n");
    printf("|i| 2. Tampilkan Semua data\n");
    printf("|i| 3. Hapus data\n");
    printf("|i| 4. Edit data\n");
    printf("\n");
    printf("|!| Masukkan angka diatas sesuai yang anda inginkan\n");
    printf(TEXT_BOLD "|?| Pilihan: "RESET);
    int sken = scanf("%d", &choice);

    

    while (sken == 1)
    {
        refreshData(path); // Membersihkan semua elemen dalam array: mhs dan mengisinya ulang / merefresh, setiap kali user memilih
        switch (choice)
        {
        case 0:
            printf(TEXT_GREEN TEXT_ITALIC"\n|!| Program selesai, sampai jumpa lagi!\n" RESET);
            return 0;

        case 1:
            tambahData(path);
            break;

        case 2:
            printMahasiswa();
            break;
        case 3:
            hapusMhs(path);
            break;
        case 4:
            editMhs(path);
            break;

        default:
            printf(TEXT_RED"|x| Pilihan tidak ada, silahkan pilih dengan benar!\n"RESET);
            pauseClear();
            printHeader();
            return menu();
        }

        fflush(stdin);
        fflush(stdout);
        choice = menu();

    }

    clearInputBuffer();
    printf(TEXT_RED"|x| Format salah, hanya angka!\n"RESET);
    pauseClear();
    printHeader();
    return menu();

    


    return choice;
}

/* Membebaskan Alokasi memori yang digunakan dalam menyimpan data */
void freeArray()
{
    for (int i = 0; i < cnt_mhs; i++)
    {
        free(mhs[i].nam);
        free(mhs[i].nim);
        free(mhs[i].pro);
        free(mhs[i].ema);
        free(mhs[i].nhp);
    }
}

/* Me-refresh isi array mhs dengan membaca ulang file yang dimaksud */
int refreshData(const char *path)
{
    if (!isExist(path)) return 0;
    cnt_mhs = 0;

    char text[230];
    FILE *file;
    file = fopen(path, "r");

    while ((fgets(text, 230, file)) != NULL)
    {
        if (text[0] == '\n') continue;
            
        char *token = strtok(text, "|"); // Memisahkan string dengan delimiter: '|'; Contoh Format String: "Nama|NIM|Prodi|Email|No. HP"
        int i = 0;
        while (token != NULL)
        {
            switch (i)
            {
            case 0:
                mhs[cnt_mhs].nam = strdup(token);
                break;
            case 1:
                mhs[cnt_mhs].nim = strdup(token);
                break;
            case 2:
                mhs[cnt_mhs].pro = strdup(token);
                break;
            case 3:
                mhs[cnt_mhs].ema = strdup(token);
                break;
            case 4:
                token[strcspn(token, "\n")] = 0; // remove newline character
                mhs[cnt_mhs].nhp = strdup(token);
                break;
            
            default:
                break;
            }
            token = strtok(NULL, "|");
            i++;
        }
        cnt_mhs++;
    }

    fclose(file);

    return 1;
}

/* Menampilkan Isi dari Array: mhs */
void printMahasiswa() {
    pauseClear();
    printHeader();

    int i = 0;
    printf(BG_YELLOW TEXT_BLACK"+--+--------------------------+------------+-----------------------+--------------------------+---------------+\n");
    printf("|NO|                    Nama  |       NIM  |                Prodi  |                   Email  |       No. HP  |\n");
    printf("+--+--------------------------+------------+-----------------------+--------------------------+---------------+\n");
    for (i = 0; i < cnt_mhs; i++)
    {
        printf("|%2d|%26.26s|%12.12s|%23.23s|%26.26s|%15.15s|\n", i + 1, mhs[i].nam, mhs[i].nim, mhs[i].pro, mhs[i].ema, mhs[i].nhp);
    }
    printf("+--+--------------------------+------------+-----------------------+--------------------------+---------------+\n"RESET);
    pause();
}

/* Menambahkan data mahasiswa ke dalam file */
int addMahasiswa(const char *path, const char *nam, const char *nim, const char *pro, const char *ema, const char *nhp)
{
    if (!isExist(path)) return 0;

    FILE *file;
    file = fopen(path, "a");

    fprintf(file, "%s|%s|%s|%s|%s\n", nam, nim, pro, ema, nhp);

    fclose(file);

    return 1;
}

/* Fungsi meminta user meng-input string; dan mencegah semua kesalahan teknis dasar yang kemungkinan terjadi */
void getInput(const char *text, char *input, int size, char type)
{
    int overflow = 0;
    printf("%s", text); // Menampilkan text permintaan yang dimaksud: atau legenda

    fflush(stdin);
    fflush(stdout);
    fgets(input, size, stdin); // Input dari user

    // Membersihkan buffer input namun tidak membuat user harus menekan enter sebanyak 2x
    if (input[strlen(input) - 1] != '\n') {
        overflow = 1;
        clearInputBuffer();
    }
    input[strcspn(input, "\n")] = 0; // Membersihkan newline dengan mencari karakter \n didalam string dan mengubah posisinya ke: 0 (null terminator)
    
    switch (type) {
        case 'n': // Nama
        case 'p': //Prodi
            for (int j = 0; j < strlen(input); j++) {
                if (isdigit(input[j])) {
                    printf(TEXT_RED"|x| Tidak boleh mengandung angka! Silahkan coba lagi.\n"RESET);
                    return getInput(text, input, size, type);
                }
            }
            break;
        case 'i': // NIM
        case 't': // No. HP
            for (int j = 0; j < strlen(input); j++) {
                if (!isdigit(input[j])) {
                    printf(TEXT_RED"|x| Hanya boleh mengandung angka! Silahkan coba lagi.\n"RESET);
                    return getInput(text, input, size, type);
                }
            }
            break;
        case 'e': // Email
            if ((strchr(input, '@') == NULL) || (strchr(input, '.') == NULL)) {
                printf(TEXT_RED"|x| Format email salah! Silahkan coba lagi.\n"RESET);
                return getInput(text, input, size, type);
            }
            break;
    }

    if (overflow) {
        printf(TEXT_YELLOW"|!| Input terlalu panjang, hanya %d karakter yang akan diambil\n"RESET, size - 1);
    }

    // Jika input mengandung karakter '|', maka akan menampilkan pesan kesalahan dan meminta user untuk menginput ulang
    if (strchr(input, '|') != NULL)
    {
        printf("|x| Input tidak boleh mengandung karakter '|'. Silakan coba lagi.\n");
        return getInput(text, input, size, type);
    }

    // Jika text tidak kosong dan input kosong, maka akan menampilkan pesan kesalahan dan meminta user untuk menginput ulang
    if (strlen(text) != 0 && ((strlen(input) < 1) || input == " ")) {
        printf("|x| Input tidak boleh kosong! Silahkan coba lagi.\n");
        return getInput(text, input, size, type);
    }
}

/* Fungsi mengkonfirmasi */
int confirm(const char *text)
{
    char c;
    printf(TEXT_YELLOW"%s", text);
    printf(" (y/t): "RESET);
    scanf(" %c", &c);
    if (c != 'y' && c != 'Y' && c != 't' && c != 'T')
    {
        printf(TEXT_RED"|x| Masukkan tidak valid, coba lagi!\n"RESET);
        return confirm(text);
    }
    if (c == 'y' || c == 'Y') return 1;

    return 0;
}

/* Fungsi meminta data yang ingin ditambahkan kedalam database */
void tambahData(const char *path)
{
    pauseClear();
    char nam[60], nim[13], pro[60], ema[75], nhp[18];

    clearInputBuffer();
    printHeader();

    printf(TEXT_CYAN TEXT_UNDERLINE"|~| Menambahkan Data-Mahasiswa baru\n"RESET);
    printf(TEXT_CYAN"|i| Panjang maksimal: di dalam kurung siku\n\n"RESET);
    printf(TEXT_YELLOW"|!| Masukkan data mahasiswa:\n"RESET);
    getInput(TEXT_YELLOW"|?| Nama [59]: "RESET, nam, sizeof(nam), 'n');
    getInput(TEXT_YELLOW"|?| NIM [12]: "RESET, nim, sizeof(nim), 'i');
    getInput(TEXT_YELLOW"|?| Prodi [59]: "RESET, pro, sizeof(pro), 'p');
    getInput(TEXT_YELLOW"|?| Email [74]: "RESET, ema, sizeof(ema), 'e');
    getInput(TEXT_YELLOW"|?| No. HP [17]: "RESET, nhp, sizeof(nhp), 't');
    printf("\n");

    // Mengkonfirmasi data yang akan ditambahkan
    if (confirm("Apakah anda yakin ingin menambahkan data diatas?") != 1)
    {
        printf(TEXT_YELLOW"|~| Data tidak ditambahkan\n"RESET);
        return;
    }

    // Jika konfirmasi berhasil, maka data akan ditambahkan kedalam database
    if (addMahasiswa(path, nam, nim, pro, ema, nhp)) {
        printf(TEXT_GREEN"|!| Data berhasil ditambahkan\n"RESET);
    } else { // Jika gagal, maka akan menampilkan pesan kesalahan
        printf(TEXT_RED"|x| Data gagal ditambahkan, silahkan coba lagi!\n"RESET);
    }
    pause();
}


/* Fungsi menghapus data mahasiswa dengan meminta NIM sebagai keyword pencari */
int hapusMhs(const char *path)
{
    char nim[13];
    int i;

    clearInputBuffer();
    pauseClear();
    printHeader();

    printf(TEXT_BOLD TEXT_RED TEXT_UNDERLINE"|~| Hapus Data Mahasiswa\n" RESET);
    getInput(TEXT_YELLOW "|?| NIM: " RESET, nim, 15, 'i');
    printf(TEXT_ITALIC"|~| Mencari...\n"RESET);

    // Mencari data mahasiswa dengan NIM yang dimaksud dengan mengecek 1 per 1 data yang ada dalam array mhs
    for (i = 0; i < cnt_mhs; i++)
    {
        if (strcmp(mhs[i].nim, nim) == 0)
            break; // Jika data ditemukan, maka akan keluar dari loop dengan i adalah index dari data yang dimaksud
    }

    pause();
    if (i == cnt_mhs) // Jika i == cnt_mhs, maka data tidak ditemukan
    {
        printf(TEXT_RED"|!| Data tidak ditemukan\n"RESET);
        return 0;
    }

    printf(TEXT_GREEN"\n|!| Data ditemukan, dengan:\n"RESET);
    printf(TEXT_CYAN TEXT_BOLD"|i| Nama: %s\n", mhs[i].nam);
    printf("|i| Nim: %s\n"RESET, mhs[i].nim);

    // Mengkonfirmasi apakah data yang dimaksud akan dihapus atau tidak
    if (confirm("Apakah anda yakin ingin menghapus data diatas?") != 1)
    {
        printf(TEXT_YELLOW"|~| Data tidak dihapus\n"RESET);
        return 0;
    }

    // Jika konfirmasi berhasil, maka data akan dihapus dari database
    // Data yang dimaksud tidak akan ditulis kedalam file
    // Data lainnya akan tetap ditulis kedalam file
    FILE *file;
    file = fopen(path, "w");

    for (int j = 0; j < cnt_mhs; j++)
    {
        if (j == i) continue; // Data yang dimaksud tidak akan ditulis kedalam file
        
        fprintf(file, "%s|%s|%s|%s|%s\n", mhs[j].nam, mhs[j].nim, mhs[j].pro, mhs[j].ema, mhs[j].nhp);
    }

    printf(TEXT_GREEN"|!| Data berhasil dihapus!\n"RESET);

    fclose(file);

    return 1;
}

/* Fungsi meng-edit data mahasiswa dengan meminta NIM sebagai keyword pencari; NIM tidak dapat diubah */
void editMhs(const char *path)
{
    char nim[13];
    int i;

    clearInputBuffer();
    pauseClear();
    printHeader();

    printf(TEXT_BOLD TEXT_YELLOW TEXT_UNDERLINE"|~| Edit Data Mahasiswa\n" RESET);
    printf(TEXT_YELLOW"|i| kosongkan input jika tidak ingin mengubah suatu data\n\n" RESET);
    getInput(TEXT_YELLOW "|?| NIM: " RESET, nim, 15, 'i');
    printf(TEXT_ITALIC"|~| Mencari...\n"RESET);

    // Mencari data mahasiswa dengan NIM yang dimaksud dengan mengecek 1 per 1 data yang ada dalam array mhs
    for (i = 0; i < cnt_mhs; i++)
    {
        if (strcmp(mhs[i].nim, nim) == 0) // Jika data ditemukan, maka akan keluar dari loop dengan i adalah index dari data yang dimaksud
        {
            break;
        }
    }
    pause();

    // Jika data tidak ditemukan, maka akan menampilkan pesan kesalahan
    if (i == cnt_mhs)
    {
        printf(TEXT_RED"|!| Data tidak ditemukan\n"RESET);
        return;
    }

    // Meminta data baru yang akan diubah
    char nam[60], pro[60], ema[75], nhp[18];


    printf(TEXT_YELLOW"|?| Nama (%s): "RESET, mhs[i].nam);
    getInput("", nam, 60, 'n');
    strlen(nam) == 0 ? strcpy(nam, mhs[i].nam) : 0;

    printf(TEXT_YELLOW"|?| Prodi (%s): "RESET, mhs[i].pro);
    getInput("", pro, 60, 'p');
    strlen(pro) == 0 ? strcpy(pro, mhs[i].pro) : 0;

    printf(TEXT_YELLOW"|?| Email (%s): "RESET, mhs[i].ema);
    getInput("", ema, 75, 'e');
    strlen(ema) == 0 ? strcpy(ema, mhs[i].ema) : 0;

    printf(TEXT_YELLOW"|?| No. HP (%s): "RESET, mhs[i].nhp);
    getInput("", nhp, 18, 't');
    strlen(nhp) == 0 ? strcpy(nhp, mhs[i].nhp) : 0;

    printf("\n");
    // Mengkonfirmasi data yang akan diubah
    if (confirm("Apakah anda yakin ingin mengubah data ini?") != 1)
    {
        printf(TEXT_YELLOW"|~| Data tidak diubah\n"RESET);
        return;
    }

    // Jika konfirmasi berhasil, maka data akan diubah dalam database
    FILE *file;
    file = fopen(path, "w");

    // Mengubah data dengan menulis ulang data yang ada dalam file
    // Dan ketika counter: j sama dengan i, yaitu data yang dimaksud, maka data yang akan diubah akan ditulis ulang
    // Data lainnya akan tetap ditulis kedalam file tanpa perubahan
    for (int j = 0; j < cnt_mhs; j++)
    {
        if (j == i)
        {
            fprintf(file, "%s|%s|%s|%s|%s\n", nam, mhs[j].nim, pro, ema, nhp); // Data yang diubah
        }
        else
        {
            fprintf(file, "%s|%s|%s|%s|%s\n", mhs[j].nam, mhs[j].nim, mhs[j].pro, mhs[j].ema, mhs[j].nhp);
        }
    }

    printf(TEXT_GREEN"|!| Data berhasil diedit!\n"RESET);

    fclose(file);
}

