// Pilleforbrug - START
  float hent_pille_kg ()                                      // Hent Total Pilleforbrug fra SD kortet
    {
      float htk;                                              // Deklarere værdien som skal returneres
      digitalWrite(W5200_CS, HIGH);                           // Slukker for Netværkforbindelsen for at starte SD kortet
        File myFile = SD.open("puls.txt", FILE_READ);         // Åbne filen hvor Total pilleforbrug er gem i
          String settings = myFile.readStringUntil('\n');     // Læs tallet indtil enden af linien
        myFile.close();                                       // Lukker filen igen
        htk = (settings.toFloat());                           // Laver String teksten om til Float værdi
      digitalWrite(SDCARD_CS, HIGH);                          // Slukker for SD kortet for at starte netværket igen
      return htk;                                             // Returnere værdien for kaldet
    }
  
  float gem_pille_kg (float val1)                             // Gemmer Total Pilleforbrug på SD kortet
    {
      digitalWrite(W5200_CS, HIGH);                           // Slukker for Netværkforbindelsen for at starte SD kortet
        SD.remove("puls.txt");                                // Sletter filen da der kun skal være en værdi i den.
        File myFile = SD.open("puls.txt", FILE_WRITE);        // Opretter filen igen
          myFile.println(val1);                               // Skriver værdien i filen
        myFile.close();                                       // Lukker filen igen
      digitalWrite(SDCARD_CS, HIGH);                          // Slukker for SD kortet for at starte netværket igen
    }
// Pilleforbrug - SLUT

// Pilleforbrug Faktor - START
  float hent_pf ()                                            // Hent Pille Kg Faktor fra SD kortet
    {
      float htk;                                              // Deklarere værdien som skal returneres
      digitalWrite(W5200_CS, HIGH);                           // Slukker for Netværkforbindelsen for at starte SD kortet
        File myFile = SD.open("pf.txt", FILE_READ);           // Åbne filen hvor Pille Kg Faktoren er gem i
          String settings = myFile.readStringUntil('\n');     // Læs tallet indtil enden af linien
        myFile.close();                                       // Lukker filen igen
        htk = (settings.toFloat());                           // Laver String teksten om til Float værdi
      digitalWrite(SDCARD_CS, HIGH);                          // Slukker for SD kortet for at starte netværket igen
      return htk;                                             // Returnere værdien for kaldet
    }

  float gem_pf (float val1)                                   // Gemmer Pille Kg Faktoren på SD kortet
    {
      digitalWrite(W5200_CS, HIGH);                           // Slukker for Netværkforbindelsen for at starte SD kortet
        SD.remove("pf.txt");                                  // Sletter filen da der kun skal være en værdi i den.
        File myFile = SD.open("pf.txt", FILE_WRITE);          // Opretter filen igen
          myFile.println(val1);                               // Skriver værdien i filen
        myFile.close();                                       // Lukker filen igen
      digitalWrite(SDCARD_CS, HIGH);                          // Slukker for SD kortet for at starte netværket igen
    }
// Pilleforbrug Faktor - SLUT  

