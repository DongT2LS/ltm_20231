const net = require('net');

const serverAddress = '127.0.0.1'; // Replace with your TCP server's address
const serverPort = 5000;           // Replace with your TCP server's port

const client = net.createConnection({ host: serverAddress, port: serverPort }, () => {
  // 'connect' listener
  console.log('Connected to TCP server');
  
  // Send a message to the TCP server
  client.write('Hello, TCP server!');
});

client.on('data', (data) => {
  console.log('Received from TCP server:', data.toString());
  // Close the connection after receiving a response
  client.end();
});

client.on('end', () => {
  console.log('Disconnected from TCP server');
});

client.on('error', (err) => {
  console.error('Error:', err);
});

client.on('close', () => {
  console.log('Connection closed');
});