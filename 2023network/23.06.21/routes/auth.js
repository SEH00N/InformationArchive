const express = require('express');
const paxxport = require('passport');

const {isLoggedIn, isNotLoggedIn} = require('../middlewares');
const {join, login, logout} = require('../controllers/auth');

const router = express.Router();

router.post('/join', isNotLoggedIn, join);
router.post('/login', isNotLoggedIn, login);
router.post('/logout', isLoggedIn, logout);

module.exports = router;