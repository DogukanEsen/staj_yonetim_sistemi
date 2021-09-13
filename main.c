#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>

//Staj hesaplama bak pointer.
typedef struct{
char ad[15];
char soyad[15];
int no;
}ogrenci;

typedef struct{
char isim[15];
char faaliyet_alani[15];
int vergi_no;
}firma;

typedef struct{
int donanim;
int yazilim;
int no;
int vergi_no;
}staj;

int ogrenci_islemleri(ogrenci ogrenciler[], int toplam_ogrenci);
int ogrenci_ekleme(ogrenci ogrenciler[], int toplam_ogrenci);
int ogrenci_duzenleme(ogrenci ogrenciler[], int toplam_ogrenci);
int ad_degistirme(int no, ogrenci ogrenciler[], int sayac);
int soyad_degistirme(int no, ogrenci ogrenciler[], int sayac);
int ogrenci_silme(ogrenci ogrenciler[], int toplam_ogrenci);
int ogrenci_listeleme(ogrenci ogrenciler[], int toplam_ogrenci);

int firma_islemleri(firma firmalar[], int toplam_firma);
int firma_ekleme(firma firmalar[], int toplam_firma);
int firma_duzenleme(firma firmalar[], int toplam_firma);
int firma_isim_degistirme(int no, firma firmalar[], int sayac);
int firma_faaliyet_alani_degistirme(int no, firma firmalar[], int sayac);
int firma_silme(firma firmalar[], int toplam_firma);
int firma_listeleme(firma firmalar[], int toplam_firma);

int staj_islemleri(ogrenci ogrenciler[], int toplam_ogrenci, firma firmalar[], int toplam_firma, staj stajlar[], int toplam_staj);
int staj_ekleme(ogrenci ogrenciler[], int toplam_ogrenci, firma firmalar[], int toplam_firma, staj stajlar[], int toplam_staj);
int tamamlanmis_staj_liste(staj stajlar[], int toplam_staj);
int tamamlanmamis_staj_liste(staj stajlar[], int toplam_staj);

int main(){
    //Tanimlamalar yapiliyor.
    int toplam_firma=0, toplam_ogrenci=0, toplam_staj=0;
    firma firmalar[100];
    ogrenci ogrenciler[50];
    staj stajlar[50];
    FILE *fp;
    int menu;

menu:printf("Hangi islemi yapmak istersiniz?\n");
    printf("1. Ogrenci islemleri\n");
    printf("2. Firma islemleri\n");
    printf("3. Staj islemleri\n");
    printf("4. Sistemden cikis\n");
    scanf("%d",&menu);

    //Girdiler aliniyor.
    fp = fopen("toplam.txt", "r");
    fscanf(fp, "%d", &toplam_ogrenci);
    fclose(fp);

    fp = fopen("ogrenci.txt", "r");
    for(int i=0; i<toplam_ogrenci; i++)
        fscanf(fp, "%d %s %s", &ogrenciler[i].no, &ogrenciler[i].ad, &ogrenciler[i].soyad);
    fclose(fp);

    fp = fopen("toplamf.txt", "r");
    fscanf(fp, "%d", &toplam_firma);
    fclose(fp);

    fp = fopen("firma.txt", "r");
    for(int i=0; i<toplam_firma; i++)
        fscanf(fp, "%d %s %s", &firmalar[i].vergi_no, &firmalar[i].isim, &firmalar[i].faaliyet_alani);
    fclose(fp);

    fp = fopen("toplams.txt", "r");
    fscanf(fp, "%d", &toplam_staj);
    fclose(fp);

    fp = fopen("staj.txt", "r");
    for(int i=0; i<toplam_staj; i++)
        fscanf(fp, "%d %d %d %d", &stajlar[i].no, &stajlar[i].vergi_no, &stajlar[i].yazilim, &stajlar[i].donanim);
    fclose(fp);
    //Seceneklere yonlendiriliyor.
    switch(menu){
case 1:
    ogrenci_islemleri(ogrenciler, toplam_ogrenci);
    printf("Menuye Gecmek icin Herhangi Bir Tusa Basiniz...\n\n");
    getch();
    goto menu;
case 2:
    firma_islemleri(firmalar, toplam_firma);
    printf("Menuye Gecmek icin Herhangi Bir Tusa Basiniz...\n\n");
    getch();
    goto menu;
case 3:
    staj_islemleri(ogrenciler, toplam_ogrenci, firmalar, toplam_firma, stajlar, toplam_staj);
    printf("Menuye Gecmek icin Herhangi Bir Tusa Basiniz...\n\n");
    getch();
    goto menu;
default:
    return 0;
    }
}

