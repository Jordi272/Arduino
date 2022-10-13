/**
 *   @author     Jordi Domenech
 *   @date       2022
 *   @brief      Beacon.ino
 *   @pre        Lee el README
 */

// -*- mode: c++ -*-
// ----------------------------------------------------
// Ejemplo IBeaconBasico.ino
// Adaptado de https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide/adafruitbluefruit
// Jordi Bataller Mascarell
// ----------------------------------------------------
#include <bluefruit.h>
// ----------------------------------------------------
// setup
// ----------------------------------------------------
/**
 * @brief se encarga de iniciar la placa y inciar el advertising
 */
void setup() {
   //
   //
   //
   Serial.begin(115200);
   //si se comenta la linease elimina la necesidad de encender el monitor serie 
   while ( !Serial ) delay(10);

   Serial.println("-----------------------\n");
   Serial.println(" PRUEBAS iBeacon  ");
   Serial.println("-----------------------\n");

   //
   // Initialise the Bluefruit module
   //
   Serial.println("Initialise the Bluefruit nRF52 module");
   Bluefruit.begin();

   //
   // Set the advertised device name (keep it short!)
   //
   Serial.println("Setting Device Name to Jordi Domenech " );

   Bluefruit.setName("Jordi_Domenech");
   Bluefruit.ScanResponse.addName();

   //
   //
   //iniciamos la transmisión del beacon
   startAdvertising();

   //
   //
   //
   Serial.println("\nAdvertising");

} // setup()
 

//Función startAdvertising()-->

// ----------------------------------------------------
// ----------------------------------------------------
/**
 * @brief añade todos los parámetros a la trama del Beacon
 */
void startAdvertising() {

   Serial.println( " startAdvertising() " );

   Serial.println( " Bluefruit.Advertising.stop(); ");
   Bluefruit.Advertising.stop(); // ya lo enchufo luego

   //
   // Advertising packet
   //Paquete de advertising
   Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
   Bluefruit.Advertising.addTxPower();

   //
   //
   //


   // Añadimos el nombre
   Serial.println( " Bluefruit.Advertising.addName(); " );
   Bluefruit.Advertising.addName();

   //
   //
   //
   Serial.println( " Bluefruit.Advertising.setBeacon( elBeacon ); ");

   //Asignamos el UUID del dipositivo
   uint8_t beaconUUID[16] = {
     'E', 'P', 'S', 'G', '-', 'G', 'T', 'I',
     '-', 'P', 'R', 'O', 'Y', '-', '3', 'A'
     };

   //introducimos en el beacon los datos (UUID, Major, minor, Tx)
   BLEBeacon elBeacon( beaconUUID, 1567, 34, 73 );
   elBeacon.setManufacturer( 0x004c ); // aple id
   Bluefruit.Advertising.setBeacon( elBeacon );

   //
   //
   //
   Bluefruit.Advertising.restartOnDisconnect(true);
   Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
   Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
   Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds

   Serial.println( " Bluefruit.Advertising.start(0);" );

} // startAdvertising ()
 

//Proceso loop()

// ----------------------------------------------------
// ----------------------------------------------------
/**
 * @brief inicializa el contador
 */
namespace Loop {
   int cont = 0;
};
// ....................................................

/**
 * @brief se cuenta lo que se transmite
 */
void loop() {
   //vamos contando lo que se transmite
   using namespace Loop;

   cont++;

   delay(1000);

   Serial.print( " ** loop cont=" );
   Serial.println( cont );
} // ()
// ----------------------------------------------------
// ----------------------------------------------------
// ----------------------------------------------------
// ----------------------------------------------------
