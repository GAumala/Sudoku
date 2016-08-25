const path = require('path')
const express = require('express')
const bodyParser = require('body-parser');
const spawn = require('child_process').spawn;

const app = express()
const port = process.env.PORT || 8192

app.use(bodyParser.json()); // for parsing application/json

app.post('/solve', function (req, res){
    const array = req.body
    const algoritmo = spawn("../main", ["-i"].concat(array));

    algoritmo.stdout.on('data', (data) => {
        res.send(data.toString('utf-8'));
    })
})

app.listen(port, function () {
    console.log('Application listening on  port ' + port);
});
