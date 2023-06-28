const express = require('express');
const cookieParser = require('cookie-parser');
const session = require('express-session');
const morgan = require('morgan');
const path = require('path');
const nunjucks = require('nunjucks');
const dotenv = require('dotenv');
const passport = require('passport');

const { sequelize } = require('./models');
const passportConfig = require('./passsport');

dotenv.config();
passportConfig();

const pageRouter = require('./routes/page');
const authRouter = require('./routes/auth');
const postRouter = require('./routes/post');

const app = express();
app.set('port', 8081);
app.set('view engine', 'html');
nunjucks.configure('views', {
    express: app,
    watch: true, 
});

sequelize.sync().then(() => {
    console.log('DB 연결 성공');
}).catch((err) => {
    console.error(err);
});

app.use(morgan('dev'));

//public 폴더에서 정적 파일 제공
app.use(express.static(path.join(__dirname, 'public')));
app.use('/img', express.static(path.join(__dirname, 'uploads')));

//json, form 요청 설정
app.use(express.json());
app.use(express.urlencoded({extended: false}));

//쿠키와 세션에 대한 옵션
app.use(cookieParser(process.env.COOKIE_SECRET));
app.use(session({
    resave: false,
    saveUninitialized: false,
    secret: process.env.COOKIE_SECRET,
    cookie: {
        httpOnly: true,
        secure: false,
    }
}));

app.use(passport.initialize());
app.use(passport.session());

app.use('/', pageRouter);
app.use('/auth', authRouter);
app.use('/post', postRouter);

//404 NOT FOUND
app.use((req, res, next) => {
    const err = new Error(`${req.method} ${req.url} 라우터가 없습니다.`);
    err.status = 404;
    next(err);
});

//기타 미들웨어
app.use((err, req, res, next) => {
    res.locals.message = err.message;
    res.locals.error = process.env.NODE_ENV !== 'production' ? err : {};
    res.status(err.stats || 500);
    res.render('error');
});

//포트에 서버 등록
app.listen(app.get('port'), () => {
    console.log(app.get('port'), '번 포트에서 대기중');
});