#!node

let sh = require('shelljs');
let URL = require('url');
let fs = require('fs');
const URL_PREFIX = "/speak/wav/", URL_PREFIX_LEN = URL_PREFIX.length;
require('http').createServer((req, res)=>{
	if(!req.url.startsWith(URL_PREFIX)) {
		res.statusCode = 404;
		res.end("Service not found.");
		return;
	}
	let toSpeakText = decodeURIComponent(req.url.substring(URL_PREFIX_LEN));

	let tmpFile = `${__dirname}/tmp/q${Date.now()}.wav`;
	let x = sh.ShellString(toSpeakText.toBase64())
			.exec(`${__dirname}/speak_to_file.exe ${tmpFile.toBase64()}`, function(retCode) {
				if(retCode === 0) {
					res.setHeader('Content-Type', 'audio/wav');
					let stream = fs.createReadStream(tmpFile);
					stream.pipe(res);
					stream.on('end', function(){
						sh.rm(tmpFile);
					})
				} else {
					res.statusCode = 500;
					res.end("ERROR");
				}
			});
	
}).listen(50805);

String.prototype.toBase64 = function() {
	return new Buffer(this.toString(), "UTF-16LE").toString('base64')
};
