/*
 * PilleStat V0.4 - 27/04-2016
 * Design og kode lavet af Kim Andreasen
 */
  const unsigned int Modul_ID = 1000;                         // PilleStat Modul ID
  const unsigned long BAUD_RATE = 115200;                     // Set BR på Serial porten
  const float lux_faktor = 0.062591687;                       // 4090 = 0 lux, 0 = 255 lux.
  const int TonePin = 6;                                      // Pin til Buzzer.

//  Alarm koder - START
  bool Update_webtid = 0;                                     // Update tiden med internet. 0 = OK
//  Alarm koder - SLUT
  

// Loop tiden for sende data - START
  const unsigned int UDP_IV = 1000;                           // Interval for sende UDP Telegram til Lokalnet.
  unsigned long UDP_PM = 0;                                   // Tiden for sidste send data. 1 gang pr sek.
  unsigned long UDP_CM = 0;                                   // Tilden nu. Opdateres i starten af loopen. 
  
  const unsigned int WEB_IV = 60000;                          // Interval for sende TCP Telegtam til WEB. 1 gang pr min.
  unsigned long WEB_PM = 0;                                   // Tiden for sidste send data.
  unsigned long WEB_CM = 0;                                   // Tilden nu. Opdateres i starten af loopen. 

  const unsigned int XXX_IV = 60000;                          // Interval for ???
  unsigned long XXX_PM = 0;                                   // Tiden for sidste send data.
  unsigned long XXX_CM = 0;                                   // Tilden nu. Opdateres i starten af loopen. 

// Loop tiden for sende data - SLUT

// Netværk og SD kort opsætning - START
  #include <EthernetV2_0.h>                                   // TCP/IP Lib
  #include <EthernetUdpV2_0.h>                                // UDP Lib
  #include <SD.h>                                             // SD Kort Lib
  #define W5200_CS 10                                         // Definere Netværkskortet Pin SS
  #define SDCARD_CS 4                                         // Definere SD kort Pin SS
  byte mac[6];                                                // MAC Adressen for Netværkskortet, Samme som ModulID
  byte ip[4];                                                 // IP Adressen for Netværkskortet
  byte subnet[4];                                             // SUBNET Adressen for Netværkskortet
  byte gateway[4];                                            // GATEWAY Adressen for Netværkskortet
  byte dnsserver[4];                                          // DNS Adressen for Netværkskortet

  const char serverName[] = "www.pillestat.eu";               // Link til PilleStat Web adresse
  const int serverPort = 80;                                  // Web Server's port #
  const char pageName[] = "/modtag_data.php";                 // Siden som data skal sendes til
  EthernetClient client;                                      // Starter ETH klienten  
  EthernetUDP Udp;
  #define UDP_TX_PACKET_MAX_SIZE 41                           // Ændre Size så den er plads til alt i Telegrammet
  IPAddress fjernserver(255, 255, 255, 255);                  // Hvor UDP data sendes til.
  unsigned int RemotePort = 8282;                             // Port UDP Sender På
  unsigned int localPort = 8282;                              // local port to listen on
  byte packetBuffer[UDP_TX_PACKET_MAX_SIZE];                  // Buffer til at sende og modtage UDP Data med
// Netværk og SD kort opsætning - SLUT

// START - Groove High Temperature Sensor
  #include "High_Temp.h"                                      // Inkludere biblioteker
  HighTemp rog_sensor(A10, A11);                              // Røggas Temperatur sensor
  HighTemp frem_sensor(A12, A13);                             // Fremløbs Temperatur sensor
  HighTemp tilbage_sensor(A14, A15);                          // Returløbs Temperatur sensor
  int sample_count = 0;                                       // Counter for antal læsninger
  const int sample_num = 344;                                 // Hvor mange gange det skal læse for at få gennemsnittet 86 passer med ca 1 sek.
  float Modul_FremL = 0.00;                                   // Fremløbs temperatur fra PilleStat sensor
  float Modul_FremL_Sum = 0.00;                               // Gennemsnits temp for Fremløb
  float Modul_ReturL = 0.00;                                  // Returløbs temperatur fra PilleStat sensor
  float Modul_ReturL_Sum = 0.00;                              // Gennemsnits temp for Returløb
  float Modul_Gas = 0.00;                                     // RøgGas temperatur fra PilleStat sensor
  float Modul_Gas_Sum = 0.00;                                 // Gennemsnits temp for Røggas
  float Modul_FB = 0.00;                                      // Omgivelses temperaturen i sensor boksen for Frem, Returløb og RøgGas. Kommer fra Røggas modulet.
  float Modul_FB_Sum = 0.00;                                  // Gennemsnits temp for sensor boksen for Frem, Returløb og RøgGas
  float Modul_SB = 0.00;                                      // Omgivelses temperaturen i Styrings boksen. Kommer fra RTC modulet
  float Modul_SB_Sum = 0.00;                                  // Gennemsnits temp for Styrings boksen.
