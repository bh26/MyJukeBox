# MyJukeBox
this Arduino script uses 7 capactitve sensors to trigger a different tune each played on the buzzer, and display some animated lights on a WS2801 addressable LEDs strip.
I built it with borrowings from many kind people that I did not keep track of all from 
 * the beginning.
 * The main step for music is from Mike Putnam Pitches.h, then completed by the beep() function that I found in an instructable from eserra (https://www.instructables.com/id/How-to-easily-play-music-with-buzzer-on-arduino-Th/) that included a first version of StarWars Imperial March.
 * Mission impossible rebuilt from Andre Thomas sketch
 * Frozen from Orlando S. Hoilett ( http://www.instructables.com/member/ohoilett/)
 * Fur elise from Emmanuel at http://repairmypc.net/2017/08/test-post/
 Also Rain of castamere, Happy birthday, StarWars, as well as the Cucaracha.
 * I have 7 capacitive aluminium foils that trigger one note from the buzzer (Do, Re, Mi, Fa Sol, La, Si),
 * then one specific song.
 The beep function includes the commands to move the lights in the WS2801 strip.
 * For each note in the songs 3 LEDs are advancing in the WS2801 strip, and change color.
