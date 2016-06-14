$(document).ready(function() {

  var socket = io();

  socket.on('arduino', function(data) {
    var color = "rgba(" + parseInt((Math.random()*255), 10) + ", " + parseInt((Math.random()*255), 10) + ", " + parseInt((Math.random()*255), 10) + ", 1)";
    console.log(color);
    var textshow = "0 0 10px rgba(255, 255, 255, 1), 0 0 20px rgba(255, 255, 255, 1), 0 0 30px rgba(255, 255, 255, 1), 0 0 40px " + color + ", 0 0 70px " + color + ", 0 0 80px " + color + ", 0 0 100px " + color;
    $(".icon-bulb").css("text-shadow", textshow);

  });

});
