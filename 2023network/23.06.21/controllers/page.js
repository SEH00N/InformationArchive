exports.renderProfile = (req, res) => {
    res.render('profile', {title: '내 정보 - NodeSNS'});
};

exports.renderJoin = (req, res) => {
    res.render('join', {title: '회원가입 - NodeSNS'});
};

exports.renderMain = (req, res) => {
    const twits = [];
    res.render('main', {title: 'NodeSNS', twits, });
};