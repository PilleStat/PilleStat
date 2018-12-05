void hent_sensor_data ()
  {
  // START - LÆS RØG, FREMLØB og RETURLØB Temperatur
  // Det tager ca 12 millisekunder at læse alle 4
      if (sample_count < sample_num)                            // Loop antal gange
      {
        Modul_FremL_Sum += frem_sensor.getThmc();               // Hent Temp for Fremløb og læg til summa
        Modul_ReturL_Sum += tilbage_sensor.getThmc();           // Hent Temp for Returløb og læg til summa
        Modul_Gas_Sum += rog_sensor.getThmc();                  // Hent Temp for RøgGas og læg til summa
        Modul_FB_Sum += rog_sensor.getRoomTmp();                // Hent Temp for Sensor boks og læg til summa
        Modul_SB_Sum += hent_rtc_temp();                        // Hent Temp for Styrings boks og læg til summa
        sample_count++;                                         // Tal op
      }
      else                                                      // Loop færdig, beregn gennemsnittet
      {
        Modul_FremL = (Modul_FremL_Sum / sample_num);           // Gennemsnittet for Fremløb - Offsettet
        Modul_ReturL = (Modul_ReturL_Sum / sample_num);         // Gennemsnittet for Returløb - Offsettet
        Modul_Gas = (Modul_Gas_Sum / sample_num);               // Gennemsnittet for RøgGas - Offsettet
        Modul_FB = Modul_FB_Sum / sample_num;                   // Gennemsnittet for Sensor Boks
        Modul_SB = Modul_SB_Sum / sample_num;                   // Gennemsnittet for Styrings Boks
        Modul_FremL_Sum = 0.0;                                  // Nulstil Summa for Fremløb
        Modul_ReturL_Sum = 0.0;                                 // Nulstil Summa for Returløb
        Modul_Gas_Sum = 0.0;                                    // Nulstil Summa for RøgGas
        Modul_FB_Sum = 0.0;                                     // Nulstil Summa for Sensor Boks
        Modul_SB_Sum = 0.0;                                     // Nulstil Summa for Styrings Boks
        sample_count = 0;                                       // Nulstil Summa for Loop
      }
  // STOP - LÆS RØG, FREMLØB og RETURLØB Temperatur
  }
