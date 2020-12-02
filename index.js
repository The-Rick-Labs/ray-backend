const express = require('express')
var cors = require('cors')

app = express()
app.use(cors())
let SerialPort = require('serialport')

let sp = new SerialPort('COM3', { baudRate: 9600 })
sp.on('open', () => {
	console.log('Opened Serial Port')
})

app.get('/smiley', (req, res) => {
	console.log('smiley')
	sp.write('h')
	res.send(':]')
})

app.get('/blink', (req, res) => {
	console.log('blink')
	sp.write('1')
	res.send('b')
})

app.get('/meh', (req, res) => {
	console.log('meh')
	sp.write('l')
	res.send(':|')
})

app.get('/sad', (req, res) => {
	sp.write('s')
	console.log('sad')
	res.send('[:')
})

app.get('/uwu', (req, res) => {
	sp.write('b')
	console.log('UwU')
	res.send('UwU')
}).listen(8080, () => {
	console.log('Server on')
})
