const path = require('path');
const MiniCssExtractPlugin = require('mini-css-extract-plugin');
const TerserPlugin = require('terser-webpack-plugin');

const _build_mode = "development";
const _get_conf = (index_type) => {
  return {
    context: path.resolve(__dirname),
    entry: './js/index_' + index_type + '.js',
    output: {
      path: path.resolve(__dirname, 'dist'),
      filename: 'bundle_' + index_type + '.js',
      library: 'LIB_' + index_type
    },
    module: {
      rules: [{
        test: /\.glsl?$/,
        use: [
          {
            loader: 'raw-loader',
            options: {
              esModule: false,
            },
          },
        ]
      }, { // extracts CSS into separate files. It creates a CSS file per JS file which contains CSS
        test: /\.(s[ac]ss|css)$/i,
        use: [
          {
            loader: MiniCssExtractPlugin.loader,
            options: {
              publicPath: '../' // path to director where assets folder is located
            }
          },
          'css-loader',
          'sass-loader'
        ]
      }, { //resolves import/require() on fonts into a url and emits the files into the output directory
        test: /\.(woff|woff2|eot|ttf|otf|svg)$/i,
        exclude: /img/,
        use: [{
          loader: 'file-loader',
          options: {
            name: 'fonts/[name].[ext]',
            // outputPath: './style/fonts/'
          }
        }]
      }, {
        test: /\.js?$/,
        use: [{
          loader: 'babel-loader',
        }]
      }]
    },
    resolve: {
      extensions: [".js"]
    },
    plugins: [
      new MiniCssExtractPlugin({
        filename: './style/' + index_type + '.css',
        chunkFilename: '[id].css',
        ignoreOrder: false
      }),
    ],
    mode: _build_mode,
    optimization: {
      minimize: _build_mode === 'production',
      minimizer: [
        new TerserPlugin()
      ],
    }
  };

  
}

module.exports = ['main'].map(type => _get_conf(type));