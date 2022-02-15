var express = require('express');
var app = express();

let port = process.env.PORT;
if (port == null || port == "") {
    port = 8000;
}

app.use(express.static('.'));
app.listen(port, () => { console.info("server listening to port " + port)});