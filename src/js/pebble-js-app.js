Pebble.addEventListener("ready", function(e) {
  console.log("PebbleKit JS ready!");

  // Notify the watchapp that it is now safe to send messages
  Pebble.sendAppMessage({ 'AppKeyReady': true });
});