// STOP - Groove High Temperature Sensor

// RTC - START
  #include <DS3231.h>                                         // DS3231 RTC Lib.
  DS3231  rtc(SDA, SCL);                                      // Definere Pins.
  Time  t;                                                    // 
// RTC - SLUT

// START - CANBUS
  #include <SPI.h>                                            // Inkludere biblioteker
  #include "mcp_can.h"                                        // CanBUS Lib.
  INT32U canId = 0x000;                                       // Sæt CanBUS modul ID
  MCP_CAN CAN(9);                                             // Sæt CanBUS interface PIN
  unsigned char can_len = 0;                                  // Til LEN af CanBUS data
  unsigned char can_buf[8];                                   // Buffer til CanBUS data
  char str[20];                                               // CanBUS LEN af hele data.
  bool Fyr_Status = 0;                                        // Brænder on/off
  bool VarmeLegme = 0;                                        // Varmelegme on/off
  bool Turbulatorerne = 0;                                    // Renser fyret on/off
  bool Pumpe_Central = 0;                                     // Pumpe for Central Varme
  bool Pumpe_VVB = 0;                                         // Pumpe for VVB
  bool Rist_Pos = 0;                                          // Rist on/off
  bool Snegl= 0;                                              // Snegle on/off
  byte LUX = 0;                                               // Lux
  byte Fan_Speed = 0;                                         // Fan Speed
  int Lambda_o2 = 0;                                          // Ilt %
  int Temp_Kedel = 0;                                         // Kedel Temp
  int Temp_Central = 0;                                       // Central Varme Temp
  int Temp_VVB = 0;                                           // VVB Temp
  int Temp_Ude = 0;                                           // Ude Temp

  unsigned int Modul_PP = 0;                                  // PillePuls i millisekunder
  float Modul_KG = 0.00;                                      // Total Pilleforbrug
  float Modul_KG_sidst_gemt = 0.00;                           // Total pilleforbrug gemt på SD
  float Pille_KG_Faktor = 0.00;                               // Pille KG Faktoren til beregning af antal gram brugt når sneglen køre.

  unsigned long pille_kg_start = 0;                           // Timer Start put piller i fyret
  unsigned long pille_kg_stop = 0;                            // Timer Stop put piller i fyret
  boolean pille_kg_run = 0;                               // Kør beregning for pilleforbrug
// STOP - CANBUS



