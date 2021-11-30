// wifi
const char* ssid =  "roottv";
const char* pswrd = "u4U0xvGh";

//Sensör 1
#define echoPin 6
#define trigPin 7

//Buzzer
#define buzzerPin 8

//Sensör 2
#define echoPin2  9
#define trigPin2  10

//potansiyometre
#define potansiyo A0
int potansiyoValue = 0;

//control led
#define leftPotansyioLed 2
#define rightPotansyioLed 3




int maximumRange = 50, minimumRange = 0;
//sayaç
int count = 0;
int flag = 0;
char code;

void setup() {
  Serial.begin(9600);
  delay(1000);

  //ledler
  pinMode(leftPotansyioLed, OUTPUT);
  pinMode(rightPotansyioLed, OUTPUT);

  //ultrasonic pinler
  pinMode(trigPin, OUTPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(echoPin2, INPUT);

}

//ardunio reset fonksiyonu
void(* resetFunc) (void) = 0;
void ultraSonic() {
  digitalWrite(leftPotansyioLed, LOW);
  digitalWrite(rightPotansyioLed, HIGH);

  //başlangıç bekleyişi kısa için 2 uzun için 10 yazabilirsin
  delay(2000);

  //ölcümler
  int olcum = mesafe(maximumRange, minimumRange);
  int olcum2 = mesafe2(maximumRange, minimumRange);

  if (olcum > 0 || olcum2 > 0) {
    count++;
    //count 2 * 3 yani = 6 sn boyunca olcum 0 dan büyük önünde engel varsa melodiyi çaldır
    if (count >= 3) {
      Serial.println(count);
      melodi(olcum * 10);
      melodi(olcum2 * 10);
    }
  } else {
    //olcum 0 sa ardunioyu resetle
    resetFunc();
  }
}

void loop() {

  //bluetooth dan gelen değer
  if (Serial.available()) {
    char code = Serial.read();
    Serial.println(code);
    if (code == 'f') {
      flag = 1;
    }
    else {
      flag = 0;
    }
  }
  if (flag == 0) {
    ultraSonic();
  } else {
    digitalWrite(leftPotansyioLed, HIGH);
    digitalWrite(rightPotansyioLed, LOW);
  }


  /*if (code == 'o') {
    digitalWrite(leftPotansyioLed, LOW);
    digitalWrite(rightPotansyioLed, HIGH);
    //başlangıç bekleyişi kısa için 2 uzun için 10 yazabilirsin
    delay(2000);

    //ölcümler
    int olcum = mesafe(maximumRange, minimumRange);
    int olcum2 = mesafe2(maximumRange, minimumRange);

    if (olcum > 0 || olcum2 > 0) {
      Serial.println(count);
      count++;
      //count 2 * 3 yani = 6 sn boyunca olcum 0 dan büyük önünde engel varsa melodiyi çaldır
      if (count >= 3) {
        melodi(olcum * 10);
        melodi(olcum2 * 10);
      }

    } else {
      //olcum 0 sa ardunioyu resetle
      resetFunc();
    }


    } else if (code == 'f') {
    digitalWrite(leftPotansyioLed, HIGH);
    digitalWrite(rightPotansyioLed, LOW);
    } else {
    //başlangıç bekleyişi kısa için 2 uzun için 10 yazabilirsin
    delay(2000);

    //ölcümler
    int olcum = mesafe(maximumRange, minimumRange);
    int olcum2 = mesafe2(maximumRange, minimumRange);

    if (olcum > 0 || olcum2 > 0) {
      Serial.println(count);
      count++;
      //count 2 * 3 yani = 6 sn boyunca olcum 0 dan büyük önünde engel varsa melodiyi çaldır
      if (count >= 3) {
        melodi(olcum * 10);
        melodi(olcum2 * 10);
      }

    } else {
      //olcum 0 sa ardunioyu resetle
      resetFunc();
    }
    }*/


  /*else {
    //potansiyo okuma
    potansiyoValue = analogRead(potansiyo);
    //bu işlem ile potansiyometre en yüksek ve en az gerilimini alarak hesaplayabiliriz
    potansiyoValue = (5.00 / 1024.00) * potansiyoValue;

    if (potansiyoValue < 4)
      digitalWrite(leftPotansyioLed, HIGH);
    digitalWrite(rightPotansyioLed, LOW);
    if (potansiyoValue == 4) {
      digitalWrite(leftPotansyioLed, LOW);
      digitalWrite(rightPotansyioLed, HIGH);
      //başlangıç bekleyişi kısa için 2 uzun için 10 yazabilirsin
      delay(2000);

      //ölcümler
      int olcum = mesafe(maximumRange, minimumRange);
      int olcum2 = mesafe2(maximumRange, minimumRange);

      if (olcum > 0 || olcum2 > 0) {
        count++;
        //count 2 * 3 yani = 6 sn boyunca olcum 0 dan büyük önünde engel varsa melodiyi çaldır
        if (count >= 3) {
          melodi(olcum * 10);
          melodi(olcum2 * 10);
        }

      } else {
        //olcum 0 sa ardunioyu resetle
        resetFunc();
      }

    }
    }*/


}



int mesafe(int maximumRange, int minimumRange) {
  long duration, distance;

  digitalWrite(trigPin, LOW);

  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);

  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);


  duration = pulseIn(echoPin, HIGH);

  /*Serial.print("Sensor 1: ");
    Serial.print((duration / 29) / 2);
    Serial.print("CM");
    Serial.println();*/

  distance = (duration / 29.1) / 2;

  delay(50);


  if (distance >= maximumRange || distance <= minimumRange)
    return 0;
  return distance;
}

int mesafe2(int maximumRange, int minimumRange) {
  long duration, distance;

  digitalWrite(trigPin2, LOW);

  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);

  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);


  duration = pulseIn(echoPin2, HIGH);

  /*Serial.print("Sensor 2: ");
    Serial.print((duration / 29) / 2);
    Serial.print("CM");
    Serial.println();*/

  distance = (duration / 29.1) / 2;

  delay(50);


  if (distance >= maximumRange || distance <= minimumRange)
    return 0;
  return distance;
}

int melodi(int dly) {
  tone(buzzerPin, 440);
  delay(dly);
  noTone(buzzerPin);
  delay(dly);
}
