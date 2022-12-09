#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// On Fonksiyon tanimlamalari
void ikiMetinBirlestirme(char kelime1[], char kelime2[], char *metin);
void sezarSifreleme(char cumle[], int kaydirma, char *sifreliCumle);
void dosyayaSifreyiYaz(char sifre[], char dosyaIsmi[]);
int asalCarpanKontrol(unsigned int ogrNo, int asalSayi);
void dosyadanSifreyiOku(char dosya[], char *sifreliMetin);
void sezarSifrelemeCozum(char sifreliData[], int kaydirma, char *fullName);
void ogrenciNoSonRakam(unsigned int sayi, int *sayininSonRakami);

// structs
struct User {
	char fullname[50];
	char fullnameSifreli[50];
	unsigned int ogrNo;
	int ogrNoAsalCarpan;
	int ogrNoSonRakam;
};

int main() {
	system("color 4b"); // Konsola biraz renk katalim
	
	struct User user;

	printf("*** Hasan Polat Yil Sonu Proje Odevi *** \n"); // start
	printf("UYARI: Turkce karakter kullanmayiniz! \n\n"); 

	printf("Isim giriniz: ");
	gets(user.name);

	printf("Soyisim giriniz: ");
	gets(user.surname);
	
	printf("Ogrenci numaranizi giriniz: ");
	scanf("%d", &user.ogrNo);

	ikiMetinBirlestirme(user.name, user.surname, &user.fullname); // Isim ve Soyisimi birlestirip, gonderdigimiz 3.parametre adresine kaydetti.
	
	ogrenciNoSonRakam(user.ogrNo, &user.ogrNoSonRakam);
	
	sezarSifreleme(user.fullname, user.ogrNoSonRakam, &user.fullnameSifreli); // fullname'yi ogrencinin son basamagina gore sezar sifreleme ile sifreleyip sifreliMetin adresiyle aldik
	
	dosyayaSifreyiYaz(user.fullnameSifreli, "sifrelimetin.txt"); // gelen sifreli metni dosyaya yazdik
	
	printf("\n");
	
	// en buyuk asal carpan kontrolu yaptik
	// ogr: 212802045 en buyuk asal carpan: 14186803 *ornek*
	printf("Ogrenci numaranizin rakamlarindan en buyuk asal carpanini nedir? : ");
	scanf("%d", &user.ogrNoAsalCarpan);

	while(asalCarpanKontrol(user.ogrNo, user.ogrNoAsalCarpan) == 0){
		printf("Yalnis paralo! Tekrar giriniz...\n");
		printf("Ogrenci numaranizin rakamlarindan en buyuk asal carpanini nedir? : ");
		scanf("%d", &user.ogrNoAsalCarpan);
	}
	
	// en buyuk asal carpan dogru girildikten sonra
	printf("\n");
	printf("-----------------------\n");
	printf("\n");

	char DosyaIcerik[50];
	char DosyaIcerikCozumlu[50];
	
	dosyadanSifreyiOku("sifrelimetin.txt", &DosyaIcerik); // dosyadan sifreyi aldik
	
	printf("Sifreli Isim: %s\n", DosyaIcerik); 
	
	sezarSifrelemeCozum(DosyaIcerik, user.ogrNoSonRakam, &DosyaIcerikCozumlu); // aldigimiz metni cozuyoruz
	
	printf("Cozumlu Isim: %s\n", DosyaIcerikCozumlu);
	printf("Ogrenci Numara: %d\n", user.ogrNo);
	
	return 0;
}

