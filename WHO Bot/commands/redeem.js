module.exports.run = async (bot, message, args, userData) => {

  var fs = require('fs');
  // var userData = JSON.parse(fs.readFileSync('Storage/userData.json', 'utf8'));
  var codes = JSON.parse(fs.readFileSync('Storage/codes.json', 'utf8'));
  let sender = message.author;
  let who = 265957683260030976;
  console.log("redeem");
  let code1 = "code1";
  let code2 = "code2";
  let code3 = "code3";
  let code4 = "code4";
  let code5 = "code5";
  let code6 = "code6";
  let code7 = "code7";
  let code8 = "code8";
  let code9 = "code9";
  let code1337 = "code1337";

  function redeemlvl1(){userData[sender.id].whosCollected += 100; message.channel.send({embed:{title: 'Valid code!', description: 'Your code has successfully been entered! You have recieved 100 WHO?s!'}}); console.log(sender.username + ' has succesfully redeemed a valid code. Message: ' + message.content);}
  function redeemlvl2(){userData[sender.id].whosCollected += 250; message.channel.send({embed:{title: 'Valid code!', description: 'Your code has successfully been entered! You have recieved 250 WHO?s!'}}); console.log(sender.username + ' has succesfully redeemed a valid code. Message: ' + message.content);}
  function redeemlvl3(){userData[sender.id].whosCollected += 500; message.channel.send({embed:{title: 'Valid code!', description: 'Your code has successfully been entered! You have recieved 500 WHO?s!'}}); console.log(sender.username + ' has succesfully redeemed a valid code. Message: ' + message.content);}
  function redeemlvl1337(){userData[sender.id].whosCollected += 1337; message.channel.send({embed:{title: 'Valid code!', description: 'Your code has successfully been entered! You have recieved 1337 WHO?s!'}}); console.log(sender.username + ' has succesfully redeemed a valid code. Message: ' + message.content);}
  function used(){message.channel.send({embed:{title: 'Used code!', description: 'Your code has already been used!'}});}

  if (message.channel.type = 'dm')
  {
    console.log(sender.username + " is trying to redeem a code.");
    if(args[0] == codes[code1].code){if(codes[code1].used == 0){redeemlvl1(); if(sender.id != who) {codes[code1].used = 1;}} else {used();}}
    else if(args[0] == codes[code3].code){if(codes[code3].used == 0 || sender.id == who){redeemlvl1(); if(sender.id != who) {codes[code3].used = 1;}} else {used();}}
    else if(args[0] == codes[code2].code){if(codes[code2].used == 0 || sender.id == who){redeemlvl1(); if(sender.id != who) {codes[code2].used = 1;}} else {used();}}
    else if(args[0] == codes[code4].code){if(codes[code4].used == 0 || sender.id == who){redeemlvl1(); if(sender.id != who) {codes[code4].used = 1;}} else {used();}}
    else if(args[0] == codes[code5].code){if(codes[code5].used == 0 || sender.id == who){redeemlvl2(); if(sender.id != who) {codes[code5].used = 1;}} else {used();}}
    else if(args[0] == codes[code6].code){if(codes[code6].used == 0 || sender.id == who){redeemlvl2(); if(sender.id != who) {codes[code6].used = 1;}} else {used();}}
    else if(args[0] == codes[code7].code){if(codes[code7].used == 0 || sender.id == who){redeemlvl2(); if(sender.id != who) {codes[code7].used = 1;}} else {used();}}
    else if(args[0] == codes[code8].code){if(codes[code8].used == 0 || sender.id == who){redeemlvl3(); if(sender.id != who) {codes[code8].used = 1;}} else {used();}}
    else if(args[0] == codes[code9].code){if(codes[code9].used == 0 || sender.id == who){redeemlvl3(); if(sender.id != who) {codes[code9].used = 1;}} else {used();}}
    else if(args[0] == codes[code1337].code){if(codes[code1337].used == 0 || sender.id == who){redeemlvl1337(); if(sender.id != who) {codes[code1337].used = 1;}} else {used();}}
    else {message.channel.send({embed:{title: 'Invalid code!', description: 'Contact WHO? if your code didn\'t work.'}}); console.log(sender.username + 'has failed to redeem a valid code. Message: ' + message.content);}
    fs.writeFile('Storage/codes.json', JSON.stringify(codes), (err) => {
      if (err) console.log(err);
    });
    fs.writeFile('Storage/userData.json', JSON.stringify(userData, null, 2), (err) => {
      if (err) console.log(err);
    });
  }
}

module.exports.config = {
  command: 'redeem'
}
