import "./index.scss";

import TrackCard from "@Components/Cards/Track";
import PageContainer from "@Pages/Container";

const arr = Array(40).fill(1);

function TracksPage() {
  return (
    <PageContainer>
      <div className="tracks">
        {arr.map((s, i) => (
          <TrackCard key={i} />
        ))}
      </div>
    </PageContainer>
  );
}

export default TracksPage;
