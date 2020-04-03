import "./index.scss";

import closeIcon from "@Svg/close-white.svg";
import { useEffect } from "react";
import { createPortal } from "react-dom";

const text = `Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nulla tempus sed mauris sit amet
        dignissim. Praesent lacus lorem, ultricies ut ullamcorper eget, molestie sit amet neque. Sed
        quis dui ut mauris tristique ornare rhoncus non dolor. Ut odio magna, euismod vel neque vel,
        consectetur semper augue. Vestibulum ornare hendrerit dapibus. Suspendisse eu tortor congue,
        ultrices felis vitae, sollicitudin libero. Nunc pharetra justo vel luctus euismod. Praesent
        mattis semper nisl, at laoreet massa semper at. Vivamus vulputate tellus et nisl placerat,
        eget posuere libero varius. Curabitur ligula leo, convallis sit amet sem ac, vehicula
        pulvinar tortor. In ac accumsan magna. Nunc aliquet suscipit ipsum. Sed nec elit id odio
        tincidunt aliquam. Nunc scelerisque vel leo non venenatis. Proin lacus urna, porta sit amet
        nisi pellentesque, condimentum aliquet dolor. Aliquam vitae suscipit orci. Suspendisse
        faucibus, quam vel tempus ultricies, orci ante egestas dui, quis consectetur justo dolor
        quis sem. Vestibulum pretium dignissim velit ac malesuada. Etiam vel tortor vitae ipsum
        venenatis convallis. Aenean vehicula, dolor non tristique congue, leo eros congue odio, ut
        ultricies mi elit et leo. Suspendisse eget hendrerit nisl, gravida consectetur mi. Curabitur
        iaculis ante et ligula maximus, blandit tincidunt lectus mattis. Ut auctor eget turpis id
        ultricies. Sed lobortis auctor ipsum, non lobortis eros elementum vel. Etiam ac placerat
        felis. Sed eget augue ullamcorper, dictum metus sed, aliquet nisi. Maecenas condimentum
        massa sit amet iaculis efficitur. Morbi velit nunc, ornare quis ipsum sed, auctor viverra
        odio. Nam vitae turpis nisi. Mauris mollis velit ac placerat blandit. Aliquam pharetra nisi
        quis lorem dignissim ornare quis vel magna. Phasellus risus lectus, malesuada auctor justo
        nec, ornare molestie ligula. Class aptent taciti sociosqu ad litora torquent per conubia
        nostra, per inceptos himenaeos. Nam ultrices libero tellus, in consectetur magna bibendum
        sed. Quisque nec aliquam augue. Donec elementum nisl sit amet imperdiet laoreet. Nulla
        accumsan, enim quis finibus posuere, dolor nibh vulputate leo, at porttitor nisl leo nec
        lorem. Suspendisse quis commodo nibh, sit amet lobortis neque. Aenean malesuada lobortis
        mauris, non rhoncus massa vestibulum id. Pellentesque ligula ipsum, maximus eu convallis
        volutpat, iaculis sed leo. Morbi sit amet fringilla felis, tristique fermentum lorem. Sed
        vitae scelerisque sapien. Curabitur eget pellentesque orci. Suspendisse elementum felis quis
        felis condimentum, vitae dictum ligula feugiat. Donec pellentesque ante a congue fringilla.
        Pellentesque nec eros molestie odio pharetra varius. Pellentesque a mattis arcu. Nunc ipsum
        orci, imperdiet eu nisl ullamcorper, aliquam egestas felis. Nam pellentesque mi non ex
        sodales accumsan. Nam fermentum commodo mi, a dignissim ante imperdiet sed. Mauris at
        pellentesque odio. Morbi tincidunt est non pharetra aliquet. Integer condimentum tincidunt
        lacus at dignissim. In hendrerit sem non suscipit varius. Maecenas vitae fermentum sapien,
        sollicitudin accumsan neque. Sed rutrum augue neque, eu faucibus dolor euismod ac. Quisque
        rutrum ligula eget dictum commodo. Aliquam nec semper ex, sed fermentum lectus. Integer
        cursus velit nunc, in vulputate tortor ullamcorper id. Ut porta tortor a mollis convallis.
        Ut commodo aliquet arcu ac vulputate. Pellentesque molestie sed tellus at mattis.
        Pellentesque efficitur venenatis neque, ac convallis neque facilisis eu.`;

function LyricsModal() {
  const container = document.getElementById("page-container");
  const lyricsModal = document.createElement("div");

  const close = () => {
    lyricsModal?.setAttribute("class", "lyrics-modal lyrics-modal--hidden");
    setTimeout(() => {
      container?.removeChild(lyricsModal);
    }, 350);
  };

  useEffect(() => {
    lyricsModal.setAttribute("class", "lyrics-modal lyrics-modal--hidden");
    container?.appendChild(lyricsModal);

    setTimeout(() => {
      lyricsModal.setAttribute("class", "lyrics-modal lyrics-modal--shown");
    }, 50);

    return () => {
      container?.removeChild(lyricsModal);
    };
  }, []);

  const modal = (
    <>
      <div className="lyrics-modal__header">
        <div className="lyrics-modal__picture"></div>
        <div className="lyrics-modal__info">
          <span className="lyrics-modal__track">Track</span>
          <span className="lyrics-modal__author">Author</span>
        </div>
        <img src={closeIcon} className="lyrics-modal__close-icon" onClick={close} />
      </div>
      <span className="lyrics-modal__text">{text}</span>
    </>
  );

  return createPortal(modal, lyricsModal);
}

export default LyricsModal;
