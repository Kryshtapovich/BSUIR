import NoteModel from "./Note";

export type NavigationParams = {
  Home: undefined;
  Form: { note?: NoteModel; submitCallback: (note: NoteModel) => void };
};
