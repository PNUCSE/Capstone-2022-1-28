const math = require('mathjs')

// coord는 [[x1, y1, z1], [x2, y2, z2], [x3, y3, z3], [x4, y4, z4]]
// distances는 [d1, d2, d3, d4] 형태로 넣으면 돼요
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


// tag pos = [1,1,1]
coord = [[0,0,2],[3,0,1.7],[0,3,1.4],[4,0,1.1]]
real_dist = [1.73205, 2.34307,  2.27156, 3.16385]
real_pos = calculate(coord, real_dist)
console.log(real_pos)

