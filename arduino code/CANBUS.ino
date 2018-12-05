void CAN_BUS_DATA ()
{
  CAN.readMsgBuf(&can_len, can_buf);                                  // Henter CanBus Data
  canId = CAN.getCanId();                                             // Henter Telegrams ID Nr.

// Fan Speed - START
  if (canId == 513)
    {
      Fan_Speed = omregn_bit_xy(can_buf[3], can_buf[2]) /25;          //
    }
// Fan Speed - STOP

// Central Varme Pumpe og Varmelegme - START
  if (canId == 582)
    {
      if (can_buf[0] > 0)
        {
          Pumpe_Central = 1;                                          // CentralVarme Pumpe On
        }
      else
        {
          Pumpe_Central = 0;                                          // CentralVarme Pumpe Off
        }

      if (can_buf[0] >= 32 && can_buf[0] <= 36)
        {
          VarmeLegme = 1;                                             // Varmelegme On
        }
      else
        {
          VarmeLegme = 0;                                             // Varmelegme Off
        }
    }
// Central Varme Pumpe og Varmelegme - STOP
    
// Fyr ON eller Pause START - Update = 250ms
  if (canId == 592)
    {
      Fyr_Status = can_buf[0];                                        // Er Fyret i pause eller drift
    }
// Fyr ON eller Pause STOP

// Temperatur Kedel & VVB START - Update = 250ms
if (canId == 710)
  {
    Temp_Kedel = omregn_bit_xy(can_buf[1], can_buf[0]);               // Temp Kedel, konverteres via Temp Tabel i SW/PHP.
    Temp_Central = omregn_bit_xy(can_buf[7], can_buf[6]);             // Temp Central Varme, konverteres via Temp Tabel i SW/PHP.
    Temp_VVB = omregn_bit_xy(can_buf[5], can_buf[4]);                 // Temp VVB, konverteres via Temp Tabel i SW/PHP.
  }
// Temperatur Kedel & VVB - STOP

// LAMBDA - START
  if (canId == 720)
    {
      if (Fyr_Status == 1)
        {
          Lambda_o2 = omregn_bit_xy(can_buf[7], can_buf[6]);          // Ilt % i 1000. Skal /100 i SW/PHP
        }
      else
        {
          Lambda_o2 = 0;                                              // Ilt = 0, da Lambda er slukket.
        }
    }
// LAMBDA - STOP

// Turbulatorerne - START
  if (canId == 838)
    {
      Turbulatorerne = can_buf[2];                                    // 1 = Rens Aktiv, 0 = Pause.
    }
// Turbulatorerne - STOP


// VVB Pumpe, Snegl og Pille puls/Forbrug - START
  if (canId == 1094)
    {
      Pumpe_VVB = can_buf[2];                                         // Køre VVB Pumpen
  
      if (can_buf[0] == 1)                                            // Snegl køre - Beregn Pilleforbrug.
        {
          if (pille_kg_run == 0)                                      // Check om der er en start tid. hvis ikke så sæt den
            {
              pille_kg_run = 1;                                       // Set Start tiden
              pille_kg_start = millis();                              // Start tiden i millis
            }
          Snegl = 1;                                                  // Snegl køre
        }
      else // Snegl køre ikke.
        {
          if (pille_kg_run == 1)                                      // Check om der er en start tid og så beregn forbrug.
            {
              pille_kg_run = 0;
              pille_kg_stop = millis();
              Modul_PP = pille_kg_stop - pille_kg_start;              // Tiden sneglen har kørt i millis
              Modul_KG = Modul_KG + (Modul_PP * Pille_KG_Faktor);   
//              Serial.println (Modul_PP);
//              Serial.print ("Plus = ");
//              Serial.println ( Modul_PP * Pille_KG_Faktor );
//              Serial.print ("KG = ");
//              Serial.println ( Modul_KG, 4 );
            }
          Snegl = 0;
        }

    }
// VVB Pumpe, Snegl og Pille puls/Forbrug - STOP

// Rist Pos, Ude Temp, Lux  - START
  if (canId == 1222)
    {
      Rist_Pos = can_buf[3];                                          // Rist Kører on/off
      Temp_Ude = omregn_bit_xy(can_buf[5], can_buf[4]);               // Ude Temp, konverteres via Temp Tabel i SW/PHP.
      LUX = 256-((omregn_bit_xy(can_buf[7],can_buf[6]))*lux_faktor);  // Lux faktor 0-255
    }
//  Rist Pos, Ude Temp, Lux  - STOP



}