int staj_islemleri(ogrenci ogrenciler[], int toplam_ogrenci, firma firmalar[], int toplam_firma, staj stajlar[], int toplam_staj){
    int menu;

    printf("Hangi islemi yapmak istersiniz?\n");
    printf("1. Staj ekleme\n");
    printf("2. Tamamlanmamis stajlar\n");
    printf("3. Tamamlanmis stajlar\n");
    scanf("%d", &menu);

   switch(menu){
case 1:
    staj_ekleme(ogrenciler, toplam_ogrenci, firmalar, toplam_firma, stajlar, toplam_staj);
    break;
case 2:
    tamamlanmamis_staj_liste(stajlar, toplam_staj);
    break;
case 3:
    tamamlanmis_staj_liste(stajlar, toplam_staj);
    break;
default:
    return 0;
}}

int ogrenci_islemleri(ogrenci ogrenciler[], int toplam_ogrenci){
    int menu;

    printf("Hangi islemi yapmak istersiniz?\n");
    printf("1. Ogrenci ekleme\n");
    printf("2. Ogrenci duzenleme\n");
    printf("3. ogrenci silme\n");
    printf("4. ogrenci listeleme\n");
    scanf("%d",&menu);
    //Yonlendiriliyor.
    switch(menu){
case 1:
    ogrenci_ekleme(ogrenciler, toplam_ogrenci);
    break;
case 2:
    ogrenci_duzenleme(ogrenciler, toplam_ogrenci);
    break;
case 3:
    ogrenci_silme(ogrenciler, toplam_ogrenci);
    break;
case 4:
    ogrenci_listeleme(ogrenciler, toplam_ogrenci);
    break;
default:
    return 0;
    }
}

int ogrenci_ekleme(ogrenci ogrenciler[], int toplam_ogrenci){
    int yanit=1;
    FILE *fp;
    //Girdiler aliniyor.
    while(yanit==1){
    printf("Adinizi Giriniz :\n");
    scanf("%s", &ogrenciler[toplam_ogrenci].ad);
    printf("Soy Adinizi Giriniz :\n");
    scanf("%s", &ogrenciler[toplam_ogrenci].soyad);
    ogrenciler[toplam_ogrenci].no = toplam_ogrenci;
    toplam_ogrenci++;

    printf("Yeni ogrenci eklemek icin 1e basiniz\n");
    scanf("%d", &yanit);
    }
    //Girdiler dosyalaniyor.
    fp = fopen("ogrenci.txt", "w");
    for(int i = 0; i<toplam_ogrenci; i++)
        fprintf(fp, "%d \t %s %s \t \n", ogrenciler[i].no, ogrenciler[i].ad, ogrenciler[i].soyad);
    fclose(fp);

    fp = fopen("toplam.txt", "w");
    fprintf(fp, "%d", toplam_ogrenci);
    fclose(fp);
    //Ogrenciler listeleniyor.
    ogrenci_listeleme(ogrenciler, toplam_ogrenci);
}

int ogrenci_duzenleme(ogrenci ogrenciler[], int toplam_ogrenci){
    FILE *fp;
    int no, menu;
    bool kayit;
    //Girdi aliniyor.
    printf("Duzenlenecek ogrenci nosunu giriniz\n");
    scanf("%d", &no);
    //Hata kontrolu yapiliyor.
    for(int i = 0; i<toplam_ogrenci; i++){
        if(ogrenciler[i].no == no)
            kayit = true;
    }
    if(kayit == false){
        printf("Hatali numara girdiniz\n");
        return 0;
    }

    printf("Hangi islemi yapmak istersiniz?\n");
    printf("1. Ogrenci adi degistirme\n");
    printf("2. Ogrenci soyadi degistirme\n");
    scanf("%d", &menu);
    //Seceneklere yonlendiriliyor.
    switch(menu){
case 1:
    ad_degistirme(no, ogrenciler, toplam_ogrenci);
    break;
case 2:
    soyad_degistirme(no, ogrenciler, toplam_ogrenci);
    break;
    }
    //Ogrenciler yazdiriliyor.
    ogrenci_listeleme(ogrenciler, toplam_ogrenci);
}

int ad_degistirme(int no, ogrenci ogrenciler[], int sayac){
    char yeni_ad[15];
    FILE *fp;
    //Girdi alinip islem yapiliyor.
    printf("Yeni adi giriniz\n");
    scanf("%s", &yeni_ad);

    strcpy(ogrenciler[no].ad, yeni_ad);
    //Veriler dosyayla esitleniyor.
    fp = fopen("ogrenci.txt", "w");
    for(int i = 0; i<sayac; i++)
        fprintf(fp, "%d \t %s %s \t \n", ogrenciler[i].no, ogrenciler[i].ad, ogrenciler[i].soyad);
    fclose(fp);

    printf("Ad degistirme basarili\n");

}

