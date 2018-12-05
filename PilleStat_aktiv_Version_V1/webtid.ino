void webUnixTime ()
  {
    unsigned long time = 0;
    int dst_sommertid = 0;
    if (client.connect("google.dk", 80))
      {
        client.print(F("GET / HTTP/1.1 \r\n\r\n"));
        char buf[5];
        client.setTimeout(3000);
        if (client.find((char *)"\r\nDate: ") && client.readBytes(buf, 5) == 5)
          {
            unsigned day = client.parseInt();
            client.readBytes(buf, 1);
            client.readBytes(buf, 3);
            int web_tid_aar = client.parseInt();
            byte web_tid_timer = client.parseInt();
            byte web_tid_min = client.parseInt();
            byte web_tid_sek = client.parseInt();
            int Dage_sidste_mdr;
            int dst_aar = 2015;
            int dst_mdr = 1;
            int dst_dag = 0;
            switch (buf[0])
              {
                case 'F':
                  Dage_sidste_mdr =  31;
                  dst_mdr = 2;
                  break;
                case 'S':
                  Dage_sidste_mdr = 243;
                  dst_mdr = 9;
                  break;
                case 'O':
                  Dage_sidste_mdr = 273;
                  dst_mdr = 10;
                  break;
                case 'N':
                  Dage_sidste_mdr = 304;
                  dst_mdr = 11;
                  break;
                case 'D':
                  Dage_sidste_mdr = 334;
                  dst_mdr = 12;
                  break;
                default:
                  if (buf[0] == 'J' && buf[1] == 'a')
                  {
                    Dage_sidste_mdr = 0;
                    dst_mdr = 1;
                  }
                  else if (buf[0] == 'A' && buf[1] == 'p')
                  {
                    Dage_sidste_mdr = 90;
                    dst_mdr = 4;
                  }
                  else switch (buf[2])
                    {
                      case 'r':
                        Dage_sidste_mdr =  59;
                        dst_mdr = 3;
                        break;
                      case 'y':
                        Dage_sidste_mdr = 120;
                        dst_mdr = 5;
                        break;
                      case 'n':
                        Dage_sidste_mdr = 151;
                        dst_mdr = 6;
                        break;
                      case 'l':
                        Dage_sidste_mdr = 181;
                        dst_mdr = 7;
                        break;
                      default:
                      case 'g':
                        Dage_sidste_mdr = 212;
                        dst_mdr = 8;
                        break;
                    }
              }
            dst_dag = day;
            dst_aar = web_tid_aar;
            int dst_timer_T = web_tid_timer + Sommer_Vintertid(dst_aar, dst_mdr, dst_dag);
            rtc.setDate(dst_dag, dst_mdr, dst_aar);
            rtc.setTime(dst_timer_T, web_tid_min, web_tid_sek);
            Update_webtid = 1;
          }
      }
    delay(10);
    client.flush();
    client.stop();
  }

int Sommer_Vintertid(int dst_web_tid_aar, int dst_month, int dst_day)
  {
    // Sidste Søndag i Mars
    int beginDSTDate = (31 - (5 * dst_web_tid_aar / 4 + 4) % 7);
    int beginDSTMonth = 3;
    //Sidste Søndag i Oktober
    int endDSTDate = (31 - (5 * dst_web_tid_aar / 4 + 1) % 7);
    int endDSTMonth = 10;
    if (((dst_month > beginDSTMonth) && (dst_month < endDSTMonth)) || ((dst_month == beginDSTMonth) && (dst_day >= beginDSTDate)) || ((dst_month == endDSTMonth) && (dst_day <= endDSTDate)))
      return 2;  // Sommertid
    else
      return 1; // Vintertid
  }

