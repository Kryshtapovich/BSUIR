import { Audio } from "expo-av";

class AudioService {
  readySound = new Audio.Sound();

  async play() {
    await this.readySound.playFromPositionAsync(0);
  }

  async configure() {
    await Audio.setAudioModeAsync({
      playsInSilentModeIOS: true,
      allowsRecordingIOS: false,
      staysActiveInBackground: true,
      interruptionModeIOS: Audio.INTERRUPTION_MODE_IOS_DO_NOT_MIX,
      interruptionModeAndroid: Audio.INTERRUPTION_MODE_ANDROID_DO_NOT_MIX,
      playThroughEarpieceAndroid: true,
      shouldDuckAndroid: true
    });
    await this.readySound.loadAsync(require("@Assets/start.mp3"));
  }

  async dispose() {
    await this.readySound.unloadAsync();
  }
}

const audioService = new AudioService();

export default audioService;
