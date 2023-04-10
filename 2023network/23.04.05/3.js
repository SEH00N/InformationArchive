const { odd, even } = require('./1.js');
const checkNum = require('./2.js');

function checkStringOddOrEven(str) {
    if(str.length % 2) {
        return odd;
    } else
        return even;
}

console.log(checkNum(10));
console.log(checkStringOddOrEven('hello'));