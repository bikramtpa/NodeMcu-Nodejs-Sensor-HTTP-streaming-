var app = require('express')();
var server = require('http').Server(app);
var io = require('socket.io')(server);

server.listen(3000, "0.0.0.0", function(){
	console.log("server started on port - 3000")
});
var socket2; 
var ctr = 1;
//app.use(express.static('views'));

app.get('/', function (req, res) {
  res.sendFile(__dirname + '/views/index.html');
  //socket2.emit('news', { msg: req.query.BPM });	
});

app.post('/', function(req, res){
	//console.log(req);
	io.sockets.emit('transmit', { msg: req.query});
});



io.on('connection', function (socket) {
  socket2 = socket;
  io.sockets.emit('transmit', { msg: 'Connected to Device' });
  socket.on('my other event', function (data) {
  });
});