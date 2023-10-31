#include <LiquidCrystal.h>

// Referência para o display lcd
int lcd_rs = 12, lcd_en = 11, lcd_d4 = 4, lcd_d5 = 5, lcd_d6 = 6, lcd_d7 = 7;

// Criando um objeto que controla o lcd
LiquidCrystal lcd(lcd_rs, lcd_en, lcd_d4, lcd_d5, lcd_d6, lcd_d7);

const int pinoSensor = A0; // Localização do pino do sensor de umidade
const int porcentagemSeco = 60; // Porcentagem que indica que o solo esta seco
int umidadeSolo = 0;

uint8_t icone[] = {0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f};

void apresentacao(){
  lcd.setCursor(3, 0);

  // Exibe a mensagem "Bem vindo!" no display
  String mensagem = "Bem vindo!";
  for(byte i = 0; i < mensagem.length(); i++){
    lcd.print(mensagem[i]);
    delay(100);
  }

  // Exibe o carregamento
  for(byte i = 0; i < 16; i++){
    lcd.setCursor(i, 1);
    lcd.write(byte(0));
    delay(100);
  }

  // Move os caracteres para a esquerda
  for(byte i = 0; i < 16; i++){
    lcd.scrollDisplayLeft();
    delay(50);
  }

  delay(100);
}

void setup() { 

  lcd.createChar(0, icone); // Armazena na memoria o icone de carregamento 

  lcd.begin(16, 2); // Inicia o display lcd 16x2

  Serial.begin(9600);

  apresentacao();
}

void avisarUsuario(){
  lcd.clear();
  lcd.print("Avisando Usuario");

  Serial.println("Planta precisa ser regada!"); // Enviará a mensagem via USB, onde na aplicação java será utilizado
  
  delay(2000);
}

void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Controle Umidade");

  while(true) {
    lcd.setCursor(0, 1);

    lcd.print("Umidade: ");

    umidadeSolo = analogRead(pinoSensor); // Obtendo os valores do sensor de umidade do solo
    umidadeSolo = map(umidadeSolo, 0, 1023, 0, 100); // Mapeia o valor da umidade para valores de 0 a 100

    lcd.print(umidadeSolo);
    lcd.print(" %   ");

    // Se a porcentagem da umidade for inferior a porcentagemSeco (60) encerra o while
    if(umidadeSolo < porcentagemSeco)
      break;

    delay(1000);
  }

  avisarUsuario();

}
