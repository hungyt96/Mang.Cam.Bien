var fs = require('fs');
var url = require('url');
var http = require('http');
var WebSocket = require('ws');
var querystring = require('querystring');// Module giúp chuyển string sang object
var db = []; //database
var mysql = require('mysql');
// function gửi yêu cầu(response) từ phía server hoặc nhận yêu cầu (request) của client gửi lên

function requestHandler(request, response) {

    // Giả sử địa chỉ nhận được http://192.168.1.7:8000/update?temp=30&humd=40
    var uriData = url.parse(request.url);
    var pathname = uriData.pathname;          // /update?
    var query = uriData.query;                // temp=30.5&hum=80
    var queryData = querystring.parse(query); // queryData.temp = 30.5, queryData.humd = 40
    //-----------------------------------------------------------------------------------------
    if (pathname == '/update') {
        var newData = {
            temp: queryData.temp,
            hum: queryData.hum,
            time: new Date()
        };
        db.push(newData);
        console.log(newData);
        response.end();
    //-----------------------------------------------------------------------------------------
    } else if (pathname == '/get') {
        response.writeHead(200, {
            'Content-Type': 'application/json'
        });
        response.end(JSON.stringify(db));
        db = [];
    //-----------------------------------------------------------------------------------------
    } else { 
        fs.readFile('index.html', function(error, content) {
            response.writeHead(200, {
                'Content-Type': 'text/html'
            });
            response.end(content);
        });
    }
    //-----------------------------------------------------------------------------------------
    var con = mysql.createConnection({
			host: "localhost",
			user: "root",
			password: "13071996",
			database: "wsn"
		});

		con.connect(function(err) {
			var temp = queryData.temp;
            var hum = queryData.hum;
            var time = new Date();
  			if (err) throw err;
  			console.log("Connected!");
  			var sql = "INSERT INTO b4 (temp, hum, time) VALUES ('" + temp + "', '" + hum + "', '" + time + "')";
  			con.query(sql, function (err, result) {
    		if (err) throw err;
    		console.log("Number of records inserted: " + result.affectedRows);
  				});
		});
}
// create http server
var server = http.createServer(requestHandler);
var ws = new WebSocket.Server({ server });
var clients = [];

function broadcast(socket, data) {
    console.log(clients.length);
    for(var i=0; i<clients.length; i++) {
        if(clients[i] != socket) {
            clients[i].send(data);
        }
    }
}
ws.on('connection', function(socket, req) {
    clients.push(socket);

    socket.on('message', function(message) {
        console.log('received: %s', message);
        broadcast(socket, message);
    });

    socket.on('close', function() {
        var index = clients.indexOf(socket);
        clients.splice(index, 1);
        console.log('disconnected');
    });
});

server.listen(3000);
console.log('Server listening on port 3000');
