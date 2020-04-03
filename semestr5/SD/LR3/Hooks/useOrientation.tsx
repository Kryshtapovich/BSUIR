import { useEffect, useState } from "react";
import { Dimensions } from "react-native";

interface Orientation {
  isPortrait: boolean;
  isLandscape: boolean;
}

function useOrientation() {
  const [isPortrait, setIsPortrait] = useState<Orientation>(
    Dimensions.get("screen").width < Dimensions.get("screen").height
      ? { isPortrait: true, isLandscape: false }
      : { isPortrait: false, isLandscape: true }
  );

  const handler = (width: number, height: number) => {
    if (width < height) {
      setIsPortrait({ isPortrait: true, isLandscape: false });
    } else {
      setIsPortrait({ isPortrait: false, isLandscape: true });
    }
  };

  useEffect(() => {
    Dimensions.addEventListener("change", ({ window: { width, height } }) =>
      handler(width, height)
    );

    return Dimensions.removeEventListener("change", ({ window: { width, height } }) =>
      handler(width, height)
    );
  }, []);

  return isPortrait;
}

export default useOrientation;
