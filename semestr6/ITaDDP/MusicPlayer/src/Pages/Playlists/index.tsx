import "./index.scss";

import PlaylistCard from "@Components/Cards/Playlist";
import PageContainer from "@Pages/Container";

const arr = Array(40).fill(1);

function PlaylistsPage() {
  return (
    <PageContainer>
      <div className="playlists">
        {arr.map((p, i) => (
          <PlaylistCard key={i} />
        ))}
      </div>
    </PageContainer>
  );
}

export default PlaylistsPage;
