const WebSocket = require('ws');

const ws = new WebSocket.Server({
    port: 8080,
    perMessageDeflate: {
        zlibDeflateOptions: {
            chunkSize: 1024,
            memLevel: 7,
            level: 3
        },
        zlibInflateOptions: {
            chunkSize: 10 * 1024
        },

        clientNoContextTakeover: true,
        serverNoContextTakeover: true,
        serverMaxWindowBits: 10,

        concurrencyLimit: 10,
        threshold: 1024

    }
});


ws.on('open', function open() {
    ws.send('something');
});

ws.on('message', function incoming(data) {
    console.log(data);
});

ws.on('open', function open() {
    const array = new Float32Array(5);

    for (var i = 0; i < array.length; ++i) {
        array[i] = i / 2;
    }

    ws.send(array);
});


server.on('upgrade', function upgrade(request, socket, head) {
    const pathname = url.parse(request.url).pathname;

    authenticate(request, (err, client) => {
        if (err || !client) {
            socket.write('HTTP/1.1 401 Unauthorized\r\n\r\n');
            socket.destroy();
        }
    })

        if (pathname === '/update') {
            ws.handleUpgrade(request, socket, head, function done(ws) {
                ws.emit('connection', ws, request);
            });
        } else if (pathname === '/sync') {
            ws.handleUpgrade(request, socket, head, function done(ws) {
                ws.emit('connection', ws, request);
            });
        } else {
            socket.destroy();
        }
})