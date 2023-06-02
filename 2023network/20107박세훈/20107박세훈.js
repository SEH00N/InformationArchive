const express = require('express');
const session = require('express-session');
const multer = require('multer');
const fs = require('fs');
const path = require('path');
const env = require('dotenv');

env.config();

const app = express();
app.set('port', 3000);
app.use(session({
    resave: false,
    saveUninitialized: false,
    secret: process.env.PW,
    cookie: {
        httpOnly: true,
        secure: false,
    },
    name: 'session-cookie',
}));

try {
    fs.readdirSync('uploads');
} catch (err) {
    console.error('uploads 폴더가 없어서 생성함 ㅋ');
    fs.mkdirSync('uploads');
}

const upload = multer({
    storage: multer.diskStorage({
        destination(req, file, done) {
            done(null, 'uploads/');
        },
        filename(req, file, done) {
            const ext = path.extname(file.originalname);
            done(null, path.basename(file.originalname, ext) + Date.now() + ext);
        }
    }),
    limits: {
        fileSize: 5 * 1024 * 1024,
    }
});

app.get('/', (req, res) => {
    res.send(`20107 박세훈, ${req.session.name}`);
});

app.get('/session/:name', (req, res) => {
    req.session.name = req.params.name;
    res.redirect('/');
});

app.get('/pic', (req, res) => {
    res.sendFile(path.join(__dirname, 'multipart.html'));
});

app.post('/upload', upload.array('image'), (req, res) => {
    req.session.pic = req.files[0];
    res.send('ok');
});

app.get('/user', (req, res) => {
    if (req.session.name == undefined) {
        res.send('사용자가 등록되어 있지 않습니다.');
    } else if (req.session.pic == undefined) {
        res.redirect('/pic');
    } else {
        res.send(`${req.session.name} | ${req.session.pic}`);
        // const file = fs.readFileSync(__dirname, 'user.html',  (err, data) => {
        //     const img = document.createElement('img');          
        //     img.src = req.session.pic;
        //     document.body.appendChild(img);

        //     const p = document.createElement('p');
        //     p.appendChild(document.createTextNode('동적으로 추가된 텍스트'));

        //     document.body.appendChild(p);
        // });
        // res.sendFile(file);
    }
});

app.use((req, res, next) => {
    res.status(404).send('404 NOT FOUND');
    res.status(500).send('500 err');
});

app.use((err, req, res, next) => {
    console.log(err);
    res.send('에러났다 ㅋ')
});

app.listen(app.get('port'), () => {
    console.log(app.get('port'), '번 포트에서 대기 중');
});