int soyad_degistirme(int no, ogrenci ogrenciler[], int sayac){
    char yeni_soyad[15];
    FILE *fp;
    //Girdi alinip islem yapiliyor.
    printf("Yeni soyadi giriniz\n");
    scanf("%s", &yeni_soyad);

    strcpy(ogrenciler[no].soyad, yeni_soyad);
    //Veriler dosyayla esitleniyor.
    fp = fopen("ogrenci.txt", "w");
    for(int i = 0; i<sayac; i++)
        fprintf(fp, "%d \t %s %s \t \n", ogrenciler[i].no, ogrenciler[i].ad, ogrenciler[i].soyad);
    fclose(fp);

    printf("Soyad degistirme basarili\n");

}

int ogrenci_silme(ogrenci ogrenciler[], int toplam_ogrenci){
    int no;
    FILE *fp;
    bool kayit;
    //Girdi aliniyor.
    printf("Silmek istediginiz ogrenci nosunu giriniz\n");
    scanf("%d", &no);
    //Hata kontrolu yapiliyor.
    for(int i = 0; i<toplam_ogrenci; i++){
        if(ogrenciler[i].no == no)
            kayit = true;
    }
    if(kayit == false){
        printf("Hatali numara girdiniz\n");
        return 0;
    }
    //Islem yapiliyor. Silinen no -1 olarak kayit ediliyor.
    strcpy(ogrenciler[no].ad, "silinmis");
    strcpy(ogrenciler[no].soyad, "silinmis");
    ogrenciler[no].no = -1;
    //veri esitleniyor.
    fp = fopen("ogrenci.txt", "w");
    for(int i = 0; i<toplam_ogrenci; i++)
        fprintf(fp, "%d \t %s %s \t \n", ogrenciler[i].no, ogrenciler[i].ad, ogrenciler[i].soyad);
    fclose(fp);
    //Ogrenciler listeleniyor.
    printf("Silme islemi basarili\n");
    ogrenci_listeleme(ogrenciler, toplam_ogrenci);
}

int ogrenci_listeleme(ogrenci ogrenciler[], int toplam_ogrenci){
    //Ekrana cikti aliniyor. -1 nolularin ciktisi alinmiyor.
    for(int i=0;i<toplam_ogrenci;i++){
        if(ogrenciler[i].no != -1){
        printf ("****************************\n");
        printf("Ad ve Soyad: %s %s \t  Numara:  %d \t \n", ogrenciler[i].ad, ogrenciler[i].soyad, ogrenciler[i].no);
        printf ("****************************\n");
    }}
}


int firma_islemleri(firma firmalar[], int toplam_firma){
    int menu;
    printf("Hangi islemi yapmak istersiniz?\n");
    printf("1. Firma ekleme\n");
    printf("2. Firma duzenleme\n");
    printf("3. Firma silme\n");
    printf("4. Firma listeleme\n");
    scanf("%d",&menu);
    //Secenege yonlendiriliyor.
    switch(menu){
case 1:
    firma_ekleme(firmalar, toplam_firma);
    break;
case 2:
    firma_duzenleme(firmalar, toplam_firma);
    break;
case 3:
    firma_silme(firmalar, toplam_firma);
    break;
case 4:
    firma_listeleme(firmalar, toplam_firma);
    break;
default:
    return 0;
    }
}

int firma_ekleme(firma firmalar[], int toplam_firma){
    FILE *fp;
    int yanit=1, vergi_no;
    //Girdiler aliniyor.
    while(yanit==1){
    printf("Firma ismini Giriniz :\n");
    scanf("%s", &firmalar[toplam_firma].isim);
    printf("Firma faaliyet alani Giriniz :\n");
    scanf("%s", &firmalar[toplam_firma].faaliyet_alani);
    printf("Firma vergi no Giriniz :\n");
    scanf("%d", &vergi_no);
    //Firmanin kayit durumu kontrol ediliyor.
    for(int i=0;i<toplam_firma;i++){
        if(vergi_no == firmalar[i].vergi_no){
            printf("Firma zaten kayitli\n");
            return 0;
    }}

    firmalar[toplam_firma].vergi_no = vergi_no;
    toplam_firma++;

    printf("Yeni firma eklemek icin 1e basiniz\n");
    scanf("%d", &yanit);
    }
    //Veriler esitleniyor.
    fp = fopen("firma.txt", "w");
    for(int i = 0; i<toplam_firma; i++)
        fprintf(fp, "%d \t %s %s \t \n", firmalar[i].vergi_no, firmalar[i].isim, firmalar[i].faaliyet_alani);
    fclose(fp);

    fp = fopen("toplamf.txt", "w");
    fprintf(fp, "%d", toplam_firma);
    fclose(fp);
    //Firmalar yazdiriliyor.
    firma_listeleme(firmalar, toplam_firma);
}

