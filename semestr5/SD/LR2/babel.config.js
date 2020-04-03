module.exports = function (api) {
  api.cache(true);
  return {
    presets: ["babel-preset-expo", "module:metro-react-native-babel-preset"],
    plugins: [
      [
        "module-resolver",
        {
          root: ["./src"],
          extensions: [
            ".ios.ts",
            ".android.ts",
            ".ts",
            ".ios.tsx",
            ".android.tsx",
            ".tsx",
            ".jsx",
            ".js",
            ".json"
          ],
          alias: {
            "@Components": "./src/Components",
            "@Hooks": "./src/Hooks",
            "@Utils": "./src/Utils",
            "@Models": "./src/Models",
            "@Services": "./src/Services",
            "@Stores": "./src/Stores",
            "@Assets": "./src/Assets"
          }
        }
      ]
    ]
  };
};
