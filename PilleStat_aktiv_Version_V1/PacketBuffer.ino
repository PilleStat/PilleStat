void make_PB ()
{
  int temp_beregn = 0;
  long temp_beregn_f = 0;
  
  packetBuffer[0] = (int)((Modul_ID >> 8) & 0XFF);              // Modul ID
  packetBuffer[1] = (int)((Modul_ID & 0XFF));                   // Fra 1.000 til 65.536

  unsigned long Unix_Tid = hent_rtc();                          // Hent Unix dato/tid
  packetBuffer[2] = (int)((Unix_Tid >> 24) & 0XFF);             // Split til 4 bytes
  packetBuffer[3] = (int)((Unix_Tid >> 16) & 0XFF);             // 
  packetBuffer[4] = (int)((Unix_Tid >> 8) & 0XFF);              // 
  packetBuffer[5] = (int)((Unix_Tid & 0XFF));                   // 

  temp_beregn = ( Modul_FremL * 100 );                          // Hent Fremløbs Temp * 100
  packetBuffer[6] = (int)((temp_beregn >> 8) & 0XFF);           // Split til 2 bytes
  packetBuffer[7] = (int)((temp_beregn & 0XFF));                //

  temp_beregn = ( Modul_ReturL * 100 );                         // Hent Returløbs Temp * 100
  packetBuffer[8] = (int)((temp_beregn >> 8) & 0XFF);           // Split til 2 bytes
  packetBuffer[9] = (int)((temp_beregn & 0XFF));                //

  temp_beregn = ( Modul_Gas * 100 );                            // Hent RøgGas Temp * 100
  packetBuffer[10] = (int)((temp_beregn >> 8) & 0XFF);          // Split til 2 bytes
  packetBuffer[11] = (int)((temp_beregn & 0XFF));               //

  temp_beregn = ( Modul_FB * 100 );                             // Hent SensorBoks Temp * 100
  packetBuffer[12] = (int)((temp_beregn >> 8) & 0XFF);          // Split til 2 bytes
  packetBuffer[13] = (int)((temp_beregn & 0XFF));               //

  temp_beregn = ( Modul_SB * 100 );                             // Hent Styringsboks Temp * 100
  packetBuffer[14] = (int)((temp_beregn >> 8) & 0XFF);          // Split til 2 bytes
  packetBuffer[15] = (int)((temp_beregn & 0XFF));               //

  packetBuffer[16] = (int)((Modul_PP >> 8) & 0XFF);             // Hent PillePlus tid i Millisekunder
  packetBuffer[17] = (int)((Modul_PP & 0XFF));                  // Split til 2 bytes

  temp_beregn_f = ( Modul_KG * 100 );                           // Hent Total Pilleforbrug i KG * 100
  packetBuffer[18] = (int)((temp_beregn_f >> 24) & 0XFF);         //  Split til 4 bytes
  packetBuffer[19] = (int)((temp_beregn_f >> 16) & 0XFF);         //
  packetBuffer[20] = (int)((temp_beregn_f >> 8) & 0XFF);          //
  packetBuffer[21] = (int)((temp_beregn_f & 0XFF));               //

  packetBuffer[22] = Fyr_Status;                                // 0 = Brænderen køre ikke, 1  = Brænderen kører
  packetBuffer[23] = VarmeLegme;                                // 0 = Varmelegme Off, 1 = Varmelegme On
  packetBuffer[24] = Turbulatorerne;                            // 0 = Turbulatorerne Renser ikke, 1 = Turbulatorerne Renser
  packetBuffer[25] = Pumpe_Central;                             // Central Varme Pumpen 0 = Off , 1 = On
  packetBuffer[26] = Pumpe_VVB;                                 // VarmtVandsBeholderen Pumpen 0 = Off, 1 = On
  packetBuffer[27] = Rist_Pos;                                  // 0 = Rist hjemme, 1 = Køre
  packetBuffer[28] = Snegl;                                     // 0 = Snegl Stoppet, 1 = Snegl køre
  packetBuffer[29] = LUX;                                       // Lux Sensor 0-255
  packetBuffer[30] = Fan_Speed;                                 // Fan Speed 0-100

  temp_beregn = ( Lambda_o2 );                            // Hent Ilt i Røggassen * 100
  packetBuffer[31] = (int)((temp_beregn >> 8) & 0XFF);          // Split til 2 bytes
  packetBuffer[32] = (int)((temp_beregn & 0XFF));               //

  packetBuffer[33] = (int)((Temp_Kedel >> 8) & 0XFF);           // Hent Kedel Temp - konverteres via Temp Tabel i SW/PHP
  packetBuffer[34] = (int)((Temp_Kedel & 0XFF));                // Split til 2 bytes

  packetBuffer[35] = (int)((Temp_Central >> 8) & 0XFF);         // Hent CentralVarme Temp - konverteres via Temp Tabel i SW/PHP
  packetBuffer[36] = (int)((Temp_Central & 0XFF));              // Split til 2 bytes

  packetBuffer[37] = (int)((Temp_VVB >> 8) & 0XFF);             // Hent VVB Temp - konverteres via Temp Tabel i SW/PHP
  packetBuffer[38] = (int)((Temp_VVB & 0XFF));                  // Split til 2 bytes

  packetBuffer[39] = (int)((Temp_Ude >> 8) & 0XFF);             // Hent Ude Temp - konverteres via Temp Tabel i SW/PHP
  packetBuffer[40] = (int)((Temp_Ude & 0XFF));                  // Split til 2 bytes

/*

packetBuffer[41] = ;
packetBuffer[42] = ;
packetBuffer[43] = ;
packetBuffer[44] = ;
packetBuffer[45] = ;
packetBuffer[46] = ;
packetBuffer[47] = ;
packetBuffer[48] = ;
packetBuffer[49] = ;
packetBuffer[50] = ;
packetBuffer[51] = ;
packetBuffer[52] = ;
packetBuffer[53] = ;
packetBuffer[54] = ;
packetBuffer[55] = ;
packetBuffer[56] = ;
packetBuffer[57] = ;
packetBuffer[58] = ;
packetBuffer[59] = ;
packetBuffer[60] = ;
packetBuffer[61] = ;
packetBuffer[62] = ;
packetBuffer[63] = ;
packetBuffer[64] = ;
packetBuffer[65] = ;
packetBuffer[66] = ;
packetBuffer[67] = ;
packetBuffer[68] = ;
packetBuffer[69] = ;

   for (int i=41; i <= 69; i++)
    {
      packetBuffer[i] = 255;
    } 
*/
}

