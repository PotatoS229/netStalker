// webpack.config.js
const path = require('path');

/** @type {import('webpack').Configuration} */
module.exports = {
  // Точка входа приложения (должен быть JS файл)
  entry: './src/server/src/server.js',
  
  // Настройки вывода собранных файлов
  output: {
    path: path.resolve(__dirname, 'dist'),
    filename: 'bundle.js'
  },
  
  // Режим сборки
  mode: 'development',
  
  module: {
    rules: [
      {
        test: /\.scss$/,
        use: [
          'style-loader',  // Встраивает стили в DOM
          'css-loader',    // Преобразует CSS в CommonJS
          'sass-loader'    // Компилирует Sass в CSS
        ]
      },
      {
        test: /\.html$/,
        use: ['html-loader'] // Обрабатывает HTML файлы
      }
    ]
  }
};