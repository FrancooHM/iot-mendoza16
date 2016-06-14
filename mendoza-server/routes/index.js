var express = require('express');
module.exports = function(io) {
    //now you can use io.emit() in this file

    var router = express.Router();

    /* GET home page. */
    router.get('/', function(req, res, next) {
        res.sendfile('views/index.html');
    });

    router.post('/hello-websockets', function(req, res) {
      io.emit('arduino');
      console.log('Hola websockets!');
      console.log('HEADERS: ');
      console.log(req.headers);
      console.log('BODY: ');
      console.log(req.body);
      console.log('DATA (sample): ');
      console.log(req.body.sample);
      res.end();
    });

    router.get('/hello', function(req, res, next) {
      console.log('Hola flisol!');
      console.log('HEADERS: ');
      console.log(req.headers);
      console.log('BODY: ');
      console.log(req.body);
      console.log('DATA (sample): ');
      console.log(req.body.sample);
      res.end();
    });
    return router;
}
