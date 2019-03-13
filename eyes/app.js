/*jslint node: true */
/* eslint-env node */
'use strict';

// Require express, socket.io, and vue
var express = require('express');
var app = express();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var path = require('path');
var ip = require("ip");

// Pick arbitrary port for server
var port = 3000;
app.set('port', (process.env.PORT || port));

// Serve static assets from public/
app.use(express.static(path.join(__dirname, 'public/')));
// Serve vue from node_modules as vue/
app.use('/vue', express.static(path.join(__dirname, '/node_modules/vue/dist/')));
// Serve index.html directly as root page
app.get('/', function (req, res) {
  res.sendFile(path.join(__dirname, 'views/index.html'));
});
app.get('/mover', function (req, res) {
  res.sendFile(path.join(__dirname, 'views/mover.html'));
});



io.on('connection', function (socket) {

/********************
HERE YOU CAN ADD COMMAND MESSAGES.
These are not associated with any logical operations
*********************/
  socket.on('move:eyes', function (eyes) {
    io.emit('move:eyes', eyes);
  });
  socket.on('move:motors', function (motors) {
    io.emit('move:motors', motors);
  });
  socket.on('move:servo', function (motors) {
    io.emit('move:servo', motors);
  });
  // For now, this is just to confirm...
  socket.on('moved:motors', function (motors) {
    io.emit('moved:motors', motors);
  });
  socket.on('moved:servo', function () {
    io.emit('moved:servo');
  });
  socket.on('move:white', function () {
    io.emit('move:white');
  });
  socket.on('moved:white', function () {
    io.emit('moved:white');
  });
  socket.on('move:red', function () {
    io.emit('move:red');
  });
  socket.on('moved:red', function () {
    io.emit('moved:red');
  });
  socket.on('move:green', function () {
    io.emit('move:green');
  });
  socket.on('moved:green', function () {
    io.emit('moved:green');
  });
  socket.on('move:blue', function () {
    io.emit('move:blue');
  });
  socket.on('moved:blue', function () {
    io.emit('moved:blue');
  });
  socket.on('move:incrBr', function () {
    io.emit('move:incrBr');
  });
  socket.on('moved:incrBr', function () {
    io.emit('moved:incrBr');
  });
  socket.on('move:decrBr', function () {
    io.emit('move:decrBr');
  });
  socket.on('moved:decrBr', function () {
    io.emit('moved:decrBr');
  });

});

var server = http.listen(app.get('port'), function () {
  console.log('Server listening on localhost:' + app.get('port') + ' and http://' + ip.address() + ':' + app.get('port'));
});
