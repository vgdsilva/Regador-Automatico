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

LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // Pinos lcd

int soloSeco = 300; //Umidade abaixo de 300 indica que o solo ta seco
int soloUmido = 700; //Umidade acima de 700 indica que esta umido o solo

DHT_Unified dht(DHTPIN, DHTTYPE); // configurando o Sensor DHT - pino e tipo
uint32_t delayMS = 500; // variável para atraso no tempo

int typemode = 0;

void setup() {
  lcd.begin(16, 2);
  delay(500); // delay de 0,5

  Serial.begin(9600); // monitor serial 9600 bps
  dht.begin(); // inicializa a função
  Serial.println("Usando o Sensor DHT");
  sensor_t sensor;

}

void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);
  int sensor1Value = analogRead(Sensor1);
  int sensor2Value = analogRead(Sensor2);
  int sensor3Value = analogRead(Sensor3);
  int sensor4Value = analogRead(Sensor4);
  int mediaSensor = ( sensor1Value + sensor2Value + sensor3Value + sensor4Value ) / 4;

  Serial.println(mediaSensor);

  
//
    lcd.print("Modo: ");

    if (typemode == 0){
      lcd.print("Automatico");
    }else{
      lcd.print("Manual");      
    }
    
    lcd.setCursor(0, 1); //coluna / linha
    lcd.print("Media UMI: ");
    lcd.print(mediaSensor);
    delay(delayMS); // atraso entre as medições

    
//  sensors_event_t event; // inicializa o evento da Temperatura
//  dht.temperature().getEvent(&event); // faz a leitura da Temperatura
//  if (isnan(event.temperature)) {// se algum erro na leitura
//    Serial.println("Erro na leitura da Temperatura!");
//  } else {// senão
//    Serial.print("Temperatura: "); // imprime a Temperatura
//    Serial.print(event.temperature);
//
//    Serial.println(" *C");
//  }
//  dht.humidity().getEvent(&event); // faz a leitura de umidade
//  if (isnan(event.relative_humidity)) {// se algum erro na leitura
//    Serial.println("Erro na leitura da Umidade!");
//  } else {// senão
//    Serial.print("Umidade: "); // imprime a Umidade
//    Serial.print(event.relative_humidity);
//    Serial.println("%");
//  }
}
