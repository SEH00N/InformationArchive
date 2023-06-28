const express = require('express');
const multer = require('multer');
const path = require('path');
const fs = require('fs');

const { afterUploadImage, uploadPost } = require('../controllers/c_post');
const { isLoggedIn } = require('../middlewares/index');

const router = express.Router();

//uploads 폴더가 없으면 생성
//uploads 폴더 하위에 사용자들의 사진 파일 저장
try {
  fs.readdirSync('uploads');
} catch (error) {
  console.error('uploads 폴더가 없어 uploads 폴더를 생성합니다.');
  fs.mkdirSync('uploads');
}

const upload = multer({
  storage: multer.diskStorage({
    destination(req, file, cb) {
      cb(null, 'uploads/');
    },
    filename(req, file, cb) {
      const ext = path.extname(file.originalname);
      cb(null, path.basename(file.originalname, ext) + Date.now() + ext);
    },
  }),
  limits: { fileSize: 5 * 1024 * 1024 },
});

// POST /post/img
// 로그인을 해야 이미지 업로드 가능
router.post('/img', isLoggedIn, upload.single('img'), afterUploadImage);

// POST /post
// 로그인을 해야 게시글 등록 가능
const upload2 = multer();
router.post('/', isLoggedIn, upload2.none(), uploadPost);

module.exports = router; //-->app.js에 연결