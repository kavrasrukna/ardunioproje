#include <LiquidCrystal.h>

#define s0 8 //Bağladığımız pinlere göre tanımlamalarımızı yapıyoruz
#define s1 9
#define s2 10
#define s3 11
#define sensorOut 12


int K, Y, M = 0; //3 ana renk için değişken tanımlıyoruz

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);//LCD pinlerini tanımlıyoruz

void setup() {
  lcd.begin(16,1);
  pinMode(s0, OUTPUT);//S0, S1, S2 ve S3 pinlerini OUTPUT olarak tanımlıyoruz
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(sensorOut, INPUT);//OUT pinini INPUT olarak tanımlıyoruz

  digitalWrite(s1,LOW);  //Frekans ölçeğimizi %20 olarak tanımlıyoruz
  digitalWrite(s0,HIGH);  
  Serial.begin(9600);

}

void loop() {
  

  digitalWrite(s2, LOW); //Kırmızıyı filtrelemek için
  digitalWrite(s3, LOW);
  K = pulseIn(sensorOut, LOW);//OUT pini üzerindeki LOW süresini okur
  Serial.print("RED= ");
  Serial.print("  ");
  delay(50);//50 milisaniye bekle
 
  digitalWrite(s2, HIGH); //Yeşili filtrelemek için
  digitalWrite(s3, HIGH);
  Y = pulseIn(sensorOut, LOW); //OUT pini üzerindeki LOW süresini okur
  Serial.print("GREEN= ");
  Serial.print("   ");
  delay(50);//50 milisaniye bekle
 
  digitalWrite(s2, LOW); //Maviyi filtrelemek için
  digitalWrite(s3, HIGH);
  M = pulseIn(sensorOut, LOW);//OUT pini üzerindeki LOW süresini okur
  Serial.print("BLUE= ");
  Serial.println();
  delay(50);//50 milisaniye bekle

  digitalWrite(s2, LOW); //Kırmızıyı filtrele
  digitalWrite(s3, LOW);
  K = pulseIn(sensorOut, LOW); //OUT pini üzerindeki LOW süresini okur
  Serial.print("RED= ");
  Serial.print("  ");
  lcd.print("  ");
  lcd.setCursor(7, 0); //İmleci 7. sütuna al
  delay(50); //50 milisaniye bekle
 
 
  digitalWrite(s2, HIGH); //Yeşili filtrele
  digitalWrite(s3, HIGH);
  Y = pulseIn(sensorOut, LOW); //OUT pini üzerindeki LOW süresini okur
  Serial.print("GREEN= ");
  Serial.print("   ");
  delay(50);

  lcd.setCursor(4, 1); //İmleci 2. satır 4. sütuna taşı
  digitalWrite(s2, LOW); //Maviyi filtrele
  digitalWrite(s3, HIGH);
  M = pulseIn(sensorOut, LOW); //OUT pini üzerindeki LOW süresini okur
  Serial.print("BLUE= "); 
  Serial.println();
  lcd.setCursor(0, 0);
  delay(1000); //1000 milisaniye bekle
  //Renk değerlerini 1 saniye boyunca ekranda göreceğiz
  
  lcd.clear(); //Ekranı temizle
  delay(150); //150 milisaniye bekle


  lcd.setCursor(1,0); //İmleci 1. sütuna al
 
  lcd.setCursor(2,1); //İmleci 2. satır 2. sütuna al
  //Kalibrasyon bölümünde elde ettiğimiz değerleri bu kısımda kullanacağız
  if(K<70 && M<70 && Y<70) //Eğer tüm renklerin yoğunluğu yüksekse: Beyaz
  {
  Serial.print("Renk = Beyaz   ");
  lcd.print("WHITE");  
  }
  else if(K<100 && Y<M && abs(K-Y)<20)
  //Kırmızı yoğunluğu yüksek ve yeşille arasındaki değer 20'den azsa: Sarı
  {
  Serial.print("Renk = Sarı   ");
  lcd.print("YELLOW");
  }
  else if(K<100 && M<Y && abs(M-K)<20)
  //Kırmızı yoğunluğu yüksek ve mavi ile arasındaki değer 20'den azsa: Magenta
  {
  Serial.print("Renk = Magenta   ");
  lcd.print("PINK");
  }
  else if(Y<130 && Y<M && Y<K)
  //Yeşil yoğunluğu belli bir seviyenin üstünde ve kırmızı-maviden daha yoğunsa: Yeşil
  {
  Serial.print("Renk = Yeşil   ");
  lcd.print("GREEN");
  }
  else if(M<100 && M<Y && M<K)
  //Mavi yoğunluğu belli bir seviyenin üstünde ve yeşil-kırmızıdan daha yoğunsa: Mavi
  {
  Serial.print("Renk = Mavi   ");
  lcd.print("BLUE");
  }
  else if(K<100 && K<Y && K<M)
  //Kırmızı yoğunluğu belli bir seviyenin üstünde ve yeşil-maviden daha yoğunsa: Kırmızı
  {
  Serial.print("Renk = Kırmızı   ");
  lcd.print("RED");
  }
  else
  {
  Serial.print("Renk algılanamadı");//Belirlediğimiz kıstaslara uymayan diğer renkler
  lcd.print("---");
  }
  
  Serial.println(); //Serial monitörde bir satır aşağı geç
  delay(1000);//1000 milisaniye bekle
  lcd.clear();//LCD ekranı temizle
  delay(150);
  
}
