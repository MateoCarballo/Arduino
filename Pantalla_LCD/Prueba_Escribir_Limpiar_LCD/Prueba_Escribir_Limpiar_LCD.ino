#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inicializar la pantalla LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Asegúrate de que la dirección I2C sea la correcta

void setup() {
  
  lcd.begin(16, 2);// Inicializar la pantalla LCD
  lcd.backlight();// Encender el retroiluminado
}

void loop() {
  // Limpiar la pantalla
  lcd.clear();

  // lcd.setCursor(0, 0); Primera opcion es la posicion en la fila (0-15) y la segunda el numero de fila (0-1)
  lcd.setCursor(0, 0);
  lcd.print("0123456789ABCDEF");
  
  delay(2000);

  // Limpiar la pantalla
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("||||||||||||||||");
  lcd.setCursor(0, 1);
  lcd.print("||||||||||||||||");
  

  delay(2000);
}
