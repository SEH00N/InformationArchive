const http = require('http');

const server = http.createServer((req, res) => {
    res.writeHead(200, { 
        'Content-Type': 'text/html; charset=utf-8' 
    });
    res.write('<h1> Hello, Node!</h1>');
    res.end('<p>이수현 바보</p>');
});

server.listen(8080);

server.on('listening', () => {
    console.log('8080번 포트에서 서버 대기중!');
});

server.on('error', (err) => {
    console.error(err);
});

const server1 = http.createServer((req, res) => {
    res.writeHead(200, { 
        'Content-Type': 'text/html; charset=utf-8' 
    });
    res.write('<h1> Hello, Node!</h1>');
    res.end('<p>이수현 바보</p>');
});

server1.listen(8081);