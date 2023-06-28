const bcrypt = require('bcrypt');
const passport = require('passport');
const User = require('../models/user');

exports.join = async(req, res, next) => {
    const {email, nick, password} = req.body;

    try {
        const exUser = await User.findOne({where:{email}});
        if(exUser) {
            return res.redirect('/join?error=exist');
        }

        const hash = await bcrypt.hash(password, 12);
        await User.create({
            email,
            nick,
            password:hash
        });

        return res.redirect('/');
    } catch(err) {
        console.error(err);
        return next(err);
    }
}

exports.login = async(req, res, next) => {
    try {
        passport.authenticate('local', (authErr, user, info) => {
            if(authErr) {
                console.error(authErr);
                return next(authErr);
            }
            if(!user){
                return res.redirect(`/?loginError=${info.message}`);
            }

            return req.login(user, (loginErr) => {
                if(loginErr) {
                    console.errror(loginErr);
                    return next(loginErr);
                }

                return res.redirect('/');
            });
        })(req, res, next);
    } catch(err) {

    }
}

exports.logout = async(req, res, next) => {
    req.logout(() => {
        res.redirect('/');
    });
}