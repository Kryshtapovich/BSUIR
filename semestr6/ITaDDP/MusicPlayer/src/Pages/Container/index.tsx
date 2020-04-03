import "./index.scss";

import Navbar from "@Components/Navbar";
import Player from "@Components/Player";

function PageContainer({ children }: React.PropsWithChildren<{}>) {
  return (
    <div className="page-container" id="page-container">
      <Navbar />
      {children}
      <Player />
    </div>
  );
}

export default PageContainer;
