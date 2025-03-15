#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Hasta durumlarını tanımlama
typedef enum {
    KIRMIZI = 1, // En acil
    SARI = 2,    // Acil
    YESIL = 3    // Acil değil
} AciliyetDurumu;

// Hasta bilgilerini tutan yapı
typedef struct {
    char isim[50];
    char soyisim[50];
    int yas;
    char tcKimlik[12];     // TC kimlik numarasını string olarak tutmak
    int triyajDurumu;
    AciliyetDurumu aciliyetDurumu;
    int kayitYapildi;
    int tedaviBasladi;
    int taburcu;
    char kayitZamani[20];  // Kayıt zamanını tutmak için
    char hl7Mesaji[1024];  // HL7 mesajını tutmak için
} Hasta;

// Fonksiyon prototipleri
void triyajYap(Hasta* hasta);
void mudahaleEt(Hasta* hasta);
void hastaKayitIslemi(Hasta* hasta);
void taburculukVeyaYatis(Hasta* hasta);
void hl7MesajiOlustur(Hasta* hasta);
void hl7MesajiKaydet(Hasta* hasta, const char* dosyaAdi);
void hl7DosyasinaYaz(const char* mesaj, const char* dosyaAdi);
void guncelZamaniAl(char* zamanDizisi);

int main() {
    int hastaSayisi;
    printf("Kac hasta kaydedilecek? ");
    scanf("%d", &hastaSayisi);

    Hasta* hastalar = (Hasta*)malloc(hastaSayisi * sizeof(Hasta));
    
    if (hastalar == NULL) {
        printf("Bellek tahsis edilemedi!\n");
        return 1;
    }

    int i;
    // Hasta bilgilerini girme
    for (i = 0; i < hastaSayisi; i++) {
        printf("\n--- Hasta %d Bilgilerini Giriniz ---\n", i + 1);
        hastaKayitIslemi(&hastalar[i]);  // Kayıt işlemi
        triyajYap(&hastalar[i]);        // Triyaj işlemi
        mudahaleEt(&hastalar[i]);       // Müdahale işlemi
        taburculukVeyaYatis(&hastalar[i]); // Taburculuk veya yatış işlemi
        
        // HL7 mesajı oluşturup dosyaya kaydet
        hl7MesajiOlustur(&hastalar[i]);
        hl7MesajiKaydet(&hastalar[i], "hastalar_hl7.txt");
    }

    printf("\n=== Tum Sürecler Tamamlandi ===\n");
    printf("HL7 mesajlari 'hastalar_hl7.txt' dosyasina kaydedildi.\n");

    free(hastalar);
    return 0;
}

// Hasta kayıt işlemi
void hastaKayitIslemi(Hasta* hasta) {
    printf("Hastanin TC kimlik numarasini giriniz: ");
    scanf("%s", hasta->tcKimlik);

    printf("Hastanin ismini giriniz: ");
    scanf("%s", hasta->isim);

    printf("Hastanin soyismini giriniz: ");
    scanf("%s", hasta->soyisim);

    printf("Hastanin yasini giriniz: ");
    scanf("%d", &hasta->yas);

    hasta->kayitYapildi = 1;
    
    // Kayıt zamanını al
    guncelZamaniAl(hasta->kayitZamani);
    
    printf("Hasta %s icin kayit islemi tamamlandi.\n", hasta->tcKimlik);
}

// Triyaj işlemi
void triyajYap(Hasta* hasta) {
    printf("Hasta %s icin triyaj yapildi mi? (1: Evet, 0: Hayir): ", hasta->tcKimlik);
    scanf("%d", &hasta->triyajDurumu);

    if (hasta->triyajDurumu == 1) {
        printf("Triyaj yapılmıstır.\n");

        printf("Aciliyet durumunu secin (1: KIRMIZI, 2: SARI, 3: YESIL): ");
        int aciliyet;
        scanf("%d", &aciliyet);
        hasta->aciliyetDurumu = aciliyet;

        const char* aciliyetStr;
        switch (hasta->aciliyetDurumu) {
            case KIRMIZI: aciliyetStr = "KIRMIZI (En Acil)"; break;
            case SARI: aciliyetStr = "SARI (Acil)"; break;
            case YESIL: aciliyetStr = "YESIL (Acil Degil)"; break;
            default: aciliyetStr = "Bilinmiyor"; break;
        }

        printf("Hasta %s icin aciliyet durumu: %s\n", hasta->tcKimlik, aciliyetStr);
    } else {
        printf("Lutfen hastayi acilde gorevli doktora yonlendiriniz.\n");
    }
}

