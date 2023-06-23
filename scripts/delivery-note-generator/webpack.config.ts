/**
 * Node imports
 */
import { lstatSync, readdirSync } from "fs";
import path from "path";

/**
 * WebPack Plugins import
 */
import HtmlWebpackPlugin from "html-webpack-plugin";

enum WebPackMode {
    DEV = "development",
    PROD = "production"
}
enum LogTheme {
    CLEAN = "CLEAN",
    INITIALISATION = "INITIALISATION"
}
enum LogLevel {
    DEBUG = "debug",
    ERROR = "error",
    INFO = "info",
    WARNING = "warning"
}

/**
 * 
 * @param level 
 * @param theme 
 * @param message 
 */
function trace(level : LogLevel, theme : LogTheme, ...message : any[]) {
  if (message.length !== 0) {
    let call = console.info;
    switch (level) {
        case LogLevel.DEBUG:
            call = console.debug;
            break;
        case LogLevel.INFO:
            call = console.info;
            break;
        case LogLevel.WARNING:
            call = console.warn;
            break;
        case LogLevel.ERROR:
            call = console.error;
            break;
    }

    call(
      `[${level}]`.padEnd(6, " "),
      theme.padEnd(25, " "),
      ...message
    );
  }
}

/**
 * 
 * @returns 
 */
function getAllVersions() : string[] {
    const deliveryContent = readdirSync(path.resolve(__dirname, '../../delivery'));
    const versionDirectories = deliveryContent.filter(name => /\d+\.\d+\.\d+(?:\d+)?/.test(name) && lstatSync(path.resolve(__dirname, '../../delivery', name)).isDirectory()  )
    console.log(versionDirectories);
    return versionDirectories
}

module.exports = () => {
  /**
   * save webpack mode
   * development or production
   */
  const MODE = process.env['NODE_ENV'];

  trace(LogLevel.INFO, LogTheme.INITIALISATION, "Webpack configuration run...");

  const config = {
    mode: MODE,
    entry: "./index.scss",
    cache: false,
    output: {
      path: path.resolve(__dirname, "../../"),
      publicPath: MODE === WebPackMode.DEV ? "/" : process.env['PUBLIC_PATH'] || ".",
      filename:
        MODE === WebPackMode.DEV  ? "[name].bundle.js" : "[name].[prod].bundle.js"
    },
    resolve: {
      // Add `.ts` and `.tsx` as a resolvable extension.
      extensions: [
        ".ts",
        ".tsx",
        ".js",
        ".scss",
        ".svg",
        ".png",
        ".gif",
        ".jpg",
        ".jpeg"
      ]
    },
    module: {
      rules: [
        {
          test: /\.s[ac]ss$/i,
          use: [
            { loader: "style-loader", options: { injectType: "styleTag" } },
            
            "css-loader",
            {
              loader: "@teamsupercell/typings-for-css-modules-loader",
              options: {
                formatter: "prettier"
              }
            },
            // prefix for css rules
            {
              loader: "postcss-loader",
              options: {
                postcssOptions: {
                  plugins: [
                    [
                      "autoprefixer",
                      {
                        // Options
                      }
                    ]
                  ]
                }
              }
            },
            // Compiles Sass to CSS
            "sass-loader"
          ]
        },
        {
          test: /\.(png|jpe?g|gif|svg)$/i,
          use: [
            {
              loader: "url-loader",
              options: {
                limit: 8192
              }
            }
          ]
        }
      ]
    },
    plugins: [
      new HtmlWebpackPlugin({
        inject: "head",
        title: "CPP-COSO",
        template: path.resolve(__dirname, "index.html"),
        favicon: path.resolve(__dirname, "../../resources/icon/cpp-coso/cpp-coso.svg"),
        filename: "index.html",
        versions : [
            ///"0.2.2", "0.2.1", "0.2.0", "0.1.0", 
            ...getAllVersions().reverse()]
      })
    ]
  };
  return config;
};