void setup() 
{
  Serial.begin(BAUD_RATE);                                    // Starter Serial Port Com. Kan slettes når alt er færdig
  rtc.begin();                                                // Starter RTC tiden
  pinMode(W5200_CS,OUTPUT);                                   // Sæt CS pin til output mode.
  digitalWrite(W5200_CS, HIGH);                               // Slukker for Netværket, så SD kan bruges
  pinMode(SDCARD_CS, OUTPUT);                                 // Sæt CS pin til output mode.
  if (!SD.begin(SDCARD_CS))                                   // Check om SD kortet virker
    {
//      Serial.println("SD initialiseringsprocessen Fejl!");    // SD Virker ikke.
      return;                                                 // 
    }
//  Serial.println("SD initialiseringsprocessen OK");           // SD kortet Virker
  digitalWrite(SDCARD_CS, HIGH);                              // Slukker for SD, så netværk kan bruges.

 //gem_pille_kg(30170.80);                                      // Skriv Antal KG til SD kortet
  Modul_KG = hent_pille_kg();                                 // Læser Antal KG værdi fra SD kortet
  Modul_KG_sidst_gemt = Modul_KG;                             // Sætter sidst gem kg på SD til samme værdi som der bliver indlæs nu

//  gem_pf(14.0);                                               // Gem pille KG Faktoren på SD. = Antal KG piller pr time.
  Pille_KG_Faktor = (hent_pf()/3600000);                        // Hent Pille KG Faktoren og * med tid. Ved 14 kg pr time er den = 0.000003888888549.

  hent_netopset();                                            // Henter netværksopsætningen fra SD og starter netkortet.
  Udp.begin(localPort);                                       // Starter UDP

// START - Groove High Temperature Sensor
  rog_sensor.begin();                                         // Start Sensor Røggas Temperatur
  frem_sensor.begin();                                        // Start Sensor Fremløbs Temperatur
  tilbage_sensor.begin();                                     // Start Sensor Returløbs Temperatur
// STOP - Groove High Temperature Sensor


// START - CANBUS
  START_INIT:
    if (CAN_OK == CAN.begin(CAN_125KBPS))
      {
//        Serial.println ("CanBus OK");
      }
    else
    {
      delay(100);
      goto START_INIT;
  }
// STOP - CANBUS

// Opdatere RTC med WebTid - START
  webtid_igen:                                                // Loop Back hvis der ikke er internet
//  Serial.println("Opdatere RTC Dato/Tid");
  webUnixTime();                                              // Opdatere RTC med WEB Tid.
  if (Update_webtid == 1)                                     // Dato/Tid er opdateret, Start Programmet
    {
//      Serial.println("Opdateret, Starter programmet");
//      vis_dato_tid ();                                        // Viser Dato/tid
      musik_alt_ok ();                                        // Spiller Musik, Alt OK
    }
  else                                                        // Ingen forbindelse til Internette, Prøver igen
    {
//      Serial.println("Ikke Opdateret");
      musik_beep_alarm ();                                    // Spiller Musik, Alarm
      goto webtid_igen;                                       // Hopper tilbage til LOOP og prøver igen.
  }
// Opdatere RTC med WebTid - SLUT


//wdt_enable(WDTO_8S);                                    // Software Reset - Sæt tiden - 15MS, 30MS, 60MS, 120MS, 250MS, 500MS, 1S, 2S, 4S, 8S
}  // end of setup




void loop() 
{
  //wdt_reset();                                              // Software Reset - nulstil timeren.

  UDP_CM = millis();                                          // Synk timer for UDP Telegram.
  WEB_CM = millis();                                          // Synk timer for WEB Telegram.
  XXX_CM = millis();                                          // Synk timer for ??? Telegram.
  
  hent_sensor_data ();                                        // Henter alle temp fra alle sensors.
    
  if ((unsigned long)(UDP_CM - UDP_PM) >= UDP_IV)
    {                                                         // TIDSLOOP - START
      UDP_PM = UDP_CM;                                        // Sætter tiden for næste synk.
      make_PB ();                                             // Byg Telegram
      udp_send ();                                            // Send UDP Telegram på lokalnettet.
      serial_send ();
    }                                                         // TIDSLOOP - STOP

  if ((unsigned long)(WEB_CM - WEB_PM) >= WEB_IV && pille_kg_run == 0)
    {                                                         // TIDSLOOP - START
      WEB_PM = WEB_CM;                                        // Sætter tiden for næste synk.
      make_PB ();                                             // Byg Telegram
      Send_Web_Data ();                                       // Send TCP Telegram til PilleStat.
      musik_beep_q ();                                        // Kort Beep hver gang der sendes data til PilleStat
    }                                                         // TIDSLOOP - STOP

  if ((unsigned long)(XXX_CM - XXX_PM) >= XXX_IV)
    {                                                         // TIDSLOOP - START
      XXX_PM = XXX_CM;                                        // Sætter tiden for næste synk.
    }                                                         // TIDSLOOP - STOP

  if (CAN_MSGAVAIL == CAN.checkReceive())                     // Hvis der er CanBus Data
    {
      CAN_BUS_DATA ();                                        // Afkode CANBUS Data.
    } 

  if (Modul_KG - Modul_KG_sidst_gemt >= 1.00)                 // Hvis der er brugt 1 kg pille, så gem på SD.
    {
      Modul_KG_sidst_gemt = Modul_KG;                         // Check tallet for næste gang.
      gem_pille_kg(Modul_KG);                                 // Gem antal kg til SD kortet
    }



}  // end of loop

