declare namespace IndexScssNamespace {
  export interface IIndexScss {
    "app-version": string;
    logo: string;
    "os-name": string;
  }
}

declare const IndexScssModule: IndexScssNamespace.IIndexScss & {
  /** WARNING: Only available when `css-loader` is used without `style-loader` or `mini-css-extract-plugin` */
  locals: IndexScssNamespace.IIndexScss;
};

export = IndexScssModule;
