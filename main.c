#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_UZUNLUK 100
#define MAX_HASTA 100
#define MAX_DOKTOR 100
// hasta ve doktor struct verisi
typedef struct {
    char TC[12];
    char isim[50];
    int hastaID;
    char sikayet[255];
    char tani[255];
}Hasta;

typedef struct {
    char ad[50];
    char kullaniciAdi[20];
    char parola[20];
}Doktor;

Hasta hasta[MAX_HASTA];
Doktor doktor[MAX_DOKTOR];
int hasta_sirasi = 0;
int doktor_sirasi = 0;

// ilaç struct verisi

typedef struct {
    char ad[50];
}Ilac;

Ilac tumIlac[MAX_UZUNLUK];
Ilac receteYazilmişIlac[MAX_UZUNLUK];
int tumIlac_sirasi = 0;
int receteYazilmişIlacSirasi = 0;

//fonksiyonlar
void anaMenu();
void adminMenu();
void doktorMenu(const char* doktorAd);
void doktorKayit();
void hastaKayit();
void hastaTani();
void hastaListe();
void ilacEkle();
void ilacReceteYazdir();
void HL7mesajOlustur(Hasta  h,char *mesaj);
void mevcutZamaniAl(char *tampon);
int receteNumarasiUret();
void tumIlacListe();

int main(void){
    anaMenu();
    return 0;
}

// anamenü fonksiyonu
void anaMenu() {
    char kullaniciAdi[20];
    char parola[20];

    while(1) {
        printf("Kullanici Adı: ");
        scanf("%s", kullaniciAdi);
        printf("Parola: ");
        scanf("%s", parola);

        if(strcmp (kullaniciAdi, "admin") == 0 && strcmp (parola, "admin123") == 0 ) {
            adminMenu();
        } else {
            int bulundu = 0;
            for (int i = 0; i < doktor_sirasi; i++) {
                if (strcmp(doktor[i].kullaniciAdi, kullaniciAdi) == 0 && strcmp(doktor[i].parola, parola) == 0) {
                    doktorMenu(doktor[i].ad);
                    bulundu = 1;
                    break;
                }
            }
            if(!bulundu) {
                printf("Gecersiz giris!");
            }
        }
    }
}

void adminMenu() {
    int tercih;

    do {
        printf("\n--- Admin Menu ---\n");
        printf("1. Doktor Kaydet\n");
        printf("2. Hasta Kaydet\n");
        printf("3. Ilac Ekle\n");
        printf("4. Ana Menuye Don\n");
        printf("Seciminiz: ");
        scanf("%d", &tercih);

        switch (tercih) {
            case 1:
                doktorKayit();
            break;
            case 2:
                hastaKayit();
            break;
            case 3:
                ilacEkle();
            break;
            case 4:
                printf("ana menuye donuluyor");
            break;
            default:
                printf("Gecersiz giris!");
        }
    } while (tercih != 4);
}

void doktorMenu(const char* doktorAd) {
    printf("Hos geldiniz, Dr. %s\n",doktorAd);
    int tercih;
    do {
        printf("\n--- Doktor Menu ---\n");
        printf("1. Mevcut Hastalari Listele\n");
        printf("2. Hasta Kaydet\n");
        printf("3. Hasta Teshis\n");
        printf("4. Recete Yaz\n");
        printf("5. Ana Menuye Don\n");
        printf("Seciminiz: ");
        scanf("%d", &tercih);

        switch (tercih) {
            case 1:
                hastaListe();
                break;
            case 2:
                hastaKayit();
                break;
            case 3:
                hastaTani();
                break;
            case 4:
                ilacReceteYazdir();
                break;
            case 5:
                printf("ana menuye donuluyor");
                break;
            default:
                printf("Gecersiz secim!");
        }
    }while (tercih != 5);
}

void doktorKayit() {

    Doktor d;

    printf("Doktor adi: ");
    scanf("%s", d.ad);
    printf("Doktor kullanici adi: ");
    scanf("%s", d.kullaniciAdi);
    printf("Doktor sifre: ");
    scanf("%s", d.parola);

    doktor[doktor_sirasi] =  d;
    doktor_sirasi++;

    printf("Doktor %s basariyla kaydedildi.\n", d.ad);
}

