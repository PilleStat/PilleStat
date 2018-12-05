void udp_send ()
{
   
  Udp.beginPacket(fjernserver, RemotePort);                     //   
  Udp.write(packetBuffer, 70);                                  //
  Udp.endPacket();                                              //
}
