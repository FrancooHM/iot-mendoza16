var express = require('express');
module.exports = function(io) {
    //now you can use io.emit() in this file
    var count = 0;
    var router = express.Router();

    /* GET home page. */
    router.get('/', function(req, res, next) {
        res.sendfile('views/index.html');
    });

    router.post('/set-temperature', function(req, res) {
      console.log('Hello websockets!');
      console.log('HEADERS: ');
      console.log(req.headers);
      console.log('BODY: ');
      console.log(req.body);
      console.log('DATA (data): ');
      console.log(req.body.data);

      var data = JSON.parse(req.body.data);

      console.log('DATA (data.t): ');
      console.log(data.t);

      console.log('DATA (data.h): ');
      console.log(data.h);

      io.emit('dht_channel', data);

      res.end();
    });


    router.get('/hello', function(req, res, next) {
      console.log('Hello tool.Up! #' + count);
      io.emit('hello', count);
      count++;
      res.end();
    });
    return router;
}
