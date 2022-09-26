const app = require('express')();
const http = require('http').Server(app);
const { io } = require('socket.io-client')(http);

const {SerialPort, ReadlineParser} = require('serialport');
const port = new SerialPort({
    path : 'COM11',
    baudRate : 115200
});
const parser = new ReadlineParser();

// socket.io 서버에 접속한다
var socket = io.connect('http://http://54.180.221.87:80/');
const webSocket = new WebSocket("ws://54.180.221.87");
// socket.emit('login',{
//     userid: $('#userID').val() // 접속한 회원 정보
// });

port.pipe(parser);

parser.on('data', function(data) {
    console.log('Data:', data);
    socket.emit('Data', data);
    webSocket.send(`증가하는 숫자를 보냅니다 => ${data}`); // 웹소켓 서버에게 메시지 전송
});

//서버로부터의 메시지가 수신되면
socket.on("message", function(data) {
    alert(data);  
});

// //테스트
// $('#form_btn').on('click',function(){
//     socket.emit('message', {
//         message: $('#test_form').serialize()
//     });
// });
