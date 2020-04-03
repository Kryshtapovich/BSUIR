import { Route } from "@Components/Navigation";
import FormPage from "@Pages/Form";
import PlaylistsPage from "@Pages/Playlists";
import TracksPage from "@Pages/Tracks";
import * as ROUTES from "@Utils/routing";
import React from "react";
import ReactDOM from "react-dom";

const App = () => (
  <React.StrictMode>
    <Route path={ROUTES.LOGIN} component={() => <FormPage />} />
    <Route path={ROUTES.REGISTRATION} component={() => <FormPage registration />} />
    <Route path={ROUTES.TRACKS} component={TracksPage} />
    <Route path={ROUTES.PLAYLISTS} component={PlaylistsPage} />
  </React.StrictMode>
);

ReactDOM.render(<App />, document.getElementById("root"));
