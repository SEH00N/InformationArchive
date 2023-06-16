const express = require('express');

const router = express.Router();

router.get('/', (req, res) => {
    if (req.session?.name) {
        res.send(`안녕하세요 ${req.session.name}`);
    } else {
        res.sendFile(path.join(__dirname, '/cookie_index.html'));
    }
});

router.post('/', (req, res) => {
    res.session.name = req.body.name;
    res.redirect('/');
});

module.exports = router;