const path = require("path");
const HtmlWebpackPlugin = require("html-webpack-plugin");

const prod = process.env.NODE_ENV === "production";

const extensions = [".ts", ".tsx", ".js", ".json"];

module.exports = {
  mode: prod ? "production" : "development",
  entry: "./src/index.tsx",
  output: { path: path.resolve(__dirname, "dist") },
  resolve: {
    alias: {
      "@Svg": path.resolve(__dirname, "assets/svg"),
      "@Components": path.resolve(__dirname, "src/Components"),
      "@Pages": path.resolve(__dirname, "src/Pages"),
      "@Utils": path.resolve(__dirname, "src/Utils"),
      fonts: path.resolve(__dirname, "assets/fonts"),
      styles: path.resolve(__dirname, "src/styles.scss")
    },
    extensions
  },
  module: {
    rules: [
      {
        test: /\.(ts|tsx)$/,
        exclude: /node_modules/,
        resolve: { extensions },
        use: ["ts-loader"]
      },
      {
        test: /\.s[ac]ss$/,
        use: ["style-loader", "css-loader", "resolve-url-loader", "sass-loader"]
      },
      {
        test: /\.(woff|svg)$/,
        type: "asset/resource"
      }
    ]
  },
  devServer: {
    static: {
      directory: path.join(__dirname, "public")
    },
    historyApiFallback: true
  },
  devtool: prod ? undefined : "source-map",
  plugins: [new HtmlWebpackPlugin({ template: "./public/index.html" })]
};
