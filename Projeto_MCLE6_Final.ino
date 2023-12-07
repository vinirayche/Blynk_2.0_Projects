#define BLYNK_TEMPLATE_ID "TMPL2ZJArM8QK"
#define BLYNK_TEMPLATE_NAME "Projeto MCLE6 Alerta de Luz"
#define BLYNK_AUTH_TOKEN "9w9ywygOmd-U4BuwBr5pT5rsi8gUrVtb"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer; // Tempo real da Notificação

char ssid[] = "MCLE6";
char pass[] = "01000001";

const int LDR = 4; // Pino D2
const int LED = 14; // Pino D5
const int BUZZ = 5; // Pino D1
int x=0; // Variável para o controle do LDR

void notifyLuz() // Notificação
{
  int isButtonPressed = digitalRead(LDR);
  if (isButtonPressed==0 && x==0) {

    Serial.println("Luz no ambiente");  
    //Blynk.email("testemail@gmail.com", "Alerta", "Luz Detectada!");
    Blynk.logEvent("alerta_luz","Alerta Luz");
  
    x=1;
  }
  else if (isButtonPressed==1)
  {
    x=0;
  }
}

void setup()
{
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  
  pinMode(BUZZ, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(LDR, INPUT_PULLUP);
  digitalWrite(BUZZ, LOW);
  timer.setInterval(5000L,notifyLuz); // Inicia o timer da notificação

}

void loop()
{
  
  Blynk.run();
  timer.run(); // Atualiza o tempo de notificação
  
  if(digitalRead(LDR)==LOW)
  { 
    tone(BUZZ, 150);
    digitalWrite(LED, HIGH);
    delay(150);

    noTone(BUZZ);
    digitalWrite(LED, LOW);
    delay(150);
  }
  else
  {
    noTone(BUZZ);
    digitalWrite(LED, LOW);
  }
}
