const express = require('express')

app = express()

app.get('/smiley', (req, res) => {
	console.log('smiley')
	res.send(':]')
})
app.get('/sad', (req, res) => {
	console.log('sad')
	res.send('[:')
})
app.get('/uwu', (req, res) => {
	console.log('UwU')
	res.send('UwU')
}).listen(8080, () => {
	console.log('Server on')
})