int firma_duzenleme(firma firmalar[], int toplam_firma){
    int vergi_no, menu, sira_no;
    FILE *fp;
    bool kayit;
    //Girdi aliniyor. Hata kontrolu yapiliyor.
    printf("Duzenlenecek vergi nosunu giriniz\n");
    scanf("%d", &vergi_no);

    for(int i = 0; i<toplam_firma; i++){
        if(firmalar[i].vergi_no == vergi_no)
            kayit = true;
    }
    if(kayit == false){
        printf("Hatali numara girdiniz\n");
        return 0;
    }
    //Sira no bulunuyor.
    for(int i=0; i<toplam_firma; i++){
        if (firmalar[i].vergi_no == vergi_no)
            sira_no=i;
    }

    printf("Hangi islemi yapmak istersiniz?\n");
    printf("1. firma isim degistirme\n");
    printf("2. firma faaliyet alani degistirme\n");
    scanf("%d", &menu);
    //Yonlendirme yapilip tum firmalar listeleniyor.
    switch(menu){
case 1:
    firma_isim_degistirme(sira_no, firmalar, toplam_firma);
    break;
case 2:
    firma_faaliyet_alani_degistirme(sira_no, firmalar, toplam_firma);
    break;
    }
    firma_listeleme(firmalar, toplam_firma);
}

int firma_isim_degistirme(int no, firma firmalar[], int sayac){
    char yeni_isim[15];
    FILE *fp;
    //Girdiler aliniyor.
    printf("Firmanin yeni ismini giriniz\n");
    scanf("%s", &yeni_isim);
    //Islem yapiliyor.
    strcpy(firmalar[no].isim, yeni_isim);
    //Veriler esitleniyor.
    fp = fopen("firma.txt", "w");
    for(int i = 0; i<sayac; i++)
        fprintf(fp, "%d \t %s %s \t \n", firmalar[i].vergi_no, firmalar[i].isim, firmalar[i].faaliyet_alani);
    fclose(fp);

    printf("Firma isim degistirme basarili\n");
}

int firma_faaliyet_alani_degistirme(int no, firma firmalar[], int sayac){
    char yeni[15];
    FILE *fp;
    //Girdiler aliniyor.
    printf("Firmanin yeni faaliyet alanini giriniz\n");
    scanf("%s", &yeni);
    //Islem yapiliyor.
    strcpy(firmalar[no].faaliyet_alani, yeni);
    //Veriler esitleniyor.
    fp = fopen("firma.txt", "w");
    for(int i = 0; i<sayac; i++)
        fprintf(fp, "%d \t %s %s \t \n", firmalar[i].vergi_no, firmalar[i].isim, firmalar[i].faaliyet_alani);
    fclose(fp);

    printf("Firma faaliyet alani degistirme basarili\n");
}

int firma_silme(firma firmalar[], int toplam_firma){
    int vergi_no, sira_no;
    FILE *fp;
    bool kayit;
    //Girdi aliniyor. Hata kontrolu yapiliyor.
    printf("Silmek istediginiz firma vergi nosunu giriniz\n");
    scanf("%d", &vergi_no);

    for(int i = 0; i<toplam_firma; i++){
        if(firmalar[i].vergi_no == vergi_no)
            kayit = true;
    }
    if(kayit == false){
        printf("Hatali numara girdiniz\n");
        return 0;
    }
    //Islemler yapiliyor. Silinen firma no -1 olarak kayit ediliyor.
    for(int i=0; i<toplam_firma; i++){
        if (firmalar[i].vergi_no == vergi_no);
            sira_no=i;
    }

    strcpy(firmalar[sira_no].isim, "silinmis");
    strcpy(firmalar[sira_no].faaliyet_alani, "silinmis");
    firmalar[sira_no].vergi_no = -1;
    //Veriler esitleniyor.
    fp = fopen("firma.txt", "w");
    for(int i = 0; i<toplam_firma; i++)
        fprintf(fp, "%d \t %s %s \t \n", firmalar[i].vergi_no, firmalar[i].isim, firmalar[i].faaliyet_alani);
    fclose(fp);

    printf("Firma silme basarili\n");
    firma_listeleme(firmalar, toplam_firma);
}