// Fonksiyonlar
void ikiMetinBirlestirme(char kelime1[], char kelime2[], char *metin) {
	strcat(kelime1, " "); // strcat 1. ve 2.parametre string degerleri birlestirip 1.parametreye koyar.
	strcat(kelime1, kelime2);
	
	int i;
	int uzunluk = strlen(kelime1);

	// Sonucu main fonk icerisine gondermek icin aldigimiz degisken adresine birlestirdigimiz kelimeyi atiyoruz
	for(i=0; i < uzunluk; i++) {
		*(metin + i) = kelime1[i];
	}
	*(metin + i) = '\0';
}
void ogrenciNoSonRakam(unsigned int sayi, int *sayininSonRakami){
	
	int rakam = 0;
	int i = 0;
	while(rakam == 0){
		rakam = sayi % 10;
		sayi = sayi / 10; 
	}
	
	*sayininSonRakami = rakam;
}
void sezarSifreleme(char cumle[], int kaydirma, char *sifreliCumle) {
	
	char alfabe[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	int i,j;
	int cumleUzunluk = strlen(cumle);
	
	for(i=0; i < cumleUzunluk; i++) { // sezar sifreleme
		if(cumle[i]==' ') {
			cumle[i] = '|';
		} else {
			for(j=0;j < 26; j++){
				if(cumle[i] == alfabe[j]){
					j = j + kaydirma;
					j = j % 26; // Sezar sifrelemede sona geldikten sonra basa donulur onu saglamak amacli 26'ya mod aliriz.
					cumle[i] = alfabe[j];
					break;
				}
			}
		}
	}
	
	// Sonucu main fonk icerisine gondermek icin aldigimiz degisken adresine sifreledigimiz cumleyi atiyoruz
	for(i=0; i < cumleUzunluk; i++) {
	
		*(sifreliCumle + i) = cumle[i];
		
	}
	
	*(sifreliCumle + cumleUzunluk) = '\0';
	
}
void dosyayaSifreyiYaz(char sifre[], char dosyaIsmi[]){
	FILE *dosya = fopen(dosyaIsmi, "w");
	
	fprintf(dosya,"%s", sifre);
	
	fclose(dosya);
}
int asalCarpanKontrol(unsigned int ogrNo, int asalSayi){
	
	int i;
	int j = 0;
	int asalSayilar[50];
	for(i=2;ogrNo>1;i++){ // asal carpanlara ayirdik
		
	  while(ogrNo%i==0){
	   	asalSayilar[j] = i;
	   	j++;
	   	ogrNo=ogrNo/i;
	  }
	}
	
	int kontrol = 0;
	
	for(i = 0; i < j; i++){ // asal carpanlarin en buyugunu bulduk
		if(asalSayilar[i] > kontrol){
			kontrol = asalSayilar[i];
		}
	}


	if(kontrol == asalSayi){ // eger gelen asal sayi ile en buyuk asal carpan esitse 1 donuyoruz yoksa 0
		return 1;
	}else{
		return 0;
	}
	
}
void dosyadanSifreyiOku(char dosya[], char *sifreliMetin){
	char metin[50], kelime1[50], kelime2[50];
	int i = 0;
	
	FILE *dosyaAc = fopen(dosya, "r");
	
	while(!feof(dosyaAc)){ // fgetc ile dosyadan metni aldik ve direkt pointer ile mainden gonderdigimiz degiskene yolladik
    	*(sifreliMetin + i) = fgetc(dosyaAc);
    	i++;
  	}
  	*(sifreliMetin + (i - 1)) = '\0';
	fclose(dosyaAc);
}
void sezarSifrelemeCozum(char sifreliData[], int kaydirma, char *fullName){
	
	char alfabe[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	int i,j;
	int cumleUzunluk = strlen(sifreliData);
	
	for(i=0; i < cumleUzunluk; i++) { // sezar sifreleme cozum
		if(sifreliData[i]=='|') {
			sifreliData[i] = ' ';
		} else {
			for(j=0;j < 26; j++){
				if(sifreliData[i] == alfabe[j]){
					j = j - kaydirma;
					if(j < 0) {
						j = j + 26;
					}

					sifreliData[i] = alfabe[j];
					break;
				}
			}
		}
	}
	
	// Sonucu main fonk icerisine gondermek icin aldigimiz degisken adresine sifreledigimiz cumleyi atiyoruz
	for(i=0; i < cumleUzunluk; i++) {
	
		*(fullName + i) = sifreliData[i];
		
	}
	
	*(fullName + cumleUzunluk) = '\0';
	
}

