### Basit Bir C Web Sunucusu
Bu proje, C programlama dili kullanarak basit bir web sunucusu uygulamasını içerir. Sunucu, HTTP protokolünü kullanarak istemcilere istekleri karşılama ve dosya içeriğini yanıt olarak gönderme yeteneğine sahiptir.

### Özellikler
HTTP GET isteklerini kabul eder.
İstemcilere statik dosyaları (örneğin HTML dosyaları, resimler, css dosyaları) yanıt olarak gönderir.
Sunucu, çoklu istemcilere hizmet vermek üzere tasarlanmıştır.

### Kullanım

Sunucuyu başlatmak için:

```bash
make
```

Tarayıcınızda http://localhost:8080 adresine giderek sunucunun çalıştığını doğrulayabilirsiniz.

### Gereksinimler
C derleyicisi (gcc gibi)
GNU Make aracı


******************************************************************************************


Bu proje sadece bir örnektir. Gelişmiş bir web server yazmak daha karmaşık bir yapı ister.
