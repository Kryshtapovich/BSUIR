import NoteModel from "@Models/Note";
import noteService from "@Services/Note";
import { makeAutoObservable, runInAction } from "mobx";
import uuid from "react-native-uuid";

export class NoteStore {
  notes: NoteModel[] = [];

  constructor() {
    makeAutoObservable(this);
  }

  dispose() {
    this.notes = [];
  }

  async init() {
    const notes = await noteService.getNotes();
    runInAction(() => {
      this.notes = notes;
    });
  }

  async addNote(note: NoteModel) {
    note.id = uuid.v4().toString();
    this.notes.push(note);
    await noteService.addNote(note);
  }

  async editNote(note: NoteModel) {
    this.notes = this.notes.map((x) => (x.id === note.id ? { ...x, ...note } : x));
    await noteService.editNote(note);
  }

  async deleteNote(note: NoteModel) {
    this.notes = this.notes.filter((x) => x.id !== note.id);
    await noteService.deleteNote(note.id);
  }

  getNotes(isSorted: boolean) {
    if (isSorted) {
      return this.notes.slice().sort((x, y) => {
        if (x.title > y.title) return 1;
        else if (x.title < y.title) return -1;
        else return 0;
      });
    } else {
      return this.notes;
    }
  }
}
