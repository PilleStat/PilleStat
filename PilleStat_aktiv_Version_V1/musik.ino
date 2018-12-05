void musik_beep_q ()
  {
    tone(TonePin, 1700, 10);
    delay(11);
    noTone(TonePin);
  }
  
void musik_beep_frem ()
  {
    tone(TonePin, 1700, 300);
    delay(400);
    noTone(TonePin);
  }

void musik_beep_tilbage ()
  {
    tone(TonePin, 1600, 300);
    delay(400);
    noTone(TonePin);
  }

void musik_beep_enter ()
  {
    tone(TonePin, 2500, 400);
    delay(500);
    noTone(TonePin);
  }

void musik_beep_alarm ()
  {
    for (int thisNote = 0; thisNote < 3; thisNote++)
      {
        tone(TonePin, 3500, 300);
        delay(400);
      }
    delay(300);   
    noTone(TonePin);
  }

void musik_alt_ok ()
  {
    int melody[] = {262, 196, 196, 220, 196, 0, 247, 262};
    int noteDurations[] = { 4, 8, 8, 4, 4, 4, 4, 4 };
    for (int thisNote = 0; thisNote < 8; thisNote++)
      {
        int noteDuration = 1000/noteDurations[thisNote];
        tone(TonePin, melody[thisNote],noteDuration);
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        noTone(TonePin);
      }
    delay(300);   
    noTone(TonePin);
  }

