#include <Arduino.h>
#include <Wire.h>
#include <DHT.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define DHTTYPE DHT11
//************** OLED ******************
//************* SCREEN******************
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
const int DHTPin = 4;

DHT dht(DHTPin, DHTTYPE);
void ver_pantalla(String, String);

hw_timer_t *My_timer = NULL;
void IRAM_ATTR onTimer(){
  //
  float h = dht.readHumidity();//read humidity
 	float t = dht.readTemperature();// Read temperature as Celsius (the default)

	String str_h = String(h);
	String str_tem = String(t);
	
  String serial_str_h = "Humidity: " + str_h;
  String serial_str_tem = "temperature: " + str_tem;
  
  //Monitoreo Serial
	Serial.println(serial_str_h);
	Serial.println(serial_str_tem);

  //Monitoreo pantalla LCD
  ver_pantalla(str_h,str_tem);
}

void setup() {
  Serial.begin(115200);
  pinMode(DHTPin,INPUT);

  //timer interrupt
  My_timer = timerBegin(0, 80, true);
  timerAttachInterrupt(My_timer, &onTimer, true);
  timerAlarmWrite(My_timer, 10000000, true);//each 10s
  timerAlarmEnable(My_timer); //Just Enable
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  Serial.println("OLED begun");
  delay(1000);
  display.clearDisplay(); // Clear the buffer.
  display.display();

  dht.begin();

}

void loop() {

}

void ver_pantalla(String str_h, String str_tem) {

  display.clearDisplay();
  //Monitoreo por pantalla
	display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(20,20);
  display.print(str_h + " %");
  display.display();
  delay(3000);//clear each 3s
	display.clearDisplay();

  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(20,20);
  display.print(str_tem + " C");
  display.display();
  
}
