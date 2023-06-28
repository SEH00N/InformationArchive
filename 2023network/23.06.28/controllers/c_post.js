const { Post, Hashtag } = require('../models');

//이미지 업로드
exports.afterUploadImage = (req, res) => {
  console.log(req.file); //이미지를 업로드하면 req.file이 생김
  res.json({ url: `/img/${req.file.filename}` }); //업로드 된 이미지를 프론트로 보내줌.
  //나중에 프론트에서 메인 페이지에 이미지가 뜨게 됨(프론트에 구현되어 있음)
};
//app.js에서 uploads 폴더 static 추가!!! 중요
//이미지 업로드까지 하고 실행해서 이미지 업로드 되는지 확인

//게시글 포스트
//req.body.content에는 게시글 내용이 들어있고
//req.body.url에는 사진 url이 들어있음
exports.uploadPost = async (req, res, next) => {
  try {
    //그러면 프론트에서 걔네를 받아서 데이터베이스에 저장
    const post = await Post.create({
      content: req.body.content,
      img: req.body.url,
      UserId: req.user.id, //로그인한 유저 객체에서 id 가져오기
    });

    //예를 들어서 누군가가 쓴 게시글이
    //여친 구해요. #여친 #남친 이런식이라고 치면
    //# 해시태그 문자를 추출해야함 (정규표현식...)
    const hashtags = req.body.content.match(/#[^\s#]*/g); //#과 (공백 또는 #이 아닌 나머지)
    //결과로는 hashtags = ['#여친', '#남친'] 이렇게 저장
    if (hashtags) {
      const result = await Promise.all(
        hashtags.map(tag => {
          return Hashtag.findOrCreate({ //기존 해시태그가 있으면 가져오고, 없으면 만들어서 가져옴
            where: { title: tag.slice(1).toLowerCase() }, //#빼고 대문자는 소문자로
          })
        }),
      );
      await post.addHashtags(result.map(r => r[0])); //post랑 해시태그랑 이어줌
    }
    res.redirect('/');
  } catch (error) {
    console.error(error);
    next(error);
  }
};