const express = require('express')
const app = express();
const wsModule = require('ws');
const math = require('mathjs')
var fs = require('fs')

const { SerialPort, ReadlineParser } = require('serialport');
const KalmanFilter = require('kalmanjs');

// Hard coded Co-ordinates
var coord = [[10, 10, 3], [-10, -10, 2], [7, 5, 1], [-6, -8, 4]]
// 실제 거리
var dist = [0, 0, 0, 0]

// 기준거리(1m)에서의 신호 세기
const rssi_0 = -47.18641666102252;


const port = new SerialPort({
	path: 'COM11',
	baudRate: 9600
});
const parser = new ReadlineParser();

port.pipe(parser);

app.use("/", (req, res) => {
	res.sendFile(__dirname + '/scene.html');
});

const HTTPServer = app.listen(80, () => {
	console.log("Server is open at port 80");
});

const webSocketServer = new wsModule.Server(
	{
		server: HTTPServer,
	}
);

webSocketServer.on('connection', (ws, request) => {
	const ip = request.headers['x-forwarded-for'] || request.connection.remoteAddress;
	console.log(`새로운 클라이언트[${ip}] 접속`);

	var prev_rssi_list = new Array();
	var module_list = new Array();
	var rssi_sum = new Array();
	var prev_val = 0;

	for (var i = 0; i < 4; i++) {
		prev_rssi_list[i] = new Array();
		module_list[i] = new KalmanFilter(-50, 3);
		rssi_sum[i] = 0;
	}

	parser.on('data', function (data) {
		console.log('Origin Data:', data);
		var obj = JSON.parse(data);
		var filtered_rssi;
		console.log(obj.val);
		var flag;
		var cur_val = Number(obj.val);
		if(prev_val>=cur_val) {
			prev_val = 0;
			return;
		}
		prev_val = cur_val;
		if (obj.name == 'PE1') {
			flag = 0;
		} else if (obj.name == 'PE2') {
			flag = 1;
		} else if (obj.name == 'PE3') {
			flag = 2;
		} else if (obj.name == 'TAG') {
			flag = 3;
		}

		if(obj.name == 'TAG') {
			fs.appendFile('4m_json_9.txt' , data+'\n', (err) => console.log(err));
			fs.appendFile('4m_RSSI_9.txt' , obj.rssi+'\n', (err) => console.log(err));
		}
		

		if(prev_rssi_list[flag].length < 80) {
			filtered_rssi = module_list[flag].filter(obj.rssi);
			prev_rssi_list[flag].push(filtered_rssi);
			rssi_sum[flag] = rssi_sum[flag]*0.8 + filtered_rssi;
			return;
		}


		// outlier
		if(obj.rssi < rssi_sum[flag] / 5 - 3 || obj.rssi > rssi_sum[flag] / 5 + 3) {
			return;
		}
		filtered_rssi = module_list[flag].filter(obj.rssi);
		rssi_sum[flag] = (rssi_sum[flag] * 0.8 + filtered_rssi);
		
		// Calculate 3D-Position
		var ret = calculate(coord, dist)
		ret[0] = ret[0].toFixed(2);
		ret[1] = ret[1].toFixed(2);
		ret[2] = ret[2].toFixed(2);
		console.log('Parsed:', ret);
		console.log('rssi_average:', rssi_sum[flag] / 5);
		ws.send(`${ret[0]},${ret[1]},${ret[2]}`);

		
		if(obj.name == 'TAG') {
			fs.appendFile('4m_FILTERED_RSSI_9.txt' , filtered_rssi+'\n', (err) => console.log(err));
		}
		// if (obj.name == 'PE2') {
		// 	fs.appendFile('PE2_rssi_1m.txt', obj.rssi + '\n', (err) => console.log(err));
		// 	fs.appendFile('PE2_filtered_rssi_1m.txt', filtered_rssi + '\n', (err) => console.log(err));
		// }
	});


	// ws.on('message', (msg) => {
	// 	console.log(`클라이언트[${ip}]에게 수신한 메시지 : ${msg}`);
	// })

	ws.on('error', (error) => {
		console.log(`클라이언트[${ip}] 연결 에러발생 : ${error}`);
	})

	ws.on('close', () => {
		console.log(`클라이언트[${ip}] 웹소켓 연결 종료`);
	})
});

// @param: coord, distance
// coord => [[x1, y1, z1], [x2, y2, z2], [x3, y3, z3], [x4, y4, z4]]
// distances => [d1, d2, d3, d4] 
function calculate(coord, distances) {
	let mA = new Array();
	let mb = new Array();
	for (let i = 0; i < 3; i++) {
		mA[i] = new Array();
		let x0 = coord[i][0];
		let x1 = coord[i + 1][0];
		let y0 = coord[i][1];
		let y1 = coord[i + 1][1];
		let z0 = coord[i][2];
		let z1 = coord[i + 1][2];
		mA[i][0] = 2 * (x1 - x0);
		mA[i][1] = 2 * (y1 - y0);
		mA[i][2] = 2 * (z1 - z0);
		mb[i] = distances[i] * distances[i] - distances[i + 1] * distances[i + 1];
		mb[i] += (x1 * x1 + y1 * y1 + z1 * z1) - (x0 * x0 + + y0 * y0 + z0 * z0);
	}
	let invertedA = math.inv(mA);
	return math.multiply(invertedA, mb);
}

function Distance(rssi) {
	return 10 ** ((rssi_0 - Number(rssi)) / 10 / 2);
}

