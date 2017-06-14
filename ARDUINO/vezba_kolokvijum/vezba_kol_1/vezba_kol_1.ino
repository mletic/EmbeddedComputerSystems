/*
 * Zadatak:
 * Napisati program koji u zavisnosti od stanja SW1 i SW2 za ulazne vrednosti sa UART-a menja stanje dioda.
 * a) Ukoliko je SW1 upaljen (HIGH) kad se na UART-u prosledi 1, na Arduino-u treba da se pale
 * diode od 33 do 30 (znaci jedna po jedna, 33, 32, 31, 30) dok sve ne budu upaljene. Razmak izmedju paljenja ovih dioda traje 1 sekundu. 
 * Ukoliko se prosledi 0 diode se gase obrnutim redosledom od onog kako su se upalile.
 * b) Ukoliko je SW2 upaljen (HIGH) kad se na UART-u prosledi 1, na Arduino-u treba da se pale diode od 26 do 29 (znaci jedna po jedna, 26, 27, 28, 29) dok sve ne budu upaljene. 
 * Razmak izmedju paljenja ovih dioda traje 1 sekundu. Ukoliko se prosledi 0 diode se gase obrnutim redosledom od onog kako su se upalile.
 * c) Ukoliko su i SW1 i SW2 upaljeni kad se na UART-u prosledi 0 ili 1 na Serial Monitor-u treba da se ispise poruka: “Nije moguce paliti/gasiti diode dok su SW1 i SW2 upaljeni (u HIGH stanju)”
 * d) Implementirati svoju Digital.write i Serial.write metodu
 */

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
