#include "DHT.h"
#include <LiquidCrystal.h>
#include <stdio.h>
#include <string.h>
 
 
#define DHTPIN 13    
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
 
LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);
DHT dht(DHTPIN, DHTTYPE);

byte name1x5[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte name0x7[] = {
  B00000,
  B00000,
  B00000,
  B00011,
  B00011,
  B00110,
  B00110,
  B01100
};

byte name0x8[] = {
  B01110,
  B01110,
  B11011,
  B11011,
  B10001,
  B00000,
  B00000,
  B10001
};

byte name0x9[] = {
  B00000,
  B00000,
  B00000,
  B11000,
  B11000,
  B01100,
  B01100,
  B00110
};

byte name1x6[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00001,
  B00011,
  B01111
};

byte name1x7[] = {
  B11111,
  B01100,
  B01100,
  B11000,
  B11000,
  B10000,
  B00000,
  B11100
};

byte name1x8[] = {
  B11111,
  B01110,
  B10001,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte name1x9[] = {
  B11111,
  B00110,
  B00110,
  B00011,
  B00011,
  B00001,
  B00000,
  B00111
};

byte name1x10[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B10000,
  B11000,
  B11110
};





byte temp1[] = {
  B00011,
  B00100,
  B01011,
  B01011,
  B01011,
  B01011,
  B00100,
  B00011
};

byte temp2[] = {
  B10000,
  B01000,
  B10111,
  B11010,
  B11000,
  B10111,
  B01000,
  B10000
};

byte temp3[] = {
  B00000,
  B00000,
  B11110,
  B10101,
  B00001,
  B11110,
  B00000,
  B00000
};

byte umidade1[] = {
  B00000,
  B00010,
  B00100,
  B01001,
  B00010,
  B00000,
  B01001,
  B00000
};

byte umidade2[] = {
  B00100,
  B01000,
  B00000,
  B00100,
  B01001,
  B10010,
  B00000,
  B00000
};

byte luz1[] = {
  B00000,
  B00000,
  B00110,
  B01011,
  B01101,
  B00110,
  B00000,
  B00000
};

byte luz2[] = {
  B00111,
  B01000,
  B10001,
  B10110,
  B10110,
  B10001,
  B01000,
  B00111
};

byte luz3[] = {
  B10000,
  B01000,
  B00100,
  B00100,
  B00100,
  B00100,
  B01000,
  B10000
};

//byte charArray[] = {name1x5, name0x7, name0x8, name0x9, name1x6, name1x7, name1x8, name1x9, name1x10};


int portLDR = A0;

int redLED = 7;
int yellowLED = 8;
int greenLED = 9;
int portBuzzer = 6;

//Timers

//Timer da Buzina
unsigned long lastBeeping = 0; 
int beepingTime = 200;

//Timer das Medidas
unsigned long lastMeasurement = 0;
int measurementTime = 2000;

//Timers do Display
unsigned long lastScreenFrame = 0;
int screenFPS = 200;                  

//Timer para trocar entre luminosidade e umidade no display
unsigned long lastSwitch = 0;
int switchTime = 10000;

//Medidas
int leituraLDR;
int light;

float temperature;
float humidity;

//Quantidade de Leituras para a Média Móvel
int quantidadeLeituras = 10;

//Variáveis de String
char upperline_text[16];
char display_text[1000];
char current_display_text[16];
int index = 0;

//Valores Preocupantes
int lightAlert = 70;
int lightWarning = 35;
int humAlert = 20;
int humWarning = 35;
int tempAlert = 15;
int tempWarning = 8;

//Variável para alternar entre Luminosidade e Umidade no Display
bool trigger = false;

void change_display_text(int currentIndex) {  //Função para rolar o texto na linha de baixo
  int length = strlen(display_text);
  for (int i=0; i<=16; i++) {
    
    if(i+currentIndex <= length-1) {
      current_display_text[i] = display_text[i+currentIndex];
    }
    else {
      current_display_text[i] = display_text[i+currentIndex-length];
    }
  }
}

void setup() {
  int time = 400;
  Serial.begin(9600);
  Serial.println(F("DHT22 example!"));
 
  dht.begin();
 
  lcd.begin(16,2);              

  //Animação da Logo Ares
  lcd.createChar(0, name1x5);
  lcd.setCursor(5, 1);
  lcd.write(byte(0));
  delay(time);
  lcd.createChar(1, name0x7);
  lcd.setCursor(7, 0);
  lcd.write(1);
  delay(time);
  lcd.createChar(2, name0x8);
  lcd.setCursor(8, 0);
  lcd.write(2);
  delay(time);
  lcd.createChar(3, name0x9);
  lcd.setCursor(9, 0);
  lcd.write(3);
  delay(time);
  lcd.createChar(4, name1x6);
  lcd.setCursor(6, 1);
  lcd.write(4);
  delay(time);
  lcd.createChar(5, name1x7);
  lcd.setCursor(7, 1);
  lcd.write(5);
  delay(time);
  lcd.createChar(6, name1x8);
  lcd.setCursor(8, 1);
  lcd.write(6);
  delay(time);
  lcd.createChar(7, name1x9);
  lcd.setCursor(9, 1);
  lcd.write(7);
  delay(time);
  lcd.createChar(0, name1x10);
  lcd.setCursor(10, 1);
  lcd.write(8);
  delay(time);
  leituraLDR = analogRead(portLDR);
  light = map(leituraLDR, 0, 1023, 100, 0);
}
 
void loop() {
  if(millis() - lastMeasurement >= measurementTime) { 
    //Monitoramento da iluminação
    int sum = 0;
    for (int i = 0; i<quantidadeLeituras; i++) { 
      leituraLDR = analogRead(portLDR);
      sum += map(leituraLDR, 0, 1023, 100, 0);
    }
    light = sum/quantidadeLeituras; //calculando a média móvel

    sum = 0;
    //Monitoramento da umidade e temperatura (DHT11)
    for (int i = 0; i<quantidadeLeituras; i++) {
      sum  += dht.readTemperature();
    }
    temperature = sum/10; //calculando a média móvel
    sum = 0;
    for (int i = 0; i<quantidadeLeituras; i++) {
      sum += dht.readHumidity();
    }
    humidity = sum/10; //calculando a média móvel
  
    // Checar se a Leitura falhou
    if (isnan(temperature) || isnan(humidity)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;

    lastMeasurement = millis();
    }
  }

  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, LOW);
  //Checando as Medidas e acendendo o LED correspondente
  if(light > lightAlert or humidity < humAlert or temperature > tempAlert) {
    digitalWrite(redLED, HIGH);
    beepingTime = 700; //Buzina tocará mais rapidamente no LED Vermelho
  }
  else if(light > lightWarning && light < lightAlert or humidity > humAlert && humidity < humWarning or temperature < tempAlert && temperature > tempWarning) {
    digitalWrite(yellowLED, HIGH);
    beepingTime = 1500; //Buzina tocará mais lentamente no LED Amarelo
  }
  else {
    digitalWrite(greenLED, HIGH);
  }

  //Tocar a buzina quando necessário
  if (digitalRead(yellowLED) == HIGH or digitalRead(redLED) == HIGH) {
    if(millis() - lastBeeping >= beepingTime) {
      digitalWrite(portBuzzer, !digitalRead(portBuzzer));
      lastBeeping = millis();
      Serial.println("beeping");
    } else {
      digitalWrite(portBuzzer, LOW);
    }
  }

  if(millis() - lastScreenFrame >= screenFPS) { //Atualizar o display
    if(index > strlen(display_text)) { //Resetar o index quando chegar no fim do texto
      index = 0;
    }

    lcd.clear();
    //Criando os icones
    lcd.createChar(0, temp1);
    lcd.createChar(1, temp2);
    lcd.createChar(2, temp3);
    lcd.createChar(3, umidade1);
    lcd.createChar(4, umidade2);
    lcd.createChar(5, luz1);
    lcd.createChar(6, luz2);
    lcd.createChar(7, luz3);
    //Escrevendo a linha de cima
    lcd.setCursor(0,0);
    lcd.write(byte(0));
    lcd.write(1);
    lcd.write(2);
    lcd.print((int)temperature);
    lcd.print((char)223);
    lcd.print("C ");

    if(trigger == false) { //Mostrar a Luminosidade
      lcd.write(5);
      lcd.write(6);
      lcd.write(7);
      Serial.println(light);
      lcd.print(light);
      lcd.print("%");
    }
    else { //Mostrar a Umidade
      lcd.write(3);
      lcd.write(4);
      lcd.print((int)humidity);
      lcd.print("%");
    }

    if(millis() - lastSwitch >= switchTime) { //Alternar entre luminosidade e umidade
      trigger = !trigger;
      lastSwitch = millis();
    }


    char previous_text[1000];
    strcpy(previous_text, display_text);

    strcpy(display_text, ""); //Limpando a segunda linha

    //Escrevendo a segunda linha
    if(light > lightAlert) {
      strcat(display_text, "!!!ALERTA: Luminosidade Alta    ");
    }
    if(humidity < humAlert) {
      strcat(display_text, "!!!ALERTA: Umidade Baixa    ");
    }
    if(temperature > tempAlert) {
      strcat(display_text, "!!!ALERTA: Temperatura Alta    ");
    }
    if (light > lightWarning && light < lightAlert) {
      strcat(display_text, "AVISO: Luminosidade acima do ideal    ");
    }
    if(humidity > humAlert && humidity < humWarning) {
      strcat(display_text, "AVISO: Umidade abaixo do ideal    ");
    }
    if(temperature > tempWarning && temperature < tempAlert) {
      strcat(display_text, "AVISO: Temperatura acima do ideal    ");
    }

    if(digitalRead(greenLED) == HIGH && strlen(display_text) == 0) {
      strcpy(display_text, "Tudo OK                ");
      Serial.println("ok");
    }

    //if(strcmp(previous_text, display_text) != 0) { index=0;}

    lcd.setCursor(0,1);

    //char buffer[10];
    //sprintf(buffer, 10, "%f", temperature);
    //strcat(display_text, buffer);

    change_display_text(index);
    lcd.print(current_display_text);

    lastScreenFrame = millis();
    index+= 1; // Rolar 1 caractere para a direita
  }
}
