
/*
 * ÄLÄ VÄLITÄ TÄSTÄ ALUSTA.
 * NÄILLÄ RIVEILLÄ VAIN VALMISTELLAAN
 * PINNIT KÄYTTÖÄ VARTEN JA MÄÄRITELLÄÄN MORSE-KOODIN
 * PISTE, VIIVA JA TAUOT.
 */

const int NAPPI = 2;
const int LED = LED_BUILTIN;


// Morse-merkkien ja taukojen pituudet
const int PISTEEN_KESTO = 300;
const int VIIVAN_KESTO = 3 * PISTEEN_KESTO;
const int MERKKI_TAUON_KESTO = PISTEEN_KESTO;
const int KIRJAIN_TAUON_KESTO = 3 * PISTEEN_KESTO;
const int SANA_TAUON_KESTO = 7 * PISTEEN_KESTO;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(NAPPI, INPUT_PULLUP);
}

void sytyta_ledi() {
  digitalWrite(LED, HIGH);
}

void sammuta_ledi() {
  digitalWrite(LED, LOW);
}

void odota(int aika) {
  delay(aika);
}

/**
 * MORSE HOMMAT
 */

void piste() {
  // Laita ledi päälle
  sytyta_ledi();
  
  // Anna sen palaa pisteen ajan
  odota(PISTEEN_KESTO);
  
  // Sammuta ledi
  sammuta_ledi();

  // Merkkien välinen tauko
  odota(MERKKI_TAUON_KESTO);
}

void viiva() {
  // Laita ledi päälle
  sytyta_ledi();
  
  // Anna sen palaa pisteen ajan
  odota(VIIVAN_KESTO);
  
  // Sammuta ledi
  sammuta_ledi();

  // Merkkien välinen tauko
  odota(MERKKI_TAUON_KESTO);
}

bool onko_nappia_painettu() {
  Serial.println(digitalRead(NAPPI));
  return digitalRead(NAPPI) == LOW; // Sisäinen pull-up vastus käytössä
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * TEE OMAT MUUTOKSET TÄSTÄ ALASPÄIN. KÄYTÄ APUNA      *
 * VALMISTA OHJELMAA, JOKA VILAUTTAA PISTEEN JA VIIVAN *
 * KUN NAPPIA PAINAA.                                  *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void loop() {
  // Tarkista onko nappi painettu
  if (onko_nappia_painettu()) {
    
    // Nappia on painettu: vilkutetaan teksti TAKO
    
    // T: -
    viiva();
    odota(KIRJAIN_TAUON_KESTO);

    // A: .-
    piste();
    viiva();
    odota(KIRJAIN_TAUON_KESTO);

    // K: -.-
    viiva();
    piste();
    viiva();
    odota(KIRJAIN_TAUON_KESTO);

    // O: ---
    viiva();
    viiva();
    viiva();
    // Sanan lopussa ei tarvitse odottaa kirjainten välistä taukoa
    
  } // if-napin painallus tarkistuksen loppu

  // Odota toistojen välissä sanojen välinen tauko
  odota(SANA_TAUON_KESTO);
}
