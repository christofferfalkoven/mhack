/*jslint es5:true, indent: 2 */
/*global Vue, io */
/* exported vm */
'use strict';
var socket = io();

var beep = (function () {
  let frequency = 50;
  let period = 1/frequency;
  let ctxClass = window.AudioContext;
  let ctx = new ctxClass();
  return function (times, finishedCallback) {
    if (typeof finishedCallback !== "function") {
      finishedCallback = function () {};
    }
    let osc = ctx.createOscillator();
    let currentTime = ctx.currentTime;
    osc.type = "square";
    osc.frequency.value = frequency;

    osc.connect(ctx.destination);
    osc.start(currentTime);
    osc.stop(currentTime + period * times);

    setTimeout(function () {
      finishedCallback();
    }, period * times);
  };
})();

    var vm = new Vue({
      el: '#dots',
      data: {
        eyePos: {},
      },
      created: function () {
        /************
        HERE YOU CAN WRITE NEW LISTENERS IF YOU NEED
        ************/

        socket.on('move:eyes', function (data) {
          this.eyePos = data;
        }.bind(this));

        // The motor commands are transferred to the Arduino by sound pulses
        socket.on('move:motors', function (motors) {
          const {left, right} = motors;
          const letTheMoverKnowItHasBeenDone = function() {
            socket.emit('moved:motors', motors);
          }

          if (left && !right) {
            beep(1, letTheMoverKnowItHasBeenDone);
          }
          if (left && right) {
            beep(3, letTheMoverKnowItHasBeenDone);
          }
          if (!left && right) {
            beep(2, letTheMoverKnowItHasBeenDone);
          }
          if (!left && !right) {
            beep(4, letTheMoverKnowItHasBeenDone);
          }
        });
        socket.on('move:white', function () {
           const letTheMoverKnowItHasBeenDone = function() {
             socket.emit('moved:white');
           }
           beep(6, letTheMoverKnowItHasBeenDone);
        });
        socket.on('move:red', function () {
          const letTheMoverKnowItHasBeenDone = function() {
            socket.emit('moved:red');
          }
          beep(7, letTheMoverKnowItHasBeenDone);
        });
        socket.on('move:green', function () {
          const letTheMoverKnowItHasBeenDone = function() {
            socket.emit('moved:green');
          }
          beep(8, letTheMoverKnowItHasBeenDone);
        });
        socket.on('move:blue', function () {
          const letTheMoverKnowItHasBeenDone = function() {
            socket.emit('moved:blue');
          }
          beep(9, letTheMoverKnowItHasBeenDone);
        });
        socket.on('move:incrBr', function () {
          const letTheMoverKnowItHasBeenDone = function() {
            socket.emit('moved:incrBr');
          }
          beep(5, letTheMoverKnowItHasBeenDone);
        });
        socket.on('move:decrBr', function () {
          const letTheMoverKnowItHasBeenDone = function() {
            socket.emit('moved:decrBr');
          }
          beep(10, letTheMoverKnowItHasBeenDone);
        });  
      }
    });
