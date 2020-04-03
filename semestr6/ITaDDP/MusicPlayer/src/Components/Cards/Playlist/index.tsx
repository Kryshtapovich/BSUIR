import "./index.scss";

import PlaylistModal from "@Components/Modals/Playlist";
import { useState } from "react";

function PlaylistCard() {
  const [isModalShown, setIsModalShown] = useState(false);

  const toggleModal = () => setIsModalShown(!isModalShown);

  return (
    <>
      <div className="playlist-card" onClick={toggleModal}>
        <div className="playlist-card__image" />
        <span className="playlist-card__name">Name</span>
      </div>
      {isModalShown && <PlaylistModal onClose={toggleModal} />}
    </>
  );
}

export default PlaylistCard;