int firma_listeleme(firma firmalar[], int toplam_firma){
    //-1 nolu firmalar listelenmiyor.
    for(int i=0;i<toplam_firma;i++){
        if(firmalar[i].vergi_no != -1){
            printf ("****************************\n");
            printf("Firma isim: %s Firma faaliyet alani: %s \t  Vergi No:  %d \t \n", firmalar[i].isim, firmalar[i].faaliyet_alani, firmalar[i].vergi_no);
            printf ("****************************\n");
    }}
}

int staj_ekleme(ogrenci ogrenciler[], int toplam_ogrenci, firma firmalar[], int toplam_firma, staj stajlar[], int toplam_staj){
    int gun[2], ay[2], yil[2], total, no = 0, vergi_no, a;
    bool kayit, kayit2, eski;
    FILE *fp;

    printf("ogrenci no giriniz\n");
    scanf("%d", &no);
    printf("Firma vergi_no giriniz\n");
    scanf("%d", &vergi_no);
    //Hata kontrolu yapilir.
    for(int i = 0; i<toplam_ogrenci; i++){
        if(ogrenciler[i].no == no)
            kayit = true;
    }
    for(int i = 0; i<toplam_firma; i++){
        if(firmalar[i].vergi_no == vergi_no)
            kayit2 = true;
    }
    if(kayit == false || kayit2 == false){
        printf("Hatali numara girdiniz\n");
        return 0;
    }
    //Kayit kontrol edilir.
    for(int i=0; i<toplam_staj; i++){
        if (stajlar[i].no == no){
            no=i;
            eski = true;
    }}

    stajlar[no].no = no;
    stajlar[no].vergi_no = vergi_no;

    printf("Staj turunu giriniz(Yazilim icin 1, donanim icin 2)\n");
    scanf("%d", &a);
    printf("Staj baslangic tarihini giriniz(gg aa yyyy seklinde)\n");
    scanf("%d %d %d", &gun[0], &ay[0], &yil[0]);
    printf("Staj bitis tarihini giriniz(gg aa yyyy seklinde)\n");
    scanf("%d %d %d", &gun[1], &ay[1], &yil[1]);

    gun[2] = gun[1] - gun[0];
    ay[2] = ay[1] - ay[0];
    yil[2] = yil[1] - yil[0];
    total = (gun[2] + ay[2] * 30 + yil[2] * 365)/7;

    if(a == 1)
        stajlar[no].yazilim += total;
    if(a == 2)
        stajlar[no].donanim += total;

    if(stajlar[no].yazilim > 12)
        stajlar[no].yazilim=0;
    if(stajlar[no].donanim > 12)
        stajlar[no].donanim=0;

    if(eski == false)
        toplam_staj++;

    fp = fopen("staj.txt", "w");
    for(int i = 0; i<toplam_staj; i++)
        fprintf(fp, "%d %d\t %d %d \t \n", stajlar[i].no, stajlar[i].vergi_no, stajlar[i].yazilim, stajlar[i].donanim);
    fclose(fp);

    fp = fopen("toplams.txt", "w");
    fprintf(fp, "%d", toplam_staj);
    fclose(fp);
}

int tamamlanmamis_staj_liste(staj stajlar[], int toplam_staj){

    for(int i=0;i<toplam_staj;i++){
        if(stajlar[i].donanim < 2 || stajlar[i].yazilim < 4 || stajlar[i].yazilim + stajlar[i].donanim != 12){
        printf ("****************************\n");
        printf("Ogrenci no: %d Firma vergi no: %d \t Yazilim staj: %d  donanim staj:  %d  toplam staj:  %d \n", stajlar[i].no, stajlar[i].vergi_no, stajlar[i].yazilim, stajlar[i].donanim, stajlar[i].yazilim + stajlar[i].donanim);
        printf ("****************************\n");
    }}
}

int tamamlanmis_staj_liste(staj stajlar[], int toplam_staj){
    for(int i=0;i<toplam_staj;i++){
        if(stajlar[i].donanim > 2 && stajlar[i].yazilim > 4 && stajlar[i].yazilim + stajlar[i].donanim > 12){
        printf ("****************************\n");
        printf("Ogrenci no: %d Firma vergi no: %d \t Yazilim staj: %d  donanim staj:  %d  toplam staj:  %d \n", stajlar[i].no, stajlar[i].vergi_no, stajlar[i].yazilim, stajlar[i].donanim, stajlar[i].yazilim + stajlar[i].donanim);
        printf ("****************************\n");
    }}
}
