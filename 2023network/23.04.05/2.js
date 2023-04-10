const { odd, even } = require('./1.js');

function checkOddOrEven(num) {
    if(num % 2) {
        return odd;
    }
    else return even;
}

module.exports = checkOddOrEven;