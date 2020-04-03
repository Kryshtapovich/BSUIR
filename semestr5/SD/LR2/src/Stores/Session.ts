import localization from "@Assets/localization";
import TimerModel from "@Models/Timer";
import { makeAutoObservable, reaction } from "mobx";

export class SessionStore {
  rounds: number[] = [];
  total = 0;
  currentRound = 0;
  roundNumber = 1;
  isReseted: boolean = false;

  constructor() {
    makeAutoObservable(this);
    reaction(
      () => this.currentRound,
      () => {
        this.currentRound % 2 === 0 && this.currentRound > 0 && this.roundNumber++;
      }
    );
  }

  init(timer: TimerModel) {
    const { rounds, workMinutes, workSeconds, cooldownMinutes, cooldownSeconds } = timer;
    const work = parseInt(workMinutes) * 60 + parseInt(workSeconds);
    const cooldown = parseInt(cooldownMinutes) * 60 + parseInt(cooldownSeconds);
    this.total = parseInt(rounds);
    this.isReseted = false;

    for (let i = 0; i < this.total; i++) {
      this.rounds.push(work);
      this.rounds.push(cooldown);
    }
  }

  dispose() {
    this.currentRound = 0;
    this.roundNumber = 1;
    this.rounds = [];
  }

  reset() {
    this.isReseted = true;
    this.currentRound = 0;
    this.roundNumber = 1;
    this.total = 0;
  }

  next() {
    this.isReseted = false;
    this.notEnd && this.currentRound++;
  }

  get notEnd() {
    return this.currentRound < this.rounds.length;
  }

  get phase() {
    const round = localization.round + ` ${this.roundNumber}/${this.total}`;
    if (!this.currentRound) return round;
    else return this.currentRound % 2 !== 0 ? round : localization.colldown;
  }

  get time() {
    return this.rounds[this.currentRound];
  }
}