void hastaKayit() {
    Hasta p;
    printf("TC kimlik no : ");
    scanf("%s",p.TC);
    printf("Hasta adi: ");
    scanf("%s",p.isim);
    p.hastaID = doktor_sirasi + 1;
    hasta[hasta_sirasi] = p;
    hasta_sirasi++;

    char HL7mesaj[1024];
    HL7mesajOlustur(p, HL7mesaj);
    printf("Hasta %s basariyla kaydedildi. Hasta numarasi: %d\n", p.isim, p.hastaID);
    printf("HL7 mesaji : \n %s",HL7mesaj);
}

void hastaTani() {
    int hastaID;
    printf("Teshis edileecek hastanin ID numarasi : ");
    scanf("%d", &hastaID);

    for (int i = 0; i < hasta_sirasi; i++) {
        if (hasta[i].hastaID == hastaID) {
            printf("Hasta adi: %s\n", hasta[i].isim);
            printf("Hasta sikayeti: ");
            scanf(" %[^\n]", hasta[i].sikayet);
            printf("Doktor gorusu: ");
            scanf(" %[^\n]", hasta[i].tani);
            printf("Sikayet ve gorus basariyla kaydedildi.\n");
            return;
        }
    }
    printf("hasta bulunamadi! ");
}

void hastaListe() {
    printf("----------Mevcut Hastalar------------------");
    for (int i = 0; i < hasta_sirasi; i++) {
        printf("HastaID:%d ,Ad:%s ,TC:%s \n",hasta[i].hastaID,hasta[i].isim,hasta[i].TC);
    }
    printf("\n");
}

void ilacEkle() {
    printf("Tum ilaclar listesine ekleneek ilacin adi: ");
    scanf("%s",tumIlac[tumIlac_sirasi].ad);
    tumIlac_sirasi++;
    printf("Ilac basariyla eklendi.");

}

void tumIlacListe() {
    for (int i = 0; i < tumIlac_sirasi; i++) {
        printf("%d. ilac: %s \n",i+1,tumIlac[i].ad);
    }
}

void ilacReceteYazdir() {
    int hastaID;
    printf("recete yazdirilacak hastanin ID numarası: ");
    scanf("%d", &hastaID);

    for (int i = 0; i < hasta_sirasi; i++) {
        if (hasta[i].hastaID == hastaID) {
            printf("Hasta adi: %s\n", hasta[i].isim);
            printf("hasta sikayeti: %s\n",hasta[i].sikayet);
            printf("Doktor gorusu: %s\n", hasta[i].tani);

            int  receteNo = receteNumarasiUret();
            printf("receteNumarasiUret: %d\n", receteNo);

            tumIlacListe();

            char ilacAdi[50];
            printf("hastaya verilecek ilac adi: ");
            scanf("%s",ilacAdi);

            for (int j = 0; j < hasta_sirasi; j++) {
                if (strcmp(tumIlac[j].ad, ilacAdi) == 0) {
                    receteYazilmişIlac[receteYazilmişIlacSirasi] = tumIlac[j];
                    receteYazilmişIlacSirasi++;
                    printf("ilac basariyla receeye eklendi");
                    return;
                }
            }
            printf("ilac bulunamadi.");
            return;
        }

    }
    printf("hasta bulunamadi.");
}

int receteNumarasiUret() {
    return rand() % 1000000; //0 ie 999999 arası sayı üretmesi için.
}

void mevcutZamaniAl(char *tampon) {
    time_t saf_zaman;
    struct tm* zamanBilgisi;
    time(&saf_zaman);
    zamanBilgisi = localtime(&saf_zaman);
    strftime(tampon, 20, "%Y%m%d%H%M%S", zamanBilgisi);
}

void HL7mesajOlustur(Hasta  p,char *mesaj) {
    char simdikiZaman[20];
    mevcutZamaniAl(simdikiZaman);

    sprintf(mesaj, "MSH|^~\\&|HastaneSistemi|Hastane|MerkeziSistem|SaglikBakanligi|%s||ADT^A01|%d|P|2.3\n"
        "EVN|A01|%s\n"
        "PID|||%d^^^TC^MR||%s||19700101|M|||123 Sokak^Istanbul^^^12345||(555)555-5555|||M||%d^^^TC^MR\n"
        "PV1||I|Acil^Oda1^1|\n", simdikiZaman, p.hastaID, simdikiZaman, p.hastaID, p.isim, p.hastaID);
}
