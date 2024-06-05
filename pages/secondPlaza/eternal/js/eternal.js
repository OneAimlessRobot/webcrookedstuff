var audio_noise = document.getElementById('noise');
var audio_song = document.getElementById('song');
// Getting
console.log("Song volume:  "+audio_song.volume);
console.log("Background volume:  "+audio_noise.volume);
// Setting
audio_noise.volume = 0.3;

audio_song.volume = 0.7;

audio_song.seekabkle= true;
console.log("Song volume:  "+audio_song.volume);
console.log("Background volume:  "+audio_noise.volume);