// Aciliyet durumuna göre müdahale
void mudahaleEt(Hasta* hasta) {
    printf("Hasta %s icin mudahale sureci basliyor...\n", hasta->tcKimlik);

    switch (hasta->aciliyetDurumu) {
        case KIRMIZI:
            printf("KIRMIZI Alan: Hasta icin hemen mudahale ediliyor!\n");
            break;
        case SARI:
            printf("SARI Alan: Hasta icin kisa surede mudahale edilecek.\n");
            break;
        case YESIL:
            printf("YESIL Alan: Hasta bekleme odasina alindi.\n");
            printf("Hasta sirasini bekliyor...\n");
            break;
        default:
            printf("Bilinmeyen aciliyet durumu!\n");
            break;
    }
}

// Taburculuk veya yatış işlemi
void taburculukVeyaYatis(Hasta* hasta) {
    int karar;
    printf("Hasta taburcu mu olacak yoksa hastaneye mi yatacak? (1: Taburcu, 0: Yatıs): ");
    scanf("%d", &karar);

    if (karar == 1) {
        printf("Hasta %s taburcu edildi.\n", hasta->tcKimlik);
        hasta->taburcu = 1;
    } else if (karar == 0) {
        printf("Hasta %s hastaneye yatirildi.\n", hasta->tcKimlik);
    } else {
        printf("Yanlis bir islem gerceklestirildi.\n");
    }

    printf("Hasta %s icin surec tamamlandi.\n", hasta->tcKimlik);
}

// HL7 mesajı oluşturma
void hl7MesajiOlustur(Hasta* hasta) {
    char aciliyetStr[20];
    switch (hasta->aciliyetDurumu) {
        case KIRMIZI: strcpy(aciliyetStr, "KIRMIZI"); break;
        case SARI: strcpy(aciliyetStr, "SARI"); break;
        case YESIL: strcpy(aciliyetStr, "YESIL"); break;
        default: strcpy(aciliyetStr, "Bilinmiyor"); break;
    }

    char taburcuStr[10];
    if (hasta->taburcu) {
        strcpy(taburcuStr, "TABURCU");
    } else {
        strcpy(taburcuStr, "YATIS");
    }

    // HL7 v2.x formatında MSH, PID, PV1 segmentlerini oluştur
    // MSH segmenti (Mesaj başlığı)
    char msh[256];
    sprintf(msh, "MSH|^~\\&|ACIL_SERVIS|HASTANE|HIS|HASTANE|%s||ADT^A01|%s|P|2.5.1", 
            hasta->kayitZamani, hasta->tcKimlik);

    // PID segmenti (Hasta kimlik bilgileri)
    char pid[256];
    sprintf(pid, "PID|||%s||%s^%s||%d|", 
            hasta->tcKimlik, hasta->isim, hasta->soyisim, hasta->yas);

    // PV1 segmenti (Hasta ziyaret bilgileri)
    char pv1[256];
    sprintf(pv1, "PV1||E|%s|||||||||||||%s||", 
            aciliyetStr, taburcuStr);

    // OBX segmenti (Gözlem bilgileri)
    char obx[256];
    sprintf(obx, "OBX|1|ST|TRIYAJ^Triyaj Durumu||%s|", aciliyetStr);

    // HL7 mesajını birleştir
    sprintf(hasta->hl7Mesaji, "%s\r%s\r%s\r%s", msh, pid, pv1, obx);
}

// HL7 mesajını dosyaya kaydet
void hl7MesajiKaydet(Hasta* hasta, const char* dosyaAdi) {
    hl7DosyasinaYaz(hasta->hl7Mesaji, dosyaAdi);
}

// HL7 mesajını dosyaya yazdır
void hl7DosyasinaYaz(const char* mesaj, const char* dosyaAdi) {
    FILE* dosya = fopen(dosyaAdi, "a"); // Dosya açma (ekleme modunda)
    
    if (dosya == NULL) {
        printf("Dosya acilamadi!\n");
        return;
    }
    
    fprintf(dosya, "%s\n\n", mesaj); // Mesajı dosyaya yaz
    fclose(dosya); // Dosyayı kapat
}

// Şu anki zamanı al
void guncelZamaniAl(char* zamanDizisi) {
    time_t t = time(NULL);
    struct tm* tm = localtime(&t);
    
    // HL7 zaman formatı: YYYYMMDDHHMMSS
    strftime(zamanDizisi, 20, "%Y%m%d%H%M%S", tm);
}
