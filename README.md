# Hastane-Acil-Servis-Uygulamas-
Hasta kayıtları HL7 formatında tutulmuştur.
HL7 Hasta Kayıt Sistemi
Bu proje, acil servis ortamında hasta kayıtlarını HL7 (Health Level 7) standardında yönetmek için geliştirilmiş bir C uygulamasıdır. Sistem, hasta kaydı, triyaj, müdahale ve taburculuk süreçlerini içerir ve tüm bu bilgileri uluslararası sağlık veri standardı olan HL7 formatında saklar.
📋 Özellikler

Hasta kimlik bilgilerinin (TC Kimlik, İsim, Soyisim, Yaş) kaydedilmesi
Triyaj değerlendirmesi ve aciliyet durumu atama (KIRMIZI, SARI, YEŞİL)
Aciliyet durumuna göre müdahale yönlendirmesi
Taburculuk veya hastane yatış işlemleri
Tüm hasta verilerinin HL7 v2.x formatında kaydedilmesi
Dosya tabanlı HL7 mesaj depolama

🔍 Sistem Akış Şeması
Sistemin çalışma mantığı aşağıdaki akış şemasında gösterilmiştir:
Show Image
💻 Kurulum
Gereksinimler

GCC veya uyumlu bir C derleyicisi
Standard C kütüphanesi

Derleme
Projeyi derlemek için terminal/komut istemcisine aşağıdaki komutu yazın:
bashCopygcc -o hasta_kayit_sistemi hl7_hasta_kayit.c
Çalıştırma
Programı çalıştırmak için:
bashCopy./hasta_kayit_sistemi
🚀 Kullanım

Program başladığında kaç hasta kaydedileceğini girin
Her hasta için sırasıyla:

TC kimlik numarası, isim, soyisim ve yaş bilgilerini girin
Triyaj durumunu belirtin (1: Evet, 0: Hayır)
Aciliyet durumunu seçin (1: KIRMIZI, 2: SARI, 3: YEŞİL)
Taburculuk veya yatış kararını belirtin (1: Taburcu, 0: Yatış)


Program tüm hastaları işledikten sonra "hastalar_hl7.txt" dosyasına HL7 formatında kayıtları oluşturur

📝 HL7 Format Açıklaması
HL7 (Health Level Seven), sağlık bilgi sistemleri arasında veri alışverişi için standart bir protokoldür. Bu projede HL7 v2.x formatı kullanılmaktadır. Oluşturulan HL7 mesajları şu segmentleri içerir:

MSH: Mesaj başlığı segmenti

Gönderen ve alıcı sistem bilgileri
Zaman damgası
Mesaj tipi (ADT^A01: Hasta kabul)


PID: Hasta kimlik segmenti

TC kimlik numarası
İsim ve soyisim
Yaş


PV1: Hasta ziyaret segmenti

Aciliyet durumu
Taburcu/yatış bilgisi


OBX: Gözlem/Triyaj sonuç segmenti

Triyaj sonucu (KIRMIZI/SARI/YEŞİL)



Örnek HL7 mesajı:
CopyMSH|^~\&|ACIL_SERVIS|HASTANE|HIS|HASTANE|20250315123045||ADT^A01|12345678901|P|2.5.1
PID|||12345678901||Ahmet^Yilmaz||35|
PV1||E|KIRMIZI|||||||||||||TABURCU||
OBX|1|ST|TRIYAJ^Triyaj Durumu||KIRMIZI|
🏗️ Kod Yapısı
Proje, aşağıdaki temel bileşenlerden oluşmaktadır:

Veri Yapıları:

AciliyetDurumu: Hasta aciliyet durumlarını sınıflandıran enum
Hasta: Hasta bilgilerini tutan yapı


Temel Fonksiyonlar:

hastaKayitIslemi(): Hasta bilgilerini alır
triyajYap(): Triyaj değerlendirmesi yapar
mudahaleEt(): Aciliyet durumuna göre müdahale sürecini başlatır
taburculukVeyaYatis(): Taburcu veya yatış işlemini gerçekleştirir


HL7 İşleme Fonksiyonları:

hl7MesajiOlustur(): HL7 formatında mesaj oluşturur
hl7MesajiKaydet(): HL7 mesajını dosyaya kaydeder
hl7DosyasinaYaz(): Dosya yazma işlemlerini gerçekleştirir
guncelZamaniAl(): HL7 formatında zaman damgası oluşturur


🔄 Veri Akışı

Hasta bilgileri kullanıcıdan alınır
Triyaj ve aciliyet durumu belirlenir
Müdahale süreci yönetilir
Taburculuk veya yatış kararı verilir
Tüm bilgiler HL7 formatında yapılandırılır
HL7 mesajı "hastalar_hl7.txt" dosyasına kaydedilir

Sistem Akış Şeması
file:///C:/Users/Selma/Downloads/Yaz%C4%B1l%C4%B1m/Veri%20Yap%C4%B1lar%C4%B1%20Ve%20Algoritmalar/Hastane%20Acil%20Servis%20Sistemi%20Ak%C4%B1%C5%9F%20%C5%9Eemas%C4%B1%205240505030drawio.html

📈 Geliştirme Potansiyeli

Veritabanı entegrasyonu
Gerçek zamanlı HL7 mesaj iletimi
Web tabanlı arayüz
HL7 FHIR formatı desteği
İstatistiksel raporlama özellikleri

📄 Lisans
Bu proje MIT Lisansı altında lisanslanmıştır.
