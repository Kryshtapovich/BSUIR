import TimerModel from "@Models/Timer";
import * as Sqlite from "expo-sqlite";

class TimerService {
  constructor() {
    const db = Sqlite.openDatabase("TabataTimer");
    db.transaction((t) =>
      t.executeSql(
        "create table if not exists Timer (" +
          "id nvarchar(40) primary key not null," +
          "title nvarchar(20)," +
          "workMinutes nvarchar(2)," +
          "workSeconds nvarchar(2)," +
          "cooldownMinutes nvarchar(2)," +
          "cooldownSeconds nvarchar(2)," +
          "rounds nvarchar(2)," +
          "color nvarchar(7)" +
          ")"
      )
    );
  }

  getTimers() {
    const db = Sqlite.openDatabase("TabataTimer");
    return new Promise<TimerModel[]>((resolve) => {
      db.transaction((t) =>
        t.executeSql("select * from Timer", [], (_, { rows }) => {
          resolve((rows as any)._array as TimerModel[]);
          return rows;
        })
      );
    });
  }

  addTimer(timer: TimerModel) {
    const db = Sqlite.openDatabase("TabataTimer");
    return new Promise<void>(() => {
      db.transaction((t) =>
        t.executeSql(
          "insert into Timer (id, title, workMinutes, workSeconds, cooldownMinutes, cooldownSeconds, rounds, color)" +
            "values (?, ?, ?, ?, ?, ?, ?, ?)",
          [
            timer.id,
            timer.title,
            timer.workMinutes,
            timer.workSeconds,
            timer.cooldownMinutes,
            timer.cooldownSeconds,
            timer.rounds,
            timer.color
          ]
        )
      );
    });
  }

  deleteTimer(id: string) {
    const db = Sqlite.openDatabase("TabataTimer");
    return new Promise<void>(() => {
      db.transaction((t) => t.executeSql("delete from Timer where id=?", [id]));
    });
  }

  editTimer(timer: TimerModel) {
    const db = Sqlite.openDatabase("TabataTimer");
    return new Promise<void>(() => {
      db.transaction((t) =>
        t.executeSql(
          "update Timer set title=?, workMinutes=?, workSeconds=?, cooldownMinutes=?, cooldownSeconds=?, rounds=?, color=? where id=?",
          [...Object.values(timer).slice(1), timer.id]
        )
      );
    });
  }
}

const timerService = new TimerService();

export default timerService;
