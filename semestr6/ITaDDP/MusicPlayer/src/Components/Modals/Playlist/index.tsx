import "./index.scss";

import closeIcon from "@Svg/close-black.svg";
import trashIcon from "@Svg/trash.svg";
import { useEffect } from "react";
import ReactDOM from "react-dom";

const tracks = Array(40).fill(1);

interface Props {
  onClose: () => void;
}

function PlaylistModal({ onClose }: Props) {
  const container = document.getElementById("page-container");
  const playlistModal = document.createElement("div");

  useEffect(() => {
    container?.appendChild(playlistModal);

    return () => {
      container?.removeChild(playlistModal);
    };
  }, []);

  const modal = (
    <>
      <div className="playlist-modal__background" onClick={onClose} />
      <div className="playlist-modal">
        <div className="playlist-modal__header">
          <div className="playlist-picture" />
          <div className="playlist-info">
            <span>Playlist Name</span>
            <span>Creator</span>
          </div>
          <img src={closeIcon} className="playlist-modal__close-icon" onClick={onClose} />
          <img src={trashIcon} className="playlist-modal__delete-icon" />
        </div>
        <table className="playlist-modal__body">
          <tbody>
            {tracks.map((t, i) => (
              <tr className="playlist-track" key={i}>
                <td>{i + 1}.</td>
                <td>Track Name</td>
                <td>Author</td>
                <td>
                  <img src={trashIcon} className="playlist-modal__delete-icon" />
                </td>
              </tr>
            ))}
          </tbody>
        </table>
      </div>
    </>
  );

  return ReactDOM.createPortal(modal, playlistModal);
}

export default PlaylistModal;
