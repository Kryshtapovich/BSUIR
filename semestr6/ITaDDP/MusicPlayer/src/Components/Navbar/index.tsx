import "./index.scss";

import Logo from "@Components/Logo";
import { NavLink } from "@Components/Navigation";
import * as ROUTES from "@Utils/routing";
import TextInput from "@Components/TextInput";

function Navbar() {
  return (
    <nav className="navbar">
      <Logo />
      <TextInput placeholder="Search" />
      <div className="tabs">
        <NavLink path={ROUTES.TRACKS} content="Tracks" />
        <NavLink path={ROUTES.PLAYLISTS} content="Playlists" />
        <NavLink path={ROUTES.LOGIN} content="Log out" />
      </div>
    </nav>
  );
}

export default Navbar;
