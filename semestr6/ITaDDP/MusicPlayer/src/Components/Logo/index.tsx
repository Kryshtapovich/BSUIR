import "./index.scss";

import noteIcon from "@Svg/note.svg";

function Logo() {
  return (
    <div className="logo">
      <img src={noteIcon} className="logo__icon" />
      <span className="logo__title">Muzifio</span>
    </div>
  );
}

export default Logo;