// Netværksopsætning - START
  void gem_netopset ()
  {
    digitalWrite(W5200_CS, HIGH);                           // Slukker for Netværkforbindelsen for at starte SD kortet
    String MinMAC =     String(mac[0], HEX) + ":" + 
                        String(mac[1], HEX) + ":" + 
                        String(mac[2], HEX) + ":" + 
                        String(mac[3], HEX) + ":" + 
                        String(mac[4], HEX) + ":" + 
                        String(mac[5], HEX);
    String MinIP =      String(ip[0]) + "." + 
                        String(ip[1]) + "." + 
                        String(ip[2]) + "." + 
                        String(ip[3]);
    String MinSubNet =  String(subnet[0]) + "." + 
                        String(subnet[1]) + "." + 
                        String(subnet[2]) + "." + 
                        String(subnet[3]);
    String MinGateWay = String(gateway[0]) + "." + 
                        String(gateway[1]) + "." + 
                        String(gateway[2]) + "." + 
                        String(gateway[3]);
    String MinDNS =     String(dnsserver[0]) + "." + 
                        String(dnsserver[1]) + "." + 
                        String(dnsserver[2]) + "." + 
                        String(dnsserver[3]);
    SD.remove("netopset.txt");                                  // Sletter filen da der kun skal være en værdi i den.
    File myFile = SD.open("netopset.txt", FILE_WRITE);          // Opretter filen igen
      myFile.println(MinMAC);                               // Skriver værdien i filen
      myFile.println(MinIP);                               // Skriver værdien i filen
      myFile.println(MinSubNet);                               // Skriver værdien i filen
      myFile.println(MinGateWay);                               // Skriver værdien i filen
      myFile.println(MinDNS);                               // Skriver værdien i filen
      myFile.println("");                               // Skriver værdien i filen
    myFile.close();                                       // Lukker filen igen
    digitalWrite(SDCARD_CS, HIGH);                          // Slukker for SD kortet for at starte netværket igen
  }

  void hent_netopset ()
    {
      digitalWrite(W5200_CS, HIGH);                           // Slukker for Netværkforbindelsen for at starte SD kortet
      char netBuffer[32];
      int chPos = 0;
      int lineNo = 0;
      File myFile = SD.open("netopset.txt",FILE_READ);
      while(myFile.available())
        {
          char ch = myFile.read();
          if(ch == '\n')
            {
              chPos = 0;
              switch(lineNo)
                {
                  case 0:
                    getMAC(netBuffer,mac);
                  break;
      
                  case 1:
                    getIP(netBuffer,ip);
                  break;
      
                  case 2:
                    getIP(netBuffer,subnet);
                  break;
      
                  case 3:
                    getIP(netBuffer,gateway);
                  break;
      
                  case 4:
                    getIP(netBuffer,dnsserver);
                  break;
                }
              lineNo++;
            }
            else if(ch == '\r')
              {
                // do nothing
              }
            else if(chPos < 31)
              {
                netBuffer[chPos] = ch;
                chPos++;
                netBuffer[chPos] = 0;
              }
        }
      myFile.close();
      digitalWrite(SDCARD_CS, HIGH);                          // Slukker for SD kortet for at starte netværket igen

//      Serial.print("IP :");
//      Ethernet.begin(mac,ip,dnsserver,gateway,subnet);
      Ethernet.begin(mac,ip);
//      Serial.println(Ethernet.localIP());
    }

// Funktion til at hente MAC fra String TXT - START
  byte getMAC(char* macBuf, byte* thisMAC)
    {
      byte thisLen = strlen(macBuf);
      byte thisOctet = 1;
      thisMAC[0] = strtol(&macBuf[0],NULL,16);
      for(int x = 0; x<thisLen; x++)
        {
          if(macBuf[x] == ':')
            {
              thisMAC[thisOctet] = strtol(&macBuf[x+1],NULL,16);
              thisOctet++;
            }
        }
  
      if(thisOctet == 6) return(1);
      else return(0);
    }
// Funktion til at hente MAC fra String TXT - SLUT

// Funktion til at hente IP, SubNet, GateWay og DNS fra String TXT - START
  byte getIP(char* ipBuf, byte* thisIP)
    {
      byte thisLen = strlen(ipBuf);
      byte thisOctet = 1;
      thisIP[0] = atoi(&ipBuf[0]);
      for(int x = 0; x<thisLen; x++)
        {
          if(ipBuf[x] == '.')
            {
              thisIP[thisOctet] = atoi(&ipBuf[x+1]);
              thisOctet++;
            }
        }
      if(thisOctet == 4) return(1);
      else return(0);
    }
// Funktion til at hente IP, SubNet, GateWay og DNS fra String TXT - SLUT

// Netværksopsætning - SLUT
