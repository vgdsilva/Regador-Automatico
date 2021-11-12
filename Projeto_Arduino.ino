#include <IRremote.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal.h>

#define DHTTYPE DHT11 // Sensor DHT11
#define DHTPIN 2 // Pino do Sensor
#define Sensor1 A0
#define Sensor2 A1
#define Sensor3 A2
#define Sensor4 A3
int bomba = 10;
IRrecv receptor(11);
decode_results resultado;


DHT_Unified dht(DHTPIN, DHTTYPE); // configurando o Sensor DHT - pino e tipo
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // Pinos lcd
uint32_t delayMS = 1000; // variável para atraso no tempo
int typemode = 0;
int isTimerselected = 0;
int wl = 0;
int timer = 0;
int count = 0;
int minuto = 0;
int hora = 0;

void setup() {
  pinMode(bomba,OUTPUT);
  digitalWrite(bomba, HIGH);
  lcd.begin(16, 2);
  delay(500); // delay de 0,5

  Serial.begin(9600); // monitor serial 9600 bps
  dht.begin(); // inicializa a função
  Serial.println("Usando o Sensor DHT");
  
  sensor_t sensor;
  receptor.enableIRIn();

}

void loop() {
  if(isTimerselected == 0){
    if(wl == 0){
      lcd.clear();
      lcd.print("Bem vindo");
      lcd.setCursor(0, 1); //coluna / linha
      lcd.print("ligando... ");
      delay(2000);
      wl = 1;
    }else{
      lcd.clear();
      lcd.print("Tempo (h): ");
      lcd.print(timer);
    }

    if(receptor.decode(&resultado)){
      Serial.println(resultado.value);
    
      switch(resultado.value){
        case 16753245 :
          timer = (timer * 10) + 1;
          break;
         case 16736925 :
          timer = (timer * 10) + 2;
          break;
         case 16769565 :
          timer = (timer * 10) + 3;
          break;
         case 16720605 :
          timer = (timer * 10) + 4;
          break;
         case 16712445 :
          timer = (timer * 10) + 5;
          break;
         case 16761405 :
          timer = (timer * 10) + 6;
          break;
         case 16769055 :
          timer = (timer * 10) + 7;
          break;
         case 16754775 :
          timer = (timer * 10) + 8;
          break;
         case 16748655 :
          timer = (timer * 10) + 9;
          break;
         case 16750695 :
          timer = (timer * 10) + 0;
          break;
         case 16726215 :
          isTimerselected = 1;
         break;
         
      }

      receptor.resume();
    }
    
    delay(500);
  }else{
    
  
  lcd.clear();
  lcd.setCursor(0, 0);

  int sensor1Value = analogRead(Sensor1);
  int sensor2Value = analogRead(Sensor2);
  int sensor3Value = analogRead(Sensor3);
  int sensor4Value = analogRead(Sensor4);
  int mediaSensor = ( sensor1Value + sensor2Value + sensor3Value + sensor4Value ) / 4;

  lcd.print("Modo:");
  if (typemode == 0) {
    lcd.print("A");
  } else {
    lcd.print("M");
  }
  lcd.print(" ");
  lcd.print(hora);
  lcd.print(":");
  lcd.print(minuto);
  lcd.print(":");
  lcd.print(count);
  
  lcd.setCursor(0, 1); //coluna / linha
  lcd.print("Media UMI: ");
  lcd.print(mediaSensor);
  delay(delayMS); // atraso entre as medições
  count++;

  if(count == 60){
    count = 0;
    minuto++;
  }

  if(minuto == 60){
    count = 0;
    minuto = 0;
    hora++;
  }
  


  if(receptor.decode(&resultado)){
    Serial.println(resultado.value);
    if(resultado.value == 16753245){
      typemode = 1;
      Serial.println("aaaa");
    }else if(resultado.value == 16736925){
      typemode = 0;
    }else if(resultado.value == 16769565){
      lcd.clear();
      Regando();
    }
    receptor.resume();
  }

  // IF para validar se o solo for seco ou não
  if (((mediaSensor >= 682) && hora >= timer) && typemode == 0) {
    lcd.clear();  
    Regando();
    count = 0;
    minuto = 0;
    hora = 0;

  } else if (mediaSensor >= 341 && mediaSensor < 682) {
    //Serial.print("Umidade da Terra esta Medio " + mediaSensor);

  } else if (mediaSensor >= 0 && mediaSensor < 341) {
    //Serial.print("Umidade da terra esta Alta " + mediaSensor);

  }

  }
  
}

void Regando() {
  Serial.println("aaaaaaaaaaaaaaaaa");
  digitalWrite(bomba, LOW);
  lcd.print("Regando...");
  lcd.setCursor(0, 1);

  delay(10000);
  digitalWrite(bomba, HIGH);
}
/*
  const int pinoSensor = A0; //PINO UTILIZADO PELO SENSOR
  int valorLido; //VARIÁVEL QUE ARMAZENA O PERCENTUAL DE UMIDADE DO SOLO
  int analogSoloSeco = 400; //VALOR MEDIDO COM O SOLO SECO (VOCÊ PODE FAZER TESTES E AJUSTAR ESTE VALOR)
  int analogSoloMolhado = 150; //VALOR MEDIDO COM O SOLO MOLHADO (VOCÊ PODE FAZER TESTES E AJUSTAR ESTE VALOR)
  int percSoloSeco = 0; //MENOR PERCENTUAL DO SOLO SECO (0% - NÃO ALTERAR)
  int percSoloMolhado = 100; //MAIOR PERCENTUAL DO SOLO MOLHADO (100% - NÃO ALTERAR)
  void setup(){
  Serial.begin(9600); //INICIALIZA A SERIAL
  Serial.println("Lendo a umidade do solo..."); //IMPRIME O TEXTO NO MONITOR SERIAL
  delay(2000); //INTERVALO DE 2 SEGUNDOS
  }
  void loop(){
  valorLido = constrain(analogRead(pinoSensor),analogSoloMolhado,analogSoloSeco); //MANTÉM valorLido DENTRO DO INTERVALO (ENTRE analogSoloMolhado E analogSoloSeco)
  valorLido = map(valorLido,analogSoloMolhado,analogSoloSeco,percSoloMolhado,percSoloSeco); //EXECUTA A FUNÇÃO "map" DE ACORDO COM OS PARÂMETROS PASSADOS
  Serial.print("Umidade do solo: "); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print(valorLido); //IMPRIME NO MONITOR SERIAL O PERCENTUAL DE UMIDADE DO SOLO
  Serial.println("%"); //IMPRIME O CARACTERE NO MONITOR SERIAL
  delay(1000);  //INTERVALO DE 1 SEGUNDO
  }
*/
