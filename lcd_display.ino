#include <LiquidCrystal.h>
#include <dht_nonblocking.h>

#define DHT_SENSOR_TYPE DHT_TYPE_11
static const int DHT_SENSOR_PIN = 2;
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);


void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
}

static bool measure_environment( float *temperature, float *humidity )
{
  static unsigned long measurement_timestamp = millis( );

  /* Measure once every four seconds. */
  if( millis( ) - measurement_timestamp > 3000ul )
  {
    if( dht_sensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis( );
      return( true );
    }
  }

  return( false );
}

void loop() {

  float temperature;
  float humidity;
  int farenheit;

  /* Measure temperature and humidity.  If the functions returns
     true, then a measurement is available. */
  if( measure_environment( &temperature, &humidity ) == true )
  {

    farenheit = int((int(temperature) * 1.8) + 32);
    
    Serial.print( "T = " );
    Serial.print( temperature, 1 );
    Serial.print( " deg. C, H = " );
    Serial.print( humidity, 1 );
    Serial.println( "%" );
    lcd.setCursor(0,0);
    lcd.print("Temp: "+String(farenheit)+"F/"+String(int(temperature))+"C");
    lcd.setCursor(0,1);
    lcd.print("Humidity: "+String(int(humidity))+"%");
    
    delay(2147483647);
    delay(2147483647);
    delay(2147483647);
    delay(2147483647);
    delay(2147483647);
    
    lcd.clear();
  }

  
}
