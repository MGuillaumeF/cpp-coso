module.exports = {
    root: true,
    env: {
      node: true
    },
    parser: "@typescript-eslint/parser",
    parserOptions: {
      ecmaVersion: 2020,
      sourceType: "module"
    },
    extends: [
      "prettier",
      "eslint:recommended",
      "plugin:@typescript-eslint/recommended",
      "plugin:promise/recommended",
      "plugin:typescript-sort-keys/recommended"
    ],
    plugins: [
      "@typescript-eslint",
      "typescript-sort-keys",
      "prettier",
      "promise"
    ],
  };