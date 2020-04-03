import * as SQLite from "expo-sqlite";

import NoteModel from "../Models/Note";

class NoteService {
  constructor() {
    const db = SQLite.openDatabase("Notes");
    db.transaction((t) =>
      t.executeSql(
        "create table if not exists Note (" +
          "id nvarchar(40) primary key not null," +
          "title nvarchar(30)," +
          "description nvarchar(300)," +
          "tags nvarchar(200)" +
          ")"
      )
    );
  }

  getNotes() {
    const db = SQLite.openDatabase("Notes");
    return new Promise<NoteModel[]>((resolve) =>
      db.transaction((t) =>
        t.executeSql("select * from Note", [], (_, { rows }) => {
          resolve((rows as any)._array as NoteModel[]);
          return rows;
        })
      )
    );
  }

  addNote(note: NoteModel) {
    const db = SQLite.openDatabase("Notes");
    return new Promise<void>(() =>
      db.transaction((t) =>
        t.executeSql("insert into Note (id, title, description, tags) values (?, ?, ?, ?)", [
          note.id,
          note.title,
          note.description,
          note.tags
        ])
      )
    );
  }

  editNote(note: NoteModel) {
    const db = SQLite.openDatabase("Notes");
    return new Promise<void>(() =>
      db.transaction((t) =>
        t.executeSql("update Note set title=?, description=?, tags=? where id=?", [
          note.title,
          note.description,
          note.tags,
          note.id
        ])
      )
    );
  }

  deleteNote(id: string) {
    const db = SQLite.openDatabase("Notes");
    return new Promise<void>(() =>
      db.transaction((t) => t.executeSql("delete from Note where id=?", [id]))
    );
  }
}

const noteService = new NoteService();

export default noteService;
