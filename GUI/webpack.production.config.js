const path = require('path')

module.exports = {
    devtool: 'eval-source-map',
    entry:  {
        main: "./src/app/app.js",
        login: "./src/login_app/LoginApp.js",
    },
    output: {
        path: "./production/",
        filename: "[name].js",
    },
    module: {
        loaders: [
            {
                test: /\.jsx?$/,
                exclude: /node_modules/,
                loader: 'babel',
            },
        ],
    },
}
