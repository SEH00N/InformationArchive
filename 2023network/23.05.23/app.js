const express = require('express');
const path = require('path');
const fs = require('fs');

const morgan = require('morgan');
const multer = require('multer');

const cookieParser = require('cookie-parser');
const session = require('express-session');
const dotenv = require('dotenv');

const indexRouter = require('./routes/index.js');

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

try {
    fs.readdirSync('uploads');
} catch(err) {
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

app.use('/', indexRouter);

app.get('/upload', (req, res) => {
    res.sendFile(path.join(__dirname, 'multipart.html'));
});

app.post('/upload', upload.array('image'), (req, res) => {
    console.log(req.files);
    res.send('ok');
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