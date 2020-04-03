import "./index.scss";

import nextIcon from "@Svg/next.svg";
import playIcon from "@Svg/play.svg";
import prevIcon from "@Svg/prev.svg";
import repeatIcon from "@Svg/repeat.svg";
import shuffleIcon from "@Svg/shuffle.svg";

function Player() {
  return (
    <div className="player">
      <div className="player__info">
        <div className="player__song">
          <span className="player__song-name">Track</span>
          <span className="player__song-author">Author</span>
        </div>
        <div className="player__picture" />
      </div>
      <div className="player__buttons">
        <img src={repeatIcon} className="player__button player__button--repeat" />
        <div className="player__buttons--main">
          <img src={prevIcon} className="player__button player__button--prev" />
          <img src={playIcon} className="player__button player__button--play" />
          <img src={nextIcon} className="player__button player__button--next" />
        </div>
        <img src={shuffleIcon} className="player__button player__button--shuffle" />
      </div>
      <div className="player__duration">
        <div className="player__time-progress" />
        <div className="player__timestamps">
          <span className="player__timestamp player__timestamp--passed">0:00</span>
          <span className="player__timestamp player__timestamp--left">-3:20</span>
        </div>
      </div>
    </div>
  );
}

export default Player;
