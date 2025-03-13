# Acil_Servis_Sistemi

Bu proje, bir hastane yönetim sistemini oluşturmayı amaçlamaktadır. Sistem, hastane içerisinde hasta ve doktor kayıtlarını tutar, teşhis koyma sürecini yönetir, reçete oluşturur ve HL7 formatında mesajlar üretir.

## Özellikler

- **Admin Paneli:** Doktor ve hasta kayıt işlemlerini yönetme.
- **Doktor Paneli:** Hastaları listeleme, teşhis koyma ve reçete yazma işlemleri.
- **Hasta Yönetimi:** Hasta bilgilerini kayıt altına alma ve güncelleme.
- **İlaç Yönetimi:** Sisteme yeni ilaç ekleme ve reçetelere ilaç ekleyebilme.
- **HL7 Mesaj Desteği:** Hasta kayıt işlemleri için HL7 formatında mesaj oluşturma.

## Kullanılan Teknolojiler

- **Programlama Dili:** C
- **Kütüphaneler:** stdio.h, stdlib.h, time.h, string.h

## Kurulum

1. Bilgisayarınızda bir C derleyicisinin (örneğin GCC) kurulu olduğundan emin olun.
2. Proje dosyasını indirin.
3. Terminal veya komut satırını açarak aşağıdaki komutu kullanarak projeyi derleyin:
   ```bash
   gcc -o hastane_yonetim hastane_yonetim.c
   ```
4. Programı çalıştırmak için şu komutu girin:
   ```bash
   ./hastane_yonetim
   ```

## Kullanım

### Giriş Ekranı

- **Admin Girişi:** `Kullanıcı Adı: admin, Parola: admin123`
- **Doktor Girişi:** Doktorlar, kendi kullanıcı adı ve şifreleriyle sisteme giriş yapabilir.

### Admin İşlemleri

- Doktor ekleyebilir ve bilgilerini yönetebilir.
- Hasta kaydı yapabilir.
- Sisteme yeni ilaç ekleyebilir.

### Doktor İşlemleri

- Kayıtlı hastaları listeleyebilir.
- Yeni hasta kaydı yapabilir.
- Hastalara teşhis koyabilir.
- Reçete yazabilir.

## Fonksiyonlar

| Fonksiyon              | Açıklama                                               |
| ---------------------- | ------------------------------------------------------ |
| `anaMenu()`            | Kullanıcı giriş ekranını yönetir.                      |
| `adminMenu()`          | Admin işlemlerini yönetir.                             |
| `doktorMenu()`         | Doktor işlemlerini yönetir.                            |
| `doktorKayit()`        | Yeni doktor kaydı yapar.                               |
| `hastaKayit()`         | Yeni hasta kaydı yapar ve HL7 mesajı oluşturur.        |
| `hastaTani()`          | Hastalara teşhis koyar.                                |
| `hastaListe()`         | Kayıtlı hastaları listeler.                            |
| `ilacEkle()`           | Yeni ilaç ekler.                                       |
| `ilacReceteYazdir()`   | Hastaya reçete yazar.                                  |
| `tumIlacListe()`       | Kayıtlı ilaçları listeler.                             |
| `HL7mesajOlustur()`    | Hasta bilgilerine göre HL7 formatında mesaj oluşturur. |
| `mevcutZamaniAl()`     | Sistemin mevcut zamanını alır.                         |
| `receteNumarasiUret()` | Rastgele reçete numarası üretir.                       |

## Sistem Akış Diyagramı

Aşağıda, sistemin işleyişini gösteren bir akış diyagramı bulunmaktadır:

![Ekran görüntüsü 2025-03-14 003017](https://github.com/user-attachments/assets/05ac0c13-d934-46b8-b956-fce3ebd98402)



## HL7 Sistemi Gösterimi

HL7 (Health Level 7), sağlık bilişimi alanında yaygın olarak kullanılan bir veri değişim standardıdır. Hasta bilgileri, teşhisler ve tedavi süreçleri hakkında veri paylaşımını kolaylaştırmak için geliştirilmiştir. HL7 mesajları, belirli veri segmentlerinden oluşur ve her segment, farklı bir bilgi içerir. Örnek bir HL7 mesajı aşağıda verilmiştir:

```
MSH|^~\&|HastaneSistemi|HastaVeriMerkezi|LAB|Hastane|20250314||ADT^A01|MSG00001|P|2.5
PID|1||123456^^^HastaneMRN||Ahmet^Yılmaz||19850101|M|||Ankara, Türkiye||||||
PV1|1|I|Servis1^Oda12^Yatak3||||12345^Dr. Kaya|||||||||||20250314
```

Yukarıdaki mesaj, bir hastanın hastaneye kabul işlemi için oluşturulmuş bir **ADT (Admit, Discharge, Transfer)** mesajıdır.

## Gelecek Güncellemeler

- Hasta geçmişi kayıtlarının tutulması
- Daha kullanıcı dostu bir arayüz geliştirilmesi
- Veritabanı entegrasyonu







