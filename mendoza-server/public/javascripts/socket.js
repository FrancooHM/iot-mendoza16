$(document).ready(function() {

  var socket = io();

  socket.on('dht_channel', function(data) {
    if (data.t>25){
      var red = 255 ;
      var blue = 0 ;
    }else{
      var red = 0 ;
      var blue = 255 ;
    }

    var green = 0;
    var color = "rgba(" + parseInt(red) + ", " + parseInt(green) + ", " + parseInt(blue) + ", 1)";
    console.log(color);
    var textshow = "0 0 10px rgba(255, 255, 255, 1), 0 0 20px rgba(255, 255, 255, 1), 0 0 30px rgba(255, 255, 255, 1), 0 0 40px " + color + ", 0 0 70px " + color + ", 0 0 80px " + color + ", 0 0 100px " + color;
    $(".icon-bulb").css("text-shadow", textshow);
    console.debug(data);
  });

  socket.on('hello', function(data) {
    var color = "rgba(" + parseInt((Math.random()*255), 10) + ", " + parseInt((Math.random()*255), 10) + ", " + parseInt((Math.random()*255), 10) + ", 1)";
    console.log(color);
    var textshow = "0 0 10px rgba(255, 255, 255, 1), 0 0 20px rgba(255, 255, 255, 1), 0 0 30px rgba(255, 255, 255, 1), 0 0 40px " + color + ", 0 0 70px " + color + ", 0 0 80px " + color + ", 0 0 100px " + color;
    $(".icon-bulb").css("text-shadow", textshow);
    console.debug(data);
  });

});
