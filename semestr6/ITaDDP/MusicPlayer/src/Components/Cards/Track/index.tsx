import "./index.scss";

import LyricsModal from "@Components/Modals/Lyrics";
import addIcon from "@Svg/add.svg";
import chevronIcon from "@Svg/chevron-right.svg";
import playIcon from "@Svg/play.svg";
import trashIcon from "@Svg/trash.svg";
import { useState } from "react";

function TrackCard() {
  const [isLyricsShown, setIsLyricsShown] = useState(false);

  const toggleLyrics = () => setIsLyricsShown(!isLyricsShown);

  return (
    <>
      <div className="track-card">
        <div className="track-card__picture" />
        <div className="track-card__right-block">
          <PopupMenu />
          <div className="track-card__info">
            <span className="track-card__name">Track</span>
            <span className="track-card__author">Author</span>
          </div>
          <img src={playIcon} className="track-card__play-button" onClick={toggleLyrics} />
        </div>
      </div>
      {isLyricsShown && <LyricsModal />}
    </>
  );
}

export default TrackCard;

function PopupMenu() {
  const menuItem = (icon: string, text: string) => (
    <div className="popup__menu-item">
      <img src={icon} />
      <span>{text}</span>
    </div>
  );

  return (
    <div className="popup">
      <img src={chevronIcon} className="popup__image" />
      <div className="popup__menu">
        {menuItem(trashIcon, "Delete")}
        {menuItem(addIcon, "Add to playlist")}
      </div>
    </div>
  );
}
