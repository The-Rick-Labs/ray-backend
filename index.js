const express = require('express')
const readline = require('readline')
var cors = require('cors')
const util = require('util')

const fs = require('fs')
const { google } = require('googleapis')
const { json } = require('express')
const { list } = require('serialport')
const SCOPES = ['https://www.googleapis.com/auth/calendar.readonly']
const TOKEN_PATH = 'token.json'

app = express()
app.use(cors())
let SerialPort = require('serialport')

let sp = new SerialPort('COM3', { baudRate: 9600 })
sp.on('open', () => {
	console.log('Opened Serial Port')
})

app.get('/calendar', (req, response) => {
	const readfile = util.promisify(fs.readFile)

	const client_secret = 'Xmb0-96Q00ycZhrXWJ1igt5q'
	const client_id = '363244684321-6tnu9aq351rpofbkqnvamhdg8jo8ntn0.apps.googleusercontent.com'
	const redirect_uris = 'http://localhost:3000'
	const oAuth2Client = new google.auth.OAuth2(client_id, client_secret, redirect_uris)
	// Check if we have previously stored a token.

	readfile('token.json')
		.then((data) => {
			return JSON.parse(data)
		})
		.then(async (data) => {
			await oAuth2Client.setCredentials(data)
			return oAuth2Client
		})
		.then((auth) => {
			const calendar = google.calendar({ version: 'v3', auth })
			calendar.events.list(
				{
					calendarId: 'primary',
					timeMin: new Date().toISOString(),
					maxResults: 10,
					singleEvents: true,
					orderBy: 'startTime',
				},
				(err, res) => {
					if (err) return console.log('The API returned an error: ' + err)
					const events = res.data.items
					// console.log(events)
					response.send({ items: events })
					// temp(events)
					// return events
				}
			)
		})

	// response.send('hello')
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
