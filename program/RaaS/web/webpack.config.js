const path = require('path');
const HtmlWebpackPlugin = require('html-webpack-plugin');
const MiniCssExtractPlugin = require('mini-css-extract-plugin');

const isDevelopment = process.env.NODE_ENV !== 'production';

module.exports = {
  // Режим сборки
  mode: isDevelopment ? 'development' : 'production',
  
  // Карта исходного кода для отладки
  devtool: isDevelopment ? 'eval-source-map' : 'source-map',
  
  // Точка входа
  entry: {
    app: './web/src/app.js',
  },
  
  // Выходные файлы
  output: {
    filename: isDevelopment ? '[name].js' : '[name].[contenthash].js',
    path: path.resolve(__dirname, 'dist'),
    clean: true, // Очищать папку dist перед каждой сборкой
    publicPath: '/',
  },
  
  // Дополнительные расширения для импортов
  resolve: {
    extensions: ['.js'],
    alias: {
      '@': path.resolve(__dirname, 'web/src'),
    },
  },
  
  // Модули и правила обработки
  module: {
    rules: [
      // JavaScript файлы
      {
        test: /\.js$/,
        exclude: /node_modules/,
        use: {
          loader: 'babel-loader',
          options: {
            presets: ['@babel/preset-env'],
          },
        },
      },
      
      // CSS файлы
      {
        test: /\.css$/,
        use: [
          isDevelopment ? 'style-loader' : MiniCssExtractPlugin.loader,
          'css-loader',
          {
            loader: 'postcss-loader',
            options: {
              postcssOptions: {
                plugins: [
                  require('autoprefixer'),
                  require('cssnano')({
                    preset: 'default',
                  }),
                ],
              },
            },
          },
        ],
      },
      
      // Изображения
      {
        test: /\.(png|svg|jpg|jpeg|gif)$/i,
        type: 'asset/resource',
        generator: {
          filename: 'assets/images/[name][ext]',
        },
      },
      
      // Шрифты
      {
        test: /\.(woff|woff2|eot|ttf|otf)$/i,
        type: 'asset/resource',
        generator: {
          filename: 'assets/fonts/[name][ext]',
        },
      },
      
      // JSON файлы
      {
        test: /\.json$/,
        type: 'json',
      },
    ],
  },
  
  // Плагины
  plugins: [
    // HTML шаблон
    new HtmlWebpackPlugin({
      template: './web/src/index.html',
      filename: 'index.html',
      inject: 'body',
      favicon: false,
      minify: !isDevelopment && {
        removeComments: true,
        collapseWhitespace: true,
        removeRedundantAttributes: true,
        useShortDoctype: true,
        removeEmptyAttributes: true,
        removeStyleLinkTypeAttributes: true,
        keepClosingSlash: true,
        minifyJS: true,
        minifyCSS: true,
        minifyURLs: true,
      },
    }),
    
    // Извлечение CSS в отдельные файлы
    ...(isDevelopment ? [] : [
      new MiniCssExtractPlugin({
        filename: '[name].[contenthash].css',
        chunkFilename: '[id].[contenthash].css',
      }),
    ]),
  ],
  
  // Конфигурация DevServer
  devServer: {
    static: {
      directory: path.join(__dirname, 'dist'),
    },
    hot: true,
    open: true,
    port: 3000,
    historyApiFallback: true,
    proxy: {
      // Проксирование запросов к API netStalker
      '/api': {
        target: 'http://localhost:8080',
        changeOrigin: true,
        secure: false,
      },
      '/ws': {
        target: 'ws://localhost:8080',
        ws: true,
      },
    },
    client: {
      overlay: {
        errors: true,
        warnings: false,
      },
      progress: true,
    },
    compress: true,
  },
  
  // Оптимизации для production
  optimization: {
    minimize: !isDevelopment,
    minimizer: [],
    splitChunks: {
      chunks: 'all',
      cacheGroups: {
        vendors: {
          test: /[\\/]node_modules[\\/]/,
          name: 'vendors',
          chunks: 'all',
        },
        styles: {
          test: /\.css$/,
          name: 'styles',
          chunks: 'all',
          enforce: true,
        },
      },
    },
    runtimeChunk: 'single',
  },
  
  // Настройки производительности
  performance: {
    hints: isDevelopment ? false : 'warning',
    maxAssetSize: 512000,
    maxEntrypointSize: 512000,
  },
};