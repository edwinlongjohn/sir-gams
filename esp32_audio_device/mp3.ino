void mp3() {
  unsigned long duration = 0;
  if (song_number >= 1 && song_number <= 70 && song_counter != song_number) {
    Serial.print("Playing Track #");
    Serial.println(song_number);
    player.play(song_number);
    delay(500);
    for (auto &command : commands) {
      if (song_number == command.songNo) {
        //if song_number is done playing then play the next song
        delay(command.songNoDuration);
        player.play(command.songPartner);
        delay(500);
        delay(command.songPartnerDuration);
        //when you're done playing turn on or turn off the relay;
        digitalWrite(relay_pin, command.relayActive ? HIGH : LOW);
        Serial.print(command.relayActive ? "relay activated" : "Relay not activated");
        //Serial.println(triggerOnNumbers[i]);
        command.relayActive ? relayActivated = true : relayActivated = false;
        break;
      }
    }
    song_counter = song_number;
    Serial.println("(Audio playing for max 10 seconds...)");
  } else if (song_counter == song_number) {
    Serial.println("do nothing");
  } else {
    Serial.println("Invalid input! Enter 1-70.");
  }
  if (!relayActivated) {
    Serial.println("i got here");
    digitalWrite(relay_pin, LOW);
  }
}