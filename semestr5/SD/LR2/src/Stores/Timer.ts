import TimerModel from "@Models/Timer";
import timerService from "@Services/Timer";
import { makeAutoObservable, runInAction } from "mobx";
import uuid from "react-native-uuid";

export class TimerStore {
  timers: TimerModel[] = [];

  constructor() {
    makeAutoObservable(this);
  }

  dispose() {
    this.timers = [];
  }

  async init() {
    const timers = await timerService.getTimers();
    runInAction(() => {
      this.timers = timers;
    });
  }

  async addTimer(timer: TimerModel) {
    timer.id = uuid.v4().toString();
    this.timers.push(timer);
    await timerService.addTimer(timer);
  }

  async editTimer(timer: TimerModel) {
    this.timers = this.timers.map((x) => (x.id === timer.id ? timer : x));
    await timerService.editTimer(timer);
  }

  async deleteTimer(timer: TimerModel) {
    this.timers = this.timers.filter((x) => x.id !== timer.id);
    await timerService.deleteTimer(timer.id);
  }
}
