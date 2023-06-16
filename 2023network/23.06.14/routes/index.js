const express = require('express');
const User = require('../models/user.js');

const router = express.Router();

router.get('/', async(req, res, next) => {
    try {
        const users = await User.findAll();
        res.render('sequelize', {users});
    } catch (err) {
        console.error(err);
        next(err);
    }
});

module.exports = router;