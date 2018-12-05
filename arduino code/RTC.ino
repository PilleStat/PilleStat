unsigned long hent_rtc ()
  {
      return rtc.getUnixTime(rtc.getTime());        // Henter Dato/tid i Unix Format.
  }

float hent_rtc_temp ()
  {
    return rtc.getTemp();                           // Henter Temp fra StyringsBoksen.
  }


void vis_dato_tid ()
  {
    Serial.print(rtc.getDateStr());                 // Viser Dato og Tid.
    Serial.print(" - ");
    Serial.println(rtc.getTimeStr());
  }
