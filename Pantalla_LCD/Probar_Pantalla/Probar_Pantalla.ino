#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inicializar la pantalla LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Asegúrate de que la dirección I2C sea la correcta

void setup() {
  // Inicializar la pantalla LCD
  lcd.begin(16, 2);
  lcd.backlight();  // Encender el retroiluminado

  // Mostrar "Hola mundo" en la pantalla
  lcd.setCursor(0, 0);
  lcd.print("Programa Cerrar");
  lcd.setCursor(0, 1);
  lcd.print("Abrir puerta");
}

void loop() {
  // Tu código aquí (si es necesario)
}
