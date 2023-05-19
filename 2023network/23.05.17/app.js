const express = require('express');
const path = require('path');

const morgan = require('morgan');
const cookieParser = require('cookie-parser');
const session = require('express-session');
const dotenv = require('dotenv');

dotenv.config();

const app = express();
app.set('port', 8081);
app.use(morgan('dev'));
app.use(cookieParser());
app.use(express.urlencoded({ extended: false }));
app.use(session({
    resave:false,
    saveUninitialized:false,
    secret: process.env.COOKIE_SECRET,
    cookie: {
        httpOnly:true,
        secure:false,
    },
    name:'session-cookie',
}));

app.get('/', (req, res) => {
    if (req.session?.name) {
        res.send(`안녕하세요 ${req.session.name}`);
    } else {
        res.sendFile(path.join(__dirname, '/cookie_index.html'));
    }
});

app.post('/', (req, res) => {
    req.session.name = req.body.name;
    res.redirect('/');
});

app.get('/delete', (req, res) => {
    res.clearCookie('name').redirect('/');
});

app.get('/cookie', (req, res) => {
    res.cookie('name', '민성', {
        httpOnly: true,
        path: '/',
    }).redirect('/');
});

app.get('/about', (req, res) => {
    res.send('Hello, About!');
});

app.get(encodeURI('/about/민성'), (req, res) => {
    res.send(`잘생겼농!`);
});

app.get('/about/:name', (req, res) => {
    res.send(`Hello, ${req.params.name}!`);
});

app.use((req, res, next) => {
    res.status(404).send('404 NOT FOUND');
});

app.use((err, req, res, next) => {
    console.log(err);
    res.send('에러났다 ㅋ')
});

app.listen(app.get('port'), () => {
    console.log(app.get('port'), '번 포트에서 대기 중');
});