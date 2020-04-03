import { useEffect, useState } from "react";
import { Dimensions } from "react-native";

function usePortrait() {
  const [isPortrait, setIsPortrait] = useState(
    Dimensions.get("screen").width < Dimensions.get("screen").height
  );

  const handler = (width: number, height: number) => {
    if (width < height) {
      setIsPortrait(true);
    } else {
      setIsPortrait(false);
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

export default usePortrait;
