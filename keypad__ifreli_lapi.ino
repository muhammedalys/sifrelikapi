#include<Keypad.h>  
#include <LiquidCrystal.h>
#include<Servo.h>
Servo servo;
#define mled 5   
#define kled 6   
#define buzzer 4

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

const byte satir = 4;  
const byte sutun = 4;  
char sifre[4] = {'1', '9', '0', '3'}; //şifre belirliyoruz
char sifre1[4];  //tuş takımında tıkacağımız şifre
char tus;   
int i = 0;  
char tus_takimi[4][4] = { 
  {'1', '4', '7', '*'},
  {'2', '5', '8', '0'},
  {'3', '6', '9', '#'},
  {'A', 'B', 'C', 'D'}
};

byte satir_pins[4] = {A0, A1, A2, A3};  //Satır pinlerinin bağlantı yerleri
byte sutun_pins[4] = {A4, A5, 3, 2};    //Sütun pinlerinin bağlantı yerleri

Keypad tuss_takimi = Keypad(makeKeymap(tus_takimi), satir_pins, sutun_pins, 4, 4);  // Keypad kütüphanesindeki özel kod
void setup() {
  servo.attach(13);
  pinMode(mled, OUTPUT);  
  pinMode(buzzer, OUTPUT);
  pinMode(kled, OUTPUT);

  lcd.begin(16, 2); 
  lcd.clear();  
  lcd.setCursor(1, 0);
  lcd.print("ARDUINO BEY");


  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("Arduino Bey");
  lcd.setCursor(0, 1);
  lcd.print("SIFRELI KAPI");  
  delay(2000);
  lcd.clear();  
  lcd.setCursor(0, 0); 
  lcd.print("SIFREYI GIRINIZ:");    
}

void loop() {
  servo.write(0);
  
digitalWrite(kled,LOW);
digitalWrite(mled,LOW);
  tus = tuss_takimi.getKey();  // Tuş takımını tıkladığımızda getKey anahtarı alır

  if (tus)   //eğer tuş varsa 
  {
    sifre1[i++] = tus;  //

    lcd.setCursor(i, 1); 
    lcd.print("*");   // * Bu karakteri kullandım, böylece ekranda yazdığım şifreler başkasından görülemeyecek
    digitalWrite(buzzer,HIGH);
delay(100);
digitalWrite(buzzer,LOW);
  }

  if (i == 4)
  { delay(200);
    char sifre[4] = {'1', '9', '0', '3'}; //Varsayılan şifre
 
    if ((strncmp(sifre1, sifre, 4) == 0))   // Bu şifreleri karşılaştırarak ilk önce 4 elemanı doğruysa işlem aşağıdaki gibi olacaktır
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      servo.write(90);
      lcd.print("SIFRE DOGRU!"); 
      digitalWrite(mled, HIGH);
      digitalWrite(kled, LOW);
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer, LOW);
      delay(100);
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer, LOW);
      delay(1000);
      lcd.clear();
      lcd.setCursor(0, 0); 
      lcd.print("SIFREYI GIRINIZ");  
      i = 0;
    }

    else
    {
        servo.write(0);
      lcd.clear();
      lcd.setCursor(0, 0); 
      lcd.print("SIFRE YANLIS!!!");  
      digitalWrite(mled, LOW);
      digitalWrite(kled, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(1000);
      digitalWrite(buzzer, LOW);
      delay(1000);
      lcd.clear();
      lcd.setCursor(0, 0); 
      lcd.print("SIFREYI GIRINIZ"); 
      i = 0;
    }
  }
}



